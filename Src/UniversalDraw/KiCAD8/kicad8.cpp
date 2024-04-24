#include "kicad8.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <QBuffer>
// #include <math.h>

KiCAD8::KiCAD8() { }

void KiCAD8::drawLine(QPointF start, QPointF end, double lineWidth)
{
    QString lineString = "  (line\n"
                         "    (name \"\")\n"
                         "    (start "
            + QString::number(start.x()) + " " + QString::number(start.y())
            + " ltcorner)\n"
              "    (end "
            + QString::number(end.x()) + " " + QString::number(end.y())
            + " ltcorner)\n"
              "    (linewidth "
            + QString::number(lineWidth)
            + ")\n"
              "  )\n";
    m_file->write(lineString.toLatin1());
}

void KiCAD8::drawLine(QLineF line, double lineWidth)
{
    drawLine(line.p1(), line.p2(), lineWidth);
}

void KiCAD8::drawRect(QPointF start, QPointF end, double lineWidth, bool fill)
{
    if (!fill) {
        QString lineString = "  (rect (name \"\")\n"
                             "    (start "
                + QString::number(start.x()) + " " + QString::number(start.y())
                + " ltcorner)\n"
                  "    (end "
                + QString::number(end.x()) + " " + QString::number(end.y())
                + " ltcorner)\n"
                  "    (linewidth "
                + QString::number(lineWidth) + ")\n  )\n";

        m_file->write(lineString.toLatin1());
    } else {
        drawPoly(QPolygonF{ QPointF{ start.x(), start.y() }, QPointF{ end.x(), start.y() },
                            QPointF{ end.x(), end.y() }, QPointF{ start.x(), end.y() } },
                 lineWidth, true);
    }
}

void KiCAD8::drawRect(QRectF rect, double lineWidth, bool fill)
{
    drawRect(rect.topLeft(), rect.bottomRight(), lineWidth, fill);
}

void KiCAD8::drawPoly(QPointF position, QList<QPointF> points, double lineWidth, bool fill)
{
    if (fill) {
        QString lineString = "  (polygon (name \"\")\n    (pos " + QString::number(position.x())
                + " " + QString::number(position.y())
                + " ltcorner)\n    (rotate 0)\n    (linewidth " + QString::number(lineWidth)
                + ")\n";
        lineString += "    (pts ";
        foreach (QPointF pt, points) {
            lineString += "(xy " + QString::number(pt.x()) + " " + QString::number(pt.y()) + ") ";
        }
        lineString += ")\n  )\n";
        m_file->write(lineString.toLatin1());
    } else {
        int i = 1;
        for (i = 1; i < points.size(); i++) {
            drawLine(points[i - 1] + position, points[i] + position, lineWidth);
        }
        drawLine(points[i - 1] + position, points[0] + position, lineWidth);
    }
}

void KiCAD8::drawPoly(QPolygonF poly, double lineWidth, bool fill)
{
    drawPoly(QPointF{ 0, 0 }, poly, lineWidth, fill);
}

void KiCAD8::drawCircle(QPointF center, double radius, double lineWidth, bool fill)
{
    double arc = 0;
    double arcPre = 0;
    while (arc <= 360) {
        if (arc) {
            double x1 = center.x() + radius * std::cos(arcPre * M_PI / 180);
            double y1 = center.y() + radius * std::sin(arcPre * M_PI / 180);
            double x2 = center.x() + radius * std::cos(arc * M_PI / 180);
            double y2 = center.y() + radius * std::sin(arc * M_PI / 180);
            drawLine(QPointF{ x1, y1 }, QPointF{ x2, y2 }, lineWidth);
        }
        arcPre = arc;
        arc += m_circleArc;
    }
}

void KiCAD8::drawText(QPointF position, QString text, double textSize,
                      TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                      double lineWidth, QString font, QString name, bool isEditable)
{
    QString anchorString = "";

    // Left
    if (textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Left) {
        anchorString = "(justify top)";
    } else if (textHeightAnchor == TextHeightAnchor::Middle
               && textWidthAnchor == TextWidthAnchor::Left) {
        anchorString = "";
    } else if (textHeightAnchor == TextHeightAnchor::Bottom
               && textWidthAnchor == TextWidthAnchor::Left) {
        anchorString = "(justify bottom)";
    }

    // Center
    else if (textHeightAnchor == TextHeightAnchor::Top
             && textWidthAnchor == TextWidthAnchor::Center) {
        anchorString = "(justify center top)";
    } else if (textHeightAnchor == TextHeightAnchor::Middle
               && textWidthAnchor == TextWidthAnchor::Center) {
        anchorString = "(justify center)";
    } else if (textHeightAnchor == TextHeightAnchor::Bottom
               && textWidthAnchor == TextWidthAnchor::Center) {
        anchorString = "(justify center bottom)";
    }

    // Right
    else if (textHeightAnchor == TextHeightAnchor::Top
             && textWidthAnchor == TextWidthAnchor::Right) {
        anchorString = "(justify right top)";
    } else if (textHeightAnchor == TextHeightAnchor::Middle
               && textWidthAnchor == TextWidthAnchor::Right) {
        anchorString = "(justify right)";
    } else if (textHeightAnchor == TextHeightAnchor::Bottom
               && textWidthAnchor == TextWidthAnchor::Right) {
        anchorString = "(justify right bottom)";
    }

    QString lineString = "  (tbtext \"" + text + "\" (name \"\")\n    (pos "
            + QString::number(position.x()) + " " + QString::number(position.y() + .3)
            + " ltcorner)\n    (font (face \"" + font + "\") (linewidth "
            + QString::number(lineWidth) + ") (size " + QString::number(textSize) + " "
            + QString::number(textSize) + ")) " + anchorString + ")\n";
    m_file->write(lineString.toLatin1());
}

