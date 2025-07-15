#include "MsgBox.h"
#include <graphics.h>

MsgBox::MsgBox(int x, int y, int w, int h)
	: BasicWidget(x, y, w, h), m_okBtn("确认", x + w / 2 - 40, y + h - 60, 80, 40)
{
	m_visible = false;
}

void MsgBox::setMessage(const std::string& msg)
{
	m_message = msg;
	m_visible = true;
}

void MsgBox::show()
{
	if (!m_visible) return;

	// 背景框
	setfillcolor(RGB(240, 240, 240));
	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(24, 0, "楷体");

	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);
	::rectangle(m_x, m_y, m_x + m_w, m_y + m_h);

	// 文本居中绘制
	int tx = m_x + 20;
	int ty = m_y + 40;
	::outtextxy(tx, ty, m_message.c_str());

	m_okBtn.show();
}

void MsgBox::eventLoop(const ExMessage& msg)
{
	if (!m_visible) return;

	m_okBtn.eventLoop(msg);

	// 检查按钮是否被点击
	if (m_okBtn.isClicked() && Timer::startTimer(400, 0)) {
		hide();  // 如果点击了确认按钮，隐藏消息框
	}
}

bool MsgBox::isVisible() const
{
	return m_visible;
}

void MsgBox::hide()
{
	m_visible = false;
}
