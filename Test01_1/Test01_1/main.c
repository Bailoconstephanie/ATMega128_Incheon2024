#include <avr/io.h> // AVR 기본 헤더
// LED Port : PG4

int main(void) // ATMega128에 LED를 연결하여 LED ON 시키는 동작
{
    /* Replace with your application code */
	// printf("hello world!"); // printf(): 콘솔 함수, ATMega128에는 콘솔이 없음 따라서 쓸 필요 없음
	DDRG |= 0x10; // G 포트 이기 때문에 G 인듯?, xxxx xxxx: 16진수를 2진수로 표현할 때 => G포트는 5개밖에 없으므로 XXX1 0000, 1 = 출력, 0 = 입력, 즉 4번비트(5번째)를 출력으로 만들었다라는 것
    while (1) 
    {
		PORTG |= 0x10;  // 원래 있던 값을 유지하기 위해서 |= (or equal) => 0,1,2,3번째는 그대로 나갈 것이고 4번째 비트
    }
}

