#ifndef PAGELAYOUT_H
#define PAGELAYOUT_H
#include <memory>

#include <QDebug>

#include <QPageLayout>
#include <QSharedData>

#include "universaldraw.h"

#include "pageframe.h"

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
    /// \brief draw draws the seten pagestyle
    /// \param into is a pointor to the Universal Draw class that is to be used
    ///
    void draw(std::shared_ptr<UniversalDraw> into);

    ///
    /// \brief getLayout returns the current pagelayout/size and nothing mor, no settings of
    /// the titleblock, frome or other \return
    ///
    [[nodiscard]] auto getLayout() const -> QPageLayout;
    ///
    /// \brief setLayout sets the current layout of the page, this includes size, sizeSting and
    /// orientation
    /// \param newLayout the new layout objekt
    ///
    void setLayout(const QPageLayout &newLayout);

    ///
    /// \brief getPageSize returns the pagesize, as an objekt with the width, height and
    /// sizeStrin but NOT with considoration of the orientation
    /// \return a QPageSize objekt
    ///
    [[nodiscard]] auto getPageSize() const -> QPageSize;
    ///
    /// \brief getPageHight returns the Hight of the page, with considoration of the Oriontetion
    /// \return
    ///
    [[nodiscard]] auto getPageHight() const -> qreal;
    ///
    /// \brief getPageWidth  returns the Hight of the page, with considoration of the Oriontetion
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
    /// \brief setPageSize setzt the page size
    /// \param newPageHight is the hight or one side of the page, it is orientation independent on
    /// sizes known to Qt(QPageSize::PageSizeId)
    /// \param newPageWidth is the width or one side of the page, it is orientation independent on
    /// sizes known to Qt(QPageSize::PageSizeId)
    /// \param newOrientation is the orientation of the page
    /// \param newName on custom pages this is the name of the page, on sizes known to
    /// Qt(QPageSize::PageSizeId) this is ignord
    ///
    /// The width and hight are orinetation independent on sizes known to Qt(QPageSize::PageSizeId)
    /// this means that, 297x210 and 210x297 are both A4 and only newOrientation says if it is
    /// Landscape or Portrit. The width and hight on costom pages should be treates as if they where
    /// in Portrit orientation, this is how Qt is using it, so in general heigth > width, this is
    /// not checkt.
    ///
    void setPageSize(qreal newPageHight, qreal newPageWidth,
                     QPageLayout::Orientation newOrientation, const QString &newName = QString());

    ///
    /// \brief getFrame returns the frame objekt
    /// \return the frame
    ///
    [[nodiscard]] auto getFrame() const -> std::shared_ptr<PageFrame>;
    ///
    /// \brief setFrame sets the frame objekt
    /// \param newFrame
    ///
    void setFrame(std::shared_ptr<PageFrame> newFrame);

private:
    ///
    /// \brief layout holds the general layout of the page
    ///
    QPageLayout m_layout;

    ///
    /// \brief frame contains the frame data
    ///
    std::shared_ptr<PageFrame> m_frame;
};

///
/// \brief operator << is used to print the state of the class to a debuging consol, with qDebug()
/// \param debug
/// \param style
/// \return
///
auto operator<<(QDebug debug, const PageStyle &style) -> QDebug;

#endif // PAGELAYOUT_H
