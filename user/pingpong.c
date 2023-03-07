#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	int fPipe[2]; // 父进程从[1]读,读出写在[0]的内容
	int cPipe[2]; // 子进程从[1]读,读出写在[0]的内容
	pipe(fPipe);
	pipe(cPipe);
	int fpid = getpid();
	int cpid = fork();
	char fbuf;
	char cbuf;
	if (cpid == 0) {
	// 子进程
		close(fPipe[1]);
		read(cPipe[1], &cbuf, 1); 
		fprintf(1, "%d: received ping\n", cpid);
		write(fPipe[0], "x", 1);
		close(fPipe[0]);
		exit(0);

	}
	// 父进程
	else{
		close(cPipe[1]);
		write(cPipe[0], "x", 1);
		close(cPipe[0]);
		read(fPipe[1], &fbuf, 1);
		wait((void*)0);
		fprintf(1, "%d: received pong\n", fpid);
		exit(0);
	}

}
