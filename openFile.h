#ifndef OPENFILE_H
#define OPENFILE_H

int openReadOnly(char* fileName, int* numFiles, int* fileCapacity ,int* fileDescriptors);

int openWriteOnly(char* fileName, int* numFiles,int* fileCapacity, int* fileDescriptors);

#endif //OPENFILE_H
