#include <stdint.h>
#include "terminal.h"

volatile uint16_t *video = (volatile uint16_t *)0xB8000;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint8_t cursor_drawn = 0;
uint16_t cursor_old;
uint16_t cursor_old_pos;
uint16_t input_start;



uint16_t get_position(void)
{
    return cursor_y * 80 + cursor_x;
}



void scroll(void)
{
    for (int y = 1; y < 25; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            video[(y - 1) * 80 + x] = video[y * 80 + x];
        }
    }

    for (int x = 0; x < 80; x++)
    {
        video[24 * 80 + x] = 0x0720;
    }
    cursor_y = 24;
}

void putchar(char c) 
{
    hide_cursor();
    if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
        

        if (cursor_y >= 25)
        {
            scroll();
        }

        draw_cursor();
        return;

    }
    video[get_position()] = 0x0700 | c;
    cursor_x++;
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= 25)
    {
        scroll();
    }
    draw_cursor();
}

void clear_screen(void)
{
    for (int i = 0; i < 80 * 25; i++)
    {
        video[i] = 0x0720;
    }

    cursor_x = 0;
    cursor_y = 0;
}
void print(const char *text)
{
    while(*text != '\0')
    {
        putchar(*text);
        text++;
    }
    
}

void draw_cursor(void)
{
    if (cursor_drawn == 0) {
    int pos = get_position();
    cursor_old_pos = pos;
    cursor_old = video[pos];


    video[pos] = 0x7020;
    cursor_drawn = 1;
    }else{

        video[cursor_old_pos] = cursor_old;
        int pos = get_position();
        cursor_old_pos = pos;
        cursor_old = video[pos];
        video[pos] = 0x7020;
    }
}

void hide_cursor(void)
{
    if (cursor_drawn == 1)
    {
        video[cursor_old_pos] = cursor_old;
        cursor_drawn = 0;
    };
    
}

void cursor(void)
{
    
    hide_cursor();
    
    if (get_position() <= input_start) {}
    else{
    if (cursor_x == 0)
    {
        if (cursor_y > 0) {
        cursor_y -= 1;
        cursor_x = 79;
        while(video[get_position()] == 0x0720 && cursor_x > 0)
        {
            cursor_x -=1;
        };
        video[get_position()] = 0x0720;
        }

    }else{
    cursor_x -=1;
    video[get_position()] = 0x0720;
    }}
    draw_cursor();
}