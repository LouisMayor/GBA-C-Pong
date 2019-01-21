#include "include/App.h"

int main(void) {
	App app;
	Setup(&app, &app.pong, &app.keyState);
	while(1) {
		if (!Update(&app.pong, &app.keyState, &app.pause)){
			break;
		}
		Draw(&app.pong);
	}
	Clean();
	return 0;
}