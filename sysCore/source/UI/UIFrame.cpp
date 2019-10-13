#include <UI/UIFrame.h>

UIFrame::UIFrame() : Node("UIFrame") {}

void UIFrame::calcClientFromFrame(RectArea& client)
{
    client.x1 = 0;
    client.y1 = 0;
    client.x2 = this->m_frame.width() - (-this->m_zero.x1 + this->m_zero.x2);
    client.y2 = this->m_frame.height() - (-this->m_zero.y1 + this->m_zero.y2);
}

void UIFrame::calcFrameFromClient(RectArea& frame)
{
    frame.x1 += this->m_zero.x1;
    frame.y1 += this->m_zero.y1;
    frame.x2 = (frame.x1 + this->m_client.x2) + (-this->m_zero.x1 + this->m_zero.x2);
    frame.y2 = (frame.y1 + this->m_client.y2) + (-this->m_zero.y1 + this->m_zero.y2);
}

void UIFrame::setClient(RectArea& client)
{
    this->m_client = client;
    calcFrameFromClient(this->m_frame);
}

void UIFrame::setFrame(RectArea& frame)
{
    this->m_frame = frame;
    calcClientFromFrame(this->m_client);
}
