#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "dump.h"
#include "cpuid.h"


/* TLB, cache, prefetch hardware info */
void c02_intel()
{
	struct cpuid_regs regs;

	regs.eax = 2;
	regs.ebx = regs.ecx = regs.edx = 0;
	cpuid(&regs);

	// AL is always 0x01
	assert((regs.eax & 0xff) == 0x01);

	// If msb of register is 0, it contains valid info; otherwise it is reserved.
	// If valid, each byte of the register contains 1 byte descriptors.
	// The descriptors are described in Table-3.21
	dump_descriptor_02(regs.eax, g_feat_02_intel_descriptors);
	dump_descriptor_02(regs.ebx, g_feat_02_intel_descriptors);
	dump_descriptor_02(regs.ecx, g_feat_02_intel_descriptors);
	dump_descriptor_02(regs.edx, g_feat_02_intel_descriptors);
}

void c03_intel()
{

}

void c04_intel()
{

}
