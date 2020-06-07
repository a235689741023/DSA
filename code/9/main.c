#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define maxn 101
#define maxp 2000005
#define mod 50000007
#define modalp 1000000009
int host[mod], pot[2][maxp], idx[2][mod], p[maxp], cnt = 1;
char re[maxp][maxn];
long long pm[2] = {512, 2048}, alp[256], mmo[2] = {mod,mod+2};
long long hashing(char *s, int id, int id2) {
	long long key = 0, len = strlen(s);
	for ( int i=0; i<len; ++i )
		key = (key*(pm[id2]-id) + alp[s[i]])%mmo[id2];
	return (key+id)%mmo[id2];
}
int get_hash(char *s) {
	long long key = hashing(s,0,0);
	while ( strcmp(s,re[host[key]]) != 0 ) {
		key = (key+hashing(s,1,0))%mod;
	}
	return host[key];
}
int find(int x) {
	return (p[x]==x ? x : (p[x]=find(p[x])));
}
void swap(int *a, int *b) {
	long long tmp = *a;
	*a = *b;
	*b = tmp;
}
void resonance(int id, long long key1, long long key2) {
	if ( idx[0][key1] != 0 && idx[0][key1] == idx[1][key2] ) {
		int tx = find(idx[0][key1]), ty = find(id);
		if ( tx > ty )	swap(&tx,&ty);
		p[ty] = tx;
		idx[0][key1] = idx[1][key2] = 0;
		printf("%s %s\n", re[tx], re[ty]);
		resonance(tx,key1*2%mmo[0],key2*2%mmo[1]);
	} else {
		while ( idx[0][key1] != 0 ) {
			key1 = (key1+1)%mmo[0];
		}
		while ( idx[1][key2] != 0 ) {
			key2 = (key2+1)%mmo[1];
		}
		pot[0][id] = key1;
		pot[1][id] = key2;
		idx[0][key1] = id;
		idx[1][key2] = id;
	}
}
int32_t main() {
	alp[0] = 1;
	for ( int i=1; i<256; ++i )	alp[i] = alp[i-1]*1213%modalp;
	int n, m;
	char s[maxn], name[maxn], name2[maxn];
	scanf("%d", &n);
	for ( int i=1; i<=n; ++i )	p[i] = i;
	while ( n-- && scanf("%s", s) ) {
		if ( s[0] == 'N' ) {
			scanf(" %s", name);
			long long key = hashing(name,0,0);
			while ( host[key] != 0 )
				key = (key+hashing(name,1,0))%mod;
			host[key] = cnt;
			strcpy(re[cnt],name);
			scanf(" %d", &m);
			long long key2 = 0, key3 = 0;
			while ( m-- && scanf(" %s", name) ) {
				key2 = (key2+hashing(name,0,0))%mmo[0];
				key3 = (key3+hashing(name,0,1))%mmo[1];
			}
			resonance(cnt,key2,key3);
			cnt++;
		} else {
			scanf(" %s %s", name, name2);
			int tu = find(get_hash(name)), tv = find(get_hash(name2));
			if ( tu > tv )	swap(&tu,&tv);
			p[tv] = tu;
			resonance(tu, (pot[0][tu]+pot[0][tv])%mmo[0], (pot[1][tu]+pot[1][tv])%mmo[1]);
		}
	}
	return 0;
}