#ifndef _KEYBOARD_
#define _KEYBOARD_

#include "types.h"
#include "system.h"

char keyboard_to_char(void){
    char rv = '\x0';
    if(inportb(0x64) & 0x1){
        switch(inportb(0x60)){
            case 1:{ rv = (char)27; break; } //esc
            case 2:{ rv = '1'; break; }
            case 3:{ rv = '2'; break; }
            case 4:{ rv = '3'; break; }
            case 5:{ rv = '4'; break; }
            case 6:{ rv = '5'; break; }
            case 7:{ rv = '6'; break; }
            case 8:{ rv = '7'; break; }
            case 9:{ rv = '8'; break; }
            case 10:{ rv = '9'; break; }
            case 11:{ rv = '0'; break; }

            case 12:{ rv = '-'; break; }
            case 13:{ rv = '='; break; }
            case 14:{ rv = '\b'; break; } //backspace
            case 15:{ rv = '\t'; break; } //tab

            case 16:{ rv = 'q'; break; }
            case 17:{ rv = 'w'; break; }
            case 18:{ rv = 'e'; break; }
            case 19:{ rv = 'r'; break; }
            case 20:{ rv = 't'; break; }
            case 21:{ rv = 'y'; break; }
            case 22:{ rv = 'u'; break; }
            case 23:{ rv = 'i'; break; }
            case 24:{ rv = 'o'; break; }
            case 25:{ rv = 'p'; break; }

            case 26:{ rv = '['; break; }
            case 27:{ rv = ']'; break; }
            case 28:{ rv = '\n'; break; } //newline
            //case 29:{ rv = ''; break; } //left ctrl

            case 30:{ rv = 'a'; break; }
            case 31:{ rv = 's'; break; }
            case 32:{ rv = 'd'; break; }
            case 33:{ rv = 'f'; break; }
            case 34:{ rv = 'g'; break; }
            case 35:{ rv = 'h'; break; }
            case 36:{ rv = 'j'; break; }
            case 37:{ rv = 'k'; break; }
            case 38:{ rv = 'l'; break; }

            case 39:{ rv = ';'; break; }
            case 40:{ rv = (char)39/*'*/; break; } //single quote (')
            case 41:{ rv = (char)39/*'*/; break; } //back tick (`)
            //case 42:{ rv = ''; break; } //left shift
            case 43:{ rv = '\\'; break; }

            case 44:{ rv = 'z'; break; }
            case 45:{ rv = 'x'; break; }
            case 46:{ rv = 'c'; break; }
            case 47:{ rv = 'v'; break; }
            case 48:{ rv = 'b'; break; }
            case 49:{ rv = 'n'; break; }
            case 50:{ rv = 'm'; break; }
            case 51:{ rv = ','; break; }
            case 52:{ rv = '.'; break; }
            case 53:{ rv = '/'; break; }
            case 54:{ rv = '.'; break; }
            case 55:{ rv = '/'; break; }
            //case 56:{ rv = ''; break; } //right shift
            case 57:{ rv = ' '; break; }
        }
    }
    return rv;
}

void keyboard_to_string(char* kbStr){
    kbStr[0] = keyboard_to_char();
    kbStr[1] = '\x0';
    return;
}

#endif