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
	printf("2.DELETE\n");
	printf("3.LIST\n");
	printf("4.SEARCH\n");
	printf("5.LIST BY EXP\n");
	printf("6.LIST BY SKILLS\n");
	printf("7.SORT\n");

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
		case 2:
			strcpy(msg1.pckmem.operation,"DELETE");
			getchar();
			printf("enter employee id to delete:");
			scanf("%d",&msg1.pckmem.data.emp_id);
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
		case 3:
			strcpy(msg1.pckmem.operation,"LIST");
			getchar();
			msg1.pckmem.endOfPacket='\0';
			if(msgsnd(msgid1,&msg1,sizeof(struct message),0)==-1){
                                printf("error in sending msg client side\n");
                                exit(EXIT_FAILURE);
                        }

                        printf("message sent to server\n");
			while(1){
				if(msgrcv(msgid2,&msg2,sizeof(struct message),getpid(),0)==-1){
					printf("error in reciving msg client side\n");
                                        exit(EXIT_FAILURE);
                                }
				if(strcmp(msg2.pckmem.data.firstName,"exit")==0){
					break;
				}
				printf("firstname: %s,lastname:%s, emp_id: %d, contact:%s, skills:%s, exp:%d, project: %s\n\n",msg2.pckmem.data.firstName,msg2.pckmem.data.lastName,msg2.pckmem.data.emp_id,msg2.pckmem.data.contact,msg2.pckmem.data.skills,msg2.pckmem.data.exp,msg2.pckmem.data.project);
			}
                        break;
		case 4:
			strcpy(msg1.pckmem.operation,"SEARCH");
			printf("1.search based on firstname\n 2.search based on lastname\n 3.search based on emp_id\n");
			printf("enter which search you want:");
			int x;
			scanf("%d",&x);
			if(x==1){
				printf("enter firstname:");
				getchar();
				scanf("%s",msg1.pckmem.data.firstName);
				getchar();
			}
			if(x==2){
				printf("enter lastname:");
                                getchar();
                                scanf("%s",msg1.pckmem.data.lastName);
                                getchar();
			}
			if(x==3){
				printf("enter emp_id:");
                                getchar();
                                scanf("%d",&msg1.pckmem.data.emp_id);
                                getchar();
			}

			msg1.pckmem.endOfPacket='\0';
			msg1.pckmem.data.exp=x;
                        if(msgsnd(msgid1,&msg1,sizeof(struct message),0)==-1){
                                printf("error in sending msg client side\n");
                                exit(EXIT_FAILURE);
                        
			}

                        printf("message sent to server\n");
			
			while(1){
				if(msgrcv(msgid2,&msg2,sizeof(struct message),getpid(),0)==-1){
					printf("error in reciving msg client side\n");
                                        exit(EXIT_FAILURE);
                               }
			       if(strcmp(msg2.pckmem.data.firstName,"exit")==0){
				       break;
			       }
                               printf("firstname: %s\n",msg2.pckmem.data.firstName);
		 	       printf("lastname: %s\n",msg2.pckmem.data.lastName);
			       printf("emp_id: %d\n",msg2.pckmem.data.emp_id);
			       printf("contact: %s\n",msg2.pckmem.data.contact);
			       printf("skills: %s\n",msg2.pckmem.data.skills);
			       printf("exp: %d\n",msg2.pckmem.data.exp);
			       printf("project: %s\n",msg2.pckmem.data.project);
			}

                        break;
		case 5:
			strcpy(msg1.pckmem.operation,"LIST BY EXP");
			printf("enter the exp:");
			getchar();
			scanf("%d",&msg1.pckmem.data.exp);
			getchar();
			msg1.pckmem.endOfPacket='\0';
			if(msgsnd(msgid1,&msg1,sizeof(struct message),0)==-1){
				printf("error in sending msg client side\n");
				exit(EXIT_FAILURE);
			}

			printf("message sent to server\n");
			while(1){
				if(msgrcv(msgid2,&msg2,sizeof(struct message),getpid(),0)==-1){
					printf("error in recieving msg client side\n");
					exit(EXIT_FAILURE);
				}
				if(strcmp(msg2.pckmem.data.firstName,"exit")==0){
					break;
				}
				 printf("firstname: %s\n",msg2.pckmem.data.firstName);
				 printf("lastname: %s\n",msg2.pckmem.data.lastName);
				 printf("emp_id: %d\n",msg2.pckmem.data.emp_id);
				 printf("contact: %s\n",msg2.pckmem.data.contact);
				 printf("skills: %s\n",msg2.pckmem.data.skills);
				 printf("exp: %d\n",msg2.pckmem.data.exp);
				 printf("project: %s\n",msg2.pckmem.data.project);
				 printf("\n\n");
			}
			break;
		
		case 6:
			strcpy(msg1.pckmem.operation,"LIST BY SKILLS");
			printf("enter the skill:");
			getchar();
			scanf("%s",msg1.pckmem.data.skills);
			getchar();
			msg1.pckmem.endOfPacket='\0';
			if(msgsnd(msgid1,&msg1,sizeof(struct message),0)==-1){
				printf("error in sending msg client side\n");
				exit(EXIT_FAILURE);
			}
			printf("message sent to server\n");
			while(1){
				if(msgrcv(msgid2,&msg2,sizeof(struct message),getpid(),0)==-1){
					printf("error in recieving msg client side\n");
					exit(EXIT_FAILURE);
				}
				if(strcmp(msg2.pckmem.data.firstName,"exit")==0){
					break;
				}
				 printf("firstname: %s\n",msg2.pckmem.data.firstName);
				 printf("lastname: %s\n",msg2.pckmem.data.lastName);
				 printf("emp_id: %d\n",msg2.pckmem.data.emp_id);
				 printf("contact: %s\n",msg2.pckmem.data.contact);
				 printf("skills: %s\n",msg2.pckmem.data.skills);
				 printf("exp: %d\n",msg2.pckmem.data.exp);
				 printf("project: %s\n",msg2.pckmem.data.project);
				 printf("\n\n");
			}
			break;
		 case 7:
                        strcpy(msg1.pckmem.operation,"SORT");
                        printf("1.sort based on firstname\n 2.sort based on lastname\n 3.sort based on emp_id\n");
                        printf("enter which sort you want:");
                        int y;
                        scanf("%d",&y);
                        if(y==1){
				printf("sort by firstname\n");
                        }
                        if(y==2){
                                printf("sort by lastname\n");
                        }
                        if(y==3){
                                printf("sort by emp_id\n");
                        }

                        msg1.pckmem.endOfPacket='\0';
                        msg1.pckmem.data.exp=y;
                        if(msgsnd(msgid1,&msg1,sizeof(struct message),0)==-1){
                                printf("error in sending msg client side\n");
                                exit(EXIT_FAILURE);

                        }

                        printf("message sent to server\n");

                        while(1){
                                if(msgrcv(msgid2,&msg2,sizeof(struct message),getpid(),0)==-1){
                                        printf("error in reciving msg client side\n");
                                        exit(EXIT_FAILURE);
                               }
                               if(strcmp(msg2.pckmem.data.firstName,"exit")==0){
				       break;
			       }
                               printf("firstname: %s\n",msg2.pckmem.data.firstName);
                               printf("lastname: %s\n",msg2.pckmem.data.lastName);
                               printf("emp_id: %d\n",msg2.pckmem.data.emp_id);
                               printf("contact: %s\n",msg2.pckmem.data.contact);
                               printf("skills: %s\n",msg2.pckmem.data.skills);
                               printf("exp: %d\n",msg2.pckmem.data.exp);
                               printf("project: %s\n",msg2.pckmem.data.project);
                        }

                        break;


                default:
                        printf("Invalid operation\n");
                        exit(EXIT_FAILURE);
        }
return 0;

}
