// includes
#include <stdlib.h>
#include <stdbool.h>
#include "macros.h"
#include "types.h"
#include "utility.h"
#include "pong-types.h"

typedef struct Pong {
	volatile uint16* paddleTile;
	volatile uint16* ballTile;

	volatile obj_attributes* paddleAttributes;
	volatile obj_attributes* ballAttributes;

	paddle playerPaddle;
	ball pongBall;

	int paddleMaxY;
} Pong;

void SetPosition( volatile obj_attributes* object, int x, int y) {
	object->attr0 = (object->attr0 & ~OBJ_MASK_ATTR0_Y) | (y & OBJ_MASK_ATTR0_Y);
	object->attr1 = (object->attr1 & ~OBJ_MASK_ATTR1_X) | (x & OBJ_MASK_ATTR1_X);
}

typedef struct App {
	Pong pong;
	uint32 keyState;
	bool pause;
} App;

void Setup(App* app, Pong* pong, uint32* keyState) {
	app->pause = false;

	// Writing sprites in VRAM. Paddle and ball
	pong->paddleTile	 = (uint16*)TILE_LAYOUT[4][1];
	pong->ballTile	 = (uint16*)TILE_LAYOUT[4][5];

	// writing 4 pixels of colour into index 1
	for( int i = 0; i < 4 * (sizeof(tile_4bpp) * 0.5); ++i ) {
		pong->paddleTile[i] = 0x1111;
	}

	// writing 4 pixels of colour into index 2
	for( int i = 0; i < sizeof(tile_4bpp) * 0.5; ++i ) {
		pong->ballTile[i] = 0x2222;
	}

	// writing the colour palette for each sprite (into the first palette, i.e. 16 colours)
	OBJ_PALETTE_LAYOUT[1] = RGB15(0x1F, 0x1F, 0x1F);
	OBJ_PALETTE_LAYOUT[2] = RGB15(0x1F, 0x00, 0x1F);

	// pass sprite data into object attribute memory
	pong->paddleAttributes = &OAM_ATTR_LAYOUT[0];
	pong->paddleAttributes->attr0 = 0x8000;
	pong->paddleAttributes->attr1 = 0x4000;
	pong->paddleAttributes->attr2 = 1;

	pong->ballAttributes = &OAM_ATTR_LAYOUT[1];
	pong->ballAttributes->attr0 = 0;
	pong->ballAttributes->attr1 = 0;
	pong->ballAttributes->attr2 = 5;

	pong->playerPaddle.velocity	 = 2;
	pong->playerPaddle.positionX	 = 5;
	pong->playerPaddle.positionY	 = 96;
	pong->playerPaddle.dimensionX	 = 8;
	pong->playerPaddle.dimensionY	 = 32;
	pong->playerPaddle.dirty = false;

	pong->pongBall.velocityX	 = 2;
	pong->pongBall.velocityY	 = 1;
	pong->pongBall.positionX	 = 22;
	pong->pongBall.positionY	 = 96;
	pong->pongBall.dimensionX	 = 8;
	pong->pongBall.dimensionY	 = 8;
	pong->pongBall.dirty = false;

	pong->paddleMaxY = HEIGHT - pong->playerPaddle.dimensionY;

	SetPosition(pong->paddleAttributes, pong->playerPaddle.positionX, pong->playerPaddle.positionY);
	SetPosition(pong->ballAttributes, pong->pongBall.positionX, pong->pongBall.positionY);

	REG_DISPLAY = 0x1000 | 0x0040;

	keyState = 0;
	}

bool Update(Pong* pong, uint32* keyState, bool* pause) {
	// REG_DISPLAY_VCOUNT - V-BLANK i.e. update AFTER screen has been fully drawn. V-DRAW i.e. draw
	//  0 -> 227
	while( REG_DISPLAY_VCOUNT >= 160 ); // V-BLANK
	while( REG_DISPLAY_VCOUNT < 160 ); // V-DRAW
	// grab current key state
	*keyState = ~REG_INPUT & KEY_ANY;
	if( !(*pause) ) {
		if ( *keyState & KEY_UP || *keyState & KEY_DOWN ) {
			if( *keyState & KEY_UP ) {
				pong->playerPaddle.positionY = ClampInt( pong->playerPaddle.positionY - pong->playerPaddle.velocity, 0, pong->paddleMaxY );
			}			
			else if( *keyState & KEY_DOWN ) {
				pong->playerPaddle.positionY = ClampInt( pong->playerPaddle.positionY + pong->playerPaddle.velocity, 0, pong->paddleMaxY );
			}
			pong->playerPaddle.dirty = true;
		}
	}
	if ( *keyState & KEY_START ) {
		(*pause) = !(*pause);
	}
}

void Draw(Pong* pong) {
	if( pong->playerPaddle.dirty ) {
		SetPosition(pong->paddleAttributes, pong->playerPaddle.positionX, pong->playerPaddle.positionY);
		pong->playerPaddle.dirty = false;
	}
	if( pong->pongBall.dirty ) {
		SetPosition(pong->ballAttributes, pong->pongBall.positionX, pong->pongBall.positionY);
		pong->pongBall.dirty = false;
	}
}

void Clean(void) {
	// All clean and tidy
}