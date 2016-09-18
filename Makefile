default: compilar

compilar:
		gcc -o simuladorMIPS_2.out simuladorMIPS_2.c

rodar:
		./simuladorMIPS_2.out

limpar:
		rm *.out
