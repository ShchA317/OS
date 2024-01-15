#include <stdio.h>
#include <linux/sched.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>

#define	SYS_GET_TASK_STRUCTURE	549;
#define	SYS_HELLO		548;

int main(int argc, char* argv[]){
  long int retval = syscall(SYS_HELLO);
  if(retval != 0){
    printf("error in syscall\n");
    return retval;
  }

  struct task_struct* ts = malloc(sizeof(struct task_struct)*200);

  if(argc == 0){
    long int retval = syscall(SYS_GET_TASK_STRUCTURE, ts);  
    if(retval != 0){
      printf("error in syscall");
      return retval;
    }

    printf("PID \t PPID \t TTY \t CMD \n");
    
    for(int i=0; i<200; ++i){
      printf(ts[i]->pid->val);
      printf("\n");
    }
  }
  if(argc == 1){
    pid = atoi(argv[0]);
  }


  return 0;
}


