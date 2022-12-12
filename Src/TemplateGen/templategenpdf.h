#ifndef TEMPLATEGENPDF_H
#define TEMPLATEGENPDF_H
#include <memory>
#include <utility>

#include <QObject>
#include <QPainter>
#include <QPdfWriter>
#include <QSvgRenderer>

#include "templategen.h"


class TemplateGenPDF : public TemplateGen
{
    Q_OBJECT
protected:
    QString getFILEENDING() override;
    bool writeBase() override;
    std::shared_ptr<QPdfWriter> PDFWRITER;
    std::shared_ptr<QPainter> PAINTER;
    std::shared_ptr<QSvgRenderer> RENDERER;

    ///
    /// \brief newSheet creates a new emty Sheet
    ///
    bool newSheet() override;

    void drawLine(Coordinate start, Coordinate end, double lineWidth) override;
    void drawRect(Coordinate start, Coordinate end, double lineWidth) override;
    void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true) override;
    void drawCircle(Coordinate center, double radius, double lineWidth, double circleArc = 5) override;
    qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont") override;

    void drawLogoTitelblockISO7200() override;
public:
    explicit TemplateGenPDF(QObject *parent = nullptr);
    ~TemplateGenPDF();
};

#endif // TEMPLATEGENPDF_H
