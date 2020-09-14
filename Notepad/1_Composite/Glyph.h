//Glyph.h

#ifndef _GLYPH_H
#define _GLYPH_H
#include<string>
using namespace std;

typedef signed long int Long;
template <typename T> class Iterator; // !!!!!!!!!! 아래에 쓸려면 먼저 선언해야되니까  주소 전방선언
class Glyph{
public:
	Glyph();
	virtual ~Glyph() = 0;
	virtual Iterator<Glyph*>* CreateIterator() { return  0; }; //이거 안해주면 doublebytecharacter할떄도 다 createIterator다 해줘야한다.
	virtual Long Add(Glyph* glyph) { return -1; }; //이건 composite에서 똑같은 메소드인데 여기서 일단 정의를 다 할수없으니까 이렇게한거
	virtual Long Put(Long index, Glyph* glyph ) { return -1; };
	virtual Long Change(Long index,Glyph* glyph) { return -1; };
	virtual Glyph* GetAt(Long index) { return 0; }; //위와 동일
	virtual string GetContents() = 0; //여기서 정의할수없으니까 그냥 선언만 해놓은것.
	virtual Glyph* Clone() = 0; //위와 동일
	virtual Long Remove(Long Index) { return 0; };
	virtual Long First() { return 0; };
	virtual Long Last() { return 0; };
	virtual Long Previous() { return 0; };
	virtual Long Next() { return 0; };
	virtual Long GetLength() const { return 0; };
	virtual Long GetCurrent() const { return 0; };
	

	

	};
#endif // _GLYPH_H

