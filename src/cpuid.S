	.text
	.globl	has_cpuid
	.type	has_cpuid, @function
# int has_cpuid(void)
has_cpuid:
	pushfq
	pop	%rax
	# save original rflags in rcx
	mov	%rax, %rcx
	# toggle bit 21 - ID flag
	btc	$21, %rax
	push	%rax
	popf
	pushf
	# get new rflags in rax
	pop	%rax
	# check if it was modified
	xor	%rcx, %rax
	# bit 21 is 1 if it was toggled successfully
	shr	$21, %rax
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
