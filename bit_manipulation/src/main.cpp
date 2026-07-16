#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint8_t counter = 0; //questa variabile conta il numero di overflow del timer

int main(void) {
  //setup dei registri
  DDRB |= (1 << DDB5); //setup del registro DDRB5 nella posizione 5 a 1
  
  TCCR0A |= (1 << WGM01); //setup della modalita' 
  OCR0A = 249;
  TIMSK0 |= (1 << OCIE0A);

  sei(); //abilita interruzioni globali
  TCCR0B |= (1 << CS01) | (1 << CS00);

  while(1) {
    //led toggle
    if(counter > 125) {
      PORTB ^= (1 << PB5);
      counter = 0;
    }
  }
}


//ISR
ISR (TIMER0_COMPA_vect) {
  counter++;
}