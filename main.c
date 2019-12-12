#include <stdio.h>
#include <stdlib.h>
#include "estados.h"

int main(){

    int j;
    unsigned int i, checksumaux;
    unsigned char saida, checksum;
    FILE* arquivo;
    FILE* logisim;
    arquivo = fopen("fed.hex","wb");
    logisim = fopen("logisim.txt","wb");
    fprintf(logisim,"v2.0 raw\n");
    for(i=0;i<=0x1fff;i++){
        saida = estados((unsigned short)i);
        /*teste = saida;
        for(j=0;j<8;j++){
            if(teste&0x80){
                printf("1");
            }
            else{
                printf("0");
            }
            teste = teste<<1;
        }
        printf("\n");*/
        checksumaux = 0;
        checksumaux = 0x01 + (i&0xff)+((i>>8)&0xff)+00+saida;
        checksumaux = checksumaux&0xff;
        checksum = 0;
        for(j=0;j<8;j++){
            if(!(checksumaux&0x80)){
                checksum++;
            }
            if(j!=7){
                checksumaux = checksumaux << 1;
                checksum = checksum << 1;
            }
        }
        checksum++;
        fprintf(arquivo,":01%04X00%02X%02X\n",i,saida,checksum);
        fprintf(logisim,"%02X\n",saida);
    }
    fprintf(arquivo,":00000001FF");
    fclose(arquivo);
    fclose(logisim);
    return 0;
}
