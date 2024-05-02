#include "pagestyle.h"
#include "UniversalDraw/universaldraw.h"

#include <QDebug>

#include <QRectF>

PageStyle::PageStyle() { }

void PageStyle::draw(std::shared_ptr<UniversalDraw> into)
{
    // UniversalDraw::printTest(into, m_layout);

    into->setHeight(m_layout.fullRect(QPageLayout::Millimeter).height());
    into->setWidth(m_layout.fullRect(QPageLayout::Millimeter).width());

    into->start();

    m_frame->draw(into, m_layout.fullRect(QPageLayout::Millimeter), m_layout);

    m_titleblocke->draw(into, m_frame->drawingArea(), m_layout);

    m_foldingLines->draw(into, m_layout);

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

void PageStyle::setPageSize(qreal newPageHeight, qreal newPageWidth,
                            QPageLayout::Orientation newOrientation, const QString &newName)
{
    QPageSize::PageSizeId pageId =
            QPageSize::id(QSizeF{ newPageWidth, newPageHeight }, QPageSize::Millimeter,
                          QPageSize::FuzzyOrientationMatch);

    if (pageId == QPageSize::Custom) {
        m_layout.setPageSize(QPageSize{ QSizeF{ newPageWidth, newPageHeight },
                                        QPageSize::Millimeter, newName, QPageSize::ExactMatch },
                             QMarginsF(0, 0, 0, 0));
    } else {
        m_layout.setPageSize(QPageSize{ pageId }, QMarginsF(0, 0, 0, 0));
    }

    m_layout.setOrientation(newOrientation);
}

auto PageStyle::frame() const -> std::shared_ptr<PageFrame>
{
    return m_frame;
}

void PageStyle::setFrame(std::shared_ptr<PageFrame> newFrame)
{
    m_frame = newFrame;
}

std::shared_ptr<TitleBlock> PageStyle::titleblocke() const
{
    return m_titleblocke;
}

void PageStyle::setTitleblocke(const std::shared_ptr<TitleBlock> &newTitleblocke)
{
    m_titleblocke = newTitleblocke;
}

std::shared_ptr<FoldingLines> PageStyle::foldingLines() const
{
    return m_foldingLines;
}

void PageStyle::setFoldingLines(const std::shared_ptr<FoldingLines> &newFoldingLines)
{
    m_foldingLines = newFoldingLines;
}

auto operator<<(QDebug debug, const PageStyle &style) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "PageStyle(" << style.getLayout() << ", " << style.getLayout().pageSize()
                    << ", " << style.frame().get() << ")";
    return debug;
}
