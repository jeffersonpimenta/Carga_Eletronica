

#define bit_set(p,m) ((p) |= _BV(m))

void pwm_init(){
		bit_set(TCCR1A,COM1B1);
		bit_set(TCCR1A,COM1A1);//modo nao inversor
		
		bit_set(TCCR1A,WGM11);
		bit_set(TCCR1A,WGM10);
		bit_set(TCCR1B,WGM12);//fast pwm 10bits
				
		//bit_set(TCCR1B,CS10);//sem prescaler, inicia o timer

		    
			

		
		sei(); //enable global interrupts
		bit_set(DDRB,PORTB2);
		bit_set(DDRB,PORTB1);
						
}

void set_pwm(uint16_t _pwm){
				    OCR1A=_pwm;
				    _pwm<<8;
				    OCR1B=_pwm;
}

	