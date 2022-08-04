#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif

#define MEM 1024
#define DEBUG 0

int memory[MEM];
int reg = 0;

int ptr = 0;

int max =0;
char ** code;

char ** split (char * str, char * c)
{
  char *strout[1024];
	char *token = strtok(str, c);
	strout[0]=token;
   int i = 1;
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
		{
      token = strtok(NULL, c);
			strout[i]=token;
			++i;
    }
	max=i-1;
	char * ret[max];
	for(i=0;i<max;++i) {
		ret[i]=strout[i];
	}
	return ret;
}

void remove_spaces (char* restrict str_trimmed, const char* restrict str_untrimmed)
{
  while (*str_untrimmed != '\0')
  {
    if(!isspace(*str_untrimmed))
    {
      *str_trimmed = *str_untrimmed;
      str_trimmed++;
    }
    str_untrimmed++;
  }
  *str_trimmed = '\0';
}

void compile(char * raw) {
	//Step 1: Remove whitespace (+23)
	//Step 2: Isolate all command-number pairs (e.g + 23 )
	//Step 3: Check if adjacent number (3a) or macro (3b)
	//Step 3a: Convert to 3 digets (+023)
	//Step 3b: Fill macros (;* -> ;000)

	//Step 1:
	char *rawb = strdup(raw);
	char *write = rawb, *read = rawb;
	do {
   if (*read != ' ')
       *write++ = *read;
	} while (*read++);
	//Step 2:
	code = split(rawb,"\n");
	//Step 3:
	FILE *fptr;
  fptr = fopen(".scaleton-comp","w");
	fprintf(fptr,"");
	fclose(fptr);
	fptr = fopen(".scaleton-comp","a");
	
	for(int i=0;i<max;++i) {
		//All this is just to ignore any chars after the first 4
		int size = strlen(code[i]);

		if(size>4) {
			size=4;
		}

		char line[size];

		//While your at it, fill in some macros
		for(int n=0;n<size;++n) {
			line[n]=(code[i])[n];
			if(line[n]=='*'){
				line[n]='0';
			}
		}
		char c = line[0];
		if(size>1) {
			
			//Step 3a
			char val[] = " 000";
			int vali = 0;
			while(size-vali>1) {
				val[strlen(val)-1-vali] = line[size-1-vali];
				++vali;
			}
			val[0] = c;

			strcpy( line, val );
			code[i] = line;
		}
		fprintf(fptr,code[i]);
		fprintf(fptr,"\n");
	}
	fclose(fptr);
}

void intrpt(int id) {
	switch(id) {
		case 000:
			printf("Program ended (interupt 0)\n");
			exit(0);
		default:
			break;
	}
}

void run(char c[4]) {
	int val = (c[3] - 48) + ((c[2] - 48)*10) + ((c[1] - 48)*100);
	switch(c[0]) {
		case '+':
			reg+=val;
			break;
		case '-':
			reg-=val;
			break;
		case '.':
			memory[val-1] = reg;
			break;
		case ',':
			reg = memory[val-1];
			break;
		case '=':
			reg = val;
			break;
		case '>':
			if(reg) {
				ptr+=val;
			}
			break;
		case '<':
			if(reg) {
				ptr-=val;
			}
			break;
		case ';':
			if(val==000) {
				printf("%c",reg);
			}
			else {
				printf("%c",memory[val-1]);
			}
			break;
		case '!':
			intrpt(val);
			break;
		default:
			break;
	}
}

char * openfile(char filename[]) {
	char * buffer;
	long length;
	FILE * f = fopen (filename, "r");

	if (f)
	{
  fseek (f, 0, SEEK_END);
  length = ftell (f);
  fseek (f, 0, SEEK_SET);
  buffer = malloc (length+1);
  if (buffer)
  {
    fread (buffer, 1, length+1, f);
  }
  fclose (f);
	}
	buffer[length]=0;
	return buffer;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("Usage:\nscal <filename>\n");
	}

	compile(openfile(argv[1]));

	code = split(openfile(".scaleton-comp"),"\n");
	remove(".scaletone-scomp");
	
	for(ptr=0;ptr<max;++ptr){
		if(DEBUG) {
			printf("%d",ptr);
			printf(" ");
			printf(code[ptr]);
			printf("\n");
		}
		run(code[ptr]);
	}
}
