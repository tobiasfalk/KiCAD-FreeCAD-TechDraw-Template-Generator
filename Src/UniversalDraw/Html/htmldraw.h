#ifndef HTMLDRAW_H
#define HTMLDRAW_H

#include "UniversalDraw/Svg/svgdraw.h"

///
/// \brief The HtmlDraw class writes an HTML file that embeds the generated SVG
///
class HtmlDraw : public SvgDraw
{
public:
    ///
    /// \brief HtmlDraw the base constructor
    ///
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
