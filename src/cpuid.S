	.text
	.globl	has_cpuid
	.type	has_cpuid, @function
# bool has_cpuid(void)
has_cpuid:
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	movl	$1, %edx
	pushfq
	btcq	$21, (%rsp)
	# Old bit 21=1 in eax
	cmovcl	%edx, %eax
	popfq
	pushfq
	btsq	$21, (%rsp)
	# New bit 21 in ecx
	cmovcl	%edx, %ecx
	# eax = was bit 21 toggled?
	xorl	%ecx, %eax
	addq	$8, %rsp
	
	ret

	.globl	cpuid
	.type	cpuid, @function
# void cpuid(struct cpuid_regs* regs)
cpuid:
	push	%rbx

	movl	0x0(%rdi), %eax
	movl	0x4(%rdi), %ebx
	movl	0x8(%rdi), %ecx
	movl	0xc(%rdi), %edx
	cpuid
	movl	%eax, 0x0(%rdi)
	movl	%ebx, 0x4(%rdi)
	movl	%ecx, 0x8(%rdi)
	movl	%edx, 0xc(%rdi)

	pop	%rbx
	ret
