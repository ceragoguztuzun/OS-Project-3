#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

// main fnc
int main(void) 
{	 
	// data accessed from module2.c and module3.c
	extern int a[4096];
	extern int b[32];
	extern long* c;
	extern long* d;
	extern void* mainPtr;
	extern long* pointerToSharedMemory;
	extern int recursiveFnc(int i); 
	extern void waitForUserInput();


	// STEP 1
	printf("---STEP 1---\n");
	printf("%s%lx\n", "Address of main fnc: ",(void *) main);
	printf("%s%lx\n", "Address of uninitialized array: ",(void *) a);
	printf("%s%lx\n", "Address of initialized array: ",(void *) b);
	printf("%s%lx\n", "Address of user input fnc: ",(void *) waitForUserInput);
	printf("%s%lx\n", "Address of printf: ",(void *) printf);
	printf("%s%d\n", "PID: ",getpid());

	waitForUserInput();

	// STEP 2
	printf("---STEP 2---\n");
	c = malloc(125000);
	d = malloc(125000);
	printf("%s%lx\n", "Address of dynamically allocated data 1: ",(void *) c);
	printf("%s%lx\n", "Address of dynamically allocated data 2: ",(void *) d);

	waitForUserInput();

	// STEP 3
	printf("---STEP 3---\n");
	recursiveFnc(12500);
	printf("%s%lx\n", "Address of main fnc: ",(void *) main);
	printf("%s%lx\n", "Address of uninitialized array: ",(void *) a);
	printf("%s%lx\n", "Address of initialized array: ",(void *) b);
	printf("%s%lx\n", "Address of user input fnc: ",(void *) waitForUserInput);
	printf("%s%lx\n", "Address of printf: ",(void *) printf);
	printf("%s%lx\n", "Address of dynamically allocated data 1: ",(void *) c);
	printf("%s%lx\n", "Address of dynamically allocated data 2: ",(void *) d);
	printf("%s%lx\n", "Address of recursive fnc: ",(void *) recursiveFnc);

	waitForUserInput();

	// STEP 4
	printf("---STEP 4---\n");
	pointerToSharedMemory = mmap(NULL, 250000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
	printf("%s%lx\n", "Address of start address: ",(void *) pointerToSharedMemory);

	waitForUserInput();

	// STEP 5
	printf("---STEP 5---\n");
	pointerToSharedMemory[0] = 123;
	pointerToSharedMemory[1] = 456;
	pointerToSharedMemory[2] = 789;
	printf("%s%d\n", "data read: ",pointerToSharedMemory[0]);
	printf("%s%d\n", "data read: ",pointerToSharedMemory[1]);
	printf("%s%d\n", "data read: ",pointerToSharedMemory[2]);

	printf("%s%lx\n", "Adrs of data read from memory mapped region: ",(void *) pointerToSharedMemory[0]);
	printf("%s%lx\n", "Adrs of data read from memory mapped region: ",(void *) pointerToSharedMemory[1]);
	printf("%s%lx\n", "Adrs of data read from memory mapped region: ",(void *) pointerToSharedMemory[2]);

	waitForUserInput();

	// STEP 6
	printf("---STEP 6---\n");
	mainPtr = (void *) (4096 * (((long unsigned int) main) / 4096)); 

	for (int i = 0; i < 4096; i++)
	{
		// address
		printf("%lx -> %02x\n", (long unsigned int) (mainPtr + i), ((char *)(mainPtr))[i]);
		// corresponding content
		//printf("%02x\n", ((char *)(mainPtr))[i]);
	}

	waitForUserInput();
	printf("end of program\n");

	return 0;
}