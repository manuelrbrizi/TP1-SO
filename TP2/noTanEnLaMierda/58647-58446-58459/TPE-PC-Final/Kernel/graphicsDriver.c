#include "videoDriver.h"
#include "lib.h"

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8

#define Y_SPACE 2
#define X_SPACE 1

typedef struct __attribute__((packed)) ModeInfoBlock {
        uint16_t ModeAttributes;
        uint8_t WinAAttributes;
        uint8_t WinBAttributes;
        uint16_t WinGranularity;
        uint16_t WinSize;
        uint16_t WinSegmentA;
        uint16_t WinSegmentB;
        uint32_t WinRealFctPtr;
        uint16_t pitch; 

        uint16_t XResolution;
        uint16_t YResolution;
        uint8_t XcharSize;
        uint8_t YcharSize;
        uint8_t NumberOfPlanes;
        uint8_t BitsPerPixel;
        uint8_t NumberOfBanks;
        uint8_t MemoryModel;
        uint8_t BankSize;
        uint8_t NumberOfImagePages;
        uint8_t ReservedPage;

        uint8_t RedMaskSize;
        uint8_t RedMaskPosition;
        uint8_t GreenMaskSize;
        uint8_t GreenMaskPosition;
        uint8_t BlueMaskSize;
        uint8_t BlueMaskPosition;
        uint8_t ReservedMaskSize;
        uint8_t ReservedMaskPosition;
        uint8_t DirectColorAttributes;

        uint32_t PhysBasePtr;  
        uint32_t OffScreenMemOffset;
        uint16_t OffScreenMemSize;
} Vesa;

