#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

int main(void) {
    LLPtr startPtr = NULL;
    unsigned int choice;
    int id;
    char name[50];

    instructions();
    printf("? ");
    scanf("%u", &choice);

    while (choice != 3) {
        switch (choice) {
            case 1:
                printf("Enter id and name: ");
                scanf("%d %s", &id, name);
                insert(&startPtr, id, name);
                printList(startPtr);
                break;
            case 2:
                if (startPtr == NULL) puts("List is empty.\n");
                else {
                    printf("Enter number to be deleted: ");
                    scanf("%d", &id);
                    if (deletes(&startPtr, id)) {
                        printf("%d deleted.\n", id);
                        printList(startPtr);
                    } else printf("%d not found.\n\n", id);
                }
                break;
        }
        printf("? ");
        scanf("%u", &choice);
    }

    puts("Clear all nodes");
    freeList(&startPtr);
    puts("End of run.");
    return 0;
}