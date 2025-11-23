#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "cpuid.h"

void c00(char *cpu_str, size_t size)
{
	struct cpuid_regs regs;
	char pstr[13];

	regs.eax = regs.ebx = regs.ecx = regs.edx = 0;
	cpuid(&regs);

	parse_vendor_id(pstr, &regs);
	if (cpu_str && size) {
		strncpy(cpu_str, pstr, size);
		cpu_str[size-1] = '\0';
	}

	printf("\tProcessor Identifier String: %s\n", pstr);
	printf("\tHighest supported function: 0x%08x\n", regs.eax);
}

void c01(const char cpustr[13], const char *feature_ecx[], const char *feature_edx[])
{
	struct cpuid_regs regs;

	regs.eax = 1;
	regs.ebx = regs.ecx = regs.edx = 0;
	cpuid(&regs);

	struct processor_identifier proc_id;
	if (!strcmp(cpustr, "AuthenticAMD"))
		get_amd_proc_id(regs.eax, &proc_id); 
	else if (!strcmp(cpustr, "GenuineIntel"))
		get_intel_proc_id(regs.eax, &proc_id);

	printf("\tFamily: %02x\n", proc_id.family);
	printf("\tModel: %02x\n", proc_id.model);
	printf("\tStepping: %02x\n", proc_id.stepping);

	printf("\tBrand Index: 0x%08x\n", regs.ebx & 0xff);
	regs.ebx >>= 8;
	printf("\tCLFLUSH Line Size: %d\n", regs.ebx & 0xff);
	printf("\tCache Line Size: %d\n", (regs.ebx & 0xff) * 8);
	regs.ebx >>= 8;
	// reserved if EDX[28] is 0
	if (regs.edx & (1 << 28))
		printf("\tMax number of addressable IDs for logical processors: %d\n", regs.ebx & 0xff);
	regs.ebx >>= 8;
	printf("\tInitial APIC ID: 0x%08x\n", regs.ebx & 0xff);

	puts("\n\t--- Features in ECX ---");
	dump_features(regs.ecx, feature_ecx);
	puts("\n\t--- Features in EDX ---");
	dump_features(regs.edx, feature_edx);
}

// Reserved on AMD...
void c02()
{
	struct cpuid_regs regs;

	regs.eax = 2;
	regs.ebx = regs.ecx = regs.edx = 0;

	// AL is always 0x01
	// If msb of register is 0, it contains valid info; otherwise it is reserved.
	// If valid, each byte of the register contains 1 byte descriptors.
	// The descriptors are described in Table-3.21
}

int main(void)
{
	struct cpuid_regs regs;
	char cpustr[13];

	if (!has_cpuid()) {
		puts("CPUID not supported");
		return 1;
	}

	puts("CPUID.EAX=0x0");
	puts("=============");
	c00(cpustr, sizeof(cpustr));

	puts("CPUID.EAX=0x1");
	puts("=============");
	c01(cpustr, g_feat_01_amd_ecx, g_feat_01_amd_edx);
	puts("CPUID.EAX=0x2");
	puts("=============");
	c02();

	return 0;
}
