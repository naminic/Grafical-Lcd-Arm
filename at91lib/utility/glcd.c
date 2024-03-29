//-----------------------
// #ifndef glcd_INCLUDED_
// #define glcd_INCLUDED_
#include "glcd.h"
#include "font.h"
#include <board.h>
#include <pio/pio.h>
#include <ssc/ssc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//-----------------------
#define KS0108_SCREEN_WIDTH	128
#define KS0108_SCREEN_HEIGHT 64


#define DISPLAY_SET_Y       0x40
#define DISPLAY_SET_X       0xB8
#define DISPLAY_START_LINE  0xC0
#define DISPLAY_ON_CMD		0x3E
#define ON	0x01
#define OFF	0x00
#define DISPLAY_STATUS_BUSY	0x80

#define DATAREG 1    
#define CONTROL 0    
#define LCD_ENABLE      1   //Zero Bit
#define LCD_CS1      0
#define LCD_CS2      1

#define DELAY()           { int i=200; while(i-- != 0); }

void glcd_init(void);
void GLCD_DisableController(unsigned char controller);
void GLCD_EnableController(unsigned char controller);
void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller);
static void DATAPORT(char val);
void GLCD_WriteData(unsigned char dataToWrite);
unsigned char GLCD_ReadByteFromROMMemory(char * ptr);
void GLCD_ClearScreen(void);
void GLCD_GoTo(unsigned char x, unsigned char y);
void GLCD_WriteChar(char charToWrite);
void GLCD_WriteString(char * stringToWrite);
void GLCD_Bitmap(char * bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy);
void putpixel(unsigned int x, unsigned int y);
void SetPage(unsigned char x);
void SetColumn(unsigned char y);
unsigned char pow2(unsigned char a,unsigned char b);
void sendlcddataram(unsigned char values);
void output(int port, unsigned char value);
int  GLCD_Write_farsi(char charToWrite);
void GLCD_WriteString_farsi(unsigned char * stringToWrite,int i);

	   const unsigned char F_FONT_MAP[111][4]={
  0xFF, 0xFF, 0xFF, 0xFF,  // 127  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 128  =>
  0x06, 0x06, 0x05, 0x05,  // 129  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 130  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 131  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 132  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 133  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 134  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 135  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 136  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 137  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 138  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 139  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 140  =>
  0x0E, 0x0E, 0x0D, 0x0D,  // 141  =>   ?
  0x17, 0x17, 0x17, 0x17,  // 142  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 143  =>
  0x31, 0x31, 0x30, 0x30,  // 144  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 145  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 146  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 147  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 148  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 149  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 150  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 151  =>
  0x2F, 0x2F, 0x2E, 0x2E,  // 152  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 153  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 154  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 155  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 156  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 157  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 158  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 159  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 160  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 161  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 162  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 163  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 164  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 165  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 166  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 167  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 168  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 169  =>
  0x3C, 0x3B, 0x3A, 0x39,  // 170  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 171  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 172  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 173  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 174  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 175  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 176  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 177  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 178  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 179  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 180  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 181  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 182  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 183  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 184  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 185  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 186  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 187  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 188  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 189  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 190  =>
  0x43, 0x43, 0x43, 0x43,  // 191  =>   ?
  0x3C, 0x3B, 0xFF, 0xFF,  // 192  =>   ?
  0x40, 0x40, 0x40, 0x40,  // 193  =>   ?
  0xFF, 0xFF, 0xFF, 0x00,  // 194  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 195  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 196  =>   ?
  0x02, 0x02, 0x02, 0x02,  // 197  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 198  =>   ?
  0x02, 0x01, 0x01, 0x02,  // 199  =>   ?
  0x04, 0x04, 0x03, 0x03,  // 200  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 201  =>   ?
  0x08, 0x08, 0x07, 0x07,  // 202  =>   ?
  0x0A, 0x0A, 0x09, 0x09,  // 203  =>   ?
  0x0C, 0x0C, 0x0B, 0x0B,  // 204  =>   ?
  0x10, 0x10, 0x0F, 0x0F,  // 205  =>   ?
  0x12, 0x12, 0x11, 0x11,  // 206  =>   ?
  0x13, 0x13, 0x13, 0x13,  // 207  =>   ?
  0x14, 0x14, 0x14, 0x14,  // 208  =>   ?
  0x15, 0x15, 0x15, 0x15,  // 209  =>   ?
  0x16, 0x16, 0x16, 0x16,  // 210  =>   ?
  0x19, 0x19, 0x18, 0x18,  // 211  =>   ?
  0x1B, 0x1B, 0x1A, 0x1A,  // 212  =>   ?
  0x1D, 0x1D, 0x1C, 0x1C,  // 213  =>   ?
  0x1F, 0x1F, 0x1E, 0x1E,  // 214  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 215  =>
  0x20, 0x20, 0x20, 0x20,  // 216  =>   ?
  0x21, 0x21, 0x21, 0x21,  // 217  =>   ?
  0x25, 0x24, 0x23, 0x22,  // 218  =>   ?
  0x29, 0x28, 0x27, 0x26,  // 219  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 220  =>
  0x2B, 0x2B, 0x2A, 0x2A,  // 221  =>   ?
  0x2D, 0x2D, 0x2C, 0x2C,  // 222  =>   ?
  0x2F, 0x2F, 0x2E, 0x2E,  // 223  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 224  =>
  0x33, 0x33, 0x32, 0x32,  // 225  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 226  =>
  0x35, 0x35, 0x34, 0x34,  // 227  =>   ?
  0x37, 0x37, 0x36, 0x36,  // 228  =>   ?
  0x3C, 0x3B, 0x3A, 0x39,  // 229  =>   ?
  0x38, 0x38, 0x38, 0x38,  // 230  =>   ?
  0xFF, 0xFF, 0xFF, 0xFF,  // 231  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 232  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 233  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 234  =>
  0xFF, 0xFF, 0xFF, 0xFF,  // 235  =>
  0x3F, 0x3E, 0x3D, 0x3D,  // 236  =>   ?
  0x3F, 0x3E, 0x3D, 0x3D  // 237  =>   ?
};

    	const static char farsi[78][8] = {
       0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x3A, 0x02,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xA0, 0x18,
       0x18, 0x24, 0x20, 0xA0, 0x20, 0x20, 0x20, 0x18,
       0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xA0, 0x98,
       0x18, 0x24, 0x20, 0xA0, 0xA0, 0xA0, 0x20, 0x18,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x22, 0x1A,
       0x18, 0x24, 0x20, 0x22, 0x20, 0x22, 0x20, 0x18,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x21, 0x1A,
       0x18, 0x24, 0x20, 0x24, 0x22, 0x24, 0x20, 0x18,
       0x00, 0x00, 0x20, 0x28, 0x24, 0xA4, 0x28, 0x10,
       0x00, 0x40, 0xA0, 0xA8, 0xA4, 0x24, 0xA8, 0x10,
       0x00, 0x00, 0x20, 0xA8, 0xA4, 0xA4, 0x28, 0x10,
       0x00, 0x40, 0xA0, 0xA8, 0x24, 0xA4, 0xA8, 0x90,
       0x00, 0x00, 0x20, 0x28, 0x24, 0x24, 0x28, 0x10,
       0x00, 0x40, 0xA0, 0xA8, 0xA4, 0x24, 0x28, 0x10,
       0x00, 0x20, 0x22, 0x28, 0x24, 0x24, 0x28, 0x10,
       0x00, 0x40, 0xA2, 0xA8, 0xA4, 0x24, 0x28, 0x10,
       0x00, 0x00, 0x00, 0x20, 0x40, 0x44, 0x28, 0x10,
       0x00, 0x00, 0x00, 0x22, 0x40, 0x44, 0x28, 0x10,
       0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x38,
       0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3A,
       0x00, 0x00, 0x00, 0x00, 0x80, 0x84, 0x42, 0x34,
       0x00, 0x20, 0x20, 0x18, 0x20, 0x18, 0x20, 0x18,
       0x70, 0x88, 0x80, 0x78, 0x20, 0x18, 0x20, 0x18,
       0x00, 0x20, 0x20, 0x18, 0x22, 0x19, 0x22, 0x18,
       0x70, 0x88, 0x80, 0x78, 0x22, 0x19, 0x22, 0x18,
       0x00, 0x20, 0x18, 0x30, 0x28, 0x24, 0x24, 0x18,
       0x70, 0x88, 0x80, 0x7C, 0x28, 0x24, 0x24, 0x18,
       0x00, 0x20, 0x18, 0x32, 0x28, 0x24, 0x24, 0x18,
       0x70, 0x88, 0x80, 0x7C, 0x28, 0x25, 0x24, 0x18,
       0x00, 0x00, 0x20, 0x3E, 0x28, 0x24, 0x24, 0x18,
       0x00, 0x00, 0x20, 0x3E, 0x28, 0x25, 0x24, 0x18,
       0x00, 0x00, 0x00, 0x20, 0x38, 0x24, 0x24, 0x28,
       0x00, 0x00, 0x20, 0x28, 0x34, 0x14, 0x34, 0x2C,
       0x00, 0x00, 0x00, 0x40, 0xA8, 0x94, 0x94, 0xA8,
       0x00, 0x00, 0x00, 0x60, 0x90, 0x9C, 0x92, 0x92,
       0x00, 0x00, 0x00, 0x20, 0x38, 0x24, 0x25, 0x28,
       0x00, 0x00, 0x20, 0x28, 0x34, 0x15, 0x34, 0x2C,
       0x00, 0x00, 0x00, 0x40, 0xA8, 0x94, 0x95, 0xA8,
       0x00, 0x00, 0x00, 0x62, 0x90, 0x9C, 0x92, 0x92,
       0x00, 0x00, 0x00, 0x20, 0x38, 0x25, 0x24, 0x18,
       0x18, 0x24, 0x20, 0x20, 0x38, 0x25, 0x24, 0x18,
       0x00, 0x00, 0x00, 0x20, 0x39, 0x24, 0x25, 0x18,
       0x00, 0x30, 0x48, 0x80, 0x99, 0xA4, 0xA5, 0x78,
       0x00, 0x00, 0x20, 0x2C, 0x2A, 0x2A, 0x2A, 0x12,
       0x18, 0x24, 0x20, 0x2C, 0x2A, 0x2A, 0x2A, 0x12,
       0x00, 0x00, 0x20, 0x2C, 0x2A, 0x2B, 0x2B, 0x13,
       0x18, 0x24, 0x20, 0x2C, 0x2A, 0x2B, 0x2B, 0x13,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x1E,
       0x00, 0x00, 0x30, 0x48, 0x40, 0x40, 0x20, 0x1E,
       0x00, 0x00, 0x20, 0x20, 0x18, 0x24, 0x24, 0x18,
       0x00, 0x00, 0xF0, 0x08, 0x18, 0x24, 0x24, 0x18,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x22, 0x18,
       0x00, 0x30, 0x48, 0x80, 0x84, 0x80, 0x40, 0x38,
       0x00, 0x00, 0x00, 0x00, 0x98, 0xA4, 0xA4, 0x78,
       0x00, 0x00, 0x20, 0x28, 0x15, 0x2A, 0x24, 0x18,
       0x00, 0x00, 0x20, 0x78, 0xA4, 0x54, 0x28, 0x20,
       0x00, 0x00, 0x00, 0x00, 0x0C, 0x12, 0x02, 0x1E,
       0x00, 0x00, 0x00, 0x00, 0x30, 0x44, 0x48, 0x30,
       0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xA0, 0x18,
       0x00, 0x70, 0x88, 0x80, 0x90, 0xA8, 0x48, 0x10,
       0x00, 0x38, 0x44, 0x80, 0x8C, 0x92, 0x92, 0x64,
       0x00, 0x00, 0x00, 0x00, 0x2C, 0x12, 0x08, 0x04,
       0x00, 0x00, 0x00, 0x00, 0x22, 0x3C, 0x20, 0x1E,
       0x00, 0x18, 0x14, 0x3E, 0x40, 0x3E, 0x40, 0x3E,
       0x00, 0x00, 0x00, 0x0C, 0x12, 0xA2, 0x02, 0x04,
       0x00, 0x00, 0x00, 0x00, 0x30, 0x48, 0x48, 0x30,
       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E,
       0x00, 0x00, 0x00, 0x00, 0x7E, 0x08, 0x08, 0x06,
       0x00, 0x00, 0x7E, 0x08, 0x08, 0x06, 0x08, 0x06,
       0x00, 0x00, 0x00, 0x7C, 0x10, 0x1C, 0x12, 0x12,
       0x00, 0x00, 0x30, 0x48, 0x22, 0x44, 0x48, 0x30,
       0x00, 0x00, 0x0C, 0x52, 0x30, 0x10, 0x08, 0x04,
       0x00, 0x00, 0x00, 0x06, 0x18, 0x60, 0x18, 0x06,
       0x00, 0x00, 0x00, 0x60, 0x18, 0x06, 0x18, 0x60,
       0x00, 0x00, 0x00, 0x00, 0x0C, 0x12, 0x12, 0x7C,
       };
			 
			 
