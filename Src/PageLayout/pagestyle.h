#ifndef PAGELAYOUT_H
#define PAGELAYOUT_H
#include <memory>

#include <QDebug>

#include <QPageLayout>
#include <QSharedData>

#include "UniversalDraw/universaldraw.h"

#include "PageLayout/Frame/pageframe.h"
#include "PageLayout/TitleBlock/titleblock.h"
#include "PageLayout/FoldingLines/foldinglines.h"

///
/// \brief The PageStyle class manages the layout and style for a page
///
class PageStyle
{
public:
    ///
    /// \brief PageStyle the basic constructor
    ///
    PageStyle();

    ///
    /// \brief draw draws the set page style
    /// \param into is a pointer to the Universal Draw class that is to be used
    ///
    void draw(std::shared_ptr<UniversalDraw> into);

    ///
    /// \brief getLayout returns the current page layout/size and nothing more, no settings of
    /// the title-block, frame or other \return
    ///
    [[nodiscard]] auto getLayout() const -> QPageLayout;
    ///
    /// \brief setLayout sets the current layout of the page, this includes size, sizeSting and
    /// orientation
    /// \param newLayout the new layout object
    ///
    void setLayout(const QPageLayout &newLayout);

    ///
    /// \brief getPageSize returns the page-size, as an object with the width, height and
    /// size string but NOT with consideration of the orientation
    /// \return a QPageSize object
    ///
    [[nodiscard]] auto getPageSize() const -> QPageSize;
    ///
    /// \brief getPageHight returns the height of the page, with consideration of the orientation
    /// \return
    ///
    [[nodiscard]] auto getPageHight() const -> qreal;
    ///
    /// \brief getPageWidth  returns the Width of the page, with consideration of the orientation
    /// \return
    ///
    [[nodiscard]] auto getPageWidth() const -> qreal;
    ///
    /// \brief setPageSize sets the pageSize based on an existing QPageSize and an orientation
    /// \param newPageSize
    /// \param newOrientation
    ///
    void setPageSize(const QPageSize &newPageSize, QPageLayout::Orientation newOrientation);
    ///
    /// \brief setPageSize sets the page size
    /// \param newPageHeight is the height or one side of the page, it is orientation independent on
    /// sizes known to Qt(QPageSize::PageSizeId)
    /// \param newPageWidth is the width or one side of the page, it is orientation independent on
    /// sizes known to Qt(QPageSize::PageSizeId)
    /// \param newOrientation is the orientation of the page
    /// \param newName on custom pages this is the name of the page, on sizes known to
    /// Qt(QPageSize::PageSizeId) this is ignored
    ///
    /// The width and height are orientation independent on sizes known to Qt(QPageSize::PageSizeId)
    /// this means that, 297x210 and 210x297 are both A4 and only newOrientation says if it is
    /// Landscape or Portrait. The width and height on custom pages should be treated as if they
    /// where in Portrait orientation, this is how Qt is using it, so in general height > width,
    /// this is not checked.
    ///
    void setPageSize(qreal, qreal newPageWidth, QPageLayout::Orientation newOrientation,
                     const QString &newName = QString());

    ///
    /// \brief frame returns the frame object
    /// \return the frame
    ///
    [[nodiscard]] auto frame() const -> std::shared_ptr<PageFrame>;
    ///
    /// \brief setFrame sets the frame object
    /// \param newFrame
    ///
    void setFrame(std::shared_ptr<PageFrame> newFrame);

    ///
    /// \brief titleblocke returns the title-block that is used
    /// \return
    ///
    std::shared_ptr<TitleBlock> titleblocke() const;
    ///
    /// \brief setTitleblocke sets the title-block that is used
    /// \param newTitleblocke
    ///
    void setTitleblocke(const std::shared_ptr<TitleBlock> &newTitleblocke);

    std::shared_ptr<FoldingLines> foldingLines() const;
    void setFoldingLines(const std::shared_ptr<FoldingLines> &newFoldingLines);

private:
    ///
    /// \brief layout holds the general layout of the page
    ///
    QPageLayout m_layout;

    ///
    /// \brief frame contains the frame data
    ///
    std::shared_ptr<PageFrame> m_frame;
    ///
    /// \brief m_titleblocke is the title-block to be drawn
    ///
    std::shared_ptr<TitleBlock> m_titleblocke;
    ///
    /// \brief m_titleblocke is the title-block to be drawn
    ///
    std::shared_ptr<FoldingLines> m_foldingLines;
};

///
/// \brief operator << is used to print the state of the class to a debugging console, with qDebug()
/// \param debug
/// \param style
/// \return
///
auto operator<<(QDebug debug, const PageStyle &style) -> QDebug;

#endif // PAGELAYOUT_H
