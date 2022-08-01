#include <wchar.h>

extern int Init_task3JoinThreads();
extern int recVarsToTask3();
extern int recVarsToTask2();
extern int recVarsToTask1();
extern int joystickGetPos();
extern void threadPrioritySet();
extern void priorInvCHOICE();

#include <stdio.h>
#include "projectMain.h"
#include "LPC17xx.h"                    // Device header
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_ADC.h"                  // ::Board Support:A/D Converter
#include "Board_Joystick.h"             // ::Board Support:Joystick
#include <stdbool.h>  
#include <string.h>
#include "cmsis_os.h"                   // CMSIS RTOS header file
#include <stdlib.h>
#include <math.h>     
//#include "osObjects.h"                      // RTOS object definitions

//------- ITM Stimulus Port definitions for printf ------------------- //
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}

//------------------------------------------------------------------- //

// Bit Band Macros used to calculate the alias address at run time
#define ADDRESS(x)    (*((volatile unsigned long *)(x)))
#define BitBand(x, y) 	ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))

volatile unsigned long * bit;

#define GPIO_Bit28 (*((volatile unsigned long *)0x23380670)) //GPIO 1.28  CENTER  --->2.0

#define GPIO_Bit2	 (*((volatile unsigned long *)0x23380A08)) //GPIO 2.2 	UP 
	
#define GPIO_Bit3  (*((volatile unsigned long *)0x23380E0C)) //GPIO 3.3 	DOWN  --->2.3
	
#define GPIO_Bit4  (*((volatile unsigned long *)0x23381210)) //GPIO 4.4		LEFT  --->2.4
	
#define GPIO_Bit5  (*((volatile unsigned long *)0x23380214)) //GPIO 0.5		RIGHT  --->2.5
	

#define LPC_GPIO(n)		((LPC_GPIO_TypeDef *)(LPC_GPIO0_BASE + 0x00020*n))

#define PI 3.14
//#define RHO 207129	
#define BLANK "\u2580"

#define osObjectsPublic                     // define objects in main module

static char text[10];

static volatile uint16_t AD_dbg; //Variable to trace in LogicAnalyzer (should not read to often)

uint16_t ADC_last; // Last converted value


	char jPosMain[68];
	
	char hexCode[3][2];
	char hexColor[6];
	
	int taskOneInput;
	int taskTwoInput;
	int taskThreeInputINT;
	

	char taskThreeInputVar[4][3] = { {"Mr"}, {"Rr"}, {"Vex"}, {"P"}};
	char planet[8][8] = {{"Mercury"}, {"Venus"}, {"Earth"}, {"Mars"}, {"Jupiter"}, {"Saturn"}, {"Uranus"}, {"Neptune"}};
	

	char colorName[16][8] = {"White","Silver", "Gray", "Black", "Red", "Maroon", "Yellow", "Olive", "Lime", "Green", "Aqua", "Teal", "Blue", "Navy", "Fuchsia", "Purple"};
	char colorHex[16][7] = {"FFFFFF", "C0C0C0", "808080", "000000", "FF0000", "800000", "FFFF00", "808000", "00FF00", "008000", "00FFFF", "008080","0000FF", "000080", "FF00FF", "800080"};
	int correspColor[16] = {14, 15, 1, 0, 2, 3, 11, 10, 13, 12, 6, 7, 4, 5, 9, 8};
		
	
	
		
	double taskThreeInput[4];

	
	
	int scanIn;
	int taskChoice[5];
	int taskOrder[3];
	int mSRSVar;
	int priorInvCH = 0;
	int k = 0;
	int planetNumMain;
	
	int a=0, b=0, c=0, d=0, e=0;
	
	long long int decimalNum[3];
	
	bool running = 1;
	bool taskChosenYet = 0;
	bool taskCHOSEN[6];
	bool boolTVars[3];





