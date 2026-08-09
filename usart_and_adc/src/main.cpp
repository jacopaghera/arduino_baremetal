#include <avr/io.h>
#include <string.h>

#define FOSC 16000000 //valore a cui inizializzo il clock, 16 Mhz
#define BAUD 9600 
#define MYUBRR FOSC/16/BAUD-1

void USART_Transmit(uint8_t);
void USART_Init(unsigned int);

char myString[11] = {'A', 'T', 'm', 'e', 'g', 'a', '3', '2', '8', 'P', '\0'};

int main(void) {
  USART_Init(MYUBRR);

  while(1) {
    for(int i = 0; i < strlen(myString); i++){
      USART_Transmit(myString[i]);
    }
    USART_Transmit('\n');
  }
  return 0;
}

void USART_Init(uint16_t baudRate, char parity, uint8_t dataBits, uint8_t stopBits) {
  uint16_t ubrr = (FOSC/16UL/baudRate - 1);
  UBRR0H = (unsigned char) (ubrr>>8);
  UBRR0L = (unsigned char) ubrr;
  //abilita sia la trasmissione sia il ricevimento

  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  //settaggio del formato: 8data, no parity, 1 stop bit, vedi datasheet
  switch(parity) {
    case 'o':
      UCSR0C |= ((1 << UPM00) | (1 << UPM01));
      break;
    case 'e':
      UCSR0C |= (1 << UPM01);
      UCSR0C &= ~(1 << UPM00);
      break;
    case 'n':
      UCSR0C &= ~(1 << UPM01);
      UCSR0C &= ~(1 << UPM00);
      break;
    default:
      UCSR0C &= ~(1 << UPM01);
      UCSR0C &= ~(1 << UPM00);
      break;
  }

  switch(dataBits){

  }

  switch(stopBits){
    
  }

}

void USART_Transmit(uint8_t DataByte){
  while((UCSR0A & (1 << UDRE0)) == 0) {}; //aspetta finche' UDR e' pronto
  UDR0 = DataByte;
}

