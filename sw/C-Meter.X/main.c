/* 
 * Author: Oliver Blaser
 *
 * Date: 01.03.2016
 * 
 */

#include "hardware_16F690.h"

void main() {
    
    unsigned char state_alt;
    unsigned char do_once;
    unsigned short long acc_cor = 55;
    
    HW_init();
    SW_init();
    EUSART_init();
    GIE_set();
    LCD_init();
    
    while(1) {
        
        input_handler();
        
        switch(state) {
            
            case S_START:
                LED = 1;
                LCD_send_text("C-Meter", 0, 0, 0);
                LCD_send_text("by Oli", 1, 15, 1);
                tmr_led = 2000;
                while(tmr_led);
                LCD_clr(0, 0, 16);
                LCD_clr(1, 0, 16);
                do_once = 0xFF;
                state = S_CON_M;
                break;
            
            /*case S_ONE_M:
                
                if(do_once & S_ONE_M) {
                    
                    LCD_clr(0, 0, 16);
                    LCD_send_text("ONE", 0, 0, 0);
                    LCD_clr(1, 0, 16);
                    
                    state_alt = S_ONE_M;
                    
                    do_once |= S_START;
                    do_once &= ~S_ONE_M;
                    do_once |= S_AVG_M;
                    do_once |= S_CON_M;
                    do_once |= S_MENU;
                    do_once |= S_UART;
                }
                
                if(inp_neg & T_MENU) state = S_MENU;
                
                if(inp_neg & T_SET) {
                    
                    LCD_clr(1, 0, 16);
                    LCD_send_text("measureing...", 1, 0, 0);
                    
                    if(measure()) {
                        cap_to_string(cap_pF - acc_cor);
                        LCD_clr(1, 0, 16);
                        LCD_send_text(cap, 1, 10, 1);
                    }
                    
                    else {
                        LCD_clr(1, 0, 16);
                        LCD_send_text("> 12.4uF", 1, 11, 1);
                    }
                }
                
                break;*/
            
            case S_AVG_M:   // calibrate
                
                if(do_once & S_AVG_M) {
                    
                    LCD_clr(0, 0, 16);
                    LCD_send_text("CAL", 0, 0, 0);
                    LCD_send_text("typ 55p", 0, 15, 1);
                    LCD_clr(1, 0, 16);
                    LCD_send_text("Let open!", 1, 0, 0);
                    
                    state_alt = S_AVG_M;
                    
                    do_once |= S_START;
                    do_once |= S_ONE_M;
                    do_once &= ~S_AVG_M;
                    do_once |= S_CON_M;
                    do_once |= S_MENU;
                    do_once |= S_UART;
                }
                
                if(inp_neg & T_MENU) state = S_MENU;
                
                if(inp_neg & T_SET) {
                    
                    LCD_clr(1, 0, 16);
                    LCD_send_text("calibrateing...", 1, 0, 0);
                    
                    if(measure()) {
                        acc_cor = cap_pF;
                        cap_to_string(acc_cor);
                        LCD_clr(1, 0, 16);
                        LCD_send_text(cap, 1, 10, 1);
                    }
                    
                    else {
                        LCD_clr(1, 0, 16);
                        LCD_send_text("touch connector-", 1, 0, 0);
                        tmr_measure = 3000;
                        while(tmr_measure);
                        LCD_clr(1, 0, 16);
                        LCD_send_text("bottom and retry", 1, 0, 0);
                        tmr_measure = 3000;
                        while(tmr_measure);
                            
                        
                        LCD_clr(1, 0, 16);
                        LCD_send_text("Let open!", 1, 0, 0);
                    }
                }
                
                break;
            
            case S_CON_M:
                
                if(do_once & S_CON_M) {
                    
                    LCD_clr(0, 0, 16);
                    LCD_send_text("CON", 0, 0, 0);
                    LCD_clr(1, 0, 16);
                    
                    state_alt = S_CON_M;
                    
                    do_once |= S_START;
                    do_once |= S_ONE_M;
                    do_once |= S_AVG_M;
                    do_once &= ~S_CON_M;
                    do_once |= S_MENU;
                    do_once |= S_UART;
                }
                
                if(inp_neg & T_MENU) state = S_MENU;
                
                if(measure()) {
                    cap_to_string(cap_pF - acc_cor);
                    LCD_clr(1, 0, 16);
                    LCD_send_text(cap, 1, 10, 1);
                    if(mes_send_en) UART_send(cap);
                }

                else {
                    LCD_clr(1, 0, 16);
                    LCD_send_text("> 12.4uF", 1, 11, 1);
                    if(mes_send_en) UART_send("> 12.4uF");
                }
                
                break;
            
            case S_UART:
                
                if(do_once & S_UART) {
                    
                    LCD_clr(0, 0, 16);
                    LCD_send_text("UART", 0, 0, 0);
                    LCD_send_text("9600 81N", 0, 15, 1);
                    LCD_clr(1, 0, 16);
                    
                    state_alt = S_UART;
                    
                    do_once |= S_START;
                    do_once |= S_ONE_M;
                    do_once |= S_AVG_M;
                    do_once |= S_CON_M;
                    do_once |= S_MENU;
                    do_once &= ~S_UART;
                }
                
                if(inp_neg & T_MENU) state = S_MENU;
                
                if(RX_READY) {
                    rx_data[16] = '\0';
                    LCD_clr(1, 0, 16);
                    LCD_send_text(rx_data, 1, 0, 0);
                    RX_READY = 0;
                }
                
                break;
                
            case S_MENU:
                
                if(do_once & S_MENU) {
                    
                    LCD_clr(0, 0, 16);
                    LCD_send_text("MENU", 0, 0, 0);
                    LCD_clr(1, 0, 16);
                    
                    menu_point = 0;
                    
                    do_once |= S_START;
                    do_once |= S_ONE_M;
                    do_once |= S_AVG_M;
                    do_once |= S_CON_M;
                    do_once &= ~S_MENU;
                    do_once |= S_UART;
                }
                
                if(inp_neg & T_MENU) menu_point++;
                
                switch(menu_point) {
                    
                    case 0:
                        LCD_send_text("Exit            ", 1, 0, 0);
                        if(inp_neg & T_SET) state = state_alt;
                        break;
                    
                    case 1:
                        LCD_send_text("Continous       ", 1, 0, 0);
                        if(inp_neg & T_SET) state = S_CON_M;
                        break;
                    
                    case 2:
                        menu_point++;
                        /*LCD_send_text("One measure     ", 1, 0, 0);
                        if(inp_neg & T_SET) state = S_ONE_M;*/
                        break;
                    
                    case 3:
                        LCD_send_text("UART monitor    ", 1, 0, 0);
                        if(inp_neg & T_SET) state = S_UART;
                        break;
                        
                    case 4:
                        LCD_send_text("State LED    ", 1, 0, 0);
                        if(led_en) LCD_send_text(" on", 1, 15, 1);
                        else LCD_send_text("off", 1, 15, 1);
                        
                        if(inp_neg & T_SET) {
                            led_en = ~led_en;
                        }
                        break;
                    
                    case 5:
                        LCD_send_text("Send measure ", 1, 0, 0);
                        if(mes_send_en) LCD_send_text(" on", 1, 15, 1);
                        else LCD_send_text("off", 1, 15, 1);
                        
                        if(inp_neg & T_SET) {
                            mes_send_en = ~mes_send_en;
                        }
                        break;
                        
                    case 6:
                        LCD_send_text("Cal   ", 1, 0, 0);
                        cap_to_string(acc_cor);
                        cap[4] = cap[5];
                        cap[5] = 'F';
                        LCD_send_text(cap, 1, 10, 0);
                        LCD_send_text("now:", 1, 6, 0);
                        if(inp_neg & T_SET) state = S_AVG_M;
                        break;
                        
                    default:
                        menu_point = 0;
                        break;
                }
                
                break;
                
            default:
                state = S_START;
                break;
        }
        
        // state LED
        if(tmr_led == 0) {
            
            if(led_en) {
                LED = ~LED;
                tmr_led = 200;
            }
            else LED = 0;
        }
    }
}
