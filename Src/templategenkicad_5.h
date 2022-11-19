#ifndef TEMPLATEGENKICAD_5_H
#define TEMPLATEGENKICAD_5_H

#include <QDebug>
#include <QObject>
#include <QFile>

#include "templategen.h"
#include "templateoptions.h"

class TemplateGenKiCAD_5 : public TemplateGen
{
    Q_OBJECT
protected:
    virtual QString getFILEENDING();
    virtual bool writeBase();
    QFile *FILE;

    virtual void drawLine(Coordinate start, Coordinate end, double lineWidth);
    virtual void drawRect(Coordinate start, Coordinate end, double lineWidth);
    virtual void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true);
    virtual void drawCircle(Coordinate center, double radius, double lineWidth);
    virtual qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont");

    virtual void drawLogoTitelblockISO7200();

    ///
    /// \brief newPage creates a new emty Page
    ///
    void newPage();

public:
    explicit TemplateGenKiCAD_5(QObject *parent = nullptr);
    ~TemplateGenKiCAD_5();

signals:

    void TRIMMINGMARKSChanged();
};

#endif // TEMPLATEGENKICAD_5_H
