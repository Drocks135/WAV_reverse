#include "file.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
/**********************************************************************
 * This function opens up a file and writes it to a buffer
 * @param filename the name of the file to open
 * @param buffer the pointer to write the file to
 ********************************************************************/
size_t read_file(char* filename, char **buffer){
	//Open a file pointer to read from
	FILE *fptr;
	fptr = fopen(filename, "r");

	if(fptr == NULL){
		printf("file could not be found");
		return 2;
	}

	//using sys/stat to get the size of the file
	//to allocate the right size char buffer
	size_t size;

	struct stat st;
	stat(filename, &st);
	size = st.st_size;
	
	//Malloc the buffer to the size
	//returned by the system
	*buffer = malloc(size);
	
	//Read in the bytes to the buffer
	//from the opened file
	fread(*buffer, sizeof(char), size, fptr);

	fclose(fptr);

	return size;
}
/**********************************************************************
 * This function writes the data of buffer to an output file
 * @param filename the name of the file to output to
 * @param buffer the buffer to write out to a file
 * @param size the amount of data to write
 *********************************************************************/
size_t write_file(char* filename, char *buffer, size_t size){
	FILE* fptr = fopen(filename, "w");
	fwrite(buffer, sizeof(char), size, fptr);
	fclose(fptr);
	return size;
}
