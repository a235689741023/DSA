#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
int sz = 1, *arr = NULL;
inline void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
inline void update() {
	int i = sz-1;
	while ( (i>>1) && arr[i] < arr[i>>1] ) {
		swap(&arr[i], &arr[i>>1]);
		i >>= 1;
	}
}
void max_heapify(int i) {
	int mx = i;
	if ( (i<<1) < sz && arr[i<<1] < arr[i] )	mx = i<<1;
	if ( (i<<1|1) < sz && arr[i<<1|1] < arr[mx] )	mx = i<<1|1;
	if ( mx != i ) {
		swap(&arr[i],&arr[mx]);
		max_heapify(mx);
	}
}
int main() {
	int n;
	long long sum = 0;
	scanf("%d", &n);
	arr = (int*)calloc(n, sizeof(int));
	for ( int i=0, x, y; i<n; ++i ) {
		scanf("%d", &x);
		if ( x ) {
			sum -= arr[1];
			arr[1] = arr[sz-1];
			sz--;
			max_heapify(1);
		} else {
			scanf("%d", &y);
			sum += y;
			arr[sz++] = y;
			update();
		}
	}
	printf("%lld\n", sum);
	return 0;
}