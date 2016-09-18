.data

vetor:		.word 1 2 3 4 5 6 7 8 9
lado: 		.word 3
msg:		.asciiz "\nFIM"
novaLinha:	.asciiz "\n"

.text
	# Declaracao de variaveis
	la $t0, vetor # Carregando o endereco do primeiro elemento da matriz
	la $t1, lado # Carregando o endereco do lado
	
	lw $s0, 0($t0) # $s0, Primeiro elemento da matriz
	lw $s1, 0($t1) # $s1, Largura da matriz

	addi $s2, $zero, 0 # $s2, contadorColuna = 0
	addi $s3, $zero, 1 # $s3, contadorLinha = 1, ex: 3 linhas, 2 quebras de linha
	
	jal pr_mat # Chamada de funcao
	
	# Termino do programa
	li $v0, 10 # Codigo para terminar o programa = 10
	syscall

pr_mat:
	beq $s2, $s1, line # Se fim da coluna, vai para a proxima linha
	
	lw $s4, 0($t0) # $s3, valor atual
	
	# Impressao do valor atual da matriz
	addi $v0, $zero, 1 # Codigo para imprimir um inteiro
	add $a0, $zero, $s4 # Carrega o valor atual para impressao
	syscall	
	
	addi $t0, $t0, 4 # Passa para o proximo elemento do vetor
		
	addi $s2, $s2, 1 # contadorColuna++;	
		
	j pr_mat
	
line:
	beq $s3, $s1, fim # Se fim das linhas, contadorLinha == lado, termina lasso
	
	# Pula uma linha
	addi $v0, $zero, 4 # Codigo para imprimir uma string = 4
	la $a0, novaLinha # Carregando a string msg para o argumento
	syscall
	
	addi $s3, $s3, 1 # contadorLinha++;
	
	add $s2, $zero, $zero # contadorColuna = 0;
	
	j pr_mat
	
fim:
	addi $v0, $zero, 4 # Codigo para imprimir uma string = 4
	la $a0, msg # Carregando a string msg para o argumento
	syscall
	
	# Pula para instrucao apos a chamada de funcao 
	jr $ra
