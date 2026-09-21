#include <stdint.h>

uint8_t shift = 0;
uint8_t caps = 0;
uint8_t ctrl = 0;
uint8_t alt = 0;

char scancode_table_min[128] = {

    [0x02] = '1',
    [0x03] = '2',
    [0x04] = '3',
    [0x05] = '4',
    [0x06] = '5',
    [0x07] = '6',
    [0x08] = '7',
    [0x09] = '8',
    [0x0A] = '9',
    [0x0B] = '0',
    [0x0C] = '-',
    [0x0D] = '=',

    [0x10] = 'q',
    [0x11] = 'w',
    [0x12] = 'e',
    [0x13] = 'r',
    [0x14] = 't',
    [0x15] = 'y',
    [0x16] = 'u',
    [0x17] = 'i',
    [0x18] = 'o',
    [0x19] = 'p',

    [0x1E] = 'a',
    [0x1F] = 's',
    [0x20] = 'd',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',

    [0x2C] = 'z',
    [0x2D] = 'x',
    [0x2E] = 'c',
    [0x2F] = 'v',
    [0x30] = 'b',
    [0x31] = 'n',
    [0x32] = 'm',

    [0x1A] = '[',
    [0x1B] = ']',

    [0x27] = ';',
    [0x28] = '\'',
    [0x29] = '`',

    [0x2B] = '\\',

    [0x33] = ',',
    [0x34] = '.',
    [0x35] = '/',

    [0x1C] = '\n',
    [0x39] = ' ',
};

char scancode_table[128] = {

    [0x02] = '!',
    [0x03] = '@',
    [0x04] = '#',
    [0x05] = '$',
    [0x06] = '%',
    [0x07] = '^',
    [0x08] = '&',
    [0x09] = '*',
    [0x0A] = '(',
    [0x0B] = ')',
    [0x0C] = '_',
    [0x0D] = '+',

    [0x10] = 'Q',
    [0x11] = 'W',
    [0x12] = 'E',
    [0x13] = 'R',
    [0x14] = 'T',
    [0x15] = 'Y',
    [0x16] = 'U',
    [0x17] = 'I',
    [0x18] = 'O',
    [0x19] = 'P',

    [0x1E] = 'A',
    [0x1F] = 'S',
    [0x20] = 'D',
    [0x21] = 'F',
    [0x22] = 'G',
    [0x23] = 'H',
    [0x24] = 'J',
    [0x25] = 'K',
    [0x26] = 'L',

    [0x2C] = 'Z',
    [0x2D] = 'X',
    [0x2E] = 'C',
    [0x2F] = 'V',
    [0x30] = 'B',
    [0x31] = 'N',
    [0x32] = 'M',

    [0x1A] = '{',
    [0x1B] = '}',

    [0x27] = ':',
    [0x28] = '"',
    [0x29] = '~',

    [0x2B] = '|',

    [0x33] = '<',
    [0x34] = '>',
    [0x35] = '?',

    [0x1C] = '\n',
    [0x39] = ' ',
};

uint8_t read_kinput(void)
{
    uint8_t kinput_result;
    __asm__ volatile (
    "inb $0x60, %%al"
    : "=a" (kinput_result)
    );
    return kinput_result;
}

uint8_t has_kinput(void)
{
    uint8_t has_kinput_result;
    __asm__ volatile (
    "inb $0x64, %%al"
    : "=a" (has_kinput_result)
    );
    

    return has_kinput_result & 1;
}


char kgetchar(void){

    

    if (has_kinput()) {
    uint8_t key = read_kinput();

    
    
    if (key == 0x1D)
    {
    ctrl = 1;
    }
    else if (key == 0x9D)
    {
    ctrl = 0;
    }
    if (key == 0x3A)
    {
    caps = !caps;
    };
    if (key == 0x2A)
    {
    shift = 1;
    }
    else if (key == 0xAA)
    {
    shift = 0;
    }
    if (key & 0x80)
    {
    return 0;
    }
    

    if (key == 0x0E) 
    {
    return '\b';
    }
    char normal = scancode_table_min[key];
        
        if (normal >= 'a' && normal <= 'z')
        {
            if (ctrl)
                {
                    return normal - 'a' + 1;
                };
            if (shift ^ caps)
            {
            
                if (key != 0) {
                return scancode_table[key];
                }
           
            }else{
                if (key != 0x0E) {
                return scancode_table_min[key];
                }
            }
            }else{
                if (shift)
                {
                    return scancode_table[key];
                }else{
                    return scancode_table_min[key];
                }
            }}
            return 0;  
          }    
          
    

