#pragma once
#include <cstdio>

class File
{
  public:
    size_t file_size;
    char *data;

  public:
    File(const char *);
    ~File();
};