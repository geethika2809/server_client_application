#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/msg.h>
#include "operation.h"

static struct record *head=NULL;
struct message msg2;

void append_record(struct record *newnode){
        if(head==NULL){
                head=newnode;
                return;
        }
        struct record *current=head;
        while(current->next!=NULL){
                current=current->next;
        }
        current->next=newnode;
}

void add_record(struct message *msg1){
        struct record *newnode=(struct record *)malloc(sizeof(struct record));
        if(newnode==NULL){
                strcpy(msg2.pckmem.data.firstName,"memory allocation error\n");
                msg2.mtype=msg1->mtype;
                if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1) {
                        printf("error in msgsnd2 sender side");
                        exit(EXIT_FAILURE);
                }
                return;
        }

        strcpy(newnode->firstName,msg1->pckmem.data.firstName);
        strcpy(newnode->lastName,msg1->pckmem.data.lastName);
        strcpy(newnode->contact,msg1->pckmem.data.contact);
        strcpy(newnode->skills,msg1->pckmem.data.skills);
        strcpy(newnode->project,msg1->pckmem.data.project);
        newnode->emp_id=msg1->pckmem.data.emp_id;
        newnode->exp=msg1->pckmem.data.exp;
        newnode->next=NULL;
        append_record(newnode);
        write_to_file();
        msg2.mtype=msg1->mtype;
        strcpy(msg2.pckmem.data.firstName,"record added successfully\n");
        if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
                printf("error in msgsnd2 sender side");
                exit(EXIT_FAILURE);
        }

}

void delete_record(struct message *msg1){
	if(head==NULL){
		printf("list is empty\n");
		return;
	}
	struct record *current=head;
	struct record *prev=NULL;
	while(current!=NULL){
		if(current->emp_id==msg1->pckmem.data.emp_id){
			if(prev==NULL){
				head=current->next;
			}
			else{
				prev->next=current->next;
			}
			free(current);
			write_to_file();
			msg2.mtype=msg1->mtype;
			strcpy(msg2.pckmem.data.firstName,"record deleted\n");
			if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
				printf("error in msgsnd2 sender side");
                                exit(EXIT_FAILURE);
                        }
			return;
		}
		prev=current;
		current=current->next;
	}
	msg2.mtype=msg1->mtype;
	strcpy(msg2.pckmem.data.firstName,"record not found");
	if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
		printf("error in msgsnd2 sender side");
                exit(EXIT_FAILURE);
        }
}

void list_record(struct message *msg1){
	struct record *current=head;
	if(head==NULL){
		printf("no elements\n");
		return;
	}
	while(current!=NULL){
		strcpy(msg2.pckmem.data.firstName,current->firstName);
		strcpy(msg2.pckmem.data.lastName,current->lastName);
		msg2.pckmem.data.emp_id=current->emp_id;
		strcpy(msg2.pckmem.data.contact,current->contact);
		strcpy(msg2.pckmem.data.skills,current->skills);
		msg2.pckmem.data.exp=current->exp;
		msg2.mtype=msg1->mtype;
		strcpy(msg2.pckmem.data.project,current->project);
                if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
			printf("Error in msgsnd2 sender side");
                        exit(EXIT_FAILURE);
                }
		current=current->next;
	}
	msg2.mtype=msg1->mtype;
	strcpy(msg2.pckmem.data.firstName,"exit");
	if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
		printf("error in msgsnd2 sender side when exit");
		exit(EXIT_FAILURE);
	}
}

void search_record(struct message *msg1){
	struct record *current=head;
	if(head==NULL){
		printf("no elements\n");
		return;
	}
	while(current!=NULL){
		if(msg1->pckmem.data.exp==1){
			if(strcmp(msg1->pckmem.data.firstName,current->firstName)==0){
				printf("record found\n");
				strcpy(msg2.pckmem.data.firstName,current->firstName);
				strcpy(msg2.pckmem.data.lastName,current->lastName);
				msg2.pckmem.data.emp_id=current->emp_id;
				strcpy(msg2.pckmem.data.contact,current->contact);
				strcpy(msg2.pckmem.data.skills,current->skills);
				msg2.pckmem.data.exp=current->exp;
				strcpy(msg2.pckmem.data.project,current->project);
                        }
		}

		if(msg1->pckmem.data.exp==2){
			if(strcmp(msg1->pckmem.data.lastName,current->lastName)==0){
                                printf("record found\n");
                                strcpy(msg2.pckmem.data.firstName,current->firstName);
                                strcpy(msg2.pckmem.data.lastName,current->lastName);
                                msg2.pckmem.data.emp_id=current->emp_id;
                                strcpy(msg2.pckmem.data.contact,current->contact);
                                strcpy(msg2.pckmem.data.skills,current->skills);
                                msg2.pckmem.data.exp=current->exp;
				strcpy(msg2.pckmem.data.project,current->project);
			}
		}
		if(msg1->pckmem.data.exp==3){
			if(msg1->pckmem.data.emp_id==current->emp_id){
				printf("record found\n");
				strcpy(msg2.pckmem.data.firstName,current->firstName);
                                strcpy(msg2.pckmem.data.lastName,current->lastName);
                                msg2.pckmem.data.emp_id=current->emp_id;
                                strcpy(msg2.pckmem.data.contact,current->contact);
                                strcpy(msg2.pckmem.data.skills,current->skills);
                                msg2.pckmem.data.exp=current->exp;
				strcpy(msg2.pckmem.data.project,current->project);
				msg2.mtype=msg1->mtype;
				if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
					printf("error in msgsnd sender side exp3");
					exit(EXIT_FAILURE);
				}
				return;
			}
		}
		msg2.mtype=msg1->mtype;
		if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
			printf("error in msgsnd sender side exp1,2");
			exit(EXIT_FAILURE);
		}
		current=current->next;
	}
	msg2.mtype=msg1->mtype;
	strcpy(msg2.pckmem.data.firstName,"exit");
	if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
		printf("error in sending exit");
		exit(EXIT_FAILURE);
	}
	printf("record not found\n");
}


