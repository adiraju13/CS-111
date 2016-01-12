#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "openFile.h"
#include "utils.h"
#include "command.h"

#define RDONLY 0
#define WRONLY 1
#define COMMAND 2
#define VERBOSE 3


int main(int argc, char **argv) {
  opterr = 0;
  int* fileDescriptors;
  int fileCapacity = 2;
  int numFiles = 0;
  struct option long_opts[] = {
    {"rdonly",  required_argument, 0, RDONLY },
    {"wronly",  required_argument, 0, WRONLY },
    {"command", required_argument, 0, COMMAND},
    {"verbose", no_argument,       0, VERBOSE},
    {0,         0,                 0, 0      }
  };

  // subproccess management
  int numpids = 0;
  int pidcap = 2;
  pid_t *pids = (pid_t *)Malloc(pidcap*sizeof(pid_t));

  // array to hold file descriptors
  fileDescriptors = (int*)Malloc(fileCapacity*sizeof(int));
  int verbose = 0;

  // loop until there are no more options
  while(1) {
    int option_index;
    int ret = getopt_long(argc, argv, "", long_opts, &option_index);
    
    if(ret == -1) {
      break;
    }

    switch(ret) {
    case RDONLY:
      if (verbose == 1)
	printVerbose(optind, argv, argc);
      if(numArgs(optind, argv, argc) > 1)
	fprintf(stderr, "The number of arguments to --rdonly  was more than one, the first was taken as input\n");
      if(optarg && !isLong(optarg)){
	int fileDescriptor = openReadOnly(optarg, &numFiles, &fileCapacity , fileDescriptors);
	if(fileDescriptor < 0){
	  fprintf(stderr, "The file %s passed to --rdonly does not exist\n", optarg);
	}
      }
      else if(isLong(optarg)){
	optind--;
	fprintf(stderr, "ERROR: There were no arguments passed to --rdonly\n");
      }
      break;
      
    case WRONLY:
      if (verbose == 1)
	printVerbose(optind, argv, argc);
      if(numArgs(optind, argv, argc)>1)
	fprintf(stderr, "The number of arguments passed to --wronly was more than one, the first file was taken as input\n");
      if(optarg && !isLong(optarg)){
	int fileDescriptor = openWriteOnly(optarg, &numFiles , &fileCapacity ,fileDescriptors);
	if (fileDescriptor < 0){
	  fprintf(stderr, "The file %s passed to --wronly does not exist\n", optarg);
	}
      }
      else if(isLong(optarg)){
	optind--;  
	fprintf(stderr, "ERROR: There were no arguments passed to --wronly\n");
	}
      break;

    case COMMAND:
      if (verbose == 1)
	printVerbose(optind, argv, argc);
      if(optarg && !isLong(optarg))
	command(optarg, optind, argc, argv, &numpids, &pidcap, pids, fileDescriptors, numFiles);
      else if(isLong(optarg)){
	optind--;
	fprintf(stderr, "ERROR: There were no arguments passed to --command\n");
      }
      break;

    case VERBOSE:
      verbose = 1;
      break;

    case '?':
      if (verbose == 1)
	printVerbose(optind + 1, argv, argc);
      if(isLong(argv[optind-1]))
	 fprintf(stderr, "Syntax error %s\n", argv[optind-1]);
      break;

    default:
      printf("getopt_long returned %d\n", ret);
    }
  }

  int looper;
  for (looper = 0; looper < numFiles; looper++){
    close(fileDescriptors[looper]);
  }
}
