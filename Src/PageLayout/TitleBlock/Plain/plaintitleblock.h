#ifndef PLAINTITLEBLOCK_H
#define PLAINTITLEBLOCK_H

#include "PageLayout/TitleBlock/titleblock.h"

///
/// \brief The PlainTitleBlock class is a title-block that is simple and mostly used as
/// demonstration and for testing
///
class PlainTitleBlock : public TitleBlock
{
public:
    ///
    /// \brief PlainTitleBlock the base constructor
    ///
    PlainTitleBlock();

    ///
    /// \brief draw draws the title-block into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param where the rectangle where the title-block is drawn in to(typically the drawing area
    /// of the frame)
    /// \param onWhat is the page layout the frame is to be draw on, this is to get
    /// the name for example
    ///
    virtual void draw(const std::shared_ptr<UniversalDraw> &into, const QRectF &where,
                      const QPageLayout &onWhat) override;

    // Behavior:
    // - Draws a plain rectangle of configurable width/height (defaults 180 x 50 mm)
    //   anchored to the bottom-right corner of the target 'where' rect.
    // - No text fields; useful for debugging layouts or as a spacer.

    ///
    /// \brief height returns the height of the title-block
    /// \return the height in mm
    ///
    double height() const;
    ///
    /// \brief setHeight sets the height of the title-block
    /// \param newHeight the new height in mm
    ///
    void setHeight(double newHeight);

    ///
    /// \brief width returns the width of the title-block
    /// \return the width in mm
    ///
    double width() const;
    ///
    /// \brief setWidth sets the width of the title-block
    /// \param newWidth the new width in mm
    ///
    void setWidth(double newWidth);

private:
    ///
    /// \brief m_height the height of the title-block in mm
    ///
    double m_height = 50;
    ///
    /// \brief m_width the width of the title-block in mm
    ///
    double m_width = 180;
};

#endif // PLAINTITLEBLOCK_H
