
// self-referential structure
struct Node {
   int id;              
   char name[50];       
   struct Node *nextPtr; 
   struct Node *prevPtr;
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode

// prototypes


void insert(LLPtr *sPtr, int id, char *name);
int deletes(LLPtr *sPtr, int id);
int isEmpty(LLPtr sPtr);
void printList(LLPtr currentPtr);
void freeList(LLPtr *sPtr); 
void instructions(void);


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert(LLPtr *sPtr, int id, char *name) {
    LLPtr newPtr = (LLPtr)malloc(sizeof(LLnode));
    if (newPtr != NULL) {
        newPtr->id = id;
        strcpy(newPtr->name, name);
        newPtr->nextPtr = NULL;
        newPtr->prevPtr = NULL;

        LLPtr previousPtr = NULL;
        LLPtr currentPtr = *sPtr;

        // หาตำแหน่งแทรกโดยเรียงตาม id
        while (currentPtr != NULL && id > currentPtr->id) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (previousPtr == NULL) { 
            newPtr->nextPtr = *sPtr;
            if (*sPtr != NULL) (*sPtr)->prevPtr = newPtr;
            *sPtr = newPtr;
        } else { 
            newPtr->nextPtr = currentPtr;
            newPtr->prevPtr = previousPtr;
            previousPtr->nextPtr = newPtr;
            if (currentPtr != NULL) currentPtr->prevPtr = newPtr;
        }
    }
}

// delete a list element
int deletes(LLPtr *sPtr, int id) {
    LLPtr currentPtr = *sPtr;

    while (currentPtr != NULL && currentPtr->id != id) {
        currentPtr = currentPtr->nextPtr;
    }

    if (currentPtr != NULL) {
        LLPtr tempPtr = currentPtr;
        
        if (currentPtr->prevPtr == NULL) { 
            *sPtr = currentPtr->nextPtr;
            if (*sPtr != NULL) (*sPtr)->prevPtr = NULL;
        } else { 
            currentPtr->prevPtr->nextPtr = currentPtr->nextPtr;
            if (currentPtr->nextPtr != NULL) {
                currentPtr->nextPtr->prevPtr = currentPtr->prevPtr;
            }
        }
        free(tempPtr);
        return id;
    }
    return 0; 
}

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList(LLPtr currentPtr) {
    if (currentPtr == NULL) {
        puts("List is empty.\n");
        return;
    }

    LLPtr lastPtr = NULL;
    puts("The list is :");
    while (currentPtr != NULL) {
        printf("%d %s -->", currentPtr->id, currentPtr->name);
        lastPtr = currentPtr; 
        currentPtr = currentPtr->nextPtr;
    }
    puts("NULL");

    while (lastPtr != NULL) {
        printf("%d %s -->", lastPtr->id, lastPtr->name);
        lastPtr = lastPtr->prevPtr;
    }
    puts("NULL\n");
}

void freeList(LLPtr *sPtr) {
    LLPtr tempPtr;
    while (*sPtr != NULL) {
        tempPtr = *sPtr;
        printf("delete %d\n", tempPtr->id);
        *sPtr = (*sPtr)->nextPtr;
        free(tempPtr);
    }
}
