#include "file.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

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

size_t write_file(char* filename, char *buffer, size_t size){
	FILE* fptr = fopen(filename, "w");
	fwrite(buffer, sizeof(char), size, fptr);
	fclose(fptr);
	return size;
}
