#include "pagestyle.h"

#include <QDebug>

#include <QRectF>

PageStyleData::PageStyleData() { }

PageStyle::PageStyle()
{
    m_pageStyleData = new PageStyleData;
}

void PageStyle::draw(std::shared_ptr<UniversalDraw> into)
{
    m_pageStyleData->frame.draw(into, m_pageStyleData->layout.fullRect());
}

auto PageStyle::getLayout() const -> QPageLayout
{
    return m_pageStyleData->layout;
}

void PageStyle::setLayout(const QPageLayout &newLayout)
{
    m_pageStyleData->layout = newLayout;
}

auto PageStyle::getPageSize() const -> QPageSize
{
    return m_pageStyleData->layout.pageSize();
}

auto PageStyle::getPageHight() const -> qreal
{
    return m_pageStyleData->layout.fullRect(QPageLayout::Millimeter).height();
}

auto PageStyle::getPageWidth() const -> qreal
{
    return m_pageStyleData->layout.fullRect(QPageLayout::Millimeter).width();
}

void PageStyle::setPageSize(const QPageSize &newPageSize, QPageLayout::Orientation newOrientation)
{
    m_pageStyleData->layout.setPageSize(newPageSize, QMarginsF(0, 0, 0, 0));
    m_pageStyleData->layout.setOrientation(newOrientation);
}

void PageStyle::setPageSize(qreal newPageHight, qreal newPageWidth,
                            QPageLayout::Orientation newOrientation, const QString &newName)
{
    QPageSize::PageSizeId pageId =
            QPageSize::id(QSizeF{ newPageWidth, newPageHight }, QPageSize::Millimeter,
                          QPageSize::FuzzyOrientationMatch);

    if (pageId == QPageSize::Custom) {
        m_pageStyleData->layout.setPageSize(QPageSize{ QSizeF{ newPageWidth, newPageHight },
                                                       QPageSize::Millimeter, newName,
                                                       QPageSize::ExactMatch },
                                            QMarginsF(0, 0, 0, 0));
    } else {
        m_pageStyleData->layout.setPageSize(QPageSize{ pageId }, QMarginsF(0, 0, 0, 0));
    }

    m_pageStyleData->layout.setOrientation(newOrientation);
}

auto PageStyle::getFrame() const -> PageFrame
{
    return m_pageStyleData->frame;
}

void PageStyle::setFrame(PageFrame &newFrame)
{
    m_pageStyleData->frame = newFrame;
}

auto operator<<(QDebug debug, const PageStyle &style) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "PageStyle(" << style.getLayout() << ", " << style.getFrame() << ")";
    return debug;
}
