#include "cpuid.h"

bool has_cpuid(void)
{
	int has;

	asm volatile(
		"xorl	%%eax, %%eax\n\t"
		"xorl	%%ecx, %%ecx\n\t"
		"movl	$1, %%ebx\n\t"
		"pushfq\n\t"
		// set CF = bit 21 and complement bit 21
		"btcq	$21, (%%rsp)\n\t"
		// move old bit 21 into %eax
		"cmovcl	%%ebx, %%eax\n\t"
		"popfq\n\t"
		"pushfq\n\t"
		"btsq	$21, (%%rsp)\n\t"
		// move new bit 21 into %ecx
		"cmovcl	%%ebx, %%ecx\n\t"
		// old in ecx, new in eax
		"xorl	%%ecx, %%eax\n\t"
		"movl	%%eax, %0\n\t"
		"addq	$8, %%rsp\n\t"
		: "=r" (has)
	);
}

void cpuid(struct cpuid_regs* regs)
{

	asm volatile(
		"cpuid\n\t"
		// copies the values from regs into the correct registers before and after
		: "+a" (regs->eax), "+b" (regs->ebx),
		  "+c" (regs->ecx), "+d" (regs->edx)
		: // no input
		: "memory"
	);
}
