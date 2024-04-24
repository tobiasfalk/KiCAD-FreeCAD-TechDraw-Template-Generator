#include "plaintitleblock.h"

PlainTitleBlock::PlainTitleBlock()
{
    setType("Plain TitleBlock");
    setTitleBlockArea(QRectF{ 0, 0, m_width, m_height });
}

void PlainTitleBlock::draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat)
{
    setTitleBlockArea(
            QRectF{ where.bottomRight() - QPointF{ m_width, m_height }, where.bottomRight() });
    into->drawRect(titleBlockArea(), 1);
    qDebug() << "TitleBlock, into: " << into.get();
    qDebug() << "On What: " << onWhat;
}

double PlainTitleBlock::height() const
{
    return m_height;
}

void PlainTitleBlock::setHeight(double newHeight)
{
    setTitleBlockArea(QRectF{ 0, 0, m_width, m_height });
    m_height = newHeight;
}

double PlainTitleBlock::width() const
{
    return m_width;
}

void PlainTitleBlock::setWidth(double newWidth)
{
    m_width = newWidth;
}
