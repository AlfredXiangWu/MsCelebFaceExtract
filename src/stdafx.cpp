#include "stdafx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define _MAX_PATH 1024
#define ACCESS access
#define MKDIR(a) mkdir((a),0755)

using namespace std;

int create_directory(const char *directory)
{
  int i;
  int len;
  char dir[_MAX_PATH], temp_dir[_MAX_PATH];

  memcpy(temp_dir, directory, _MAX_PATH);

  len = (int)strlen(temp_dir);
  for(i=0; i<len; i++)
  {
    if(temp_dir[i] == '\\')
      temp_dir[i] = '/';
  }
  if(temp_dir[len-1] != '/')
  {
    temp_dir[len] = '/';
    temp_dir[len+1] = 0;
    len++;
  }
  memset(dir, 0, _MAX_PATH);
  for(i=0; i<len; i++)
  {
    dir[i] = temp_dir[i];
    if(temp_dir[i] == '/')
    {
      if(i > 0)
      {
        if(temp_dir[i-1] == ':')
          continue;
        else
        {
          if(ACCESS(dir, NULL) == 0)
            continue;
          else /* create it */
          {
            if(MKDIR(dir) != 0)
              return -1;
          }
        }
      }
    }
  }

  return 0;
}

int get_dir_from_filename(const char *file_name, char *dir)
{
  int len;
  int i;

  len = (int) strlen(file_name);
  for(i=len-1; i>=0; i--)
  {
    if(file_name[i] == '\\' || file_name[i] == '/')
    {
      break;
    }
  }

  strcpy(dir, file_name);
  dir[i+1] = 0;

  return 0;
}

int replace_ext_name(char *id, const char *ext)
{
  int i, len, idx;
  bool found = false;

  len = (int) strlen(id);
  for(i=len-1; i>=0; i--)
  {
    if(id[i] == '.')
    {
      found = true;
      break;
    }
  }

  if(!found)
    return -1;

  idx = i + 1;
  len = (int) strlen(ext);
  for(i=0; i<len; i++)
  {
    id[idx+i] = ext[i];
  }
  id[idx+len] = 0;

  return 0;
}