/////////////////////////////////////////////////////////////////// Methods/Functions
//custom delay function for e sconds
void delay(unsigned int e){ 
		int c, d, m;
		e = e*30000; //30000
   
   for (c = 0; c <= e/6; c++) {
			for (d = 0; d <= e; d++){
				
			}
			printf("-");
			//printf("delay");
	 }
	 printf("\nDONE DELAY \n\n");
}

//terminate prorgam
void terminate(){
		printf("Program Terminating in 5s\n");
		delay(5000);
		running = 0;
}

//invalid entry
void invalidEntry(){
		printf("You entered %d\n INVALID ENTRY, PLEASE TRY AGAIN\n", scanIn); 
		taskChosenYet = 0;
}


void printJALL(){
	printf("The possible Joystcick configurations used for inputs are: ");
	printf("No Pins on | N/A == 0 ");
	printf("UP | P1.20 == 4 ");
	printf("RIGHT | P1.23 == 8 ");
	printf("DOWN | P1.24 == 2 ");
	printf("LEFT | P1.25 == 16 ");
	printf("UP-RIGHT | P1.26 == 1 ");
	printf("UP-LEFT | 23, 24 == 10 ");
	printf("DOWN-LEFT | 23, 26 == 9 ");
	printf("DOWN-RIGHT | 25, 26 == 17 ");
	printf("SELECT-UP | 20, 23 == 12 ");
	printf("SELECT-RIGHT | 20, 24 == 6 ");
	printf("SELECT-DOWN | 20, 25 == 20 ");
	printf("SELECT-LEFT | 20, 26 == 5 ");
	printf("SELECT-UP-RIGHT | 20, 23, 24 == 14 ");
	printf("SELECT-UP-LEFT | 20, 23, 26 == 13 ");
	printf("SELECT-DOWN-LEFT | 20, 25, 26 == 21 ");
	printf("SELECT-DOWN-RIGHT | 20, 24, 25 == 22 ");
}

void hexAssoc(int x){
	switch(x){
		case 1: //WHITE
			hexCode[0][0] = 'F'; hexCode[0][1] = 'F'; hexCode[1][0] = 'F'; hexCode[1][1] = 'F'; hexCode[2][0] = 'F'; hexCode[2][1] = 'F';
		
		case 2: //SILVER
			hexCode[0][0] = 'C'; hexCode[0][1] = '0'; hexCode[1][0] = 'C'; hexCode[1][1] = '0'; hexCode[2][0] = 'C'; hexCode[2][1] = '0';
		
		case 3: //GRAY
			hexCode[0][0] = '8'; hexCode[0][1] = '0'; hexCode[1][0] = '8'; hexCode[1][1] = '0'; hexCode[2][0] = '8'; hexCode[2][1] = '0';
		
		case 4: //BLACK
			hexCode[0][0] = '0'; hexCode[0][1] = '0'; hexCode[1][0] = '0'; hexCode[1][1] = '0'; hexCode[2][0] = '0'; hexCode[2][1] = '0';;
		
		case 5: //RED
			hexCode[0][0] = 'F'; hexCode[0][1] = 'F'; hexCode[1][0] = '0'; hexCode[1][1] = '0'; hexCode[2][0] = '0'; hexCode[2][1] = '0';
		
		case 6: //MAROON
			hexCode[0][0] = '8'; hexCode[0][1] = '0'; hexCode[1][0] = '0'; hexCode[1][1] = '0'; hexCode[2][0] = '0'; hexCode[2][1] = '0';
		
		case 7: //YELLOW
			hexCode[0][0] = 'F'; hexCode[0][1] = 'F'; hexCode[1][0] = 'F'; hexCode[1][1] = 'F'; hexCode[2][0] = '0'; hexCode[2][1] = '0';
		
		case 8: //OLIVE
			hexCode[0][0] = '8'; hexCode[0][1] = '0'; hexCode[1][0] = '8'; hexCode[1][1] = '0'; hexCode[2][0] = '0'; hexCode[2][1] = '0';
		
		case 9: //LIME
			hexCode[0][0] = '0'; hexCode[0][1] = '0'; hexCode[1][0] = 'F'; hexCode[1][1] = 'F'; hexCode[2][0] = '0'; hexCode[2][1] = '0';
		
		case 10: //GREEN
			hexCode[0][0] = '0'; hexCode[0][1] = '0'; hexCode[1][0] = '8'; hexCode[1][1] = '0'; hexCode[2][0] = '0'; hexCode[2][1] = '0';
		
		case 11: //AQUA
			hexCode[0][0] = '0'; hexCode[0][1] = '0'; hexCode[1][0] = 'F'; hexCode[1][1] = 'F'; hexCode[2][0] = 'F'; hexCode[2][1] = 'F';
		
		case 12: //TEAL
			hexCode[0][0] = '0'; hexCode[0][1] = '0'; hexCode[1][0] = '8'; hexCode[1][1] = '0'; hexCode[2][0] = '8'; hexCode[2][1] = '0';
		
		case 13: //BLUE
			hexCode[0][0] = '0'; hexCode[0][1] = '0'; hexCode[1][0] = '0'; hexCode[1][1] = '0'; hexCode[2][0] = 'F'; hexCode[2][1] = 'F';
		
		case 14: //NAVY
			hexCode[0][0] = '0'; hexCode[0][1] = '0'; hexCode[1][0] = '0'; hexCode[1][1] = '0'; hexCode[2][0] = '8'; hexCode[2][1] = '0';
		
		case 15: //FUCHSIA
			hexCode[0][0] = 'F'; hexCode[0][1] = 'F'; hexCode[1][0] = '0'; hexCode[1][1] = '0'; hexCode[2][0] = 'F'; hexCode[2][1] = 'F';
		
		case 16: //PURPLE
			hexCode[0][0] = '8'; hexCode[0][1] = '0'; hexCode[1][0] = '0'; hexCode[1][1] = '0'; hexCode[2][0] = '8'; hexCode[2][1] = '0';
	}
}

