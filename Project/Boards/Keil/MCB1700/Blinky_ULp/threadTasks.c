#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LPC17xx.h"
#include <stdbool.h> 

extern int runTask1();
extern int hexColorConvRUN();
extern int escapeVelAndMass();
extern void delay();


//------- ITM Stimulus Port definitions for printf ------------------- //
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

/*
struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;


int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch); 
}*/
//------------------------------------------------------------------- //

// Bit Band Macros used to calculate the alias address at run time
#define ADDRESS(x)    (*((volatile unsigned long *)(x)))
#define BitBand(x, y) 	ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))

//volatile unsigned long * bit;

#define GPIO_Bit28 (*((volatile unsigned long *)0x23380670)) //GPIO 1.28

#define GPIO_Bit2	 (*((volatile unsigned long *)0x23380A08)) //GPIO 2.2
	
#define GPIO_Bit3  (*((volatile unsigned long *)0x23380E0C)) //GPIO 3.3
	
#define GPIO_Bit4  (*((volatile unsigned long *)0x23381210)) //GPIO 4.4
	
#define GPIO_Bit5  (*((volatile unsigned long *)0x23380214)) //GPIO 0.5
	

#define LPC_GPIO(n)		((LPC_GPIO_TypeDef *)(LPC_GPIO0_BASE + 0x00020*n))

unsigned int A=0;
unsigned int x=0;
unsigned int i=0;
int priorInvCHThread;
int z = 0;

unsigned int nB=0;
unsigned int j = 0;
int resSemToken = 0;

double B=0;
double C=0;
double nC=0;
double D=0;
double E=0;

char taskOneInputThread[101];
char hexCodeThread[3][2];
double taskThreeInputThread[4];
 
int boolMUT[3] = { 0, 0, 0};
int semaphorLive = 0;
int resSemaphoreLive = 0;
int doneTask[3] = {0, 0, 0};
 
//for threads
void Thread1 (void const *argument); // thread function
void Thread2 (void const *argument); // thread function
void Thread3 (void const *argument); // thread function

osMutexDef(threadMut);
osMutexId(threadMut_id);

//for sems
osSemaphoreId semaphore;
/*
osSemaphoreId semThread1;
osSemaphoreId semThread2;
osSemaphoreId semThread3;
*/

osThreadId tid1_Thread, tid2_Thread, tid3_Thread; // thread id

osThreadDef (Thread1, osPriorityNormal, 1, 0);                   
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   
osThreadDef (Thread3, osPriorityNormal, 1, 0);       

osSemaphoreDef(semaphore);

void threadPrioritySet(int taskOrder[3]){
	int prioritySet = 0;
	//while(prioritySet == 0) {
				if(taskOrder[0] == 1 && taskOrder[1] == 2 && taskOrder[2] == 3) {
					osThreadDef (Thread1, osPriorityRealtime, 1, 0);                  // thread object, priority +3 == 1 in manual
					osThreadDef (Thread2, osPriorityHigh, 1, 0);   									 	// thread object, priority +2 == 2 in manual
					osThreadDef (Thread3, osPriorityAboveNormal, 1, 0);               // thread object, priority +1 == 3 in manual
					prioritySet = 1;
					printf("ORDER SET: %d, %d, %d\n", taskOrder[0], taskOrder[1], taskOrder[2]);
				}
				
				else if(taskOrder[0] == 1 && taskOrder[1] == 3 && taskOrder[2] == 2) {
					osThreadDef (Thread1, osPriorityRealtime, 1, 0);                  // thread object, priority +3 == 1 in manual
					osThreadDef (Thread3, osPriorityHigh, 1, 0);   									 	// thread object, priority +2 == 2 in manual
					osThreadDef (Thread2, osPriorityAboveNormal, 1, 0);               // thread object, priority +1 == 3 in manual
					prioritySet = 1;
					printf("ORDER SET: %d, %d, %d\n", taskOrder[0], taskOrder[1], taskOrder[2]);
				}
				
				else if(taskOrder[0] == 2 && taskOrder[1] == 1 && taskOrder[2] == 3) {
					osThreadDef (Thread2, osPriorityRealtime, 1, 0);                  // thread object, priority +3 == 1 in manual
					osThreadDef (Thread1, osPriorityHigh, 1, 0);   									 	// thread object, priority +2 == 2 in manual
					osThreadDef (Thread3, osPriorityAboveNormal, 1, 0);               // thread object, priority +1 == 3 in manual
					prioritySet = 1;
					printf("ORDER SET: %d, %d, %d\n", taskOrder[0], taskOrder[1], taskOrder[2]);
				}
				
				else if(taskOrder[0] == 2 && taskOrder[1] == 3 && taskOrder[2] == 1) {
					osThreadDef (Thread2, osPriorityRealtime, 1, 0);                  // thread object, priority +3 == 1 in manual
					osThreadDef (Thread3, osPriorityHigh, 1, 0);   									 	// thread object, priority +2 == 2 in manual
					osThreadDef (Thread1, osPriorityAboveNormal, 1, 0);               // thread object, priority +1 == 3 in manual
					prioritySet = 1;
					printf("ORDER SET: %d, %d, %d\n", taskOrder[0], taskOrder[1], taskOrder[2]);
				}
				
				else if(taskOrder[0] == 3 && taskOrder[1] == 1 && taskOrder[2] == 2) {
					osThreadDef (Thread3, osPriorityRealtime, 1, 0);                  // thread object, priority +3 == 1 in manual
					osThreadDef (Thread1, osPriorityHigh, 1, 0);   									 	// thread object, priority +2 == 2 in manual
					osThreadDef (Thread2, osPriorityAboveNormal, 1, 0);               // thread object, priority +1 == 3 in manual
					prioritySet = 1;
					printf("ORDER SET: %d, %d, %d\n", taskOrder[0], taskOrder[1], taskOrder[2]);
				}
				
				else if(taskOrder[0] == 3 && taskOrder[1] == 2 && taskOrder[2] == 1) {
					osThreadDef (Thread3, osPriorityRealtime, 1, 0);                  // thread object, priority +3 == 1 in manual
					osThreadDef (Thread2, osPriorityHigh, 1, 0);   									 	// thread object, priority +2 == 2 in manual
					osThreadDef (Thread1, osPriorityAboveNormal, 1, 0);               // thread object, priority +1 == 3 in manual
					prioritySet = 1;
					printf("ORDER SET: %d, %d, %d\n", taskOrder[0], taskOrder[1], taskOrder[2]);
				}
				
				else {
					printf("Invalid Priority Settings, Try again\n");
					prioritySet = 0;
				}
	//}
}

