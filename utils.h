#ifndef UTILS_H
#define UTILS_H

int isLong(char *str);

// wrapper function for malloc that checks for errors
void *Malloc(size_t size);

// wrapper function for realloc that checks for errors
void *Realloc(void *ptr, size_t size);

int checkSize(int *num, int *cap, int *arr);

void printVerbose(int optind, char** argv, int argc);

int numArgs(int optind, char** argv, int argc);

int isDigit(char c);

int isNumber(char *str);

#endif /* UTILS_H */
