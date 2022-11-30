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
    QString getFILEENDING();
    bool writeBase();
    std::shared_ptr<QPdfWriter> PDFWRITER;
    std::shared_ptr<QPainter> PAINTER;
    std::shared_ptr<QSvgRenderer> RENDERER;

    ///
    /// \brief newPage creates a new emty Page
    ///
    bool newPage();

    void drawLine(Coordinate start, Coordinate end, double lineWidth);
    void drawRect(Coordinate start, Coordinate end, double lineWidth);
    void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true);
    void drawCircle(Coordinate center, double radius, double lineWidth);
    qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont");

    void drawLogoTitelblockISO7200();
public:
    explicit TemplateGenPDF(QObject *parent = nullptr);
    ~TemplateGenPDF();
};

#endif // TEMPLATEGENPDF_H
