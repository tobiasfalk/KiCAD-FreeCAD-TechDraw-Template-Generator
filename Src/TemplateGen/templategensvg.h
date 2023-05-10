#ifndef TEMPLATEGENSVG_H
#define TEMPLATEGENSVG_H

#include "templategenpdf.h"
#include <QObject>
#include <QSvgGenerator>
#include <QPainter>
#include <QPdfWriter>
#include <QSvgRenderer>


class TemplateGenSVG : public TemplateGen
{
protected:
    QString getFILEENDING() override;
    bool writeBase() override;
    std::shared_ptr<QSvgGenerator> SVGWRITER;
    std::shared_ptr<QPainter> PAINTER;
    std::shared_ptr<QSvgRenderer> LOGORENDERER;

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
    explicit TemplateGenSVG(QObject *parent = nullptr);
    ~TemplateGenSVG();
};

#endif // TEMPLATEGENSVG_H
