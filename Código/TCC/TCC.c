	/*
 * TCC.c
 *
 * Created: 05/09/2015 00:59:30
 *  Author: Jéfferson
 */ 


#define bit_get(p,m) ((p) & _BV(m))
#define bit_set(p,m) ((p) |= _BV(m))
#define bit_clear(p,m) ((p) &= ~_BV(m))
#define bit_flip(p,m) ((p) ^= _BV(m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x) (0x01 << (x))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))  //macros
#define swap(a,b) ({a ^= b; b ^= a; a ^= b; })

#define F_CPU 12000000  //12MHz
#include <avr/delay.h>
#include <avr/interrupt.h>

#include <math.h>
#include <avr/io.h>
#include "lcd.h"
#include "pwm.h"
#include "adc.h"
#include "encoder.h"


int pegacaractere(uint8_t x,uint8_t y){
	
	uint8_t encoder=0;
	uint8_t num=0;
	
	lcd_set_position(x,y);//posiciona cursor
	lcd_write_instruction(Set_blink_on);//pisca
	
	while(get_keypressed()==0){//faz até apertar o botao do encoder		
		
		encoder=read_encoder();
		
		if (encoder==1)//testa encoder horário
		{
			if(num==0)//testa se o numero já esta no seu menor valor possivel
			{
				num=9;//faz o overflow do numero
			}else{
				num--;//decrementa normal
			}
			
			lcd_set_position(x,y);//posiciona cursor
			lcd_write_int(num);//atualiza no lcd o valor
			lcd_set_position(x,y);//posiciona cursor
		}
		
		
		if (encoder==2)//testa encoder antihorário
		{
			if (num==9)//testa se já tá com o maior valor
			{
				num=0;//faz o overflow
			}else{
				num++;//incrementa normal
			}
			
			
			
			lcd_set_position(x,y);//posiciona cursor
			lcd_write_int(num);//atualiza no lcd o valor	
			lcd_set_position(x,y);//posiciona cursor	
			
			
		}
			
	}
	
	
	
	lcd_write_instruction(Set_blink_off);//desliga cursor
	return num;
	
}


double take_number(uint8_t tip,uint8_t virgres, uint8_t x, uint8_t y){
	
	//x e y indicam o início da variável a ser pega, fiz isso pra escrever no lcd direitin
	//virgres representa a quantidade de casas depois da virgula
	//tip representa a quantidade de casas do numero sem a virgula

	
	
	uint8_t numero=0;
	double total=0;
	
	for (uint8_t i=0;i<tip;i++)
	{
		_delay_ms(200);
		if (i>=(tip-virgres))//testa se o número pego é depois ou antes da virgula
		{
			if (i==(tip-virgres))//testa se i é igual a virgula
			{
				lcd_write_xy(".",(x+i),y);//escreve a virgula no lugar correto
			}			
			
			numero=pegacaractere((x+i+1),y);//desloca o numero uma casa
			total=total+(numero*(pow(10,(tip-i-virgres-1))));
			
			
		}else{
			
			numero=pegacaractere((x+i),y);//nao desloca uma casa, numero sendo pego antes da virgula
			total=total+(numero*(pow(10,(tip-i-virgres-1))));
		}
		
		
	}
	
	return total;		
		
	}


