#include "Space_Invaders_3DApp.h"

int main() {
	
	auto app = new Space_Invaders_3DApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}