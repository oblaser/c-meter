//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include "LCD.h"

void lcd_timer(char x) {
    lcd_tmr = x;
    while(lcd_tmr > 0);
}

void LCD_init(void)
{
    lcd_timer(15);
	LCD_send_byte(0b00110000);
	
    lcd_timer(5);
	LCD_send_byte(0b00110000);
	
    lcd_timer(1);
	LCD_send_byte(0b00110010);	
	LCD_send_byte(0b00101000);	//Function Set
	LCD_send_byte(0b10000000);	//Display OFF
	LCD_send_byte(0b00010000);	//Display Clear
	LCD_send_byte(0b00000110);	//Entrymode set
    LCD_send_byte(0b00001100);	//Entrymode set
   
    lcd_timer(10);
    LCD_define_char();
    LCD_disp_clear();
}

void LCD_send_byte(char b)
{
    //Das Byte wird in einzelne Bits aufgeteilt
    //Danach wird es im 4 Bit Modus auf das Display übertragen
	char b0 = (b & 0x01);
	char b1 = (b & 0x02)>>1;
	char b2 = (b & 0x04)>>2;
	char b3 = (b & 0x08)>>3;
	char b4 = (b & 0x10)>>4;
	char b5 = (b & 0x20)>>5;
	char b6 = (b & 0x40)>>6;
	char b7 = (b & 0x80)>>7;
	
	D_DB4 = 0;
	D_DB5 = 0;
	D_DB6 = 0;
	D_DB7 = 0;
	
	D_E = 1;
    
	D_DB4 = b4;
	D_DB5 = b5;
	D_DB6 = b6;
	D_DB7 = b7;
	D_E = 0;
    
    
	D_DB4 = 0;
	D_DB5 = 0;
	D_DB6 = 0;
	D_DB7 = 0;
	
	D_E = 1;
	D_DB4 = b0;
	D_DB5 = b1;
	D_DB6 = b2;
	D_DB7 = b3;
	D_E = 0;
	
	D_DB4 = 0;
	D_DB5 = 0;
	D_DB6 = 0;
	D_DB7 = 0;
	D_RS = 0;
}

void LCD_send_char(char ch)
{
    //Es wird ein Char an das Display gesendet
	D_RS = 1;
	LCD_send_byte(ch);
}

void LCD_clr(char zeile, char spalte, char anz) {
    
    LCD_disp_xy(zeile, spalte);
    
    for (int i = 0; i < anz; i++) LCD_send_char(' ');
}

void LCD_disp_clear(void)
{
    //Das Display wird mit Leerzeichen gefüllt
    char i = 0;
    int y = 0;

    LCD_disp_xy(0,0);
    for(i=0; i<40; i++)
    {
        LCD_send_char(0x20);
        if(i==19)
        {
            LCD_disp_xy(1,0);
           
        }
    }
}

void LCD_disp_xy(char zeile, char spalte)
{
	char addresse = 0;
	
	//Zeile 2?
	if(zeile == 1)
	{
		addresse = 0x40;	//Addresse wir auf die Zweite Zeile gesetzt
	}
	//Addresse wird um die Spaltenzahl addiert
	addresse = addresse + spalte;
	
	//Coursor auf die Addresse setzen
	addresse = addresse | 0x80;
	LCD_send_byte(addresse);
}
    
void LCD_define_char()
{
    //Definiert zusätzliche zeichen z.b ° (Grad Zeichen)
    
    // Variablen deklarieren
    char i;
    char j;

    // RAM Adresse auf 0
    // Siehe Datenblatt
    LCD_send_byte(0x40);

    // Alle 8 Linien schreiben
    for (i = 0; i < 8;i++)
    {
        for(j = 0; j < 8;j++)
        {
            LCD_send_char(zeichen[i][j]);
        }	
    }	
}
    
void LCD_send_text (unsigned char text[],char zeile, char spalte, char bundig)
{
    //Giebt einen Text an der Gewünschten Position auf dem Display aus
    unsigned char textlenght = 0;   //Textlaenge
    unsigned char n = 0;            //Zaehlvariable
    while(text[textlenght] != 0)
    {
        textlenght++;
    }
    if(bundig == 0)
    {
        LCD_disp_xy(zeile,spalte);
    }
    else
    {
        LCD_disp_xy(zeile,spalte-textlenght+1);
    }
    for(n=0;n<textlenght;n++)
    {
        
        LCD_send_char(text[n]);
    }
}
    