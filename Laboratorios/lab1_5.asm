.data

v1:	.word 1 2 3 4
v2:	.word 4 3 2 1
tam: 	.word 4
msg:	.asciiz "\nFIM"

.text 
	# Declaracao de variaveis
 	la $t0, v1 # Carregando o endereco do primeiro elemento do v1
 	la $t1, v2 # Carregando o endereco do primeiro elemento do v2
 	la $t2, tam # Carregando o endereco do tamanho de v1
 	
 	lw $s0, 0($t0) # $s0, Primeiro elemento do v1
 	lw $s1, 0($t1) # $s1, Primeiro elemento do v2
 	lw $s2, 0($t2) # $s2, Tamanho do v1
 	
 	add $s3, $zero, $zero # $s2, contador = 0
 	
 	jal sum_vet # Chamada de funcao para contar o numero de elementos do vetor
	
	# Termino do programa
	li $v0, 10 # Codigo para terminar o programa = 10
	syscall
	
sum_vet:
	beq $s3, $s2, fim
	
	lw $s4, 0($t0) # $s4, valor atual de v1
	lw $s5, 0($t1) # $s5, valor atual de v2
	
	add $s6, $s4, $s5 # $s6, soma dos valores atuais de v1 e v2
	
	sw $s6, 0($t0) # Armazena a soma no v1
	
	lw $s4, 0($t0) # $s4, valor atual de v1
	
	# Impressao do valor atual do v1
	addi $v0, $zero, 1 # Codigo para imprimir um inteiro
	add $a0, $zero, $s4 # Valor atual de v1
	syscall
	
	addi $t0, $t0, 4 # Passa para o proximo elemento do v1
	addi $t1, $t1, 4 # Passa para o proximo elemento do v2
	addi $s3, $s3, 1 # contador++;
	
	j sum_vet
			
fim:
	addi $v0, $zero, 4 # Codigo para imprimir uma string = 4
	la $a0, msg # Carregando a string msg para o argumento
	syscall
	
	# Pula para instrucao apos a chamada de funcao 
	jr $ra
