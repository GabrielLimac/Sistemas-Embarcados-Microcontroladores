/*****************************************************************
** Atividade 02                                                 **
**                                                              **
** Exemplo para utilizacao de buzzer do kit PIC 18 F452.        **
** Ao carregar o programa no kit, o buzzer desse sera           **
** acionado quando dois numeros 6 forem sorteados.              **
**                                                              **
** Compilador : MikroC PRO PIC v .7.2.0                         **
** Gabriel Lima Cordeiro                                        **
** UFLA - Lavras /MG - 11/04/2025                               **
*****************************************************************/
void main ()
{
   //variaveis para armazenar a fun��o rand do sorteio.
   int x1;
   int x2;
   //variavel para garantir apenas um sorteio.
   int sorteou=0;
   // trisc e' uma posicao (registrador) na memoria de dados
   // do microcontrolador. Configura o pino RC1 como saida para
   // comunicacao com o buzzer.
   trisb = 1;
   trisc = 0xFD; // 0b11111101
   trisd = 0;
   // Inicia com buzzer desligado.
   portc.rc1 = 1;
   portb = 0;
   portd = 0;
   // Loop infinito
   while(1){
        while(portb.rb0==0){
            //garantir que apenas um sorteio seja feito.
            if(sorteou == 0){
            x1 = (rand()%6)+1;
            x2 = (rand()%6)+1;
            sorteou=1;
            }
            portb=255;
            portd=255;
        }
        //reseta as variaveis.
        sorteou = 0;
        portb=0;
        portd=0;
        if(portb.rb0==1){
            //acender os LEDs portb
            if(x1==1){
                portb.rb1 = 1;
            }else if(x1==2){
                portb.rb2 = 1;
            }else if(x1==3){
                portb.rb3 = 1;
            }else if(x1==4){
                portb.rb4 = 1;
            }else if(x1==5){
                portb.rb5 = 1;
            }else if(x1==6){
                portb.rb6 = 1;
            }
            //acender os LEDs portd
            if(x2==1){
                portd.rb1 = 1;
            }else if(x2==2){
                portd.rb2 = 1;
            }else if(x2==3){
                portd.rb3 = 1;
            }else if(x2==4){
                portd.rb4 = 1;
            }else if(x2==5){
                portd.rb5 = 1;
            }else if(x2==6){
                portd.rb6 = 1;
            }
            //ligar o buzzer caso ambos sejam 6.
            if(x1==x2 && x1==6){
                portc.rc1 = 0;
            }else{
                portc.rc1 = 1;
            }
        }
   }
}