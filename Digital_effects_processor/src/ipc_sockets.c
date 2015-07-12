#include "ipc_sockets.h"
#include "user_interface.h"



#define TYPE_OFFSET 9
#define JSON_MAX_LENGTH 20

void adjustEffects();

void *ipc_audio_effects(void *arg) {
    processor_t *processor = (processor_t *) arg;
    
    int server_socket, client_socket, remote_length, address_length;
    
    socket_address_unix local, remote;
    
    char buffer[100], data[50];
    char *pch;
    
    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Error opening audio server socket!\n");
        return NULL;
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, AUDIO_RACK_PATH);
    unlink(local.sun_path);
    
    address_length = strlen(local.sun_path) + sizeof(local.sun_family);
    remote_length = sizeof(remote);
    
    if (bind(server_socket, (socket_address *)&local, address_length) == -1) {
        perror("Error binding server socket with local address!\n");
        return NULL;
    }

    if (listen(server_socket, SERVER_QUEUE_LENGTH) == -1) {
        perror("Error while starting server!\n");
        return NULL;
    }

    while(1) {
        int done, message_length;
        fprintf(stderr, "Waiting for a connection...\n");
        
        if ((client_socket = accept(server_socket, (socket_address *)&remote, &remote_length)) == -1) {
            perror("Error while accepting client!\n");
            return NULL;
        }
        fprintf(stderr, "Connected.\n");
        
        done = 0;
        do {
            message_length = recv(client_socket, buffer, sizeof(buffer), 0);
            if (message_length == -1) {
                perror("Error while receiving message!");
                done = 1;
            }
            
            if (message_length == 0) {
                done = 1;
            }

            if (!done) {
                pch = strstr(buffer, "}");
                pch++;
                *pch = 0;
                fprintf(stderr, "Primio poruku %s\n", buffer);
                adjustEffects(processor, buffer);
            }
                
        } while (!done);
        close(client_socket);
    }
    return NULL;
}

void *ipc_data_out(void *arg) {
    
    
    return NULL;
}

void adjustEffects(processor_t *processor, char *message) {
    char *type_t, *data_t, type[JSON_MAX_LENGTH], data[JSON_MAX_LENGTH];
    double data_value;
    
    if(message[0] != '{' || message[strlen(message) - 1] != '}') {
        return;
    }
    
    /** Parse JSON from IPC **/
    type_t = strstr(message, "{\"type\":\"");
    type_t += strlen("{\"type\":\"");
    data_t = strstr(type_t, "\"");
    *data_t = '\0';
    strcpy(type, type_t);
    data_t += 1;
    data_t += strlen("\"data\":\"");
    type_t = strstr(data_t, "}");
    *type_t = '\0';
    strcpy(data, data_t);
    
    /** Log data **/
    fprintf(stderr, "TYPE: %s , DATA: %s\n", type, data);
    
    data_value = atof(data);
    
    if (!strcmp(type, "gain")) {
        processor -> dist -> gain = data_value/10;
    } else if (!strcmp(type, "psaturation")) {
        processor -> dist -> psaturation = data_value/100;
    } else if (!strcmp(type, "nsaturation")) {
        processor -> dist -> nsaturation = data_value/100;
    } else if (!strcmp(type, "decay")) {
        processor -> reverb -> decay = data_value/100;
    } else if (!strcmp(type, "delay")) {
        setDelay(processor -> reverb -> delayLine, data_value / 100 * 15000);
    } else if (!strcmp(type, "eq_0")) {
        processor -> filter[0] -> dBgain = (data_value - 50)/4;
        processor -> filter[0] -> calcCoefficients(processor -> filter[0]);
    } else if (!strcmp(type, "eq_1")) {
        processor -> filter[1] -> dBgain = (data_value - 50)/4;
        processor -> filter[1] -> calcCoefficients(processor -> filter[1]);
    } else if (!strcmp(type, "eq_2")) {
        processor -> filter[2] -> dBgain = (data_value - 50)/4;
        processor -> filter[2] -> calcCoefficients(processor -> filter[2]);
    } else if (!strcmp(type, "eq_3")) {
        processor -> filter[3] -> dBgain = (data_value - 50)/4;
        processor -> filter[3] -> calcCoefficients(processor -> filter[3]);
    } else if (!strcmp(type, "eq_4")) {
        processor -> filter[4] -> dBgain = (data_value - 50)/4;
        processor -> filter[4] -> calcCoefficients(processor -> filter[4]);
    } else if (!strcmp(type, "eq_5")) {
        processor -> filter[5] -> dBgain = (data_value - 50)/4;
        processor -> filter[5] -> calcCoefficients(processor -> filter[5]);
    } else if (!strcmp(type, "eq_6")) {
        processor -> filter[6] -> dBgain = (data_value - 50)/4;
        processor -> filter[6] -> calcCoefficients(processor -> filter[6]);
    } else if (!strcmp(type, "eq_7")) {
        processor -> filter[7] -> dBgain = (data_value - 50)/4;
        processor -> filter[7] -> calcCoefficients(processor -> filter[7]);
    }
    
    return;
    
}