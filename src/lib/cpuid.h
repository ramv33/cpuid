#ifndef CPUID_H
#define CPUID_H

#include <stdint.h>

#define BIT(x)	(1 << (x))
#define VENDOR_STRING_INTEL	"GenuineIntel"
#define VENDOR_STRING_AMD	"AuthenticAMD"

static const char *g_feat_01_intel_ecx[] = {
	[0] = "SSE3", [1] = "PCLMULQDQ", [2] = "64-bit DS Area", [3] = "MONITOR/MWAIT",
	[4] = "CPL Qualified Debug Store", [5] = "VM extensions", [6] = "Safer Mode Extensions", [7] = "Enhanced Intel SpeedStep",
	[8] = "Thermal Monitor 2", [9] = "SSSE3", [10] = "L1 Context ID", [11] = "IA32_DEBUG_INTERFACE MSR for Silicon Debug",
	[12] = "FMA", [13] = "CMPXCHG16B", [14] = "xTPR Update Control", [15] = "PerfMon and Debug Capability",
	[16] = "RESERVED", [17] = "Process-context Identifiers", [18] = "DCA (Prefetch data from a mmaped device)", [19] = "SSE4_1",
	[20] = "SSE4_2", [21] = "x2APIC", [22] = "MOVBE", [23] = "POPCNT",
	[24] = "TSC_DEADLINE", [25] = "AESNI", [26] = "XSAVE", [27] = "OSXSAVE",
	[28] = "AVX", [29] = "F16C", [30] = "RDRAND", [31] = "UNUSED"
};

static const char *g_feat_01_intel_edx[] = {
	[0] = "FPU", [1] = "VME", [2] = "Debugging Extensions", [3] = "Page Size Extension",
	[4] = "RDTSC", [5] = "MSR", [6] = "PAE", [7] = "MCE",
	[8] = "CMPXCHG8B", [9] = "APIC", [10] = "RESERVED", [11] = "SYSENTER/SYSEXIT",
	[12] = "MTRR", [13] = "Page Global Bit", [14] = "MCA", [15] = "CMOV",
	[16] = "Page Attr Table", [17] = "36-bit PSE", [18] = "Processor Serial No.", [19] = "CLFLUSH",
	[20] = "RESERVED", [21] = "Debug Store", [22] = "ACPI", [23] = "MMX",
	[24] = "FXSAVE/FXRSTOR", [25] = "SSE", [26] = "SSE2", [27] = "Self Snoop",
	[28] = "Hyper-Threading", [29] = "Thermal Monitor", [30] = "RESERVED", [31] = "Pending Break Enable"
};

static const char *g_feat_01_amd_ecx[] = {
	[0] = "SSE3", [1] = "PCLMULQDQ", [2] = "RESERVED", [3] = "MONITOR/MWAIT",
	[4] = "RESERVED", [5] = "RESERVED", [6] = "RESERVED", [7] = "RESERVED",
	[8] = "RESERVED", [9] = "SSSE3", [10] = "RESERVED", [11] = "RESERVED",
	[12] = "FMA", [13] = "CMPXCHG16B", [14] = "RESERVED", [15] = "RESERVED",
	[16] = "RESERVED", [17] = "RESERVED", [18] = "RESERVED", [19] = "SSE4_1",
	[20] = "SSE4_2", [21] = "x2APIC", [22] = "MOVBE", [23] = "POPCNT",
	// AES instead of AESNI in amd
	[24] = "RESERVED", [25] = "AES", [26] = "XSAVE", [27] = "OSXSAVE",
	[28] = "AVX", [29] = "F16C", [30] = "RDRAND", [31] = "UNUSED"
};

static const char *g_feat_01_amd_edx[] = {
	[0] = "FPU", [1] = "VME", [2] = "Debugging Extensions", [3] = "Page Size Extension",
	[4] = "RDTSC", [5] = "MSR", [6] = "PAE", [7] = "MCE",
	[8] = "CMPXCHG8B", [9] = "APIC", [10] = "RESERVED", [11] = "SYSENTER/SYSEXIT",
	[12] = "MTRR", [13] = "Page Global Bit", [14] = "MCA", [15] = "CMOV",
	[16] = "Page Attr Table", [17] = "36-bit PSE", [18] = "RESERVED", [19] = "CLFLUSH",
	[20] = "RESERVED", [21] = "RESERVED", [22] = "RESERVED", [23] = "MMX",
	[24] = "FXSAVE/FXRSTOR", [25] = "SSE", [26] = "SSE2", [27] = "RESERVED",
	[28] = "Hyper-Threading", [29] = "RESERVED", [30] = "RESERVED", [31] = "RESERVED"
};

struct cpuid_regs {
	uint32_t	eax;
	uint32_t	ebx;
	uint32_t	ecx;
	uint32_t	edx;
};

struct processor_identifier {
	unsigned char	family;
	unsigned char	model;
	unsigned char	stepping;
};

int has_cpuid(void);
void cpuid(struct cpuid_regs *regs);
void show_features(int32_t reg, const char *feat_array[]);
void dump_all_features(int32_t reg, const char *feat_array[]);
void get_vendor_id(char pstr[13]);
void parse_vendor_id(char vendor_id[13], struct cpuid_regs *regs);

// Get Processor Identifier bits from CPUID.1.EAX
void get_amd_proc_id(uint32_t eax, struct processor_identifier *proc_id);
void get_intel_proc_id(uint32_t eax, struct processor_identifier *proc_id);
void get_processor_info(struct processor_identifier *proc_id, struct cpuid_regs *regs);

static inline unsigned char get_stepping(uint32_t eax)
{
	// bits 0-3
	return eax & 0xf;
}

static inline unsigned char get_base_fam(uint32_t eax)
{
	// bits 4-7
	return ((eax >> 4) & 0xf);
}

static inline unsigned char get_base_model(uint32_t eax)
{
	// bits 8-11
	return ((eax >> 8) & 0xf);
}

static inline unsigned char get_ext_fam(uint32_t eax)
{
	// bits 20-27
	return ((eax >> 20) & 0xff);
}

static inline unsigned char get_ext_model(uint32_t eax)
{
	// bits 16-19
	return ((eax >> 16) & 0xf);
}

// For intel processors, bits 12-13
static inline unsigned char get_proc_type(uint32_t eax)
{
	return ((eax >> 12) & 0x3);
}

#endif