void MutThreads(){
	boolMUT[0] = 1;
	boolMUT[1] = 1;
	boolMUT[2] = 1; 
	
	threadMut_id = osMutexCreate(osMutex(threadMut));
}

void SemThreads(){ 
	semaphorLive = 1;
	semaphore = osSemaphoreCreate(osSemaphore(semaphore), 1);
}
 
void RSemThreads(){ 
	resSemaphoreLive = 1;

}

void priorInvCHOICE(int priorInvCHThreadTemp){
	priorInvCHThread = priorInvCHThreadTemp;
	//choose MODE
	switch(priorInvCHThread){
				case 1:{
					MutThreads(); // chooses MUTEX  
				}
				
				case 2:{
					SemThreads(); // chooses SEMAPHORES
				}
				
				case 3:{
					RSemThreads(); // chooses RES SEMAPHORES
				}
			}
	
			printf("prior INV set\n");		
}

int Init_task3JoinThreads() {
	tid1_Thread = osThreadCreate (osThread(Thread1), NULL);
	tid2_Thread = osThreadCreate (osThread(Thread2), NULL);
	tid3_Thread = osThreadCreate (osThread(Thread3), NULL);
  if(!tid1_Thread) return(-1);
	
	
	
	printf("THREADS MADE 1.0\n");		
			
  return(0);
}

void Thread3 (void const *argument) { //TASK C
	while(doneTask[2] == 0){
		if(boolMUT[2] == 1){
			osMutexWait(threadMut_id, osWaitForever);  //for MUT 1
			//osMutexWait(threadMut_id, 1);  //for MUT 1
			printf("RUNNING 3\n");
			escapeVelAndMass(); 
			osMutexRelease(threadMut_id);
		}
		
		if(semaphorLive == 1){
				osSemaphoreWait(semaphore, osWaitForever);
				escapeVelAndMass();
				osSemaphoreRelease(semaphore);
		}
		
		if(resSemaphoreLive == 1){
			if(resSemToken == 0){
				resSemToken = 3;
			}
		
			if(resSemToken == 3){	
				escapeVelAndMass();
				resSemToken = 0;
			}
		}	
		doneTask[2] = 1;
	}
}

void Thread2 (void const *argument) { //TASK B
	while(doneTask[1] == 0){
		if(boolMUT[1] == 1){
			osMutexWait(threadMut_id, osWaitForever);
			//osMutexWait(threadMut_id, 2);
			printf("RUNNING 2\n");		
			
			hexColorConvRUN();
			osMutexRelease(threadMut_id);
		}
		
		if(semaphorLive == 1) {
			delay(10);
				int val = osSemaphoreWait(semaphore, 2);
				if(val >0){
					hexColorConvRUN();
					osSemaphoreRelease(semaphore);
				}
		}
		
		if(resSemaphoreLive == 1){
			delay(10);
			if(resSemToken == 0){
				resSemToken = 2;
			}
			
			if(resSemToken == 2){	
				hexColorConvRUN();
				resSemToken = 0;
			}
		}
		doneTask[1] = 1;
	}
}

void Thread1(void const *argument){
	//z = 5;
	z++;
	//printf("works\n");
	//delay(10);
}

/*
void Thread1 (void const *argument) { //TASK A
	z = 5;
	z++;
	
	printf("TASK 1 START");
	delay(1000);
	
	z = 10;
	
	delay(1000); 
	
	
	printf("AHAHAHHAHAHAHAHA     BEFORE INFINITE WHILE TASK 1\n");  /////////////ERROR HERE
	while(doneTask[0] == 0){
		printf("AHAHAHHAHAHAHAHA RUNNING 1.01 AHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
		
		if(boolMUT[0] == 1){ 
			printf("RUNNING 1.0\n");
			osStatus status;
			status = osMutexWait(threadMut_id, osWaitForever);
			printf("RUNNING 1.1\n");
			
			if(status != osOK){
				printf("ERROR\n");
				break;
			}
			printf("RUNNING 1.2\n");
			
			//osMutexWait(threadMut_id, 3);
			printf("RUNNING 1.3\n");
			runTask1();
			osMutexRelease(threadMut_id);
			printf("RUNNING 1.4\n");
		}
		
		
		
	 if(semaphorLive == 1) {
			delay(10);
			int val = osSemaphoreWait(semaphore, 1);
			if(val >0){
				runTask1();
				osSemaphoreRelease(semaphore);
			}
		}
		
		else if(resSemaphoreLive == 1) {
			delay(10);
			if(resSemToken == 0){
				resSemToken = 1;
			}
			
			if(resSemToken == 1){	
				runTask1();
				resSemToken = 0;
			}
		}
		doneTask[0] = 1;
	}
}                                          
*/