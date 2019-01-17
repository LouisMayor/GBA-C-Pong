// includes
#include <stdlib.h>
#include "include/macros.h"
#include "include/types.h"

// forward decl
void SetPosition( volatile obj_attributes* object, int x, int y);

int main(void) {

	REG_DISPLAY = 0x1000 | 0x0040;

	REG_VIDEOMODE = 0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	REG_BGMODE = 0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)
	
	while(1) {
		// REG_DISPLAY_VCOUNT - V-BLANK i.e. update AFTER screen has been fully drawn. V-DRAW i.e. draw
		while( REG_DISPLAY_VCOUNT >= 160 ); // V-BLANK - 0 -> 227
		while( REG_DISPLAY_VCOUNT < 160 ); // V-DRAW
	}

	return 0;
}

void SetPosition( volatile obj_attributes* object, int x, int y) {

}