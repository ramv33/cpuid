#ifndef CPUID_H

#include <stdint.h>

// Feature information - Table 3-19 Vol 2
#define ECX_BIT_SSE3		0
#define ECX_BIT_PCLMULQDQ	1
#define ECX_BIT_DTES64		2
#define ECX_BIT_MONITOR		3
#define ECX_BIT_DS_CPL		4
#define ECX_BIT_VMX		5
#define ECX_BIT_SMX		6
#define ECX_BIT_EIST		7
#define ECX_BIT_TM2		8
#define ECX_BIT_SSSE3		9
#define ECX_BIT_CNXT_ID		10
#define ECX_BIT_SDBG		11
#define ECX_BIT_FMA		12
#define ECX_BIT_CMPXCHG16B	13
#define ECX_BIT_xTPR_UPD_CTRL	14
#define ECX_BIT_PDCM		15
#define ECX_BIT_RESERVED	16
#define ECX_BIT_PCID		17
#define ECX_BIT_DCA		18
#define ECX_BIT_SSE4_1		19
#define ECX_BIT_SSE4_2		20
#define ECX_BIT_x2APIC		21
#define ECX_BIT_MOVBE		22
#define ECX_BIT_POPCNT		23
#define ECX_BIT_TSC_DEADLINE	24
#define ECX_BIT_AESNI		25
#define ECX_BIT_XSAVE		26
#define ECX_BIT_OSXSAVE		27
#define ECX_BIT_AVX		28
#define ECX_BIT_F16C		29
#define ECX_BIT_RDRAND		30
#define ECX_BIT_UNUSED		31

#define BIT(x)	(1 << (x))

const char *g_features_ecx[] = {
	[ECX_BIT_SSE3] = "SSE3",
	[ECX_BIT_PCLMULQDQ] = "PCLMULQDQ",
	[ECX_BIT_DTES64] = "64-bit DS Area",
	[ECX_BIT_MONITOR] = "MONITOR/MWAIT",
	[ECX_BIT_DS_CPL] = "CPL Qualified Debug Store",
	[ECX_BIT_VMX] = "VM extensions",
	[ECX_BIT_SMX] = "Safer Mode Extensions",
	[ECX_BIT_EIST] = "Enhanced Intel SpeedStep",
	[ECX_BIT_TM2] = "Thermal Monitor 2",
	[ECX_BIT_SSSE3] = "SSSE3",
	[ECX_BIT_CNXT_ID] = "L1 Context ID",
	[ECX_BIT_SDBG] = "IA32_DEBUG_INTERFACE MSR for Silicon Debug",
	[ECX_BIT_FMA] = "FMA",
	[ECX_BIT_CMPXCHG16B] = "CMPXCHG16B",
	[ECX_BIT_xTPR_UPD_CTRL] = "xTPR Update Control",
	[ECX_BIT_PDCM] = "PerfMon and Debug Capability",
	[ECX_BIT_RESERVED] = "RESERVED",
	[ECX_BIT_PCID] = "Process-context Identifiers",
	[ECX_BIT_DCA] = "DCA (Prefetch data from a mmaped device)",
	[ECX_BIT_SSE4_1] = "SSE4_1",
	[ECX_BIT_SSE4_2] = "SSE4_2",
	[ECX_BIT_x2APIC] = "x2APIC",
	[ECX_BIT_MOVBE] = "MOVBE",
	[ECX_BIT_POPCNT] = "POPCNT",
	[ECX_BIT_TSC_DEADLINE] = "TSC_DEADLINE",
	[ECX_BIT_AESNI] = "AESNI",
	[ECX_BIT_XSAVE] = "XSAVE",
	[ECX_BIT_OSXSAVE] = "OSXSAVE",
	[ECX_BIT_AVX] = "AVX",
	[ECX_BIT_F16C] = "F16C",
	[ECX_BIT_RDRAND] = "RDRAND",
};


struct cpuid_regs {
	int32_t	eax;
	int32_t	ebx;
	int32_t	ecx;
	int32_t	edx;
};

void cpuid(struct cpuid_regs* regs);
bool has_cpuid(void);

#endif
