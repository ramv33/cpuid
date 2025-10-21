#ifndef CPUID_H

#include <stdint.h>

struct cpuid_regs {
	int32_t	eax;
	int32_t	ebx;
	int32_t	ecx;
	int32_t	edx;
};

void cpuid(struct cpuid_regs* regs);
bool has_cpuid(void);

#endif
