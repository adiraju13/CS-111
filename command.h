#ifndef COMMAND_H
#define COMMAND_H

int getNumArgs(int optind, int argc, char **argv);

char **createArgArr(int numargs, int optind, char **argv);

int checkPidSize(int *numpids, int *pidcap, pid_t *pids);

int command(char *optarg, int optind, int argc, char **argv, int *numpids, int *pidcap, pid_t *pids, int *fileDescriptors, int numFiles);

#endif /* COMMAND_H */
