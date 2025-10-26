#include <stdio.h>

#include "cpuid.h"


int has_cpuid(void)
{
	int has;

	asm volatile(
		"pushf\n\t"
		"pop	%%rax\n\t"
		"mov	%%rax, %%rcx\n\t"
		// complement bit 21
		"btc	$21, %%rax\n\t"
		"push	%%rax\n\t"
		"popf\n\t"
		// get rflags and check if it was updated
		"pushf\n\t"
		"pop	%%rax\n\t"
		// check if bit 21 was toggled
		"xor	%%rcx, %%rax\n\t"
		"shr	$21, %%rax\n\t"
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

void dump_features(int32_t reg, const char *feat_array[])
{
	for (int i = 0; i < 31; i++)
		printf("\t%s: %c\n", feat_array[i], reg & (1 << i) ? 'Y' : 'N');
}

void get_cpu_string(char pstr[13])
{
	struct cpuid_regs regs;

	regs.eax = 0;
	cpuid(&regs);

	pstr[0] = regs.ebx & 0xff;
	pstr[1] = (regs.ebx >> 8) & 0xff;
	pstr[2] = (regs.ebx >> 16) & 0xff;
	pstr[3] = (regs.ebx >> 24) & 0xff;
	pstr[4] = regs.edx & 0xff;
	pstr[5] = (regs.edx >> 8) & 0xff;
	pstr[6] = (regs.edx >> 16) & 0xff;
	pstr[7] = (regs.edx >> 24) & 0xff;
	pstr[8] = regs.ecx & 0xff;
	pstr[9] = (regs.ecx >> 8) & 0xff;
	pstr[10] = (regs.ecx >> 16) & 0xff;
	pstr[11] = (regs.ecx >> 24) & 0xff;
	pstr[12] = '\0';
}
