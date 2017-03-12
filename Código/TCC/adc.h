#define bit_set(p,m) ((p) |= _BV(m))
#define bit_get(p,m) ((p) & _BV(m))
#define bit_clear(p,m) ((p) &= ~_BV(m))

void adc_init(){
	bit_set(ADCSRA,ADEN);
	bit_set(ADCSRA,ADPS2);
	bit_set(ADCSRA,ADPS0);
	
	
	//ADMUX=0x05;//escolhe ad
	
	bit_set(ADMUX,REFS0);
	bit_set(ADMUX,REFS1);



	bit_set(ADMUX,MUX2);
}


uint16_t adc_read(uint8_t canal){
	
	
	if (canal==5) bit_set(ADMUX,MUX0);
	else bit_clear(ADMUX,MUX0);
		 
	
		 
		 
	
	
	bit_set(ADCSRA,ADSC);
	
	while(bit_get(ADCSRA,ADSC));
	
	return ADCW;
}