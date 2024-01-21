#define TASK_COMM_LEN 16

struct my_task_struct{
    int pid;
    int ppid;
    char cmd[TASK_COMM_LEN];
    char tty[64];
};
