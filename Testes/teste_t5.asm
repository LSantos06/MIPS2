.data

.text
	addi $s0, $s0, -1
	addi $s1, $s1, -4096
	
	sll $t0, $s0, 8
	
	srl $t1, $s0, 8
	
	sra $t2, $s0, 8
	
	div $s0, $s1
	
	mfhi $t3
	
	mult $s1, $s0
	
	mflo $t4
	
	# Termino do programa
	li $v0, 10 # Codigo para terminar o programa = 10
	syscall
	