void KiCAD8::drawPicture(QString picturePath, QPointF position, double width, double height,
                         int dpiVector)
{

    if (picturePath.endsWith(".svg")) {
        // Load SVG
        QSvgRenderer renderer(picturePath);
        QSize size = renderer.defaultSize();

        double resulutionDPI = 9600;
        double resulutionPMM = (resulutionDPI * (1 / 25.4)); // 1300.0 p/mm = 33020 dpi

        // Prepare a QImage with desired characteritisc
        double widthMM = width; // 2400dpi to p/mm
        int widthPx = resulutionPMM * widthMM; // 24mm bei 2400dpi(KiCAD scale 0.125)

        int heightPx = int(widthPx * (double(size.height()) / size.width()));
        double heightMM = heightPx / resulutionPMM; // 2400dpi to p/mm

        if (heightMM > height) {
            heightMM = height; // 2400dpi to p/mm
            heightPx = resulutionPMM * heightMM; // 30mm bei 2400dpi(KiCAD scale 0.125)

            widthPx = int(heightPx * (double(size.width()) / size.height()));
            widthMM = widthPx / resulutionPMM; // 2400dpi to p/mm
        }
        QImage image(widthPx, heightPx, QImage::Format_ARGB32);
        image.fill(0x00FFFFFF); // partly transparent background

        // Get QPainter that paints to the image
        QPainter painter(&image);
        renderer.render(&painter);

        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");

        int rows = ba.length() / 32; // number of lines
        if (ba.length() % 32)
            rows++;

        // create hex dump(https://forum.qt.io/topic/106891/displaying-data-in-hex-format)
        QString data = "  (bitmap (name \"\") (pos " + QString::number(position.x() + widthMM / 2)
                + " " + QString::number(position.y() + heightMM / 2) + "  ltcorner) (scale "
                + QString::number((double)300 / (double)resulutionDPI) + ")\n";
        data += "  (pngdata\n";
        for (int i = 0; i < rows; i++) {
            QString dump;

            dump = ""; //
            QByteArray line = ba.mid(32 * i, 32);
            QString hex;

            // 16 ba by line
            for (int b = 0; b < line.length(); b++) {
                uint8_t c = uint8_t(line.at(b));
                hex += QString::asprintf("%02X ", c); // hex
            }

            while (hex.size() < 48)
                hex.append(' ');
            dump.append(hex);
            data.append("    (data \"" + dump.toLatin1() + " \")\n");
        }
        data.append("    )\n  )\n");
        m_file->write(data.toLatin1());
    } else if (picturePath.endsWith(".png")) {
        // Load SVG
        QImage image(picturePath);
        QSize size = image.size();

        double resulutionPMM = size.width() / width;
        double resulutionDPI = resulutionPMM * 25.4;

        double widthMM = width;
        int widthPx = size.width();

        int heightPx = size.height();
        double heightMM = heightPx / resulutionPMM;

        if (heightMM > height) {
            heightMM = height; // 2400dpi to p/mm
            resulutionPMM = size.height() / height;
            resulutionDPI = resulutionPMM * 25.4;

            widthMM = widthPx / resulutionPMM;
        }

        // Get QPainter that paints to the image

        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");

        int rows = ba.length() / 32; // number of lines
        if (ba.length() % 32)
            rows++;

        // create hex dump(https://forum.qt.io/topic/106891/displaying-data-in-hex-format)
        QString data = "  (bitmap (name \"\") (pos " + QString::number(position.x() + (widthMM / 2))
                + " " + QString::number(position.y() + (heightMM / 2)) + "  ltcorner) (scale "
                + QString::number((double)300 / resulutionDPI) + ")\n";
        data += "  (pngdata\n";
        for (int i = 0; i < rows; i++) {
            QString dump;

            dump = ""; //
            QByteArray line = ba.mid(32 * i, 32);
            QString hex;

            // 16 ba by line
            for (int b = 0; b < line.length(); b++) {
                uint8_t c = uint8_t(line.at(b));
                hex += QString::asprintf("%02X ", c); // hex
            }

            while (hex.size() < 48)
                hex.append(' ');
            dump.append(hex);
            data.append("    (data \"" + dump.toLatin1() + " \")\n");
        }
        data.append("    )\n  )\n");
        m_file->write(data.toLatin1());
    }
}

bool KiCAD8::start()
{
    m_file = std::shared_ptr<QFile>(new QFile(this->fileName()));
    if (m_file->open(QIODeviceBase::WriteOnly)) {
        m_file->write("(kicad_wks\n"
                      "  (version 20231118)\n" // KiCAD 8.0.1
                      "  (generator \"KiCAD-FreeCAD-Temp-Gen\")\n"
                      "	 (generator_version \"2.0\")\n"
                      "  (setup "
                      "    (textsize 0 0)\n"
                      "    (linewidth 0)\n"
                      "    (textlinewidth 0)\n"
                      "    (left_margin 0)\n"
                      "    (right_margin 0)\n"
                      "    (top_margin 0)\n"
                      "    (bottom_margin 0)\n"
                      "  )\n");
        return true;
    } else {
        qCritical() << "Could not open File(KiCAD 5)";
        return false;
    }
}

bool KiCAD8::end()
{
    m_file->write(")\n");
    bool ret = m_file->flush();
    m_file->close();
    return ret;
}
