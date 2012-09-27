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
	shufps	$0, %xmm0, %xmm0
	.p2align 4,,10
	.p2align 3
.L2:
	movaps	x(%rax), %xmm8
	movaps	x+16(%rax), %xmm7
	mulps	%xmm0, %xmm8
	movaps	x+32(%rax), %xmm6
	mulps	%xmm0, %xmm7
	movaps	x+48(%rax), %xmm5
	mulps	%xmm0, %xmm6
	movaps	x+64(%rax), %xmm4
	mulps	%xmm0, %xmm5
	addps	y(%rax), %xmm8
	movaps	x+80(%rax), %xmm3
	mulps	%xmm0, %xmm4
	addps	y+16(%rax), %xmm7
	movaps	x+96(%rax), %xmm2
	mulps	%xmm0, %xmm3
	addps	y+32(%rax), %xmm6
	movaps	x+112(%rax), %xmm1
	mulps	%xmm0, %xmm2
	addps	y+48(%rax), %xmm5
	movaps	%xmm8, z(%rax)
	mulps	%xmm0, %xmm1
	movaps	%xmm7, z+16(%rax)
	movaps	%xmm6, z+32(%rax)
	movaps	%xmm5, z+48(%rax)
	addps	y+64(%rax), %xmm4
	addps	y+80(%rax), %xmm3
	addps	y+96(%rax), %xmm2
	addps	y+112(%rax), %xmm1
	movaps	%xmm4, z+64(%rax)
	movaps	%xmm3, z+80(%rax)
	movaps	%xmm2, z+96(%rax)
	movaps	%xmm1, z+112(%rax)
	subq	$-128, %rax
	cmpq	$262144, %rax
	jne	.L2
	rep
	ret
	.cfi_endproc
.LFE0:
	.size	_Z5saxpyv, .-_Z5saxpyv
	.globl	a
	.bss
	.align 16
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
