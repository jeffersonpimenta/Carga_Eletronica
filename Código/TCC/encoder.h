#define bit_get(p,m) ((p) & _BV(m))
#define bit_set(p,m) ((p) |= _BV(m))
#define bit_clear(p,m) ((p) &= ~_BV(m))

#define EncoderPORT PORTD
#define EncoderPinA PORTD6
#define EncoderPinB PORTD7
#define EncoderPin PIND
#define EncoderDDR DDRD

void encoder_init(){
	
	bit_clear(EncoderDDR,EncoderPinA);
	bit_clear(EncoderDDR,EncoderPinB);
	
	bit_clear(DDRB,PORTB0);//chave encoder

	
	//	bit_clear(EncoderPORT,EncoderPinA);
		//bit_clear(EncoderPORT,EncoderPinB);
	
}

int read_encoder(){

	
		if (bit_get(EncoderPin,EncoderPinA))
		{
			
			while(bit_get(EncoderPin,EncoderPinA));
			
			_delay_ms(130);
			
			if (bit_get(EncoderPin,EncoderPinB))
			{
				return 1;
			}else{
				return 2;
			}

		}else return 0;
		
	

/*

if (bit_get(EncoderPin,EncoderPinA))
{
	_delay_ms(500);
	return 2;
}
	
if (bit_get(EncoderPin,EncoderPinB))
{
	_delay_ms(500);
	return 1;
}


*/
return 0;
		
	
}


int get_keypressed(){
	
	if(bit_get(PINB,PORTB0)){
		_delay_ms(1000);
		if (bit_get(PINB,PORTB0))
		{
			return 2;
		}else return 1;
	}else return 0;
	
}

