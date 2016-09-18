# MIPS2
##Trabalho 2 de Organizacão e Arquitetura de Computadores

O trabalho consiste na elaboração de um simulador da arquitetura MIPS, como o *MARS*, em uma linguagem de alto nivel. O simulador deve implementar as seguintes funções: **fetch()**, busca da instrução; **decode()**, decodificação da instrução; **execute()**, execução da instrução. O programa binário a ser executado deve ser gerado a partir do MIPS. O simulador implementado deve ler os arquivos binarios contendo as instruções e os dados para sua memória e executá-lo.

##Compilação utilizando o *Makefile*
  - **make**: compilação do simulador, simuladorMIPS_2.c;
  - **make rodar**: executa o simulador, simuladorMIPS_2.out;
  - **make limpar**: remove os arquivos .out;

##Instruções
  - Bibliotecas utilizadas: stdio.h, stdlib.h e inttypes.h;
  - Compilador utilizado: GCC 4.6.3;
  - Sistema Operacional: elementary OS 0.2.1 "Luna" (64-bit), criado em Ubuntu 12.04 ("Precise");
  - IDE: NULL;
