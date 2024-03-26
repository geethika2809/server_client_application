#ifndef OPERATION_H
#define OPERATION_H

#define MAX_TEXT_SIZE 20
#define MAX_DATA_SIZE 20

struct record{
        char firstName[MAX_DATA_SIZE];
        char lastName[MAX_DATA_SIZE];
        int emp_id;
        char contact[MAX_DATA_SIZE];
        char skills[MAX_DATA_SIZE];
        int exp;
        char project[MAX_DATA_SIZE];
        struct record *next;
};

struct packet{
        char operation[MAX_DATA_SIZE];
        struct record data;
        char endOfPacket;
};

struct message{
        int mtype;
        struct packet pckmem;
};

extern int msgid1;
extern int msgid2;

extern struct message msg1;
extern struct message msg2;



void add_record(struct message *msg);
void append_node(struct record *newnode);
void delete_record(struct message *msg);
void list_record(struct message *msg);
void search_record(struct message *msg);
void listbyexp_record(struct message *msg);
void listbyskills_record(struct message *msg);
void sort_record(struct message *msg);
void write_to_file();
void read_from_file();

#endif
