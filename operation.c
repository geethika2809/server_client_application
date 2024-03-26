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

int arrayStore(struct record *head,struct record **arr,int n){
	int c=0;
	while(head!=NULL && c<n){
		arr[c++]=head;
		head=head->next;
	}
	return c;
}

void merge_fn(struct record **arr,int lb,int mid,int ub){
    int i,j,k;
    int n1=mid-lb+1;
    int n2=ub-mid;

    struct record* L[n1];
    struct record* R[n2];

    for(i=0;i<n1;i++)
        L[i]=arr[lb+i];
    for (j=0;j<n2;j++)
        R[j]=arr[mid+1+j];
    i=0;
    j=0;
    k=lb;
    while(i<n1 && j<n2) {
        if(strcmp(L[i]->firstName,R[j]->firstName)<=0) {
            arr[k]=L[i];
            i++;
        } else {
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1) {
	arr[k]=L[i];
        i++;
        k++;
    }
    while (j<n2) {
        arr[k]=R[j];
        j++;
        k++;
    }
}

void mergesort_fn(struct record **arr,int lb,int ub){
	if(lb<ub){
		int mid=(lb+ub)/2;
		mergesort_fn(arr,lb,mid);
		mergesort_fn(arr,mid+1,ub);
		merge_fn(arr,lb,mid,ub);
	}
}

void merge_ln(struct record **arr,int lb,int mid,int ub){
    int i,j,k;
    int n1=mid-lb+1;
    int n2=ub-mid;

    struct record* L[n1];
    struct record* R[n2];

    for(i=0;i<n1;i++)
        L[i]=arr[lb+i];
    for (j=0;j<n2;j++)
        R[j]=arr[mid+1+j];
    i=0;
    j=0;
    k=lb;
    while(i<n1 && j<n2) {
        if(strcmp(L[i]->lastName,R[j]->lastName)<=0) {
            arr[k]=L[i];
            i++;
        } else {
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1) {
        arr[k]=L[i];
        i++;
        k++;
    }
    while (j<n2) {
        arr[k]=R[j];
        j++;
        k++;
    }
}

void mergesort_ln(struct record **arr,int lb,int ub){
        if(lb<ub){
                int mid=(lb+ub)/2;
                mergesort_ln(arr,lb,mid);
                mergesort_ln(arr,mid+1,ub);
                merge_ln(arr,lb,mid,ub);
        }
}

void merge_emp(struct record **arr,int lb,int mid,int ub){
    int i,j,k;
    int n1=mid-lb+1;
    int n2=ub-mid;

    struct record* L[n1];
    struct record* R[n2];

    for(i=0;i<n1;i++)
        L[i]=arr[lb+i];
    for (j=0;j<n2;j++)
        R[j]=arr[mid+1+j];
    i=0;
    j=0;
    k=lb;
    while(i<n1 && j<n2) {
        if(L[i]->emp_id<=R[j]->emp_id) {
            arr[k]=L[i];
            i++;
        } else {
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1) {
        arr[k]=L[i];
        i++;
        k++;
    }
    while (j<n2) {
        arr[k]=R[j];
        j++;
        k++;
    }
}

void mergesort_emp(struct record **arr,int lb,int ub){
        if(lb<ub){
                int mid=(lb+ub)/2;
                mergesort_emp(arr,lb,mid);
                mergesort_emp(arr,mid+1,ub);
                merge_emp(arr,lb,mid,ub);
        }
}
	


void sort_record(struct message *msg1){
	if(head==NULL){
		printf("no elements\n");
		return;
	}
	int n=100;
	struct record* arr[n];
	int c=arrayStore(head,arr,n);
	if(msg1->pckmem.data.exp==1){
		mergesort_fn(arr,0,c-1);
		for(int i=0;i<c;i++){
			strcpy(msg2.pckmem.data.firstName, arr[i]->firstName);
                        strcpy(msg2.pckmem.data.lastName,arr[i]->lastName);
                        msg2.pckmem.data.emp_id=arr[i]->emp_id;
                        strcpy(msg2.pckmem.data.contact,arr[i]->contact);
                        strcpy(msg2.pckmem.data.skills,arr[i]->skills);
                        msg2.pckmem.data.exp=arr[i]->exp;
                        strcpy(msg2.pckmem.data.project,arr[i]->project);
			msg2.mtype=msg1->mtype;
                        if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
				printf("error in msgsnd sender side");
                                exit(EXIT_FAILURE);
                        }
		}
	}
	if(msg1->pckmem.data.exp==2){
                mergesort_ln(arr,0,c-1);
                for(int i=0;i<c;i++){
                        strcpy(msg2.pckmem.data.firstName,arr[i]->firstName);
                        strcpy(msg2.pckmem.data.lastName,arr[i]->lastName);
                        msg2.pckmem.data.emp_id=arr[i]->emp_id;
                        strcpy(msg2.pckmem.data.contact,arr[i]->contact);
                        strcpy(msg2.pckmem.data.skills,arr[i]->skills);
                        msg2.pckmem.data.exp=arr[i]->exp;
                        strcpy(msg2.pckmem.data.project,arr[i]->project);
                        msg2.mtype=msg1->mtype;
                        if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
                                printf("error in msgsnd sender side");
                                exit(EXIT_FAILURE);
                        }
                }
        }
	if(msg1->pckmem.data.exp==3){
                mergesort_emp(arr,0,c-1);
                for(int i=0;i<c;i++){
                        strcpy(msg2.pckmem.data.firstName,arr[i]->firstName);
                        strcpy(msg2.pckmem.data.lastName,arr[i]->lastName);
                        msg2.pckmem.data.emp_id=arr[i]->emp_id;
                        strcpy(msg2.pckmem.data.contact,arr[i]->contact);
                        strcpy(msg2.pckmem.data.skills,arr[i]->skills);
                        msg2.pckmem.data.exp=arr[i]->exp;
                        strcpy(msg2.pckmem.data.project,arr[i]->project);
                        msg2.mtype=msg1->mtype;
                        if(msgsnd(msgid2,&msg2,sizeof(struct message),0)==-1){
                                printf("error in msgsnd sender side");
                                exit(EXIT_FAILURE);
                        }
                }
        }
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
