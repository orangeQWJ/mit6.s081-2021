#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

	int re = write(2, "hi", 2);
	printf("\n");
	printf("%d\n", re);
	exit(0);
}
