/** @file ipc_sockets.h
 *
 * @brief header file for interprocess communication of NodeJs application and Digital Effects
 	processor application. Contains declarations of functions. Implementations can be found in 		ipc_sockets.c source file. File contatins documentation of functions.
 * @author Ivan Pavic
 * @version 1.0
 */
#ifndef _IPC_SOCKETS_H
#define _IPC_SOCKETS_H

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define AUDIO_RACK_PATH "/tmp/DEP_audio_rack"
#define AUDIO_DATA_PATH "/tmp/DEP_audio_data"
#define SERVER_QUEUE_LENGTH 10

typedef struct sockaddr_un socket_address_unix;
typedef struct sockaddr    socket_address;
/**
 * Task represents Inter-process communication server.
 * @param arg: explicitly casts to processor_t strcuture
 */
void *ipc_server(void *arg);
void *ipc_audio_effects(void *arg);

#endif