void listbyexp_record(struct message *msg1){
	if(head==NULL){
		printf("no elements\n");
		return;
	}
	struct record *current=head;
	while(current!=NULL){
		if(msg1->pckmem.data.exp==current->exp){
			strcpy(msg2.pckmem.data.firstName,current->firstName);
			strcpy(msg2.pckmem.data.lastName,current->lastName);
			msg2.pckmem.data.emp_id=current->emp_id;
			strcpy(msg2.pckmem.data.contact,current->contact);
			strcpy(msg2.pckmem.data.skills,current->skills);
			msg2.pckmem.data.exp=current->exp;
			strcpy(msg2.pckmem.data.project,current->project);
			msg2.mtype=msg1->mtype;
			if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
				printf("error in msgsnd sender side");
				exit(EXIT_FAILURE);
			}
		}
		current=current->next;
	}
	msg2.mtype=msg1->mtype;
	strcpy(msg2.pckmem.data.firstName,"exit");
	if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
		printf("error in msgsnd sender side");
		exit(EXIT_FAILURE);
	}
}

void listbyskills_record(struct message *msg1){
	if(head==NULL){
		printf("no elements\n");
		return;
	}
	struct record *current=head;
	while(current!=NULL){
		if(strcmp(msg1->pckmem.data.skills,current->skills)==0){
			 strcpy(msg2.pckmem.data.firstName,current->firstName);
			 strcpy(msg2.pckmem.data.lastName,current->lastName);
			 msg2.pckmem.data.emp_id=current->emp_id;
			  strcpy(msg2.pckmem.data.contact,current->contact);
			  strcpy(msg2.pckmem.data.skills,current->skills);
			  msg2.pckmem.data.exp=current->exp;
			  strcpy(msg2.pckmem.data.project,current->project);
			  msg2.mtype=msg1->mtype;
			  if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
				  printf("error in msgsnd sender side");
				  exit(EXIT_FAILURE);
			  }
	        }
		current=current->next;
	}
	msg2.mtype=msg1->mtype;
	strcpy(msg2.pckmem.data.firstName,"exit");
	if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
		printf("error in msgsnd sender side");
		exit(EXIT_FAILURE);
	}
}

	


void write_to_file(){
        FILE *file=fopen("data.txt","w");
        if(file==NULL){
                printf("error in opening file in write mode\n");
                return;
        }
        struct record *current=head;
        while(current!=NULL){
               fprintf(file,"%s,%s,%d,%s,%s,%d,%s\n",current->firstName,current->lastName,current->emp_id,current->contact,current->skills,current->exp,current->project);
               current=current->next;
        }
        fclose(file);
}

void read_from_file(){
        FILE *file=fopen("data.txt","r");
        if(file==NULL){
                printf("error in reading file\n");
                return;
        }
        struct record data;
	char line[100]; 

        while(fgets(line, sizeof(line), file) != NULL){
		if (sscanf(line,"%[^,],%[^,],%d,%[^,],%[^,],%d,%[^\n]", data.firstName, data.lastName, &data.emp_id, data.contact, data.skills, &data.exp, data.project) == 7) {
			printf("Reading data from file: %s %s %d %s %s %d %s\n", data.firstName, data.lastName, data.emp_id, data.contact, data.skills, data.exp, data.project);

                         struct record *newnode=(struct record*)malloc(sizeof(struct record));
                         if(newnode==NULL){
				 printf("memory allocation error\n");
                                 fclose(file);
                                 return;
                         }
                         strcpy(newnode->firstName,data.firstName);
                         strcpy(newnode->lastName,data.lastName);
                         strcpy(newnode->contact,data.contact);
                         strcpy(newnode->skills,data.skills);
                         strcpy(newnode->project,data.project);
                         newnode->emp_id=data.emp_id;
                         newnode->exp=data.exp;
                         newnode->next=NULL;
                         append_record(newnode);
           } 
	         else {
                         printf("Error parsing line: %s\n", line);
            }
    }

    fclose(file);
}
