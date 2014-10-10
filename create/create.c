/* Author: Christopher Anzalone
*  Project: hash-based-employee-system */
/* create.c */
/* Create and initialize the file emp to hold all of the buckets */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main ( )
{
	FILE *fp;
	int    i, j;

	/* Create primary file. */
	fp = fopen ("emp", "w");

	/* Initialize emp file with fixed length dummy records. */
	/* Assume there are 10 records in the file. */
	for (i = 0; i < 10; i++)
	{
		//header record per bucket
		fprintf (fp, "%4d%4d\n", 0, -1); 

		//create three dummy records per bucket
		for (j = 0; j < 3; j++) 
		{
			fprintf (fp, "%3d%10s%21s%10.2f\n", -1, "x", "x", 0.0); 
		}
    }
    fclose(fp);

	/* Create overflow file. */
	fp = fopen ("over", "w");
	fprintf (fp, "%4d\n", 0);   //over file initialized with 0, for 0 overflowed records

	fclose (fp);
	printf ("Create complete.\n");
	scanf("%d",&i);
}