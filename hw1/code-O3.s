	.file	"code.c"
	.text
	.p2align 4,,15
	.globl	_Z5saxpyv
	.type	_Z5saxpyv, @function
_Z5saxpyv:
.LFB0:
	.cfi_startproc
	movss	a(%rip), %xmm1
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2:
	movss	x(%rax), %xmm0
	mulss	%xmm1, %xmm0
	addss	y(%rax), %xmm0
	movss	%xmm0, z(%rax)
	addq	$4, %rax
	cmpq	$262144, %rax
	jne	.L2
	rep
	ret
	.cfi_endproc
.LFE0:
	.size	_Z5saxpyv, .-_Z5saxpyv
	.globl	a
	.bss
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.zero	4
	.globl	z
	.align 32
	.type	z, @object
	.size	z, 262144
z:
	.zero	262144
	.globl	y
	.align 32
	.type	y, @object
	.size	y, 262144
y:
	.zero	262144
	.globl	x
	.align 32
	.type	x, @object
	.size	x, 262144
x:
	.zero	262144
	.ident	"GCC: (SUSE Linux) 4.6.2"
	.section	.comment.SUSE.OPTs,"MS",@progbits,1
	.string	"Ospwg"
	.section	.note.GNU-stack,"",@progbits
