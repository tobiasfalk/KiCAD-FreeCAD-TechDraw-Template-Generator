#ifndef TEMPLATEGENFREECAD_H
#define TEMPLATEGENFREECAD_H
#include <memory>
#include <utility>

#include <QObject>
#include <QFile>
#include <QDomDocument>

#include "templategen.h"
#include "templateoptions.h"

class TemplateGenFreeCAD : public TemplateGen
{
    Q_OBJECT
protected:
    QString getFILEENDING() override;
    bool writeBase() override;
    std::shared_ptr<QFile> FILE;
    std::shared_ptr<QTextStream> XMLTEXTSTREM;
    QDomDocument DOCUMENT;
    QDomElement ROOT;

    void drawLine(Coordinate start, Coordinate end, double lineWidth) override;
    void drawRect(Coordinate start, Coordinate end, double lineWidth) override;
    void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true) override;
    void drawCircle(Coordinate center, double radius, double lineWidth, double circleArc = 5) override;
    qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont") override;

    void drawLogoTitelblockISO7200() override;

    ///
    /// \brief newSheet creates a new emty Sheet
    ///
    bool newSheet() override;
public:
    explicit TemplateGenFreeCAD(QObject *parent = nullptr);
    ~TemplateGenFreeCAD();

signals:

};

#endif // TEMPLATEGENFREECAD_H
