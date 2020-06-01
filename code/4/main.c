#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define maxn 10005
#define maxl 200005
char *arr[maxn], s[maxl];
const long long p = 31, mod = 1000000007;
long long *hash[maxn];
long long dp[maxl];
bool match(int row1, int l1, int r1, int row2, int l2, int r2) {
	long long diff1 = (l1==0?0:hash[row1][l1-1]), diff2 = (l2==0?0:hash[row2][l2-1]);
	long long key1 = (hash[row1][r1]-diff1+mod)%mod;
	long long key2 = (hash[row2][r2]-diff2+mod)%mod;
	if ( l1 < l2 )	key1 = key1*dp[l2-l1]%mod;
	else	key2 = key2*dp[l1-l2]%mod;
	if ( key1 != key2 )	return false;
	// for ( int i=l1, j=l2; i<=r1; ++i, ++j )
	// 	if ( arr[row1][i] != arr[row2][j] )
	// 		return false;
	return true;
}
int main() {
	dp[0] = 1;
	for ( int i=1; i<maxl; ++i )	dp[i] = dp[i-1]*p%mod;
	int n, q;
	scanf("%d", &n);
	fgets(s, maxl, stdin);
	for ( int i=0; i<n; ++i ) {
		fgets(s, maxl, stdin);
		s[strlen(s)-1] = '\0';
		long long len = strlen(s);
		arr[i] = (char*)malloc(sizeof(char)*(len+1));
		strcpy(arr[i], s);
		hash[i] = (long long*)malloc(sizeof(long long)*len);
		hash[i][0] = arr[i][0]-'a';
		for ( int j=1; j<len; ++j )
			hash[i][j] = (hash[i][j-1]+(arr[i][j]-'a')*dp[j])%mod;
	}
	scanf("%d", &q);
	while ( q-- ) {
		int row1, l1, r1, row2, l2, r2;
		bool ans = true;
		scanf("%d %d %d %d %d %d", &row1, &l1, &r1, &row2, &l2, &r2);
		while ( l1 < r1 ) {
			int mid1 = l1+r1>>1;
			int mid2 = l2+r2>>1;
			bool matchL = match(row1, l1, mid1, row2, l2, mid2);
			bool matchR = match(row1, mid1+1, r1, row2, mid2+1, r2);
			if ( matchL && matchR ) {
				break;
			} else if ( matchL ) {
				l1 = mid1+1;
				l2 = mid2+1;
			} else if ( matchR ) {
				r1 = mid1;
				r2 = mid2;
			} else {
				ans = false;
				break;
			}
		}
		if ( ans )	printf("Y\n");
		else	printf("N\n");
	}
	return 0;
}