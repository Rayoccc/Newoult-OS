#include <stdint.h>
#include "fs.h"
#include "../terminal/terminal.h"

struct Node
{
    char name[32];
    uint8_t type;
    uint32_t size;
    char data[512];
};

void copy_string(char *destiny, const char *origin)
{
    uint8_t i = 0;

    while (origin[i] != '\0')
    {
        destiny[i] = origin[i];
        i++;

    }
    destiny[i] = '\0';
}

struct Node arquivo[10];
// struct Node arquivo;

void test(void)
{
    


}

void create_file(char *name, enum NodeType type, char *content)
{
uint8_t i = 0;
uint8_t o = 0;
uint8_t a = 0;

while(name[a] != '\0')
{
    a++;
};

if (a > 31)
{
    print("Impossible to write file: The file's name is too big. Please choose a name between 1 and 30 characters.");
    putchar('\n');
    return;
}

while(content[o] != '\0')
{
    o++;
};

if (o > 511)
{
print("Impossible to write file: The file is too big. Only 512B supported.");
putchar('\n');
return;
}


while(i < 10) 
{

if (arquivo[i].name[0] == '\0')
{
    
copy_string(arquivo[i].name, name);


arquivo[i].type = type;
arquivo[i].size = o;
copy_string(arquivo[i].data, content);
break;
}



i++;
}


if (i == 10)
{
    print("Impossible to write file: You ran out of storage.");
    putchar('\n');
    return;
}
}

void list_files(void)
{
    uint8_t i = 0;

    while(i < 10)
    {
        if (arquivo[i].name[0] != '\0')
        {
            if (arquivo[i].type == FILE)
            {
            print(arquivo[i].name);
            putchar('\n');
            }
            if (arquivo[i].type == DIRECTORY)
            {
            print(arquivo[i].name);
            print("/");
            putchar('\n');
            }
        }
        i++;
    }
}
