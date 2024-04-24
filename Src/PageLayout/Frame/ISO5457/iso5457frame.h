#ifndef ISO5457FRAME_H
#define ISO5457FRAME_H

#include "PageLayout/Frame/pageframe.h"

class ISO5457Frame : public PageFrame
{
public:
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
    /// \param onWhat
    ///
    void decideBottomAndTopCenteringLine(double TitleBlockWidth, double TitleBlockHeight,
                                         QRectF where);

private:
    bool m_topCenteringLines = true;
    bool m_bottomCenteringLines = true;
    bool m_leftCenteringLines = true;
    bool m_rigthCenteringLines = true;
};

#endif // ISO5457FRAME_H
