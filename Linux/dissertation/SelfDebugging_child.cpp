#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char** argv)
{
    int parentPid = getppid();
    ptrace(PTRACE_ATTACH, parentPid, 0, 0);
    ptrace(PTRACE_CONT, parentPid, 0, 0);
    while(true) sleep(1);
    return 0;
}