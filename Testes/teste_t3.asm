.data

.text
	addi $s0, $s0, 16
	addi $s1, $s1, 48
	
	add $t0, $s0, $s1
	
	sub $t1, $s0, $s1
	
	mult $s0, $s1
		
	div $s1, $s0
	
	# Termino do programa
	li $v0, 10 # Codigo para terminar o programa = 10
	syscall
	