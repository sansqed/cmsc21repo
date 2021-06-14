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

int main(){
    /////////////////////////////////////// part 1

    FILE *fp = fopen("input.txt", "r");
    // freadline(fp);
    printf("%s\n", freadline(fp));
    fclose(fp);

    /////////////////////////////////////// part 2

    // empty(&list);
    return 0;
}

/////////////////////////////////////// part 1

// Implement a function char* freadline(FILE* fp) that reads a line from fp and returns it. Use the function fgets defined in stdio.h; the returned char* must have the exact memory allocated as needed. (that is, sizeof(line) == strlen(line) + 1) (10 pts)
char* freadline(FILE* fp){

    int lineSize = 255;                                         // initial size of line is 255
    int flag;                                                   // flag detects a '/n' or EOF in buffer (i.e. detects end of line)

    char buffer[255];                                           // temp storage for string
    char *line = (char*) malloc(sizeof(char) * lineSize);
    line[0] = '\0';                                             // initialize line,, will have grabage values if not initialized

    do {
        flag = 0;

        if (fgets(buffer, sizeof(buffer)+1, fp) == NULL)        // EOF or a new line is reached
            break;

        for (int i=0; i<sizeof(buffer) && flag==0; i++){        // detects '\n' in buffer (i.e. end of line)
            if (buffer[i] == '\n')
                flag = 1;                                       
        }

        strcat(line, buffer);                                   // append buffer to line

        if (flag == 0){                                         // resizes line if there are still substrings in line
            lineSize *= 2;
            line = (char*) realloc(line, lineSize);
        }

    } while (flag==0);

    line = (char*) realloc(line, strlen(line)+1);               // resizes line to exact memory allocation

    return line;
}


/////////////////////////////////////// part 2

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