static const char font5x8[] = {
0x00, 0x00, 0x00, 0x00, 0x00,// (spacja)
0x00, 0x00, 0x5F, 0x00, 0x00,// !
0x00, 0x07, 0x00, 0x07, 0x00,// "
0x14, 0x7F, 0x14, 0x7F, 0x14,// #
0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
0x23, 0x13, 0x08, 0x64, 0x62,// %
0x36, 0x49, 0x55, 0x22, 0x50,// &
0x00, 0x05, 0x03, 0x00, 0x00,// '
0x00, 0x1C, 0x22, 0x41, 0x00,// (
0x00, 0x41, 0x22, 0x1C, 0x00,// )
0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
0x08, 0x08, 0x3E, 0x08, 0x08,// +
0x00, 0x50, 0x30, 0x00, 0x00,// ,
0x08, 0x08, 0x08, 0x08, 0x08,// -
0x00, 0x30, 0x30, 0x00, 0x00,// .
0x20, 0x10, 0x08, 0x04, 0x02,// /
0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
0x00, 0x42, 0x7F, 0x40, 0x00,// 1
0x42, 0x61, 0x51, 0x49, 0x46,// 2
0x21, 0x41, 0x45, 0x4B, 0x31,// 3
0x18, 0x14, 0x12, 0x7F, 0x10,// 4
0x27, 0x45, 0x45, 0x45, 0x39,// 5
0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
0x01, 0x71, 0x09, 0x05, 0x03,// 7
0x36, 0x49, 0x49, 0x49, 0x36,// 8
0x06, 0x49, 0x49, 0x29, 0x1E,// 9
0x00, 0x36, 0x36, 0x00, 0x00,// :
0x00, 0x56, 0x36, 0x00, 0x00,// ;
0x00, 0x08, 0x14, 0x22, 0x41,// <
0x14, 0x14, 0x14, 0x14, 0x14,// =
0x41, 0x22, 0x14, 0x08, 0x00,// >
0x02, 0x01, 0x51, 0x09, 0x06,// ?
0x32, 0x49, 0x79, 0x41, 0x3E,// @
0x7E, 0x11, 0x11, 0x11, 0x7E,// A
0x7F, 0x49, 0x49, 0x49, 0x36,// B
0x3E, 0x41, 0x41, 0x41, 0x22,// C
0x7F, 0x41, 0x41, 0x22, 0x1C,// D
0x7F, 0x49, 0x49, 0x49, 0x41,// E
0x7F, 0x09, 0x09, 0x01, 0x01,// F
0x3E, 0x41, 0x41, 0x51, 0x32,// G
0x7F, 0x08, 0x08, 0x08, 0x7F,// H
0x00, 0x41, 0x7F, 0x41, 0x00,// I
0x20, 0x40, 0x41, 0x3F, 0x01,// J
0x7F, 0x08, 0x14, 0x22, 0x41,// K
0x7F, 0x40, 0x40, 0x40, 0x40,// L
0x7F, 0x02, 0x04, 0x02, 0x7F,// M
0x7F, 0x04, 0x08, 0x10, 0x7F,// N
0x3E, 0x41, 0x41, 0x41, 0x3E,// O
0x7F, 0x09, 0x09, 0x09, 0x06,// P
0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
0x7F, 0x09, 0x19, 0x29, 0x46,// R
0x46, 0x49, 0x49, 0x49, 0x31,// S
0x01, 0x01, 0x7F, 0x01, 0x01,// T
0x3F, 0x40, 0x40, 0x40, 0x3F,// U
0x1F, 0x20, 0x40, 0x20, 0x1F,// V
0x7F, 0x20, 0x18, 0x20, 0x7F,// W
0x63, 0x14, 0x08, 0x14, 0x63,// X
0x03, 0x04, 0x78, 0x04, 0x03,// Y
0x61, 0x51, 0x49, 0x45, 0x43,// Z
0x00, 0x00, 0x7F, 0x41, 0x41,// [
0x02, 0x04, 0x08, 0x10, 0x20,// "\"
0x41, 0x41, 0x7F, 0x00, 0x00,// ]
0x04, 0x02, 0x01, 0x02, 0x04,// ^
0x40, 0x40, 0x40, 0x40, 0x40,// _
0x00, 0x01, 0x02, 0x04, 0x00,// `
0x20, 0x54, 0x54, 0x54, 0x78,// a
0x7F, 0x48, 0x44, 0x44, 0x38,// b
0x38, 0x44, 0x44, 0x44, 0x20,// c
0x38, 0x44, 0x44, 0x48, 0x7F,// d
0x38, 0x54, 0x54, 0x54, 0x18,// e
0x08, 0x7E, 0x09, 0x01, 0x02,// f
0x08, 0x14, 0x54, 0x54, 0x3C,// g
0x7F, 0x08, 0x04, 0x04, 0x78,// h
0x00, 0x44, 0x7D, 0x40, 0x00,// i
0x20, 0x40, 0x44, 0x3D, 0x00,// j
0x00, 0x7F, 0x10, 0x28, 0x44,// k
0x00, 0x41, 0x7F, 0x40, 0x00,// l
0x7C, 0x04, 0x18, 0x04, 0x78,// m
0x7C, 0x08, 0x04, 0x04, 0x78,// n
0x38, 0x44, 0x44, 0x44, 0x38,// o
0x7C, 0x14, 0x14, 0x14, 0x08,// p
0x08, 0x14, 0x14, 0x18, 0x7C,// q
0x7C, 0x08, 0x04, 0x04, 0x08,// r
0x48, 0x54, 0x54, 0x54, 0x20,// s
0x04, 0x3F, 0x44, 0x40, 0x20,// t
0x3C, 0x40, 0x40, 0x20, 0x7C,// u
0x1C, 0x20, 0x40, 0x20, 0x1C,// v
0x3C, 0x40, 0x30, 0x40, 0x3C,// w
0x44, 0x28, 0x10, 0x28, 0x44,// x
0x0C, 0x50, 0x50, 0x50, 0x3C,// y
0x44, 0x64, 0x54, 0x4C, 0x44,// z
0x00, 0x08, 0x36, 0x41, 0x00,// {
0x00, 0x00, 0x7F, 0x00, 0x00,// |
0x00, 0x41, 0x36, 0x08, 0x00,// }
0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};
static const Pin GLcdpins[] = {GLCD_PINS};
static const Pin sscPins[] = {PIN_SSC_TD, PIN_SSC_TK,PIN_SSC_TF};
//-------------------------
unsigned char screen_x = 0, screen_y = 0;
unsigned char CurrentColumn,DisplayData[8][128];
//----------------------
static void DATAPORT(char val)
{
	SSC_Write(AT91C_BASE_SSC,0);
	SSC_Write(AT91C_BASE_SSC,val);
}

