#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	srand(5566);
	int a, b, c = rand()%2;
	scanf("%d%d", &a, &b);
	printf("%d\n", a+b);
	return 0;
}
