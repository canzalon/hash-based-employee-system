/* Author: Christopher Anzalone
*  Project: hash-based-employee-system */
/* insert.c */
/* Insert a record into employee table. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LNL 2L
main ( )
{
	FILE * fp;
	FILE * fpd = 0; 

	char issn[10], iname[21]; /* emp record to insert */
	float isal;

	int del;  /* delete flag */
	char ssn[10], name[21]; /* emp record read from file */
	float sal;
	int h;  /* hash value = (key % 10) */
	long off;  /* offset */
	int x;  /* integer value of primary key string issn */
	int i;
	int nrec;  /* number of records in overflow (of current chain) */

	/*additional vars*/
	int j, z; 
	int ovptr;  //value of next bucket in the current chain
	int offr; //offset for current record being read (in bucket)
	int nov;  //number of overflowed buckets; used for storing value in over file
	

	fp = fopen ("../create/emp", "r+");
	printf ("Please enter SSN, name and salary separated by blanks\n");
	scanf ("%s%s%f", issn, iname, &isal);
 

	/* convert primary key string to integer */
	for ( x = i = 0; issn[i]!=0; i++)
	{
		x = x + issn[i];
	}

	h = x  % 10;/* convert integer value of primary key to slot number */

	  //current bucket
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
			if ( (del == 0) && (strcmp(ssn, issn) == 0) )
			{
				printf("Error!!!SSN all ready Exist, aborting the insert.");
				fclose(fp);   //close file
				scanf("%d", &del);  //clear buffer or something?
				exit(1);     //exit program; code 1 indicates unsuccessful insert.
			}

			/*if a dead record is encountered in this current bucket, save its location with fpd file pointer, using the offset recorded
			in offr to set fpd's position indicator of the file stream to the location of the appropriate employee record*/
			if ( del == 1 )
			{
				fpd = fopen("../create/emp", "r+");  //open emp file with read only status using fpd file pointer
				fseek(fpd, offr, 0);     //save position indicator to file stream object for emp file
			}
		} //j loop - record loop
	}

	/*if a deleted record was found (iow, if fpd file ptr holds a value for a position indicator)*/
	if (fpd != 0)
	{
		fprintf(fpd, "%3d%10s%21s%10.2f\n", 0, issn, iname, isal);
		fclose(fpd);
	}
	else if (nrec < 3)  /*if there are less than 3 records in the bucket, insert record into this last bucket encountered in i loop*/
	{
		/*navigate to the next line, after the last record in bucket, and print new employee record*/
		fseek(fp, 2L/*LNL*/, 1/*SEEK_CUR*/);  //fp indicator is at the end of the last known record in bucket, fseek to the next line for new record
		fprintf(fp, "%3d%10s%21s%10.2f\n", 0, issn, iname, isal);  //print new record into open row of bucket (0 indicates living record)

		/*Modify header of bucket to reflect the addition of the new employee record to it*/
		fseek(fp, off, 0/*SEEK_*/); //fseek to 'off' offset in emp file. note: 'off' is still positioned at the header of the bucket, following the i-loop above
	
		fprintf(fp, "%4d", ++nrec); 
		
	}
	else /*if no deleted record was found, and there is no empty slot in the last bucket of the chain, then create a new bucket on the overflow chain*/
	{
		fpd = fopen("../create/over", "r+");   //open 'over' file in read mode with fpd file pointer
	  
		fscanf(fpd, "%d", &nov);  //read in number of overflowed buckets into nov

		// fclose(fpd);  //close fpd object

		/*set ovptr in the header of the last bucket encountered to (10+nov)*/
		fseek(fp, off, 0/*SEEK_BEG*/);  //fseek to the header of the current bucket; note: 'off' still positioned at the header of the bucket
		fprintf(fp, "%4d%4d\n", nrec, 10+ nov);  //modify the header record using the same nrec, but changing the ovptr to connect the last bucket to the new one

		/*Create new bucket, at the end of emp file (logically, at the end of the current overflow chain)*/
		fseek(fp, 0L, 2/*SEEK_END*/); //move fpd file pointer to the end of the emp file
		fprintf (fp, "%4d%4d\n", 1, -1);   //create header, with record count at 1 (for new record), and the ovptr at -1 (it's at the end of the chain)
		fprintf(fp, "%3d%10s%21s%10.2f\n", 0, issn, iname, isal);   //populate first record slot with new employee record

		/*Create two dummy records at the end of the new bucket*/
		for (z = 0; z < 2; z++) 
		{
			fprintf (fp, "%3d%10s%21s%10.2f\n", -1, "x", "x", 0.0); 
		}
		fseek(fpd, 0L,0);
		fprintf(fpd, "%4d\n", ++nov);
		fclose(fpd);

		/*Change value of nov count in the 'over' file*/
		
	//}  


}  //i loop - bucket loop

	fclose(fp);
	
	printf("Insert complete.\n");
	scanf("%d", &del);

	exit(0);  //exit, successful insert.

}