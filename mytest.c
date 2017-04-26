#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXDAYS 120 /* prevent overflow by the usr */
#define PATH_BUFFER 400 /* buffer for path provided by usr */
#define BUFFER 200 /* general buffer */ 
size_t LINE_BUFF = 200;

void openFile(char *outPut,char *settingsFile); /* opens the files */
void getSettings(); /* idea for importing settings from an extra .txt file for various outputs */
void importLines(); /* calls parseLine, getLine */
char *getLine (FILE *fp); /* gets line from file */
void parseLine(char*line, int index); /* parse the lines from the input file to tokens and get dates and data */
void printData(); /* loops through dates and data and prints to output stream */
void mallocData(); /* mallocs the arrays dates and data */
void calcData(); /* calls converToInt, computeAverage, findMax, findMin */
void convertToInt(); /* convert the data to ints for dataVals*/
double computeAverage(); /* computes the average in dataVals */
int findMax(); /* find the max in dataVals */
int findMin(); /* find the min in dataVals */
void outputData(char *outputFile); /* outputs the data to a file passed in at argv[2] */
void createPlotFile(); /* creates a file to be used for plotting purposes */
void generateHTMLFile();/* generates the html file */
void generatePlotFile(); /* gens plot */
void pushToWebsite(); /* see this func for more info*/

FILE *fp; /* file pointer with argv[1] */
FILE *settings; /* settings file */
char *outputFile; /* file pointer with argv[2] if passed in */
char *dataPath; /* path where data.csv file is, if NULL defaults to current dir */
int pushWebsite = 0; /* wheter or not to push to a website check line here for how you want this system call to work*/
char *dates[MAXDAYS]; /* array of strings that stores the datas from the input file */
char *data[MAXDAYS]; /* array of strings that stores the data/reading from the input file */
int dataVals[MAXDAYS]; /* array of the data but converted to int */
double average; /* the avrg of the dataVals*/
int max; /* max of dataVals*/
int min; /* min of dataVals */
int NUMDAYS; /* num of days to pull by the usr in the settings file */

int main (int argc, char* argv[]){
    
    openFile(argv[1],argv[2]);
    
    getSettings();

    importLines();
    
    calcData();
    
    printData();
    
    outputData(outputFile);

    createPlotFile();
    
    generateHTMLFile();

    generatePlotFile();

    pushToWebsite();
 
    printf("End Main, exiting....\n");
    
    exit(EXIT_SUCCESS);
    
}//end Main

/* opens the files passed into argv[] */
void openFile(char *outPut,char *settingsFile){
    
/* open settings file */ 
    settings = fopen(settingsFile,"r");
    
    if(settings==NULL){
        printf("Settings File Not Found...\n");
        exit(EXIT_FAILURE);
    }
    
    //mallocData();
    
/* get name of ouputFile from argv[1]*/ 
    if(outPut==NULL){
        printf("No ouptput file given..\n");
        exit(EXIT_FAILURE);
    }
    else{
        outputFile = outPut;
    }

}//end openFile

/* looks at the settings files and thus affects the overall settings, also opens the input file */
void getSettings(){
    int numDays=0;
    dataPath = malloc(sizeof(char)*PATH_BUFFER);
    fscanf(settings,"%d",&numDays);
    if(numDays==0){
        numDays=30;
    }
    fscanf(settings,"%s",dataPath); 
    if((strcmp(dataPath,"null")!=0)&&(strcmp(dataPath,"")!=0)){
        printf("Path: %s\n",dataPath);
        if((fp = fopen(dataPath,"r"))==NULL){
            printf("Error opening data file...\n");
            exit(EXIT_FAILURE);
        }
    }else{//default 
        printf("No input path found, defaulting to current dir...\n");
        dataPath = "diary.csv";
        if((fp = fopen(dataPath,"r"))==NULL){
            printf("Error opening data file...\n");
            exit(EXIT_FAILURE);
        }
    }
    fscanf(settings,"%d",&pushWebsite);

    if(pushWebsite==0){
	printf("PushtoWebsite? NO\n");
    }else{
	printf("PushtoWebsite? Yes\n");
    }

    if(numDays==0){//default 
        NUMDAYS = 30;
    }
    if(numDays>MAXDAYS){
        printf("numDays to large defaulting to MAXDAYS (120)...\n");
        NUMDAYS=MAXDAYS;
    }else{
        NUMDAYS=numDays;
    }
    printf("Settings File Found numDays: %d\n",numDays);

}


/* does some loops and calls getLine and parseLine to import the data of the file */
void importLines(){

/* get lines for correct amount of desired readings */
  fseek(fp,399,SEEK_SET);//seek to first needed line of dates and data	//WAS 393
  char c;
    int x=0;
    char *test[NUMDAYS];
    while(x<NUMDAYS){
        test[x]=malloc(sizeof(char)*LINE_BUFF);
        test[x]=getLine(fp);
        x++;
	//fseek(fp, 1, SEEK_CUR);
    }
    
/* parse the lines for dates and data */
    x=0;
    int a=0;
    while(x<NUMDAYS){
        parseLine(test[a],a);
        a++;
        x++;
	//free(test[a]);
    }

}//end importLines

