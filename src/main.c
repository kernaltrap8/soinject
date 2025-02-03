// Copyright (c) 2025 kernaltrap8
// Licensed under BSD-3
// src/main.c
// @description Example code for usage of `libso.so` `write()` call
// replacement shared object.

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char *str = "hi you shouldn't be seeing this\n";
  write(1, str, strlen(str));
  return 0;
}
