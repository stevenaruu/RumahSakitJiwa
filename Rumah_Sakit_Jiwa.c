#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int pos = 6;

struct Data {
    char name[26];
    int age;
    char description[269];
    char code[10];
    int priorityCode;
    int pos;

    struct Data *next;
    struct Data *prev;

}*head = NULL, *tail = NULL, *curr = NULL;

struct Data *createData(char name[], int age, char description[], char code[], int priorityCode, int pos) {

    struct Data *node = (struct Data*)malloc(sizeof(struct Data));

    strcpy(node->name, name);
    node->age = age;
    strcpy(node->description, description);
    strcpy(node->code, code);
    node->priorityCode = priorityCode;
    node->pos = pos;
    
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void pushHead(struct Data *node) {

    if(head == NULL){
        head = tail = node;
    }else{
        node->next = head;
        head->prev = node;
        head = node;
    }


}

void pushTail(struct Data *node){
    
    if(head == NULL){
        head = tail = node;
    }else{
        node->prev = tail;
        tail->next = node;
        tail = node;
    }

}

void pushMid(struct Data *node) {

    if(head == NULL) {
        head = tail = node;
    }else if(node->priorityCode > head->priorityCode || (node->priorityCode == head->priorityCode && node->pos < head->pos)){
        pushHead(node);
    }else if(node->priorityCode < tail->priorityCode || (node->priorityCode == tail->priorityCode && node->pos > head->pos)){
        pushTail(node);
    }else{

        struct Data *curr;
        curr = head;

        while(node->priorityCode <= curr->priorityCode){
            if(node->priorityCode == curr->priorityCode && node->pos < curr->pos){
                break;
            }
            curr = curr->next;
        }

        node->prev = curr->prev;
        node->next = curr;
        curr->prev->next = node;
        curr->prev = node;

    }

}

void viewData() {

    int counter = 1;

    struct Data *curr;
    curr = head;

    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("|No   | Name                      | Age  | Description                                             | Code   |\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    while(curr != NULL) {
        printf("|%-4d | %-25s | %-4d | %-55s | %-6s |\n", counter, curr->name, curr->age, curr->description, curr->code);
        counter++;
        curr = curr->next;
    }

    printf("-------------------------------------------------------------------------------------------------------------\n");
    
    printf("Press Enter to continue ...\n");

}

void insertData() {

    char name[26];
    int age;
    char description[269];
    char code[10];
    int len;
    int priorityCode = 0;

    do {

        printf("Input patient name[4-25]: ");
        scanf(" %[^\n]", name);

        len = strlen(name);

    }while(len < 4 || len > 25);

    do {
        
        printf("Input patient age[>= 0]: ");
        scanf(" %d", &age);

    }while(age < 0);

    do {
        
        printf("Input description[>= 6]: ");
        scanf(" %[^\n]", description);

        len = strlen(description);

    }while(len < 6);

    int flag = 0;

    do {
        
        printf("Input code[Red|Yellow|Green]: ");
        scanf(" %[^\n]", code);

        if(strcmp(code, "Red") == 0){
            flag = 1;
            priorityCode = 3;
        }else if(strcmp(code, "Yellow") == 0){
            flag = 1;
            priorityCode = 2;
        }else if(strcmp(code, "Green") == 0){
            flag = 1;
            priorityCode = 1;
        }

    }while(flag != 1);

    printf("\nInsert success !\n");

    pushMid(createData(name, age, description, code, priorityCode, pos));
    pos++;

}

void nextQueue() {

    if(head == NULL) {
        printf("There is no queue yet !\n\n");
        printf("Press Enter to continue ...\n");
    }else{
        printf("The next patient is:\n");
        printf("Name            : %s\n", head->name);
        printf("Age             : %d\n", head->age);
        printf("Description     : %s\n", head->description);
        printf("Code            : %s\n\n", head->code);
        printf("Press Enter to continue ...\n");

        if(head == tail){
            free(head);
            head = NULL;
        }else{
            head->prev = NULL;
            head = head->next;
            free(head->prev);
        }

    }


}

int main(){ 

    // data dummy
    pushMid(createData("Mr. Budi", 34, "Serious injury from car accident", "Red", 3, 1));
    pushMid(createData("Mr. John", 45, "GERD", "Yellow", 2, 2));
    pushMid(createData("Mr. Doe", 23, "Cough and fever", "Green", 1, 3));
    pushMid(createData("Mrs. Carolina", 28, "Nausea, vomiting, sweating, and difficulties walking", "Yellow", 2, 4));
    pushMid(createData("Mrs. Taylor", 50, "Hard to breahte and chest pain", "Red", 3, 5));

    int input;

    do {

        system("cls");

        printf("Bluejack Hospital\n");
        printf("=================\n");
        printf("1. Insert\n");
        printf("2. View\n");
        printf("3. Next Queue\n");
        printf("4. Exit\n");
        printf(">> ");

        scanf("%d", &input);
        
        switch(input) {

            case 1:
                system("cls");
                insertData();
                getchar();
                break;
            case 2:
                system("cls");
                viewData();
                getchar();
                break;
            case 3:
                system("cls");
                nextQueue();
                getchar();
                break;
            case 4:
                printf("-- Thank You --");
                break;
            default:
                break;
        }

        getchar();

    }while(input != 4); 

}