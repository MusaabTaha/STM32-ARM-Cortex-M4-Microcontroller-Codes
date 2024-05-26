#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{

  	int val = 250;
  	int control_reg;
  	int ivar = 70;
  	int ovar = 0;
    int p1,*p2;
  	p2 = (int*)0x200F0208;
    
    //Move the content of val variable into register 
    __asm volatile("MOV R0,%0": :"r"(val));
  	__asm volatile("MOV R0,%0": :"i"(0x50));
  
    //Load the contents in memory to R1 and R2 registers
  	__asm volatile("LDR R1,=#0x21001020");
  	__asm volatile("LDR R2,=#0x20101F04");
  	__asm volatile("LDR R0,[R1]");
  	__asm volatile("LDR R1,[R2]");
  
    //Add the content of R1 and R0 and store it on R0 and then store it in memory location stored on R2
  	__asm volatile("ADD R0,R0,R1");
  	__asm volatile("STR R0,[R2]");
    
    //Move the content of control_reg varialbe to the control register of the processor
  	__asm volatile("MRS %0,CONTROL":"=r"(control_reg)::);
  
    //Move the content of variable ivar to variable ovar
  	__asm volatile("MOV %0,%1":"=r"(ovar):"r"(ivar));
    printf("%d",ovar);
  
    //Load the content of the memory location stored in pointer p2 to memory locaton stored in pointer p1
  	__asm volatile("LDR %0,[%1]":"=r"(p1):"r"(p2));

}
