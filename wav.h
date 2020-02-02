#ifndef WAV_H
#define WAV_H
typedef struct{
char riff[4];
int chunkSize;
char wave[4];
char format[4];
short formatLength;
short formatType;
short numChannels;
int sampleRate;
int byteRate;
short blockAlignment;
short bitsPerSample;
char dataHeader[4];
int sizeOfData;
}wav_file;

wav_file* parse(char* contents);
#endif
