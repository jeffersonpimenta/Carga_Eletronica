



#ifndef F_CPU
#define F_CPU 4000000UL
#endif

#define bit_get(p,m) ((p) & _BV(m))
#define bit_set(p,m) ((p) |= _BV(m))
#define bit_clear(p,m) ((p) &= ~_BV(m))

 #define KEYPAD_PORT PORTD
 #define KEYPAD_DDR   DDRD
 #define KEYPAD_PIN   PIND
 
 
 
 int get_keypad(){
	 
	 
	 
	 
	 bit_set(KEYPAD_DDR,PORTD0);
	 bit_set(KEYPAD_DDR,PORTD1);
	 bit_set(KEYPAD_DDR,PORTD2);
	 bit_clear(KEYPAD_DDR,PORTD3);
	 bit_clear(KEYPAD_DDR,PORTD4);
	 bit_clear(KEYPAD_DDR,PORTD5);
	 bit_clear(KEYPAD_DDR,PORTD6);
	 
	 KEYPAD_PORT=0x00;
	 
	 bit_clear(KEYPAD_PORT,PORTD2);
	 bit_set(KEYPAD_PORT,PORTD0);
	 _delay_ms(10);
	 if (KEYPAD_PIN & (0x01<<3))
	 {
		 return 10;
	 } else if (KEYPAD_PIN & (0x01<<4))
	 {
		 return 9;
	 } else if (KEYPAD_PIN & (0x01<<5))
	 {
		 return 6;
	 } else if (KEYPAD_PIN & (0x01<<6))
	 {
		 return 3;
	 }
	 
	 
	 bit_clear(KEYPAD_PORT,PORTD0);
	 bit_set(KEYPAD_PORT,PORTD1);
	 _delay_ms(10);
	 if (KEYPAD_PIN & (0x01<<3))
	 {
		 return 0;
	 } else if (KEYPAD_PIN & (0x01<<4))
	 {
		 return 8;
	 } else if (KEYPAD_PIN & (0x01<<5))
	 {
		 return 5;
	 } else if (KEYPAD_PIN & (0x01<<6))
	 {
		 return 2;
	 }	 
	 
	
	 bit_clear(KEYPAD_PORT,PORTD1);
	 bit_set(KEYPAD_PORT,PORTD2);
	 _delay_ms(10);
	 if (KEYPAD_PIN & (0x01<<3))
	 {
		 return 11;
	 } else if (KEYPAD_PIN & (0x01<<4))
	 {
		 return 7;
	 } else if (KEYPAD_PIN & (0x01<<5))
	 {
		 return 4;
	 } else if (KEYPAD_PIN & (0x01<<6))
	 {
		 return 1;
	 } else return 255;
	 

 }