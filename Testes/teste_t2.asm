.data

.text
	addi $t0, $t0, 2000
	addi $s0, $s0, 16
	
	slti $t1, $t0, -1
	
	sltiu $t2, $t0, -1
	
	andi $t3, $t0, 20
	
	ori $t4, $s0, 8
	
	xori $t5, $s0, 8
	
	# Termino do programa
	li $v0, 10 # Codigo para terminar o programa = 10
	syscall
	