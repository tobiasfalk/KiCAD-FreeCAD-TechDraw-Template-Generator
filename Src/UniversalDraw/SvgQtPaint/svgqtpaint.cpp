#include "svgqtpaint.h"

SvgQtPaint::SvgQtPaint() { }

void SvgQtPaint::drawText(const QPointF &position, const QString &text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, const QString &font, const QString &name, bool isEditable)
{
    if (isEditable && !this->showEditable()) {
        return;
    }

    QFont qFont(font);
    QFont qFontA(font);
    qFont.setPointSizeF(textSize / 458.612); // 18897.6378
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
    if (editableBlue() && isEditable) {
        pen = QPen(Qt::blue);
    }

    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    painter()->setPen(pen);
    painter()->setBrush(Qt::NoBrush);

    painter()->setFont(qFont);
    painter()->drawText(QPointF(posX, posY), text);
}

bool SvgQtPaint::start()
{
    m_svgWriter =
            std::shared_ptr<QSvgGenerator>(new QSvgGenerator(QSvgGenerator::SvgVersion::SvgTiny12));
    m_svgWriter->setFileName(this->fileName());
    m_svgWriter->setResolution(33020);
    m_svgWriter->setSize(QSize(this->width() * (m_svgWriter->resolution() * (1 / 25.4)),
                               this->height() * (m_svgWriter->resolution() * (1 / 25.4))));
    m_svgWriter->setViewBox(QRect(0, 0, this->width(), this->height()));
    this->setPainter(std::shared_ptr<QPainter>(new QPainter(m_svgWriter.get())));
    return true;
}

bool SvgQtPaint::end()
{
    this->painter()->end();
    return true;
}
