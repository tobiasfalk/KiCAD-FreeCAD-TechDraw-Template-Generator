#ifndef TEMPLATEGENKICAD_5_H
#define TEMPLATEGENKICAD_5_H
#include <memory>
#include <utility>

#include <QDebug>
#include <QObject>
#include <QFile>

#include "templategen.h"
#include "templateoptions.h"

class TemplateGenKiCAD_5 : public TemplateGen
{
    Q_OBJECT
protected:
    virtual QString getFILEENDING() override;
    virtual bool writeBase() override;
    std::shared_ptr<QFile> FILE;

    virtual void drawLine(Coordinate start, Coordinate end, double lineWidth) override;
    virtual void drawRect(Coordinate start, Coordinate end, double lineWidth) override;
    virtual void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true) override;
    virtual void drawCircle(Coordinate center, double radius, double lineWidth, double circleArc = 5) override; // circleArc in degre(°) and it needs to be a fraction of 360, 5° is not noticable
    virtual qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont") override;

    virtual void drawLogoTitelblockISO7200() override;

    ///
    /// \brief newSheet creates a new emty Sheet
    ///
    bool newSheet() override;

public:
    explicit TemplateGenKiCAD_5(QObject *parent = nullptr);
    ~TemplateGenKiCAD_5();

signals:

    void TRIMMINGMARKSChanged();
};

#endif // TEMPLATEGENKICAD_5_H
