#include "openFile.h"
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

int openReadOnly(char* fileName,int* numFiles, int* fileCapacity ,int* fileDescriptors)
{
  int descriptor = open(fileName, O_RDONLY);
  checkSize(numFiles, fileCapacity, fileDescriptors);
  fileDescriptors[*numFiles] = descriptor;
  (*numFiles)++;
  return descriptor;
}

int openWriteOnly(char* fileName, int* numFiles, int* fileCapacity, int* fileDescriptors)
{
  int descriptor = open(fileName, O_WRONLY);
  checkSize(numFiles, fileCapacity, fileDescriptors);
  fileDescriptors[*numFiles] = descriptor;
  (*numFiles)++;
  return descriptor;
}
