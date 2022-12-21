#ifndef TEMPLATEGENEAGLE_H
#define TEMPLATEGENEAGLE_H
#include <memory>
#include <utility>

#include <QObject>
#include <QFile>
#include <QDomDocument>

#include "templategen.h"
#include "templateoptions.h"

class TemplateGenEagle : public TemplateGen
{
    Q_OBJECT
protected:
    QString getFILEENDING() override;
    bool writeBase() override;
    std::shared_ptr<QFile> FILE;
    std::shared_ptr<QTextStream> XMLTEXTSTREM;
    QDomDocument DOCUMENT;
    QDomElement ROOT;
    QDomElement DRAWING;
    QDomElement LIBRARY;
    QDomElement PACKAGES;
    QDomElement SYMBOLS;
    QDomElement DEVICESETS;

    QDomElement CSYMBOL;
    QDomElement CPACKAGE;
    QDomElement CDEVICS;

    QDomElement DEVICES;
    QDomElement DEVICE;
    QDomElement TECHNOLOGYS;
    QDomElement TECHNOLOGY;

    QList<QDomElement> OPACKAGES;
    QList<QDomElement> OSYMBOLS;
    QList<QDomElement> ODEVICESETS;

    QList<QString> ONAMELIST;

    ///
    /// \brief newSheet creates a new emty Sheet
    ///
    bool newSheet() override;

    void drawLine(Coordinate start, Coordinate end, double lineWidth) override;
    void drawRect(Coordinate start, Coordinate end, double lineWidth) override;
    void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true) override; // Always filled
    void drawCircle(Coordinate center, double radius, double lineWidth, double circleArc = 5) override;
    qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont") override;

    void drawLogoTitelblockISO7200() override;
public:
    explicit TemplateGenEagle(QObject *parent = nullptr);
    ~TemplateGenEagle();
};

#endif // TEMPLATEGENEAGLE_H
