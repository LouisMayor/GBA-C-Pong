// includes
#include <stdlib.h>
#include "include/macros.h"
#include "include/types.h"

void LoadHelloWorldRBGScene( volatile uint16* _vram ) {
	// y * max x + x = colour
	_vram[HALF_HEIGHT * WIDTH + HALF_WIDTH - 5]	= RED;
	_vram[HALF_HEIGHT * WIDTH + HALF_WIDTH]		= GREEN;
	_vram[HALF_HEIGHT * WIDTH + HALF_WIDTH + 5]	= BLUE;
}

int main(void) {
	
	REG_DISPLAY = 0x1000 | 0x0040;

	REG_VIDEOMODE = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	REG_BGMODE = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

	LoadHelloWorldRBGScene( &REG_VRAM );

	// Wait forever
	while(1);

	return 0;
}