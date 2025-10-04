/*****************************************************************
** Pratica 05                                                   **
**                                                              **
** Exemplo para utilizacao dos displays de 7 segmentos          **
** presente no kit PIC 18F452. usando os 4 displays foi         **
** feito um timer ajustavel, que ao fim liga o buzzer           **
** Ex: display 1 = 1, display 2 = 2, etc...                     ** 
** Compilador: MikroC PRO PIC v.7.2.0                           **
**                                                              **
** Nome: Gabriel Lima Cordeiro                                  **
**                                                              **
** Obs: Ativar dips switchs: DISP1 a DISP4                      **
**                                                              **
** UFLA - Lavras/MG - 07/05/2025                                **
******************************************************************/

// Define o tempo de acendimento do display em ms.
#define tempo 5

// Converte valor numerico decimal para codigo 7 segmentos
unsigned short mask(unsigned short num){
    switch (num){
    case 0 : return 0x3F;
    case 1 : return 0x06;
    case 2 : return 0x5B;
    case 3 : return 0x4F;
    case 4 : return 0x66;
    case 5 : return 0x6D;
    case 6 : return 0x7D;
    case 7 : return 0x07;
    case 8 : return 0x7F;
    case 9 : return 0x6F;
    }
}

void atualizarDisplay(int *numeros){
    // Escreve valor no display 1 em codigo 7 segmentos.
    PORTD = mask(numeros[3]);
    porta.f2 = 1; // Ativa display 1.
    Delay_ms(tempo);
    porta.f2 = 0; // Desativa display 1.

    // Escreve valor no display 2 em codigo 7 segmentos.
    PORTD = mask(numeros[2]);
    porta.f3 = 1; // Ativa display 2.
    Delay_ms(tempo);
    porta.f3 = 0; // Desativa display 2.

    // Escreve valor no display 3 em codigo 7 segmentos
    PORTD = mask(numeros[1]);
    porta.f4 = 1; // Ativa display 3.
    Delay_ms(tempo);
    porta.f4 = 0; // Desativa display 3.

    // Escreve valor no display 4 em codigo 7 segmentos.
    PORTD = mask(numeros[0]);
    porta.f5 = 1; // Ativa display 4.
    Delay_ms(tempo);
    porta.f5 = 0; // desativa display 4.
}

void main(void){
    int cont = 0;
    int comecar = 0;
    int numeros[4];
    numeros[0]=0;
    numeros[1]=0;
    numeros[2]=0;
    numeros[3]=0;
    ADCON0 = 0X00;
    ADCON1 = 0X06; // desabilita conversor A/D.
    INTCON = 0; // desabilita interrupcoes.
    TRISA = 0; // configura portA como saida.
    trisc = 0xFD; //configura a portC para o buzzer
    PORTA = 0;
    TRISD = 0; // configura portD como saida.
    PORTD = 0;
    portb = 0;
    portc = 0;

    while(1){ // inicio do loop infinito.
        //caso o push-botton rb2 for apertado inicia o timer
        if(portb.rb2 == 0){
            comecar=1;
        }
        atualizarDisplay(numeros); //50 vezes = 1 segundo

        //caso esteja iniciado começa a decrementar o timer usando a atualização do display como referencia para os segundos
        if(comecar==1){
            cont++;
            if(cont == 50){
                cont = 0;
                numeros[0]--;
                if(numeros[0]<0){
                    numeros[0]=9;
                    numeros[1]--;
                    if(numeros[1]<0){
                        numeros[1]=9;
                        numeros[2]--;
                        if(numeros[2]<0){
                            numeros[2]=9;
                            numeros[3]--;
                            if(numeros[3]<0){
                                numeros[0]=0;
                                numeros[1]=0;
                                numeros[2]=0;
                                numeros[3]=0;
                            }
                        }
                    }
                }
            }
        }

        //caso o push-botton rb1 seja apertado ele incrementa o timer para seu ajuste
        if(portb.rb1 == 0){
            comecar=0;
            numeros[0]++;
            if(numeros[0]>9){
                numeros[0]=0;
                numeros[1]++;
                if(numeros[1]>9){
                    numeros[1]=0;
                    numeros[2]++;
                    if(numeros[2]>9){
                        numeros[2]=0;
                        numeros[3]++;
                        if(numeros[3]>9){
                            numeros[0]=0;
                            numeros[1]=0;
                            numeros[2]=0;
                            numeros[3]=0;
                        }
                    }
                }
            }
        }

        //caso o push-botton rb0 seja apertado ele decrementa o timer para seu ajuste
        if(portb.rb0 == 0){
            comecar=0;
            numeros[0]--;
            if(numeros[0]<0){
                numeros[0]=9;
                numeros[1]--;
                if(numeros[1]<0){
                    numeros[1]=9;
                    numeros[2]--;
                    if(numeros[2]<0){
                        numeros[2]=9;
                        numeros[3]--;
                        if(numeros[3]<0){
                            numeros[0]=0;
                            numeros[1]=0;
                            numeros[2]=0;
                            numeros[3]=0;
                        }
                    }
                }
            }
        }

        //quando finalizar o timer liga o buzzer até algum push-botton de ajuste seja apertado
        if(numeros[0]==0 && numeros[1]==0 && numeros[2]==0 && numeros[3]==0 && comecar==1){
            portc.rc1 = 0; //ligar buzzer
        }else{
            portc.rc1 = 1; //desligar buzzer
        }
    } // Fim do loop infinito
} // Fim do programa principal.