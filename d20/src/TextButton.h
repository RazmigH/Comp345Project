#pragma once

#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(TextButton, spTextButton);
class TextButton : public Sprite {
public:
	TextButton(std::string);
	~TextButton();
};