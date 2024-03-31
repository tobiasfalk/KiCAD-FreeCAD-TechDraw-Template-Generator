#include "pageframe.h"

#include "../../UniversalDraw/universaldraw.h"

#include <QDebug>

PageFrame::PageFrame() { }

QString PageFrame::type() const
{
    return m_type;
}

void PageFrame::draw(std::shared_ptr<UniversalDraw> into, QRectF where)
{
    into->drawRect(where, 1, 0);

    qDebug() << "PageFram, into: " << into.get();

    // into.drawRect(QPointF{ 0, 0 }, QPointF{0, 0}, 1);
    // into.fileName();
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
