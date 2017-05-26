#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>

void count(char *Opration,char *FileName);
main()
{
	int iProcId;
	char t1[30];
	char t2[30];
	char t3[30];
	char t4[30];
	int iNoOfTokens;
	char szBuffer[80];

	while(1)
	{
		printf("\n[Mayur@MYSHELL...$]");
		fflush(stdin);
		fgets(szBuffer, 80, stdin);
		iNoOfTokens = sscanf(szBuffer, "%s%s%s%s", t1, t2, t3, t4);
		switch(iNoOfTokens)
		{
			case 1 :
				iProcId = fork();
				if(0 == iProcId)
				{
					execlp(t1,t1,NULL);
				}
				else
				{
					wait();
				}
			break;

			case 2 : 
				iProcId = fork();
				if(0 == iProcId)
				{
					execlp(t1,t1,t2,NULL);
				}
				else
				{
					wait();
				}
			break;

			case 3 : 
				if(strcmp(t1,"count") == 0)
				{
					count(t2,t3);
				}
				else
				{
					iProcId = fork();
					if(0 == iProcId)
					{
						execlp(t1,t1,t2,t3,NULL);
					}
					else
					{
						wait();
					}
				}
			break;

			case 4 : 
				iProcId = fork();
				if(0 == iProcId)
				{
					execlp(t1,t1,t2,t3,t4,NULL);
				}
				else
				{
					wait();
				}
			break;
		}//switch
	}//while
}//main


void count(char *Opration,char *FileName)
{
	char ch;
	int iHandle;
	int iCharCount;
	int iWordCount;
	int iLineCount;

	iHandle = open(FileName, O_RDONLY);
	if (-1 == iHandle)
	{
		printf("Unable to open file %s\n",FileName);
		return;
	}

	iCharCount = 0;
	iWordCount = 0;
	iLineCount = 0;
	while(read(iHandle,&ch,1))
	{
		if (ch == ' ')
		{
			iWordCount++;
		}
		else if (ch == '\n')
		{
			iWordCount++;
			iLineCount++;
		}
		else 
		{
			iCharCount++;
		}
	}	

	if(strcmp(Opration, "cw") == 0)
		printf("characters=%d \twords=%d\n", iCharCount, iWordCount);
	else if(strcmp(Opration,"wl") == 0)
		printf("words=%d \tlines=%d\n", iWordCount, iLineCount);
	else if(strcmp(Opration,"cl") == 0)
		printf("charaters=%d \tlines=%d\n", iCharCount, iLineCount);
	else if(strcmp(Opration,"cwl") == 0)
		printf("characters=%d \twords=%d \tlines=%d\n", iCharCount, iWordCount, iLineCount);
	else
		printf("invalid option");

	close(iHandle);
}

