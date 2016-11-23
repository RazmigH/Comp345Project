#pragma once
#include "oxygine-framework.h"
#include "MapDao.h"

using namespace oxygine;

namespace res {
	extern Resources resources;
	void load();
	void free();
	static unique_ptr<MapDao> mapDao(new MapDao);
}