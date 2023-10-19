#include<stdio.h>
#include<stdlib.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node next;
   Node prev;
} NodeObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// private List type
typedef struct ListObj{
   Node front;
   Node back;
   int length;
   int cursor;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
List newList(void){
   List L = malloc(sizeof(ListObj));
   assert( L!=NULL );
    L->front = newNode(-1);
   L->back = newNode(-1);

   L->front->next = L->back;
   L->front->prev = NULL;
   L->back->prev = L->front;
   L->back->next = NULL;
   L->length = 0;
   L->cursor = -1;
   return(L);
}
bool isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}

void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL) {
      while(!isEmpty(*pL)) {
         deleteFront(*pL);
      }
      free((*pL)->front);
      free((*pL)->back);
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------
int length(List L) {
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

int indexx(List L){
    //printf("mayb\n");
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor);
}
int front(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->length >0){
    return(L->front->next->data);
   }
}
int back(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->length >0){
    return(L->back->prev->data);
   }
}
int get(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   //printf("%d\n", L->cursor);
   //iterate until we reach cursor element
    if(L->length >0 && L->cursor >=0){
        Node index = L->front->next;
        for(int i=0; i < L->cursor; i++){
            index = index->next;
        }
    return(index->data);
    }
}
bool equals(List A, List B){
    if( A==NULL || B==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   bool eq = false;
   bool eq1;
   //bool eq2;
   Node N, M;
   
   eq1 = ( A->length == B->length);
   //printf("%d is true r false", A->length);
   //eq2 = ( A->cursor == B->cursor);
   if(eq1){
        eq = true;
   }
   N = A->front;
   M = B->front;
   while(eq && N!=NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return(eq);
}

void clear(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L-> length != 0){
        Node N = L->front->next;
        Node M = L->front->next->next;
        while(N != L->back){
            free(N);
            N = M;
            M = M->next;
        }
    }
    L->front = L->back = NULL;
   L->length = 0;
   L->cursor = -1;
}
void set(List L, int x){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->length>0 && L->cursor>=0){
        Node index = L->front->next;
        for(int i=0; i < L->cursor; i++){
            //printf("%d\n", L->cursor);
            index = index->next;
        }
        index->data = x;
    }
}
void moveFront(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(!isEmpty(L)){
        L->cursor = 0;
    }
}
void moveBack(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(!isEmpty(L)){
        L->cursor = (L->length)-1;
    }
}
void movePrev(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->cursor!=-1 || L->cursor!=0)
        L->cursor = (L->cursor)-1;
    else
        L->cursor = -1;
}
//moves cursor
void moveNext(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->cursor!=-1 && L->cursor!=((L->length)-1))
        L->cursor = (L->cursor)+1;
    else
        L->cursor = -1;
}

void prepend(List L, int x){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->length == 0){
        Node N = newNode(x);
        L->front->next = N;
        L->back->prev = N;
        N->next = L->back;
        N->prev = L->front;
    }
    if(L->length == 1){
        Node N = newNode(x);
        L->front->next = N;
        L->back->prev->prev = N;
        N->next = L->back->prev;
        N->prev = L->front;
    }
    else{
        Node N = newNode(x);
        L->front->next->prev = N;
        N->next = L->front->next;
        L->front->next = N;
        N->prev = L->front;
    }
    L->length += 1;
    //moveNext(L);
}
void append(List L, int x){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->length == 0){
        Node N = newNode(x);
        L->front->next = N;
        L->back->prev = N;
        N->next = L->back;
        N->prev = L->front;
    }
    if(L->length == 1){
        Node N = newNode(x);
        L->back->prev = N;
        L->front->next->next = N;
        N->next = L->back;
        N->prev = L->front->next;
    }
    else{
        Node N = newNode(x);
        L->back->prev->next = N;
        N->prev = L->back->prev;
        L->back->prev = N;
        N->next = L->back;
    }
    L->length += 1;
}
void insertBefore(List L, int x){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->length>0 && L->cursor>=0){
        if(L->cursor==0){
            prepend(L, x);
            L->length += 1;
        }
        else{
            Node N = newNode(x);
            Node temp = L->front->next;
            for(int i=0; i < L->cursor; i++){
                temp = temp->next;
            }
            temp->prev->next = N;
            N->prev = temp->prev;
            temp->prev = N;
            N->next = temp;
            L->length += 1;
            moveNext(L);
        }
    }
    printf("%d\n",L->cursor);
}
void insertAfter(List L, int x){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->length>0 && L->cursor>=0){
        if(L->cursor==((L->length)-1)){
            append(L, x);
            L->length += 1;
        }
        else{
            Node N = newNode(x);
            Node temp = L->back->prev;
            for(int i=L->length-1; i > L->cursor; i--){
                temp = temp->prev;
            }
            temp->next->prev = N;
            N->next = temp->next;
            temp->next = N;
            N->prev = temp;
            L->length +=1;
        }
    }
    printf("%d\n",L->cursor);
}
void deleteFront(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->length>0){
        Node temp = L->front->next;
        L->front->next = L->front->next->next;
        L->front->next->next->prev = L->front;
        free(temp);
        L->length -= 1;

    }
}
void deleteBack(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->length>0){
        Node temp = L->back->prev;
        L->back->prev = L->back->prev->prev;
        L->back->prev->prev->next = L->back;
        free(temp);
        L->length -= 1;
    }
}
void delete(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    if(L->length>0 && L->cursor>=0){
        Node temp = L->front->next;
        for(int i=0; i < L->cursor; i++){
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
        L->cursor=-1;
        L->length -= 1;
    }
}
void printList(FILE* out, List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

    //fprintf(out, "front ");
    if(L->length > 0){
        Node temp = L->front->next;
        for(int i=0; i < L->length; i++){
            fprintf(out, "%d ", temp->data);
            temp = temp->next;
        }
    }
}
List copyList(List L){
    if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
    List dup = newList();
    //dup->length = L->length;
    //printf("%d \n", dup->length);
    if(L->length > 0){
        Node temp = L->front->next;
        for(int i=0; i < L->length; i++){
            //printf("copied: %d \n", temp->data);
            append(dup, temp->data);
            temp = temp->next;
        }
    }
    //printList(stdout, dup);
    return dup;
}