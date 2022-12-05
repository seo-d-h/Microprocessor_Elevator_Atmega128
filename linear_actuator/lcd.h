#ifndef _INCLUDE_LCD_H__
#define _INCDLUE_LCD_H__
/*****************************************************************************/
/************************       lcd.h  ***************************************/
/*****************************************************************************/

#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_WDATA   PORTA        // LCD ������ ���� ���� (������ ����)
#define LCD_WINST   PORTA        // LCD ������ ���� ���� (��ɾ� ����)
#define LCD_RDATA   PINA         // LCD ������ ���� ���� (������ �б�)

#define LCD_CTRL    PORTG        // LCD ���� ��ȣ ����
#define LCD_EN  0                // Enable ��ȣ
#define LCD_RW  1                // �б�(1)/����(0)
#define LCD_RS  2                // ������(1)/��ɾ�(0)

#define RIGHT 1                  // Ŀ�� �� ȭ�� �̵� ������ ���� ����
#define LEFT 0                   // Ŀ�� �� ȭ�� �̵� ���� ���� ����

//void LCD_Data(unsigned char ch);	
//void LCD_Comm(unsigned char command);
//void LCD_Delay(unsigned char ms);		
//void LCD_Char(unsigned char ch);
//void LCD_Str(unsigned char *str);
//void LCD_Pos(unsigned char x, unsigned char y);
//void LCD_Clear(void);		
//void LCD_PORT_Init(void);
//void LCD_Init(void);
//void LCD_Display_Shift(unsigned char p);	
//void LCD_Cursor_Shift(unsigned char p);		
//void LCD_Cursor_Home(void);
//void LCD_Cursor_Shift(void);

void LCD_Data(unsigned char ch)
{
    LCD_CTRL |= (1 << LCD_RS);    // RS=1, =0���� ������ ���� ����Ŭ
    LCD_CTRL &= ~(1 << LCD_RW);    
    LCD_CTRL |= (1 << LCD_EN);    // LCD Enable
    _delay_us(50);                   // �ð�����
    LCD_WDATA = ch;                 // ������ ���
    _delay_us(50);                   // �ð�����
    LCD_CTRL &= ~(1 << LCD_EN);     // LCD Disable
}

void LCD_Comm(unsigned char command)
{
    LCD_CTRL &= ~(1 << LCD_RS);     // RS==0���� ��ɾ� ���� ����Ŭ
    LCD_CTRL &= ~(1 << LCD_RW);    
    LCD_CTRL |= (1 << LCD_EN);      // LCD Enable 
    _delay_us(50);                   // �ð�����
    LCD_WINST = command;            // ��ɾ� ����
    _delay_us(50);                   // �ð�����
    LCD_CTRL &= ~(1 << LCD_EN);     // LCD Disable
}

void LCD_Delay(unsigned char ms)
{
    for(int i=0;i<ms;i++)
        _delay_ms(1);
}

void LCD_Char(unsigned char ch)          // �� ���� ���
{
    LCD_Delay(1);
    LCD_Data(ch);
}

void LCD_Str(unsigned char *str)        // ���ڿ� ���
{
    while(*str != 0) {
        LCD_Char(*str);
        str++;
    }
}

void LCD_Pos(unsigned char x, unsigned char y)  // LCD ������ ����, x�� y�� ��� ���� �ǹ���.
{
    LCD_Comm(0x80|(x*0x40+y));                  // x = ������(0, 1), y = ���ο�(0-15)
}

void LCD_Clear(void)    // ȭ�� Ŭ���� (1)
{
    LCD_Comm(0x01);
    LCD_Delay(2);
}

void LCD_PORT_Init(void)
{
    DDRA  = 0xFF;        // PORTA�� �������
    DDRG |= 0x0F;        // PORTG�� ���� 4��Ʈ�� �������
}

void LCD_Init(void)     // LCD �ʱ�ȭ
{
    LCD_PORT_Init();
    
    LCD_Comm(0x38);     // DDRAM, ������ 8��Ʈ���, LCD 2���� ��� (6)
    LCD_Delay(4);       // 4ms ����
    LCD_Comm(0x38);     // DDRAM, ������ 8��Ʈ���, LCD 2���� ��� (6)        
    LCD_Delay(4);       // 4ms ����
    LCD_Comm(0x38);     // DDRAM, ������ 8��Ʈ���, LCD 2���� ��� (6)
    LCD_Delay(4);       // 4ms ����
    LCD_Comm(0x0e);     // Display ON/OFF
    LCD_Delay(2);       // 2ms ����        
    LCD_Comm(0x06);     // �ּ�+1 , Ŀ���� ���� �̵� (3)
    LCD_Delay(2);       // 2ms ����        
    LCD_Clear();        // LCD ȭ�� Ŭ����
}

void LCD_Display_Shift(unsigned char p)
{
    if(p==RIGHT){
        LCD_Comm(0x1c);
        LCD_Delay(1); // �ð�����
    }
    //ǥ�� ȭ�� ��ü�� �������� �̵�
    else if(p == LEFT) {
        LCD_Comm(0x18);
        LCD_Delay(1);
    }
}

void LCD_Cursor_Shift(unsigned char p)
{
        if(p == RIGHT) {
                LCD_Comm(0x14);
                LCD_Delay(1);
        }
        else if(p == LEFT) {
                LCD_Comm(0x10);
                LCD_Delay(1);
        }
}

void LCD_Cursor_Home(void)
{
    LCD_Comm(0x02);
    LCD_Delay(2);
}

#endif 