/* Author: Christopher Anzalone
*  Project: hash-based-employee-system */
/* retrieve.c */
/* retrieve and print an employee record with given SSN */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE	* find(char * key);  /* declare find function */

main ( )
{
  FILE * fp;
  char rssn[10];
  int del;
  char ssn[10], name[21];
  float sal;

  printf("Please enter SSN\n");
  scanf ("%s", rssn);

  fp = find(rssn);	
  if (fp == 0)
  {
    printf("SSN not found\n");
	scanf("%s",ssn);
    exit(1);
  }

  fscanf (fp, "%d%s%s%f", &del, ssn, name, &sal);
  printf ("ssn = %s name = %s salary = %10.2f\n", ssn, name, sal);
  fclose(fp);
  printf ("retrieve complete\n");
  scanf("%s",ssn);
}
