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

static const char *g_feat_02_intel_descriptors[] = {
	// 0x00 is the NULL descriptor
	// Missing entries are RESERVED
	[0x01] = "ITLB: 4KiB pages; 4-way; 32 entries",
	[0x02] = "ITLB: 4MiB pages; Fully associative; 2 entries",
	[0x03] = "DTLB: 4KiB Pages; 4-way; 32 entries",
	[0x04] = "DTLB: 4MiB Pages; 4-way; 8 entries",
	[0x05] = "TLB1: 4MiB Pages; 4-way; 32 entries",
	[0x06] = "iL1: 8KiB; 4-way; 32B lines",
	[0x08] = "iL1: 16KiB; 4-way; 64B lines",
	[0x09] = "iL1: 32KiB; 4-way: 64B lines",
	[0x0a] = "dL1: 8KiB; 2-way: 32B lines",
	[0x0b] = "ITLB: 4MiB; 4-way; 4 entries",
	[0x0c] = "dL1: 16KiB; 4-way; 32B lines",
	[0x0d] = "dL1: 16KiB; 4-way; 64B lines",
	[0x0E] = "dL1: 24KiB; 6-way; 64B line",
	[0x1D] = "L2: 128KiB; 2-way; 64B line",
	[0x21] = "L2: 256KiB; 8-way; 64B line",
	[0x22] = "L3: 512KiB; 4-way; 64B line; 2 lines per sector",
	[0x23] = "L3: 1MiB; 8-way; 64B line; 2 lines per sector",
	[0x24] = "L2: 1MiB; 16-way; 64B line",
	[0x25] = "L3: 2MiB; 8-way; 64B line; 2 lines per sector",
	[0x29] = "L3: 4MiB; 8-way; 64B line; 2 lines per sector",
	[0x2C] = "dL1: 32KiB; 8-way; 64B line",
	[0x30] = "iL1: 32KiB; 8-way; 64B line",
	[0x40] = "? No L2 or, if processor contains a valid L2, no L3",
	[0x41] = "L2: 128KiB; 4-way; 32B line",
	[0x42] = "L2: 256KiB; 4-way; 32B line",
	[0x43] = "L2: 512KiB; 4-way; 32B line",
	[0x44] = "L2: 1MiB; 4-way; 32B line",
	[0x45] = "L2: 2MiB; 4-way; 32B line",
	[0x46] = "L3: 4MiB; 4-way; 64B line",
	[0x47] = "L3: 8MiB; 8-way; 64B line",
	[0x48] = "L2: 3MiB; 12-way; 64B line",
	[0x49] = "L3: 4MiB; 16-way; 64B line; (Intel Xeon processor MP, Family 0FH, Model 06H)\n"
		"L2: 4MiB; 16-way; 64B line",
	[0x4A] = "L3: 6MiB; 12-way; 64B line",
	[0x4B] = "L3: 8MiB; 16-way; 64B line",
	[0x4C] = "L3: 12MiB; 12-way; 64B line",
	[0x4D] = "L3: 16MiB; 16-way; 64B line",
	[0x4E] = "L2: 6MiB; 24-way; 64B line",
	[0x4F] = "ITLB: 4KiB pages; 32 entries",
	[0x50] = "ITLB: 4KiB and 2MiB or 4MiB pages; 64 entries",
	[0x51] = "ITLB: 4KiB and 2MiB or 4MiB pages; 128 entries",
	[0x52] = "ITLB: 4KiB and 2MiB or 4MiB pages; 256 entries",
	[0x55] = "ITLB: 2MiB or 4MiB pages; fully associative; 7 entries",
	[0x56] = "DTLB: 4MiB pages; 4-way; 16 entries",
	[0x57] = "DTLB: 4KiB pages; 4-way; 16 entries",
	[0x59] = "DTLB: 4KiB pages; fully associative; 16 entries",
	[0x5A] = "DTLB: 2MiB or 4MiB pages; 4-way; 32 entries",
	[0x5B] = "DTLB: 4KiB and 4MiB pages; 64 entries",
	[0x5C] = "DTLB: 4KiB and 4MiB pages; 128 entries",
	[0x5D] = "DTLB: 4KiB and 4MiB pages; 256 entries",
	[0x60] = "dL1: 16KiB; 8-way; 64B line",
	[0x61] = "ITLB: 4KiB pages; fully associative; 48 entries",
	[0x63] = "DTLB: 2MiB or 4MiB pages; 4-way; 32 entries\n"
		"DTLB: 1GiB pages; 4-way; 4 entries",
	[0x64] = "DTLB: 4KiB pages; 4-way; 512 entries",
	[0x66] = "dL1: 8KiB; 4-way; 64B line",
	[0x67] = "dL1: 16KiB; 4-way; 64B line",
	[0x68] = "dL1: 32KiB; 4-way; 64B line",
	[0x6A] = "uTLB: 4KiB pages; 8-way; 64 entries",
	[0x6B] = "DTLB: 4KiB pages; 8-way; 256 entries",
	[0x6C] = "DTLB: 2MiB or 4MiB pages; 8-way; 128 entries",
	[0x6D] = "DTLB: 1GiB pages; fully associative; 16 entries",
	[0x70] = "Trace: 12K-uop; 8-way",
	[0x71] = "Trace: 16K-uop; 8-way",
	[0x72] = "Trace: 32K-uop; 8-way",
	[0x76] = "ITLB: 2MiB or 4MiB pages; fully associative; 8 entries",
	[0x78] = "L2: 1MiB; 4-way; 64B line",
	[0x79] = "L2: 128KiB; 8-way; 64B line; 2 lines/sector",
	[0x7A] = "L2: 256KiB; 8-way; 64B line; 2 lines/sector",
	[0x7B] = "L2: 512KiB; 8-way; 64B line; 2 lines/sector",
	[0x7C] = "L2: 1MiB; 8-way; 64B line; 2 lines/sector",
	[0x7D] = "L2: 2MiB; 8-way; 64B line",
	[0x7F] = "L2: 512KiB; 2-way; 64B line",
	[0x80] = "L2: 512KiB; 8-way; 64B line",
	[0x82] = "L2: 256KiB; 8-way; 32B line",
	[0x83] = "L2: 512KiB; 8-way; 32B line",
	[0x84] = "L2: 1MiB; 8-way; 32B line",
	[0x85] = "L2: 2MiB; 8-way; 32B line",
	[0x86] = "L2: 512KiB; 4-way; 64B line",
	[0x87] = "L2: 1MiB; 8-way; 64B line",
	[0xa0] = "DTLB: 4 KB pages; fully associative; 32 entries",
	[0xb0] = "ITLB: 4 KB pages; 4-way; 128 entries",
	[0xb1] = "ITLB: 2MiB pages; 4-way; 8 entries; or 4MiB pages; 4-way; 4 entries",
	[0xb2] = "ITLB: 4 KB pages; 4-way; 64 entries",
	[0xb3] = "DTLB: 4 KB pages; 4-way; 128 entries",
	[0xb4] = "DTLB L1: 4 KB pages; 4-way associative; 256 entries",
	[0xb5] = "ITLB: 4 KB pages; 8-way; 64 entries",
	[0xb6] = "ITLB: 4 KB pages; 8-way; 128 entries",
	[0xba] = "DTLB L1: 4 KB pages; 4-way associative; 64 entries",
	[0xc0] = "DTLB: 4 KB & 4MiB pages; 4-way associative; 8 entries",
	[0xc1] = "STLB L2: 4 KB/2MiB pages; 8-way associative; 1024 entries",
	[0xc2] = "DTLB: 4 KB/2MiB pages; 4-way associative; 16 entries",
	[0xc3] = "STLB L2: 4 KB/2MiB pages; 6-way; 1536 entries; 1 GiB pages; 4-way; 16 entries",
	[0xc4] = "DTLB: 2MiB/4MiB pages; 4-way associative; 32 entries",
	[0xca] = "STLB L2: 4 KB pages; 4-way associative; 512 entries",
	[0xd0] = "L3: 512 KB; 4-way; 64B line",
	[0xd1] = "L3: 1MiB; 4-way; 64B line",
	[0xd2] = "L3: 2MiB; 4-way; 64B line",
	[0xd6] = "L3: 1MiB; 8-way; 64B line",
	[0xd7] = "L3: 2MiB; 8-way; 64B line",
	[0xd8] = "L3: 4MiB; 8-way; 64B line",
	[0xdc] = "L3: 1.5MiB; 12-way; 64B line",
	[0xdd] = "L3: 3MiB; 12-way; 64B line",
	[0xde] = "L3: 6MiB; 12-way; 64B line",
	[0xe2] = "L3: 2MiB; 16-way; 64B line",
	[0xe3] = "L3: 4MiB; 16-way; 64B line",
	[0xe4] = "L3: 8MiB; 16-way; 64B line",
	[0xea] = "L3: 12MiB; 24-way; 64B line",
	[0xeb] = "L3: 18MiB; 24-way; 64B line",
	[0xec] = "L3: 24MiB; 24-way; 64B line",
	[0xf0] = "Prefetch: 64B",
	[0xf1] = "Prefetch: 128B",
	// 0xfe: Leaf 2 does not report TLB descriptor info; use leaf 0x18
	// 0xff: Leaf 2 does not report cache descriptor info; use leaf 0x4
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
