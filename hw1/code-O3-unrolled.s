	.file	"code.c"
	.text
	.p2align 4,,15
	.globl	_Z5saxpyv
	.type	_Z5saxpyv, @function
_Z5saxpyv:
.LFB0:
	.cfi_startproc
	movss	a(%rip), %xmm0
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2:
	movss	x(%rax), %xmm8
	movss	x+4(%rax), %xmm7
	mulss	%xmm0, %xmm8
	movss	x+8(%rax), %xmm6
	mulss	%xmm0, %xmm7
	movss	x+12(%rax), %xmm5
	mulss	%xmm0, %xmm6
	movss	x+16(%rax), %xmm4
	mulss	%xmm0, %xmm5
	movss	x+20(%rax), %xmm3
	mulss	%xmm0, %xmm4
	addss	y(%rax), %xmm8
	movss	x+24(%rax), %xmm2
	mulss	%xmm0, %xmm3
	movss	x+28(%rax), %xmm1
	mulss	%xmm0, %xmm2
	mulss	%xmm0, %xmm1
	addss	y+4(%rax), %xmm7
	addss	y+8(%rax), %xmm6
	addss	y+12(%rax), %xmm5
	addss	y+16(%rax), %xmm4
	movss	%xmm8, z(%rax)
	addss	y+20(%rax), %xmm3
	addss	y+24(%rax), %xmm2
	addss	y+28(%rax), %xmm1
	movss	%xmm7, z+4(%rax)
	movss	%xmm6, z+8(%rax)
	movss	%xmm5, z+12(%rax)
	movss	%xmm4, z+16(%rax)
	movss	%xmm3, z+20(%rax)
	movss	%xmm2, z+24(%rax)
	movss	%xmm1, z+28(%rax)
	addq	$32, %rax
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
