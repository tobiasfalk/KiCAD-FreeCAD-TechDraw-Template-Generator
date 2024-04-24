#ifndef PLAINFRAME_H
#define PLAINFRAME_H

#include "PageLayout/Frame/pageframe.h"

///
/// \brief The PlainFrame class sets up and draws a simple and plain frame only consisting of a
/// simple rectangle
///
class PlainFrame : public PageFrame
{
public:
    ///
    /// \brief PlainFrame is the base Constructor
    ///
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

    ///
    /// \brief indentLeft returns the indent/space to the line on the left side/west of the page
    /// \return the indent in mm
    ///
    double indentLeft() const;
    ///
    /// \brief setIndentLeft sets the indent/space to the line on the left side/west of the page
    /// \param newIndentLeft the new indent in mm
    ///
    void setIndentLeft(double newIndentLeft);

    ///
    /// \brief indentRight same as indentLeft but on the right side/east of the page
    /// \return
    ///
    double indentRight() const;
    ///
    /// \brief setIndentRight same as setIndentLeft but on the right side/east of the page
    /// \param newIndentRight
    ///
    void setIndentRight(double newIndentRight);

    ///
    /// \brief indentTop same as indentLeft but on the top side/north of the page
    /// \return
    ///
    double indentTop() const;
    ///
    /// \brief setIndentTop same as setIndentLeft but on the top side/north of the page
    /// \param newIndentTop
    ///
    void setIndentTop(double newIndentTop);

    ///
    /// \brief indentBottom same as indentLeft but on the bottom side/south of the page
    /// \return
    ///
    double indentBottom() const;
    ///
    /// \brief setIndentBottom same as setIndentLeft but on the bottom side/south of the page
    /// \param newIndentBottom
    ///
    void setIndentBottom(double newIndentBottom);

    ///
    /// \brief lineWidth returns the with of the line the frame should be drawn with
    /// \return the line width in mm
    ///
    double lineWidth() const;
    ///
    /// \brief setLineWidth sets the with of the line the frame should be drawn with
    /// \param newLineWidth the new line width in mm
    ///
    void setLineWidth(double newLineWidth);

private:
    ///
    /// \brief m_indentLeft is the space from the left edge to the rectangle in mm
    ///
    double m_indentLeft = 5;
    ///
    /// \brief m_indentRight is the space from the right edge to the rectangle in mm
    ///
    double m_indentRight = 5;
    ///
    /// \brief m_indentTop is the space from the top edge to the rectangle in mm
    ///
    double m_indentTop = 5;
    ///
    /// \brief m_indentBottom is the space from the bottom edge to the rectangle in mm
    ///
    double m_indentBottom = 5;

    ///
    /// \brief m_lineWidth is the line width of the rectangle in mm
    ///
    double m_lineWidth = 1;
};

#endif // PLAINFRAME_H
