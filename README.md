# Códigos da disciplina - Sistemas Embarcados com PIC

Este repositório contém os códigos desenvolvidos durante as aulas da disciplina, utilizando o **compilador MikroC PRO for PIC v7.2.0**.

---

## 🛠️ Compilador utilizado

- **MikroC PRO for PIC v7.2.0**
  - Baseado na linguagem **C**.
  - Desenvolvido pela [MikroElektronika](https://www.mikroe.com/mikroc).
  - Possui bibliotecas prontas para periféricos do PIC (UART, I2C, SPI, PWM, ADC, LCD, etc).
  - Gera arquivos `.hex` que podem ser gravados diretamente no microcontrolador.

### 📌 Exemplo simples em MikroC
```c
void main() {
   TRISB = 0x00;     // Configura PORTB como saída
   while(1) {
      PORTB = 0xFF;  // Liga todos os pinos
      Delay_ms(500);
      PORTB = 0x00;  // Desliga todos
      Delay_ms(500);
   }
}
