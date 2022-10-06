#ifndef TEMPLATEGENFREECAD_H
#define TEMPLATEGENFREECAD_H

#include <QObject>
#include <QFile>
#include <QDomDocument>

#include "templategen.h"
#include "templateoptions.h"

class TemplateGenFreeCAD : public TemplateGen
{
    Q_OBJECT
protected:
    QString getFILEENDING();
    bool writeBase();
    QFile *FILE;
    QTextStream *XMLTEXTSTREM;
    QDomDocument DOCUMENT;
    QDomElement ROOT;

    void drawLine(Coordinate start, Coordinate end, double lineWidth);
    void drawRect(Coordinate start, Coordinate end, double lineWidth);
    void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth);
    void drawCircle(Coordinate center, double radius, double lineWidth);
    qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont");

    void drawLogoTitelblockISO7200();
public:
    explicit TemplateGenFreeCAD(QObject *parent = nullptr);
    ~TemplateGenFreeCAD();

signals:

};

#endif // TEMPLATEGENFREECAD_H
