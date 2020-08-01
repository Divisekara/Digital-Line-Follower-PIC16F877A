/*
 * File:   newmain.c
 * Author: user
 *
 * Created on December 30, 2018, 11:24 PM
 */
#define _XTAL_FREQ 16000000
#define TMR2PRESCALE 4
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

long freq;
int PWM_Max_Duty()
{
    return(_XTAL_FREQ/(freq*TMR2PRESCALE));
}
PWM1_Init(long fre)
{
    PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;//register timer 2 modules period register
    freq = fre;
}
PWM2_Init(long fre)
{
    PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
    freq = fre;
}
PWM1_Duty(unsigned int duty)
{
    if(duty<1024);
    {
        duty = ((float)duty/1023)*PWM_Max_Duty();
        CCP1X = duty & 2;//compare capture PWM pin 17...store 1 st bit
        CCP1Y = duty & 1;//pin 16 store the 0th bit
        CCPR1L = duty>>2;//CCP register 1 low....store the remaining 8 bit
    }
}
PWM2_Duty(unsigned int duty)
{
    if(duty<1024);
    {
        duty = ((float)duty/1023)*PWM_Max_Duty();
        CCP2X = duty & 2; //pin 16
        CCP2Y = duty & 1;
        CCPR2L = duty>>2;
    }
}
PWM1_Start()
{
    CCP1M3 = 1;
    CCP1M2 = 1;
#if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
#elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
#elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
#endif
    TMR2ON = 1;
    TRISC2 = 0;
}
PWM1_Stop()
{
    CCP1M3 = 0;
    CCP1M2 = 0;
}
PWM2_Start()
{
    CCP2M3 = 1;
    CCP2M2 = 1;
#if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
#endif
    TMR2ON = 1;
    TRISC1 = 0;
}
PWM2_Stop()
{
    CCP2M3 = 0;
    CCP2M2 = 0;
}

void main(void) {
    TRISC=0;//output port c
    TRISD=0b11110000;//port D input and output
    TRISB=1;//port b output and input
    PWM1_Init(5000);
    PWM2_Init(5000);
    while(1){
         PWM1_Start();
        PWM2_Start();
        __delay_ms(20);
        RD3=1;                            //pin 2,7 and 10,15
        RD4=0;                           //logic 01-clockwise ....logic 10-anticlockwise
        RD1=1;
        RD2=0;
        PWM1_Start();//17
        PWM2_Start();//16
        PWM1_Duty(900);//right
        PWM2_Duty(865);//left
    }         
    return;
}
