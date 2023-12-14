/************************************************************/
/*    Title:    Debug										*/
/*    Author:   lau											*/
/*    Hardware: ATmega16/Megacard							*/
/*    Note:     fclk=12MHz									*/
/************************************************************/
#include <AVR/io.h>
#include <AVR/interrupt.h>

volatile char mode=0;

ISR(TIMER0_OVF_vect)	//f=12MHz/256 = ca. 46kHz
{
	static unsigned char vt=0,dir=1;
	vt++;
	if (vt>=5)
	{
		vt=0;
		switch (mode)
		{
			case 1:
				PORTC>>=1;
				if (!PORTC)
					PORTC=0x80;
				break;
			case 2:
				PORTC<<=1;
				if (!PORTC)
					PORTC=0x01;
				break;
			case 3:
				if (dir)
				{
					PORTC<<=1;
					if (!PORTC)
					{
						PORTC=0x40;
						dir=0;
					}
				}
				else
				{
					PORTC>>=1;
					if (!PORTC)
					{
						PORTC=0x02;
						dir=1;
					}
				}
				break;
			default:
				PORTC++;
				break;
		}
	}
}

void init()
{
	DDRC   = 0xFF;			// LED-Ports auf Ausgang
	//PORTA  = 0x0F;			// PA0...PA3=Taster
	DDRA = 0x00;
	PORTC  = 0x01;			// 1.Leuchtpunkt einschalten
	
	TCCR0 |= (1<<CS00);		// kh=1
	TIMSK |= (1<<TOIE0);	// TOV0-enable
}
int main( void )
{
	init();
	sei();					// Interrupts enablen

	for(;;)
	{
		/*if ((PINA & 0x01)==0x00)
			mode=1;
		if (!(PINA &0x02))
			mode =2;
		if (~PINA & 0x04)
			mode=3;
		if (~PINA & 0x04)
			mode=0;*/
		if ((PINA & 0x01) == 0x00)
			mode = 1;
		if (!(PINA & 0x02))
			mode = 2;
		if (!(PINA & 0x04))
			mode = 3;
		if (!(PINA & 0x08))
			mode = 0;
	}
}

