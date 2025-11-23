#include <stdio.h>
#include <string.h>

#include "cpuid.h"

/*
 * get_amd_proc_id
 * 	Extract AMD CPU stepping, family, and model from @eax and store in @proc_id
 *
 * 	@eax:		eax register after calling CPUID.01
 * 	@proc_id:	stepping, family, and model is stored in this struct.
 */
void get_amd_proc_id(uint32_t eax, struct processor_identifier *proc_id)
{
	unsigned char base_fam = get_base_fam(eax);
	unsigned char ext_fam = get_base_fam(eax);
	unsigned char base_model = get_base_model(eax);
	unsigned char ext_model = get_base_model(eax);

	proc_id->stepping = get_stepping(eax);

	proc_id->family = base_fam;
	if (base_fam == 0xf)
		proc_id->family += ext_fam;

	if (base_fam == 0xf)
		proc_id->model = (ext_model << 4) | base_model;
	else
		proc_id->model = base_model;
}

/*
 * get_intel_proc_id
 * 	Extract Intel CPU stepping, family, and model from @eax and store in @proc_id
 *
 * 	@eax:		eax register after calling CPUID.01
 * 	@proc_id:	stepping, family, and model is stored in this struct.
 */
void get_intel_proc_id(uint32_t eax, struct processor_identifier *proc_id)
{
	unsigned char base_fam = get_base_fam(eax);
	unsigned char ext_fam = get_base_fam(eax);
	unsigned char base_model = get_base_model(eax);
	unsigned char ext_model = get_base_model(eax);

	proc_id->stepping = get_stepping(eax);

	proc_id->family = base_fam;
	if (base_fam == 0xf)
		proc_id->family += ext_fam;

	// Intel checks for 0x6 which AMD does not
	if (base_fam == 0xf || base_fam == 0x6)
		proc_id->model = (ext_model << 4) | base_model;
	else
		proc_id->model = base_model;
}

/*
 * has_cpuid:
 *	Returns 0 if processor does not support CPUID, and non-zero otherwise
 */
int has_cpuid(void)
{
	int has;

	__asm__ volatile(
		"pushf\n\t"
		"pop	%%rax\n\t"
		// save rflags in rcx
		"mov	%%rax, %%rcx\n\t"
		// complement bit 21
		"btc	$21, %%rax\n\t"
		"push	%%rax\n\t"
		"popf\n\t"
		// get rflags and check if it was updated
		"pushf\n\t"
		"pop	%%rax\n\t"
		// check if bit 21 was toggled
		"xor	%%rcx, %%rax\n\t"
		"shr	$21, %%rax\n\t"
		: "=r" (has)
	);
}

/*
 * cpuid
 * 	Call CPUID with values in @regs.
 * 	@regs is modified to contain the values returned.
 */
void cpuid(struct cpuid_regs* regs)
{

	__asm__ volatile(
		"cpuid\n\t"
		// copies the values from regs into the correct registers before and after
		: "+a" (regs->eax), "+b" (regs->ebx),
		  "+c" (regs->ecx), "+d" (regs->edx)
		: // no input
		: "memory"
	);
}

void dump_features(int32_t reg, const char *feat_array[])
{
	for (int i = 0; i < 31; i++)
		printf("\t%s: %c\n", feat_array[i], reg & (1 << i) ? 'Y' : 'N');
}

/*
 * parse_vendor_id
 * 	Parse the 12 byte vendor identification string from registers ebx, ecx, edx
 *
 * 	@vendor_id:	char array of size 13 atleast
 * 	@regs:		regs after calling CPUID.00
 */
void parse_vendor_id(char vendor_id[13], struct cpuid_regs *regs)
{
	vendor_id[0] = regs->ebx & 0xff;
	vendor_id[1] = (regs->ebx >> 8) & 0xff;
	vendor_id[2] = (regs->ebx >> 16) & 0xff;
	vendor_id[3] = (regs->ebx >> 24) & 0xff;
	vendor_id[4] = regs->edx & 0xff;
	vendor_id[5] = (regs->edx >> 8) & 0xff;
	vendor_id[6] = (regs->edx >> 16) & 0xff;
	vendor_id[7] = (regs->edx >> 24) & 0xff;
	vendor_id[8] = regs->ecx & 0xff;
	vendor_id[9] = (regs->ecx >> 8) & 0xff;
	vendor_id[10] = (regs->ecx >> 16) & 0xff;
	vendor_id[11] = (regs->ecx >> 24) & 0xff;
	vendor_id[12] = '\0';
}

/*
 * get_vendor_id
 * 	Call CPUID.EAX=0 and store the vendor id string in @vendor_id
 *
 * 	@vendor_id:	char array of size 13 atleast
 */
void get_vendor_id(char vendor_id[13])
{
	struct cpuid_regs regs = { .eax = 0, .ebx = 0, .ecx = 0, .edx = 0};
	cpuid(&regs);
	parse_vendor_id(vendor_id, &regs);
}

void get_processor_info(struct processor_identifier *proc_id, struct cpuid_regs *regs)
{
	char vendor_id[13] = "";

	get_vendor_id(vendor_id);
	if (!strcmp(vendor_id, "AuthenticAMD"))
		get_amd_proc_id(regs->eax, proc_id);
	else if (!strcmp(vendor_id, "GenuineIntel"))
		get_intel_proc_id(regs->eax, proc_id);
}
