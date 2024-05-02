#include "qtpainterdrawer.h"

#include <QFile>

QtPainterDrawer::QtPainterDrawer(std::shared_ptr<QPainter> painter)
{
    m_painter = painter;
}

QtPainterDrawer::QtPainterDrawer() { }

QtPainterDrawer::~QtPainterDrawer() { }

void QtPainterDrawer::drawLine(QPointF start, QPointF end, double lineWidth)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    QLineF line(start, end);
    m_painter->drawLine(line);
}

void QtPainterDrawer::drawLine(QLineF line, double lineWidth)
{
    drawLine(line.p1(), line.p2(), lineWidth);
}

void QtPainterDrawer::drawRect(QPointF start, QPointF end, double lineWidth, bool fill)
{
    drawRect(QRectF{ start, end }, lineWidth, fill);
}

void QtPainterDrawer::drawRect(QRectF rect, double lineWidth, bool fill)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    // QRectF rectangle(QPointF(start.X, start.Y), QPointF(end.X, end.Y));
    m_painter->drawRect(rect);

    // Brush
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    if (fill) {
        // Fill polygon
        QPainterPath path;
        path.addPolygon(rect);
        m_painter->fillPath(path, brush);
    }
}

void QtPainterDrawer::drawPoly(QPointF position, QList<QPointF> points, double lineWidth, bool fill)
{
    QList<QPointF> qPoints;
    for (int i = 0; i < points.length(); i++) {
        qPoints.append(QPointF(points[i].x() + position.x(), points[i].y() + position.y()));
    }
    drawPoly(qPoints, lineWidth, fill);
}

void QtPainterDrawer::drawPoly(QPolygonF poly, double lineWidth, bool fill)
{
    // Because there is a offset with the size of the line width
    // if(!fill)
    // {
    //     position.X += lineWidth;
    //     position.Y += lineWidth;
    // }
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);

    m_painter->drawPolygon(poly, Qt::WindingFill);

    // Brush
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    if (fill) {
        // Fill polygon
        QPainterPath path;
        path.addPolygon(poly);
        m_painter->fillPath(path, brush);
    }
}

void QtPainterDrawer::drawCircle(QPointF center, double radius, double lineWidth, bool fill)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    QRectF rectangle(center.x() - radius, center.y() - radius, radius * 2, radius * 2);

    m_painter->drawEllipse(rectangle);

    // Brush
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    if (fill) {
        // Fill polygon
        QPainterPath path;
        path.addEllipse(rectangle);
        m_painter->fillPath(path, brush);
    }
}

void QtPainterDrawer::drawText(QPointF position, QString text, double textSize,
                               TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                               double lineWidth, QString font, QString name, bool isEditable)
{
    QFont qFont(font);
    QFont qFontA(font);
    qFont.setPointSizeF(textSize); // 18897.6378
    qFontA.setPointSizeF(100);
    double posX = position.x();
    double posY = position.y();
    QFontMetrics fm(qFontA);

    if (textWidthAnchor == TextWidthAnchor::Left) {
    } else if (textWidthAnchor == TextWidthAnchor::Center) {
        posX -= (textSize * (fm.size(Qt::TextDontPrint, text).width() / double(100))) / 2;
    } else if (textWidthAnchor == TextWidthAnchor::Right) {
        posX -= (textSize * (fm.size(Qt::TextDontPrint, text).width() / double(100)));
    }

    if (textHeightAnchor == TextHeightAnchor::Top) {
        posY += textSize;
    } else if (textHeightAnchor == TextHeightAnchor::Middle) {
        posY += (textSize / 2);
    } else if (textHeightAnchor == TextHeightAnchor::Bottom) {
    }

    QPen pen(Qt::black);
    if (m_editableBlue && isEditable) {
        pen = QPen(Qt::blue);
    }

    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    m_painter->setFont(qFont);
    m_painter->drawText(QPointF(posX, posY), text);
}

void QtPainterDrawer::drawPicture(QString picturePath, QPointF position, double width,
                                  double height, int dpiVector)
{
    double resulutionPMM = dpiVector * (1 / 25.4);
    if (picturePath.endsWith(".svg")) {
        // Load SVG
        std::shared_ptr<QSvgRenderer> svgRenderer =
                std::shared_ptr<QSvgRenderer>(new QSvgRenderer(picturePath));
        QSize size = svgRenderer->defaultSize();

        // Prepare a QImage with desired characteristic
        int widthPx = resulutionPMM * width;
        int widthCalc = width;

        int heightPx = int(widthPx * (double(size.height()) / size.width()));
        double heightCalc = heightPx / resulutionPMM;

        if (heightCalc > height) {
            heightPx = resulutionPMM * height;
            widthPx = int(heightPx * (double(size.width()) / size.height()));

            heightCalc = height;
            widthCalc = widthPx / resulutionPMM;

            QImage image(widthPx, heightPx, QImage::Format_ARGB32);
            image.fill(Qt::transparent); // partly transparent background

            // Get QPainter that paints to the image
            QPainter painter(&image);
            painter.setBackground(QBrush{ Qt::transparent });
            svgRenderer->render(&painter);

            QRectF target(position, QSizeF(widthCalc, heightCalc));

            // Draw the Logo
            // m_painter->drawImage(target, image);

            svgRenderer->render(m_painter.get(), target);
        } else if (picturePath.endsWith(".png")) {
            QPixmap qtPixmap;
            qtPixmap.load(picturePath, "PNG");

            // Prepare a QImage with desired characteristic
            // int widthPx = qtPixmap.width(); // 24mm at 2400dpi(KiCAD scale 0.125)
            double widthCalc = width;

            int heightPx = qtPixmap.height();
            double heightCalc = heightPx / (qtPixmap.width() / widthCalc); // px/mm

            if (heightCalc > height) {
                heightCalc = height;
                widthCalc = qtPixmap.width() / (qtPixmap.height() / heightCalc); // 2400dpi to p/mm
            }

            QRectF target(position, QSizeF(widthCalc, heightCalc));
            m_painter->drawPixmap(target, qtPixmap, qtPixmap.rect());
        }
    }
}

bool QtPainterDrawer::start()
{
    return true;
}

bool QtPainterDrawer::end()
{
    return true;
}

std::shared_ptr<QPainter> QtPainterDrawer::painter() const
{
    return m_painter;
}

void QtPainterDrawer::setPainter(const std::shared_ptr<QPainter> &newPainter)
{
    m_painter = newPainter;
}

bool QtPainterDrawer::editableBlue() const
{
    return m_editableBlue;
}

void QtPainterDrawer::setEditableBlue(bool newEditableBlue)
{
    m_editableBlue = newEditableBlue;
}

auto operator<<(QDebug debug, const QtPainterDrawer &qtpainterdrawer) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "QtPainterDrawer class";
    return debug;
}
