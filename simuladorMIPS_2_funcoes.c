#include "simuladorMIPS_2_funcoes.h"

/* Memoria */
/* Carrega o arquivo data.bin na memoria */
void loadData(FILE *ponteiroArquivo){
    /* Inicia no 0x00002000, 2048 em decimal */
    uint32_t endereco = 2048;

    /* Percorre o arquivo e armazena na memoria */
    while(!feof(ponteiroArquivo)){
        fread(&mem[endereco], sizeof(int32_t), 1, ponteiroArquivo);
        endereco++;
    }
}

/* Carrega o arquivo text.bin na memoria */
void loadText(FILE * ponteiroArquivo){
    /* Inicia no 0x00000000, 0 em decimal */
    uint32_t endereco = 0;

    /* Percorre o arquivo e armazena na memoria */
    while(!feof(ponteiroArquivo)){
        fread(&mem[endereco], sizeof(int32_t), 1, ponteiroArquivo);
        endereco++;
    }
}
/******************************************************************************/

/* Leitura */
/* Lê um inteiro alinhado - endereços múltiplos de 4 */
int32_t lw(uint32_t endereco, int16_t deslocamento){

    if(endereco % 4 != 0 || deslocamento % 4 != 0){
        printf("lw: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 4), erro:\n");
        return -2;
    }

    /* Retorna o valor armazenado no endereco + deslocamento */
    return mem[(endereco + deslocamento)/4];
}

