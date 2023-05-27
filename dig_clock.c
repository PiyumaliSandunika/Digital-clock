#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

//function prototyping
void digToArray(char,int,int);
void graphicDigit(int array[5][6],int,int);
void timePrint(int);
void errorPrint(int,char*);
int chooseColor(int,char*);

int selectedColor; //global var - user prefered color

int main(int argc,char **argv){
	int option,received,flagc=0 ;
	int msg1=1,msg2=2,manual =3;
	
	if(argc>1){
		
		//using getopt() to parse cmd line args until -1(no more options to process)(c: - need args)(h- doesn't need args)
		while ((option = getopt(argc,argv,":hc:"))!= -1 ) {
			switch(option){
				//considering h flag and call errorPrint() to print user manual	
				case 'h' :
					errorPrint(manual,optarg);
					return 0;
				//considering c flag and and call to check the argument 
				case 'c':
					flagc=1;
					received = chooseColor(argc,optarg);
					if(received ==100){
						errorPrint(msg2,optarg);
						return 1;
					}
					break;
				//if c called withour giving any value
				case '?' :
					flagc =1;
					errorPrint(msg1,optarg);
					return 1;
				//if there are any undefined flags
				case ':' :
					flagc =1;
					errorPrint(msg1,optarg);
					return 1;
				}
			
					
			}
			//arguments without flags will print in default clock color
			if(flagc==0)
				selectedColor =7;
			
		}
		//if program is called by namespace
		if(argc ==1){
			selectedColor =7;}
			
		printf("\e[?25l"); //hidding cursor
		printf("\e[H\e[J"); //clear console
		
		while(1){
			 
			 //print time& date with given color
			 timePrint(selectedColor);
			 printf("\n");
			 printf("\e[0m"); // reset color
			 
			 sleep(1);
			 
		}
			printf("\e[H\e[J");
			printf("\e[0m");
			return 0;
			
		
}



int chooseColor(int argc,char *arg){
	char *colors1[] ={"black","red","green","yellow","blue","magenta","cyan","white"};
	
	int size = sizeof(colors1)/sizeof(colors1[1]);
	int flag =0;
	for(int i=0;i<size;i++){
		//comparing user enetered colors with available colors
		if(strcasecmp(arg,colors1[i])==0){
		selectedColor = i;
		flag  =1;
		break;
	
		}
	}
	
	if(flag==0)
		return 100;
	else
		return selectedColor;
}

//Funtion to print error masgs and manual as necessary
void errorPrint(int number,char *arg){
	
	if(number==1){
		printf("Invalid use of arguments.\n");
		printf("usage : clock -h                quick help on cmd\n");
		printf("usage : clock -c <color>        print clock with a color\n");
	}
	
	else if(number ==2){
		
		printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n",arg);
	}

	else if(number==3){
		printf("usage : clock -h                quick help on cmd\n");
		printf("usage : clock -c <color>        print clock with a color\n");
		printf("<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
	}	
}

//function to get the system time and pass them to print their relevant 2d array
void timePrint (int selectedColor){
	
	int position;
	time_t time1;
	struct tm *currentTime;
	char timeStr[15];
	char dateStr [15];
	
	time1 = time(NULL);
	currentTime = localtime(&time1);
	strftime(timeStr,15,"%H:%M:%S\n",currentTime);
	strftime(dateStr,15,"%Y-%m-%d\n",currentTime);
	
	for(position=0;position<8;position++){
		digToArray(timeStr[position],position,selectedColor);
	}
	printf("\n");
	printf("\e[8;23H");
	printf("\e[0m");
	//to achieve the color codes that mentioned at the end of the code
	printf("\e[%dm",selectedColor+30);
	for(int i=0;i<10;i++){
		printf("%c",dateStr[i]);
		
	}
		printf("\e[0m");
}

//function to convert number string to their 2d array such that they appear like in 7 segment display
void digToArray(char val,int position,int color){
	
	int array[5][6] = {};		//2d array initialized to all element=0
	int digit = val-'0';         //character to integer conversion
	
	for(int i=0;i<5;i++){
		
		for(int j=0;j<6;j++){
			
			//value of the elements in the array is made into 1's such that those digits can get their 7 segment appearence
			if(digit==0){
				if(!((i>=1)&&(i<=3)&&(j>=2)&&(j<=3)))
				array[i][j]=1;
			}
				
			else if(digit==1){
				if(j>=4)
					array[i][j]=1; 
			}
				
			else if(digit==2){
				if(!(((j<4)&&(i==1))||((j>1)&&(i==3))))
				array[i][j]=1;
			}
				
			else if(digit==3){
				if(!(((j<4)&&(i==1))||((j<4)&&(i==3))))
				array[i][j]=1;	
			}
			
			else if(digit==4){
				if(!(((i>=0)&&(i<=1)&&(j>=2)&&(j<=3))||((i>=3)&&(i<=4)&&(j>=0)&&(j<=3))))
				array[i][j]=1; 
			}
				
			
			else if(digit==5){
				if(!(((j>1)&&(i==1))||((j<4)&&(i==3))))
				array[i][j]=1; 
			}
				
			
			else if(digit==6){
				if(!(((j>1)&&(i==1))||((j==2)&&(i==3))||((j==3)&&(i==3))))
				array[i][j]=1;
			}
				
			else if(digit==7){
				if(!((i>0)&&(j<4)))
				array[i][j]=1;
			}
					
			else if(digit==8){
			if(!(((j==2)&&(i==1))||((i==1)&&(j==3))||((i==3)&&(j==2))||((i==3)&&(j==3))))
			array[i][j]=1;
			}

				
			
			else if(digit==9){
				if(!(((j==2)&&(i==1))||((i==1)&&(j==3))||((i==3)&&(j<4))))
				array[i][j]=1;
			}
				
			else{
				if(((j==2)&&(i==1))||((i==1)&&(j==3))||((i==3)&&(j==2))||((i==3)&&(j==3)))
				array[i][j]=1;
			}
		}
	}
	graphicDigit(array,position,color);

}

//function to decide the printing position of the terminal and relevant colors
void graphicDigit(int array[5][6],int position,int color){
	
	int row,column,value;
	int space;
	
	//here positions are related with system time output and spaces are related with terminal positions from the left corner
	if(position==0)
		space =2;
	else if(position==1)
		space=9;
	else if(position==2)
		space=15;
	else if(position==3)
		space=21;
	else if(position==4)
		space=28;
	else if(position==5)
		space=34;
	else if(position==6)
		space=40;
	else if(position==7)
		space=47;
	
	for(row=0;row<5;row++){
		
		for(column=0;column<6;column++){
			//allaocating locations horizontally and vertically to 2d array elements
			printf("\e[%d;%dH",row+2,column+space);
			value = array[row][column];
			if(value==0){
				printf("\e[0m"); //use ansi codes to print black spaces in 0's in the array
				printf(" ");
			}
			else if(value==1){
				printf("\e[0m");
				//in order to use the relevant color code below mentioned
				printf("\e[%dm",color+40);
				printf(" ");
			}
		}

	}
}


/* -----background colors "\e[%dm" where d is -----------
	black - 40
	red =41
	green = 42
	yellow =43
	blue = 44
	magenta =45
	cyan = 46
	white = 47
	
	------font colors "\e[%dm" where d is ---------------
	black - 30
	red =31
	green = 32
	yellow =33
	blue = 34
	magenta =35
	cyan = 36
	white = 37
*/	
	


