#include "PushButton.h"

PushButton::PushButton(const std::string& text, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_text(text)
{
	memset(&m_msg, 0, sizeof(ExMessage));
}

void PushButton::show()
{
	m_visible = true;
	if (!m_visible) return;

	setfillcolor(cur_c);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	settextcolor(RED);
	//把文字居中显示在按钮中间
	int tx = m_x + (m_w - textwidth(m_text.c_str())) / 2;
	int ty = m_y + (m_h - textheight(m_text.c_str())) / 2;
	::outtextxy(tx, ty, m_text.c_str());
}

bool PushButton::isin()
{
	if (!m_visible) return false;
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h)
	{
		return true;
	}
	return false;
}

bool PushButton::isClicked()
{
	if (!m_visible) return false;
	if (isin())
	{
		if (m_msg.message == WM_LBUTTONDOWN)
		{
			return true;
		}
	}
	return false;
}

void PushButton::hide()
{
	m_visible = false;
}

void PushButton::eventLoop(const ExMessage& msg)
{
	if (!m_visible) return;
	m_msg = msg;
	//如果鼠标没有放在按键上
	if (!isin())
	{
		cur_c = normal_c;
	}
	else
	{
		cur_c = hover_c;
	}
}

void PushButton::setBackgroundColor(COLORREF c)
{
	normal_c = c;
}

void PushButton::setHoverColor(COLORREF c)
{
	hover_c = c;
}
