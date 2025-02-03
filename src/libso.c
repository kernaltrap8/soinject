// Copyright (c) 2025 kernaltrap8
// Licensed under BSD-3
// src/libso.c
// @description This code is for a shared object that will
// replace the `write()` call when preloaded/linked with another program.
// A example usage program is available in `src/main.c`

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count) {
  static ssize_t (*real_write)(int, const void *, size_t) = NULL;
  int triggered = 0;
  char *str = "Hooked!\n";
  if (!real_write)
    real_write = dlsym(RTLD_NEXT, "write");

  if (!triggered) {
    triggered = 1;
    real_write(fd, str, strlen(str));
    _exit(0);
  }

  return real_write(fd, buf, count);
}
