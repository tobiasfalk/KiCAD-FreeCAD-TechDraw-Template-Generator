#include "svgqtpaint.h"

SvgQtPaint::SvgQtPaint() { }

void SvgQtPaint::drawText(QPointF position, QString text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, QString font, QString name, bool isEditable)
{
    if (isEditable) {
        return;
    }
    textSize = textSize / 458.612;
    QtPainterDrawer::drawText(position, text, textSize, textHeightAnchor, textWidthAnchor,
                              lineWidth, font, name, isEditable);
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
