#include "kernel/types.h"
#include "user/user.h"
#include "kernel/sysinfo.h"

int main(){
	struct sysinfo s;
	int re;
	re = sysinfo(&s);
	printf("%d\n %d\n %d\n", re, s.freemem, s.nproc);
	exit(0);
}