/* reads a line from the file of 100 chars long just to make sure you reach end of line returns this line to caller */
char *getLine (FILE *fp){
    char *line;
    line = malloc(sizeof(char)*LINE_BUFF);
    getline(&line,&LINE_BUFF,fp);
    //fseek(fp,1,SEEK_CUR);
    //printf("Line Read: %s\n",line);
    return line;
}//end getLine

/* parse the line looking for the token ';' returns this new char to caller */
void parseLine(char*line, int index){
    char*tmp=strtok(line,";");
    dates[index]=tmp;
  tmp=strtok(NULL,";");
    tmp=strtok(NULL,";");
    data[index]=tmp;
}//end parseLine

/*call this if you wish to quickly print out the info stored in dates and data
    only prints to output stream not a file */
void printData(){
    int cnt=0;
    printf("Printing data...\n");
    while(cnt<NUMDAYS){
        printf("%d: %s",cnt+1,dates[cnt]);
        printf(" Reading: %s",data[cnt]);
        printf(" DataVal: %d\n",dataVals[cnt]);
        cnt++;
    }
    printf("Average reading for last %d days was: %f\nMinimum reading for last %d days was: %d\nMaximum reading for last %d days was: %d\n", NUMDAYS, average, NUMDAYS, min, NUMDAYS, max);
}//end printData

/* ensures there is proper space for all the data put into these arrays */
void mallocData(){
    int cnt=0;
    while(cnt<NUMDAYS){
        dates[cnt]=malloc(sizeof(char)*10);
        data[cnt]=malloc(sizeof(char)*5);
        //dataVals[cnt] = malloc(sizeof(int)*3);
        cnt++;
    }
}//end mallocData

/*calls methods to calc the data in dataVals just used to clean up the main*/
void calcData(){
    convertToInt();
    average = computeAverage();
    min = findMin();
    max = findMax();
}

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
    fputs("Glucose Meter Reading Report: Your Last ", tmp);
    fprintf(tmp, "%d", NUMDAYS);
    fputs(" Days\n\n", tmp);
    fputs("Your Glucose Levels Were:\n\n", tmp);
    int x = NUMDAYS;
    int count=0;
    while(x>0){
	if(x%5==0){
		fputs("Days ", tmp);
		fprintf(tmp, "%d", (count*5)+1);
		fputs(" - ", tmp);
		fprintf(tmp, "%d\t", (count*5)+5);
		count++;
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

/* creates a file that is formatted to use with plotter */

void createPlotFile(){
	FILE *fp = fopen("plotdata.dat", "w");
	int i=NUMDAYS;
	while(i>0){
//	for (i; i>0; i--){
		fprintf(fp, "%d", i);
		fputs("\t", fp);
		fputs(data[i-1], fp);
		fputs("\n", fp);
		i--;
	}
	fclose(fp);
}//end createPlotFile

/* generate the HTML */

void generateHTMLFile(){
	FILE *site = fopen("index.html", "w");
	int i=0;
	fputs("<!DOCTYPE html>\n<head>\n<link rel=\"stylesheet\" href=\"styles.css\">\n", site);
	fputs("<title>My Glucose Levels</title>\n</head>\n<body>\n", site);
	fputs("<h1>Blood Glucose Levels for the Last ", site);
	fprintf(site, "%d", NUMDAYS);
	fputs(" Days</h1><br>\n", site);
	fputs("<table>\n<tr>\n<th>Average Level</th>\n<th>Lowest Level</th>\n<th>Highest Level</th>\n</tr>\n", site);
	fputs("<tr>\n<td>", site);
	fprintf(site, "%f", average);
	fputs("</td>\n<td>", site);
	fprintf(site, "%d", min);
	fputs("</td>\n<td>", site);
	fprintf(site, "%d", max);
	fputs("</td>\n</tr>\n</table><br><br>", site);
	fputs("<img src=\"output.jpg\" alt=\"Glucose Graph\"><br><br>\n<table>\n<tr>\n<th>Date</th>\n<th>Glucose Level (mg/dL)</th>\n</tr>\n", site);
//Put in all the data here!!
	for(i; i<NUMDAYS; i++){
		fputs("<tr>\n", site);
		fputs("<td>", site);
		fprintf(site, "%s", dates[i]);
		fputs("</td>\n<td>", site);
		fprintf(site, "%d", dataVals[i]);
		fputs("</td>\n", site);
		fputs("</tr>\n", site);
	}
	fputs("</table>\n</body>\n</html>", site);
	fclose(site);
}

/* this calls the script plot that makes the .jpg */
void generatePlotFile(){
	int ret = system("gnuplot 'plot'");
	printf("plotret: %d\n",ret);
	sleep(2);
}

/* function to push the html file to a website*/
void pushToWebsite(){
	if(pushWebsite==1){
		int ret = system("./sitepush.sh"); /* here is where you would edit if you wanted to change what site to push to see sitepush.sh */
		printf("webpushret: %d\n",ret);
	}else{
		return;
	}
}
