.data

x:	.word 33
msg:	.asciiz "O valor eh: "
msg2:	.asciiz "\nO dobro eh: "

.text

	# O valor eh
	addi $v0, $zero, 4 # Codigo para imprimir uma string = 4
	la $a0, msg # Carregando a string msg para o argumento
	syscall 
	
	# x	
	la $t0, x # Carregando o x para o registrador $t0
	addi $v0, $zero, 1 # Codigo para imprimir um inteiro = 1
	lw $a0, 0($t0) # Carregando o valor de x para o argumento
	syscall
	
	# Multiplicando por 2
	sll $t1, $a0, 1 # Multiplicacao por 2
	sw $t1, 0($t0) # Resultado da multiplicacao
	
	# O dobro eh
	addi $v0, $zero, 4 # Codigo para imprimir uma string = 4
	la $a0, msg2 # Carregando a string msg2 para o argumento
	syscall 
	
	# 2*x
	addi $v0, $zero, 1 # Codigo para imprimir um inteiro = 1
	lw $a0, 0($t0) # Carregando o valor de 2*x para o argumento
	syscall
	
	# Termino do programa
	addi $v0, $zero, 10 # Codigo para terminar o programa = 10
	syscall 
	