//------------------------
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_DisableController(unsigned char controller)
{
switch(controller){
	case 0 : PIO_Set(&GLcdpins[4]); break;
	case 1 : PIO_Set(&GLcdpins[3]); break;
	}
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_EnableController(unsigned char controller)
{
    switch(controller)
    {
        case 0 : PIO_Clear(&GLcdpins[4]); break;
        case 1 : PIO_Clear(&GLcdpins[3]); break;
    }
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller)
{
unsigned int command;
DELAY();

PIO_Clear(&GLcdpins[0]);
PIO_Clear(&GLcdpins[2]);
GLCD_EnableController(controller);
command=commandToWrite;
DATAPORT(command);	
PIO_Set(&GLcdpins[1]);	
DELAY();	
PIO_Clear(&GLcdpins[1]);	
GLCD_DisableController(controller);
}
//-------------------------------------
void GLCD_WriteData(unsigned char dataToWrite)
{
unsigned int byte;
DELAY() 	
PIO_Clear(&GLcdpins[2]);
PIO_Set(&GLcdpins[0]);	
byte = dataToWrite;
DATAPORT(byte);	
GLCD_EnableController(screen_x / 64);
PIO_Set(&GLcdpins[1]);
DELAY();	
PIO_Clear(&GLcdpins[1]);	
GLCD_DisableController(screen_x / 64);
screen_x++;
}

//-----------------------------
void GLCD_GoTo(unsigned char x, unsigned char y)
{
unsigned char i;
screen_x = x;
screen_y = y;

for(i = 0; i < KS0108_SCREEN_WIDTH/64; i++)
{
    GLCD_WriteCommand(DISPLAY_SET_Y | 0,i);
    GLCD_WriteCommand(DISPLAY_SET_X | y,i);
    GLCD_WriteCommand(DISPLAY_START_LINE | 0,i);
}
GLCD_WriteCommand(DISPLAY_SET_Y | (x % 64), (x / 64));
GLCD_WriteCommand(DISPLAY_SET_X | y, (x / 64));
}

//---------------------------
unsigned char GLCD_ReadByteFromROMMemory(char * ptr)
{
return *(ptr);
}

//---------------------------
void glcd_init(void)
{
	unsigned int tcmr,tfmr;
	unsigned char i;
  
  PIO_Configure(GLcdpins,PIO_LISTSIZE(GLcdpins));
	PIO_Configure(sscPins, PIO_LISTSIZE(sscPins));	
	
	PIO_Set(&GLcdpins[3]);
	PIO_Set(&GLcdpins[4]);
	
	SSC_Configure(AT91C_BASE_SSC,AT91C_ID_SSC,500000,BOARD_MCK);
    
  tcmr=AT91C_SSC_CKS_TK|AT91C_SSC_CKO_DATA_TX|AT91C_SSC_START_CONTINOUS;
  tfmr=SSC_DATLEN(8)|SSC_DATNB(15)|SSC_FSLEN(16)|AT91C_SSC_FSOS_LOW|AT91C_SSC_FSDEN ;
    
  SSC_ConfigureTransmitter(AT91C_BASE_SSC,tcmr,tfmr);
  SSC_EnableTransmitter(AT91C_BASE_SSC);
	
	PIO_Set(&GLcdpins[5]); 
  //PIO_Clear(&GLcdpins[5]);
	for(i = 0; i < 3; i++);
  GLCD_WriteCommand((DISPLAY_ON_CMD | ON), i);
	
}	
//--------------------------------
void GLCD_ClearScreen(void)
{
unsigned char i, j;
for(j = 0; j < KS0108_SCREEN_HEIGHT/8; j++)
  {
    GLCD_GoTo(0,j);
    for(i = 0; i < KS0108_SCREEN_WIDTH; i++)
        GLCD_WriteData(0x00);
  }
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteChar(char charToWrite)
{
int i;
charToWrite -= 32; 
for(i = 0; i < 5; i++) 
  GLCD_WriteData(GLCD_ReadByteFromROMMemory((char *)((int)font5x8 + (5 * charToWrite) + i))); 
GLCD_WriteData(0x00);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteString(char * stringToWrite)
{
while(*stringToWrite)
  GLCD_WriteChar(*stringToWrite++);
}

//-----------------------
void SetPage(unsigned char x){
	GLCD_WriteCommand(DISPLAY_SET_X | x, 0);
	GLCD_WriteCommand(DISPLAY_SET_X | x, 1);
}
//-----------------------
void SetColumn(unsigned char y){
CurrentColumn = y;
if (y < 64){
	GLCD_WriteCommand(DISPLAY_SET_Y | (y&63), 0);
	GLCD_WriteCommand(DISPLAY_SET_Y | 0, 1);
	 }
else{
	GLCD_WriteCommand(DISPLAY_SET_Y | 63, 0);
	GLCD_WriteCommand(DISPLAY_SET_Y | ((y-64)&63), 1);
	 }
}
//-----------------------
unsigned char pow2(unsigned char a,unsigned char b){
unsigned char i=0,ret=1;
for(;i<b;i++) ret*=a;
return ret;
}
//-----------------------
void sendlcddataram(unsigned char values){
unsigned char c_s;
c_s = CurrentColumn>63?LCD_CS2:LCD_CS1;
output(CONTROL, c_s );   
DELAY();
output(DATAREG,values); 
DELAY();
output(CONTROL, LCD_ENABLE | c_s ); 
DELAY();
}
//-----------------------
void output(int port, unsigned char value){

int dummy=0;  
if(port){
    dummy = ((unsigned int)value & 0xFC) <<24 | ((unsigned int)value & 0x01)<<17  | ((unsigned int)value & 0x02)<<17;
    //AT91F_PIO_ClearOutput ( AT91C_BASE_PIOA, 1<<17 | 1<<18 | 1<<26 | 1<<27 | 1<<28 | 1<<29 | 1<<30 | 1<<31 );
    //AT91F_PIO_SetOutput ( AT91C_BASE_PIOA, dummy);  
DATAPORT(dummy);  
}
else{
	if(value&1) value&=0XFE; else value|=1;
	if(value&2) value&=0XFD; else value|=2;
	if(value&8) value&=0XF7; else value|=8;

	//CTRLPORT=value;     
	}
}
//-----------------------

//-----------------------
void putpixel(unsigned int x, unsigned int y)
{
    unsigned char tmp=0;
    GLCD_GoTo(x, (y / 8));
    tmp |= (1 << (y % 8));
    GLCD_WriteData(tmp);
}
void GLCD_Bitmap(char * bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy)
{
unsigned char i, j;
for(j = 0; j < dy / 8; j++)
  {
  GLCD_GoTo(x,y + j);
  for(i = 0; i < dx; i++) 
    GLCD_WriteData(GLCD_ReadByteFromROMMemory(bmp++));
  }
}
//-----------------------

//-----------------------
void GLCD_Write_font(char charToWrite)
{
	int i;
	for(i = 0; i < 8; i++) 
		GLCD_WriteData(GLCD_ReadByteFromROMMemory((char *)((int)font + (8 * charToWrite) + i))); 
}
//-----------------------

//-----------------------
int  GLCD_Write_farsi(char charToWrite)
{
//charToWrite -= 32; 
 char  bit_8;
int i,ii=0;
for(i = 0; i < 8; i++)
{
    bit_8=GLCD_ReadByteFromROMMemory((char *)((int)farsi + (8 * charToWrite) + i));
	if(bit_8 == 0x00)
	         ii++;
  GLCD_WriteData(bit_8); 
}
   return (ii);
}

//-----------------------

//-----------------------

void GLCD_WriteString_farsi(unsigned char * stringToWrite,int i)
{
    unsigned char buffer[18],char_to_write;
	unsigned  char *str,val;
	str=buffer+1;
	int  index=0,data;
	int  j=1,k=1,d=0;
while(*stringToWrite)
   {
       buffer[j]=*stringToWrite;
	   stringToWrite++;
	   j++;
   }
	  buffer[0]=32;
	  buffer[j+1]='\0';
	  buffer[j+2]='\0';

	while(*str)
	{
	   
      str--;
      val = *str;
      str++;
      if(val==32 || val==199 || val==194 || val==207 || val==208 || val==209 || val==210 || val==142 || val==230)
      {
          str++;
          val = *str;
          str--;
          if(val==32 || val=='\0')
          data = 0;
          else
          data = 3;
      }
      else
      {
           str++;
           val = *str;
           str--;
           if(val==32 || val=='\0')
           data = 1;
           else
           data = 2;
       }
	   if(*str>=127)
	   {    
		   char_to_write=F_FONT_MAP[*str-127][data];
		    
	        GLCD_GoTo((128-k*8+index),i); 
			k++;
			str++;
		   index=GLCD_Write_farsi(char_to_write)+index;
		}
		else
		{
		  	 char_to_write=*str;
	 
	 	     GLCD_GoTo((d*8),i);
			  d++;
			  str++;
			 GLCD_Write_font(char_to_write);
		}
	 }
}

