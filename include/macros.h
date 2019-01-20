/* SOF - MACROS */

// http://cdn.preterhuman.net/texts/gaming_and_diversion/Gameboy%20Advance%20Programming%20Manual%20v1.1.pdf

#ifndef MACROS_HEADER
#define MACROS_HEADER

#include "types.h"

// Data

// GBA data

// HWD addresses
#define EXE_ONLY_ROM	0x00000000
#define EWRAM			0x02000000
#define IWRAM			0x03000000
#define IO				0x04000000
#define COL_PAL			0x05000000
#define VRAM			0x06000000
#define OAM				0x07000000
#define PAK_ROM			0x08000000
#define PAK_RAM			0x0E000000

// Registers				(*(type)ptr)
#define REG_DISPLAY			(*((volatile uint32*)(IO)))
#define REG_DISPLAY_VCOUNT	(*((volatile uint32*)(IO + 0x0006)))
#define REG_VIDEOMODE		(*((volatile uint32*)(IO + 0x0004)))
#define REG_BGMODE			(*((volatile uint32*)(IO + 0x0008)))
#define REG_VRAM			(*((volatile uint16*)(VRAM)))
#define REG_INPUT			(*((volatile uint16*)(IO + 0x0130)))

// Viewport
#define HEIGHT		160
#define WIDTH 		240
#define HALF_HEIGHT	80
#define HALF_WIDTH	120

// Colours
#define RED		0x001F
#define GREEN	0x03E0
#define BLUE	0x7C00
#define WHITE	0xFFFF
#define BLACK	0x0000

// Input
#define KEY_A		0x0001
#define KEY_B		0x0002
#define KEY_SELECT	0x0004
#define KEY_START	0x0008
#define KEY_RIGHT	0x0010
#define KEY_LEFT	0x0020
#define KEY_UP		0x0040
#define KEY_DOWN	0x0080
#define KEY_R		0x0100
#define KEY_L		0x0200
#define KEY_ANY		0x03FF

/* 	OAM masks (includes more than described)
	attribute 0: y pos, obj shape, colour mode of tiles
	attribute 1: x pos, obj size
	attribute 2: obj base tile index, colour palette
*/
#define OBJ_MASK_ATTR0_Y	0x0FF
#define OBJ_MASK_ATTR1_X	0x1FF

#define OAM_ATTR_LAYOUT		((volatile obj_attributes*)OAM)
#define TILE_LAYOUT			((volatile tile_block*)VRAM)
#define OBJ_PALETTE_LAYOUT	((volatile rgb15*)(COL_PAL + 0x200))

// Functions

#define ALLOCATE(_add,	_ty)\
		_add = malloc(sizeof(_ty))

#define DEALLOCATE(_add)\
		free((void*)_add)

#endif

/* EOF - MACROS */