#ifndef UART1_H_
#define UART1_H_

void UART_1_init(void);		//초기화
void UART1_transmit(char data);		//송신
unsigned char UART1_receive(void);		//수신
void UART1_print_string(char* str);		//문자열 출력
void UART1_print_1_byte_number(uint8_t n);		//1바이트 크기 정수 출력

#endif