#include "LineEdit.h"
#include"PushButton.h"


LineEdit::LineEdit(int x , int y , int w , int h )
	:BasicWidget(x,y,w,h)
{
}

void LineEdit::show()
{
	setfillcolor(RGB(232, 232, 236));
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	

	settextcolor(BLACK);
	settextstyle(24, 0, "����");
	//�����־�����ʾ�ڰ�ť�м�
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(m_x + 5, ty, m_text.c_str());

}
void LineEdit::eventLoop(const ExMessage& msg)
{
	//�ж��Ƿ���Ҫ������������
	if (msg.x > m_x && msg.x < m_x + m_w && msg.y > m_y && msg.y < m_y + m_h
		&& msg.message == WM_LBUTTONDOWN)
	{
		char buf[128];
		InputBox(buf, 128, m_title.data(), m_title.data());
		m_text = buf;
	}
}

void LineEdit::setText(const std::string& text)
{
	m_text = text;  // ���� m_text
	show();          // ˢ����ʾ
}

std::string LineEdit::text1()
{
	return m_text;
}

void LineEdit::clear()
{
	m_text.clear();
}
