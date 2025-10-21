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

void print_cpu_string(void)
{
	char pstr[13];
	get_cpu_string(pstr);
	printf("Processor Identifier String: %s\n", pstr);
}

void c01(void)
{
	struct cpuid_regs regs;

	regs.eax = 1;
	cpuid(&regs);

	printf("Stepping ID: 0x%04x\n", regs.eax & 0xf);
	regs.eax >>= 4;
	printf("Model: 0x%04x\n", regs.eax & 0xf);
	regs.eax >>= 4;
	printf("Family ID: 0x%04x\n", regs.eax & 0xf);
	regs.eax >>= 4;
	printf("Processor Type: 0x%02x\n", regs.eax & 0x3);
	regs.eax >>= 2;
	regs.eax >>= 2; // reserved bits
	printf("Extended Model ID: 0x%04x\n", regs.eax & 0xf);
	regs.eax >>= 4;
	printf("Extended Family ID: 0x%04x\n", regs.eax & 0xff);

	printf("Brand Index: 0x%08x\n", regs.ebx & 0xff);
	regs.ebx >>= 8;
	printf("CLFLUSH Line Size: %d\n", regs.ebx & 0xff);
	printf("Cache Line Size: %d\n", (regs.ebx & 0xff) * 8);
	regs.ebx >>= 8;
	if (regs.edx & (1 << 28))
		printf("Max number of addressable IDs for logical processors: %d\n", regs.ebx & 0xff);
	regs.ebx >>= 8;
	printf("Initial APIC ID: 0x%08x\n", regs.ebx & 0xff);

	puts("\n--- Features in ECX ---");
	// bit 31 is always 0 and not used
	for (int i = 0; i < 31; i++)
		printf("%s: %c\n", g_features_ecx[i], regs.ecx & (1 << i) ? 'Y' : 'N');


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
	c01();

	return 0;
}
