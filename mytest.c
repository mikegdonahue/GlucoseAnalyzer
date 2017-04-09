#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMDAYS 30

char *getLine (FILE *fp); /*gets line from file*/
void outputData(char *outputFile); /* outputs the data to a file passed in at argv[2] */
void parseLine(char*line, int index); /* parse the lines from the input file to tokens and get dates and data */
void printData(); /* loops through dates and data and prints to output stream */
void mallocData(); /* mallocs the arrays dates and data */
void convertToInt();
double computeAverage();
int findMax();
int findMin();

char *dates[31]; /* array of strings that stores the datas from the input file */
char *data[31]; /* array of strings that stores the data/reading from the input file */
int dataVals[30]; /* array of the data but converted to int */
double average; /* the avrg of the dataVals*/
int max; /* max of dataVals*/
int min; /* min of dataVals */

int main (int argc, char* argv[]){
    
/* open the file passed into at the start of the program
   currently only looks for argv[1] */
    
    FILE *fp;
    
    fp = fopen(argv[1],"r");
    if(fp==NULL){
        exit(EXIT_FAILURE);
    }
    else{
        printf("File found: %s\n",argv[1]);
        printf("Pulling and computing data...\n");
    }
    
    mallocData();

    
/* get name of ouputFile from argv[2]*/   
    char *outputFile;
    if(argv[2]==NULL){
        printf("No ouptput file given..\n");
        exit(EXIT_FAILURE);
    }
    else{
        outputFile = argv[2];
    }

/* get lines for correct amount of desired readings */
    int x=0;
    char *test[38];
    while(x<38){
        test[x]=malloc(sizeof(char)*26);
        test[x]=getLine(fp);
        //printf("%d: %s\n",x-6,test[x]);
        x++;
    }
    
/* parse the lines for dates and data */
    x=0;
    int a=6;
    while(x<30){
        parseLine(test[a],a);
        //printf("%d: %s\n",x,dates[x]);
        //printf("%d: %s\n",x,data[x]);
        a++;
        x++;
    }
    
/*do a quick check, see printData*/
    //printData();
    
    convertToInt();
    average = computeAverage();
    min = findMin();
    max = findMax();
    

/* calls method to output data to a file */
    outputData(outputFile);
    
    printf("End Main, exiting....\n");
    
    exit(EXIT_SUCCESS);
    
}//end Main

/* reads a line from the file of 100 chars long just to make sure you reach end of line returns this line to caller */
char *getLine (FILE *fp){
    char *line;
    line = malloc(sizeof(char)*26);
    fgets(line,100
    ,fp);
    //printf("Line Read: %s\n",line);
    return line;
}//end getLine

/* parse the line looking for the token ';' returns this new char to caller */
void parseLine(char*line, int index){
    char*tmp=strtok(line,";");
    dates[index-6]=tmp;
    tmp=strtok(NULL,";");
    tmp=strtok(NULL,";");
    data[index-6]=tmp;
    
}//end parseLine

/* output the data to the txt file passed in after the .csv (argv[2])
    assuming this is not empty */
void outputData(char *outputFile){
    
    FILE *tmp;
    tmp = fopen(outputFile,"w");
    if(tmp==NULL){
        exit(EXIT_FAILURE);
    }
    else{
        printf("Output File Opened, writing data...\n");
    }
    fputs("Glucose Meter Reading Report: Your Last 30 Days\n\n", tmp);
    fputs("Your Glucose Levels Were:\n\n", tmp);
    int x = 30;
    while(x>0){
	switch(x){
		case 30:
			fputs("Days 1 - 5\t", tmp);
			break;
		case 25:
			fputs("Days 5 - 10\t", tmp);
			break;
		case 20:
			fputs("Days 10 - 15\t", tmp);
			break;
		case 15:
			fputs("Days 15 - 20\t", tmp);
			break;
		case 10:
			fputs("Days 20 - 25\t", tmp);
			break;
		case 5:
			fputs("Days 25 - 30\t", tmp);
			break;
	}
        fputs("Date: ",tmp);
        fputs(dates[x-1],tmp);
        fputs(" -- ",tmp);
        fputs(data[x-1],tmp);
        fputs(" mg/dl",tmp);
	if((x-1)%5==0){
        	fputs("\n",tmp);
	}else{
		fputs("\t", tmp);
	}
        x--;
    }
	
	fputs("\nYour Average Glucose Level Was: ", tmp);
	fprintf(tmp, "%f\n", average);
	fputs("\nYour Lowest Glucose Level Was: ", tmp);
	fprintf(tmp, "%d\n", min);
	fputs("\nYour Highest Glucose Level Was: ", tmp);
	fprintf(tmp, "%d", max);

    
    printf("Finished, closing file.\n");
    
    //fclose(tmp); /*if you clsoe the file you get an error, trying to work this out */
    
}//end outputData

/*call this if you wish to quickly print out the info stored in dates and data
    only prints to output stream not a file */
void printData(){
    int cnt=0;
    printf("Printing data...\n");
    while(cnt<30){
        printf("%d: %s",cnt+1,dates[cnt]);
        printf(" Reading: %s\n",data[cnt]);
        cnt++;
    }
    printf("Average reading for last %d days was: %f\nMinimum reading for last %d days was: %d\nMaximum reading for last %d days was: %d\n", NUMDAYS, average, NUMDAYS, min, NUMDAYS, max);
}//end printData

/* ensures there is proper space for all the data put into these arrays */
void mallocData(){
    int cnt=0;
    while(cnt<30){
        dates[cnt]=malloc(sizeof(char)*10);
        data[cnt]=malloc(sizeof(char)*5);
//	dataVals[cnt] = malloc(sizeof(int)*3);
        cnt++;
    }
}//end mallocData

/* Converts data string array to double array */
void convertToInt(){
	int i=0;
	for(i; i<NUMDAYS; i++){
		dataVals[i] = atoi(data[i]);
	}
}//end convertToInt

/* computes the average of dataVals, aka the average of the readings */
double computeAverage(){
	int i=0;
	double sum=0.0;
	for(i; i<NUMDAYS; i++){
		sum += dataVals[i];
	}
	return sum/NUMDAYS;
}//end computeAverage

/* finds the highest data value in dataVals aka, highest reading */
int findMax(){
	max = dataVals[0];
	int i=1;
	for(i; i<NUMDAYS; i++){
		if(dataVals[i]>max){
			max = dataVals[i];
		}
	}
	return max;
}//end findMax

/* finds min data value in dataVals aka, lowest reading */
int findMin(){
	min = dataVals[0];
	int i=1;
	for(i; i<NUMDAYS; i++){
		if(dataVals[i]<min){
			min = dataVals[i];
		}
	}
	return min;
}//end findMin
