#include <stdio.h>
#include <stdlib.h>
#define maxn 2000005
int arr[maxn], dp_max[maxn];
typedef struct _stack_ {
	int top;
	int *arr;
} stack;
stack *init(int sz) {
	stack *s = malloc(sizeof(stack));
	s->top = -1;
	s->arr = malloc(sizeof(int)*(sz));
	return s;
}
void push(stack *s, int x) {
	s->top += 1;
	s->arr[s->top] = x;
}
void pop(stack *s) {
	s->arr[s->top] = 0;
	s->top -= 1;
}
int main() {
	int n, x;
	scanf("%d %d", &n, &x);
	stack *stk = init(n);
	for ( int i=0; i<n; ++i ) {
		scanf("%d", arr+i);
	}
	for ( int i=n-1; i>=0; --i ) {
		if ( arr[i] >= dp_max[i+1] ) {
			dp_max[i] = arr[i];
		} else {
			dp_max[i] = dp_max[i+1];
		}
	}
	for ( int i=0; i<n; ++i ) {
		while ( stk->top >= 0 && stk->arr[stk->top] > dp_max[i] ) {
			printf("%d ", stk->arr[stk->top]);
			pop(stk);
		}
		if ( dp_max[i] == arr[i] ) {
			printf("%d ", arr[i]);
		} else {
			push(stk,arr[i]);
		}
	}
	while ( stk->top >= 0 ) {
		printf("%d ", stk->arr[stk->top]);
		pop(stk);
	}
	free(stk);
	return 0;
}