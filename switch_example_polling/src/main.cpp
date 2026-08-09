#include <avr/io.h>
#include <avr/interrupt.h>

//uint8_t ButtonPressed(void);
uint16_t RawKeyPressed(void);
bool DebounceSwitch(void);

int main(void) {
  DDRB |= (1 << DDB5); //set arduino pin 13 as output
  DDRD &= ~(1 << DDD5); //set arduino pin 5 as input
  PORTD |= (1 << PD5); //turn on input pullup

  TCCR0A |= (1 << WGM01);
  OCR0A = 62;
  TIMSK0 |= (1 << OCIE0A);
  sei();
  TCCR0B |= (1 << CS02);

  while(1) {
    //ButtonPressed();
  }
}

ISR (TIMER0_COMPA_vect) {
  if (DebounceSwitch())
    PORTB ^= 1 << 5;
}

bool DebounceSwitch() {
  static uint16_t State = 0;
  State = (State << 1) | RawKeyPressed() | 0xe000;
  if(State == 0xf000) return true;
  return false;
}

uint16_t RawKeyPressed() {
  return (PIND & 1<<5) >> 5;
}

// uint8_t ButtonPressed(void) {
//   static uint8_t buttonState = 0;
//   static uint8_t lastButtonState = 0;
//   buttonState = (PIND & (1<<5)) >> 5;
//   if((buttonState != lastButtonState) && (buttonState == 0)) {
//     PORTB ^= 1 << 5;
//   }
//   lastButtonState = buttonState;
//   return buttonState; //problema col bouncing
// }