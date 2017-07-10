
.data
tttemporary_7:
	.long 0
lit0:
	.long 0 
lit1:
	.long 1 
lit2:
	.long 2 
lit3:
	.long 3 
lit4:
	.long 4 
lit5:
	.long 5 
tttemporary_26:
	.long 0
lit6:
	.long 6 
lit8:
	.long 8 
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
lit250:
	.long 250 
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
tttemporary_31:
	.long 0
tttemporary_13:
	.long 0
tttemporary_6:
	.long 0
tttemporary_24:
	.long 0
tttemporary_8:
	.long 0
tttemporary_30:
	.long 0
tttemporary_16:
	.long 0
tttemporary_28:
	.long 0
tttemporary_21:
	.long 0
tttemporary_12:
	.long 0
lit10:
	.long 10 
lit11:
	.long 11 
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
tttemporary_29:
	.long 0
tttemporary_5:
	.long 0
tttemporary_11:
	.long 0
tttemporary_22:
	.long 0
.LC0:
	.string "%d"
a:
	.long 2
i:
	.long 0
b:
	.long 0
m:
	.long 0
n:
	.long 0
.LC1:
	.string "\n"
.LC2:
	.string "\n"
par1:
	.long 0
par2:
	.long 0
par3:
	.long 0
par4:
	.long 0
par5:
	.long 0
par6:
	.long 0
.LC3:
	.string " "
.LC4:
	.string " "
.LC5:
	.string " "
.LC6:
	.string " "
.LC7:
	.string " "
.LC8:
	.string "\n"
j:
	.long 0
.LC9:
	.string "\n"
.LC10:
	.string "insira o valor de b: "
.LC11:
	.string "o valor de b eh: "
.LC12:
	.string "\n"
.LC13:
	.string "\n"
.LC14:
	.string "\n"
.LC15:
	.string "\n"
.LC16:
	.string "\n"
.LC17:
	.string "dentro while\n"
.LC18:
	.string "fora while\n"
.LC19:
	.string "a: "
.LC20:
	.string "\n"
.LC21:
	.string "dentro for a="
.LC22:
	.string "\n"
.LC23:
	.string "ok1 a > 11\n"
.LC24:
	.string "ok2 a <= 11\n"
.LC25:
	.string "\n"

.comm v, 12

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

	## TAC_ARG_RECEIVE
	movl %edi, m(%rip)

	## TAC_ARG_RECEIVE
	movl %esi, n(%rip)

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
	.globl parametros
