tttemporary_7:
	.long 0
tttemporary_9:
	.long 0
tttemporary_14:
	.long 0
tttemporary_0:
	.long 0
tttemporary_10:
	.long 0
tttemporary_2:
	.long 0
tttemporary_4:
	.long 0
tttemporary_13:
	.long 0
tttemporary_6:
	.long 0
tttemporary_8:
	.long 0
tttemporary_12:
	.long 0
tttemporary_1:
	.long 0
tttemporary_3:
	.long 0
tttemporary_15:
	.long 0
tttemporary_5:
	.long 0
tttemporary_11:
	.long 0
a:
	.long 0
i:
	.long 0
v:
	.long 1
	.long 3

	## TAC_BEGIN_FUNC

.globl main
main:
	.cfi_startproc
	pushq	%rbp

	## TAC_VEC_READ
	movl v+8(%rip), %eax
	movl %eax, tttemporary_8(%rip)

	## TAC_VEC_WRITE
	movl tttemporary_8(%rip), %eax
	movl %eax, v+4(%rip)

	## TAC_ADD
	movl 1(%rip), %eax
	addl 1(%rip), %eax
	movl %eax, tttemporary_9(%rip)

	## TAC_VEC_READ
	movl tttemporary_9(%rip), %eax
	cltq
	movl v(,%rax, 4), %eax
	movl %eax, tttemporary_10(%rip)

	## TAC_VEC_WRITE
	movl tttemporary_10(%rip), %eax
	movl %eax, v+4(%rip)

	## TAC_ADD
	movl 10(%rip), %eax
	addl a(%rip), %eax
	movl %eax, tttemporary_11(%rip)

	## TAC_MOVE
	movl tttemporary_11(%rip), %eax
	movl %eax, a(%rip)

	## TAC_SUB
	movl i(%rip), %eax
	subl a(%rip), %eax
	movl %eax, tttemporary_12(%rip)

	## TAC_MOVE
	movl tttemporary_12(%rip), %eax
	movl %eax, i(%rip)

	## TAC_LABEL
.ttlabel_4:

	## TAC_G
	movl a(%rip), %edx
	movl 0(%rip), %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, tttemporary_13(%rip)

	## TAC_IFZ
	movl tttemporary_13(%rip), %eax
	testl %eax, %eax
	je .ttlabel_5

	## TAC_ADD
	movl a(%rip), %eax
	addl 1(%rip), %eax
	movl %eax, tttemporary_14(%rip)

	## TAC_MOVE
	movl tttemporary_14(%rip), %eax
	movl %eax, a(%rip)

	## TAC_JUMP
	jmp .ttlabel_4

	## TAC_LABEL
.ttlabel_5:

	## TAC_MOVE
	movl a(%rip), %eax
	movl %eax, i(%rip)

	## TAC_LABEL
.ttlabel_6:

	## TAC_IFLESSEQ
	movl i(%rip), %eax
	cmpl 10(%rip), %eax
	jg .ttlabel_7

	## TAC_MUL
	movl a(%rip), %eax
	imull 50(%rip), %eax
	movl %eax, tttemporary_15(%rip)

	## TAC_MOVE
	movl tttemporary_15(%rip), %eax
	movl %eax, i(%rip)

	## TAC_INC
	movl i(%rip), %eax
	addl $1, %eax
	movl %eax, i(%rip)

	## TAC_JUMP
	jmp .ttlabel_6

	## TAC_LABEL
.ttlabel_7:

	## TAC_RETURN
	movl a(%rip), %eax

	## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc
