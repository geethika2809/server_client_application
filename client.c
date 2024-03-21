#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include"operation.h"

int msgid1;
int msgid2;
struct message msg1;
struct message msg2;

int main(){
        key_t key1=123;
        key_t key2=456;


        msgid1=msgget(key1,0666|IPC_CREAT);
        if(msgid1==-1){
                printf("error in msg send client side\n");
                exit(EXIT_FAILURE);
        }

        msgid2=msgget(key2,0666|IPC_CREAT);
        if(msgid2==-1){
                printf("error in msg recive client side");
                exit(EXIT_FAILURE);
        }
        printf("select operation:\n");
        printf("1.ADD\n");

        printf("enter operation number:");
        int op;
        scanf("%d",&op);
        msg1.mtype=getpid();

        switch(op){
                case 1:
                        strcpy(msg1.pckmem.operation,"ADD");
                        getchar();
                        printf("enter firstname:");
                        scanf("%[^\n]s",msg1.pckmem.data.firstName);
                        getchar();
                        printf("enter lastName:");
                        scanf("%[^\n]s",msg1.pckmem.data.lastName);
                        getchar();
                        printf("enter employee id:");
                        scanf("%d",&msg1.pckmem.data.emp_id);
                        getchar();
                        printf("enter contact:");
                        scanf("%[^\n]s",msg1.pckmem.data.contact);
                        getchar();
                        printf("enter skills:");
                        scanf("%[^\n]s",msg1.pckmem.data.skills);
                        getchar();
                        printf("enter experience:");
                        scanf("%d",&msg1.pckmem.data.exp);
                        getchar();
                        printf("enter project:");
                        scanf("%[^\n]s",msg1.pckmem.data.project);
                        getchar();

                        msg1.pckmem.endOfPacket='\0';
                        if(msgsnd(msgid1,&msg1,sizeof(struct message),0)==-1){
                                printf("error in sending msg client side\n");
                                exit(EXIT_FAILURE);
                        }

                        printf("message sent to server\n");
                        if(msgrcv(msgid2,&msg2,sizeof(struct message),getpid(),0)==-1){
                                printf("error in reciving msg client side\n");
                                exit(EXIT_FAILURE);
                        }
                        printf("client recieved %s\n",msg2.pckmem.data.firstName);
                        break;

                default:
                        printf("Invalid operation\n");
                        exit(EXIT_FAILURE);
        }
return 0;

}
