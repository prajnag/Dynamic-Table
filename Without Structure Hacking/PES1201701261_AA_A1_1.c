#include "dyntable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define ALLOC_THRESHOLD 0.6
#define DEALLOC_THRESHOLD 0.25
#define BENCHMARK_COUNT 20
//int ct=0;
typedef struct dynarr {
    int * arr;
    int capacity;
    int size;
} dynarray_t;

void* make_new_dynamic_table(int n)
{
    dynarray_t * array=(dynarray_t*)malloc(sizeof(dynarray_t)+sizeof(int)*n);
    array->arr=(int*)malloc(sizeof(int)*n);
    array->capacity=n;
    array->size=0;
    return array;

}

// Inserts element at the end of dynamic table 
void push_back(void** arr, int data)
{
    if((int)(ALLOC_THRESHOLD*((dynarray_t*)arr)->capacity)==((dynarray_t*)arr)->size)
    {

        //ct++;
        ((dynarray_t*)arr)->capacity*=2;
        int *new_table = (int *)malloc(sizeof(int)*((dynarray_t*)arr)->capacity);
        for(int i = 0; i <= ((dynarray_t*)arr)->size; i++)
        {

            new_table[i] = ((dynarray_t*)arr)->arr[i];
        }
        free(((dynarray_t*)arr)->arr);
        ((dynarray_t*)arr)->arr = new_table;
    }
    
    ((dynarray_t*)arr)->arr[++((dynarray_t*)arr)->size]=data;

    //printf("capacity is %d size is %d\n",((dynarray_t*)arr)->capacity, ((dynarray_t*)arr)->size);
}

// Pops element from the end of dynamic table. Return -1 if empty
int pop_back(void** arr)
{
    if (((dynarray_t*)arr)->capacity==0 || ((dynarray_t*)arr)->size==0)
    {
        printf("underflow\n");
        return -1;
    }
     if((int)(DEALLOC_THRESHOLD*((dynarray_t*)arr)->capacity)==((dynarray_t*)arr)->size) //threshold as 1
     {

         //ct++;
    
        ((dynarray_t*)arr)->capacity*=0.75;
        //printf("cap %d\n",((dynarray_t*)arr)->capacity );
        int *new_table = (int *)malloc(sizeof(int)*((dynarray_t*)arr)->capacity);
        for(int i = 0; i <= ((dynarray_t*)arr)->size; i++)
        {
            new_table[i] = ((dynarray_t*)arr)->arr[i];
        }
        free(((dynarray_t*)arr)->arr);
        ((dynarray_t*)arr)->arr = new_table;
     }
        //printf("capacity %d\n",((dynarray_t*)arr)->capacity);

        return(((dynarray_t*)arr)->size--);
        
}
/*
void disp(void *arr)
{
    printf("displaying\n");
    for(int i=1; i<=((dynarray_t*)arr)->size; ++i)
    {
        printf("%d\n", ((dynarray_t*)arr)->arr[i]);
    }
}
*/


