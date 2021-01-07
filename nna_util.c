/**
Copyright 20201 Andrei N. Ciobanu

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <stdio.h>
#include <stdarg.h>
#include "nna_util.h"

#define BUFFER_SIZE 4096

void nna_log(
  FILE* stream,
  const char* file_name,
  unsigned int line,
  const char* format,
  ...
) {
#if DEBUG_TRUE
  va_list argp;
  va_start(argp, format);
  nna_vlog(stream, file_name, line, format, argp);
  va_end(argp);
#endif
}

void nna_vlog(
  FILE* stream,
  const char *file_name,
  unsigned int line,
  const char *format,
  va_list argp
){
#if DEBUG_TRUE
  char buffer[BUFFER_SIZE];
  char* level;
  int stop;

  if (stderr == stream) {
      level = "ERROR";
  } else if (stdout == stream) {
      level = "INFO";
  }

  // Formating string and
  // Check if the the string has been completly written and
  // no buffer overflow occured
  stop = vsnprintf(buffer, BUFFER_SIZE, format, argp);
  if (stop < BUFFER_SIZE && stop > 0) {
    fprintf(stream, "[%s:%d] [%s] %s\n", file_name, line, level, buffer);
  }
#endif
}