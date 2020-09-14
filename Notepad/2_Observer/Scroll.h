//Scroll.h
#ifndef _SCROLL_H
#define _SCROLL_H

class NotePadForm;
typedef signed long int Long;
class Scroll {
public:
	Scroll(NotePadForm* notePadForm = 0);
	~Scroll();
	void SetScrollWidth(Long scrollWidth);
	void SetScrollHeight(Long scrollHeight);
	Long GetScrollWidth() const;
	Long GetScrollHeight() const;
private:
	NotePadForm* notePadForm;
	Long scrollWidth;
	Long scrollHeight;
};

inline Long Scroll::GetScrollWidth() const {
	return this->scrollWidth;
}
inline Long Scroll::GetScrollHeight() const {
	return this->scrollHeight;
}
#endif // !_SCROLL_H
