#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

int getNumArgs(int optind, int argc, char **argv) {
  int num = 0;
  while((optind+3+num) < argc && !isLong(argv[optind+3+num])) num++;
  num += 2;
  return num;
}

char **createArgArr(int numargs, int optind, char **argv) {
  char **cmdargs = (char **)Malloc((numargs) * sizeof(char *));
  cmdargs[0] = argv[optind+2];
  int i = 1;
  while(i < numargs-1) {
    cmdargs[i] = argv[optind+2+i];
    i++;
  }
  cmdargs[i] = NULL;
  return cmdargs;
}

int checkPidSize(int *numpids, int *pidcap, pid_t *pids) {
  if(*numpids == *pidcap) {
    (*pidcap) *= 2;
    pids = (pid_t *)Realloc(pids, (*pidcap)*sizeof(pid_t));
  }
  return 0;
}

int command(char *optarg, int optind, int argc, char **argv, int *numpids, int *pidcap, pid_t *pids, int *fileDescriptors, int numFiles) {
  //printf("option command");
  //printf("The number of file descriptors is: %d\n", numFiles);
  if(optarg) {
    // error check: make sure optind stays less than argc

    // count the number of arguments to the command
    int numargs = getNumArgs(optind, argc, argv);
    
    // create an array of those arguments
    char **cmdargs = createArgArr(numargs, optind, argv);

    // store the file descriptor indeces
    int sinIndex;
    int soutIndex;
    int serrIndex;

    if(isNumber(optarg)) {
      sinIndex = atoi(optarg);
    } else {
      fprintf(stderr, "Incorrect syntax for --command option\n");
      return 0;
    }

    if(isNumber(argv[optind])) {
      soutIndex = atoi(argv[optind]);
    } else {
      fprintf(stderr, "Incorrect syntax for --command option\n");
      return 0;
    }

    if(isNumber(argv[optind+1])) {
      serrIndex = atoi(argv[optind+1]);
    } else {
      fprintf(stderr, "Incorrect syntax for --command option\n");
      return 0;
    }
        

    // fork process and pass cmdargs to it
    checkPidSize(numpids, pidcap, pids);
    int p = fork();
    if(p == 0) { // child process
      if(sinIndex >= numFiles) {
	fprintf(stderr, "No file descriptor corresponding to file number %d\n", sinIndex);
	return 0;
      } else if(soutIndex >= numFiles) {
	fprintf(stderr, "No file descriptor corresponding to file number %d\n", soutIndex);
	return 0;
      } else if(serrIndex >= numFiles) {
	fprintf(stderr, "No file descriptor corresponding to file number %d\n", serrIndex);
	return 0;
      }
      dup2(fileDescriptors[sinIndex], STDIN_FILENO);
      dup2(fileDescriptors[soutIndex], STDOUT_FILENO);
      dup2(fileDescriptors[serrIndex], STDERR_FILENO);
      int val = execvp(argv[optind+2], cmdargs);
      if(val < 0) {
	fprintf(stderr, "Error executing command %s\n", argv[optind+2]);
	return 0;
      }
	
      //printf("I am the child");
    } else if (p > 0) { // parent process
      pids[*numpids] = p;
      (*numpids)++;
      //printf("I am the parent");
    } else { // error
      fprintf(stderr, "Error creating child process\n");
    }

    // testing
    //printf(", stdin: %s, stdout: %s, stderr: %s, executable: %s\n", optarg, argv[optind], argv[optind+1], argv[optind+2]);
    //printf("Arguments to %s: ", argv[optind+2]);
    /*
    int i = 1;

    while(i < numargs-1) {
      printf("%s ", cmdargs[i]);
      i++;
    }
    */
  }
  //printf("\n");
  //printf("Is next arg after %s a long option? %d\n", argv[optind+2], is_long(argv[optind+3]));

  return 0;
}
