#ifndef VBC_C
#define VBC_C

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void unexpected(char c);
int check_string(char *s);
int factor(char **s);
int product(char **s);
int sum(char **s);


#endif