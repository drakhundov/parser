#include "parser.h"

#include <ctype.h>
#include <stdlib.h>

int _stoi(char *s) {
  int i = 0;
  while (isspace(s[i])) i++;
  int sign = 1;
  if (s[i] == '-' || s[i] == '+') {
    sign = (s[i] == '-') ? -1 : 1;
    i++;
  }
  int a = 0;
  while (1) {
    if (s[i] == '\0') {
      break;
    }
    if (isdigit(s[i])) {
      a = (a * 10) + (s[i] - '0');
    } else {
      break;
    }
    i++;
  }
  return a * sign;
}

void _fscanf(FILE *f, char *s, ...) {
  if (f == NULL) {
    fprintf(stderr, "FILE hasn't been initialized.");
    exit(1);
  }
  va_list args;
  va_start(args, s);
  char c;
  while (*s) {
    if (feof(f)) {
      fprintf(stderr, "String too long.\n");
      exit(1);
    }
    if (*s == '%') {
      switch (*++s) {
        case 'd': {
          printf("Parsing a number.\n");
          int *ptr = va_arg(args, int *);
          *ptr = 0;
          char c;
          int sign = 1;
          if ((c = fgetc(f)) == '-' || c == '+') {
            sign = (c == '-') ? -1 : 1;
          } else {
            ungetc(c, f);
          }
          while (isdigit(c = fgetc(f))) {
            *ptr = (*ptr * 10) + (c - '0');
          }
          ungetc(c, f);
          *ptr *= sign;
          s++;  // Skip 'd'.
          break;
        }
        default:
          fprintf(stderr, "Unsupported format specifier: %%%c\n", c);
          va_end(args);
          exit(1);
      }
    } else {
      c = fgetc(f);
      printf("c: %c, s: %c\n", c, *s);
      if (c != *s) {
        fprintf(stderr, "Unable to parse: the strings don't match. c: '%c' s: '%s'", c, s);
        va_end(args);
        exit(1);
      }
      s++;
    }
  }
  va_end(args);
}