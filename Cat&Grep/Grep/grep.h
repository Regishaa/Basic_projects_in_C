#ifndef GREP_H
#define GREP_H
#define BUFFER 10000
#define MAX_REGEX_LENGTH 1000
typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int c_flag;
  char str[BUFFER];
  char str_o[BUFFER];
  char str_buf[BUFFER];
  char filename[BUFFER];
} option_type;

#endif