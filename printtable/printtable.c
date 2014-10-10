/* Author: Christopher Anzalone
*  Project: hash-based-employee-system */
/* printtable.c */
/* Create and initialize the file emp to hold all of the buckets */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LNL 2L

main()
{
	//variable declaration
	FILE  *fp;
	FILE  *fpd;

	int   nrec=0, i;
	int   del=0,off=0,nov=0, j;
	char  ssn[10], name[21];
	float sal;

	//retrieving nov val from file
	fp = fopen("../create/over", "r");
	fscanf(fp, "%d", &nov);
	fclose(fp);


	printf("SSN        NAME                 SALARY\n");

	fp = fopen("../create/emp", "r"); 

	/* sequentially print primary records */
	for(i=0;i<(10+nov);i++)
		{ 
			fseek(fp, 10, 1);	//skip over header file

			for(j=0;j<3;j++)
			{
				fscanf(fp,"%d%s%s%f",&del,ssn,name,&sal);
				if (del==0)printf("%-11s%-21s%-10.2f\n",ssn,name,sal); 
			}
		}
	printf("Print table complete");
	scanf("%d", del);
	fclose(fp);
}