parametros:
	.cfi_startproc
	pushq	%rbp

	## TAC_ARG_RECEIVE
	movl %edi, par1(%rip)

	## TAC_ARG_RECEIVE
	movl %esi, par2(%rip)

	## TAC_ARG_RECEIVE
	movl %edx, par3(%rip)

	## TAC_ARG_RECEIVE
	movl %ecx, par4(%rip)

	## TAC_ARG_RECEIVE
	movl %r8d, par5(%rip)

	## TAC_ARG_RECEIVE
	movl %r9d, par6(%rip)

	## TAC_PRINT: VAR
	movl par1(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC3, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl par2(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC4, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl par3(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC5, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl par4(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC6, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl par5(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC7, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl par6(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC8, %edi
	movl $0, %eax
	call printf

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

	## TAC_ARG_CALL
	movl $1, %edi

	## TAC_ARG_CALL
	movl $2, %esi

	## TAC_ARG_CALL
	movl $3, %edx

	## TAC_ARG_CALL
	movl $4, %ecx

	## TAC_ARG_CALL
	movl $5, %r8d

	## TAC_ARG_CALL
	movl $6, %r9d

	## TAC_CALL
	call parametros
	movl %eax, tttemporary_16(%rip)

	## TAC_ARG_CALL
	movl $parametros, %edi

	## TAC_MOVE
	movl tttemporary_16(%rip), %eax
	movl %eax, j(%rip)

	## TAC_VEC_WRITE
	movl $3, %eax
	movl %eax, v+8(%rip)

	## TAC_VEC_READ
	movl v+8(%rip), %eax
	movl %eax, tttemporary_17(%rip)

	## TAC_MOVE
	movl tttemporary_17(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC9, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC10, %edi
	movl $0, %eax
	call printf

	## TAC_READ
	movl $b, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$0, %eax

	## TAC_PRINT: STRING
	movl $.LC11, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl b(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC12, %edi
	movl $0, %eax
	call printf

	## TAC_MOVE
	movl $2, %eax
	movl %eax, a(%rip)

	## TAC_ARG_CALL
	movl a(%rip), %esi

	## TAC_ARG_CALL
	movl $10, %edx

	## TAC_CALL
	call sub
	movl %eax, tttemporary_18(%rip)

	## TAC_ARG_CALL
	movl $sub, %edi

	## TAC_MOVE
	movl tttemporary_18(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC13, %edi
	movl $0, %eax
	call printf

	## TAC_CALL
	call add
	movl %eax, tttemporary_19(%rip)

	## TAC_ARG_CALL
	movl $add, %edi

	## TAC_MOVE
	movl tttemporary_19(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC14, %edi
	movl $0, %eax
	call printf

	## TAC_MUL
	movl a(%rip), %eax
	imull $2, %eax
	movl %eax, tttemporary_20(%rip)

	## TAC_MOVE
	movl tttemporary_20(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC15, %edi
	movl $0, %eax
	call printf

	## TAC_DIV
	movl a(%rip), %eax
	cltd
	idivl 2(%rip)
	movl %eax, tttemporary_21(%rip)

	## TAC_MOVE
	movl tttemporary_21(%rip), %eax
	movl %eax, a(%rip)

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC16, %edi
	movl $0, %eax
	call printf

	## TAC_MOVE
	movl $0, %eax
	movl %eax, a(%rip)

	## TAC_LABEL
.ttlabel_8:

	## TAC_L
	movl a(%rip), %edx
	movl $2, %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, tttemporary_22(%rip)

	## TAC_L
	movl a(%rip), %edx
	movl $5, %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, tttemporary_23(%rip)

	## TAC_OR
	movl tttemporary_22(%rip), %eax
	testl %eax, %eax
	je .L0
	movl $1, tttemporary_24(%rip)
	jmp .L2
.L0:
	movl tttemporary_23(%rip), %eax
	testl %eax, %eax
	je .L1
	movl $1, tttemporary_24(%rip)
	jmp .L2
.L1:
	movl $0, tttemporary_24(%rip)
.L2:

	## TAC_IFZ
	movl tttemporary_24(%rip), %eax
	testl %eax, %eax
	je .ttlabel_9

	## TAC_PRINT: STRING
	movl $.LC17, %edi
	movl $0, %eax
	call printf

	## TAC_ADD
	movl a(%rip), %eax
	addl $1, %eax
	movl %eax, tttemporary_25(%rip)

	## TAC_MOVE
	movl tttemporary_25(%rip), %eax
	movl %eax, a(%rip)

	## TAC_JUMP
	jmp .ttlabel_8

	## TAC_LABEL
.ttlabel_9:

	## TAC_PRINT: STRING
	movl $.LC18, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC19, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC20, %edi
	movl $0, %eax
	call printf

	## TAC_MOVE
	movl $1, %eax
	movl %eax, a(%rip)

	## TAC_LABEL
.ttlabel_10:

	## TAC_IFLESSEQ
	movl a(%rip), %eax
	cmpl $10, %eax
	jnbe .ttlabel_11

	## TAC_PRINT: STRING
	movl $.LC21, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC22, %edi
	movl $0, %eax
	call printf

	## TAC_INC
	movl a(%rip), %eax
	addl $1, %eax
	movl %eax, a(%rip)

	## TAC_JUMP
	jmp .ttlabel_10

	## TAC_LABEL
.ttlabel_11:

	## TAC_MOVE
	movl $250, %eax
	movl %eax, a(%rip)

	## TAC_G
	movl a(%rip), %edx
	movl $11, %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, tttemporary_26(%rip)

	## TAC_IFZ
	movl tttemporary_26(%rip), %eax
	testl %eax, %eax
	je .ttlabel_12

	## TAC_PRINT: STRING
	movl $.LC23, %edi
	movl $0, %eax
	call printf

	## TAC_JUMP
	jmp .ttlabel_13

	## TAC_LABEL
.ttlabel_12:

	## TAC_PRINT: STRING
	movl $.LC24, %edi
	movl $0, %eax
	call printf

	## TAC_LABEL
.ttlabel_13:

	## TAC_EQ
	movl a(%rip), %edx
	movl a(%rip), %eax
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, tttemporary_27(%rip)

	## TAC_NOT
	cmpl $0, tttemporary_27(%rip)
	sete %al
	movzbl %al, %eax
	movl %eax, tttemporary_28(%rip)

	## TAC_NOT
	cmpl $0, tttemporary_28(%rip)
	sete %al
	movzbl %al, %eax
	movl %eax, tttemporary_29(%rip)

	## TAC_IFZ
	movl tttemporary_29(%rip), %eax
	testl %eax, %eax
	je .ttlabel_14

	## TAC_DIV
	movl a(%rip), %eax
	cltd
	idivl a(%rip)
	movl %eax, tttemporary_30(%rip)

	## TAC_MOVE
	movl tttemporary_30(%rip), %eax
	movl %eax, a(%rip)

	## TAC_JUMP
	jmp .ttlabel_15

	## TAC_LABEL
.ttlabel_14:

	## TAC_DIV
	movl $8, %eax
	cltd
	idivl lit4(%rip)
	movl %eax, tttemporary_31(%rip)

	## TAC_MOVE
	movl tttemporary_31(%rip), %eax
	movl %eax, a(%rip)

	## TAC_LABEL
.ttlabel_15:

	## TAC_PRINT: VAR
	movl a(%rip), %eax
	movl %eax, %esi
	movl $.LC0, %edi
	movl $0, %eax
	call printf

	## TAC_PRINT: STRING
	movl $.LC25, %edi
	movl $0, %eax
	call printf

	## TAC_RETURN
	movl a(%rip), %eax

	## TAC_END_FUNC
	popq	%rbp
	ret
	.cfi_endproc
