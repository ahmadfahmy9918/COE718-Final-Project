#include <stdio.h>
#include <stdbool.h> 
#include <math.h>

#define G (6.674*(pow(10, -11)))

double planetVars[4];

bool planetChosen = 0;

//double taskThreeInputTASK[1];
int planetNum;

double output[3];

void recVarsToTask3(/*double taskTempThreeInputTASK[4]*/ int x){
	//for(int i = 0; i < 4; i++){
		//	taskThreeInputTASK[i] = taskTempThreeInputTASK[i];
	//}
	planetNum = x;
}

void planetChoose(P){   ///////////////////////put all the numbers for each PLANET
	while(planetChosen == 0) {
		switch(P){
			case 1:{ //Mercury
				planetVars[0] = 3.3011*pow(10,23);
				planetVars[1] = 4880*1000/2;
				planetVars[2] = 0.020;
				planetVars[3] = 3.7;
				planetChosen = 1;
			}
				
			case 2:{ //Venus
				planetVars[0] = 4.8675*pow(10,24);
				planetVars[1] = 6051.8*1000;
				planetVars[2] = 65;
				planetVars[3] = 8.87;
				planetChosen = 1;
			}
			
			case 3:{ //Earth
				planetVars[0] = 5.97237*pow(10,24);
				planetVars[1] = 6378.137*1000;
				planetVars[2] = 1.2;
				planetVars[3] =9.8;
				planetChosen = 1;
			}
				
			case 4:{ //Mars
				planetVars[0] = 6.4171*pow(10,23);
				planetVars[1] = 3389.5*1000;
				planetVars[2] = 0.020;
				planetVars[3] = 3.721;
				planetChosen = 1;
			}
			
			case 5:{ //Jupiter
				planetVars[0] = 1.8982*pow(10,27);
				planetVars[1] = 71492*1000;
				planetVars[2] = 0.16;
				planetVars[3] = 24.79;
				planetChosen = 1;
			}
				
			case 6:{ //Saturn
				planetVars[0] = 5.6834*pow(10,26);
				planetVars[1] = 60268*1000;
				planetVars[2] = 0.19;
				planetVars[3] = 10.44;
				planetChosen = 1;
			}
			
			case 7:{ //Uranus 
				planetVars[0] = 86.813*pow(10,24);
				planetVars[1] = 25559*1000;
				planetVars[2] = 0.42;
				planetVars[3] = 8.87	;
				planetChosen = 1;
			}
				
			case 8:{ //Neptune
				planetVars[0] = 102.413*pow(10,24);
				planetVars[1] = 24764*1000;
				planetVars[2] = 0.45;
				planetVars[3] = 11.15;
				planetChosen = 1;
			}
			
			default:
				printf("You entered %d\n INVALID ENTRY, PLEASE TRY AGAIN\n", P); //confirmation 
				planetChosen = 0;
		
		}
	}
}

void allCalc(){
	//Escape Vel
	output[0] = sqrt((2*G*planetVars[0])/planetVars[1]);

	//total mass of rocket
	//output[1] = taskThreeInputTASK[0]* exp((output[0] / taskThreeInputTASK[2]));
	output[1] = 2000* exp((output[0] / 5000));

	//mass of fuel
	//output[2] = output[1] - taskThreeInputTASK[0];
	output[2] = output[1] - 2000;
}

void escapeVelAndMass(){
	planetChoose(planetNum); //chooses the corresponding planet
	allCalc();
	
	printf("Your necessary Escape Velocity is %lf: ", output[0]); printf("m/s \n");
	printf("The total mass of your rocket with fuel should be approximately %lf: ", output[1]); printf("kg \n");
	printf("The total mass of rocket fuel should be approximately %lf: ", output[2]); printf("kg \n");
}


