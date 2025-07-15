#pragma once
#include"BasicWidget.h"
#include"configure.h"
#include<string>
class LineEdit : 
	public BasicWidget
{
public:
	void eventLoop(const ExMessage& msg);
	LineEdit(int x = 0, int y = 0, int w = 150, int h = 30);
	void show()override;
	inline void setTitle(const std::string& title) { m_title = title; }
	inline const std::string& text()const { return m_text; }
	std::string text1();
	void clear();
	void setText(const std::string& text);

private:
	std::string m_text;
	std::string m_title;
	bool m_isPopUp;

};