const unsigned char font[96][6] = {
        {0x00,0x00,0x00,0x00,0x00,0x00}, //  
        {0x5c,0x00,0x00,0x00,0x00,0x00}, // !
        {0x06,0x00,0x06,0x00,0x00,0x00}, // "
        {0x28,0x7c,0x28,0x7c,0x28,0x00}, // #
        {0x5c,0x54,0xfe,0x54,0x74,0x00}, // $
        {0x44,0x20,0x10,0x08,0x44,0x00}, // %
        {0x28,0x54,0x54,0x20,0x50,0x00}, // &
        {0x06,0x00,0x00,0x00,0x00,0x00}, // '
        {0x38,0x44,0x00,0x00,0x00,0x00}, // (
        {0x44,0x38,0x00,0x00,0x00,0x00}, // )
        {0x02,0x07,0x02,0x00,0x00,0x00}, // *
        {0x10,0x10,0x7c,0x10,0x10,0x00}, // +
        {0xc0,0x00,0x00,0x00,0x00,0x00}, // ,
        {0x10,0x10,0x10,0x10,0x10,0x00}, // -
        {0x40,0x00,0x00,0x00,0x00,0x00}, // .
        {0x60,0x10,0x0c,0x00,0x00,0x00}, // /
        {0x7c,0x64,0x54,0x4c,0x7c,0x00}, // 0
        {0x48,0x7c,0x40,0x00,0x00,0x00}, // 1
        {0x64,0x54,0x54,0x54,0x48,0x00}, // 2
        {0x44,0x54,0x54,0x54,0x6c,0x00}, // 3
        {0x3c,0x20,0x70,0x20,0x20,0x00}, // 4
        {0x5c,0x54,0x54,0x54,0x24,0x00}, // 5
        {0x7c,0x54,0x54,0x54,0x74,0x00}, // 6
        {0x04,0x04,0x64,0x14,0x0c,0x00}, // 7
        {0x7c,0x54,0x54,0x54,0x7c,0x00}, // 8
        {0x5c,0x54,0x54,0x54,0x7c,0x00}, // 9
        {0x44,0x00,0x00,0x00,0x00,0x00}, // :
        {0xc4,0x00,0x00,0x00,0x00,0x00}, // ;
        {0x10,0x28,0x44,0x00,0x00,0x00}, // <
        {0x28,0x28,0x28,0x28,0x28,0x00}, // =
        {0x44,0x28,0x10,0x00,0x00,0x00}, // >
        {0x08,0x04,0x54,0x08,0x00,0x00}, // ?
        {0x7c,0x44,0x54,0x54,0x5c,0x00}, // @
        {0x7c,0x24,0x24,0x24,0x7c,0x00}, // A
        {0x7c,0x54,0x54,0x54,0x6c,0x00}, // B
        {0x7c,0x44,0x44,0x44,0x44,0x00}, // C
        {0x7c,0x44,0x44,0x44,0x38,0x00}, // D
        {0x7c,0x54,0x54,0x54,0x44,0x00}, // E
        {0x7c,0x14,0x14,0x14,0x04,0x00}, // F
        {0x7c,0x44,0x44,0x54,0x74,0x00}, // G
        {0x7c,0x10,0x10,0x10,0x7c,0x00}, // H
        {0x44,0x44,0x7c,0x44,0x44,0x00}, // I
        {0x60,0x40,0x40,0x44,0x7c,0x00}, // J
        {0x7c,0x10,0x10,0x28,0x44,0x00}, // K
        {0x7c,0x40,0x40,0x40,0x40,0x00}, // L
        {0x7c,0x08,0x10,0x08,0x7c,0x00}, // M
        {0x7c,0x08,0x10,0x20,0x7c,0x00}, // N
        {0x38,0x44,0x44,0x44,0x38,0x00}, // O
        {0x7c,0x14,0x14,0x14,0x08,0x00}, // P
        {0x3c,0x24,0x64,0x24,0x3c,0x00}, // Q
        {0x7c,0x14,0x14,0x14,0x68,0x00}, // R
        {0x5c,0x54,0x54,0x54,0x74,0x00}, // S
        {0x04,0x04,0x7c,0x04,0x04,0x00}, // T
        {0x7c,0x40,0x40,0x40,0x7c,0x00}, // U
        {0x0c,0x30,0x40,0x30,0x0c,0x00}, // V
        {0x3c,0x40,0x30,0x40,0x3c,0x00}, // W
        {0x44,0x28,0x10,0x28,0x44,0x00}, // X
        {0x0c,0x10,0x60,0x10,0x0c,0x00}, // Y
        {0x44,0x64,0x54,0x4c,0x44,0x00}, // Z
        {0x7c,0x44,0x00,0x00,0x00,0x00}, // [
        {0x0c,0x10,0x60,0x00,0x00,0x00}, // "\"
        {0x44,0x7c,0x00,0x00,0x00,0x00}, // ]
        {0x00,0x01,0x00,0x01,0x00,0x00}, // ^
        {0x40,0x40,0x40,0x40,0x40,0x40}, // _
        {0x00,0x01,0x00,0x00,0x00,0x00}, // `
        {0x7c,0x24,0x24,0x24,0x7c,0x00}, // a
        {0x7c,0x54,0x54,0x54,0x6c,0x00}, // b
        {0x7c,0x44,0x44,0x44,0x44,0x00}, // c
        {0x7c,0x44,0x44,0x44,0x38,0x00}, // d
        {0x7c,0x54,0x54,0x54,0x44,0x00}, // e
        {0x7c,0x14,0x14,0x14,0x04,0x00}, // f
        {0x7c,0x44,0x44,0x54,0x74,0x00}, // g
        {0x7c,0x10,0x10,0x10,0x7c,0x00}, // h
        {0x44,0x44,0x7c,0x44,0x44,0x00}, // i
        {0x60,0x40,0x40,0x44,0x7c,0x00}, // j
        {0x7c,0x10,0x10,0x28,0x44,0x00}, // k
        {0x7c,0x40,0x40,0x40,0x40,0x00}, // l
        {0x7c,0x08,0x10,0x08,0x7c,0x00}, // m
        {0x7c,0x08,0x10,0x20,0x7c,0x00}, // n
        {0x38,0x44,0x44,0x44,0x38,0x00}, // o
        {0x7c,0x14,0x14,0x14,0x08,0x00}, // p
        {0x3c,0x24,0x64,0x24,0x3c,0x00}, // q
        {0x7c,0x14,0x14,0x14,0x68,0x00}, // r
        {0x5c,0x54,0x54,0x54,0x74,0x00}, // s
        {0x04,0x04,0x7c,0x04,0x04,0x00}, // t
        {0x7c,0x40,0x40,0x40,0x7c,0x00}, // u
        {0x0c,0x30,0x40,0x30,0x0c,0x00}, // v
        {0x3c,0x40,0x30,0x40,0x3c,0x00}, // w
        {0x44,0x28,0x10,0x28,0x44,0x00}, // x
        {0x0c,0x10,0x60,0x10,0x0c,0x00}, // y
        {0x44,0x64,0x54,0x4c,0x44,0x00}, // z
        {0x10,0x7c,0x44,0x00,0x00,0x00}, // {
        {0x6c,0x00,0x00,0x00,0x00,0x00}, // |
        {0x44,0x7c,0x10,0x00,0x00,0x00}, // }
        {0x02,0x01,0x02,0x01,0x00,0x00}, // ~
        {0x00,0x00,0x00,0x00,0x00,0x00}
};



static Vesa * video = (Vesa*)0x5C00;

static int xpos = 0;
static int ypos = 0;

static int xprev = 0;
static int yprev = 0;

void newLine();
void erase_char();
void scroll();


