#include <string.h>
#include "pancake_names.h"
#define base 27
#define maxh 531441 // 27^4
#define val(x) (x-'a'+1)
int cnt[maxh], pre[maxh];
inline int hashing(char *s) {
	int len = strlen(s), idx = 0;
	for ( int i=0; i<len; ++i )	idx = idx*base + val(s[i]);
	for ( int i=len; i<4; ++i )	idx = idx*base;
	return idx;
}
int main() {
	InitPancakes();
	for ( int i=0; i<N; ++i )	cnt[hashing(S[i])]++;
	for ( int i=1; i<maxh; ++i )	pre[i] = pre[i-1] + cnt[i];
	for ( int i=0; i<M; ++i )	AnswerArvin(i, pre[hashing(Q2[i])]-pre[hashing(Q1[i])-1]);
	ByeArvin();
	return 0;
}