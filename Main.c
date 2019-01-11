// includes
#include <stdlib.h>

// macros
#define HEIGHT 160
#define WIDTH 240

#define HALF_HEIGHT 80
#define HALF_WIDTH 120

#define RED 0x001F
#define GREEN 0x03E0
#define BLUE 0x7C00
#define WHITE 0xFFFF

#define ALLOCATE(_add, _ty)\
		_add = malloc(sizeof(_ty))

#define DEALLOCATE(_add)\
		free((void*)_add)

// types
typedef unsigned char uint8;
typedef unsigned short uint16;

void LoadHelloWorldRBGScene( volatile uint16* _vram ) {
	// y * max x + x = colour
	_vram[HALF_HEIGHT * WIDTH + HALF_WIDTH - 5]   = RED;
	_vram[HALF_HEIGHT * WIDTH + HALF_WIDTH]       = GREEN;
	_vram[HALF_HEIGHT * WIDTH + HALF_WIDTH + 5]   = BLUE;
}

int main(void) {
	// grab registers... note: keyword volatile, stops compiler optimising reads/writes away
	volatile uint8* ioram = (uint8*)0x04000000;
	// contingous locations
	ioram[0] = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	ioram[1] = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	// writing to VRAM (Note: 16bits colour space)
	volatile uint16* vram = (uint16*)0x06000000;

	LoadHelloWorldRBGScene( vram );

	// Wait forever
	while(1);

	return 0;
}