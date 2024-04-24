#ifndef TITLEBLOCK_H
#define TITLEBLOCK_H
#include <memory>

#include <QRectF>

#include <QObject>

#include <QDebug>

#include "universaldraw.h"

class TitleBlock
{
public:
    TitleBlock();

    QString type() const;

    QString description() const;

    ///
    /// \brief draw draws the titleblock into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param where the rectangle where the titleblock is drawn in to(typically the drawing area of
    /// the frame)
    /// \param onWhat is the page layout the frame is to be draw on, this is to get the name for
    /// example
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat);

protected:
    ///
    /// \brief setType sets the type of the frame, the base class TitleBlock has the type "none"
    /// \param newType the new Type
    ///
    void setType(const QString &newType);
    void setDescription(const QString &newDescription);

private:
    ///
    /// \brief m_type the type name of the titleblock
    ///
    QString m_type = "none";

    ///
    /// \brief m_description is a more detailed description of the titleblock, it is meant to be
    /// uses as a user Info or something similar
    ///
    QString m_description = "No Titleblock at all";
};

#endif // TITLEBLOCK_H