void drawPixel(int x, int y, int colour){
        unsigned location = y*video->pitch + x*(video->BitsPerPixel/8);
        char * screen = (char *) (video->PhysBasePtr + location);
        *(screen) = colour & 225;
        *(screen + 1) = (colour >> 8) & 225;
        *(screen +2) = (colour >> 16) & 225;
}

void drawChar(char c, int color) {
    uint8_t i,j;

        if(c == '\n'){
                newLine();
                return;
        }
        if(c == '\b'){
                erase_char();
                return;
        }

    if (c < ' ') {
        c = 0;
    } else {
        c -= ' ';
    }

    for (i=0; i<6; i++) {
        for (j=0; j<8; j++) {
            if (font[c][i] & (1<<j)) {
                for(int k = 0;k<2;k++){
                    for(int l =0; l<2; l++){
                        drawPixel(xpos+2*i+k, ypos+2*j+l , color);
                    }
                }
            }
        }
    }

    xpos += CHAR_WIDTH*2;
   
}

void drawCharAt(char c, int color,int x,int y) {
    uint8_t i,j;

        if(c == '\n'){
                newLine();
                return;
        }
        if(c == '\b'){
                erase_char();
                return;
        }

    if (c < ' ') {
        c = 0;
    } else {
        c -= ' ';
    }

    for (i=0; i<6; i++) {
        for (j=0; j<8; j++) {
            if (font[c][i] & (1<<j)) {
                for(int k = 0;k<2;k++){
                    for(int l =0; l<2; l++){
                        drawPixel(x+2*i+k, y+2*j+l , color);
                    }
                }
            }
        }
    }
}


void drawString(char * str, int size){
    for(int i = 0; i<size && str[i]!='\0'; i++){
        drawChar(str[i],0x3ecc60);
        if( xpos >= 2*CHAR_WIDTH* 85){
            ypos += CHAR_HEIGHT*2;
            xpos = 0;
            if(ypos >= 48*2*CHAR_HEIGHT){
                scroll();
                ypos -= 2*CHAR_HEIGHT;
            }
        }
    }
}

void scroll(){

        unsigned location = ((2*CHAR_HEIGHT)+(2*Y_SPACE))*(video->pitch) + X_SPACE*(video->BitsPerPixel/8);

        char * source = (char *) (video->PhysBasePtr + location);
        unsigned whereOnScreen2 = (Y_SPACE)*(video->pitch) + X_SPACE*(video->BitsPerPixel/8);
        char * dest = (char *) (video->PhysBasePtr + whereOnScreen2);
        int size = (video->YResolution)*(video->XResolution)*3;
        memcpy(dest, source, size);

}

void newLine(){

        ypos += CHAR_HEIGHT*2;

        xpos = 0;
        if(ypos >= 48*2*CHAR_HEIGHT){
                scroll();
                ypos -= 2*CHAR_HEIGHT;
            }
}

void clear(){

    for(int i = 0; i<video->XResolution*3;i++){
        for(int j = 0; j < video->YResolution*3;j++){
            drawPixel(i,j,0x0000000000000000);
        }
    }
    xprev = 0;
    yprev = 0;

    xpos = 0;
    ypos = 0;
}




void drawBar(int x, int y){
    for(int l=0;l<22;l++){
        for(int k = 0; k<22;k++){
            drawPixel(x+k, y-l, 0x0000000000000000000);
        }
    }

    for(int l=0;l<22;l++){
        for(int k = 0; k<22;k++){
            drawPixel(x+k, y+150+l, 0x0000000000000000000);
        }
    }

    for(int i =0; i<20; i++){
        for(int j = 0; j<150;j++){
            drawPixel(x+i,y+j,0x3ecc60);
        }
    }
}


void drawBall(int x, int y){
    if(xprev == 0){
        for(int i = 130; i<135;i++){
            for(int j = 0; j < video->XResolution*3;j++){
                drawPixel(j,i,0x3ecc60);
        }
    }
    }

    for(int i =0; i<20; i++){
        for(int j = 0; j<20;j++){
            drawPixel(xprev+i,yprev+j,0x0000000000000000000);
        }
    }

    for(int i =0; i<20; i++){
        for(int j = 0; j<20;j++){
            drawPixel(x+i,y+j,0x3ecc60);
        }
    }

    xprev=x;
    yprev=y;

}


void erase_char(){
    xpos -= CHAR_WIDTH*2;
    for (int i =0; i<6; i++) {
        for (int j=0; j<8; j++) {
            for(int k = 0;k<2;k++){
                for(int l =0; l<2; l++){
                    drawPixel(xpos+2*i+k, ypos+2*j+l , 0x0000000000000000);

                }
            }
        }
    }
}

