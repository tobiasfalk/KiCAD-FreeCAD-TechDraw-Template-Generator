#ifndef PLAINTITLEBLOCK_H
#define PLAINTITLEBLOCK_H

#include "PageLayout/TitleBlock/titleblock.h"

class PlainTitleBlock : public TitleBlock
{
public:
    PlainTitleBlock();

    ///
    /// \brief draw draws the titleblock into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param where the rectangle where the titleblock is drawn in to(typically the drawing area of
    /// the frame)
    /// \param onWhat is the page layout the frame is to be draw on, this is to get the name for
    /// example
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QRectF where,
                      QPageLayout onWhat) override;

    double height() const;
    void setHeight(double newHeight);

    double width() const;
    void setWidth(double newWidth);

private:
    double m_height = 50;
    double m_width = 180;
};

#endif // PLAINTITLEBLOCK_H
