#define bit_get(p,m) ((p) & _BV(m))
#define bit_set(p,m) ((p) |= _BV(m))
#define bit_clear(p,m) ((p) &= ~_BV(m))

#define EncoderPORT PORTB
#define EncoderPinA PORTB0
#define EncoderPinB PORTB1
#define EncoderPin PINB
#define EncoderDDR DDRB

void encoder_init(){
	
	bit_clear(EncoderDDR,EncoderPinA);
	bit_clear(EncoderDDR,EncoderPinB);
	
		bit_clear(EncoderPORT,EncoderPinA);
		bit_clear(EncoderPORT,EncoderPinB);
	
}

int read_encoder(){
	
	if (bit_get(EncoderDDR,EncoderPinA))
	{
		while(bit_get(EncoderDDR,EncoderPinB)!=0)
		return 1
	}
	
	if (bit_get(EncoderDDR,EncoderPinB))
	{
		while(bit_get(EncoderDDR,EncoderPinA)!=0)
		return 2
	}	else return 0;
	
}

