#include "foldinglines.h"

FoldingLines::FoldingLines() { }

void FoldingLines::draw(std::shared_ptr<UniversalDraw> into, QPageLayout onWhat)
{
    qInfo() << "FoldingLines None, Into: " << into.get();
    qInfo() << "FoldingLines None, On What: " << onWhat;
}

double FoldingLines::depth() const
{
    return m_depth;
}

void FoldingLines::setDepth(double newDepth)
{
    m_depth = newDepth;
}

void FoldingLines::drawVerFoldLine(std::shared_ptr<UniversalDraw> into, QPageLayout onWhat,
                                   double x, double depth, double width)
{
    into->drawLine(QPointF{ x, 0 }, QPointF{ x, depth }, width);
    into->drawLine(QPointF{ x, onWhat.fullRect(QPageLayout::Millimeter).height() },
                   QPointF{ x, onWhat.fullRect(QPageLayout::Millimeter).height() - depth }, width);
}

void FoldingLines::drawHorFoldLine(std::shared_ptr<UniversalDraw> into, QPageLayout onWhat,
                                   double y, double depth, double width)
{
    into->drawLine(QPointF{ 0, y }, QPointF{ depth, y }, width);
    into->drawLine(QPointF{ onWhat.fullRect(QPageLayout::Millimeter).width(), y },
                   QPointF{ onWhat.fullRect(QPageLayout::Millimeter).width() - depth, y }, width);
}

QPageLayout FoldingLines::toWhat() const
{
    return m_toWhat;
}

void FoldingLines::setToWhat(const QPageLayout &newToWhat)
{
    m_toWhat = newToWhat;
}

QString FoldingLines::description() const
{
    return m_description;
}

void FoldingLines::setDescription(const QString &newDescription)
{
    m_description = newDescription;
}

QString FoldingLines::type() const
{
    return m_type;
}

void FoldingLines::setType(const QString &newType)
{
    m_type = newType;
}
