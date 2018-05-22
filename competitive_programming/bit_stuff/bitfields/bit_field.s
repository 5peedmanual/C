	.file	"bit_field.c"
	.text
	.comm	receiver,4,4
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movzbl	receiver(%rip), %eax
	shrb	$2, %al
	andl	$1, %eax
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	movzbl	receiver(%rip), %eax
	andl	$-2, %eax
	movb	%al, receiver(%rip)
	movzbl	receiver(%rip), %eax
	orl	$2, %eax
	movb	%al, receiver(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.1.0"
	.section	.note.GNU-stack,"",@progbits
