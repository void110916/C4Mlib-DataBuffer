#include "stdio.h"
#include "Bios.h" 
#include "M128Bios.h" 
#include "RemoBF.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define DBUFFER_DEPTH 8
#define VBUFFER_DEPTH 2



RemoBFStr_t RemoBF_str={.DataDepth=DBUFFER_DEPTH*4,.VariDepth=VBUFFER_DEPTH};
uint32_t RemoBF_DataList_p[DBUFFER_DEPTH]={0};/*Define Data Temp Array*/ 
RemoVari_t RemoBF_VariList_p[VBUFFER_DEPTH]={0};/*Define variable Temp Array*/
uint32_t A,B,C,D; // Define under test varialbes
int16_t A_RegId ,P_A_RegId,C_RegId,P_C_RegId;
int16_t P_C,P_D;



int main() {
	/*Reset Time interrupt period*/
	Pwm0HWSetData_uni.Str.CSn0_2 = TIM0_CLK_DIV_BY64;
	Pwm2HWSetData_uni.Str.CSn0_2 = TIM123_CLK_DIV_BY64;
    /*Setting up Section*/
    /*Setting up Timer0*/
    HardWareSet_lay(&Pwm0HWSet_str,Pwm0FlagPara_p,Pwm0RegPara_p,Pwm0HWSetData_uni.List);
	HardWareSet_step((void*)&Pwm0HWSet_str); 
    /*Setting up Timer2*/
    HardWareSet_lay(&Pwm2HWSet_str,Pwm2FlagPara_p,Pwm2RegPara_p,Pwm2HWSetData_uni.List);
	HardWareSet_step((void*)&Pwm2HWSet_str); 
    /*Setting up HMI*/
	C4M_STDIO_init();
    /*Layout Remo Buffer */   
	RemoBF_lay(&RemoBF_str,(uint8_t*)RemoBF_DataList_p,RemoBF_VariList_p);
    /*Registers A as  a remo_buffer register  */
    A_RegId=RemoBF_reg(&RemoBF_str,(void*)&A,4);
    printf("A was registered as a RemoBF0_str register with ID:%d\n",A_RegId);
    P_A_RegId=RemoBF_reg(&RemoBF_str,(void*)&A,4);
    printf("P_A was registered as a RemoBF0_str register with ID:%d\n",P_A_RegId);

    /*Registers C as  a remo_buffer register  */
    C_RegId=RemoBF_reg(&RemoBF_str,(void*)&C,4);
    printf("C was registered as a RemoBF0_str register with ID:%d\n",C_RegId); 
    P_C_RegId=RemoBF_reg(&RemoBF_str,(void*)&C,4);
    printf("C was registered as a RemoBF0_str register with ID:%d\n",P_C_RegId);  
    /*Polling Section */
	uint8_t  state=0;
	while(1){
   		if (state ==0){
			state=1;
			A=0x00000000;
			PROTECTED_EQUATION(P_A_RegId= 0x0000);
		}else{
			state=0;
			A=0xFFFFFFFF; // without extra protect 
			PROTECTED_EQUATION(P_A_RegId= 0xFFFF); //with extra protect 
		}
  	}
}
uint8_t Tim0State=0,temp0,HWREG;
uint32_t ByteCount=0;

ISR( TIMER0_OVF_vect){
	sei(); //allow interrupt 
	switch(Tim0State){
	case 0: //Remo Get A and save to B
		if(ByteCount==0) RemoBF_catch(&RemoBF_str,A_RegId);
		RemoBF_get(&RemoBF_str,A_RegId ,&temp0);
		REGPUT(&HWREG,1,&temp0);
		REGGET(&HWREG ,1, (uint8_t *)&B +ByteCount);// Simu Remo MCU action
		ByteCount++;
		if(ByteCount==4) {
			if(B !=0x00000000 && B != 0xFFFFFFFF  ) printf("A ERROR\n");// Simu Remo
			ByteCount=0;
			Tim0State =1;
		}
	case 1: // Access  B Remo Put C 
		REGPUT(&HWREG ,1, (uint8_t *)&B+ ByteCount);// Simu Remo MCU put
		REGGET(&HWREG,1,&temp0);
		RemoBF_put(&RemoBF_str,C_RegId ,temp0);
		ByteCount++;
		if(ByteCount==4) {
			RemoBF_dist(&RemoBF_str,C_RegId );
			ByteCount=0;
			Tim0State =2;
		}
	case 2://Remo Get P_A and save to B
		if(ByteCount==0) RemoBF_catch(&RemoBF_str,P_A_RegId);
		RemoBF_get(&RemoBF_str,P_A_RegId ,&temp0);
		REGPUT(&HWREG,1,&temp0);
		REGGET(&HWREG ,1, (uint8_t *)&B +ByteCount);// Simu Remo MCU action
		ByteCount++;
		if(ByteCount==4) {
			if(B !=0x00000000 && B != 0xFFFFFFFF ) printf("P_A ERROR\n");// Simu Remo
			ByteCount=0;
			Tim0State =3;
		}
	case 3: // Access  B Remo Put P_C 
		REGPUT(&HWREG ,1, (uint8_t *)&B +ByteCount);// Simu Remo MCU put
		REGGET(&HWREG,1,&temp0);
		RemoBF_put(&RemoBF_str,P_C_RegId ,temp0);
		ByteCount++;
		if(ByteCount==4) {
			RemoBF_dist(&RemoBF_str,P_C_RegId );
			ByteCount=0;
			Tim0State =0;
		}
	}
}

ISR( TIMER2_OVF_vect){
	sei(); //allow interrupt 
	D=C;
	cli();
	if(D!=0x00000000 && D!=0xFFFFFFFF ) printf("C ERROR  \n" );
	sei();
	PROTECTED_EQUATION(D=C);
	cli();
	if(D!=0x00000000 && D!=0xFFFFFFFF ) printf("Protected C ERROR  \n" );
	sei();
	P_D=P_C;
	cli();
	if(P_D!=0x00000000 && P_D!=0xFFFFFFFF ) printf("P_C ERROR  \n" );
	sei();
	PROTECTED_EQUATION(P_D=P_C);
	cli();
	if(P_D!=0x00000000 && P_D!=0xFFFFFFFF ) printf("Protected  P_C ERROR  \n" );
	sei();
}
