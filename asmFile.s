tttemporary_7:
	.long 0
tttemporary_26:
	.long 0
tttemporary_18:
	.long 0
tttemporary_9:
	.long 0
tttemporary_14:
	.long 0
tttemporary_0:
	.long 0
tttemporary_10:
	.long 0
tttemporary_23:
	.long 0
tttemporary_2:
	.long 0
tttemporary_17:
	.long 0
tttemporary_27:
	.long 0
tttemporary_4:
	.long 0
tttemporary_20:
	.long 0
tttemporary_13:
	.long 0
tttemporary_6:
	.long 0
tttemporary_24:
	.long 0
tttemporary_8:
	.long 0
tttemporary_16:
	.long 0
tttemporary_21:
	.long 0
tttemporary_12:
	.long 0
tttemporary_1:
	.long 0
tttemporary_25:
	.long 0
tttemporary_19:
	.long 0
tttemporary_3:
	.long 0
tttemporary_15:
	.long 0
tttemporary_5:
	.long 0
tttemporary_11:
	.long 0
tttemporary_22:
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
	movl %eax, tttemporary_14(%rip)

	## TAC_VEC_WRITE
	movl tttemporary_14(%rip), %eax
	movl %eax, v+4(%rip)

	## TAC_ADD
	movl 1(%rip), %eax
	addl 1(%rip), %eax
	movl %eax, tttemporary_15(%rip)

	## TAC_VEC_READ
	movl tttemporary_15(%rip), %eax
	cltq
	movl v(,%rax, 4), %eax
	movl %eax, tttemporary_16(%rip)

	## TAC_VEC_WRITE
	movl tttemporary_16(%rip), %eax
	movl %eax, v+4(%rip)

	## TAC_ADD
	movl 10(%rip), %eax
	addl a(%rip), %eax
	movl %eax, tttemporary_17(%rip)

	## TAC_MOVE
	movl tttemporary_17(%rip), %eax
	movl %eax, a(%rip)

	## TAC_SUB
	movl i(%rip), %eax
	subl a(%rip), %eax
	movl %eax, tttemporary_18(%rip)

	## TAC_MOVE
	movl tttemporary_18(%rip), %eax
	movl %eax, i(%rip)

	## TAC_LABEL
.ttlabel_6:

	## TAC_G
	movl a(%rip), %edx
	movl 0(%rip), %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, tttemporary_19(%rip)

	## TAC_G
	movl i(%rip), %edx
	movl 0(%rip), %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, tttemporary_20(%rip)

	## TAC_OR
	movl tttemporary_19(%rip), %eax
	testl %eax, %eax
	je .L0
	movl $1, tttemporary_21(%rip)
	jmp .L2
.L0:
	movl tttemporary_20(%rip), %eax
	testl %eax, %eax
	je .L1
	movl $1, tttemporary_21(%rip)
	jmp .L2
.L1:
	movl $0, tttemporary_21(%rip)
.L2:

	## TAC_IFZ
	movl tttemporary_21(%rip), %eax
	testl %eax, %eax
	je .ttlabel_7

	## TAC_ADD
	movl a(%rip), %eax
	addl 1(%rip), %eax
	movl %eax, tttemporary_22(%rip)

	## TAC_MOVE
	movl tttemporary_22(%rip), %eax
	movl %eax, a(%rip)

	## TAC_JUMP
	jmp .ttlabel_6

	## TAC_LABEL
.ttlabel_7:

	## TAC_LABEL
.ttlabel_8:

	## TAC_G
	movl a(%rip), %edx
	movl 0(%rip), %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, tttemporary_23(%rip)

	## TAC_G
	movl i(%rip), %edx
	movl 0(%rip), %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, tttemporary_24(%rip)

	## TAC_AND
	movl tttemporary_23(%rip), %eax
	testl %eax, %eax
	jne .L3
	movl $0, tttemporary_25(%rip)
	jmp .L5
.L3:
	movl tttemporary_24(%rip), %eax
	testl %eax, %eax
	je .L4
	movl $1, tttemporary_25(%rip)
	jmp .L5
.L4:
	movl $0, tttemporary_25(%rip)
.L5:

	## TAC_IFZ
	movl tttemporary_25(%rip), %eax
	testl %eax, %eax
	je .ttlabel_9

	## TAC_ADD
	movl a(%rip), %eax
	addl 1(%rip), %eax
	movl %eax, tttemporary_26(%rip)

	## TAC_MOVE
	movl tttemporary_26(%rip), %eax
	movl %eax, a(%rip)

	## TAC_JUMP
	jmp .ttlabel_8

	## TAC_LABEL
.ttlabel_9:

	## TAC_MOVE
	movl a(%rip), %eax
	movl %eax, i(%rip)

	## TAC_LABEL
.ttlabel_10:

	## TAC_IFLESSEQ
	movl i(%rip), %eax
	cmpl 10(%rip), %eax
	jg .ttlabel_11

	## TAC_MUL
	movl a(%rip), %eax
	imull 50(%rip), %eax
	movl %eax, tttemporary_27(%rip)

	## TAC_MOVE
	movl tttemporary_27(%rip), %eax
	movl %eax, i(%rip)

	## TAC_INC
	movl i(%rip), %eax
	addl $1, %eax
	movl %eax, i(%rip)

	## TAC_JUMP
	jmp .ttlabel_10

	## TAC_LABEL
.ttlabel_11:

	## TAC_RETURN
	movl a(%rip), %eax

	## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc
