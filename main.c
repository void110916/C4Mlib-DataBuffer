#include "stdio.h"
#include "M128Bios.h"
/*
int main(){
    C4M_STDIO_init();
    //Pwm3HWSetData_uni.Str.CSn0_2=TIM16_CLK_DIV_BY8;
    HardWareSet_lay(&Pwm1HWSet_str,Pwm1FlagPara_p,Pwm1RegPara_p,Pwm1HWSetData_uni.List);
    HardWareSet_step((void*)&Pwm1HWSet_str); 
    uint16_t Witdth;
    
    while(1){
        printf("Please Provide New PWM Pusle Width?\n");
        scanf("%d",&Witdth);
        REGPUT(Pwm1Op_str.WidthAReg_p, Pwm1Op_str.WidthABytes, &Witdth);
    }   
}
*/




int main()
{
    C4M_STDIO_init();
    int TimerOn = 1;
    uint8_t One = 1, Zero=0;
    HardWareSet_lay(&Tim1HWSet_str, Tim1FgGpData_str, Tim1RegPara_p, Tim1HWSetData_uni.List);
    HardWareSet_step((void *)&Tim1HWSet_str);

     while (1)
    {
        
        printf("Ture on or off TIM?\n");
        scanf(" %d",&TimerOn);
        if (TimerOn == 0)
        {
            printf("turn off\n");
            REGFPT(Tim1Op_str.StopReg_p,Tim1Op_str.StopMask,Tim1Op_str.StopShift,One);
        }
        else
        {
            printf("turn on\n");
            REGFPT(Tim1Op_str.StartReg_p,Tim1Op_str.StartMask,Tim1Op_str.StartShift,Zero);
        }
    }
}

