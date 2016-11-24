#include "ResFontFT.h"
#include "res/Resources.h"
#include "Font.h"
#include "res/CreateResourceContext.h"
#include "core/NativeTexture.h"
#include "MemoryTexture.h"
#include "core/ImageDataOperations.h"
#include "core/VideoDriver.h"
#include "ft2build.h"

#include FT_FREETYPE_H

FT_Library  _library = 0;

#ifdef _MSC_VER
typedef unsigned __int8  uint8_t;
typedef unsigned __int32 uint32_t;
#else
#include <stdint.h>
#endif



#define ASCII_IN_TABLE 1

static const uint8_t utf8d[] = {

#if ASCII_IN_TABLE
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
#endif

	070,070,070,070,070,070,070,070,070,070,070,070,070,070,070,070,
	050,050,050,050,050,050,050,050,050,050,050,050,050,050,050,050,
	030,030,030,030,030,030,030,030,030,030,030,030,030,030,030,030,
	030,030,030,030,030,030,030,030,030,030,030,030,030,030,030,030,
	204,204,188,188,188,188,188,188,188,188,188,188,188,188,188,188,
	188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,
	174,158,158,158,158,158,158,158,158,158,158,158,158,142,126,126,
	111, 95, 95, 95, 79,207,207,207,207,207,207,207,207,207,207,207,

	0,1,1,1,8,7,6,4,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,
	1,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,4,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,8,7,6,4,5,4,3,2,1,1,1,1,

};

uint32_t decodeSymbol(int sym)
{
	int symArr[] = { sym, 0 };
	uint8_t* s = (uint8_t*)symArr;
	uint8_t data, byte, stat = 9;
	uint32_t unic = 0;

	while ((byte = *s++)) {

		// Each byte is associated with a character class and a mask;
		// The character class is used to advance a finite automaton;
		// The mask is used to strip off leading bits from the byte;
		// The remaining bits are combined into a Unicode code point;
		// A code point is complete if the DFA enters the final state.

#if ASCII_IN_TABLE
		data = utf8d[byte];
		stat = utf8d[256 + (stat << 4) + (data >> 4)];
		byte = (byte ^ (uint8_t)(data << 4));
#else
		if (byte < 0x80) {
			stat = utf8d[128 + (stat << 4)];
		}
		else {
			data = utf8d[byte - 0x80];
			stat = utf8d[128 + (stat << 4) + (data >> 4)];
			byte = (byte ^ (uint8_t)(data << 4));
		}
#endif

		unic = (unic << 6) | byte;

		if (!stat) {
			// unic is now a proper code point, we just print it out.
			//printf("U+%04X\n", unic);
			return unic;
		}

		if (stat == 1) {
			// the byte is not allowed here; the state would have to
			// be reset to continue meaningful reading of the string
		}

	}
	return 0;
}


namespace oxygine
{
	class FontFT : public Font
	{
	public:
		
		FontFT(ResFontFT *rs, int size) :_rs(rs), _size(size)
		{
			init("abc", size, size, size);
#if !defined(_MSC_VER) ||  (_MSC_VER >= 1900)
			_glyphs.reserve(100);
#endif
		}

	protected:
		ResFontFT *_rs;
		int _size;
		bool loadGlyph(int code, glyph& g) OVERRIDE
		{
			FT_Face face = _rs->_face;
			FT_Set_Pixel_Sizes(_rs->_face, 0, _size);


			/* load glyph image into the slot (erase previous one) */
			int sm = decodeSymbol(code);
			int error = FT_Load_Char(face, sm, FT_LOAD_RENDER);
			if (error)
				return false;

			FT_GlyphSlot  slot = face->glyph;

			

			FT_Bitmap bitmap = slot->bitmap;

			ImageData src(bitmap.width, bitmap.rows, bitmap.pitch, TF_A8, bitmap.buffer);


			Rect srcRect;
			spTexture t;

			static MemoryTexture mt;
			if (src.w && src.h)
			{
				mt.init(src.w, src.h, TF_R8G8B8A8);

				ImageData dest = mt.lock();
				operations::blitPremultiply(src, dest);
				//PixelA8

				_rs->_atlas.add(dest, srcRect, t);

				OX_ASSERT(t);


				g.src = srcRect.cast<RectF>();
				Vector2 sz((float)t->getWidth(), (float)t->getHeight());
				g.src.pos = g.src.pos.div(sz);
				g.src.size = g.src.size.div(sz);
				g.texture = safeSpCast<NativeTexture>(t);
			}			

			g.advance_x = static_cast<short>(slot->advance.x >> 6);
			g.advance_y = static_cast<short>(slot->advance.y >> 6);
			g.offset_x = slot->bitmap_left;
			g.offset_y = - slot->bitmap_top;
			g.sh = src.h;
			g.sw = src.w;			
			g.ch = code;

			return true;
		}
	};


	Resource* ResFontFT::createResource(CreateResourceContext& context)
	{
		ResFontFT *res = new ResFontFT;


		pugi::xml_node node = context.walker.getNode();
		setNode(res, node);
		std::string file = context.walker.getPath("file");
		res->setName(Resource::extractID(node, file, ""));
		res->init(file);
		context.resources->add(res);
		return res;
	}

	void ResFontFT::initLibrary()
	{
		Resources::registerResourceType(&ResFontFT::createResource, "ftfont");

		FT_Init_FreeType(&_library);
	}

	void ResFontFT::freeLibrary()
	{
		FT_Init_FreeType(&_library);
	}

	ResFontFT::ResFontFT() :_atlas(CLOSURE(this, &ResFontFT::createTexture)), _face(0)
	{
		_atlas.init();
	}

	ResFontFT::~ResFontFT()
	{

	}

	spTexture ResFontFT::createTexture(int w, int h)
	{
		MemoryTexture mt;
		mt.init(512, 512, TF_R8G8B8A8);
		mt.fill_zero();

		spNativeTexture texture = IVideoDriver::instance->createTexture();
		texture->init(mt.lock());
		
		return texture;
	}

	void ResFontFT::init(const std::string &fnt)
	{
		file::read(fnt.c_str(), _fdata);

		int error = FT_New_Memory_Face(_library,
			reinterpret_cast<const unsigned char*>(_fdata.getData()), _fdata.getSize(), 0, &_face);
        OX_ASSERT(!error);
		//_fonts.push_back(FontFT(this, 32));
	}

	Font* ResFontFT::getFont(int size)
	{
		for (fonts::iterator i = _fonts.begin(); i != _fonts.end(); ++i)
		{
			FontFT &f = *i;
			if (f.getSize() == size)
				return &f;
		}

		_fonts.push_back(FontFT(this, size));

		return &_fonts.back();
	}

	const Font* ResFontFT::getFont(const char* name, int size) const
	{
		OX_ASSERT(size > 0);
		ResFontFT *r = const_cast<ResFontFT*>(this);
		return r->getFont(size);
	}

	void ResFontFT::_load(LoadResourcesContext* context)
	{

	}

	void ResFontFT::_unload()
	{

	}
}