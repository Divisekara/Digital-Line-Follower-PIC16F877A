#define sensors TRISB
#define s1 PORTB.F7
#define s2 PORTB.F6
#define s3 PORTB.F5
#define s4 PORTB.F4

#define motors TRISD
#define M_R_F PORTD.F1
#define M_R_B PORTD.F2
#define M_L_F PORTD.F3
#define M_L_B PORTD.F4
void forward () {
    PWM1_Set_Duty (220);
    PWM2_Set_Duty (220) ;}
void forwardd (){
    PWM1_Set_Duty (200);
    PWM2_Set_Duty (200) ;}
void right(){
    PWM1_Set_Duty (50);
    PWM2_Set_Duty (220) ;}
void rightt(){
    PWM1_Set_Duty (100);
    PWM2_Set_Duty(220) ;}
void left(){
    PWM1_Set_Duty(220);
    PWM2_Set_Duty(50) ;}
void leftt(){
    PWM1_Set_Duty(220);
    PWM2_Set_Duty(100) ;}
void stop(){
    PWM1_Set_Duty(0);
    PWM2_Set_Duty(0) ;}

void main(void) {
    TRISD=0x00;
    TRISC=0x00;
    TRISB=0xFF;
    PORTD=0; 
    PORTB=0; 
    PORTC=0;
    PWM1_Init (5000);
    PWM2_Init (5000);
    PWM1_Start ();
    PWM2_Start ();
    PWM1_Set_Duty (0);
    PWM2_Set_Duty (0);
    M_R_F=1;
    M_R_B=0;
    M_L_F=1;
    M_L_B=0;
    while (1) {
        if ((s3==1) &&(s2==1)){
            stop () ;}
        else {
            if ((s4==1)&&(s3==0)&&(s2==0)){
                while (1){
                    if ((s3==0) &&(s2==0)){
                        forwardd () ;}
                    else if ((s3==0)&&(s2==1)){
                        left () ;}
                    else if ((s3==1)&&(s2==0)){
                        right() ;}
                    else if ((s3==1)&&(s2==1)) {
                        while (1){
                            if ((s3==0)&&(s2==0)){
                                break ;}
                            else{
                                leftt() ;}
                        }
                        break ;}
                }
            }
            else if ((s1==1)&&(s3==0)&&(s2==0)){
                while (1){
                    if ((s3==0)&&(s2==0)){
                        forward () ;}
                    else if ((s3==0)&&(s2==1)){
                        left() ;}
                    else if ((s3==1)&&(s2==0)){
                        right() ;}
                    else if ((s3==1)&&(s2==1)){
                        while (1){
                            if ((s3==0)&&(s2==0)){
                                break ;}
                            else{
                                rightt() ;}
                        }
                        break ;}
                }
            }
            else {
                if ((PORTB.F5==0)&&(PORTB.F6==0)){
                    forward() ;}
                else if ((s3==0)&&(s2==1)){
                    left () ;}
                else if ((s3==1)&&(s2==0)){
                    right () ;}
                else {
                    stop () ;}
            }
        }
    }
}

