	.file	"code.c"
	.globl	x
	.bss
	.align 32
	.type	x, @object
	.size	x, 262144
x:
	.zero	262144
	.globl	y
	.align 32
	.type	y, @object
	.size	y, 262144
y:
	.zero	262144
	.globl	z
	.align 32
	.type	z, @object
	.size	z, 262144
z:
	.zero	262144
	.globl	a
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.text
	.globl	_Z5saxpyv
	.type	_Z5saxpyv, @function
_Z5saxpyv:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	cltq
	movss	x(,%rax,4), %xmm1
	movss	a(%rip), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, -8(%rbp)
	movl	-4(%rbp), %eax
	cltq
	movss	y(,%rax,4), %xmm0
	addss	-8(%rbp), %xmm0
	movl	-4(%rbp), %eax
	cltq
	movss	%xmm0, z(,%rax,4)
	addl	$1, -4(%rbp)
.L2:
	cmpl	$65535, -4(%rbp)
	setle	%al
	testb	%al, %al
	jne	.L3
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z5saxpyv, .-_Z5saxpyv
	.ident	"GCC: (SUSE Linux) 4.6.2"
	.section	.comment.SUSE.OPTs,"MS",@progbits,1
	.string	"ospwg"
	.section	.note.GNU-stack,"",@progbits
