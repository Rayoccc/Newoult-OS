#ifndef TERMINAL_H
#define TERMINAL_H

// Insere apenas UM caractere
void putchar(char c);
// Imprime string no terminal
void print(const char *text);
// Limpa a tela
void clear_screen(void);
// Apaga o caractere anterior e move o cursor para trás
void cursor(void);
// Desenha o cursor
void draw_cursor(void);
// Esconde o cursor 
void hide_cursor(void);

extern uint16_t input_start;
uint16_t get_position(void);

#endif
