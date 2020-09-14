//GlyphFactory.cpp

#include"GlyphFactory.h"
#include"Glyph.h"
#include"Row.h"
#include"NotePad.h"
#include"SingleByteCharacter.h"
#include"DoubleByteCharacter.h"


GlyphFactory::GlyphFactory() {
	this->contents[0] = ' ';
	this->contents[1] = ' ';
}

GlyphFactory::~GlyphFactory() {

}

Glyph* GlyphFactory::MakeGlyph(char(*contents)) {
	
	Glyph* glyph=0;

		if (contents[0] == '\0') {//�׳� ""�ϸ� �ȵ��� ���ڹ迭�� �Է¹޴µ� �ƹ��͵� ������ ��ǥ�÷� �ؾ���
		glyph = new NotePad;
		}

		else if(contents[0] == '\r' && contents[1] == '\n') {
		glyph = new Row;
		}

		else if (!(contents[0] & 0x80 )) {//����ִµ����Ϳ� �ƽ�Ű�ڵ�� ���Ҷ� �̷� ǥ���� ����!
		glyph = new SingleByteCharacter(contents[0]);//����������ؾ��� �� ����Ʈ�� �ϳ�
		}
		
		else if (contents[0] & 0x80){//����ִµ����Ϳ� �ƽ�Ű�ڵ�� ���Ҷ� �̷� ǥ���� ����!
		glyph = new DoubleByteCharacter(contents);////����������ؾ��� �� ����Ʈ�� �ϳ�
		}
		
		return glyph;

}