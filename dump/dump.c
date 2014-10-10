/* Author: Christopher Anzalone
*  Project: hash-based-employee-system */
/* dump.c */
/* Print emp and over exactly as they are. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main ( )
{ 
	int i;

	printf("emp\n");
	system("type ..\\create\\emp");

	printf("over\n");
	system("type ..\\create\\over");
	scanf("%d", &i);
}