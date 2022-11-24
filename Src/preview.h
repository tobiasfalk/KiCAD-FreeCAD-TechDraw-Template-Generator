#ifndef PREVIEW_H
#define PREVIEW_H

#include <QFrame>
#include <QObject>
#include <QPainter>

#include "templategen.h"

class Preview : public QFrame, public TemplateGen
{
protected:
    QString getFILEENDING() override;
    bool writeBase() override;
    QPainter *PAINTER;

    ///
    /// \brief newPage creates a new emty Page
    ///
    bool newPage() override;

    void drawLine(Coordinate start, Coordinate end, double lineWidth) override;
    void drawRect(Coordinate start, Coordinate end, double lineWidth) override;
    void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true) override;
    void drawCircle(Coordinate center, double radius, double lineWidth) override;
    qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont") override;

    void drawLogoTitelblockISO7200() override;
private:
    void paintEvent(QPaintEvent *e) override;
    double SCALE = 1;
public:
    Preview();
};

#endif // PREVIEW_H
