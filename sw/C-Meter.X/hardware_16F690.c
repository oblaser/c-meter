/* 
 * Author: Oliver Blaser
 *
 * Date: 01.03.2016
 * 
 */

#include "hardware_16F690.h"

//------------------------------------------------------------------------------
// Config
//------------------------------------------------------------------------------

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

//------------------------------------------------------------------------------
// Funktionen
//------------------------------------------------------------------------------

void HW_init() {
    
    //--------------------------------
    // 3.0 Clock Sources 47
    //--------------------------------
    
    OSCCON  = 0b00001000;   // external OSC (16MHz)
    OSCTUNE = 0b00000000;
    
    //--------------------------------
    // 4.0 I/O PORTs 49
    //--------------------------------
    
    PORTA = 0b00000000;
    TRISA = 0b11111001;     // 0:Out 1:In
    WPUA  = 0b00000000;     // PullUp's: 0:disabled 1:enabled
    IOCA  = 0b00000000;     // Interrupt on change: 0:disabled 1:enabled
    
    PORTB = 0b00000000;
    TRISB = 0b10111111;     // 0:Out 1:In
    WPUB  = 0b00000000;     // PullUp's: 0:disabled 1:enabled
    IOCB  = 0b00000000;     // Interrupt on change: 0:disabled 1:enabled
    
    TRISC = 0b00000111;     // 0:Out 1:In
    PORTC = 0b00000000;
    
    //--------------------------------
    // 5.0 Timer0 72
    //--------------------------------
    
    OPTION_REG = 0b11010100;    // CS = Fosc/4 PS = 1:32    by Fosc = 16MHz
    TMR0       = 0b00000000;
    
    //--------------------------------
    // 6.0 Timer1 75
    //--------------------------------
    
    T1CON = 0b00000001;     // CS = Fosc/4 PS = 1:1  => f= 4MHz T= 250ns
    TMR1H = 0x00;
    TMR1L = 0x00;
    
    //--------------------------------
    // 7.0 Timer2 79
    //--------------------------------
    
    T2CON = 0b00000000;     // timer2 is off
    
    //--------------------------------
    // 8.0 Comparator 83
    //--------------------------------
    
    CM1CON0 = 0b00000000;   // Comp1 disabled
    CM2CON0 = 0b10000001;   // not invertd
    
    //--------------------------------
    // 9.0 ADC 98
    //--------------------------------
    
    ANSEL  = 0b00100000;    // AN5 analog (Comp2) others digital
    ANSELH = 0b00000000;    // digital
    
    ADCON0 = 0b00000000;    // ADC off
    ADCON1 = 0b00000000;
    
    //--------------------------------
    // 10.0 EEPROM 107
    //--------------------------------
    
    // needs no changes
    
    //--------------------------------
    // 11.0 ECCP+ 115
    //--------------------------------
    
    // needs no changes
    
    //--------------------------------
    // 12.0 EUSART 134
    //--------------------------------
    
    // #include "EUSART.h"
    
    //--------------------------------
    // 13.0 SSP 158
    //--------------------------------
    
    // needs no changes
    
    //--------------------------------
    // 14.3 Interrupt 187
    //--------------------------------
    
    INTCON  = 0b01100000;    // Peripheral Timer0
    PIE1    = 0b00000001;    // Timer1
    PIE2    = 0b01000000;    // Comp2
    PIR1    = 0b00000000;
    PIR2    = 0b00000000;
    
    //--------------------------------
    // 14.5 WDT 190
    //--------------------------------
    
    // needs no changes
}

void SW_init() {
    
    // timers
    tmr_led = 0;
    tmr_measure = 0;
    
    // input
    inp_neu = 0;
    inp_pos = 0;
    inp_neg = 0;
    
    inp_alt = 0;
    if(COMP) inp_alt |= INP_COMP;
    if(Taster_L) inp_alt |= INP_TL;
    if(Taster_R) inp_alt |= INP_TR;
    
    inp_cnt_tl = TRESHOLD_TL / 2;
    inp_cnt_tr = TRESHOLD_TR / 2;
    
    led_en = 1;
    state = S_START;
    
    // Messung
    cnt_tmr_of = 0;
    tmr1_val = 0;
    mes_send_en = 0;
}

