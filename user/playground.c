#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

	int re = write(1, "hi", 2);
	// mov x0 1
	// mov x1 "hi"
	// mov x2 2
	// call write
	printf("\n");
	printf("%d\n", re);
	exit(0);

	// usys.pl -> usys.o 
	// printf.c -> printf.o
	// playground.c 
	// ld p.o usys.o printf.o
}
