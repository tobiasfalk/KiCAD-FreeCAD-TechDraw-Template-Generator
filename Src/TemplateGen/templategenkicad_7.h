#ifndef TEMPLATEGENKICAD_7_H
#define TEMPLATEGENKICAD_7_H

#include <QObject>
#include <QFile>

#include "templategen.h"
#include "templategenkicad_6.h"
#include "templateoptions.h"

class TemplateGenKiCAD_7 : public TemplateGenKiCAD_6
{
    Q_OBJECT
protected:
    virtual QString getFILEENDING() override;
    virtual bool writeBase() override;

    virtual qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont") override;

public:
    explicit TemplateGenKiCAD_7(QObject *parent = nullptr);
    ~TemplateGenKiCAD_7();
signals:

};

#endif // TEMPLATEGENKICAD_7_H
