#include "pageframe.h"

#include <QDebug>

PageFrame::PageFrame() { }

QString PageFrame::type() const
{
    return m_type;
}

void PageFrame::draw(UniversalDraw &into, QRectF where)
{
    into.drawRect(where, 1, 0);
    // into.drawRect(QPointF{ 0, 0 }, QPointF)
}

void PageFrame::setType(const QString &newType)
{
    m_type = newType;
}
auto operator<<(QDebug debug, const PageFrame &frame) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "PageFrame(" << frame.type() << ")";
    return debug;
}
