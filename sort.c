#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

//sort here
void sort(char ** str, int n, int firstSortStr) 
{ 
	if(firstSortStr >= n)
	{
		return;
	}
	
	char temp[1024] = "\0";
	
	for(int i = firstSortStr - 1; i<n; i++) 
      for(int j = i+1; j < n;j++)
      {
		  
         if(strcmp(str[i],str[j]) > 0)
         {
            strcpy(temp,str[i]);
            strcpy(str[i],str[j]);
            strcpy(str[j],temp); 
         }
      
      }
} 
  
//Reverse Sort
void ReverseSort(char **str, int n, int firstSortStr)
{
	if(firstSortStr > n)
	{
		return;
	}
	
	char temp[1024] = "\0";
	
	for(int i=firstSortStr -1; i<n; i++) 
      for(int j = i+1; j < n;j++)
      {
		  
         if(strcmp(str[i],str[j]) < 0)
         {
            strcpy(temp,str[i]);
            strcpy(str[i],str[j]);
            strcpy(str[j],temp); 
         }
      
      } 
}

//Integer Sort
void sortByInteger(char **str, int n,int firstSortStr)
{
	if(firstSortStr > n)
	{
		return;
	}
	
	char temp[1024] = "\0";
	
	int a;
	int b;
	
	for(int i=firstSortStr - 1; i<n; i++) 
      for(int j = i+1; j < n;j++)
      {
		a = 0;
		b = 0;
        sscanf(str[i],"%d",&a);
		sscanf(str[j],"%d",&b);
		if(a > b)
         {
            strcpy(temp,str[i]);
            strcpy(str[i],str[j]);
            strcpy(str[j],temp); 
         }
      
      }
}

//Reverse Integer Sort
void reverseSortByInteger(char **str, int n, int firstSortStr)
{
	if(firstSortStr > n)
	{
		return;
	}
	
	char temp[1024] = "\0";
	
	int a;
	int b;
	
	for(int i=firstSortStr -1; i<n; i++) 
      for(int j = i+1; j < n;j++)
      {
		a = 0;
		b = 0;
        sscanf(str[i],"%d",&a);
		sscanf(str[j],"%d",&b);
		if(a < b)
         {
            strcpy(temp,str[i]);
            strcpy(str[i],str[j]);
            strcpy(str[j],temp); 
         }
      
      }
}
//Printing array
void PrintString(char ** str, int size) 
{ 
    int i;
    //printf("\n"); 
    for (i=0; i < size; i++) 
	printf("%s",str[i]); 
     
} 


int main(int argc, char **argv)
{
	
	//flag declaration
	int mn_flag = 0;
	int r_flag = 0;
	int o_flag = 0;
	int pn_flag = 0;
	
	//File pointer declaration
	FILE *fp;
	FILE *fpoflag;//for o_flag
	
	char * outfile = malloc(sizeof(char) * 64);
	
	int i = 1;
	int num = 1;
	
	//Parameter Check
	if(argc == 1)
	{
		printf("No option specified\n");
		return -1;
	}
	
	//Parsing options
	while((argv[i][0] == '-') || (argv[i][0] == '+'))
	{
		if(strcmp(argv[i],"-n") == 0)
		{
			mn_flag = 1;
		}
		else if(strcmp(argv[i],"+n") == 0)
		{
			pn_flag = 1;
			num = atoi(argv[i+1]);
			i++;
		}
		else if(strcmp(argv[i],"-r") == 0)
		{
			r_flag = 1;
		}
		else if (strcmp(argv[i],"-o") == 0)
		{
			o_flag = 1;
			strcpy(outfile,argv[i+1]);
			i++;
		}
		else
		{
			printf("Incorrect Option\n");
			return -1;
		}
		i++;
	}
	
	//Opening Files
	int maxlength = 0;
	int stringcounter = 0;
	
	char * buf = malloc(sizeof(char) * 1024);
	
	for(int j=i; j<argc;j++)
	{
		fp = fopen(argv[j],"r");
		if(fp == NULL)
		{
			printf("Cannot open file\n");
			return -1;
		}
		while(fgets(buf,1024,fp) != NULL)
		{
			if(strlen(buf) > maxlength)
			{
				maxlength = strlen(buf);
			}
			stringcounter++;
		}
		fclose(fp);
	}
	
	char ** strStore = malloc(sizeof(char *) * stringcounter);
	
	int k=0;
	for(int j=i; j<argc;j++)
	{
		fp = fopen(argv[j],"r");
		if(fp == NULL)
		{
			printf("Cannot open file\n");
			return -1;
		}
		
		while(! feof(fp))
		{
			char * tempString = malloc(sizeof(char) * (maxlength + 1)); 
			
			if (fgets(tempString,1024,fp))
			{
				strStore[k] = tempString;
				k++;
		    }
		    else
		    {
				free(tempString);
			}
		} 
		
		fclose(fp);
	}
	
	
    //Checking if -r is present
	if(r_flag == 0)
	{
		if(mn_flag == 0)
		{
			sort(strStore,stringcounter,num);
		}
		else
		{
			sortByInteger(strStore,stringcounter,num);
			
		}
	}
	else
	{
		//Checking for -n flag
		if (mn_flag == 0)
		{
			ReverseSort(strStore,stringcounter,num);
		}
		else
		{
			reverseSortByInteger(strStore,stringcounter,num);
			
		}
	}
    
    //Checking for -o flag
	if(o_flag == 1)
	{
		fpoflag = fopen(outfile,"w");
		
		if(fpoflag == NULL)
		{
			printf("Cannot open file\n");
			return -1;
		}
		
		for(int j=0;j<stringcounter;j++)
		{
			fprintf(fp,"%s",strStore[j]);
		}
		
	}
	else 
	{
		PrintString(strStore,stringcounter);
	}
	
	//Cleaning Memory
	for(int k=0;k<stringcounter;k++)
	{
		free(strStore[k]);
	}
	free(strStore);
	free(outfile);
	free(buf);
	
	return 0;
}
