/* Author: Christopher Anzalone
*  Project: hash-based-employee-system */
/* File name: find.c */
/* contains find function which finds the record with 
   SSN*/
/* find function returns open file pointer that is 
   positioned to found record, or 0 if the record is not found. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LNL 2L

FILE  * find(char * key)  /* key is pointer to SSN */

{
	FILE  *  fp;
	int   x, h, nrec, i, j;
	long  off, offr;
	int   del;
	char  ssn[10], name[21];
	float sal;
	int ovptr;

	for (i = x = 0; key[i] != 0; i++)
	{
		x = x + key[i];
	}

	h = x % 10;  /* calculate hash value */
	off = h * (44 + LNL);  /* convert slot number to offset */

	fp = fopen("../create/emp", "r+");  /* check primary file emp */
	fseek (fp, off, 0);  /* go to hash position in primary file emp */

	for (i = h/*hasbucketnumber*/; i != -1; i = ovptr)
	{
		/*Calculate the offset of header record of ith bucket*/
		off = i * (10L + 3 * (3+10+21+10+2));

		/*fseek to the desired header record using the offset*/
		fseek(fp, off, 0);  
		
		/*scan the header record*/
		fscanf(fp, "%d%d", &nrec, &ovptr);
		

		//scan records of bucket
		for (j=0; j < nrec; j++)
		{
			offr = ftell(fp) + 2; //Remember offset of record about to be read, will be useful in remembering the first deleted record below

			/*Read entire employee record (thus also moving the position of the file ptr stream to the area/byte of the next record*/
			fscanf (fp, "%d%s%s%f", &del, ssn, name, &sal); 

			/*if the record is alive and ssn of employee record we read is the ssn we are trying to insert
			then there is a duplicate, living, record of this individual stored already and so we abort*/
			if ( (del == 0) && (strcmp(ssn, /*issn*/key) == 0) )
			{
				fseek(fp, offr, 0);  //offset to record location that was recorded before the scanf
				return fp;  //return file pointer location of record
			}
		} //j loop - record loop
	}

	fclose(fp);
	return 0;
}










///* check overflow file */
//fclose(fp);
//fp = fopen ("../create/over", "r+");
//
//fscanf (fp, "%d", &nrec);  /* read overflow file header */
///* sequentially search overflow file */
//for (i = 0; i < nrec; i++)
//  {
//    off = LNL + ftell (fp);  /* remember the position of next record */
//    fscanf (fp, "%d%s%s%f", &del, ssn, name, &sal);  /* read entire 
//                            record to get past it for next iteration */
//
//    if (del == 0 && (strcmp (key,ssn) == 0))  /* record found, return 
//                                                 open file pointer */
//    {
//      fseek (fp, off, 0);
//      return fp;
//    }
//  }
//fclose (fp);
//return 0;  /* record not found, return 0 */
//}
