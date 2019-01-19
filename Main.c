// includes
#include <stdlib.h>
#include "include/macros.h"
#include "include/types.h"
#include "include/utility.h"
#include "include/pong-types.h"

volatile uint16* paddleTile;
volatile uint16* ballTile;

volatile obj_attributes* paddleAttributes;
volatile obj_attributes* ballAttributes;

paddle playerPaddle;
ball pongBall;

int paddleMaxY;
uint32 keyState;

void SetPosition( volatile obj_attributes* object, int x, int y) {
	object->attr0 = (object->attr0 & ~OBJ_MASK_ATTR0_Y) | (y & OBJ_MASK_ATTR0_Y);
	object->attr1 = (object->attr1 & ~OBJ_MASK_ATTR1_X) | (x & OBJ_MASK_ATTR1_X);
}

void Setup(void) {
// Writing sprites in VRAM. Paddle and ball
	paddleTile	 = (uint16*)TILE_LAYOUT[4][1];
	ballTile	 = (uint16*)TILE_LAYOUT[4][5];

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
	paddleAttributes = &OAM_ATTR_LAYOUT[0];
	paddleAttributes->attr0 = 0x8000;
	paddleAttributes->attr1 = 0x4000;
	paddleAttributes->attr2 = 1;

	ballAttributes = &OAM_ATTR_LAYOUT[1];
	ballAttributes->attr0 = 0;
	ballAttributes->attr1 = 0;
	ballAttributes->attr2 = 5;

	playerPaddle.velocity	 = 2;
	playerPaddle.positionX	 = 5;
	playerPaddle.positionY	 = 96;
	playerPaddle.dimensionX	 = 8;
	playerPaddle.dimensionY	 = 32;

	pongBall.velocityX	 = 2;
	pongBall.velocityY	 = 1;
	pongBall.positionX	 = 22;
	pongBall.positionY	 = 96;
	pongBall.dimensionX	 = 8;
	pongBall.dimensionY	 = 8;

	paddleMaxY = HEIGHT - playerPaddle.dimensionY;

	SetPosition(paddleAttributes, playerPaddle.positionX, playerPaddle.positionY);
	SetPosition(ballAttributes, pongBall.positionX, pongBall.positionY);

	REG_DISPLAY = 0x1000 | 0x0040;

	keyState = 0;
}

void GameLoop(void) {
		// REG_DISPLAY_VCOUNT - V-BLANK i.e. update AFTER screen has been fully drawn. V-DRAW i.e. draw
		//  0 -> 227
		while( REG_DISPLAY_VCOUNT >= 160 ); // V-BLANK
		while( REG_DISPLAY_VCOUNT < 160 ); // V-DRAW

		// grab current key state
		keyState = ~REG_INPUT & KEY_ANY;

		if ( keyState & KEY_UP || keyState & KEY_DOWN ) {
			if( keyState & KEY_UP ) {
				playerPaddle.positionY = ClampInt( playerPaddle.positionY - playerPaddle.velocity, 0, paddleMaxY );
			}			
			else if( keyState & KEY_DOWN ) {
				playerPaddle.positionY = ClampInt( playerPaddle.positionY + playerPaddle.velocity, 0, paddleMaxY );
			}
			SetPosition(paddleAttributes, playerPaddle.positionX, playerPaddle.positionY);
		}

		SetPosition(ballAttributes, pongBall.positionX, pongBall.positionY);
}

int main(void) {
	Setup();
	while(1) {
		GameLoop();
	}
	return 0;
}