#pragma once
#include "oxygine-framework.h"
#include "MapDao.h"
#include "CharacterDao.h"

using namespace oxygine;

namespace res {
	extern Resources resources;
	void load();
	void free();
	static unique_ptr<MapDao> mapDao(new MapDao);
	static unique_ptr<CharacterDao> characterDao(new CharacterDao);
}