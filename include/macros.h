/* SOF - MACROS */

#include "types.h"

// Data

// GBA data

// HWD addresses
#define EXE_ONLY_ROM 	0x00000000
#define EWRAM 			0x02000000
#define IWRAM 			0x03000000
#define IO 				0x04000000
#define COL_PAL 		0x05000000
#define VRAM 			0x06000000
#define OAM 			0x07000000
#define PAK_ROM 		0x08000000
#define PAK_RAM 		0x0E000000

// Registers
#define REG_DISPLAY		(*((volatile uint32*)(IO)))
#define REG_VIDEOMODE	(*((volatile uint32*)(IO + 0x0004)))
#define REG_BGMODE		(*((volatile uint32*)(IO + 0x0008)))
#define REG_VRAM		(*((volatile uint16*)(VRAM)))

// Viewport
#define HEIGHT 		160
#define WIDTH 		240
#define HALF_HEIGHT 80
#define HALF_WIDTH 	120

// Colours
#define RED 	0x001F
#define GREEN 	0x03E0
#define BLUE 	0x7C00
#define WHITE 	0xFFFF
#define BLACK 	0x0000

// Functions

#define ALLOCATE(_add, _ty)\
		_add = malloc(sizeof(_ty))

#define DEALLOCATE(_add)\
		free((void*)_add)

/* EOF - MACROS */