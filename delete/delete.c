/* Author: Christopher Anzalone
*  Project: hash-based-employee-system */
/* delete.c */
/* delete employee record using find function */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE * find(char * key);  /* declare find function */

main ( )
{
  FILE * fp;
  char ssn[10];

  printf("Please enter the SSN of the employee to be fired.\n");
  scanf ("%s", ssn);

  fp = find (ssn);  /* find returns 0 or open file pointer positioned to 
                       beginning of found employee record */

  if (fp == 0)  /* employee not found */
  {
    printf("Employee does not exist.\n");
	scanf("%s",ssn);
    exit(1);
  }

  fprintf (fp, "%3d", 1);  /* employee found, set delete flag for employee */

  fclose(fp);
  printf("Firing complete.\n");
  scanf("%s",ssn);
}
