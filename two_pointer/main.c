#include <stdio.h>
#include <stddef.h>

int main()
{
	char buf[9] = {1,8,6,2,5,4,8,3,7}; //49
	char *head = buf;
	char *tail = &buf[8];
	int max_area = 0;
	while (head < tail ) {
		int a = (tail - head) * (*head < *tail? *head++: *tail--);
		if (a > max_area) {
			max_area = a;
		}
			
	}
	printf("%d\n", max_area);

	return 0;
}
