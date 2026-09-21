#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

uint8_t read_kinput(void);
uint8_t has_kinput(void);
char kgetchar(void);

#endif
