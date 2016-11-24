#pragma once
#include "res/ResFont.h"
#include "utils/AtlasTool.h"
#include "core/file.h"
#include <list>

extern "C"
{
	typedef struct FT_FaceRec_*  FT_Face;
}

namespace oxygine
{
	class CreateResourceContext;
	class FontFT;

	class ResFontFT : public ResFont
	{
	public:
		static void initLibrary();
		static void freeLibrary();

		ResFontFT();
		~ResFontFT();

		void init(const std::string &fnt);

		const Font* getFont(const char* name, int size) const OVERRIDE;

	protected:
		friend class FontFT;

		static Resource* createResource(CreateResourceContext& context);
		void _load(LoadResourcesContext* context) OVERRIDE;
		void _unload() OVERRIDE;

		Font* getFont(int size);

		MultiAtlas _atlas;
		spTexture createTexture(int w, int h);

		FT_Face _face;

		typedef std::list<FontFT> fonts;
		fonts _fonts;
		file::buffer _fdata;
	};
}