#include "proc.h"
#include "syscall.h"
#include "types.h"
#include "stat.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"

//int
//backtrace(struct proc* curproc)
//{
//  struct trapframe* tf = curproc->tf;
//  uint32_t ebp = tf->ebp;
  //uint32_t arg0, arg1, arg2, arg3, arg4;
//  while(ebp){
    
//   uint32_t eax = tf->eax;
//   uint32_t ebx = tf->ebx;
//   uint32_t ecx = tf->ecx;
//   uint32_t edx = tf->edx;
//   uint32_t edi = tf->edi;
//   uint32_t esi = tf->esi;
//   uint32_t eip = tf->eip;
//   uint32_t esp = tf->esp;
/*   uint32_t eflag = tf->eflags;
   uint32_t old_ebp = ebp;
   ebp = *(uint32_t*)ebp;
   cprintf("eax: %x\nebx: %x\necx: %x\nedx: %x\nedi:%x\nesi: %x\neip: %x\nesp: %x\neflag: %x\nebp: %x\n",\
   eax,ebx,ecx,edx,edi,esi,eip,esp,eflag,old_ebp);
   cprintf("return addr: %x\n", *(old_ebp+1);
   cprintf("#0: %x\n#1:%x\n#2: %x\n#3: %x\n#4: %x\n",*(old_ebp+2),*(old_ebp+3), *(old_ebp+4),*(old_ebp+5), *(old_ebp+6));  
  }
  return 0;
  
}
*/
int
main(int argc, char *argv[])
{
  struct proc *curproc = myproc();
  
  //if(curproc != 0){
    backtrace(curproc);
 // }

  exit();
}

