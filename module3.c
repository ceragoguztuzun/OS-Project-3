#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//here we have functions
void waitForUserInput() 
{
	char input = getchar();
	while( input != 'n')
	{
		input = getchar();
	}
}

int recursiveFnc(int i) 
{
   if(i <= 0) 
   {
      return i;
   }
   return recursiveFnc(i - 1);
}