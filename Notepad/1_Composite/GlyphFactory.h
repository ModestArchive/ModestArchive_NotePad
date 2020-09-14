//GlyphFactory.h
#ifndef _GLYPHFACTORY_H
#define _GLYPHFACTORY_H
#include"Glyph.h"

class GlyphFactory {
public:
	GlyphFactory();
	GlyphFactory(char(*contents));
	~GlyphFactory();

	//메소드
	Glyph* MakeGlyph(char(*contents));
	//인라인함수
	char* GetContents() const;

private:
	char contents[2];
	
};

inline char* GlyphFactory::GetContents() const {
	return const_cast<char*>(this->contents);
}
#endif//_GLYPHFACTORY_H