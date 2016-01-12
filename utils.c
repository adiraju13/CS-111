#include <stdlib.h>
#include <stdio.h>

// checks if option is long (starts with --)
int isLong(char *str) {
  int i = 0;
  while(str[i] != '\0' && i < 2) {
    if(str[i] != '-')
      return 0;
    i++;
  }
  if(i != 2) return 0;
  return 1;
}

// wrapper function for malloc that checks for errors
void *Malloc(size_t size) {
  void * result = malloc(size);
  if(result == NULL) {
    perror("simpsh");
    exit(1);
  }
  return result;
}

// wrapper function for realloc that checks for errors
void *Realloc(void *ptr, size_t size) {
  void * result = realloc(ptr, size);
  if(result == NULL) {
    perror("simpsh");
    exit(1);
  }
  return result;
}

// check if array has reached is size limit
int checkSize(int *num, int *cap, int *arr) {
  if((*num) == (*cap)) {
    (*cap) *= 2;
    arr = (int *)Realloc(arr, (*cap) * sizeof(int));
  }
  return 0;
}

// prints out the current option and its arguments
void printVerbose(int optind, char** argv, int argc)
{
  int index = optind - 2;
  printf("%s", argv[index]);
  index++;
  while (index < argc && !isLong(argv[index])){
    printf(" %s", argv[index]);
    index++;
  }
  printf("\n");
  fflush(stdout);
}

// counts the number of arguments that the current option has
int numArgs(int optind, char** argv, int argc)
{
  int count = 0;
  int index = optind -1;
  while (index < argc && !isLong(argv[index])){
    count++;
    index++;
  }

  return count;
  
}

// checks if a character represents a digit
int isDigit(char c) {
  return (c >= '0' && c <= '9');
}

// checks if a string represents a number
int isNumber(char *str) {
  while((*str) != '\0') {
    if(!isDigit(*str))
      return 0;
    str++;
  }
  return 1;
}
