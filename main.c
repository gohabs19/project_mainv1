// filename ******** Main.C **************
//***********************************************************************
// Simple ADC example for the Technological ArtsEsduinoXtreme board
// by Carl Barnes, 12/03/2014
//***********************************************************************
#include <hidef.h> /* common defines and macros */
#include "derivative.h" /* derivative information */
#include "SCI.h"
char string[20];
signed short val;
unsigned int sign;//0 for negative, 1 for positive
double g = 9.81;
void msDelay(unsigned int);
//---------------------OutCRLF---------------------
// Output a CR,LF to SCI to move cursor to a new line
// Input: none
// Output: none
// Toggle LED each time through the loop
void OutCRLF(void){
 SCI_OutChar(CR);
 SCI_OutChar(LF);
 PTJ ^= 0x20; // toggle LED D2
}
void main(void) {
// Setup and enable ADC channel 0
// Refer to Chapter 14 in S12G Reference Manual for ADCsubsystem details

 ATDCTL1 = 0x4F; // set for 12-bit resolution
 ATDCTL3 = 0x88; // right justified, one sample persequence
 ATDCTL4 = 0x02; // prescaler = 2; ATD clock =6.25MHz / (2 * (2 + 1)) == 1.04MHz
 ATDCTL5 = 0x20; // continuous conversion on channel0

// Configure Timer for PWM on channel 0 (uncomment belowfor milestone 2)
// PWMCTL= 0x??
// PWMCLK= 0x??
// PWMCLKAB= 0x??
// PWMPRCLK= 0x??
// PWME= 0x??
// Configure PWM preoperties (uncomment below for milestone2)
// PWMPOL= 0x??
// PWMPER0= ?
// PWMCAE= 0x??
// PWMDTY0= ?
// Setup LED and SCI
 DDRJ |= 0x01; // PortJ bit 0 is output to LED D2 onDIG13
 SCI_Init(9600);


 for(;;) {
   PTJ ^= 0x01; // toggle LED

   ATDCTL5 = 0x24; // continuous conversion on channel4
   val=ATDDR0;
   SCI_OutString("x:");
   SCI_OutUDec(val);
                                                    
   SCI_OutChar(',');

   ATDCTL5 = 0x25; // continuous conversion on channel5
   val=ATDDR0;
   SCI_OutString(",y:");
   if (val>=1330) {
       val=val-1330;
       sign=1;
   } 
   else {
       val=1330-val;
       sign=0;           
   }
   //val=val;
   SCI_OutUDec(val);
   SCI_OutString("   Sign:");
   SCI_OutUDec(sign);
   OutCRLF();

   //SCI_OutString("Ben Stephens 400135219");
   //OutCRLF();

   msDelay(500); // 1 sec delay, you can validate usingmethod outlined in Lecture W8-2_W8-3
  }
}
void msDelay(unsigned int time)
{
 unsigned int j,k;
 for(j=0;j<time;j++)
 for(k=0;k<1033;k++);
}
