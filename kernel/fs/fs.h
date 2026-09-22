#ifndef FILESYSTEM_H
#define FILESYSTEM_H

enum NodeType
{
    FILE,
    DIRECTORY
};

void create_file(char *name, enum NodeType type, char *content);

void list_files(void);

#endif