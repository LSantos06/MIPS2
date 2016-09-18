#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MEM_SIZE 4096

/* Registradores */
uint32_t pc;
uint32_t ri;
int32_t hi;
int32_t lo;

/* Banco de Registradores */
int32_t reg[32];

/* Campos da instrucao */
uint32_t opcode;
uint32_t rs;
uint32_t rt;
uint32_t rd;
uint32_t shamt;
uint32_t funct;
int32_t k16; /* Imediato */
uint32_t k26; /* Endereco */
/******************************************************************************/

/* Instrucoes - Sao considerados os 6 primeiros bits dessa constantes */
enum OPCODES {
  EXT=0x00,     LW=0x23,      LB=0x20,      LBU=0x24,       ADDIU=0x09,
  LH=0x21,      LHU=0x25,     LUI=0x0F,     SW=0x2B,
  SB=0x28,      SH=0x29,      BEQ=0x04,     BNE=0x05,
  BLEZ=0x06,    BGTZ=0x07,    ADDI=0x08,    SLTI=0x0A,
  SLTIU=0x0B,   ANDI=0x0C,    ORI=0x0D,     XORI=0x0E,
  J=0x02,       JAL=0x03
};

enum FUNCT {
  ADD=0x20,     SUB=0x22,     MULT=0x18,    DIV=0x1A,         AND=0x24,
  OR=0x25,      XOR=0x26,     NOR=0x27,     SLT=0x2A,         JR=0x08,
  SLL=0x00,     SRL=0x02,     SRA=0x03,     SYSCALL=0x0c,     MFHI=0x10,  MFLO=0x12
};
/******************************************************************************/

/* Memoria */
int32_t mem[MEM_SIZE];

/* Carrega o arquivo data.bin na memoria */
void loadData(FILE *ponteiroArquivo);

/* Carrega o arquivo text.bin na memoria */
void loadText(FILE *ponteiroArquivo);
/******************************************************************************/

/* Leitura */
/* Lê um inteiro alinhado - endereços múltiplos de 4 */
int32_t lw(uint32_t endereco, int16_t deslocamento);

/* Lê meia palavra, 16 bits - retorna inteiro com sinal */
int32_t lh(uint32_t endereco, int16_t deslocamento);

/* Lê um byte - retorna inteiro com sinal */
int32_t lb(uint32_t endereco, int16_t deslocamento);

/* Lê meia palavra, 16 bits - retorna inteiro sem sinal */
int32_t lhu(uint32_t endereco, int16_t deslocamento);

/* Lê um byte - retorna inteiro sem sinal */
int32_t lbu(uint32_t endereco, int16_t deslocamento);
/******************************************************************************/

/* Escrita */
/* Escreve um inteiro alinhado na memória - endereços múltiplos de 4 */
void sw(uint32_t endereco, int16_t deslocamento, int32_t dado);

/* Escreve meia palavra, 16 bits - endereços múltiplos de 2 */
void sh(uint32_t endereco, int16_t deslocamento, int16_t dado);

/* Escreve um byte na memória */
void sb(uint32_t endereco, int16_t deslocamento, int8_t dado);
/******************************************************************************/

/* Menu */
/* Menu de interação com o usuário */
void menu ();
/******************************************************************************/

/* Funcoes */
/* Lê uma instrucao da memoria e coloca-a em ri, atualizando o pc para apontar para a proxima instrucao (+4)*/
void fetch(uint32_t instrucao);

/* Extrai os campos da instrucao */
void decode();

/* Executa a instrucao que foi lida pala funcao fetch() e decodificada pela funcao decode()*/
void execute();

/* fetch(), decode(), execute() */
void step();

/* Executa o programa ate a chamada de encerramento ou o pc chegar ao fim da memoria */
void run();

/* Imprime o conteudo da memoria do start ate end, em hexa ou decimal*/
void dump_mem(uint32_t start, uint32_t end, char format);

/* Imprime o conteudo dos registradores do MIPS, o banco de registradores e pc, hi e lo, em hexa ou decimal */
void dump_reg(char format);
