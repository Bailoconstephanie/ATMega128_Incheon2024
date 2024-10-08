#define F_CPU 16000000UL // 16MHz
#include <avr/io.h> // AVR 기본 헤더
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
// LED Port : PG4, output
// Switch : PG3, input => SW 버튼을 눌러줘야 깜빡거리게 하는 동작을 구현하고자 함
// 함수로 만들어보자
int Check()
{
	char v = 0;
	v = PING & 0x01; // v = G3 bit의 값, SW를 누르면 v = 0
	if( v==0)
	{
		return 1; // Pushed
	}
	else
	{
		return 0;
	}
	
}
int Check_fast()
{
	char v = 0;
	v = PING & 0x02; // v = G1 bit의 값, SW를 누르면 v = 0 // delay 감소...
	if( v==0)
	{
		return 1; // Pushed
	}
	else
	{
		return 0;
	}
	
}
int Check_slow()
{
	char v = 0;
	v = PING & 0x04; // v = G1 bit의 값, SW를 누르면 v = 0 // delay 증가...
	if( v==0)
	{
		return 1; // Pushed
	}
	else
	{
		return 0;
	}
	
}

void delay(int x)
{
	while (x > 0)
	{
		_delay_ms(1);
		x--;
	}
}

int main(void) // ATMega128에 LED를 연결하여 LED ON 시키는 동작 // SW 1번 누르면 동작, 다시 한 번 누르면 멈춤, 또 다시 한 번 누르면 동작하는 프로그램
{
	DDRG |= 0x10; // G4포트 출력 XXX1 XXXX
	DDRG &= ~0x01; // G0 포트 입력 XXXX XXX0
	//char v = 1;
	char mode = 0; // mode = 0: disable, mode = 1: active
	int t = 500;
	
	while(1) // sw 눌리기 전까진 waiting 상태여야 함, 한번만 sw 눌러도 while문 탈출
	{
		if(Check() == 1)
		{
			mode = 1;
			break;
		}
	}
	
	 // if(PING & 0x08), v = G그룹 3번 bit의 값 // 0x10, 0x08 등 이런 것을 Bit Mask라고 부름
	while (1) 
    {
		if(Check() == 1)
		{
			if(mode == 0)
			{
				mode = 1;
			}
			else
			{
				mode = 0;
			}
			_delay_ms(300); // 버튼을 눌렀을 때 mode 1, 즉 LED가 동작하고 있으면 멈추고 LED가 멈춰있으면 깜빡여준다 (상태전환)
		}
		
		if ( mode == 1) // mode 1은 LED가 깜빡이는 것을 설명
		{
		PORTG |= 0x10;
		_delay_ms(t);
		PORTG &= ~(0x10); // 해당 bit off
	    _delay_ms(t);
		if(Check_fast() == 1)
		{
			if(t>100)
			t -=100;
			_delay_ms(50);
		}
		if(Check_slow() == 1)
		{
			t += 100;
			_delay_ms(50);
		}
	    }
    }
	
}