// includes
#include <stdlib.h>
#include "include/macros.h"
#include "include/types.h"
#include "include/utility.h"

// forward decl
void SetPosition( volatile obj_attributes* object, int x, int y);

int main(void) {
	
	// Writing sprites in VRAM. Paddle and ball
	volatile uint16* paddleTile = (uint16*)TILE_LAYOUT[4][1];
	volatile uint16* ballTile = (uint16*)TILE_LAYOUT[4][5];

	// writing 4 pixels of colour into index 1
	for( int i = 0; i < 4 * (sizeof(tile_4bpp) * 0.5); ++i ) {
		paddleTile[i] = 0x1111;
	}

	// writing 4 pixels of colour into index 2
	for( int i = 0; i < sizeof(tile_4bpp) * 0.5; ++i ) {
		ballTile[i] = 0x2222;
	}

	// writing the colour palette for each sprite (into the first palette, i.e. 16 colours)
	OBJ_PALETTE_LAYOUT[1] = RGB15(0x1F, 0x1F, 0x1F);
	OBJ_PALETTE_LAYOUT[2] = RGB15(0x1F, 0x00, 0x1F);

	// pass sprite data into object attribute memory
	volatile obj_attributes* paddleAttributes = &OAM_ATTR_LAYOUT[0];
	paddleAttributes->attr0 = 0x8000;
	paddleAttributes->attr1 = 0x4000;
	paddleAttributes->attr2 = 1;

	volatile obj_attributes* ballAttributes = &OAM_ATTR_LAYOUT[1];
	ballAttributes->attr0 = 0;
	ballAttributes->attr1 = 0;
	ballAttributes->attr2 = 5;

	const int paddleWidth = 8;
	const int paddleHeight = 32;

	const int ballWidth = 8;
	const int ballHeight = 8;

	int paddleVelocity = 2;
	int ballVelocityX = 2;
	int ballVelocityY = 1;

	int paddleX = 5;
	int paddleY = 96;

	int ballX = 22;
	int ballY = 96;

	const int paddleMaxY = HEIGHT - paddleHeight;

	SetPosition(paddleAttributes, paddleX, paddleY);
	SetPosition(ballAttributes, ballX, ballY);

	REG_DISPLAY = 0x1000 | 0x0040;
	
	uint32 keyState = 0;
	while(1) {
		// REG_DISPLAY_VCOUNT - V-BLANK i.e. update AFTER screen has been fully drawn. V-DRAW i.e. draw
		//  0 -> 227
		while( REG_DISPLAY_VCOUNT >= 160 ); // V-BLANK
		while( REG_DISPLAY_VCOUNT < 160 ); // V-DRAW

		// grab current key state
		keyState = ~REG_INPUT & KEY_ANY;

		if ( keyState & KEY_UP || keyState & KEY_DOWN ) {
			if( keyState & KEY_UP ) {
				paddleY = ClampInt( paddleY - paddleVelocity, 0, paddleMaxY );
			}			
			else if( keyState & KEY_DOWN ) {
				paddleY = ClampInt( paddleY + paddleVelocity, 0, paddleMaxY );
			}
			SetPosition(paddleAttributes, paddleX, paddleY);
		}

		SetPosition(ballAttributes, ballX, ballY);
	}
	return 0;
}

void SetPosition( volatile obj_attributes* object, int x, int y) {
	object->attr0 = (object->attr0 & ~OBJ_MASK_ATTR0_Y) | (y & OBJ_MASK_ATTR0_Y);
	object->attr1 = (object->attr1 & ~OBJ_MASK_ATTR1_X) | (x & OBJ_MASK_ATTR1_X);
}