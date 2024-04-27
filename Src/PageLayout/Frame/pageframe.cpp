#include "pageframe.h"

#include "UniversalDraw/universaldraw.h"

#include <QDebug>

PageFrame::PageFrame() { }

QString PageFrame::type() const
{
    return m_type;
}

void PageFrame::draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat)
{

    setDrawingArea(where);

    qInfo() << "PageFrame None, Into: " << into.get();
    qInfo() << "PageFrame None, On What: " << onWhat;
    qInfo() << "PageFrame None, Where: " << where;

    // into.drawRect(QPointF{ 0, 0 }, QPointF{0, 0}, 1);
    // into.fileName();
}

void PageFrame::setType(const QString &newType)
{
    m_type = newType;
}

QString PageFrame::description() const
{
    return m_description;
}

void PageFrame::setDescription(const QString &newDescription)
{
    m_description = newDescription;
}

QRectF PageFrame::drawingArea() const
{
    return m_drawingArea;
}

void PageFrame::setDrawingArea(const QRectF &newDrawingArea)
{
    m_drawingArea = newDrawingArea;
}

bool PageFrame::noDrawingAreaIndent() const
{
    return m_noDrawingAreaIndent;
}

void PageFrame::setNoDrawingAreaIndent(bool newNoDrawingAreaIndent)
{
    m_noDrawingAreaIndent = newNoDrawingAreaIndent;
}
auto operator<<(QDebug debug, const PageFrame &frame) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "PageFrame(" << frame.type() << ")";
    return debug;
}