void GIE_set() {
    GIE = 1;
}

void input_handler() {
    
    // entprellen
    if(Taster_L == 1 && inp_cnt_tl < TRESHOLD_TL) inp_cnt_tl++;
    if(Taster_L == 0 && inp_cnt_tl > 0) inp_cnt_tl--;
    
    if(inp_cnt_tl >= TRESHOLD_TL) inp |= INP_TL;
    if(inp_cnt_tl <= 0) inp &= ~INP_TL;
    
    if(Taster_R == 1 && inp_cnt_tr < TRESHOLD_TR) inp_cnt_tr++;
    if(Taster_R == 0 && inp_cnt_tr > 0) inp_cnt_tr--;
    
    if(inp_cnt_tr >= TRESHOLD_TR) inp |= INP_TR;
    if(inp_cnt_tr <= 0) inp &= ~INP_TR;
    
    // neu werte
    inp_neu = 0;
    
    inp_neu |= (inp & INP_TL);
    inp_neu |= (inp & INP_TR);
    
    if(COMP) inp_neu |= INP_COMP;
    else inp_neu &= ~INP_COMP;
    
    if(rx_idle) inp_neu |= RX_IDLE;
    else inp_neu &= ~RX_IDLE;
    
    // flanken
    inp_pos = ~inp_alt & inp_neu;
    inp_neg = inp_alt & ~inp_neu;
    
    // input werte in alt speichern
    inp_alt = inp_neu;
}

unsigned char measure() {
    
    unsigned short long f_tau = 0;
    
    if(led_en) LED = 0;
    while(tmr_measure);
    if(led_en) LED = 1;
    
    // entladen
    CHG_DSC = 0;
    tmr_measure = 40;   // 10uF * 330R * 5 = 16.5ms
    while(tmr_measure);
    
    // LED blink
    if(led_en) {
        LED = 0;
        tmr_measure = 100;
        while(tmr_measure);
        LED = 1;
    }
    
    // Messung starten
    TMR1ON = 1;
    _meas_done = 1;
    cnt_tmr_of = 0;
    TMR1L = 0x00;
    TMR1H = 0x00;
    CHG_DSC = 1;
    
    // warten bis messung gemacht
    while(_meas_done) {
        
        // C zu gross
        if(cnt_tmr_of > 760) {   // 760 * 16.384ms = 12.45s => Cmax = 12.44uF
            return 0;
        }
        
        // Taster menue gedrückt
        if(!T_menu) {
            state = S_MENU;
            menu_point = 0;
            tmr_measure = 100;
            while(tmr_measure);
            return 0;
        }
    }
    
    // rechnen
    tmr1_val = tmr1_val_h;
    tmr1_val <<= 8;
    tmr1_val |= tmr1_val_l;
    
    // tau [ns] = (tmr1_val * 0.25) + (cnt_tmr_of * us_OVERFLOW)
    // C = tau/R_MEAS
    
    f_tau = (tmr1_val / 4) + (cnt_tmr_of * us_OVERFLOW);
    
    cap_pF = f_tau;
    
    CHG_DSC = 0;
    tmr_measure = 0;
    
    if(led_en) LED = 0;
    
    return 1;
}

