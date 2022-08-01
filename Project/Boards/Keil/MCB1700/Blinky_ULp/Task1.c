
#include <stdio.h>
#include <string.h>
#include <math.h>


char taskOneInputTASK[101];

double inputDoubles[5];
double extraDerivDoubleAll = 1;
char varsWPow[10][3];
char function[10];
char derivsAllAND0;
char inputVar;

int finalOut = 0;
int fullSizeVar = 0;
int n = 0;
double seriesTot = 0;
double seriesN = 0;
int i = 1;

/*
void fullSize(){
	int i=0;
	
	while(fullSizeVar<i){
		if(taskOneInputTASK[i] == NULL && taskOneInputTASK[i+1] == NULL){
			fullSizeVar = i;
			i++;
		}
	}
}
*/


/*
void recVarsToTask1(char taskTempOneInputTASK[101]){
	for(int i = 0; i < fullSizeVar; i++){
		taskOneInputTASK[i] = taskTempOneInputTASK[i];
	}
}*/


/*
void breakApart(){
	int i=0;
	int currentVarWPow = 0;
	int fullSize = 0;
	
	while(fullSize < fullSizeVar){ //runs through all
		
		
		
		//runs through all until space (32) and (array cell behind value not a different type OR array cell behind not 0*//*)
		while(taskOneInputTASK[i] != 32 && (taskOneInputTASK[i] != taskOneInputTASK[i-1] || ((i-1) == 0)*//*)){ 
		//for(int i=0; i < sizeof(&taskOneInputTASK); i++){
			if(taskOneInputTASK[i] == '0'){ //check if double  ///////////neeeds to change
				inputDoubles[0] = taskOneInputTASK[i];
			}
			
			if(taskOneInputTASK[i] == 'c'){ // check if char   //////////////////needs to change
				if(taskOneInputTASK[i+1] == 'c'){ ////check if double
					
				}
			}
			
			else { //IS char or operator
					if(taskOneInputTASK[i] == 42){ ////multiply operator
						
					}
					
					if(taskOneInputTASK[i] == 43){ ////add operator
						
					}
					
					if(taskOneInputTASK[i] == 45){ ////subtract operator
						
					}
					
					if(taskOneInputTASK[i] == 47){ ////divide operator
						
					}
					
					else if( (taskOneInputTASK[i]>='a' && taskOneInputTASK[i]<='z') || (taskOneInputTASK[i]>='A' && taskOneInputTASK[i]<='Z')){   // IS var
						inputVar = taskOneInputTASK[i];
							if(taskOneInputTASK[i+1] == 94){
								while(taskOneInputTASK[i] != 32 && (taskOneInputTASK[i] != taskOneInputTASK[i-1] || ((i-1) == 0)*//*)){
									for(int d=0; d<3; d++){
										varsWPow[currentVarWPow++][d] = taskOneInputTASK[i];
									}
								}
							}
					}
			}
		}
	}
}


void derivAND0(int current){
	
	//do derivative of x
	derivsAllAND0 = varsWPow
	
	extraDerivDoubleAll = extraDerivDoubleAll * (varsWPow[current][2]-1); //put the power brought down here and multiply all together

}

void calcMac(){  ///you need to program BEDMAS
	int i=0;
	while(i < sizeof(taskOneInputTASK)){
			if(taskOneInputTASK[i] == inputVar){
				derivAND0(i);
				
			}
			
			
	
			finalOut += finalOut;
	}
}
*/

long factorial(int nFact){
	int fact =1;
	for(int i=1;i<nFact+1;i++){    
      fact=fact*i; 
	}
		return fact;
}

void recVarsToTask1(int tempN){
	n = tempN;
}

void calcSeries(){
	//
	
}

void runTask1(){
	//fullSize();
	//breakApart();
	//calcMac();
	
	calcSeries();
	
	printf("the sum of the series with n= %d is %lf", n, seriesTot);
	
	//
}



int Thread1a(void const *argument){
	seriesTot = seriesTot + seriesN;
}

int Thread1b(void const *argument){
	seriesN = seriesN / factorial(i);
}

int Thread1c(void const *argument){
	seriesN = (pow(2, i)+4);
	i++;
}