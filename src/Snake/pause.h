#pragma once
#include <stdbool.h>
#include "button.h"
#include "globals.h"
#include "snake.h"

bool Snake_Pause(bool isPaused);
void Snake_PauseMenu_Init();
void Snake_PauseMenu_Update();
void Snake_Pause_Continue();