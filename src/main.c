#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "cpuid.h"

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

int main(void)
{
	struct cpuid_regs regs;

	if (!has_cpuid()) {
		puts("CPUID not supported");
		return 1;
	}

	char pstr[13];
	get_cpu_string(pstr);
	puts(pstr);

	return 0;
}
