#include <stdio.h>
#include <stdlib.h>
int main() {
	int n, x, top = -1;
	int *arr, *dp_max, *stk;
	scanf("%d %d", &n, &x);
	arr = malloc(sizeof(int)*(n));
	dp_max = malloc(sizeof(int)*(n));
	stk = malloc(sizeof(int)*(n));
	for ( int i=0; i<n; ++i ) {
		scanf("%d", arr+i);
	}
	dp_max[n-1] = arr[n-1];
	for ( int i=n-2; i>=0; --i ) {
		if ( arr[i] >= dp_max[i+1] ) {
			dp_max[i] = arr[i];
		} else {
			dp_max[i] = dp_max[i+1];
		}
	}
	for ( int i=0; i<n; ++i ) {
		while ( top >= 0 && stk[top] > dp_max[i] ) {
			printf("%d", stk[top--]);
			putchar(' ');
		}
		if ( dp_max[i] == arr[i] ) {
			printf("%d", arr[i]);
			putchar(' ');
		} else {
			// push
			stk[++top] = arr[i];
		}
	}
	while ( top >= 0 ) {
		printf("%d", stk[top--]);
		putchar(' ');
	}
	free(arr);
	free(dp_max);
	free(stk);
	return 0;
}