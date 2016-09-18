.data

m1:		.word 1 1 1 2 2 2 3 3 3
m2:		.word 4 4 4 5 5 5 6 6 6 
m3:		.word 0 0 0 0 0 0 0 0 0
lado: 		.word 3
msg:		.asciiz "\nFIM"
novaLinha:	.asciiz "\n"

.text 
	# Declaracao de variaveis
	la $t0, m1 # Carregando o endereco do primeiro elemento da matriz 1
	la $t1, m2 # Carregando o endereco do primeiro elemento da matriz 2
	la $t2, m3 # Carregando o endereco do primeiro elemento da matriz 3
	la $t3, lado # Carregando o endereco do lado das matrizes
	
	lw $s0, 0($t0) # $s0, Primeiro elemento de m1
	lw $s1, 0($t1) # $s1, Primeiro elemento de m2
	lw $s2, 0($t2) # $s2, Primeiro elemento de m3
	lw $s3, 0($t3) # $s3, Largura das matrizes
	
	addi $t4, $zero, 0 # $t4, contadorColuna = 0
	addi $t5, $zero, 1 # $t5, contadorLinha = 1, ex: 3 linhas, 2 quebras de linha
	
	jal sum_mat # Chamada de funcao
	
	# Termino do programa
	li $v0, 10 # Codigo para terminar o programa = 10
	syscall
	
sum_mat:
	beq $t4, $s3, line # Se fim da coluna, vai para a proxima linha
	
	lw $s4, 0($t0) # $s4, valor atual de m1
	lw $s5, 0($t1) # $s5, valor atual de m2
	lw $s6, 0($t2) # $s6, valor atual de m3
	
	add $s6, $s4, $s5 # $s6, soma dos valores atuais de m1 e m2
	
	# Impressao do valor atual de m3
	addi $v0, $zero, 1 # Codigo para imprimir um inteiro
	add $a0, $zero, $s6 # Carrega o valor atual para impressao
	syscall	
	
	addi $t0, $t0, 4 # Passa para o proximo elemento de m1
	addi $t1, $t1, 4 # Passa para o proximo elemento de m2
	addi $t2, $t2, 4 # Passa para o proximo elemento de m3
			
	addi $t4, $t4, 1 # contadorColuna++;	
		
	j sum_mat
	
line:
	beq $t5, $s3, fim # Se fim das linhas, contadorLinha == lado, termina lasso
	
	# Pula uma linha
	addi $v0, $zero, 4 # Codigo para imprimir uma string = 4
	la $a0, novaLinha # Carregando a string msg para o argumento
	syscall
	
	addi $t5, $t5, 1 # contadorLinha++;
	
	add $t4, $zero, $zero # contadorColuna = 0;
	
	j sum_mat
	
fim:
	addi $v0, $zero, 4 # Codigo para imprimir uma string = 4
	la $a0, msg # Carregando a string msg para o argumento
	syscall
	
	# Pula para instrucao apos a chamada de funcao 
	jr $ra
