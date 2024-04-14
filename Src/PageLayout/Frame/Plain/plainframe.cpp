#include "plainframe.h"

PlainFrame::PlainFrame()
{
    setType("Plain Frame");
    setDescription("A simple frame only consisting of a line, the indent from the \"where\" "
                   "rectangle/page border");
}

void PlainFrame::draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat)
{
    qDebug() << "ABA";
    setDrawingArea(QRectF{ where.topLeft() + QPointF{ m_indentLeft, m_indentTop },
                           where.bottomRight() - QPointF{ m_indentRigth, m_indentBottom } });
    qDebug() << "ABB";
    into->drawRect(drawingArea(), m_lineWidth, 0);
    qDebug() << "ABC";
    qDebug() << "On What: " << onWhat;
}

double PlainFrame::indentLeft() const
{
    return m_indentLeft;
}

void PlainFrame::setIndentLeft(double newIndentLeft)
{
    m_indentLeft = newIndentLeft;
}

double PlainFrame::indentRigth() const
{
    return m_indentRigth;
}

void PlainFrame::setIndentRigth(double newIndentRigth)
{
    m_indentRigth = newIndentRigth;
}

double PlainFrame::indentTop() const
{
    return m_indentTop;
}

void PlainFrame::setIndentTop(double newIndentTop)
{
    m_indentTop = newIndentTop;
}

double PlainFrame::indentBottom() const
{
    return m_indentBottom;
}

void PlainFrame::setIndentBottom(double newIndentBottom)
{
    m_indentBottom = newIndentBottom;
}

double PlainFrame::lineWidth() const
{
    return m_lineWidth;
}

void PlainFrame::setLineWidth(double newLineWidth)
{
    m_lineWidth = newLineWidth;
}
