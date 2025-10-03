/**************************************************************
** Exemplo 03                                                 *
**                                                            *
** Exemplo para utilizacao do LCD presente no kit PIC         *
** 18F452. O programa inicializa o display e execurará        *
** a lógica de um rélogio sistema de ajuste.                  *
**                                                            *
** Arquivo: lcd.c                                             *
** Compilador: Mikro C PRO PIC v.7.2.0                        *
**                                                            *
** Nome: Gabriel Lima Cordeiro                                *
**                                                            *
** UFLA - Lavras/MG - 25/04/2025                              *
***************************************************************/
int segundos=0,minutos=0,horas=0;
char seg[7];
char minuts[7];
char hor[7];
char horario[10];
// Conexoes LCD do kit PICGenios com 18F
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
// Fim das conexoes
void main(){
    portb = 0;
    ADCON0 = 0x00; // Configura todos pinos das portas para digital e
    ADCON1 = 0x0F; // desabilita o conversor A/D
    Lcd_Init(); //Inicializa o Display
    delay_ms(100);
    Lcd_Cmd(_LCD_CLEAR); //Limpa o Display
    delay_ms(100);
    Lcd_Cmd(_LCD_CURSOR_OFF); //Desabilita o cursor
    delay_ms(100);
    while(1){
        //Quando apertar o pushbutton rb0 incrementa os minutos
        if(portb.rb0==0){
            minutos=minutos+1;
        }else{
            delay_ms(1000);
        }
        //Quando apertar o pushbutton rb1 incrementa as horas
        if(portb.rb1==0){
            horas=horas+1;
        }
        segundos=segundos+1;

        //lógica para incremento dos minutos e horas
        if(segundos==60){
            minutos=minutos+1;
            segundos = 0;
        }
        if(minutos==60){
            horas=horas+1;
            minutos=0;
            segundos=0;
        }
        if(horas==24){
            horas=0;
            minutos=0;
            segundos=0;
        }

        //converter segundos, minutos e horas em string
        IntToStr(segundos,seg);
        Ltrim(seg);
        IntToStr(minutos,minuts);
        Ltrim(minuts);
        IntToStr(horas,hor);
        Ltrim(hor);
        //reseta o horario anterior
        horario[0] = '\0';
        //Os if adicionando o 0 dos valores menos que 10.
        if(horas<10){
            strcat(horario,"0");
        }
        //concatenação dos tempos
        strcat(horario,hor);
        strcat(horario,":");
        if(minutos<10){
            strcat(horario,"0");
        }
        strcat(horario,minuts);
        strcat(horario,":");
        if(segundos<10){
            strcat(horario,"0");
        }
        strcat(horario,seg);

        Lcd_Cmd(_LCD_CLEAR); //Limpa o Display
        delay_ms(100);
        Lcd_Cmd(_LCD_CURSOR_OFF); //Desabilita o cursor
        delay_ms(100);

        Lcd_Out(1,4,horario); // Escreve no LCD na linha 1 coluna 4
        delay_ms(100);
    }
 } // fim do programa