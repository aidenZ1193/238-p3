#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int 
sys_thread_create(void)
{
  // retrive args 
  // int thread_create(void(*fcn)(void*), void *arg, void*stack)
  char* fcn;
  char* arg;
  char* stack;
  
  if(argptr(0, &fcn, 4)<0)
    cprintf("Arg#1 function error.\n");
  if(argptr(1, &arg, 4)<0)
    cprintf("Arg#2 args error.\n");
  if(argptr(2, &stack, 4)<0)
    cprintf("Arg#3 stack error.\n");  

  return thread_create((void*)fcn, arg, stack);
}

int 
sys_thread_join(void)
{
  return thread_join();
}

int
sys_thread_exit(void){
  return thread_exit();
}


int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;

}

//extern int backtrace(struct proc*);

int
sys_backtrace(void)
{
  backtrace();
  return 0;
}

int
sys_getprocinfo()
{
  // iterate through the process table, get info for each process
  //struct uproc *up = malloc(sizeof(struct proc));
  /*
   int pid = 0;
   char *up;
   
   if(argint(0, &pid) < 0 || argptr(1, &up, sizeof(struct uproc)) < 0){
      return -1;
   }
   getprocinfo(pid, (struct uproc*)up);
   cprintf("going through sysproc.c\n");
   */
   //struct uproc *up = malloc(sizeof(struct uproc));
   struct uproc* up = 0;
   int i = 0;
   //process name, process id, parent process id, size of process memory, process state, whether process is waiting on a channel, and whether it's been killed
   cprintf("Process name        PID     ParentID    Size        Killed      State\n");
   for(i = 0; i < 64; i++){
    if(getprocinfo(i, (struct uproc*)up) == 0){
      cprintf("\t%s\t\t %d\t %d\t %d\t\t %d\t",up->name, up->pid, up->parent_pid, up->sz, up->killed);
      switch(up->state){
        case UNUSED:
         cprintf("UNUSED\n");
         break;
        case EMBRYO:
         cprintf("EMBRYO\n");
         break;
        case SLEEPING:
         cprintf("SLEEPING\n");
         break;
        case RUNNABLE:
         cprintf("RUNNABLE\n");
         break;
        case RUNNING:
         cprintf("RUNNING\n");
         break;
        case ZOMBIE:
         cprintf("ZOMBIE\n");
         break;
     }
    }
  }  
  //free(up);
  return 0;
}
