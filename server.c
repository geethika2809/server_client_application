#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<pthread.h>
#include "operation.h"

pthread_mutex_t mutex;
int msgid1;
int msgid2;
struct message msg1;

void perform_operation(struct message *msg1){
        if(strcmp(msg1->pckmem.operation,"ADD")==0){
                add_record(msg1);
        }
	if(strcmp(msg1->pckmem.operation,"DELETE")==0){
		delete_record(msg1);
	}
	if(strcmp(msg1->pckmem.operation,"LIST")==0){
                list_record(msg1);
        }
}

void *client_handler(void *arg) {
    struct message *msg1 = (struct message *)arg;

    pthread_mutex_lock(&mutex);
    perform_operation(msg1);
    pthread_mutex_unlock(&mutex);

    printf("Operation Done: %s\n",msg1->pckmem.operation);

    pthread_exit(NULL);
}

int main() {
    key_t key1=123;
    key_t key2=456;

    pthread_mutex_init(&mutex, NULL);

    msgid1=msgget(key1,0666 | IPC_CREAT);
    if(msgid1==-1) {
        printf("error in msgget recieve of server");
        exit(EXIT_FAILURE);
    }

    msgid2=msgget(key2,0666 | IPC_CREAT);
    if(msgid2==-1){
            printf("error in msgget send of server");
            exit(EXIT_FAILURE);
    }

    printf("Server started.\n");

    read_from_file();

    while(1) {
        if(msgrcv(msgid1,&msg1,sizeof(struct message),0,0)==-1) {
            printf("error in msgrcv server side");
            exit(EXIT_FAILURE);
        }

        printf("Received message from client of type :%d\n", msg1.mtype);

        pthread_t client_thread;
        if(pthread_create(&client_thread,NULL,client_handler,(void *)&msg1)!=0) {
            printf("error in pthread_create");
            exit(EXIT_FAILURE);
        }
        if(pthread_join(client_thread,NULL)!=0){
                printf("error in pthread_join");
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}
