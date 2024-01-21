#include <stdio.h>
#include <linux/sched.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_task_struct.h"

#define	SYS_GET_TASK_STRUCTURE	549
#define	SYS_HELLO		548

int main(int argc, char* argv[]){
  long int retval = syscall(SYS_HELLO);
  if(retval != 0){
    printf("error in syscall\n");
    return retval;
  }

  int cnt = 150;
  struct my_task_struct* ts = malloc(cntof(struct my_task_struct)*cnt);

  retval = syscall(SYS_GET_TASK_STRUCTURE, &cnt, ts);  
  if(retval != 0){
    printf("error in syscall");
    return retval;
  }

  printf("PID \t PPID \t TTY \t CMD \n");
  
  for(int i=0; i<cnt; ++i){
    printf("%i \t %i \t %s \t %s \n", ts[i].pid, ts[i].ppid, ts[i].cmd, ts[i].tty);
  }
  //if(argc == 1){
  //  pid = atoi(argv[0]);
  //}


  return 0;
}


