#ifndef PREVIEW_H
#define PREVIEW_H
#include <memory>

#include <QFrame>
#include <QPainter>
#include <QSvgRenderer>

#include "PageLayout/pagestyle.h"

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

    std::shared_ptr<QPainter> painter() const;
    void setPainter(const std::shared_ptr<QPainter> &newPainter);

    std::shared_ptr<PageStyle> pageStyle() const;
    void setPageStyle(const std::shared_ptr<PageStyle> newPageStyle);

private:
    ///
    /// \brief m_painter is a pointer to the painter to use
    ///
    std::shared_ptr<QPainter> m_painter;

    ///
    /// \brief pageStyle is the page style to be drawn
    ///
    std::shared_ptr<PageStyle> m_pageStyle;

    ///
    /// \brief paintEvent is the event that actually does the painting and is called when the
    /// windows changes or is build \param e
    ///
    void paintEvent(QPaintEvent *e) override;
};

///
/// \brief operator << is to print out the status of the PreView class to the Debugging interface
/// \param debug
/// \param preview
/// \return
///
auto operator<<(QDebug debug, const PreView &preview) -> QDebug;

#endif // PREVIEW_H
