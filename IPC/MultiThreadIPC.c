#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "beagleblack_lcd.h"


#define SOCK_PATH "lcd_socket"

void fillPinout(lcd_pinout *lcd) {
    lcd -> en = 68; //P8_10
    lcd -> rs = 67; //P8_8
    lcd -> db_7 = 44; //P8_12
    lcd -> db_6 = 26; //P8_14
    lcd -> db_5 = 46; //P8_16
    lcd -> db_4 = 65; //P8_1
    
}

char *extractData(char *data) {
    char *pch;
    pch = strstr(data, "\"data\":\"") + strlen("\"data\":\"");
    return pch;
}

void *checkSwitch(void *param) {
    int current_value;
    gpio_export(60);
    current_value = gpio_get_value(60);
    while(1) {
        if (gpio_get_value(60) != current_value) {
            printf("Vrijednost se promijenila i sad je %d\n", !current_value);
            current_value = !current_value;
        }
    }
}

void *IPC_server(void *param) {
    int s, s2, t, len;
    char *pch;
    lcd_pinout *lcd = (lcd_pinout *)param;
    struct sockaddr_un local, remote;
    char str[100], data[50];

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }

    for(;;) {
        int done, n;
        printf("Waiting for a connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

        done = 0;
        do {
            n = recv(s2, str, 100, 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
                done = 1;
            }

            if (!done) {
                pch = strstr(str, "}");
                pch++;
                *pch = 0;
                printf("Primio %s \n", str);
                strcpy(data, extractData(str));
                data[strlen(data) - 2] = '\0';
                printf("Extracted: %s\n", data);
                lcd_clear(lcd);
                lcd_print(lcd, data);
                if (send(s2, str, n, 0) < 0) {
                    perror("send");
                    done = 1;
                }
                //lcd_print(lcd, str);
               
            }
        } while (!done);
        close(s2);
    }
}

int main() {
    
    pthread_t lcd_socket_thread;
    pthread_t switch_thread;
    lcd_pinout lcd;
    fillPinout(&lcd);
    lcd_init(&lcd);
    
    
    if (pthread_create(&lcd_socket_thread, NULL, IPC_server, &lcd)) {
        fprintf(stderr, "Greska prilikom stvaranja socket dretve\n");
        return 1;
    }
    
//    if (pthread_create(&switch_thread, NULL, checkSwitch, NULL)) {
//        fprintf(stderr, "Greska prilikom stvaranja socket dretve\n");
//        return 1;
//    }

    
    sleep(-1);
    
    return 0;    
}
