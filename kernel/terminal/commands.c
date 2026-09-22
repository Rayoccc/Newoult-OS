#include <stdint.h>
#include "terminal.h"
#include "../drivers/keyboard.h"

char commands[30] = {
  [29] = '\0'
};

uint8_t command_pos = 0;
uint8_t compare(const char *command, const char *input);



void hello(void);
void help(void);
void clear(void);
void version(void);

struct Command
{
  const char *name;
  void (*func)(void);
};

struct Command command_table[] = {
  {"hello", hello},
  {"help", help},
  {"clear", clear},
  {"version", version}
};

uint8_t size = sizeof(command_table) / sizeof(command_table[0]);

void command(void)
{
  
  char key = kgetchar();
if (key == 0 )
  {
    
  }else{
  if (key == '\n') {
      putchar('\n');

    if (command_pos > 0) {
      uint8_t i = 0;
      uint8_t result = compare(commands, command_table[i].name);
      
      
      while (result == 0 && i < size) {
        
        i++;
        result = compare(commands, command_table[i].name);
        
      }
    
      if (result == 1)
      {
        command_table[i].func();
      } 
      else
      {
      print("Unknown Command, type `HELP` to see all commands\n");
      }
      
    }
      command_pos = 0;
      commands[0] = '\0';
      input_start = get_position();
      print("[sysroot]: ");

    }else{

    if (key == '\b') {
      cursor();
      if (command_pos > 0) {
      commands[command_pos -1] = '\0';
      command_pos -=1;}
      
    }else{
      if (key == 12)
      {
        clear_screen();
        print("[sysroot]: ");
      }else{
    putchar(key);
    if (command_pos == 29) {

    }else
    {
    commands[command_pos] = key;
    command_pos +=1;
    commands[command_pos] = '\0';
    }}
  };
  
  }
  }
}

uint8_t compare(const char *command, const char *input)
{
  uint8_t i = 0;
  while (input[i] != '\0' && command[i] != '\0'){

      if (command[i] != input[i])
      {
        
        return 0;
      }
      
      i++;
    }
    if (command[i] == '\0' && input[i] == '\0')
    {
    return 1;
    }

    return 0;

}

void hello(void)
{
  
  print("Hello, World!");
      putchar('\n');
}

void help(void)
{
  putchar('\n');
  putchar('\n');
  print("Newoult OS Shell");
        putchar('\n');
        print("These commands are defined internally, type `HELP` to see this list.");
        putchar('\n');
        print("If you don't know what you're doing, its highly recommended that you don't try to run any commands in `DEBUG`, `CRITICAL` and `KERNEL` section.");
        putchar('\n');
        putchar('\n');
        print("TERMINAL");
        putchar('\n');
        print("CLEAR: Cleans the shell.");
        putchar('\n');
        putchar('\n');
        print("OUTPUT");
        putchar('\n');
        print("HELLO: Hello, World!");
        putchar('\n');
        print("HELP: You're looking at it right now!");
        putchar('\n');
        print("VERSION: Displays useful information about the version ");
        putchar('\n');
        putchar('\n');
}

void clear(void)
{
  clear_screen();

}

void version(void)
{
  print("Newoult OS v0.0.0-pre-alpha-0002");
  putchar('\n');
  print("Drivers version:");
  putchar('\n');
  print("Metal 0.0.0-pre-alpha-0003");
}