#include "Board_Joystick.h"             // ::Board Support:Joystick
#include <string.h>
#include <stdio.h>

int joystickGetPos(/*char position[]*/) {
	switch(Joystick_GetState()){
				case 0:{
					//strcpy(position, "No Direction, No Select");
					printf("1 - No Direction, No Select\n");
					return(1);
				break;
				}
				
				case 8:{
					//strcpy(position, "Up");
					printf("2 - Up\n");
					return(2);
				break;
				}
				
				case 2:{
					//strcpy(position, "Right");
					printf("3 - Right\n");
					return(3);
				break;
				}
				
				case 16:{
					//strcpy(position, "Down");
					printf("4 - Down\n");
					return(4);
				break;
				}
				
				case 1:{
					//strcpy(position, "Left");
					printf("5 - Left\n");
					return(5);
				break;
				}
				
				case 4:{
					//strcpy(position, "Select");
					printf("6 - SELECT\n");
					return(6);
				break;
				}
				
				
				case 10:{
					//strcpy(position, "Up-Right");
					printf(" 7 - Up-Right\n");
					return(7);
				break;
				}
				
				case 9:{
					//strcpy(position, "Up-Left");
					printf("8 - Up-Left\n");
					return(8);
				break;
				}
				
				case 17:{
					//strcpy(position, "Down-Left");
					printf("9 - Down-Left\n");
					return(9);
				break;
				}
				
				
				case 18:
					//strcpy(position, "Down-Right");
					printf("10 - Down-Right\n");
					return(10);
				break;
				
				case 12:
					//strcpy(position, "Select-Up");
					printf("11 - Select-Up\n");
					return(11);
				break;
				
				case 6:
					//strcpy(position, "Select-Right");
					printf("12 - Select-Right\n");
					return(12);
				break;
				
				case 20:
					//strcpy(position, "Select-Down");
					printf("13 - Select-Down\n");
					return(13);
				break;
				
				case 5:
					//strcpy(position, "Select-Left");
					printf("14 - Select-Left\n");
					return(14);
				break;
				
				case 14:
					//strcpy(position, "Select-Up-Right");
					printf("15 - Select-Up-Right\n");
					return(15);
				break;
				
				case 13:
					//strcpy(position, "Select-Up-Left");
					printf("16 - Select-Up-Left\n");
					return(16);
				break;
				
				
				/*
				case 21:
					strcpy(position, "Select-Down-Left");
				break;
				
				case 22:
					strcpy(position, "Select-Down-Right");
				break;
				*/
				default:{
						printf("Physically Impossible combination, try using non-opposing positions");
					return(0);
				}
	}
			
}



	
int scanfToJ(char scanIn){
	int x = Joystick_GetState();
	
	return x;
}
