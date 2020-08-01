#include "dyntable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define ALLOC_THRESHOLD 0.6
#define DEALLOC_THRESHOLD 0.25
#define BENCHMARK_COUNT 50
int ct=0;
typedef struct dynarr {
    int capacity;
    int size;
    int arr[1];
} dynarray_t;
// Initialize a dynamic table.
void* make_new_dynamic_table(int n)
{
    dynarray_t * array=(dynarray_t*)malloc(sizeof(dynarray_t)+sizeof(int)*n);
    //array->arr[n];
    array->capacity=n;
    array->size=0;
    return array;

}
// Inserts element at the end of dynamic table 
void push_back(void** arr, int data)
{
    if((int)(ALLOC_THRESHOLD*((dynarray_t*)arr)->capacity)==((dynarray_t*)arr)->size)
    {
        ct++;
        //printf("entering");
        ((dynarray_t*)arr)->capacity*=2;
        //dynamically creating another dynarray
        dynarray_t * new_table=(dynarray_t*)make_new_dynamic_table(((dynarray_t*)arr)->capacity);
        new_table->size=((dynarray_t*)arr)->size;
        new_table->capacity=((dynarray_t*)arr)->capacity;
        int *new_arr = (int*)malloc(sizeof(int)*((dynarray_t*)arr)->capacity);
        for(int i = 0; i <= ((dynarray_t*)arr)->size; i++) //copying array contents
        {
            new_arr[i] = ((dynarray_t*)arr)->arr[i];
        }
        //free(((dynarray_t*)arr)->arr);
        for(int i = 0; i <= ((dynarray_t*)arr)->size; i++) 
        {
            ((dynarray_t*)arr)->arr[i]=new_arr[i];
        }
    }
    
    ((dynarray_t*)arr)->arr[++((dynarray_t*)arr)->size]=data;
    //printf("capacity is %d size is %d\n",((dynarray_t*)arr)->capacity, ((dynarray_t*)arr)->size);
}

// Pops element from the end of dynamic table. Return -1 if empty

int pop_back(void** arr)
{
    if (((dynarray_t*)arr)->capacity==0 || ((dynarray_t*)arr)->size==0) //checking for underflow
    {
        printf("underflow\n");
        return -1;
    }
     if((int)(DEALLOC_THRESHOLD*((dynarray_t*)arr)->capacity)==((dynarray_t*)arr)->size) //threshold as 1
      {
          ct++;
        ((dynarray_t*)arr)->capacity*=0.75;
        dynarray_t * new_table=(dynarray_t*)make_new_dynamic_table(((dynarray_t*)arr)->capacity);
        new_table->size=((dynarray_t*)arr)->size;
        new_table->capacity=((dynarray_t*)arr)->capacity;
        int *new_arr = (int*)malloc(sizeof(int)*((dynarray_t*)arr)->capacity);
        for(int i = 0; i <= ((dynarray_t*)arr)->size; i++)
        {
            new_arr[i] = ((dynarray_t*)arr)->arr[i];
        }
        //free(((dynarray_t*)arr)->arr);
        for(int i = 0; i <= ((dynarray_t*)arr)->size; i++)
        {
            ((dynarray_t*)arr)->arr[i]=new_arr[i];
        }
      }
        //printf("entering pop\n");
       // printf("size %d\n",((dynarray_t*)arr)->size);
       // printf("capacity %d\n",((dynarray_t*)arr)->capacity);
        return(((dynarray_t*)arr)->size--);
        
}

void disp(void *arr)
{
    printf("displaying\n");
    for(int i=1; i<=((dynarray_t*)arr)->size; ++i)
    {
        printf("%d\n", ((dynarray_t*)arr)->arr[i]);
    }
}

/*
int main() {
    int choice, loop = 1;
    static int n=1;
    void* dynarr=make_new_dynamic_table(10);

    while(loop) {
        scanf("%d", &choice);
        switch(choice) {
            int element, pop;
            case 0:
                scanf("%d", &element);
                push_back(dynarr, element);
                break;

            case 1:
                disp(dynarr);
                break;

            case 2:
                pop=pop_back(dynarr);
                break;

            case 3: 
                loop=0;
        
            
        }
        
    }


    printf("ct is %d\n", ct);
    return 0;
}
*/