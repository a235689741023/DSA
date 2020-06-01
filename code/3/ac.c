#include <stdio.h>
#include <stdlib.h>
#include "Arvin.h"
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void q_sort(int l, int r, int *arr, int *brr) {
	if ( l >= r )	return;
	int pivot1 = arr[l+rand()%(r-l+1)], pivot2, pt1 = l, pt2 = l;
	for ( int i=l; i<=r; ++i ) {
		int res = query(pivot1,brr[i]);
		if ( res == 1 ) {
			swap(&brr[pt1++],&brr[i]);
		} else if ( res == 0 ) {
			pivot2 = brr[i];
		}
	}
	for ( int i=r; i>=l; --i )	if ( brr[i] == pivot2 )	swap(&brr[i],&brr[pt1]);
	for ( int i=l; i<=r; ++i ) {
		int res = query(arr[i],pivot2);
		if ( res == -1 ) 
			swap(&arr[pt2++],&arr[i]);
	}
	for ( int i=r; i>=l; --i )	if ( arr[i] == pivot1 )	swap(&arr[i],&arr[pt2]);
	q_sort(l,pt1-1,arr,brr);
	q_sort(pt1+1,r,arr,brr);
}
int main() {
	srand(9487);
	int n, *arr, *brr;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	brr = (int*)malloc(sizeof(int)*n);
	for ( int i=0; i<n; ++i )	scanf("%d", arr+i);
	for ( int i=0; i<n; ++i )	scanf("%d", brr+i);
	q_sort(0,n-1,arr,brr);
	for ( int i=0; i<n; ++i )	printf("%d %d\n", arr[i], brr[i]);
	free(arr);
	free(brr);
	return 0;
}