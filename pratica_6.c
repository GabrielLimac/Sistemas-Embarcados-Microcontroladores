/*****************************************************************
** pratica 06                                                   **
**                                                              **
** Exemplo para utilizacao do sensor otico                      **
** presente no kit PICGenios com microcontrolador 18F452.       **
** Liga a ventoinha e mostra a contagem de pulsos nos           **
** LEDs da porta D.                                             **
**                                                              **
** Arquivo: sensor_infra.c                                      **
** Compilador: MikroC PRO PIC v.7.2.0                           **
**                                                              **
** Nome: Gabriel Lima Cordeiro                                  **
**                                                              **
** Obs: Ativar dips switchs: INFR, VENT e LED1                  **
**                                                              **
** UFLA - Lavras/MG - 20/05/2025                                **
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

#define atraso 1

void LCD(unsigned long int cont){
    char texto[16];
    LongToStr(cont,texto);
    Lcd_Cmd(_LCD_CLEAR); //limpa o Display
    delay_ms(atraso);
    Lcd_Out(1,4,texto);
    delay_ms(atraso);
}

void main(){
    char contadorPas = 0;
    unsigned long int contadorGiros = 0;

    ADCON0 = 0x00; // Configura todos pinos para digital e
    ADCON1 = 0x06; // desabilita o conversor A/D
    trisd = 0;
    portd = 0;
    portb = 0xFF;
    trisc = 1; // Entrada: RC0 ; os outros pinos sao saida
    portc.rc2 = 1; // liga a ventoinha

    Lcd_Init(); //Inicializa o Display
    delay_ms(atraso);
    Lcd_Cmd(_LCD_CLEAR); //limpa o Display
    delay_ms(atraso);
    Lcd_Cmd(_LCD_CURSOR_OFF); //Desabilita o cursor
    delay_ms(atraso);

    while(1) {
        while (portc.rc0 == 0)
            delay_us(1);
        while (portc.rc0 == 1)
            delay_us(1);

        contadorPas = contadorPas + 1;
        portd = contadorPas;
        
        if(contadorPas == 7){ //ventoinha possui 7 pás
            contadorPas=0;
            contadorGiros = contadorGiros + 1;
        }
        if(portb.rb0 == 0){
            contadorGiros=0;
        }
        LCD(contadorGiros);
    }
} // fim do programaa