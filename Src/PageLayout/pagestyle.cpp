#include "pagestyle.h"
#include "universaldraw.h"

#include <QDebug>

#include <QRectF>

PageStyle::PageStyle() { }

void PageStyle::draw(std::shared_ptr<UniversalDraw> into)
{
    // UniversalDraw::printTest(into, m_layout);

    into->setHight(m_layout.fullRect(QPageLayout::Millimeter).height());
    into->setWidth(m_layout.fullRect(QPageLayout::Millimeter).width());

    into->start();

    m_frame->draw(into, m_layout.fullRect(QPageLayout::Millimeter));

    // into->drawLine(QPointF{ 0, 0 }, QPointF{ 297, 210 }, .5);
    // into->drawLine(QLineF{ 0, 210, 297, 0 }, 3);

    // into->drawCircle(QPointF{ 297 / 2, 210 / 2 }, 50, 1);

    // into->drawRect(QPointF{ 20, 20 }, QPointF{ 30, 30 }, .3);

    // into->drawPoly(QPointF{ 40, 40 },
    //                QList<QPointF>{ QPointF(0, 0), QPointF(0, 10), QPointF(10, 10), QPointF(10,
    //                5),
    //                                QPointF(5, 5), QPointF(5, 0) },
    //                .8, true);

    // into->drawText(QPointF{ 60, 10 }, "TextABCabc", 3, TextHeightAnchor::Bottom,
    //                TextWidthAnchor::Left, .3, "osifont", "testText1", true);
    // into->drawText(QPointF{ 60, 20 }, "TextABCabc", 5, TextHeightAnchor::Bottom,
    //                TextWidthAnchor::Left, .5, "osifont");
    // into->drawText(QPointF{ 60, 30 }, "TextABCabc", 1, TextHeightAnchor::Bottom,
    //                TextWidthAnchor::Left, .1, "osifont");

    // into->drawPicture("./Test/wieserfalke_2.svg", QPointF{ 80, 100 }, 30, 20, 3600);
    // into->drawPicture("./Test/wieserfalke_1A.png", QPointF{ 160, 100 }, 30, 50);

    into->end();
}

auto PageStyle::getLayout() const -> QPageLayout
{
    return m_layout;
}

void PageStyle::setLayout(const QPageLayout &newLayout)
{
    m_layout = newLayout;
}

auto PageStyle::getPageSize() const -> QPageSize
{
    return m_layout.pageSize();
}

auto PageStyle::getPageHight() const -> qreal
{
    return m_layout.fullRect(QPageLayout::Millimeter).height();
}

auto PageStyle::getPageWidth() const -> qreal
{
    return m_layout.fullRect(QPageLayout::Millimeter).width();
}

void PageStyle::setPageSize(const QPageSize &newPageSize, QPageLayout::Orientation newOrientation)
{
    m_layout.setPageSize(newPageSize, QMarginsF(0, 0, 0, 0));
    m_layout.setOrientation(newOrientation);
}

void PageStyle::setPageSize(qreal newPageHight, qreal newPageWidth,
                            QPageLayout::Orientation newOrientation, const QString &newName)
{
    QPageSize::PageSizeId pageId =
            QPageSize::id(QSizeF{ newPageWidth, newPageHight }, QPageSize::Millimeter,
                          QPageSize::FuzzyOrientationMatch);

    if (pageId == QPageSize::Custom) {
        m_layout.setPageSize(QPageSize{ QSizeF{ newPageWidth, newPageHight }, QPageSize::Millimeter,
                                        newName, QPageSize::ExactMatch },
                             QMarginsF(0, 0, 0, 0));
    } else {
        m_layout.setPageSize(QPageSize{ pageId }, QMarginsF(0, 0, 0, 0));
    }

    m_layout.setOrientation(newOrientation);
}

auto PageStyle::getFrame() const -> std::shared_ptr<PageFrame>
{
    return m_frame;
}

void PageStyle::setFrame(std::shared_ptr<PageFrame> newFrame)
{
    m_frame = newFrame;
}

auto operator<<(QDebug debug, const PageStyle &style) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "PageStyle(" << style.getLayout() << ", " << style.getLayout().pageSize()
                    << ", " << style.getFrame().get() << ")";
    return debug;
}
