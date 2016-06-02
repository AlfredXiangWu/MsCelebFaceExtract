#ifndef STDAFX_H_
#define STDAFX_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory.h> // strlen/memcpy


int create_directory(const char* directory);
int get_dir_from_filename(const char *file_name, char *dir);
int replace_ext_name(char *id, const char *ext);


#endif // STDAFX_H_
