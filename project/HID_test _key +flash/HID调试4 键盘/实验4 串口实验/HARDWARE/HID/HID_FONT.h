//键盘,report_usage的部分字节对应的ASCII字符，

#ifndef __HIDFONT_H
#define __HIDFONT_H

#include "string.h"
struct options { 
    const char    *opt;
    unsigned char val; 
};
static struct options kmod[] = { 
    {.opt = "--left-ctrl",        .val = 0x01},
    {.opt = "--right-ctrl",        .val = 0x10},
    {.opt = "--left-shift",        .val = 0x02},
    {.opt = "--right-shift",    .val = 0x20},
    {.opt = "--left-alt",        .val = 0x04},
    {.opt = "--right-alt",        .val = 0x40},
    {.opt = "--left-meta",        .val = 0x08},
    {.opt = "--right-meta",        .val = 0x80},
    {.opt = NULL} 
};
static struct options kval[] = { 
    {.opt = "--return",    .val = 0x28},
    {.opt = "--esc",    .val = 0x29},
    {.opt = "--bckspc",    .val = 0x2a},
    {.opt = "--tab",    .val = 0x2b},
    {.opt = "--spacebar",    .val = 0x2c},
    {.opt = "--caps-lock",    .val = 0x39},
    {.opt = "--f1",        .val = 0x3a},
    {.opt = "--f2",        .val = 0x3b},
    {.opt = "--f3",        .val = 0x3c},
    {.opt = "--f4",        .val = 0x3d},
    {.opt = "--f5",        .val = 0x3e},
    {.opt = "--f6",        .val = 0x3f},
    {.opt = "--f7",        .val = 0x40},
    {.opt = "--f8",        .val = 0x41},
    {.opt = "--f9",        .val = 0x42},
    {.opt = "--f10",    .val = 0x43},
    {.opt = "--f11",    .val = 0x44},
    {.opt = "--f12",    .val = 0x45},
    {.opt = "--insert",    .val = 0x49},
    {.opt = "--home",    .val = 0x4a},
    {.opt = "--pageup",    .val = 0x4b},
    {.opt = "--del",    .val = 0x4c},
    {.opt = "--end",    .val = 0x4d},
    {.opt = "--pagedown",    .val = 0x4e},
    {.opt = "--right",    .val = 0x4f},
    {.opt = "--left",    .val = 0x50},
    {.opt = "--down",    .val = 0x51},
    {.opt = "--kp-enter",    .val = 0x58},
    {.opt = "--up",        .val = 0x52},
    {.opt = "--num-lock",    .val = 0x53},
    {.opt = NULL} 
};

struct KBD_USAGE_2_CHAR{
    unsigned char usageCode;
    unsigned char lowerCase;
    unsigned char upperCase;
};
static struct KBD_USAGE_2_CHAR kbdUsage2Char[] = {
        {0x04,'a','A'}, // a A
        {0x05,'b','B'}, // b B
        {0x06,'c','C'}, // c C
        {0x07,'d','D'}, // d D
        {0x08,'e','E'}, // e E
        {0x09,'f','F'}, // f F
        {0x0A,'g','G'}, // g G
        {0x0B,'h','H'}, // h H
        {0x0C,'i','I'}, // i I
        {0x0D,'j','J'}, // j J
        {0x0E,'k','K'}, // k K
        {0x0F,'l','L'}, // l L
        {0x10,'m','M'}, // m M
        {0x11,'n','N'}, // n N
        {0x12,'o','O'}, // o O
        {0x13,'p','P'}, // p P
        {0x14,'q','Q'}, // q Q
        {0x15,'r','R'}, // r R
        {0x16,'s','S'}, // s S
        {0x17,'t','T'}, // t T
        {0x18,'u','U'}, // u U
        {0x19,'v','V'}, // v V
        {0x1A,'w','W'}, // w W
        {0x1B,'x','X'}, // x X
        {0x1C,'y','Y'}, // y Y
        {0x1D,'z','Z'}, // z Z
        {0x1E,'1','!'}, // 1 !
        {0x1F,'2','@'}, // 2 @
        {0x20,'3','#'}, // 3 #
        {0x21,'4','$'}, // 4 $
        {0x22,'5','%'}, // 5 %
        {0x23,'6','^'}, // 6 ^
        {0x24,'7','&'}, // 7 &
        {0x25,'8','*'}, // 8 *
        {0x26,'9','('}, // 9 (
        {0x27,'0',')'}, // 0 )
        {0x28,0x0A,0x0A}, // Enter
        {0x2A,0x08,0x08}, // Backspace
        {0x2B,'\t','\t'}, // Tab
        {0x2C,' ',' '}, // Space
        {0x2D,'-','_'}, // - _
        {0x2E,'=','+'}, // = +
        {0x2F,'[','{'}, // [ {
        {0x30,']','}'}, // ] }
        {0x31,'\\','|'}, // \ |
        {0x33,';',':'}, // ; :
        {0x34,'\'','\"'}, // ' "
        {0x35,'`','~'}, // ` ~
        {0x36,',','<'}, // , <
        {0x37,'.','>'}, // . >
        {0x38,'/','?'}, // / ?
        {0x54,'/','/'}, // Keypad / (Note 1)
        {0x55,'*','*'}, // Keypad *
        {0x56,'-','-'}, // Keypad -
        {0x57,'+','+'}, // Keypad +
        {0x58,0x0A,0x0A}, // Keypad Enter
        {0x59,'1','1'}, // Keypad 1 End
        {0x5A,'2','2'}, // Keypad 2 Down
        {0x5B,'3','3'}, // Keypad 3 PageDn
        {0x5C,'4','4'}, // Keypad 4 Left
        {0x5D,'5','5'}, // Keypad 5
        {0x5E,'6','6'}, // Keypad 6 Right
        {0x5F,'7','7'}, // Keypad 7 Home
        {0x60,'8','8'}, // Keypad 8 Up
        {0x61,'9','9'}, // Keypad 9 PageUp
        {0x62,'0','0'}, // Keypad 0 Insert
        {0x63,'.','.'}, // Keypad . Delete
};
#endif