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
  static ssize_t (*real_write)(int, const void *, size_t) =
      NULL; // function ptr so we can store original `write` to call later
  int triggered = 0;
  int exit = 0;
  char *str = "Hooked!\n";
  if (!real_write)
    real_write = dlsym(RTLD_NEXT, "write");

  if (!triggered) {
    triggered = 1;
    real_write(fd, str, strlen(str));
    // fprintf(stderr, "Intercepted write: %zu bytes\n", count);
    printf("Intercepted write\n");
    fprintf(stderr, "fd: %i\n", fd);
    // since buf is a raw pointer, we need to interate through it
    // in order for it to print properly
    fprintf(stderr, "buf: ");
    for (size_t i = 0; i < count; i++) {
      fprintf(stderr, "%02x ", ((unsigned char *)buf)[i]);
    }
    fprintf(stderr, "\n");

    fprintf(stderr, "count: %zu\n", count);

    if (exit)
      _exit(0);
  }

  return real_write(fd, buf, count);
}
