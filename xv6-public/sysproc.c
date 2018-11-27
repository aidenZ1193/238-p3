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
  struct proc* curproc = myproc();
  //backtrace(p);
  //return 0;
  struct trapframe* tf = curproc->tf;
  uint ebp = tf->ebp;
 // uint arg0, arg1, arg2, arg3, arg4;
  while(ebp){

   uint eax = tf->eax;
   uint ebx = tf->ebx;
   uint ecx = tf->ecx;
   uint edx = tf->edx;
   uint edi = tf->edi;
   uint esi = tf->esi;
   uint eip = tf->eip;
   uint esp = tf->esp;
   uint eflag = tf->eflags;
   uint old_ebp = ebp;
   ebp = *(uint*)ebp;
   cprintf("eax: %x\nebx: %x\necx: %x\nedx: %x\nedi:%x\nesi: %x\neip: %x\nesp: %x\neflag: %x\nebp: %x\n",\
   eax,ebx,ecx,edx,edi,esi,eip,esp,eflag,old_ebp);
   cprintf("return addr: %x\n", *(uint*)(old_ebp+4));
   cprintf("#0: %x\n#1:%x\n#2: %x\n#3: %x\n#4: %x\n",*(uint*)(old_ebp+8),*(uint*)(old_ebp+12), *(uint*)(old_ebp+16),*(uint*)(old_ebp+20), *(uint*)(old_ebp+24));
  }
  return 0;
}
