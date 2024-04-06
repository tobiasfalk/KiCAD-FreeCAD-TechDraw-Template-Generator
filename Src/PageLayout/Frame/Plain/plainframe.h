#ifndef PLAINFRAME_H
#define PLAINFRAME_H

#include "pageframe.h"

class PlainFrame : public PageFrame
{
public:
    PlainFrame();

    ///
    /// \brief draw draws the frame into the given drawer and into the given rectangal
    /// \param into the universal drawer that is drawen in to
    /// \param where the rectangle where the frame is drawen in to(typicaly the dimasions of the
    /// page)
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QRectF where) override;

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
    double m_indentLeft = 5;
    double m_indentRigth = 5;
    double m_indentTop = 5;
    double m_indentBottom = 5;

    double m_lineWidth = 1;
};

#endif // PLAINFRAME_H
