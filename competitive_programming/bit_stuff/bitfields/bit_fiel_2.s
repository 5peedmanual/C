	.file	"bit_fiel_2.c"
	.text
	.globl	s1
	.data
	.align 8
	.type	s1, @object
	.size	s1, 12
s1:
	.long	1
	.long	2
	.long	3
	.globl	s2
	.align 4
	.type	s2, @object
	.size	s2, 4
s2:
	.byte	5
	.zero	3
	.section	.rodata
.LC0:
	.string	"sizeof foo is %u\n"
.LC1:
	.string	"size of bar is %u\n"
.LC2:
	.string	"s2.a %d\n"
.LC3:
	.string	"s2.b %d\n"
.LC4:
	.string	"s2.c %d\n"
	.text
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
	movl	$12, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$4, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	s2(%rip), %eax
	andl	$1, %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	s2(%rip), %eax
	shrb	%al
	andl	$1, %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movzbl	s2(%rip), %eax
	shrb	$2, %al
	andl	$1, %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.1.0"
	.section	.note.GNU-stack,"",@progbits