double pega_numero(uint8_t tip, uint8_t vigres, uint8_t x, uint8_t y){
	
	uint8_t numero[tip];
	double total=0;
	uint8_t encoder=0;
	uint8_t i;
	
	
	for (i=0;i<tip;i++)
	{
		numero[i]=0;//zera vetor
	}
	
	i=0;	
	lcd_set_position(x,y);//posiciona cursor
	lcd_write_instruction(Set_blink_on);//pisca	
	
	
	while(1){//enquanto nao sair daqui com break;
			
		
		encoder=read_encoder();	//le se rodou o encoder
		
		
		if (encoder==2)//se rodou no sentido horario
		{
			
			if (i==(tip-1))//se o contador for igual ao número de dígitos, direciona ele pro primeiro caractere
			{
				i=0;//primeiro caractere
			}else i++;//senao, incrementa normalmente
			
			
			if (i>=tip-vigres)//testa se o cursor está antes ou depois da virgula
			{
				lcd_set_position(x+i+1,y);//se sim, desloca o cursor uma posição
			}else{
				lcd_set_position(x+i,y);//caso contrario nao desloca
			}
		}
		
		
		
		
		if (encoder==1)//se rodou no sentido anti horario
		{
			if (i==0)//se o contador for igual a zero, faz a rotação
			{
				i=(tip-1);//ultimo caractere
			}else i--;//senao, decrementa normalmente
			
			
			if (i>=tip-vigres)//testa se o cursor está antes ou depois da virgula
			{
				lcd_set_position(x+i+1,y);//se sim, desloca o cursor uma posição
			}else{
				lcd_set_position(x+i,y);//caso contrario nao desloca
			}	
		}
		
		
		encoder=get_keypressed();//le o botao do encoder
		
		if (encoder==1)//se tiver apertado, entra pra configurar o numero
		{
			
			if (i>=tip-vigres)//testa se o cursor está antes ou depois da virgula
			{
				numero[i]=pegacaractere((x+i+1),y);	//ajusta a virgula
			}else{
				numero[i]=pegacaractere(x+i,y);	//nao ajusta a virgula
			}			
			

			lcd_write_instruction(Set_blink_on);//pisca				
		}
		
		if (encoder==2)//testa se foi segurado
		{
			
			for (i=0;i<tip;i++)
			{
				total=total+(numero[i]*pow(10,(tip-i-vigres-1)));//calcula total
			}			
			break;
		}
		
	}
	
	lcd_write_instruction(0b00001100);//desliga cursor
	return total;	
	
}	


void show_menu(uint8_t tip,double I,double P, double R, double V){

	if (tip==0)//função menu cíclico
	{
		lcd_write_xy(">00.00A",0,1);
		lcd_write_xy(" 000.0W",0,2);
		lcd_write_xy(" 000.00",8,1);
		lcd_write_character(0b11110100);//simbolo ohm
	}
	if (tip==1)
	{
		lcd_write_xy(" 00.00A",0,1);
		lcd_write_xy(">000.0W",0,2);
		lcd_write_xy(" 000.00",8,1);
		lcd_write_character(0b11110100);
	}
	if (tip==2)
	{
		lcd_write_xy(" 00.00A",0,1);
		lcd_write_xy(" 000.0W",0,2);
		lcd_write_xy(">000.00",8,1);
		lcd_write_character(0b11110100);
	}
	
	if (tip==3)
	{
		lcd_set_position(1,1);//corrente
			if (I<10) lcd_write_int(0); //resolve problema do zero extra
		lcd_write_int16(I,4,2);
		lcd_set_position(1,2);//potencia
		lcd_write_int16(P,4,1);
		lcd_set_position(9,1);//resistencia
		lcd_write_int16(R,6,2);
		lcd_set_position(9,2);//tensao
		lcd_write_int16(V,4,1);
	}
	
	if (tip==4)
	{
		lcd_write_xy(">00.00A",0,1);
		lcd_write_xy(" 000.0W",0,2);
		lcd_write_xy(" 000.00",8,1);
		lcd_write_character(0b11110100);//exibe o caractere ohm
		lcd_write_xy(" 000.0V",8,2);//mostra menuzinho
		lcd_write_character(0b11011100);//mostra indicativo de circuito aberto
	}
	

}


void overload(){

	if (bit_get(PINC,PORTC3))
	{
		set_pwm(0);//desliga corrente
		lcd_write_instruction(lcd_Clear);//limpa tela
		lcd_write_xy("Temp overload",2,1);
		lcd_write_xy("Wait and reboot",1,2);//mostra mensagem de sobrecarga
		while(1){
			
		}
	}

}


double letensao(){
	double tensao;
	uint16_t array[40];
	
	
	for (int i=0;i<40;i++)
	{
		array[i]=adc_read(4);
		_delay_ms(10);
	}
	
	for (int j=39;j>1;j--)
	{
		for (int i=0;i<j;i++)
		{
			if (array[i]>array[i+1])
			{
				tensao=array[i+1];
				array[i+1]=array[i];
				array[i]=tensao;
			}
		}
	}

	tensao=0;
	
	for (int i=18;i<22;i++)
	{
		tensao=tensao+array[i];
	}
	
	tensao=tensao/4;

	
	tensao=tensao*0.21299073;
	
	return tensao;
}


