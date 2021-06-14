#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
    int value;
    struct Node* next;
};
typedef struct Node Node;

struct SLList {
    struct Node* head;
    struct Node* tail;
    int size;
};
typedef struct SLList SLList;

char* freadline(FILE* fp);

void empty(SLList* list);
SLList initList ();
void insertNode (SLList *list, int item);
void printList (SLList list);

int main(){
    /////////////////////////////////////// part 1

    // FILE *fp = fopen("input.txt", "r");
    // printf("`%s`\n", freadline(fp));
    // printf("`%s`\n", freadline(fp));
    // printf("`%s`\n", freadline(fp));
    // printf("`%s`\n", freadline(fp));

    /////////////////////////////////////// part 2
    SLList list = initList();

    insertNode(&list, 1);
    insertNode(&list, 2);
    insertNode(&list, 3);

    printList(list);
    printf("\nsize = %d \n", list.size);

    empty(&list);
    printf("\nsize after empty = %d \n", list.size);
    printList(list);

    return 0;
}

////////////////////////////////////////////////////////////////////////////
//                                part 1                                  //
////////////////////////////////////////////////////////////////////////////

// Implement a function char* freadline(FILE* fp) that reads a line from fp and returns it. Use the function fgets defined in stdio.h; the returned char* must have the exact memory allocated as needed. (that is, sizeof(line) == strlen(line) + 1) (10 pts)
char* freadline(FILE* fp){
    char buffer[255];

    if (fgets(buffer, 255, fp) != NULL){
        char *line = malloc(strlen(buffer));
        strcpy(line, buffer);

        return line;
    }

    else
        return NULL;

}


////////////////////////////////////////////////////////////////////////////
//                                part 2                                  //
////////////////////////////////////////////////////////////////////////////

// Implement a function void empty(SLList* list) that empties and frees the nodes of the singly-linked list. (5 pts)
void empty(SLList* list){
    Node *current = list->head;
    Node *next = current->next;

    for (int i=0; list->size!=0; i++){
        list->head = next;              // move head to the next node

        free(current);                  // frees the memory used by current node
        list->size--;

        current = next;                 // move current and next pointer
        next = next->next;
    }

    return;
}

SLList initList (){
    SLList list;

    list.head = 0;
    list.tail = 0;
    list.size = 0;

    return list;
}

void insertNode (SLList *list, int item){
    // initialize node
    Node *n = (Node*) malloc(sizeof (Node));
    n->value = item;

    // insert node to list
    if (list->size == 0){
        list->head = n;
        list->tail = n;
    }

    else {
        list->tail->next = n;
        list->tail = n;
    }

    list->size++;

    return;
}

// print list for debugging purposes
void printList (SLList list){
    Node *current = list.head;

    for (int i=0; i<list.size; i++){
        printf("%d ", current->value);

        current = current->next;
    }

    return;
}