#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/msg.h>
#include "operation.h"

struct record *head;
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

void write_to_file(){
        FILE *file=fopen("data.txt","w");
        if(file==NULL){
                printf("error in opening file in write mode\n");
                return;
        }
        struct record *current=head;
        while(current!=NULL){
                fprintf(file,"%s %s %d %s %s %d %s\n",current->firstName,current->lastName,current->emp_id,current->contact,current->skills,current->exp,current->project);
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
        while(fscanf(file,"%s %s %d %s %s %d %s\n",data.firstName,data.lastName,&data.emp_id,data.contact,data.skills,&data.exp,data.project)!=EOF){
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
        fclose(file);
}
