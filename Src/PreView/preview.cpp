#include "preview.h"

#include "universaldraw.h"

#include "QtPaint/qtpainterdrawer.h"

void PreView::paintEvent(QPaintEvent *e)
{

    m_painter = std::shared_ptr<QPainter>(new QPainter(this));

    std::shared_ptr<QtPainterDrawer> pre_painter = std::make_shared<QtPainterDrawer>(m_painter);

    double scale = this->minimumWidth() / m_pageStyle->getPageWidth();
    if (m_pageStyle->getPageHight() * scale > this->height()) {
        scale = this->height() / m_pageStyle->getPageHight();
    }
    m_painter->setTransform(QTransform().scale(scale, scale)); // 18,897.6378 p/mm = 480,000 dpi

    // QPen pen(Qt::black);
    // pen.setStyle(Qt::SolidLine);
    // pen.setWidthF(1);
    // m_painter->setPen(pen);
    // m_painter->setBrush(Qt::NoBrush);

    // QRectF rectangle(QPointF(0, 0), QPointF(297, 210));
    // // m_painter->drawRect(rectangle);

    // // Brush, sheetBorder
    // QBrush brush;
    // brush.setColor(Qt::white);
    // brush.setStyle(Qt::SolidPattern);
    // // Fill polygon
    // QPainterPath path;
    // path.addPolygon(rectangle);
    // m_painter->fillPath(path, brush);

    m_pageStyle->draw(pre_painter);

    // UniversalDraw::printTest(pre_painter);

    // if(sheetBorder){
    //     drawRect(Coordinate{0,0}, Coordinate{SHEETSIZE.width, SHEETSIZE.height}, 1);
    // }

    m_painter->end();

    QFrame::paintEvent(e);
}

PreView::PreView() { }

PreView::~PreView() { }

std::shared_ptr<QPainter> PreView::painter() const
{
    return m_painter;
}

void PreView::setPainter(const std::shared_ptr<QPainter> &newPainter)
{
    m_painter = newPainter;
}

std::shared_ptr<PageStyle> PreView::pageStyle() const
{
    return m_pageStyle;
}

void PreView::setPageStyle(const std::shared_ptr<PageStyle> newPageStyle)
{
    m_pageStyle = newPageStyle;
}

auto operator<<(QDebug debug, const PreView &preview) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "PreView class";
    return debug;
}
