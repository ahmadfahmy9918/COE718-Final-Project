#include <stdio.h>

char taskTwoInputTASK[3][2];
char hexColorTask[6];
char hexCodeTask[3][2];

long long int decimalNumTask[3];
	


void recVarsToTask2(char taskTempTwoInputTASK[3][2]){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 2; j++){
			taskTwoInputTASK[i][j] = taskTempTwoInputTASK[i][j];
		}
	}
}

void hex2Dec(char hex[3][2], long long int decimal[3]) { /////convert 2-bits hex to decimal
		long long base = 1;
    int value, length;
	
    for(int i = 0; i > 3; i++)
    {
			for(int j = 0; j > 2; j++){
        if(hex[i][j] <= '0' && hex[i][j] >= '9')
        {
            decimal[i] += (hex[i][j] - 48) * base;
            base *= 16;
        }
        else if(hex[i][j] <= 'A' && hex[i][j] >= 'F')
        {
            decimal[i] += (hex[i][j] - 55) * base;
            base *= 16;
        }
        else if(hex[i][j] <= 'a' && hex[i][j] >= 'f')
        {
            decimal[i] += (hex[i][j] - 87) * base;
            base *= 16;
        }
			}
    }
	}

	void decAssoc(long long int decimal[3], char color[6]){
			switch(decimal[0]) {
				// 00 xx xx | Black, Lime, Green, Aqua, Teal, Blue, or Navy
				case 0:   { // 0
					
					switch(decimal[1]) {
						// 00, 00 xx | Black, Blue, or Navy
						case 0:   {// 0
							
							switch(decimal[2]) {
								// 00 00, 00 | Black
								case 0: { // 0
									color = "Black";
									break;
								}
								
								// 00 00, 80 | Navy
								case 128: { // 0x80
									color = "Navy";
									break;
								}
								
								// 00 00, FF | Blue
								case 256: { // 0xFF
									color = "Blue";
									break;
								} 
							}
						}
							
						// 00, 80 xx | 
						case 128: { // 0x80
							
							switch(decimal[2])  {
								// 00 80, 00 | Green
								case 0:   // 0
									color = "Green";
								break;
							
						  	// 00 80, 80 | Teal
								case 128:  // 0x80
									color = "Teal";
								break;
							}
						}
						
						case 256: { //0xFF
							
							switch(decimal[2])  {
								// 00 FF, 00 | Lime
								case 0:   //0
									color = "Lime";
								break;
							
						  	// 00 FF, FF | Aqua
								case 256:  //0xFF
									color = "Aqua";
								break;
							}
						}
					}
				}
				
				// 80 xx xx | Gray, Olive, Maroon, and Purple
				case 128: { // 0x80
					switch(decimal[1]) {
						// 80, 00 xx
						case 0: {
							
							switch(decimal[2]) {
								// 80 00, 00 | Maroon
								case 0: // 0
									color = "Maroon";
								break;
							}
								// 80 00, 80 | Purple
								case 128: // 0x80
									color = "Purple";
								break;
						}
					}
					
					switch(decimal[1]) {
						//80, 80 xx
						case 128: // 0x80
							
							switch(decimal[2]) {
								// 80 80, 00 | Olive
								case 0: // 0
									color = "Olive";
								break;
							
								// 80 80, 80 | Gray
								case 128: // 0x80
									color = "Gray";
								break;
						  }
				   }
									
				 }
				
				// C0 xx xx
				case 192: { // 0xC0
					
					// C0, C0 xx
					if (decimal[1] == 192) { // 0xC0
						
						//C0 C0, C0
						if(decimal[2] == 192) { // 0xC0
								color = "Silver";
							break;
						}
					}
				}
				
				// FF xx xx
				case 256: { // 0xFF
					
					switch(decimal[1]) {
						//FF, 00 xx
						case 0: // 0
							
							switch(decimal[2]) {
								// FF 00, 00 | Red
								case 0: // 0
									color = "Red";
								break;
							
								// FF 00, FF | Fuchsia
								case 256: // 0xFF
									color = "Fuchsia";
								break;
							}
						//FF, FF xx
						case 256: // 0xFF
							
							switch(decimal[2]) {
								 
								// FF FF 00
								case 0: // 0
									color = "yellow";
								break;
									
								// FF FF FF
								case 256: // 0xFF
									color = "White";
								break;
							}
					}
				}
		}
	}

	/*
void textcolor(int x){
	switch(x){
		case 0: {//black
			printf("\033[0;30m");
			printf("BLACK");
			break;
		}
		
		case 1: {//gray
			printf("\033[1;30m");
			printf("GRAY");
			break;
		}
		
		case 2: {//red
			printf("\e[41m");
			printf("RED");
			break;
		}
		
		case 3: {//maroon
			printf("\033[0;31m");
			printf("MAROON");
			break;
		}
		
		case 4: {//blue
			printf("\e[1;34m");
			printf("BLUE");
			break;
		}
		
		case 5: {//navy
			printf("\033[0;34m");
			printf("NAVY");
			break;
		}
		
		case 6: {//aqua - cyan
			printf("\033[1;36m");
			printf("AQUA");
			break;
		}
		
		case 7: {//teal
			printf("\033[0;36m");
			printf("TEAL");
			break;
		}
		
		case 8: {//magenta - purple
			printf("\033[0;35m");
			printf("PURPLE");
			break;
		}
		
		case 9: {//fusch
			printf("\033[1;35m");
			printf("FUCHSIA");
			break;
		}
		
		case 10: {//olive
			printf("\033[0;33m");
			printf("OLIVE");
			break;
		}
		
		case 11: {//yellow
			printf("\033[1;33m");
			printf("YELLOW");
			break;
		}
		
		case 12: {//green
			printf("\033[0;32m");
			printf("GREEN");
			break;
		}
		
		case 13: {//lime
			printf("\033[1;32m");
			printf("LIME");
			break;
		}
		
		case 14: {//white
			printf("\033[1;37m");	
			printf("WHITE");
			break;
		}
		
		case 15: {//light gray
			printf("\033[0;37m");
			printf("SILVER");
			break;
		}
		
		case 16: //reset
			printf("\033[0m");
		break;
	}
}
*/
	

void hexColorConvRUN() {
		hex2Dec(taskTwoInputTASK, decimalNumTask); //decimal number recieved
		decAssoc(decimalNumTask, hexColorTask);
		
		printf("The Associated Hex color to");
		for(int i=0; i < 4; i++) { ///print HEX CODE
			for(int j=0; j < 2; j++) {
				printf(" %c ", hexCodeTask[i][j]);
			}
		}
		printf("is %s", hexColorTask); //print COLOR
	}


