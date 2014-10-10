hash-based-employee-system
==========================

This hash based employee system uses the external chaining with bucketed primary and bucketed overflow as its collision resolution method for handling employee insertion. 

An employee table is produced in a file named "emp," which contains the primary area. This primary file contains the first 10 buckets, with the overflow area being stored in it as well. A file named "over" contains a number representing the amount of buckets that are currently in the overflow area. Each bucket contains three records, and a header with the number of logical records in the bucket, along with the number of the next bucket on the overflow chain. 

The project contains the following programs: create, dump, insert, print table, delete, and retrieve. The program names are self-explanitory: create initializes the emp and over files, dump prints the information to the respective files in the directory, insert allows for insertion of employee data, print table prints the contents of the buckets to the console, delete allows the removal of particular employee records, and retrieve allows for the retrieval of a certain employee's records. 
