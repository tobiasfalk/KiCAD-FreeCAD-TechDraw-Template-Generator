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
    QString getFILEENDING();
    bool writeBase();
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

    QList<QDomElement> OPACKAGES;
    QList<QDomElement> OSYMBOLS;
    QList<QDomElement> ODEVICESETS;

    QList<QString> ONAMELIST;

    ///
    /// \brief newPage creates a new emty Page
    ///
    bool newPage();

    void drawLine(Coordinate start, Coordinate end, double lineWidth);
    void drawRect(Coordinate start, Coordinate end, double lineWidth);
    void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true); // Always filled
    void drawCircle(Coordinate center, double radius, double lineWidth);
    qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont");

    void drawLogoTitelblockISO7200();
public:
    explicit TemplateGenEagle(QObject *parent = nullptr);
    ~TemplateGenEagle();
};

#endif // TEMPLATEGENEAGLE_H
