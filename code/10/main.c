#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define maxn 50005
typedef struct _node_ {
	int id;
	struct _node_ *next;
} node;
typedef struct _data_ {
	int id, lv;
} data;
node *head;
node *init(int id) {
	node *tmp = (node*)malloc(sizeof(node));
	tmp->id = id;
	return tmp;
}
void insert(int x, int y) {
	for ( node *i=head[x].next; i!=NULL; i=(i->next) )	if ( i->id == y )	return;
	node *tmp = init(y);
	tmp->next = head[x].next;
	head[x].next = tmp;
}
int cnt[maxn], q_f = 0, q_b = 0;
long long D[maxn][105];
data queue[maxn*100];
bool cake[maxn][105], vis[maxn][105];
int bfs(int goal, int n) {
	queue[q_b].id = 0;
	queue[q_b++].lv = 1;
	vis[0][1] = true;
	memset(D,0x7f,sizeof(D));
	long long inf = D[0][0];
	D[0][1] = 0;
	while ( q_f != q_b ) {
		int x = queue[q_f].id;
		int lv = queue[q_f++].lv;
		q_f %= (maxn*100);
		long long dist = D[x][lv];
		// printf("x, lv, dist: %d %d %d\n", x, lv, dist);
		for ( node *i=head[x].next; i!=NULL; i=i->next ) {
			int id = i->id;
			if ( vis[id][lv] )	continue;
			if ( cnt[id] == 0 || (cnt[id] == 1 && cake[id][lv]) ) {
				vis[id][lv] = true;
				queue[q_b].id = id;
				queue[q_b++].lv = lv;
				D[id][lv] = dist+1;
				q_b %= (maxn*100);
				if ( cnt[id] == 1 && cake[id][lv] ) {
					vis[id][lv+1] = true;
					queue[q_b].id = id;
					queue[q_b++].lv = lv+1;
					D[id][lv+1] = dist+2;
					q_b %= (maxn*100);
				}
			}
		}
	}
	long long ans = inf;
	for ( int i=0; i<n; ++i )	if ( D[i][goal] < ans )	ans = D[i][goal];
	return ans==inf ? -1 : ans;
}
int main() {
	int n, m, l, g;
	scanf("%d %d %d %d", &n, &m, &l, &g);
	for ( int i=0; i<g; ++i ) {
		int x, y;
		scanf("%d %d", &x, &y);
		if ( !cake[x][y] ) {
			cake[x][y] = 1;
			cnt[x]++;
		}
	}
	head = (node*)malloc(sizeof(node)*n);
	for ( int i=0; i<n; ++i )	head[i].next = NULL;
	for ( int i=0; i<m; ++i ) {
		int x, y;
		scanf("%d %d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	// for ( int i=0; i<n; ++i ) {
	// 	printf("%d:", i);
	// 	for ( node *j=head[i].next; j!=NULL; j=j->next ) {
	// 		printf(" %d", j->id);
	// 	}
	// 	printf("\n");
	// }
	printf("%d\n", bfs(l,n));
	return 0;
}