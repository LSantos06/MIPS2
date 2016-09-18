.data

w:	.word 64
msg: 	.asciiz	"bne"
msg1: 	.asciiz	"blez"
msg2: 	.asciiz	"bgtz"

.text
	la $s0, w
	
	lui $t0, 6
	
	bne $t0, $t1, wow
	
wow:
	li $v0,	4 # Impressao da msg	
	la $a0,	msg
	syscall
	
	blez $t0, wow1
	
	bgtz $t0, wow2
	
	# Termino do programa
	addi $v0, $zero, 10 # Codigo para terminar o programa = 10
	syscall 

wow1:

	li $v0,	4 # Impressao da msg	
	la $a0,	msg1
	syscall
	
	# Termino do programa
	addi $v0, $zero, 10 # Codigo para terminar o programa = 10
	syscall 
	
wow2:

	li $v0,	4 # Impressao da msg	
	la $a0,	msg2
	syscall
	
	# Termino do programa
	addi $v0, $zero, 10 # Codigo para terminar o programa = 10
	syscall