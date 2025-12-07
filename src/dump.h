#ifndef DUMP_H
#define DUMP_H

#include <stdint.h>

#include "cpuid.h"

void dump_leaf(const struct cpuid_regs *regs);

void c00(char *cpu_str, size_t size);

void c01(const char cpustr[13], const char *feature_ecx[], const char *feature_edx[]);

void dump_descriptor_02(uint32_t reg, const char *feat_descriptor[]);

/* TLB, cache, prefetch hardware info */
void c02_intel();

void c02_amd();

/*
 * Leaf 0x02
 * AMD: Reserved
 * Intel: TLB, cache, prefetch hardware info.
 */
void c02();

#endif // DUMP_H
