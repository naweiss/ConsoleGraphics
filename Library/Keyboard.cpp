#include "Keyboard.h"
#include <Windows.h>

static const unsigned int NumberOfKeys = 256U;
static bool previousKeyboardState[NumberOfKeys];
//Works fine.
bool isKeyDown(int key)
{
    return (GetAsyncKeyState(key) & (1 << 16));
}

int keysDown(){
	//Get the current state of each key as the application starts to ensure that keys held down beforehand are not processed as pressed keys.
	for (unsigned int keyNum = 0U; keyNum < NumberOfKeys; ++keyNum)
	{
		bool previousState = previousKeyboardState[keyNum];
		previousKeyboardState[keyNum] = isKeyDown(keyNum);
		if (previousKeyboardState[keyNum] && !previousState){
			return keyNum;
		}
	}
	return -1;
}