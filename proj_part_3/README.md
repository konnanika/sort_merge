# DEPARTMENT OF INFORMATICS & TELECOMMUNICATIONS of NATIONAL AND KAPODISTRIAN UNIVERSITY OF ATHENS 
## SORT MERGE JOIN
###### Project: Software Development &amp; Informational Systems 

                                                                        Athanasopoulos Aleksandros
                                                                        Nika Konstantina
                                                                        Sakkas Nikitas

***

sort_merge contains the 1st part of the project and 2 directories for the next 2 parts (also 1 directory for the unit testing)

1st Part (executable : smj)
 
consts.h		:	Global variables and values
helpers.c/.h	:	Extra functions we had to create in order to do specific small jobs
Makefile		:	makefile include make clean
merged.c/.h		:	All the fuctions that use a sorted table and create the final result of a join
parser.c/.h		:	All the functions that read a table from a file and save it in our structs
smj.c/.h		:	main
sorted.c/.h		:	All the functions that use a table and create a copy of it but sorted
unsorted.c/.h	:	All the basic functions take the input from parser and save it in our structs

Everything is executed (valgrind 0 errors from 0 contexts/no segmentation or endless loop)

2nd Part (executable : sql)

consts.h		:	Global variables and values
data.c/.h		:	Structs and init functions
helpers.c/.h	:	Extra functions we had to create in order to do specific small jobs
Makefile		:	makefile include make clean
menu.c/.h		:	All the functions for the table_files menu and queries menu
merged.c/.h		:	All the fuctions that use a sorted table and create the final result of a join
queries.c/.h	:	Structs and functions need to execute a query
read.c/.h		:	All the functions used to read a binary file
sorted.c/.h		:	All the functions that use a table and create a copy of it but sorted
sql.c.h			:	main
unsorted.c/.h	:	All the functions used to copy the involved tables to a query

Everything is executed but sometimes we get a segmentation fault during the sort of a pair of tables (valgrind 0 errors from 0 contexts)

2nd Part (executable : sql)

consts.h		:	Global variables and values
data.c/.h		:	Structs and init functions
helpers.c/.h	:	Extra functions we had to create in order to do specific small jobs
Makefile		:	makefile include make clean
menu.c/.h		:	All the functions for the table_files menu and queries menu
merged.c/.h		:	All the fuctions that use a sorted table and create the final result of a join
queries.c/.h	:	Structs and functions need to execute a query
read.c/.h		:	All the functions used to read a binary file
sorted.c/.h		:	All the functions that use a table and create a copy of it but sorted
sql.c.h			:	main
unsorted.c/.h	:	All the functions used to copy the involved tables to a query

Everything is executed exept the algorithm of valuating the best order of smj execution (valgrind 0 errors from 0 contexts) (and also we didnt manage to solve the error from part 2)

***
