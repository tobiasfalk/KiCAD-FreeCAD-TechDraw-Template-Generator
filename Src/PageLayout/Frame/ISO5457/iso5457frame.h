#ifndef ISO5457FRAME_H
#define ISO5457FRAME_H

#include "PageLayout/Frame/pageframe.h"

///
/// \brief The ISO5457Frame class creates a ISO 5457 conform frame
///
class ISO5457Frame : public PageFrame
{
public:
    ///
    /// \brief ISO5457Frame is the base constructor
    ///
    ISO5457Frame();

    ///
    /// \brief draw draws the frame into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param where the rectangle where the frame is drawn in to(typically the dimensions of the
    /// page)
    /// \param onWhat is the page layout the frame is to be draw on
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QRectF where,
                      QPageLayout onWhat) override;

    ///
    /// \brief decideBottomCenteringLine decides if the Bottom Centering mark should be drawn.
    /// \param TitleBlockWidth
    /// \param TitleBlockHeight
    /// \param where
    ///
    void decideBottomAndTopCenteringLine(double TitleBlockWidth, double TitleBlockHeight,
                                         QRectF where);

    ///
    /// \brief showPageSize returns true if the page size should be drawn on the bottom right
    /// \return
    ///
    bool showPageSize() const;
    ///
    /// \brief setShowPageSize sets if the page size should be drawn on the bottom right(true shows
    /// it)
    /// \param newShowPageSize
    ///
    void setShowPageSize(bool newShowPageSize);

    ///
    /// \brief showTrimmingMarks returns if the Trimming Marks should be drawn(true  draws them)
    /// \return
    ///
    bool showTrimmingMarks() const;
    ///
    /// \brief setShowTrimmingMarks sets if the Trimming Marks should be drawn(true  draws them)
    /// \param newShowTrimmingMarks
    ///
    void setShowTrimmingMarks(bool newShowTrimmingMarks);

private:
    ///
    /// \brief m_topCenteringLines if true the top centering mark is drawn
    ///
    bool m_topCenteringLines = true;
    ///
    /// \brief m_bottomCenteringLines if true the bottom centering mark is drawn
    ///
    bool m_bottomCenteringLines = true;
    ///
    /// \brief m_leftCenteringLines if true the left centering mark is drawn
    ///
    bool m_leftCenteringLines = true;
    ///
    /// \brief m_rigthCenteringLines if true the rigth centering mark is drawn
    ///
    bool m_rigthCenteringLines = true;

    ///
    /// \brief m_showPageSize true if the page size should be drawn on the bottom right,
    /// setting this to false, it is no longer confirm to ISO 5457
    ///
    bool m_showPageSize = true;

    ///
    /// \brief m_showTrimmingMarks this enables or disables the Trimming marks in the corners,
    /// setting this to false, it is no longer confirm to ISO 5457
    ///
    bool m_showTrimmingMarks = true;
};

#endif // ISO5457FRAME_H