void planetAssoc(int x){
	switch(x){
		case 1:
			planetNumMain = 1;
		
		case 2:
			planetNumMain = 2;
		
		case 3:
			planetNumMain = 3;
		
		case 4:
			planetNumMain = 4;
		
		case 5:
			planetNumMain = 5;
		
		case 6:
			planetNumMain = 6;
		
		case 7:
			planetNumMain = 7;
		
		case 8:
			planetNumMain = 8;
	}
}

//REPEAT inputs
void repeatEntriesTask1(){
	
	printf("%d\n", taskOneInput);
}

void repeatEntriesTask2(char inputTask2[3][2]){
	printf("0x");
	for(int l = 0; l < 3; l++){
		for(int m=0; m < 2; m++) {
			printf("%c", inputTask2[l][m]);
		}
	}
	printf("\n");
}

void repeatEntriesTask3(double inputTask3[4]){
	for(int l = 0; l < 4; l++){
		printf("%lf", inputTask3[l]);
	}
	printf("\n");
}

void repeatEntriesTask4(int tempmSRSVar){

		printf("%d", tempmSRSVar);
	printf("\n");
}


////SCAN inputs
void scanTask1(){
	printf("Task 1\n_______\n Enter the value of n (1-16) you'd like use in the sum, using the joystick\n"); //TASK 1 get input Var's
			
	delay(20);
	
	taskOneInput = joystickGetPos(); 
}

void scanTask2(){
	printf("Task 2\n_______\n Enter the hex CODE's associated number (1-16) using the joystick\n"); //TASK 2 get input Var's
	
	delay(20);
	
	hexAssoc(joystickGetPos());
}

void scanTask3(){
	printf("\nTask 3\n_______\n Choose the number of the planet (1-8)\n");  //TASK 3 get input Var's
	
		delay(20);
	
		planetAssoc(joystickGetPos());
}