double lecorrente(){
	double corrente;
	uint16_t array[40];
	

	
	for (int i=0;i<40;i++)
	{
		array[i]=adc_read(5);
		_delay_ms(10);
	}
	
	for (int j=39;j>1;j--)
	{
		for (int i=0;i<j;i++)
		{
			if (array[i]>array[i+1])
			{
				corrente=array[i+1];
				array[i+1]=array[i];
				array[i]=corrente;
			}
		}
	}
	
	
	corrente=0;
	
	for (int i=18;i<22;i++)
	{
		corrente=corrente+array[i];
	}
	
	corrente=corrente/4;
	
	corrente=(corrente*0.010972612);
	

	return corrente;	
}


void setI(double I){
	
	if (I>10) I=10;	
	I=I*102.4;
	
	if (I!=0)
	{
		bit_set(TCCR1B,CS10);//sem prescaler, inicia o timer
	}else{
		bit_clear(TCCR1B,CS10);//sem prescaler, desliga o timer
	}
	
	set_pwm(I);
}


int main(void)
{
	lcd_init();
	pwm_init();
	adc_init();
	encoder_init();
	bit_clear(DDRC,PORTC3);//configura a porta da proteção
	set_pwm(0);

	uint8_t j;
	uint8_t encoder;
	double P=0;
	double U=0;
	double R=0;
	double I=0;//declara variaveis
	
	
	uint8_t menu;// menu0 - corrente constante
					//menu1 - potência constante
					//menu2 - resistência constante


	while(1)
	{
		
		menu=0;
		show_menu(4,0,0,0,0);//mostra valores zerados

		_delay_ms(1000);
	
	
		while(get_keypressed()==0)//enquanto botao de encoder n for apertado
		{
			encoder=read_encoder();
			if (encoder==1)
			{
				if (menu==2) menu=0;
				else menu++;
				show_menu(menu,0,0,0,0);
			}

			if (encoder==2)
			{
				if (menu==0) menu=2;
				else menu--;
				show_menu(menu,0,0,0,0);
			}
		}//rotação da seleção do menu
	
		_delay_ms(100);


			if (menu==0)
			{			
				I=pega_numero(4,2,1,1);//corrente		
	
				
				
	
				setI(I);//seta corrente
				lcd_set_position(15,2);
				lcd_write_character(0b11011011);//indicativo circuito fechado
			
				while(get_keypressed()!=2){//enquanto nao segurar o botao do encoder
				
					overload();//testa se existe sobrecarga
					

					I=lecorrente();

				

					U=letensao();
			
									
								
				
					show_menu(3,I,I*U,U/I,U);//mostra
									
					_delay_ms(50);//delay
				}
			setI(0);
				
			}
		
			if (menu==1)
			{
				P=pega_numero(4,1,1,2);//potencia

				lcd_set_position(15,2);
				lcd_write_character(0b11011011);//indicativo circuito fechado
			
				while(get_keypressed()!=2){//enquanto nao segurar o botao do encoder
				
					overload();//testa se existe sobrecarga
				

						U=letensao();
			
				
					I=P/U;//calcula corrente
					setI(I);//seta corrente
				

					I=lecorrente();
									
				
					show_menu(3,I,I*U,U/I,U);//mostra valores
					_delay_ms(50);//delay				
				}
			setI(0);
			
			}
		
			if (menu==2)
			{
				R=pega_numero(5,2,9,1);//resistencia
				
				lcd_set_position(15,2);
				lcd_write_character(0b11011011);//indicativo circuito fechado			
			
				while(get_keypressed()!=2){//enquanto nao segurar o botao do encoder

					overload();//testa se existe sobrecarga
					

						U=letensao();
						
	

					I=U/R;//calcula o valor da corrente
					if (I>10) I=10;
					
					
					setI(I);//seta o valor da corrente
				

						I=lecorrente();
	
	
					show_menu(3,I,I*U,R,U);//mostra os valores				
					_delay_ms(50);//delay				
				}		
			setI(0);
			
			
		}	
}
}