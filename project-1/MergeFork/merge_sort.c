#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int b[10000];
int *shm_array;

void merge_sort( int start, int end);
void merge( int start, int mid, int end);


int main(int argc, char *argv[]){
	
	key_t key;/* key to be passed to shmget() */ 
	int shmflg;/* shmflg to be passed to shmget() */ 
	int shmid;/* return value from shmget() */ 
	int size;/* size to be passed to shmget() */ 
	key = IPC_PRIVATE;
	/* Create the shared memory segment. */
	size = 10000 * sizeof(int);
	if ((shmid = shmget(key, size, IPC_CREAT| 0660)) == -1) {
		perror("shmget");
		exit(1);
	}
	/* Attached to the shared memory segment in order to use it. */
	if ((shm_array = shmat(shmid, NULL, 0)) == (int *) -1) {
		perror("shmat");
		exit(1);
	}
	/*
	* Copy the data to be sorted from the local memory into the shared memory.
	*/
	for (int i = 0; i < 10000; i++) {
		shm_array[i] = rand() % 10000;
	}
	
	merge_sort( 0,9999);
	for(int i=0;i<10000;i++){
        	printf("%d is %d\n",i,shm_array[i]);
	}
    return 0;
	}

void merge_sort( int start, int end){
    if(start >= end)return;
    int mid = (start+end)/2;
    int status;
    int lchild,rchild;
    lchild = fork();

    if (lchild < 0) {
        perror("fork");
        exit(1);
    }
    if (lchild == 0) {
        merge_sort( start, mid);
        exit(0);
    } else {
        rchild = fork();
        if (rchild < 0) {
            perror("fork");
            exit(1);
        }
        if (rchild == 0) {
            merge_sort( mid+1, end);
            exit(0);
        }
    }
    waitpid(lchild, &status, 0);
    waitpid(rchild, &status, 0);
    merge( start, mid, end);
}

void merge(int start, int mid, int end) {
    int l1, l2, i;

    for(l1 = start, l2 = mid + 1, i = start; l1 <= mid && l2 <= end; i++) {
        if(shm_array[l1] <= shm_array[l2])
            b[i] = shm_array[l1++];
        else
            b[i] = shm_array[l2++];
    }

    while(l1 <= mid)
        b[i++] = shm_array[l1++];

    while(l2 <= end)
        b[i++] = shm_array[l2++];

    for(i = start; i <= end; i++)
        shm_array[i] = b[i];
}
