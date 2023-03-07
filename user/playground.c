#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{

	int p[2];
	pipe(p);
	int cbuf[10];
	if (fork() == 0) {
		// 子
		close(0);
		dup(p[0]);
		close(p[1]);
		close(p[0]);
		sleep(100);
		int re = read(0, cbuf, 8);
		fprintf(1, "返回值 %d\n", re);
		fprintf(1, "读到的值 %s\n", cbuf);

	} else {
		// 父
		close(1);
		dup(p[1]);
		close(p[1]);
		close(p[0]);
		//write(1, "hello\n", 6);
		close(1);

		wait((void *)0);

	}
	exit(0);
}
