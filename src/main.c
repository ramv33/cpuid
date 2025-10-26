#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "cpuid.h"


void print_cpu_string(void)
{
	char pstr[13];
	get_cpu_string(pstr);
	printf("Processor Identifier String: %s\n", pstr);
}

void c01(const char *feature_ecx[], const char *feature_edx[])
{
	struct cpuid_regs regs;

	regs.eax = 1;
	regs.ebx = regs.ecx = regs.edx = 0;
	cpuid(&regs);

	puts("CPUID.EAX=0x1");
	puts("=============");
	printf("\tStepping ID: 0x%04x\n", regs.eax & 0xf);
	regs.eax >>= 4;
	printf("\tModel: 0x%04x\n", regs.eax & 0xf);
	regs.eax >>= 4;
	printf("\tFamily ID: 0x%04x\n", regs.eax & 0xf);
	regs.eax >>= 4;
	printf("\tProcessor Type: 0x%02x\n", regs.eax & 0x3);
	regs.eax >>= 2;
	regs.eax >>= 2; // reserved bits
	printf("\tExtended Model ID: 0x%04x\n", regs.eax & 0xf);
	regs.eax >>= 4;
	printf("\tExtended Family ID: 0x%04x\n", regs.eax & 0xff);

	printf("\tBrand Index: 0x%08x\n", regs.ebx & 0xff);
	regs.ebx >>= 8;
	printf("\tCLFLUSH Line Size: %d\n", regs.ebx & 0xff);
	printf("\tCache Line Size: %d\n", (regs.ebx & 0xff) * 8);
	regs.ebx >>= 8;
	if (regs.edx & (1 << 28))
		printf("\tMax number of addressable IDs for logical processors: %d\n", regs.ebx & 0xff);
	regs.ebx >>= 8;
	printf("\tInitial APIC ID: 0x%08x\n", regs.ebx & 0xff);

	puts("\n\t--- Features in ECX ---");
	dump_features(regs.ecx, feature_ecx);
	puts("\n\t--- Features in EDX ---");
	dump_features(regs.edx, feature_edx);
}

void c02()
{
	struct cpuid_regs regs;

	regs.eax = 2;
	regs.ebx = regs.ecx = regs.edx = 0;

	puts("CPUID.EAX=0x2");
	puts("=============");

	// AL is always 0x01
	// If msb of register is 0, it contains valid info; otherwise it is reserved.
	// If valid, each byte of the register contains 1 byte descriptors.
	// The descriptors are described in Table-3.21

}

int main(void)
{
	struct cpuid_regs regs;

	if (!has_cpuid()) {
		puts("CPUID not supported");
		return 1;
	}

	print_cpu_string();
	puts("---------------\n");
	c01(g_feat_ecx_intel_01, g_feat_edx_intel_01);

	return 0;
}