//GRAB VARS FROM USER
void ifWhileVarGrab() {
	int task1VarsChosen=0, task2VarsChosen=0, task3VarsChosen=0, allTaskVars=0;
	
	while(allTaskVars == 0) {
			if(taskOrder[0] == 1 && taskOrder[1] == 2 && taskOrder[2] == 3) {
						scanTask1();
						//repeatEntriesTask1();
							
						scanTask2();
						//repeatEntriesTask2(hexCode);
							
						scanTask3();
						//repeatEntriesTask3(taskThreeInput);
				
						
						allTaskVars = 1;
			}
				
					
			if(taskOrder[0] == 1 && taskOrder[1] == 3 && taskOrder[2] == 2) {
						scanTask1();
					//	repeatEntriesTask1();
							
						scanTask3();
						//repeatEntriesTask3(taskThreeInput);
				
						scanTask2();
						//repeatEntriesTask2(hexCode);
				
				
				allTaskVars = 1;
			}
			
			if(taskOrder[0] == 2 && taskOrder[1] == 1 && taskOrder[2] == 3) {
						scanTask2();
						//repeatEntriesTask2(hexCode);

						scanTask1();
						//repeatEntriesTask1();
				
						scanTask3();
						//repeatEntriesTask3(taskThreeInput);
				
				
				allTaskVars = 1;
			}
			
			if(taskOrder[0] == 2 && taskOrder[1] == 3 && taskOrder[2] == 1) {
						scanTask2();
						//repeatEntriesTask2(hexCode);
				
						scanTask3();
						//repeatEntriesTask3(taskThreeInput);
				
						scanTask1();
						//repeatEntriesTask1();
				
				
				allTaskVars = 1;
			}
			
			if(taskOrder[0] == 3 && taskOrder[1] == 1 && taskOrder[2] == 2) {
						scanTask3();
						//repeatEntriesTask3(taskThreeInput);
				
						scanTask1();
						//repeatEntriesTask1();
				
						scanTask2();
						//repeatEntriesTask2(hexCode);
				
				
				allTaskVars = 1;
			}
			
			if(taskOrder[0] == 3 && taskOrder[2] == 2 && taskOrder[2] == 1) {
						scanTask3();
						//repeatEntriesTask3(taskThreeInput);
				
						scanTask2();
						//repeatEntriesTask2(hexCode);
				
						scanTask1();
						//repeatEntriesTask1();
				
				
				allTaskVars = 1;
			}
		}
	}
	
	///PASSING VARS to TASKS
	void passVarsToTask1(int taskOneInput){
		recVarsToTask1(taskOneInput);
	}
	
	void passVarsToTask2(char hexCode[3][2]){
		recVarsToTask2(hexCode);
	}
	
	void passVarsToTask3(/*double taskThreeInput[4]*/ int planetNumMain){
		recVarsToTask3(planetNumMain);
	}
	
void passVarsToTasks(/*int taskOneInput, char hexCode[3][2], double taskThreeInput[4]*/){
	passVarsToTask1(taskOneInput);
	passVarsToTask2(hexCode);
	passVarsToTask3(planetNumMain);
}

void mutexSemOrResSEM(/*int tempmSRSVar[3]*/){
	printf("Would you like to run Mutex (1), Semaphore (2), or Resemble Semaphore (3)? Please enter in the form: GPIO nothing (1) or 1.23 (UP - 2) or 1.24 (RIGHT - 3) \n\n using only pins: nothing, 23, and 24");
	
	delay(20);
	mSRSVar = joystickGetPos();
	
	//while(priorInvCH == 0) {
		switch(mSRSVar){
			 case 1: {  //MUTEX
							//repeatEntriesTask4(mSRSVar);
							printf("MODE: MUTEX\n\n");
							priorInvCH = 1;
				 break;
				}
						
			 case 2: { //SEM
							//repeatEntriesTask4(mSRSVar);
							printf("MODE: SEMAPHORE\n\n");
							priorInvCH = 2;
				 break;
				}
				
				case 3: { //RESSEM
							//repeatEntriesTask4(mSRSVar);
							printf("MODE: RESEMBLE SEMAPHORE\n\n");
							priorInvCH = 3;
					break;
				}
			}
		//}
}

