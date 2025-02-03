#define _GNU_SOURCE
#include <X11/Xlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int (*real_XNextEvent)(Display *, XEvent *) = NULL;

void create_popup(Display *dpy) {
  Window root = DefaultRootWindow(dpy);
  int screen = DefaultScreen(dpy);
  Window win =
      XCreateSimpleWindow(dpy, root, 200, 200, 300, 150, 1,
                          BlackPixel(dpy, screen), WhitePixel(dpy, screen));

  XStoreName(dpy, win, "Injected Popup");
  XMapWindow(dpy, win);

  XFlush(dpy);

  XEvent event;
  while (1) {
    XNextEvent(dpy, &event);
    if (event.type == Expose) {
      GC gc = XCreateGC(dpy, win, 0, NULL);
      XSetForeground(dpy, gc, BlackPixel(dpy, screen));
      XDrawString(dpy, win, gc, 50, 50, "Hello from injected code!", 25);
      XFreeGC(dpy, gc);
    }
    if (event.type == KeyPress || event.type == ButtonPress) {
      break;
    }
  }

  XDestroyWindow(dpy, win);
}

// hooked XNextEvent function
int XNextEvent(Display *display, XEvent *event) {
  if (!real_XNextEvent) {
    real_XNextEvent = dlsym(RTLD_NEXT, "XNextEvent");
  }

  char *str = "Hooked!\n";
  write(1, str, strlen(str));

  int result = real_XNextEvent(display, event);

  if (event->type == MapNotify) {
    create_popup(display);
  }

  return result;
}
