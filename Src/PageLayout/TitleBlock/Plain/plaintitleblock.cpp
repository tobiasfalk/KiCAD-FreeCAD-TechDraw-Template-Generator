#include "plaintitleblock.h"

PlainTitleBlock::PlainTitleBlock()
{
    setType("Plain TitleBlock");
    setTitleBlockArea(QRectF{ 0, 0, m_width, m_height });
}

void PlainTitleBlock::draw(const std::shared_ptr<UniversalDraw> &into, const QRectF &where, const QPageLayout &onWhat)
{
    // Anchor plain rectangle in bottom-right with current width/height.
    setTitleBlockArea(
            QRectF{ where.bottomRight() - QPointF{ m_width, m_height }, where.bottomRight() });
    into->drawRect(titleBlockArea(), 1);
}

double PlainTitleBlock::height() const
{
    return m_height;
}

void PlainTitleBlock::setHeight(double newHeight)
{
    m_height = newHeight;
    setTitleBlockArea(QRectF{ 0, 0, m_width, m_height });
}

double PlainTitleBlock::width() const
{
    return m_width;
}

void PlainTitleBlock::setWidth(double newWidth)
{
    m_width = newWidth;
}
