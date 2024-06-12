#include <avr/io.h>
#include <util/delay.h>

int i=0, j=0, k=0, l=0, c, d, n=0, n1, n2, o, result;

//char tab[10]={~0b00111111, ~0b00000110, ~0b01011011, ~0b01001111, ~0b01100110, ~0b01101101, ~0b01111101, ~0b00000111, ~0b011111111, ~0b01101111}; //for real microcontroller
char tab[10]={0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b011111111, 0b01101111}; // for simulator

char y1, y2;

void show(){
	PORTB=tab[l];
	PORTD=0b00000001; //negate for real microcontroller
	_delay_ms(10);
	PORTB=tab[k];
	PORTD=0b00000010; //negate for real microcontroller
	_delay_ms(10);
	PORTB=tab[j];
	PORTD=0b00000100; //negate for real microcontroller
	_delay_ms(10);
	PORTB=tab[i];
	PORTD=0b00001000; //negate for real microcontroller
}

int getNumber(){
	return ((1000 * l) + (100 * k) + (10 * j) + i);
}

int operation(){
	if(o==1){
		return n1 + n2;
	}
	else if(o==2){
		return n1 - n2;
	}
	else if(o==3){
		return n1 * n2;
	}
	else if(o==4){
		return n1 / n2;
	}
}

void getResult(){
	if (result >= 9999){
		i = 9;
		j = 9;
		k = 9;
		l = 9;
		result = 9999;
	}
	else if (result <= 0){
		i = 0;
		j = 0;
		k = 0;
		l = 0;
		result = 0;
	}
	else{
		l = result / 1000;
		k = (result/100) % 10;
		j = (result/10) % 10;
		i = result % 10;
	}
}

void check(){
	if((d>=1 && d<=9) && n==3){
		l=k;
		k=j;
		j=i;
		i=d;
		n++;
	}
	else if((d>=1 && d<=9) && n==2){
		k=j;
		j=i;
		i=d;
		n++;
	}
	else if((d>=1 && d<=9) && n==1){
		j=i;
		i=d;
		n++;
	}
	else if((d>=1 && d<=9) && n==0){
		i=d;
		n++;
	}
	else if(d == 10 && (n==0 ||  n==1 || n==2 || n==3) && !(i==0 && j==0 && k==0 && l==0)){
		l=k;
		k=j;
		j=i;
		i=0;
		n++;	
	}
	
	else if(d == 12){
		n=0;
		n1 = getNumber();
		o = 4;
		i=0;
		j=0;
		k=0;
		l=0;
	}
	else if(d == 13){
		n=0;
		n1 = getNumber();
		o = 1;
		i=0;
		j=0;
		k=0;
		l=0;
	}
	else if(d == 14){
		n=0;
		n1 = getNumber();
		o = 2;
		i=0;
		j=0;
		k=0;
		l=0;
	}
	else if(d == 15){
		n=0;
		n1 = getNumber();
		o = 3;
		i=0;
		j=0;
		k=0;
		l=0;
	}
	else if(d == 16){
		n=0;
		n2 = getNumber();
		result = operation();
		o = 0;
		//_delay_ms(2000);
		getResult();
		n1 = getNumber();
		if(getNumber()>999){
			n=4;
		}
		else if(getNumber()>99){
			n=3;
		}
		else if(getNumber()>9){
			n=2;
		}
		else{
			n=1;
		}
	}
	_delay_ms(2000);
}

int main(void)
{
	DDRA = 0b11110000;
	PORTA = 0b00001111;
	
	DDRB = 255;
	PORTB = 0;
	
	DDRD = 0b00001111;
	PORTD = 0b00000000;
	

	while (1)
	{
		show();
		
		for (c = 4; c < 8; c++) {
			PORTA = ~(1 << c);
			_delay_ms(1);
			y1 = PINA & 0x0F;
			_delay_ms(10);
			show();
			y2 = PINA & 0x0F;
			if(y1==y2){
				switch(y1) {
					case 0b00001110:
					d = (0 * 4) + (c - 3);
					check();
					break;
					case 0b00001101:
					d = (1 * 4) + (c - 3);
					check();
					break;
					case 0b00001011:
					d = (2 * 4) + (c - 3);
					check();
					break;
					case 0b00000111:
					d = (3 * 4) + (c - 3);
					check();
					break;
				}
			}
		}
	}
}