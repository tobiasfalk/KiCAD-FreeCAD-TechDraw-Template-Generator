#include "pngqtpaint.h"
#include "qcolor.h"
#include "qnamespace.h"
#include "qpixmap.h"

#include <QFile>

PngQtPaint::PngQtPaint() : QtPainterDrawer() { }

// void PngQtPaint::drawText(QPointF position, QString text, double textSize,
//                           TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
//                           double lineWidth, QString font, QString name, bool isEditable)
// {
//     if (isEditable && !this->showEditable()) {
//         return;
//     }

//     QFont qFont(font);
//     QFont qFontA(font);
//     qFont.setPointSizeF(((textSize * std::sqrt(2)) / m_resolutionPMM)
//                         * 2.8346456692913); // 18897.6378
//     qFontA.setPointSizeF(100);
//     double posX = position.x();
//     double posY = position.y();
//     QFontMetrics fm(qFontA);

//     if (textWidthAnchor == TextWidthAnchor::Left) {
//     } else if (textWidthAnchor == TextWidthAnchor::Center) {
//         posX -= (textSize * (fm.size(Qt::TextDontPrint, text).width() / double(100))) / 2;
//     } else if (textWidthAnchor == TextWidthAnchor::Right) {
//         posX -= (textSize * (fm.size(Qt::TextDontPrint, text).width() / double(100)));
//     }

//     if (textHeightAnchor == TextHeightAnchor::Top) {
//         posY += textSize;
//     } else if (textHeightAnchor == TextHeightAnchor::Middle) {
//         posY += (textSize / 2);
//     } else if (textHeightAnchor == TextHeightAnchor::Bottom) {
//     }

//     QPen pen(Qt::black);
//     if (editableBlue() && isEditable) {
//         pen = QPen(Qt::blue);
//     }

//     pen.setStyle(Qt::SolidLine);
//     pen.setWidthF(lineWidth);
//     painter()->setPen(pen);
//     painter()->setBrush(Qt::NoBrush);

//     painter()->setFont(qFont);
//     painter()->drawText(QPointF(posX, posY), text);
// }

bool PngQtPaint::start()
{
    m_image = std::shared_ptr<QImage>(new QImage((int)(this->width() * m_resolutionPMM),
                                                 (int)(this->height() * m_resolutionPMM),
                                                 QImage::Format_ARGB32));
    this->setPainter(std::shared_ptr<QPainter>(new QPainter(m_image.get())));
    this->painter()->setTransform(QTransform().scale(m_resolutionPMM, m_resolutionPMM));
    return true;
}

bool PngQtPaint::end()
{
    // this->painter()->drawPixmap(10, 130, 50, 50, pixmap);
    this->painter()->end();
    m_image->save(this->fileName());
    return true;
}

int PngQtPaint::resolutionDPI() const
{
    return m_resolutionDPI;
}

void PngQtPaint::setResolutionDPI(int newResolutionDPI)
{
    m_resolutionDPI = newResolutionDPI;
    m_resolutionPMM = m_resolutionDPI * (1 / 25.4);
}

double PngQtPaint::resolutionPMM() const
{
    return m_resolutionPMM;
}

void PngQtPaint::setResolutionPMM(double newResolutionPMM)
{
    m_resolutionPMM = newResolutionPMM;
    m_resolutionDPI = int(m_resolutionPMM * 25.4);
}
