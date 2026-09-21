#include <stdint.h>
#include "terminal/terminal.h"
#include "drivers/keyboard.h"
#include "terminal/commands.h"

__attribute__((section(".multiboot")))
const uint32_t multiboot_header[] =
{
    0x1BADB002,
    0,
    -(0x1BADB002)
};

void kernel_main(void)
{
    clear_screen();

    print("Newoult OS \n");
    print("Initializing Kernel...\n");
    print("Welcome, user.");
    putchar('\n');
    print("[sysroot]: ");
    input_start = get_position();
   

    while (1)
{
    command();
    
}
}

