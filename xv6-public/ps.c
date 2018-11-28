#include "user.h"
#include "syscall.h"
#include "types.h"
#include "stat.h"

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct uproc{
  uint sz;              // size of process memory
  int pid;              // Process iD
  char name[16];        // Process name
  enum procstate state; // Process states
  void* chan;           // If non-zero, sleeping on chan
  int killed;           // If non-zero, have been killed
  int parent_pid;       // Parent pid  
};
int main(int argc, char *argv[])
{
   // iterate through the process table, get info for each process
   struct uproc *up = malloc(sizeof(struct uproc));
   
   int pid = 0;

  /*
  struct uproc *up = malloc(sizeof(struct uproc));
  printf(1, "Process name        PID     ParentID    Size        Killed      State\n");
   for(i = 0; i < 64; i++){
    if(getprocinfo(i, up) == 0){
      printf(1, "%s\t\t %d\t\t %d\t %d\t %d\t",up->name, up->pid, up->parent_pid, up->sz, up->killed);
      switch(up->state){
        case UNUSED:
         printf(1, "UNUSED\n");
         break;
        case EMBRYO:
         printf(1, "EMBRYO\n");
         break;
        case SLEEPING:
         printf(1, "SLEEPING\n");
         break;
        case RUNNABLE:
         printf(1, "RUNNABLE\n");
         break;
        case RUNNING:
         printf(1, "RUNNING\n");
         break;
        case ZOMBIE:
         printf(1, "ZOMBIE\n");
         break;
     }
    }
  }
  */
  getprocinfo(pid, up);
  free(up);
  return 0;



}
