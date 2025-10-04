/*************************************************************************************
** Programa: Leitura do sensor LM35                                                 **
** Placa: KIT PICGENIOS com microcontrolador 18F452                                 **
** Objetivo: Ler o canal AN2 (RA2 - sensor temperatura LM35) e escrever no LCD      **
**                                                                                  **
** Compilador: MikroC PRO PIC v.7.2.0                                               **
**                                                                                  **
** Nome: Gabriel Lima Cordeiro                                                      **
**                                                                                  **
** Obs.: fechar os dip-switchs TEMP e LCD                                           **
**                                                                                  **
** UFLA - Lavras/MG - 27/05/2025                                                    **
**************************************************************************************/

// Conexoes LCD do kit PICGenios com 18F452
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

//**************** definicao de variaveis ********************************
char texto[16]; // string para envio de mensagens ao LCD
unsigned int valor_AD; // resultado da conversao AD
int temperatura; // temperatura em graus Celsius
float temp_kelvin;
float temp_far;
//************************************************************************

//************** programa principal **************************************
void main(){
    // Desliga CAD
    ADCON0 = 0x00;
    ADCON1 = 0x06;
    trisd = 0x00; //define todos pinos do portd como saida - LCD
    trisa = 0x04; // define RA2/AN2 como entrada, outros pinos como saida
    trise = 0x00; // define todos pinos do porte como sa?da - LCD
    portd = 0;

    // Inicializa o LCD
    Lcd_Init(); //Inicializa o Display
    Delay_ms(100);
    Lcd_Cmd(_LCD_CLEAR); //limpa o Display
    Delay_ms(100);
    Lcd_Cmd(_LCD_CURSOR_OFF); //Desabilita o cursor
    Delay_ms(100);
    Lcd_Out(1,1,"Temperatura[oC]:");
    Delay_ms(100);
    ADC_Init(); // Inicializa o CAD

    /*reconfigura e define pinos de A/D - ADCON1
    B7 - 1: justificado a direita
    0: justificado a esquerda
    B6 - 0: fonte de clock oscilador RC interno do ADC
    B5 - NC
    B4 - NC
    B3:B0 = 0b0010 = canais AN0 a AN4, Vref+ = VDD, Vref- = GND */

    ADCON1 = 0b10000010;

    /*reconfigura A/D - ADCON0
    B7:B6 - 0b11: fonte de clock oscilador RC interno do ADC
    B5:B3 - 0b010: canal 2 - AN2
    B2 - status do CAD
    B1 - NC
    B0 - 1: ADC ligado
    0: ADC desligado */

    ADCON0 = 0b11010001;

    do {
        valor_AD = ADC_Get_Sample(2); // le canal 2 e salva
        temperatura = (float)valor_AD * ((float)500 / (float)1024); // converte para oC
        temp_kelvin = temperatura + 273.15;
        temp_far = temperatura * 1.8 + 32;

        // Verifica qual botao esta pressionado e exibe a temperatura correspondente
        if (portb.rb0 == 0) { // Se RB0 for pressionado
            Lcd_Out(1, 1, "Temperatura[oC]:");
            FloatToStr(temperatura, texto); // Converte valor temperatura em string
            Lcd_Out(2, 1, texto); // Envia para o LCD o valor string da conversao AD
        }
        else if (portb.rb1 == 0) { // Se RB1 for pressionado
            Lcd_Out(1, 1, "Temperatura[K]:");
            FloatToStr(temp_kelvin, texto); // Converte valor temperatura em string
            Lcd_Out(2, 1, texto); // Envia para o LCD o valor string da conversao AD
        }
        else if (portb.rb2 == 0) { // Se RB2 for pressionado
            Lcd_Out(1, 1, "Temperatura[F]:");
            FloatToStr(temp_far, texto); // Converte valor temperatura em string
            Lcd_Out(2, 1, texto); // Envia para o LCD o valor string da conversao AD
        }

        Delay_ms(100); // Delay de 100ms
    } while (1);
}
