.data
	
primos:	.word	1,3,5,7,11,13,17,19
size:	.word	8	
msg: 	.asciiz	"Os oito primeiros numeros primos sao: "
space: 	.ascii	" "

.text 
	la $t0,	primos # Carrega o endereco inicial do array de primos
	la $t1,	size # Carrega o endereco do size

	lw $t1,	0($t1) # Carrega size em t1 	
	
	li $v0,	4 # Impressao da msg	
	la $a0,	msg
	syscall
	 
loop:	 
	beq $t1, $zero,	exit # Se percorreu todo o array, encerra
	
	li $v0,	1 # Impressao de um inteiro
	lw $a0,	0($t0) # Inteiro a ser exibido 	 	
	syscall		
	 	
	li $v0,	4 # Impressao do space	
	la $a0,	space
	syscall
	
	addi $t0, $t0, 4 # Incrementa indice array 	
	addi $t1, $t1, -1 # Decrementa contador
 	j loop 	 
 	
exit:	 	
	li $v0,	10 # Termino do programa
	syscall