/* Lê meia palavra, 16 bits - retorna inteiro com sinal */
int32_t lh(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco, anterior;
    int32_t bitMaisSiginificativo[1];
    int32_t bitMaisSiginificativoAnterior;

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("lh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2), erro:\n");
        return -2;
    }

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Obtendo os bits mais significativos */
    bitMaisSiginificativo[0] = mem[novoEndereco] & 0x0000f000;
    bitMaisSiginificativo[1] = mem[novoEndereco] & 0xf0000000;

    /* Obtendo o endereco anterior para deslocamentos negativos */
    anterior = novoEndereco - 1;

    /* Obtendo o bit mais significativo do anterior */
    bitMaisSiginificativoAnterior = mem[anterior] & 0xf0000000;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        /* Se a meia palavra negativa */
        if(bitMaisSiginificativo[0] >= 0x00008000){
            return (mem[novoEndereco] | 0xffff0000);
        }
        /* Se a meia palavra for positiva */
        return (mem[novoEndereco] & 0x0000ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        /* Se a meia palavra negativa */
        if(bitMaisSiginificativo[1] >= 0x80000000){
            return ((mem[novoEndereco] >> 16) | 0xffff0000);
        }
        /* Se a meia palavra for positiva */
        return ((mem[novoEndereco] >> 16) & 0x0000ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for- 2 */
    if(resto == -2){
        /* Se a meia palavra negativa */
        if(bitMaisSiginificativoAnterior >= 0x80000000){
            return ((mem[anterior]  >> 16) | 0xffff0000);
        }
        /* Se a meia palavra for positiva */
        return ((mem[anterior]  >> 16) & 0x0000ffff);
    }
}

/* Lê um byte - retorna inteiro com sinal */
int32_t lb(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco, anterior;
    int32_t bitMaisSiginificativo[3];
    int32_t bitMaisSiginificativoAnterior[2];

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Obtendo os bits mais significativos */
    bitMaisSiginificativo[0] = mem[novoEndereco] & 0x000000f0;
    bitMaisSiginificativo[1] = mem[novoEndereco] & 0x0000f000;
    bitMaisSiginificativo[2] = mem[novoEndereco] & 0x00f00000;
    bitMaisSiginificativo[3] = mem[novoEndereco] & 0xf0000000;

    /* Obtendo o endereco anterior para deslocamentos negativos */
    anterior = novoEndereco - 1;

    /* Obtendo o bit mais significativo do anterior */
    bitMaisSiginificativoAnterior[0] = mem[anterior] & 0xf0000000;
    bitMaisSiginificativoAnterior[1] = mem[anterior] & 0x00f00000;
    bitMaisSiginificativoAnterior[2] = mem[anterior] & 0x0000f000;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        /* Se o byte for negativo */
        if(bitMaisSiginificativo[0] >= 0x00000080){
            return (mem[novoEndereco] | 0xffffff00);
        }
        /* Se o byte for positivo */
        return (mem[novoEndereco] & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 1 */
    if(resto == 1){
        /* Se o byte for negativo */
        if(bitMaisSiginificativo[1] >= 0x00008000){
            return ((mem[novoEndereco] >> 8) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem[novoEndereco] >> 8) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -1 */
    if(resto == -1){
        /* Se o byte for negativo */
        if(bitMaisSiginificativoAnterior[0] >= 0x80000000){
            return ((mem[anterior] >> 24) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem[anterior] >> 24) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        /* Se o byte for negativo */
        if(bitMaisSiginificativo[2] >= 0x00800000){
            return ((mem[novoEndereco] >> 16) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem[novoEndereco] >> 16) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -2 */
    if(resto == -2){
        /* Se o byte for negativo */
        if(bitMaisSiginificativoAnterior[1] >= 0x00800000){
            return ((mem[anterior] >> 16) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem[anterior] >> 16) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == 3){
        /* Se o byte for negativo */
        if(bitMaisSiginificativo[3] >= 0x80000000){
            return ((mem[novoEndereco] >> 24) | 0xffffff00);
        }
        return ((mem[novoEndereco] >> 24) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -3 */
    if(resto == -3){
        /* Se o byte for negativo */
        if(bitMaisSiginificativoAnterior[2] >= 0x00008000){
            return ((mem[anterior] >> 8) | 0xffffff00);
        }
        return ((mem[anterior] >> 8) & 0x000000ff);
    }
}

/* Lê meia palavra, 16 bits - retorna inteiro sem sinal */
int32_t lhu(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco;

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("lh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2), erro:\n");
        return -2;
    }

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        return (mem[novoEndereco] & 0x0000ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        return ((mem[novoEndereco] >> 16) & 0x0000ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -2 */
    if(resto == -2){
        return ((mem[novoEndereco-1] >> 16) & 0x0000ffff);
    }
}

/* Lê um byte - retorna inteiro sem sinal */
int32_t lbu(uint32_t endereco, int16_t deslocamento){
    int16_t palavras, resto;
    int32_t novoEndereco;

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        return (mem[novoEndereco] & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 1 */
    if(resto == 1){
        return ((mem[novoEndereco] >> 8) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -1 */
    if(resto == -1){
        return ((mem[novoEndereco-1] >> 24) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        return ((mem[novoEndereco] >> 16) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == -2){
        return ((mem[novoEndereco-1] >> 16) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == 3){
        return ((mem[novoEndereco] >> 24) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == -3){
        return ((mem[novoEndereco-1] >> 8) & 0x000000ff);
    }
}
/******************************************************************************/

/* Escrita */
/* Escreve um inteiro alinhado na memória - endereços múltiplos de 4 */
void sw(uint32_t endereco, int16_t deslocamento, int32_t dado){

    if(endereco % 4 != 0 || deslocamento % 4 != 0){
        printf("sw: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 4)\n");
        return;
    }

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Armazena o valor do dado no endereco */
    mem[endereco + (deslocamento/4)] = dado;
}

/* Escreve meia palavra, 16 bits - endereços múltiplos de 2 */
void sh(uint32_t endereco, int16_t deslocamento, int16_t dado){
    int16_t palavras, resto;
    int32_t novoEndereco, anterior;

    if(endereco % 4 != 0 || deslocamento % 2 != 0){
        printf("sh: Endereco (Não é multíplo de 4) ou Deslocamento (Não é multíplo de 2)\n");
        return;
    }

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Obtendo o endereco anterior para deslocamentos negativos */
    anterior = novoEndereco - 1;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        mem[novoEndereco] = (dado & 0x0000ffff) | (mem[novoEndereco] & 0xffff0000);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        /* 16 bits = 2 bytes */
        mem[novoEndereco] = ((dado & 0x0000ffff) << 16) | (mem[novoEndereco] & 0x0000ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -2 */
    if(resto == -2){
        /* 16 bits = 2 bytes */
        mem[anterior] = ((dado & 0x0000ffff) << 16) | (mem[anterior] & 0x0000ffff);
    }
}

/* Escreve um byte na memória */
void sb(uint32_t endereco, int16_t deslocamento, int8_t dado){
    int16_t palavras, resto;
    int32_t novoEndereco, anterior;

    /* Endereco em indices da memoria */
    endereco = endereco / 4;

    /* Numero de palavras que vao ser deslocadas */
    palavras = deslocamento / 4;

    /* Novo endereco de acordo com o o numero de palavras q serao deslocadas */
    novoEndereco = endereco + palavras;

    /* Numero de bytes que vao ser deslocados dentro do endereco */
    resto = deslocamento % 4;

    /* Obtendo o endereco anterior para deslocamentos negativos */
    anterior = novoEndereco - 1;

    /* Se o numero de bytes deslocados dentro do endereco for 0 */
    if(resto == 0){
        mem[novoEndereco] = (dado & 0x000000ff) | (mem[novoEndereco] & 0xffffff00);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 1 */
    if(resto == 1){
        mem[novoEndereco] = ((dado & 0x000000ff) << 8) | (mem[novoEndereco] & 0xffff00ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -1 */
    if(resto == -1){
        mem[anterior] = ((dado & 0x000000ff) << 24) | (mem[anterior] & 0x00ffffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        mem[novoEndereco] = ((dado & 0x000000ff) << 16) | (mem[novoEndereco] & 0xff00ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == -2){
        mem[anterior] = ((dado & 0x000000ff) << 16) | (mem[anterior] & 0xff00ffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == 3){
        mem[novoEndereco] = ((dado & 0x000000ff) << 24) | (mem[novoEndereco] & 0x00ffffff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == -3){
        mem[anterior] = ((dado & 0x000000ff) << 8) | (mem[anterior] & 0xffff00ff);
    }
}

/******************************************************************************/
/* Menu */
/* Menu de interação com o usuário */
void menu (){
    int escolha = 0;
    uint32_t endereco = 0;
    uint32_t inicio, fim;
    char formato;

    do{
        printf("\n\n/**************SIMULADOR ASSEMBLER MIPS**************/\n\n");
        printf("(1) - Dump Memory\n");
        printf("(2) - Dump All Memory\n");
        printf("(3) - Step by Step\n");
        printf("(4) - Dump Registers\n");
        printf("(5) - Run\n");
        printf("(0) - Exit\n");
        printf("------------------------------------------------------\n");

        printf("Digite um valor correspondente a um opcao no menu: ");
        scanf("%d", &escolha);

        /* Dump Memory */
        if(escolha == 1){
            printf("\n");

            printf("\nDigite o endereco inicial em hexadecimal: ");
            scanf("%" SCNd32, &inicio);

            printf("\nDigite o endereco final em hexadecimal: ");
            scanf("%" SCNd32, &fim);

            getchar();
            printf("\nDigite o formato da exibicao: ");
            scanf("%c", &formato);

            dump_mem((inicio/4), (fim/4), formato);
        }

        /* Dump All Memory */
        else if(escolha == 2){
            printf("\n");

            for(endereco = 0; endereco < MEM_SIZE; endereco++){
                if(mem[endereco] != 0){
                    printf("Address [0x%.8x] = 0x%.8x\n", endereco*4, mem[endereco]);
                }
            }
        }

        /* Step by Step */
        else if(escolha == 3){
            printf("\nDump Step:");

            printf("\nSaida no terminal = ");
            step();

            printf("\nInstrução atual = 0x%.8x\n", ri);
            printf("opcode = 0x%.8x\n", opcode);
            printf("rs = 0x%.8x\n", rs);
            printf("rt = 0x%.8x\n", rt);
            printf("rd = 0x%.8x\n", rd);
            printf("shamt = 0x%.8x\n", shamt);
            printf("funct = 0x%.8x\n", funct);
            printf("k16 = 0x%.8x\n", k16);
            printf("k26 = 0x%.8x\n", k26);

            dump_reg('x');
        }

        /* Dump Registers */
        else if(escolha == 4){
            getchar();
            printf("\nDigite o formato da exibicao: ");
            scanf("%c", &formato);

            dump_reg(formato);
        }

        /* Run */
        else if(escolha == 5){
            pc = 0;
            run();
        }

    }while(escolha != 0);

}

/* Funcoes */
/* Lê uma instrucao da memoria e coloca-a em ri, atualizando o pc para apontar para a proxima instrucao (+4) */
void fetch(uint32_t endereco){
    /* Armazena a instrucao no ri */
    ri = mem[endereco];
    /* Endereco da proxima instrucao */
    pc = endereco + 1;
}

/* Extrai os campos da instrucao */
void decode(){
    /* instrucao = ri */

    /* OPCODE */
    /* Obtem os 6 bits em que o opcode se encontra */
    opcode = ri >> 26;
    // printf("opcode = 0x%.8x\n", opcode);

    /* RS */
    /* Anula o valor dos 6 bits mais significativos */
    rs = ri << 6;
    /* Obtem os 5 bits em que rs se encontra */
    rs = rs >> 27;
    // printf("rs = 0x%.8x\n", rs);

    /* RT */
    /* Anula o valor dos 11 bits mais significativos */
    rt = ri << 11;
    /* Obtem os 5 bits em que rt se encontra */
    rt = rt >> 27;
    // printf("rt = 0x%.8x\n", rt);

    /* RD */
    /* Anula o valor dos 16 bits mais significativos */
    rd = ri << 16;
    /* Obtem os 5 bits em que rd se encontra */
    rd = rd >> 27;
    // printf("rd = 0x%.8x\n", rd);

    /* SHAMT */
    /* Anula o valor dos 21 bits mais significativos */
    shamt = ri << 21;
    /* Obtem os 5 bits em que shamt se encontra */
    shamt = shamt >> 27;
    // printf("shamt = 0x%.8x\n", shamt);

    /* FUNCT */
    /* Anula o valor dos 26 bits mais significativos */
    funct = ri << 26;
    /* Obtem os 6 bits em que funct se encontra */
    funct = funct >> 26;
    // printf("funct = 0x%.8x\n", funct);

    /* k16 */
    /* Anula o valor dos 16 bits mais significativos */
    k16 = ri << 16;
    /* Obtem os 16 bits em que k16 se encontra */
    k16 = k16 >> 16;
    // printf("k16 = 0x%.8x\n", k16);

    /* k16 */
    /* Anula o valor dos 6 bits mais significativos */
    k26 = ri << 6;
    /* Obtem os 26 bits em que k26 se encontra */
    k26 = k26 >> 6;
    // printf("k26 = 0x%.8x\n", k26);

}

/* Executa a instrucao que foi lida pala funcao fetch() e decodificada pela funcao decode() */
void execute(){
    /* instrucao = ri */

    /* Tipo I */
    /* opcode,rs,rt,k16(immediate) */

    /* Tipo J */
    /* opcode,k26(address) */

    /* Tipo R */
    /* opcode,rs,rt,rd,shamt,funct */

    /*********************************************************/
    /* Instrucoes do Tipo I */

    if(opcode == LW){
        /* Load Word */
        reg[rt] = lw(reg[rs], k16);
    }

    if(opcode == LB){
        /* Load Byte */
        reg[rt] = lb(reg[rs], k16);
    }

    if(opcode == LBU){
        /* Load Byte Unsigned */
        reg[rt] = lbu(reg[rs], k16);
    }

    if(opcode == LH){
        /* Load Halfword */
        reg[rt] = lh(reg[rs], k16);
    }

    if(opcode == LHU){
        /* Load Halfword Unsigned */
        reg[rt] = lhu(reg[rs], k16);
    }

    if(opcode ==  LUI){
        /* Load upper immediate */
        reg[rt] = k16 << 16;
    }

    if(opcode == SW){
        /* Store Word */
        sw(reg[rs],k16,reg[rt]);
    }

    if(opcode == SB){
        /* Store Byte */
        sb(reg[rs],k16,reg[rt]);
    }

    if(opcode == SH){
        /* Store Halfword */
        sh(reg[rs],k16,reg[rt]);
    }

    if(opcode == BEQ){
        /* Branch On Equal */

        /* k16 = deslocamento de endereco */
        if(reg[rs] == reg[rt]){
            pc = pc + k16;
        }
    }

    if(opcode == BNE){
        /* Branch On Not Equal */

        /* k16 = deslocamento de endereco */
        if(reg[rs] != reg[rt]){
            pc = pc + k16;
        }
    }

    if(opcode == BLEZ){
        /* Branch On Less Than Equal To Zero */

        /* k16 = deslocamento de endereco */
        if(reg[rs] <= 0){
            pc = pc + k16;
        }
    }

    if(opcode == BGTZ){
        /* Branch On Greater Than Zero */

        /* k16 = deslocamento de endereco */
        if(reg[rs] > 0){
            pc = pc + k16;
        }
    }

    if(opcode == ADDI){
        /* Add Immediate */
        reg[rt] = reg[rs] + k16;
    }

    if(opcode == SLTI){
        /* Set Less Than Immediate */
        reg[rt] = (reg[rs] < k16) ? 1 : 0;
    }

    if(opcode == SLTIU){
        /* Set Less Than Immediate Unsigned */
        reg[rt] = (reg[rs] < (uint32_t)k16) ? 1 : 0;
    }

    if(opcode == ANDI){
        /* And Immediate */
        reg[rd] = reg[rs] & k16;
    }

    if(opcode == ORI){
        /* Or Immediate */
        reg[rt] = reg[rs] | k16;
    }

    if(opcode == XORI){
        /* Xor Immediate */
        reg[rt] = reg[rs] ^ k16;
    }

    /* ADDIU implementado, pois o MIPS interpreta alguns ADDI como ADDIU */
    if(opcode == ADDIU){
        /* Add Immediate Unsigned */
        reg[rt] = reg[rs] + k16;
    }

    /*********************************************************/

    if(opcode == J){
        /* Jump */

        /* Endereco de pulo */
        pc = k26;
    }

    if(opcode == JAL){
        /* Jump And Link */

        /* Endereco da proxima instrucao */
        /* reg[31] = ra */
        reg[31] = pc;
        /* Endereco de pulo */
        pc = k26;
    }

    /*********************************************************/
    /* Instrucoes do Tipo R */
    if(opcode == EXT){

        if(funct == ADD){
            /* Add */
            reg[rd] = reg[rs] + reg[rt];
        }

        if(funct == SUB){
            /* Sub */
            reg[rd] = reg[rs] - reg[rt];
        }

        if(funct == MULT){
            /* Mult */
            int64_t temporario;

            /* Variavel auxiliar para armazenar a multiplicacao */
            temporario = reg[rs] * reg[rt];

            /* Armazenando o resultado nos registradores hi e lo */
            hi = (temporario & 0x1111111100000000) >> 32;
            lo = temporario & 0x0000000011111111;
        }

        if(funct == DIV){
            /* Div */
            lo = reg[rs] / reg[rt];
            hi = reg[rs] % reg[rt];
        }

        if(funct == AND){
            /* And */
            reg[rd] = reg[rs] & reg[rt];
        }

        if(funct == OR){
            /* Or */
            reg[rd] = reg[rs] | reg[rt];
        }

        if(funct == XOR){
            /* Or */
            reg[rd] = reg[rs] ^ reg[rt];
        }

        if(funct == NOR){
            /* Nor */
            reg[rd] = ~(reg[rs] | reg[rt]);
        }

        if (funct == SLT){
            /* Set Less Than */
            reg[rd] = (reg[rs] < reg[rt]) ? 1 : 0;
        }

        if(funct == JR){
            /* Jump Register */

            /* Pula para o registrador rs */
            pc = reg[rs];
        }

        if(funct == SLL){
            /* Shift Left Logical */
            reg[rd] = reg[rt] << shamt;
        }

        if(funct == SRL){
            /* Shift Right Logical */
            reg[rd] = (uint32_t)reg[rt] >> shamt;
        }

        if(funct == SRA){
            /* Shift Right Arithimetic */

            /* Suporta numeros em complemento de 2 */
            reg[rd] = reg[rt] >> shamt;
        }

        if(funct == SYSCALL){
            /* System Call */

            /* reg[2] = v0 */
            /* reg[4] = a0 */
            if(reg[2] == 1){
                printf("%d", reg[4]);
            }

            if(reg[2] == 4){
                /* Endereco em indices do vetor */
                uint32_t endereco = reg[4]/4;

                char *caracter;

                /* Ponteiro auxiliar aponta para o endereco que contem a string */
                caracter = (char *)&(mem[endereco]);

                /* Deslocamento feito dentro do endereco */
                caracter += reg[4] % 4;

                /* Enquando nao encontrar o fim de uma string */
                do{
                    printf("%c", *caracter);
                    caracter++;
                }while(*caracter != '\0');
            }

            /* Syscall para encerrar o programa */
            if(reg[2] == 10){
                printf("\n-- program is finished running --\n");

                dump_reg('x');

                exit(EXIT_SUCCESS);
            }

        }

        if(funct == MFHI){
            /* Move From High */
            reg[rd] = hi;
        }

        if(funct == MFLO){
            /* Move From Low */
            reg[rd] = lo;
        }

    }
}

/* fetch(), decode(), execute() */
void step(){

    fetch(pc);
    decode();
    execute();

}

/* Executa o programa ate a chamada de encerramento ou o pc chegar ao fim da memoria */
void run(){
    uint32_t indice = 0;

    while(indice < MEM_SIZE){
        /* O valor do reg[0] sempre eh 0 */
        reg[0] = 0;

        step();
        indice++;

        // dump_reg('x');
        // getchar();
    }
}

/* Imprime o conteudo da memoria do start ate end, em hexa ou decimal */
void dump_mem(uint32_t start, uint32_t end, char format){
    uint32_t indice;

    printf("\nDump Memory:\n");
    for(indice = start; indice <= end; indice++){
        if(format == 'd'){
            printf("Address [0x%.8x] = %d\n", indice*4, mem[indice]);
        }

        else{
            printf("Address [0x%.8x] = 0x%.8x\n", indice*4, mem[indice]);
        }
    }
}

/* Imprime o conteudo dos registradores do MIPS, o banco de registradores e pc, hi e lo, em hexa ou decimal */
void dump_reg(char format){
      uint32_t indice;

    if(format == 'd'){
        printf("\nDump Registers:\n");

        for(indice = 0; indice < 32; indice++){
            printf("reg[%d] = %d\n", indice, reg[indice]);
        }

        printf("pc = %d\n", pc);
        printf("hi = %d\n", hi);
        printf("lo = %d\n", lo);
        // printf("Instrução atual = %d\n", ri);
    }

    else{
        printf("\nDump Registers:\n");

        for(indice = 0; indice < 32; indice++){
            printf("reg[%d] = 0x%.8x\n", indice, reg[indice]);
        }

        printf("pc = 0x%.8x\n", pc);
        printf("hi = 0x%.8x\n", hi);
        printf("lo = 0x%.8x\n", lo);
        // printf("Instrução atual = 0x%.8x\n", ri);
    }
}
