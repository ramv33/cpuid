#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "dump.h"
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
	get_processor_info(&proc_id, &regs);

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
	show_features(regs.ecx, feature_ecx);
	puts("\n\t--- Features in EDX ---");
	show_features(regs.edx, feature_edx);
}

void dump_descriptor_02(uint32_t reg, const char *feat_descriptor[])
{
	// register does not contain valid descriptors
	if (reg & 0x80000000)
		return;

	unsigned char b1 = ((reg & 0xff) >> 24);
	unsigned char b2 = ((reg & 0xff) >> 16);
	unsigned char b3 = ((reg & 0xff) >> 8);
	unsigned char b4 = reg & 0xff;
	
	printf("%s", feat_descriptor[b1] ? feat_descriptor[b1] : "");
	printf("%s", feat_descriptor[b2] ? feat_descriptor[b2] : "");
	printf("%s", feat_descriptor[b3] ? feat_descriptor[b3] : "");
	printf("%s", feat_descriptor[b4] ? feat_descriptor[b4] : "");
}

/*
 * Leaf 0x02
 * AMD: Reserved
 * Intel: TLB, cache, prefetch hardware info.
 */
void c02()
{
	char vendor_id[13];

	get_vendor_id(vendor_id);
	if (!strcmp(vendor_id, VENDOR_STRING_INTEL)) {
		puts("CPUID.EAX=0x2");
		puts("=============");
		c02_intel();
	} else if (!strcmp(vendor_id, VENDOR_STRING_AMD)) {
		puts("CPUID.EAX=0x2 is not supported on AMD!");
	}
}
