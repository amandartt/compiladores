
.data
tttemporary_7:
	.long 0
tttemporary_0:
	.long 0
tttemporary_2:
	.long 0
tttemporary_4:
	.long 0
tttemporary_6:
	.long 0
tttemporary_1:
	.long 0
tttemporary_3:
	.long 0
tttemporary_5:
	.long 0
.LC0:
	.string "%d"
m:
	.long 0
n:
	.long 0
.LC1:
	.string "\n"
.LC2:
	.string "\n"
a:
	.long 2
i:
	.long 0

	## TAC_BEGIN_FUNC
	.text
	.globl add
add:
	.cfi_startproc
	pushq	%rbp

	## TAC_RETURN
	movl $2, %eax

	## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc

	## TAC_BEGIN_FUNC
	.text
	.globl sub
sub:
	.cfi_startproc
	pushq	%rbp
	 movl %ecx, m(%rip)
	 movl %edx, n(%rip)

	## TAC_PRINT: VAR
	movl m(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC1, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl n(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC2, %edi
	movl $0, %eax
	call printf

	## TAC_RETURN
	movl $1, %eax

	## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc

	## TAC_BEGIN_FUNC
	.text
	.globl main
main:
	.cfi_startproc
	pushq	%rbp

	## TAC_EQ
	movl a(%rip), %edx
	movl a(%rip), %eax
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, tttemporary_4(%rip)

	## TAC_NOT
	cmpl $0, tttemporary_4(%rbp)
	sete %al
	movzbl %al, %eax
	movl %eax, tttemporary_5(%rbp)

	## TAC_IFZ
	movl tttemporary_5(%rip), %eax
	testl %eax, %eax
	je .ttlabel_2

	## TAC_DIV
	movl a(%rip), %eax
	cltd
	idvl $2
	movl %eax, tttemporary_6(%rip)

	## TAC_MOVE
	movl tttemporary_6(%rip), %eax
	movl %eax, a(%rip)

	## TAC_JUMP
	jmp .ttlabel_3

	## TAC_LABEL
.ttlabel_2:

	## TAC_DIV
	movl $4, %eax
	cltd
	idvl $2
	movl %eax, tttemporary_7(%rip)

	## TAC_MOVE
	movl tttemporary_7(%rip), %eax
	movl %eax, a(%rip)

	## TAC_LABEL
.ttlabel_3:

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_RETURN
	movl a(%rip), %eax

	## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc
