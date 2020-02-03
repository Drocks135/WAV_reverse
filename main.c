//Collaborated with Aiden Marten

#include <stdio.h>
#include <string.h>
#include "file.h"
#include "wav.h"

int main(int argc, char** argv){
	char* buffer;

	int fileSize;
	fileSize = read_file(argv[1], &buffer);
	
	wav_file* song;
	song = parse(buffer);
	
	char exp[4] = "RIFF";
	for(int i = 0; i < 4; i++){
		if(song -> riff[i] != exp[i]){
			printf("This file isn't a wave file");
			return 1;
			}
	}	


	printf("File: %s\n", argv[1]);
	printf("===============\n");
	printf("- File size is %i. Read %i bytes.\n", fileSize, song -> sizeOfData);
	printf("- Format is %s with format data length %i\n", 
			song -> format, song -> formatLength);
	printf("- Format is %s format\n", song -> wave);
	printf("- %i channel(s) with a sample rate of %i\n", 
			song -> numChannels, song -> sampleRate);
	printf("- %i byte rate, %i block alignment, %i bits per sample\n",
			song -> byteRate, song -> blockAlignment, song -> bitsPerSample);
	printf("- %s is data and data size is %i\n", 
			song -> dataHeader, song -> sizeOfData);


	//This area is the actual reversing of the data
	int dataStart = 44;
	int chunkSize = song -> numChannels * song -> bitsPerSample;
	int dataEnd = 44 + song -> sizeOfData - chunkSize;
	char tempChunk[chunkSize];
	while(dataStart != dataEnd){
		memcpy(&tempChunk, &buffer[dataStart], chunkSize);
		memcpy(&buffer[dataStart], &buffer[dataEnd], chunkSize);
		memcpy(&buffer[dataEnd], &tempChunk, chunkSize);
		dataStart += chunkSize;
		dataEnd -= chunkSize;
		if(dataStart > dataEnd)
			dataStart = dataEnd;
	}

	write_file(argv[2], buffer, fileSize);
	
	free(buffer);
	return 0;
}
