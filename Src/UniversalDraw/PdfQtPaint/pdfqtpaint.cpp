#include "pdfqtpaint.h"

PdfQtPaint::PdfQtPaint() : QtPainterDrawer() { }

void PdfQtPaint::drawText(QPointF position, QString text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, QString font, QString name, bool isEditable)
{
    if (isEditable) {
        return;
    }
    textSize = ((textSize * std::sqrt(2)) / m_resolutionPMM) * 2.8346456692913;
    QtPainterDrawer::drawText(position, text, textSize, textHeightAnchor, textWidthAnchor,
                              lineWidth, font, name, isEditable);
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
