#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

#define SIZE 8
#define MAX_FILE 1024
#define CHARS 16

int commi = 0;

char code[MAX_FILE];

char chars[16] = " ><+-.,;*&[]:0#!";

int sel = 0;
int pointer = 0;
short mem[SIZE];

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void delay(int milli_seconds) {
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + (milli_seconds*1000))
        ;
}

char * toC(char c) {
	switch(c) {
		case '>':
			return("pointer++;");
		case '<':
			return("pointer--;");
		case '+':
			return("sel++;");
		case '-':
			return("sel--;");
		case '.':
      return("sel = mem[pointer];");
      break;
    case ',':
      return("mem[pointer] = sel;");
    case ';':
      return("printf(\"\%d\", sel);printf(\"\\n\");");
    case ':':
      return("scanf(\"\%d\", &sel);"); 
    case '*':
      return("sel = pointer;");
    case '&':
      return("pointer = sel;");
    case '#':
      return("delay(mem[pointer]*10);");
    case '0':
      return("sel = 0;");
    case '!':
      return("return 1;");
		case '[':
			return("while(mem[pointer]) {");
		case ']':
			return("}");
		default:
			break;
	}
	return("");
}

int run(char c) {
  int depth = 0;
  switch(c) {
    case '>':
      pointer++;
      break;
    case '<':
      pointer--;
      break;
    case '+':
      sel++;
      break;
    case '-':
      sel--;
      break;
    case '.':
      sel = mem[pointer];
      break;
    case ',':
      mem[pointer] = sel;
      break;
    case ';':
      printf("%d", sel);
      printf("\n");
      break;
    case ':':
      scanf("%d", &sel); 
      break;
    case '*':
      sel = pointer;
      break;
    case '&':
      pointer = sel;
      break;
    case '#':
      delay(100);
      break;
    case ']':
      if(mem[pointer] != 0) {
        while(commi > 0) {
          commi--;
          if(code[commi] == ']') {
            depth++;
          }
          if(code[commi] == '[') {
            depth--;
          }
          if(depth == -1) {
            break;
          }
        }
        break;
      case '0':
        sel = 0;
        break;
      case '!':
        return 1;
      default:
        break;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
	if(argc == 2 && !strcmp(argv[1],"shell")) {
		int r = 0;
		while(!r) {
			char chr = ' ';
			scanf("%c", &chr);
			code[commi] = chr;
			r = run(code[commi]);
			commi++;
		}
	}
	else if(argc == 2) {
		char * filename = argv[1];
		FILE *file = fopen(filename, "r");
		fgets(code, MAX_FILE, file);
  	code[strlen(code)] = '\0';
  	while(code[commi] != '\0') {
    	int r = run(code[commi]);
    	commi++;
    	if(r) {
      	break;
    	}
  	}
  	fclose(file);
  	printf("Prog ended at pos: %d",pointer);
	}
	else if(argc == 4 && !strcmp(argv[1],"-d")) {
		char * filename = argv[2];
		char * compfilename = argv[3];
		
		FILE *file = fopen(filename, "r");
		fgets(code, MAX_FILE, file);
  	code[strlen(code)] = '\0';

		//Very dumb way to wipe a file but its 12am right now and I am not dealing with any more segmentation faults
  	FILE *compfile = fopen(compfilename, "w");
		fprintf(compfile,"");
		fclose(compfile);
		compfile = fopen(compfilename, "a");

  	printf("Compiling to %s",compfilename);
		printf("\n");
  	commi=0;
  	while(code[commi]) {
    	for(int i = 0;i<CHARS;++i) {
      	if(chars[i] == code[commi]){
        	fprintf(compfile,"%d",i);
        	fprintf(compfile,"%c",' ');
	        break;
	      }
    	}
    	commi++;
  	}
		fclose(compfile);
	}
	else if(argc == 4 && !strcmp(argv[1],"-c")) {
		char * filename = argv[2];
		char * compfilename = argv[3];
		
		FILE *file = fopen(filename, "r");
		fgets(code, MAX_FILE, file);
  	code[strlen(code)] = '\0';

		//Very dumb way to wipe a file but its 12am right now and I am not dealing with any more segmentation faults
  	FILE *compfile = fopen(compfilename, "w");
		fprintf(compfile,"");
		fclose(compfile);
		compfile = fopen(compfilename, "a");

  	printf("Compiling to %s",compfilename);
		printf("\n");
  	commi=0;
		fprintf(compfile,"#include<stdio.h>\n#include<time.h>\nint pointer=0;int mem[8];int sel=0;void delay(int milli_seconds) {clock_t start_time = clock();while (clock() < start_time + (milli_seconds*1000));}\nint main() {");
  	while(code[commi]) {
    	fprintf(compfile,"%s",toC(code[commi]));
    	commi++;
  	}
		fprintf(compfile,"}");
		fclose(compfile);
	}
	else if(argc == 4 && !strcmp(argv[1],"-b")) {
		char * filename = argv[2];
		char * compfilename = ".scal-bin-compc.c";
		char * comm = concat(concat("g++ -o ",argv[3])," .scal-bin-compc.c");
		
		FILE *file = fopen(filename, "r");
		fgets(code, MAX_FILE, file);
  	code[strlen(code)] = '\0';

		//Very dumb way to wipe a file but its 12am right now and I am not dealing with any more segmentation faults
  	FILE *compfile = fopen(compfilename, "w");
		fprintf(compfile,"");
		fclose(compfile);
		compfile = fopen(compfilename, "a");

  	printf("Compiling to %s",argv[3]);
		printf("\n");
  	commi=0;
		fprintf(compfile,"#include<stdio.h>\n#include<time.h>\nint pointer=0;int mem[8];int sel=0;void delay(int milli_seconds) {clock_t start_time = clock();while (clock() < start_time + (milli_seconds*1000));}\nint main() {");
  	while(code[commi]) {
    	fprintf(compfile,"%s",toC(code[commi]));
    	commi++;
  	}
		fprintf(compfile,"}");
		fclose(compfile);
		system(comm);
		remove(compfilename);
	}
	else {
		printf("Usage\n-----\nscal <filename> - run the specified scal file\nscal -b <filename> - compile the specified scal file into an executable binary\nscal -d <filename> - compile the specified scal file into a hexidecimal file\nscal -c <filename> - compile the specified scal file into a C file");
		return 0;
	}
}