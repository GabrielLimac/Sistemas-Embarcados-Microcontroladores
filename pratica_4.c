/*****************************************************************
** pratica 04                                                   **
**                                                              **
** Exemplo para utilizacao do LCD e do teclado matricial        **
** presente no kit PICGenios com PIC 18F452.                    **
** De acordo com a tecla acionada no teclado, os LEDs           **
** piscaram se a senha for correta, do contrario o buzzer       **
** ligará por alguns segundos                                   **
**                                                              **
** Nome: Gabriel Lima Cordeiro                                  **
**                                                              **
** Arquivo: teclado_LCD.c                                       **
** Compilador: MikroC PRO PIC v.7.2.0                           **
** Obs.: fechar dipswitch LCD                                   **
** UFLA - Lavras/MG - 01/05/2025                                **
******************************************************************/
// Conexoes LCD do kit PICGenios
sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// Fim das conexoes do LCD
// Conexoes do teclado
// Saidas do PIC:
// RB0 - primeira coluna
// RB1 - segunda coluna
// RB2 - terceira coluna
// Entradas do PIC:
// RD3 - primeira linha
// RD2 - segunda linha
// RD1 - terceira linha
// RD0 - quarta linha

#define atraso 50
void LCD(char texto[16]){
    Lcd_Cmd(_LCD_CLEAR); //limpa o Display
    delay_ms(atraso);
    Lcd_Out(1,4,texto);
    delay_ms(atraso);
}

//Função para retornar o numero apertado
char *teclado(){
    do{
        portb.rb0 = 0; //habilita primeira coluna do teclado
        delay_ms(atraso);
        if (portd.rd0 == 0) {
            LCD("<---");
        }
        else if (portd.rd1 == 0){
            //LCD("7");
            return "7";
        }
        else if (portd.rd2 == 0){
            //LCD("4");
            return "4";
        }
        else if (portd.rd3 == 0){
            //LCD("1");
            return "1";
        }
        portb.rb0 = 1; //desabilita primeira coluna do teclado
        delay_ms(atraso);
        //--------------------------------------------------------------------------
        portb.rb1 = 0; //habilita segunda coluna do teclado
        delay_ms(atraso);
        if (portd.rd0 == 0){
            //LCD("0");
            return "0";
        }
        else if (portd.rd1 == 0){
            //LCD("8");
            return "8";
        }
        else if (portd.rd2 == 0){
            //LCD("5");
            return "5";
        }
        else if (portd.rd3 == 0){
            //LCD("2");
            return "2";
        }
        portb.rb1 = 1; //desabilita segunda coluna do teclado
        delay_ms(atraso);
        //------------------------------------------------------------------------
        portb.rb2 = 0; //habilita terceira coluna do teclado
        delay_ms(atraso);
        if (portd.rd0 == 0) LCD("--->");
        else if (portd.rd1 == 0){
            //LCD("9");
            return "9";
        }
        else if (portd.rd2 == 0){
            //LCD("6");
            return "6";
        }
        else if (portd.rd3 == 0) {
            //LCD("3");
            return "3";
        }
        portb.rb2 = 1; //desabilita terceira coluna do teclado
        delay_ms(atraso);
        //------------------------------------------------------------------------
    } while(1);
}

//Função para piscar o LED quando a senha estiver certa
void piscarLeds(){
    portb.rb5=1;
    portb.rb6=1;
    portb.rb7=1;
    delay_ms(500);
    portb.rb5=0;
    portb.rb6=0;
    portb.rb7=0;
    delay_ms(500);
}
void main(){
    char texto[5];
    int cont=0;
    ADCON0 = 0X00; // Desabilita o conversor A/D
    ADCON1 = 0x06; // Configura todos pinos da porta A para digital
    trisd = 0x0F; //configura os pinos RD0,RD1,RD2,RD3 da PORTD como
    // entradas (teclado), e RD4,RD5,RD6,RD7 como saida
    // (LCD)
    //trisb = 0xF8; // configura pinos RB0,RB1,RB2 da PORTB como saida (teclado)
    // e o restante como entrada
    trisb = 0x00;
    trisc = 0xFD; //configurar pino do buzzer
    portb = 0xFF; //configura todos os pinos PORTB como saida
    portc.rc1 = 0; //inicia o buzzer desligado
    portb.rb4 = 0; //apaga o LED RB4
    texto[0]='\0'; //inicializa o texto do LCD
    Lcd_Init(); //Inicializa o Display
    delay_ms(atraso);
    Lcd_Cmd(_LCD_CLEAR); //limpa o Display
    delay_ms(atraso);
    Lcd_Cmd(_LCD_CURSOR_OFF); //Desabilita o cursor
    delay_ms(atraso);
    while(1){
        //apaga os demais LEDs
        portb.rb5=0;
        portb.rb6=0;
        portb.rb7=0;
        while(cont<=3){
            strcat(texto,teclado());
            LCD(texto);
            cont = cont+1;
        }
        
        //caso a senha: 3004 seja apertada pisca os LEDs algumas vezes, 
        //caso contrario liga buzzer por alguns segundos.
        if(texto[0]=='3' && texto[1]=='0' && texto[2]=='0' && texto[3]=='4'){
            piscarLeds();
            piscarLeds();
            piscarLeds();
            piscarLeds();
        }else{
            portc.rc1 = 1;
            delay_ms(2000);
            portc.rc1 = 0;
        }
        //reinicia as variaveis
        cont=0;
        texto[0]='\0';
        Lcd_Init(); //Inicializa o Display
        delay_ms(atraso);
        Lcd_Cmd(_LCD_CLEAR); //limpa o Display
        delay_ms(atraso);
        Lcd_Cmd(_LCD_CURSOR_OFF); //Desabilita o cursor
        delay_ms(atraso);
    }
} // fim do progra