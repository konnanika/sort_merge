# DEPARTMENT OF INFORMATICS & TELECOMMUNICATIONS of NATIONAL AND KAPODISTRIAN UNIVERSITY OF ATHENS 
## SORT MERGE JOIN
###### Project: Software Development &amp; Informational Systems 

                                                                        Athanasopoulos Aleksandros
                                                                        Nika Konstantina
                                                                        Sakkas Nikitas

***
This project is about the «Sort Merge Join Algorithm». It includes 6 .c programs and 7 .h programs. 
The main program is the smj.c, which calls all the other processes / programs. These programs are:

 - Parser.c
 - Helpers.c
 - Unsorted.c
 - Sorted.c
 - Merged.c
 
 With their libraries:
 
 - Parser.h
 - Consts.h
 - Helpers.h
 - Unsorted.h
 - Sorted.h
 - Merged.h
 
The main program’s arguments are inserted by the users.
At first, it checks the arguments and then parsers them. After that, it creates the bin tables for the process of sorting both of the tables. Finally, the program shuts down and it deallocates the memory.
In greater detail, we are going to explain all the processes that we used into the project.

1. Parser.c: it includes one process parse_input_file that parses the 2 files and fills 2 unsorted tables.  Into this process we need to convert a string to uint64_t.
2. Helpers.c: It contains the process atouint64_t, which converts a string to uint64_t and returns the number written in the string.
3. Unsorted.c: It contains the following processes:
   - *Init_unsorted_tables*: for the initialization of the 2 unsorted tables
   - *fill_bin_table*: Fill, for each unsorted_record, a table (the size of the tables is 8 bytes) where each element has the unsigned value of each byte
   - *print_unsorted_table*: Print an unsorted table
4. Sorted.c: It contains the following processes:
   - *init_sorted_tables*: for the initialization of  the 2 sorted tables
   - *init_histogram*: Initialization of the histrogram table
   - *init_psum*: initialization of the psum table
   - *print_sorted_table*: printing the sorted_table
   - *sort*:This process has to be analyzed because is the main process. Firstly reads an unsorted table and fills the histogram and then the psum table. After that, It reads, again, the unsorted table, but in 1 position of the histogram. We have 3 statements of “if”. The first checking is for the last byte of the table. We insert the records to the sorted table after the checking. If we are in the case that the records are less than 8192 ( <64Kb) then we run quicksort and insert the records to the sorted table. And the third statement, we run the sort recursively if we can’t use the *quicksort*. 

5. Merged.c: It contains the following processes:
   - *init_buffer*: for the initialization of the buffer
   - *new_buffer*: creation a new buffer
   - *destroy_buffers*: destroy all the buffers
   - *print_merged_table*: printing the merged_table
   - *merge*: This is the main process. Firstly, It reads the records from 	the first sorted table_1 one by one, from the starting point to the end. From the first reading record in table_1, it reads the records, one by one, from the second sorted table_2. In the loop, if the record from table_1 is higher from the record from table_2 then reads the next of last in table_2. Else if the record from table_1 is lower from the record from table_2 then reads the next in table_1.
If the record from table_1 is equal to the record from table_2 then does:

     - We create a new buffer, if we need it using the processes of the buffer (init_buffer, new_buffer)
     - We insert the record to the buffer
     - If there is a previous record in table_1, the table_2 is not finished and the next record in table_2 is equal to
		 	the one of we compare at that moment then move the last to next record.
   - We keep the key of the current record from table_1 to use it during the next read.
   - When it’s all done, then add a mark to define the end of the records

The structs, that we used, are the following:

- *unsorted_record*: it contains the key, payload, rowID and an array of 8 chars. 
- *unsorted_tables*: it contains the pointers in to unsorted tables.
- *sorted_record*: it contains the key and the rowID 
- *sorted_tables*: it contains the pointers in to sorted tables
- *histogram*: it contains the value and a pointer to a temporary unsorted record
- *merged record*: it contains the key and the payload of table_1 and the payload of table_2
- *buffer*: it contains a pointer to the next buffer and a table size of the buffer

This project includes a README, a makefile for compile and a file with all the unit tests that we do for the testing.
For the running, we need 2 input files (the 2 unsorted tables):
***./smj -1 input_1 -2 input_2***

***
