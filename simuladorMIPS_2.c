#include "simuladorMIPS_2_funcoes.c"

int main(){
    FILE *arquivoData;
    FILE *arquivoText;

    uint32_t endereco = 0;
    int indice = 0;

    /* Inicializando a memoria com 0 */
    for(endereco = 0; endereco < MEM_SIZE; endereco++){
        mem[endereco] = 0;
    }

    /* Inicializando os registradores com 0 */
    for(indice = 0; indice < 32; indice++){
        reg[indice] = 0;
    }

    /* Abrindo o arquivo de dados */
    arquivoData = fopen("data_fibonacci.bin", "rb");
    if(arquivoData == NULL){
        perror("Erro ao abrir o arquivo de dados");
        exit(-1);
    }

    /* Abrindo o arquivo de instruções */
    arquivoText = fopen("text_fibonacci.bin", "rb");
    if(arquivoText == NULL){
        perror("Erro ao abrir o arquivo de instruções");
        exit(-1);
    }

    /* 0x20082000 => 0020 0820 => 2000 2008 => 0x20082000 */

    /* Carrega o arquivo data.bin na memoria */
    loadData(arquivoData);

    /* Carrega o arquivo text.bin na memoria */
    loadText(arquivoText);

    menu();

    fclose(arquivoData);
    fclose(arquivoText);

    return 0;
}
