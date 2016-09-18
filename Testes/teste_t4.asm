.data

.text
	addi $s0, $s0, -1
	addi $s1, $s1, -4096
	
	and $t0, $s0, $s1
	
	or $t1, $s0, $s1
	
	xor $t2, $s0, $s1
	
	nor $t3, $s0, $s1
	
	slt $t4, $s1, $s0
	
	# Termino do programa
	li $v0, 10 # Codigo para terminar o programa = 10
	syscall
	