#include "file_io.h"

File::File(const char *name)
{
    FILE* file;
    file = fopen(name, "r");
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    data = new char[file_size];
    fread(data, sizeof(char), file_size, file);
    fclose(file);
}

File::~File()
{
    delete data;
}