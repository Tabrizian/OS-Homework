#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
int b[10000];//temp array for help to merging in merge sort!
int *shm_array;
int M=1000;//when the subArray has less than M member we stop forking

void merge_sort( int start, int end);
void merge( int start, int mid, int end);


int main(int argc, char *argv[]){
	/* for Measuring time*/
	struct timeval start, end;
    long mtime, seconds, useconds;
    gettimeofday(&start, NULL);
	/* starting declare shared Memory*/
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

	/* read inputs from file*/
	FILE *fp;
	fp = fopen("./test.txt", "r");
	for (int i = 0; i < 10000; i++) {
		int a;
		fscanf(fp, "%d", &a);
		shm_array[i] =a;
	}
	fclose(fp);





	merge_sort( 0,9999);
	for(int i=0;i<10000;i++){
        	printf("%d is %d\n",i,shm_array[i]);
	}
	gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);

    return 0;
}

void merge_sort( int start, int end){
    if(start >= end)return;
    int mid = (start+end)/2;
    int status;
    int lchild,rchild;
	int length = end - start +1 ;

	// if the size of subArray is greater than M then we fork
	if(length > M){
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
	else{
	merge_sort( start, mid);
	merge_sort( mid+1, end);
	merge( start, mid, end);
	}
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
