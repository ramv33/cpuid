#ifndef CPUID_H
#define CPUID_H

#include <stdint.h>

#define BIT(x)	(1 << (x))

static const char *g_feat_ecx_intel_01[] = {
	[0] = "SSE3", [1] = "PCLMULQDQ", [2] = "64-bit DS Area", [3] = "MONITOR/MWAIT",
	[4] = "CPL Qualified Debug Store", [5] = "VM extensions", [6] = "Safer Mode Extensions", [7] = "Enhanced Intel SpeedStep",
	[8] = "Thermal Monitor 2", [9] = "SSSE3", [10] = "L1 Context ID", [11] = "IA32_DEBUG_INTERFACE MSR for Silicon Debug",
	[12] = "FMA", [13] = "CMPXCHG16B", [14] = "xTPR Update Control", [15] = "PerfMon and Debug Capability",
	[16] = "RESERVED", [17] = "Process-context Identifiers", [18] = "DCA (Prefetch data from a mmaped device)", [19] = "SSE4_1",
	[20] = "SSE4_2", [21] = "x2APIC", [22] = "MOVBE", [23] = "POPCNT",
	[24] = "TSC_DEADLINE", [25] = "AESNI", [26] = "XSAVE", [27] = "OSXSAVE",
	[28] = "AVX", [29] = "F16C", [30] = "RDRAND", [31] = "UNUSED"
};

static const char *g_feat_edx_intel_01[] = {
	[0] = "FPU", [1] = "VME", [2] = "Debugging Extensions", [3] = "Page Size Extension",
	[4] = "RDTSC", [5] = "MSR", [6] = "PAE", [7] = "MCE",
	[8] = "CMPXCHG8B", [9] = "APIC", [10] = "Reserved", [11] = "SYSENTER/SYSEXIT",
	[12] = "MTRR", [13] = "Page Global Bit", [14] = "MCA", [15] = "CMOV",
	[16] = "Page Attr Table", [17] = "36-bit PSE", [18] = "Processor Serial No.", [19] = "CLFLUSH",
	[20] = "Reserved", [21] = "Debug Store", [22] = "ACPI", [23] = "MMX",
	[24] = "FXSAVE/FXRSTOR", [25] = "SSE", [26] = "SSE2", [27] = "Self Snoop",
	[28] = "HTT", [29] = "Thermal Monitor", [30] = "Reserved", [31] = "Pending Break Enable"
};

static const char *g_feat_ecx_amd_01[] = {
	[0] = "SSE3", [1] = "PCLMULQDQ", [2] = "64-bit DS Area", [3] = "MONITOR/MWAIT",
	[4] = "CPL Qualified Debug Store", [5] = "VM extensions", [6] = "Safer Mode Extensions", [7] = "Enhanced Intel SpeedStep",
	[8] = "Thermal Monitor 2", [9] = "SSSE3", [10] = "L1 Context ID", [11] = "IA32_DEBUG_INTERFACE MSR for Silicon Debug",
	[12] = "FMA", [13] = "CMPXCHG16B", [14] = "xTPR Update Control", [15] = "PerfMon and Debug Capability",
	[16] = "RESERVED", [17] = "Process-context Identifiers", [18] = "DCA (Prefetch data from a mmaped device)", [19] = "SSE4_1",
	[20] = "SSE4_2", [21] = "x2APIC", [22] = "MOVBE", [23] = "POPCNT",
	[24] = "TSC_DEADLINE", [25] = "AESNI", [26] = "XSAVE", [27] = "OSXSAVE",
	[28] = "AVX", [29] = "F16C", [30] = "RDRAND", [31] = "UNUSED"
};

static const char *g_feat_edx_amd_01[] = {
	[0] = "FPU", [1] = "VME", [2] = "Debugging Extensions", [3] = "Page Size Extension",
	[4] = "RDTSC", [5] = "MSR", [6] = "PAE", [7] = "MCE",
	[8] = "CMPXCHG8B", [9] = "APIC", [10] = "Reserved", [11] = "SYSENTER/SYSEXIT",
	[12] = "MTRR", [13] = "Page Global Bit", [14] = "MCA", [15] = "CMOV",
	[16] = "Page Attr Table", [17] = "36-bit PSE", [18] = "Processor Serial No.", [19] = "CLFLUSH",
	[20] = "Reserved", [21] = "Debug Store", [22] = "ACPI", [23] = "MMX",
	[24] = "FXSAVE/FXRSTOR", [25] = "SSE", [26] = "SSE2", [27] = "Self Snoop",
	[28] = "HTT", [29] = "Thermal Monitor", [30] = "Reserved", [31] = "Pending Break Enable"
};

struct cpuid_regs {
	int32_t	eax;
	int32_t	ebx;
	int32_t	ecx;
	int32_t	edx;
};

int has_cpuid(void);
void cpuid(struct cpuid_regs* regs);
void dump_features(int32_t reg, const char *feat_array[]);
void get_cpu_string(char pstr[13]);

#endif
