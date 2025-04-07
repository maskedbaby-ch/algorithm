#include <stdio.h>
#include <stddef.h>

void swap(char *a, char*b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	char buf[9] = {1,8,6,2,5,4,8,3,7};
	for (int i=0; i<9; i++) {
		for (int j=i; j<9-i-1; j++) {
			if (buf[j] > buf[j+1]) {
				swap(&buf[j], &buf[j+1]);
			}
		}
	}
	for(int i=0; i<9; i++) {
		printf("%d\n", buf[i]);
	}

	return 0;
}
