struct my_task_struct{
    int pid;
    int ppid;
    int com_len;
    int tty_len;
    char *cmd;
    char *tty;
};
