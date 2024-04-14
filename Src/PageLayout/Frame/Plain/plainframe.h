#ifndef PLAINFRAME_H
#define PLAINFRAME_H

#include "pageframe.h"

///
/// \brief The PlainFrame class sets up and draws a simple and plain frame only consisting of a
/// simple rectangle
///
class PlainFrame : public PageFrame
{
public:
    PlainFrame();

    ///
    /// \brief draw draws the frame into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param where the rectangle where the frame is drawn in to(typically the dimensions of the
    /// page)
    /// \param onWhat is the page layout the frame is to be draw on
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QRectF where,
                      QPageLayout onWhat) override;

    double indentLeft() const;
    void setIndentLeft(double newIndentLeft);

    double indentRigth() const;
    void setIndentRigth(double newIndentRigth);

    double indentTop() const;
    void setIndentTop(double newIndentTop);

    double indentBottom() const;
    void setIndentBottom(double newIndentBottom);

    double lineWidth() const;
    void setLineWidth(double newLineWidth);

private:
    ///
    /// \brief m_indentLeft is the space from the left edge to the rectangle
    ///
    double m_indentLeft = 5;
    double m_indentRigth = 5;
    double m_indentTop = 5;
    double m_indentBottom = 5;

    double m_lineWidth = 1;
};

#endif // PLAINFRAME_H
