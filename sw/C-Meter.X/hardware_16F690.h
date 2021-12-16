/* 
 * Author: Oliver Blaser
 *
 * Date: 01.03.2016
 * 
 */

#ifndef HARDWARE_16F690_H
#define	HARDWARE_16F690_H

#include <pic16f690.h>
#include <xc.h>
#include "LCD.h"
#include "EUSART.h"

//------------------------------------------------------------------------------
// Defines (Projekt)
//------------------------------------------------------------------------------

#define COMP            C2OUT
#define Taster_L        PORTBbits.RB4   // Layout: Taster_2
#define Taster_R        PORTCbits.RC2   // Layout: Taster_1
#define T_menu          Taster_L
#define T_set           Taster_R

#define LED             PORTAbits.RA1

/**
 * 1: Charge 0: Discharge
 */
#define CHG_DSC         PORTAbits.RA2   // 1: Charge 0: Discharge

#define INP_COMP        0x01
#define INP_TL          0x02
#define INP_TR          0x04
#define RX_IDLE         0x08

#define T_MENU          INP_TL
#define T_SET           INP_TR

#define TRESHOLD_TL     20
#define TRESHOLD_TR     20

#define S_START         0x01
#define S_ONE_M         0x02
#define S_AVG_M         0x04    // !!! Calibrate
#define S_CON_M         0x08    // CONTINOUS
#define S_MENU          0x10
#define S_UART          0x20    // UART monitor

#define R_MEAS          1000000 // 1MR
#define us_OVERFLOW     16384   // 250ns * 65536 = 16.384ms = 16384us

#define X               17

//------------------------------------------------------------------------------
// Variablen (global)
//------------------------------------------------------------------------------

// timers
unsigned int tmr_led;
unsigned int tmr_measure;

// input
unsigned char inp;
unsigned char inp_alt;
unsigned char inp_neu;  // entprellte Eingänge
unsigned char inp_pos;  // positive Flanke
unsigned char inp_neg;  // negative Flanke
unsigned char inp_cnt_tl;
unsigned char inp_cnt_tr;

bit led_en;
unsigned char state;
unsigned char menu_point;

// Messung
unsigned short long cnt_tmr_of;
unsigned int tmr1_val;
unsigned int tmr1_val_l;
unsigned int tmr1_val_h;
bit _meas_done;
unsigned long tau;
unsigned short long cap_pF;
unsigned char cap[11];
bit mes_send_en;


//------------------------------------------------------------------------------
// Funktionen
//------------------------------------------------------------------------------

void HW_init();

void SW_init();

void GIE_set();

void input_handler();

unsigned char measure();

void cap_to_string(unsigned short long f_cap_pF);

#endif	/* HARDWARE_16F690_H */
