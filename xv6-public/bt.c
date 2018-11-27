#include "proc.h"
#include "syscall.h"
#include "types.h"
#include "stat.h"
#include "user.h"

int
backtrace(struct trapframe* tf)
{




}


int
main(int argc, char *argv[])
{
  struct proc* curproc = myproc();
  struct trapframe* curtf = curproc->traoframe;
  
  if(curtf != NULL){
    backtrace();
  }

  exit();
}
