/*
 * TODO
 * 
 * nach GIE=1:
LCD_Init();
 * 
 * 
 * in 1ms-interrupt einfügen:

if(lcd_tmr) lcd_tmr--;

 * 
 */

#ifndef LCD_H
#define LCD_H

#include <xc.h>

#define D_RS    PORTCbits.RC5
#define D_E     PORTCbits.RC4
#define D_DB4   PORTCbits.RC3
#define D_DB5   PORTCbits.RC6
#define D_DB6   PORTCbits.RC7
#define D_DB7   PORTBbits.RB6

char lcd_tmr;
void lcd_timer(char x);

//Array fuer LCD_define_char
char const zeichen[8][8] =
{
	{0x0E, 0x0A, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00},		// Grad 
	{0x11, 0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x00},		// Ae Umlaut
	{0x11, 0x0E, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00},		// Oe Umlaut
	{0x0A, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00},		// oe Umlaut
	{0x0A, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00},		// Ue Umlaut
	{0x0A, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0D, 0x00},		// ue Umlaut
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},		// Reserved
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}		// Reserved
    
};



/**
 * Initialisiert das LCD
 */
void LCD_init(void);

/**
 * Sendet einen Char an das Display
 * @param ch Der zu sendende Char
 */
void LCD_send_char(char ch);

void LCD_clr(char zeile, char spalte, char anz);

/**
 * Sendet ein Byte an das Display
 * @param b Das zu sendende Byte
 */
void LCD_send_byte(char b);

/**
 * Löscht das Display
 */
void LCD_disp_clear(void);

/**
 * Setzt den Cursor auf die gewälte position
 * @param zeile
 * @param spalte
 */
void LCD_disp_xy(char zeile, char spalte);

/**
 * Initialisiert die Umlaute auf dem Display
 */
void LCD_define_char(void);

/**
 * Sendet ein Text an der Angegebenen Position und ist wie gewählt formatiert
 * @param text 
 * @param zeile 0 = erste Zeile, 1 = zweite Zeile
 * @param spalte 0-19
 * @param bundig 0 = Linksbuendig, 1 = Rechtsbuendig
 */
void LCD_send_text (unsigned char text[],char zeile, char spalte, char bundig);

#endif //LCD_H
