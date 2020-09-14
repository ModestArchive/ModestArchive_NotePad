//GlyphFactory.h
#ifndef _GLYPHFACTORY_H
#define _GLYPHFACTORY_H
#include"Glyph.h"

class GlyphFactory {
public:
	GlyphFactory();
	GlyphFactory(char(*contents));
	~GlyphFactory();

	//�޼ҵ�
	Glyph* MakeGlyph(char(*contents));
	//�ζ����Լ�
	char* GetContents() const;

private:
	char contents[2];
	
};

inline char* GlyphFactory::GetContents() const {
	return const_cast<char*>(this->contents);
}
#endif//_GLYPHFACTORY_H