/*------------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void) {
  int32_t  res;
	
  uint32_t AD_sum   = 0U;
  uint32_t AD_cnt   = 0U;
  uint32_t AD_value = 0U;
  uint32_t AD_print = 0U;

  LED_Initialize();                      // LED Initialization
  ADC_Initialize();                      // ADC Initialization
	Joystick_Initialize();                 // Joystick Initialization

	LPC_SC->PCONP		|= (1 << 15); 				 // Powering Up Joystick
	
	/* P1.20, P1.23..26 is GPIO (Joystick) */
	LPC_PINCON->PINSEL3 &= ~((3<< 8) | (3<< 14) | (3<< 16) | (3<< 18) | (3<< 20));
	
	/* P1.20, P1.23..26 ids input */
	LPC_GPIO2->FIODIR 	&= ~((1<<20) | (1<<23) | (1<<24) | (1<<25) | (1<<26));
	
	
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock/100U);  // Generate interrupt each 10 ms
						 
  printf("WELCOME TO AHMAD FAHMY's, 500913092, COE718 FINAL PROJECT\n");
	printf("TASK 1 : 0 | Calculate the Series of up till input n\n");
	
	printf("TASK 2 : 1 | Convert one of the 16 basic HEX COLOR CODEs to COLOR name\n");
	for(int s =0; s<16; s++){
		printf("	(%d) color HEX:%s       color:", s+1, colorHex[s]);
		
		//textcolor(correspColor[s]);
		printf("	color name: %s\n", colorName[s]); //\u2580
		
	}
	
	char o = NULL;
	int k = 0;
	
	printf("TASK 3 : 2 | Calculates the excape velocity (Ve), Mass of fuel (Mf) and Max Altitude (Ya) using Joinable Threads for \n");
	printf("a rocket of mass (2000kg), on a planet (P) of your choice in the solar system from 1-8 corresponding to the planet's \n");
	printf("ranked position compared to the others. Mercury = 1, Venus = 2, Earth = 3 ... Uranus = 8\n");
	
	printf("	Planet Details:\n______________________\n");
	for(int z = 0; z<8; ){
			printf("	%s (%d):", planet[z], z);
		
			printf("	Mp (mass): X, Rp (radius): Y,  RHO (air density): Z, and a (gravitational acceleration): A\n");///////////////////////////////////////////CHANGE RHO
			//printf(" (%d): Mp (mass): X, Rp (radius): Y,  RHO (air density), and a (gravitational acceleration): Z\n", s+1);
			z++;
	}
	
	//TEST//printf("%d %d %d %d", correspColor[0], correspColor[1], correspColor[2], correspColor[3]);
	/* //PRINT ASCII's
	int x = 0;
	for(;;){
		printf(" %x %c\n ", x, x);
		x++;
	}
	*/
	
	printf("TERMINATE : 99\n");
	printJALL();
	
	printf("\nPlease enter the order/priority of tasks:\n GPIO nothing (0)\n 1.23 (UP - 1) \n 1.24 (RIGHT - 2)\n using only pins: nothing, 23, and 24\n");
			Joystick_Initialize();
			
			delay(20);
			taskOrder[0] = joystickGetPos();
			delay(20);
			taskOrder[1] = joystickGetPos();
			delay(20);
			taskOrder[2] = joystickGetPos();
			
			osKernelInitialize ();                    // initialize CMSIS-RTOS
			printf("\n\n");
			delay(20);
			
			ifWhileVarGrab(); 				// user enters the input-variables for each Task
			//passVarsToTasks(taskOneInput, hexCode, taskThreeInput);
			passVarsToTasks();
			delay(20);
			mutexSemOrResSEM();
			
			threadPrioritySet(taskOrder);
			priorInvCHOICE(priorInvCH);
			
			Init_task3JoinThreads();
			
			printf("THREADS MADE 1.5\n");
			
			osKernelStart ();                         // start thread execution  
			osDelay(osWaitForever);
			
			printf("PROGRAM DONE\n");
			
			//printf("KERNEL STARTED\n");
			//delay(200000);
}
