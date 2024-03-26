#ifndef PREVIEW_H
#define PREVIEW_H
#include <memory>

#include <QFrame>
#include <QPainter>
#include <QSvgRenderer>

#include "universaldraw.h"

#include "QtPaint/qtpainterdrawer.h"

///
/// \brief The PreView class uses the QtPainterDrawer class to draw a PreView in to the main window
///
class PreView : public QFrame
{
public:
    ///
    /// \brief PreView a basic constructor
    ///
    PreView();
    ~PreView();

private:

    ///
    /// \brief m_painter is a pointer to the painter to use
    ///
    std::shared_ptr<QPainter> m_painter;

    ///
    /// \brief paintEvent is the event that acualy doues the painting and is cald when the windows changes or is build
    /// \param e
    ///
    void paintEvent(QPaintEvent *e) override;
};

///
/// \brief operator << is to print out the status of the PreView class to the Debuging interface
/// \param debug
/// \param preview
/// \return
///
auto operator<<(QDebug debug, const PreView &preview) -> QDebug;

#endif // PREVIEW_H