void cap_to_string(unsigned short long f_cap_pF) {
    
    // bis 9pF
    if(f_cap_pF < 10) {
        
        cap[0] = ' ';
        cap[1] = ' ';
        cap[2] = ' ';
        cap[3] = (f_cap_pF % 10) + 0x30;
        
        cap[4] = ' ';
        cap[5] = 'p';
        cap[6] = 'F';
        cap[7] = '\0';
    }
    
    // bis 99pF
    else if(f_cap_pF < 100) {
        
        cap[0] = ' ';
        cap[1] = ' ';
        cap[2] = ((f_cap_pF / 10) % 10) + 0x30;
        cap[3] = (f_cap_pF % 10) + 0x30;
        
        cap[4] = ' ';
        cap[5] = 'p';
        cap[6] = 'F';
        cap[7] = '\0';
    }
    
    // bis 999pF
    else if(f_cap_pF < 1000) {
        
        cap[0] = ' ';
        cap[1] = ((f_cap_pF / 100) % 10) + 0x30;
        cap[2] = ((f_cap_pF / 10) % 10) + 0x30;
        cap[3] = (f_cap_pF % 10) + 0x30;
        
        cap[4] = ' ';
        cap[5] = 'p';
        cap[6] = 'F';
        cap[7] = '\0';
    }
    
    // bis 9.99nF
    else if(f_cap_pF < 10000) {
        
        cap[0] = ((f_cap_pF / 1000) % 10) + 0x30;
        cap[1] = '.';
        cap[2] = ((f_cap_pF / 100) % 10) + 0x30;
        cap[3] = ((f_cap_pF / 10) % 10) + 0x30;
        
        cap[4] = ' ';
        cap[5] = 'n';
        cap[6] = 'F';
        cap[7] = '\0';
    }
    
    // bis 99.9nF
    else if(f_cap_pF < 100000) {
        
        cap[0] = ((f_cap_pF / 10000) % 10) + 0x30;
        cap[1] = ((f_cap_pF / 1000) % 10) + 0x30;
        cap[2] = '.';
        cap[3] = ((f_cap_pF / 100) % 10) + 0x30;
        
        cap[4] = ' ';
        cap[5] = 'n';
        cap[6] = 'F';
        cap[7] = '\0';
    }
    
    // bis 999nF
    else if(f_cap_pF < 1000000) {
        
        cap[0] = ' ';
        cap[1] = ((f_cap_pF / 100000) % 10) + 0x30;
        cap[2] = ((f_cap_pF / 10000) % 10) + 0x30;
        cap[3] = ((f_cap_pF / 1000) % 10) + 0x30;
        
        cap[4] = ' ';
        cap[5] = 'n';
        cap[6] = 'F';
        cap[7] = '\0';
    }
    
    // bis 9.99uF
    else if(f_cap_pF < 10000000) {
        
        cap[0] = ((f_cap_pF / 1000000) % 10) + 0x30;
        cap[1] = '.';
        cap[2] = ((f_cap_pF / 100000) % 10) + 0x30;
        cap[3] = ((f_cap_pF / 10000) % 10) + 0x30;
        
        cap[4] = ' ';
        cap[5] = 'u';
        cap[6] = 'F';
        cap[7] = '\0';
    }
    
    // bis 15.9uF
    else if(f_cap_pF < 16000000) {
        
        cap[0] = ((f_cap_pF / 10000000) % 10) + 0x30;
        cap[1] = ((f_cap_pF / 1000000) % 10) + 0x30;
        cap[2] = '.';
        cap[3] = ((f_cap_pF / 100000) % 10) + 0x30;
        
        cap[4] = ' ';
        cap[5] = 'u';
        cap[6] = 'F';
        cap[7] = '\0';
    }
    
    else {
        
        cap[0] = 'c';
        cap[1] = 'a';
        cap[2] = 'l';
        cap[3] = 'i';
        cap[4] = 'b';
        cap[5] = 'r';
        cap[6] = 'a';
        cap[7] = 't';
        cap[8] = 'e';
        cap[9] = '!';
        cap[10] = '\0';
    }
}

//------------------------------------------------------------------------------
// Interrupt
//------------------------------------------------------------------------------

interrupt void iupt() {
    
    // Timer0 1ms
    if(T0IE && T0IF) {
        
        if(lcd_tmr) lcd_tmr--;
        if(tmr_led) tmr_led--;
        if(tmr_measure) tmr_measure--;
        
        TMR0 = 130;
        T0IF = 0;
    }
    
    // Timer1 250ns * 65536
    if(T1IE && T1IF) {
        
        cnt_tmr_of++;
        
        T1IF = 0;
    }
    
    // COMP 2
    if(C2IE && C2IF) {
        
        tmr1_val_l = TMR1L;
        tmr1_val_h = TMR1H;
        TMR1ON = 0;
        
        _meas_done = 0;
        
        C2IF = 0;
    }
    
    // UART TX
    if(TXIE && TXIF) TX_interrupt();

    // UART RX
    if(RCIE && RCIF) RX_interrupt();
}