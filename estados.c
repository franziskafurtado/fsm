#include "estados.h"

unsigned char estados(unsigned short entrada){
    char estado = (char) entrada&0x0F;
    char sensorfim = (char) ((entrada&0x10)>>4);
    char sensorbug = (char) ((entrada&0x20)>>5);
    char sensorfeature = (char) ((entrada&0x40)>>6);
    char botaoinicio = (char) ((entrada&0x80)>>7);
    char tempo = (char) ((entrada&0x100)>>8);
    char clockend = (char) ((entrada&0x200)>>9);

    unsigned char saida = 0;
    if(estado==INIT){
        if(botaoinicio){
            saida += COMECOUDIR;
        }
        else{
            saida += INIT;
        }
    }
    else if(estado==COMECOUDIR){
        saida += DIRECAOMOTORDIR;
        if(clockend){
            saida += PERDEU;
        }
        else if(sensorbug){
            saida += UMPONTO;
        }
        else if(sensorfim){
            saida +=COMECOUESQ;
        }
        else{
            saida +=COMECOUDIR;
        }
    }

    else if(estado==COMECOUESQ){
        saida += DIRECAOMOTORESQ;
        if(clockend){
            saida += PERDEU;
        }
        if(sensorbug){
            saida += UMPONTO;
        }
        if(sensorfim){
            saida +=COMECOUDIR;
        }
        else{
            saida +=COMECOUESQ;
        }
    }

    else if(estado==UMPONTO){
        saida += BUZZER;
        if(tempo){
            saida += SEGUNDARODADADIR;
        }
        else{
            saida +=UMPONTO;
        }
    }

    else if(estado==SEGUNDARODADADIR){
        saida += DIRECAOMOTORDIR;
        if(clockend){
            saida += PERDEU;
          }
        else if(sensorbug){
            saida += DOISPONTOS;
        }
        else if(sensorfim){
            saida +=SEGUNDARODADAESQ;
        }
        else if(sensorfeature){
            saida+=COMECOUDIR;
        }
        else{
            saida +=SEGUNDARODADADIR;
        }
    }

    else if(estado==SEGUNDARODADAESQ){
        saida += DIRECAOMOTORESQ;
        if(clockend){
            saida += PERDEU;
        }
        else if(sensorbug){
            saida += DOISPONTOS;
        }
        else if (sensorfeature) {
            saida +=COMECOUDIR;
        }
        else if(sensorfim){
            saida +=SEGUNDARODADADIR;
        }
        else{
            saida +=SEGUNDARODADAESQ;
        }
      }

        else if(estado==DOISPONTOS){
            saida += BUZZER;
            if(tempo){
                saida += TERCEIRARODADADIR;
            }
            else{
                saida +=DOISPONTOS;
            }
          }

            else if(estado==TERCEIRARODADADIR){
                saida += DIRECAOMOTORDIR;
                saida += VELOCIDADE;
                if(clockend){
                    saida += PERDEU;
                }
                else if(sensorbug){
                    saida += GANHOU;
                  }
                else if(sensorfim){
                    saida +=TERCEIRARODADAESQ;
                }
                else if(sensorfeature){
                    saida +=COMECOUDIR;
                }
                else{
                    saida +=TERCEIRARODADADIR;
                }
            }

            else if(estado==TERCEIRARODADAESQ){
                saida += DIRECAOMOTORESQ;
                saida += VELOCIDADE;
                if(clockend){
                    saida += PERDEU;
                }
                else if(sensorbug){
                    saida += GANHOU;
                }
                else if(sensorfim){
                    saida +=TERCEIRARODADADIR;
                }
                else if(sensorfeature){
                    saida +=COMECOUDIR;
                }
                else{
                    saida +=TERCEIRARODADAESQ;
                }
              }

              else if (estado==GANHOU){
                saida +=BUZZER;
                if(tempo){
                  saida+=INIT;
                }
                else{
                    saida+=GANHOU;
                }
              }

              else if (estado==PERDEU){
                if(tempo){
                  saida+=INIT;
                }
                else{
                    saida+=PERDEU;
                }
              }
              return(saida);
}
