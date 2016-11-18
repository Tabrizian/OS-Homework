#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int a[10] = { 99, 14, 19, 26, 27, 31, 33, 35, 42, 44 };
int b[10];


void merge_sort( int start, int end);
void merge( int start, int mid, int end);


int main(int argc, char *argv[]){

	merge_sort( 0,9);
	for(int i=0;i<10;i++){
		printf("%d is %d\n",i,a[i]);
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
      if(a[l1] <= a[l2])
         b[i] = a[l1++];
      else
         b[i] = a[l2++];
   }
   
   while(l1 <= mid)    
      b[i++] = a[l1++];

   while(l2 <= end)   
      b[i++] = a[l2++];

   for(i = start; i <= end; i++)
      a[i] = b[i];
}
