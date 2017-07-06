tttemporary_0:
	.long 0
tttemporary_1:
	.long 0
a:
	.long 0
i:
	.long 0
## TAC_BEGIN_FUNC

.globl main
main:
	.cfi_startproc
	pushq	%rbp
## TAC_ADD
	movl 10(%rip), %eax
	addl a(%rip), %eax
	movl %eax, tttemporary_1(%rip)
## TAC_RETURN
	movl a(%rip), %eax
## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc
