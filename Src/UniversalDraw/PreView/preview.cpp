#include "preview.h"

#include "universaldraw.h"

void PreView::paintEvent(QPaintEvent *e)
{

    m_painter = std::shared_ptr<QPainter>(new QPainter(this));

    std::shared_ptr<QtPainterDrawer> m_pre_painter = std::make_shared<QtPainterDrawer>(m_painter);


    double scale = this->minimumWidth() / 297;
    if(210 * scale > this->height())
    {
        scale = this->height() / 210;
    }
    m_painter->setTransform(QTransform().scale(scale, scale));// 18,897.6378 p/mm = 480,000 dpi



    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    QRectF rectangle(QPointF(0, 0), QPointF(297, 210));
    // m_painter->drawRect(rectangle);

    // Brush, sheetBorder
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    // Fill polygon
    QPainterPath path;
    path.addPolygon(rectangle);
    m_painter->fillPath(path, brush);

    test::printTest(m_pre_painter);

    // if(sheetBorder){
    //     drawRect(Coordinate{0,0}, Coordinate{SHEETSIZE.width, SHEETSIZE.height}, 1);
    // }


    m_painter->end();

    QFrame::paintEvent(e);
}

PreView::PreView() {}

PreView::~PreView() {}


auto operator<<(QDebug debug, const PreView &preview) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "PreView class";
    return debug;
}
