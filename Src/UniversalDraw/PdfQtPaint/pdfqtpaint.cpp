#include "pdfqtpaint.h"

PdfQtPaint::PdfQtPaint() : QtPainterDrawer() { }

void PdfQtPaint::drawText(const QPointF &position, const QString &text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, const QString &font, const QString &name, bool isEditable)
{
    if (isEditable && !this->showEditable()) {
        return;
    }

    QFont qFont(font);
    QFont qFontA(font);
    qFont.setPointSizeF(((textSize * std::sqrt(2)) / m_resolutionPMM)
                        * 2.8346456692913); // 18897.6378
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

bool PdfQtPaint::start()
{
    m_pdfWriter = std::shared_ptr<QPdfWriter>(new QPdfWriter(this->fileName()));
    // m_pdfWriter->setPdfVersion(QPagedPaintDevice::PdfVersion_A1b);
    m_pdfWriter->setPageMargins(QMarginsF(0, 0, 0, 0));
    m_pdfWriter->setPageSize(
            QPageSize(QSizeF(this->width(), this->height()), QPageSize::Millimeter));
    m_pdfWriter->setResolution(m_resolutionDPI);
    this->setPainter(std::shared_ptr<QPainter>(new QPainter(m_pdfWriter.get())));
    this->painter()->setTransform(QTransform().scale(m_resolutionPMM, m_resolutionPMM));
    return true;
}

bool PdfQtPaint::end()
{
    this->painter()->end();
    return true;
}

int PdfQtPaint::resolutionDPI() const
{
    return m_resolutionDPI;
}

void PdfQtPaint::setResolutionDPI(int newResolutionDPI)
{
    m_resolutionDPI = newResolutionDPI;
    m_resolutionPMM = m_resolutionDPI * (1 / 25.4);
}

double PdfQtPaint::resolutionPMM() const
{
    return m_resolutionPMM;
}

void PdfQtPaint::setResolutionPMM(double newResolutionPMM)
{
    m_resolutionPMM = newResolutionPMM;
    m_resolutionDPI = int(m_resolutionPMM * 25.4);
}
