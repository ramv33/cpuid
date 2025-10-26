#include "cpuid.h"

bool has_cpuid(void)
{
	bool has;

	asm volatile(
		"pushf\n\t"
		"pop	%%rax\n\t"
		"mov	%%rax, %%rcx\n\t"
		// set CF = bit 21 and complement bit 21
		"btc	$21, %%rax\n\t"
		"push	%%rax\n\t"
		"popf\n\t"
		"pushf\n\t"
		"pop	%%rax\n\t"
		// check if bit 21 was toggled
		"xor	%%rcx, %%rax\n\t"
		"shr	$20, %%rax\n\t"
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
