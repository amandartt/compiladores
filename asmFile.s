
.data
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
tttemporary_17:
	.long 0
tttemporary_4:
	.long 0
tttemporary_13:
	.long 0
tttemporary_6:
	.long 0
tttemporary_8:
	.long 0
tttemporary_16:
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
.LC0:
	.string "%d"
.LC1:
	.string "\n"
.LC2:
	.string "%d"
.LC3:
	.string "\n"
.LC4:
	.string "%d"
.LC5:
	.string "\n"
.LC6:
	.string "%d"
.LC7:
	.string "\n"
.LC8:
	.string "dentro while\n"
.LC9:
	.string "fora while"
.LC10:
	.string "a:"
.LC11:
	.string "%d"
.LC12:
	.string "\n"
.LC13:
	.string "ok1 a > 11"
.LC14:
	.string "ok2 a <= 11"
a:
	.long 2
i:
	.long 0

	## TAC_BEGIN_FUNC
	.text
	.globl main
main:
	.cfi_startproc
	pushq	%rbp

	## TAC_SUB
	movl a(%rip), %eax
	subl $1, %eax
	movl %eax, tttemporary_9(%rip)

	## TAC_MOVE
	movl tttemporary_9(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC1, %edi
	movl $0, %eax
	call printf

	## TAC_ADD
	movl a(%rip), %eax
	addl $1, %eax
	movl %eax, tttemporary_10(%rip)

	## TAC_MOVE
	movl tttemporary_10(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC2, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC3, %edi
	movl $0, %eax
	call printf

	## TAC_MUL
	movl a(%rip), %eax
	imull $2, %eax
	movl %eax, tttemporary_11(%rip)

	## TAC_MOVE
	movl tttemporary_11(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC4, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC5, %edi
	movl $0, %eax
	call printf

	## TAC_DIV
	movl a(%rip), %eax
	cltd
	idivl 2(%rip)
	movl %eax, tttemporary_12(%rip)

	## TAC_MOVE
	movl tttemporary_12(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC6, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC7, %edi
	movl $0, %eax
	call printf

	## TAC_MOVE
	movl $0, %eax
	movl %eax, a(%rip)

	## TAC_LABEL
.ttlabel_4:

	## TAC_L
	movl a(%rip), %edx
	movl $2, %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, tttemporary_13(%rip)

	## TAC_L
	movl a(%rip), %edx
	movl $5, %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, tttemporary_14(%rip)

	## TAC_OR
	movl tttemporary_13(%rip), %eax
	testl %eax, %eax
	je .L0
	movl $1, tttemporary_15(%rip)
	jmp .L2
.L0:
	movl tttemporary_14(%rip), %eax
	testl %eax, %eax
	je .L1
	movl $1, tttemporary_15(%rip)
	jmp .L2
.L1:
	movl $0, tttemporary_15(%rip)
.L2:

	## TAC_IFZ
	movl tttemporary_15(%rip), %eax
	testl %eax, %eax
	je .ttlabel_5

	## TAC_PRINT: STRING
	movl $.LC8, %edi
	movl $0, %eax
	call printf

	## TAC_ADD
	movl a(%rip), %eax
	addl $1, %eax
	movl %eax, tttemporary_16(%rip)

	## TAC_MOVE
	movl tttemporary_16(%rip), %eax
	movl %eax, a(%rip)

	## TAC_JUMP
	jmp .ttlabel_4

	## TAC_LABEL
.ttlabel_5:

	## TAC_PRINT: STRING
	movl $.LC9, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC10, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC11, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC12, %edi
	movl $0, %eax
	call printf

	## TAC_MOVE
	movl $250, %eax
	movl %eax, a(%rip)

	## TAC_G
	movl a(%rip), %edx
	movl $11, %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, tttemporary_17(%rip)

	## TAC_IFZ
	movl tttemporary_17(%rip), %eax
	testl %eax, %eax
	je .ttlabel_6

	## TAC_PRINT: STRING
	movl $.LC13, %edi
	movl $0, %eax
	call printf

	## TAC_JUMP
	jmp .ttlabel_7

	## TAC_LABEL
.ttlabel_6:

	## TAC_PRINT: STRING
	movl $.LC14, %edi
	movl $0, %eax
	call printf

	## TAC_LABEL
.ttlabel_7:

	## TAC_RETURN
	movl a(%rip), %eax

	## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc
