#ifndef TEMPLATEGENKICAD_6_H
#define TEMPLATEGENKICAD_6_H

#include <QObject>
#include <QFile>

#include "templategen.h"
#include "templategenkicad_5.h"
#include "templateoptions.h"

class TemplateGenKiCAD_6 : public TemplateGenKiCAD_5
{
    Q_OBJECT
protected:
    virtual QString getFILEENDING();
    virtual bool writeBase();

public:
    explicit TemplateGenKiCAD_6(QObject *parent = nullptr);
    ~TemplateGenKiCAD_6();

signals:

};

#endif // TEMPLATEGENKICAD_6_H
