#include <stdio.h>
#include <stdlib.h>
#include "Arvin.h"
inline void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
int *arr, *brr;
void q_sort(int l, int r) {
	if ( l >= r )	return;
	int pivot = arr[l+rand()%(r-l+1)], pt = l, res;
	for ( int i=l; i<r; ++i ) {
		res = query(pivot,brr[i]);
		if ( res == 1 )
			swap(&brr[pt++],&brr[i]);
		else if ( res == 0 ) 
			swap(&brr[r],&brr[i--]);
	}
	swap(&brr[pt],&brr[r]);
	pivot = brr[pt];
	pt = l;
	for ( int i=l; i<r; ++i ) {
		res = query(arr[i],pivot);
		if ( res == -1 )
			swap(&arr[pt++],&arr[i]);
		else if ( res == 0 )
			swap(&arr[r],&arr[i--]);
	}
	swap(&arr[pt],&arr[r]);
	q_sort(l,pt-1);
	q_sort(pt+1,r);
}
int main() {
	srand(9487);
	int n;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	brr = (int*)malloc(sizeof(int)*n);
	for ( int i=0; i<n; ++i )	scanf("%d", arr+i);
	for ( int i=0; i<n; ++i )	scanf("%d", brr+i);
	q_sort(0,n-1);
	for ( int i=0; i<n; ++i )	printf("%d %d\n", arr[i], brr[i]);
	free(arr);
	free(brr);
	return 0;
}