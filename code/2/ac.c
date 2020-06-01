#include <stdio.h>
#include <stdlib.h>
#define maxn 300005
#define maxk 550
typedef struct _node_ {
	int size;
	char array[maxk];
	struct _node_ *next;
} node;
node *head;
int K;
void init(int n) {
	K = 0;
	while ( K*K <= n )	K++;
	head = (node*)malloc(sizeof(node));
	head->size = 0;
	head->next = NULL;
	node *now = head;
	for ( int i=K; i<n; i+=K ) {
		node *tmp = (node*)malloc(sizeof(node));
		tmp->size = 0;
		tmp->next = NULL;
		now->next = tmp;
		now = tmp;
	}
}
void locate(int *pos, node **now) {
	while ( *pos > (*now)->size ) {
		*pos -= (*now)->size;
		*now = (*now)->next;
	}
}
void insert(int pos, char val) {
	node *now = head;
	locate(&pos, &now);
	if ( now->size == K ) {
        // divide into half
        node *tmp = (node*)malloc(sizeof(node));
        tmp->next = now->next;
        now->next = tmp;
        tmp->size = K/2;
        for ( int i=0; i<K/2; ++i ) {
            tmp->array[i] = now->array[now->size-K/2+i];
        }
        now->size -= K/2;
        if ( pos < now->size ) {
            for ( int i=now->size; i>pos; --i ) {
                now->array[i] = now->array[i-1];        
            }
            now->array[pos] = val;
            now->size += 1;
        } else {
            pos -= now->size;
            for ( int i=tmp->size; i>pos; --i ) {
                tmp->array[i] = tmp->array[i-1];
            }
            tmp->array[pos] = val;
            tmp->size += 1;
        }
    } else {
        for ( int i=now->size; i>pos; --i ) {
            now->array[i] = now->array[i-1];
        }
        now->array[pos] = val;
        now->size += 1;
    }
}
void delete(int pos) {
	node *now = head;
	locate(&pos, &now);
	for ( int i=pos; i<now->size; ++i ) {
		now->array[i-1] = now->array[i];
	}
	now->size -= 1;
}
void print(int l, int r) {
	node *now = head;
	int pos = l+1, len = r-l;
	locate(&pos, &now);
	// printf("%d %d\n", pos, len);
	for ( int cnt=0, i=pos-1; cnt<len; ++cnt, ++i ) {
		while ( i == now->size ) {
			now = now->next;
			i = 0;
		}
		putchar(now->array[i]);
	}
	putchar('\n');
}
int main() {
	int n, id, l, r;
	scanf("%d", &n);
	init(n);
	for ( int i=0; i<n; ++i ) {
		scanf("%d ", &id);
		if ( id == 1 ) {
			scanf("%d %c", &l, &r);
			insert(l,r);
		} else if ( id == 2 ) {
			scanf("%d", &l);
			delete(l+1);
		} else {
			scanf("%d %d", &l, &r);
			print(l,r);
		}
	}
	free(head);
	return 0;
}