#include <stdint.h>

// US QWERTY scancode set 1
static const char scancode_set1[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=',8,9,
    'q','w','e','r','t','y','u','i','o','p','[',']','\\',0,0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\',
    'z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0,
};

static inline uint8_t inb(uint16_t port) {
    uint8_t val;
    __asm__ volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

// Reads a line from keyboard into buf, returns length
int keyboard_read(char* buf, int maxlen) {
    int i = 0;
    while (i < maxlen) {
        uint8_t sc = 0;
        // Wait for a key press
        do { sc = inb(0x60); } while (sc == 0);
        if (sc & 0x80) continue; // Ignore key releases
        char c = scancode_set1[sc];
        if (c == 0) continue;
        if (c == 8) { // Backspace
            if (i > 0) i--;
        } else if (c == 13 || c == '\n') { // Enter
            break;
        } else {
            buf[i++] = c;
        }
    }
    buf[i] = 0;
    return i;
}
