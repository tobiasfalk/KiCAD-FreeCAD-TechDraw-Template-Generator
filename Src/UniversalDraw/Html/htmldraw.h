#ifndef HTMLDRAW_H
#define HTMLDRAW_H

#include "UniversalDraw/Svg/svgdraw.h"

class HtmlDraw : public SvgDraw
{
public:
    HtmlDraw();

    ///
    /// \brief start initialises the file and make everything ready
    /// to be drawn in to
    /// \return true if successful
    ///
    virtual bool start() override;

    ///
    /// \brief end finishes and closes the file
    /// \return true if successful
    ///
    virtual bool end() override;
};

#endif // HTMLDRAW_H
