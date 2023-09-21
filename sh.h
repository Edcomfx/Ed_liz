#ifndef SHELL_H
#define SHELL_H

/* 
 * The following below are my standard library
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * The following below are my functions prototypes
 */
void customized_prompt(void);
void eby_print(const char *errand);
void user_input(char *command, size_t size);
void execute_command(const char *command);
void implement_command(const char *command);

#endif
