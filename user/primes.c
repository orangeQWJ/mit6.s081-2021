#include "kernel/types.h"
#include "user/user.h"

#define RFD 0
#define WFD 1

// 从管道中取出第一个数字
int getFirstNum(int lPipe[], int* dst);
// 除了第一个进程和最后一个进程
// 其他进程的行为都是相似的
__attribute__((noreturn))
void primes(int lPipe[]);
// 将lPipe中符合要求的数字送入rPipe中
void transmitData(int lPipe[], int rPipe[], int firstNum);

void transmitData(int lPipe[], int rPipe[], int firstNum)
{
    int buf;
    while (read(lPipe[RFD], (void*)&buf, sizeof(int)) == sizeof(int)) {
        if (buf % firstNum != 0) {
            write(rPipe[WFD], (void*)&buf, sizeof(int));
        }
    }
}

int getFirstNum(int lPipe[], int* dst)
{
    if (read(lPipe[RFD], (void*)dst, sizeof(int)) == sizeof(int)) {
        return 0;
    } else {
        return -1;
    }
}

void primes(int lPipe[])
{
    // 本进程拿到的这对文件描述符应当是这样的
    // 1. 父进程先fork，将描述符的读写传递给子进程
    // 2. 然后父进程关闭对管道的读写
    // 关于管道管理，本进程应该完成的事情
    // 1. 在fork之前关闭父进程传进来的管道的读写端
    // 2. 在fork之前创还能管道，在fork之后关闭对创建管道的读写

    // 拿到上一个进程写好的管道。
    // 对于这一个管道本进程不写
    // 所以关闭写端
    close(lPipe[WFD]);
    // 从管道中捞出第一个数来
    // 这个数是素数，后面数字若不能被整除，则放入rPipe
    int firstNum;
    if (getFirstNum(lPipe, &firstNum) == 0) {
        // 左边的管道中还有数据
        printf("prime %d\n", firstNum);
        int rPipe[2];
        pipe(rPipe); // fork之后关闭读写
        transmitData(lPipe, rPipe, firstNum);
        // rPipe中已经放进了数据，也有可能已经没有数据了
        close(lPipe[RFD]);
        if (fork() == 0) {
            primes(rPipe);
        } else {
            close(rPipe[RFD]);
            close(rPipe[WFD]);
            wait(0);
            exit(0);
        }
    } else { // 左边给的管道中已经没有数据了
        close(lPipe[RFD]);
        exit(0);
    }
}

int main()
{
    int p[2];
    pipe(p);
    for (int i = 2; i <= 35; i++) {
        write(p[WFD], (void*)&i, sizeof(int));
    }
    if (fork() == 0) {
        primes(p);
    } else {
        close(p[WFD]);
        close(p[RFD]);
        wait(0);
    }
    exit(0);
}
