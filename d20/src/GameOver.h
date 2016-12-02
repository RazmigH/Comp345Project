#pragma once
#include "Layout.h"
#include "TextButton.h"

DECLARE_SMART(GameOver, spGameOver);
class GameOver : public Layout {
public:
	GameOver();
	~GameOver();

	void update();
private:
	spTextField gameOver;
	spTextButton okbtn;
};