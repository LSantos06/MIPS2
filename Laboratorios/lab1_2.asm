.data

vetor:	.word 1 4 3 4 5 6 7 8 9
tam: 	.word 9
msg:	.asciiz "\nFIM"

.text
	# Declaracao de variaveis
	la $t0, vetor # Carregando o endereco do primeiro elemento do vetor
	la $t1, tam # Carregando o endereco do tamanho
	
	lw $s0, 0($t0) # $s0, Primeiro elemento do vetor
	lw $s1, 0($t1) # $s1, Tamanho do vetor

	addi $s2, $zero, 0 # $s2, contador = 0
	
	jal pr_vet # Chamada de funcao
	
	# Termino do programa
	li $v0, 10 # Codigo para terminar o programa = 10
	syscall

pr_vet:
	beq $s2, $s1, fim # Se fim do vetor, contador == tam, termina lasso
	
	lw $s3, 0($t0) # $s3, endereco do valor atual
	
	# Impressao do valor atual do vetor
	addi $v0, $zero, 1 # Codigo para imprimir um inteiro
	add $a0, $zero, $s3 # Valor atual do vetor
	syscall
	
	addi $t0, $t0, 4 # Passa para o proximo elemento do vetor de ints
	addi $s2, $s2, 1 # contador++;
			
	j pr_vet
	
fim:
	addi $v0, $zero, 4 # Codigo para imprimir uma string = 4
	la $a0, msg # Carregando a string msg para o argumento
	syscall
	
	# Pula para instrucao apos a chamada de funcao 
	jr $ra
	
