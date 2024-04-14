#ifndef PAGEFRAME_H
#define PAGEFRAME_H
#include <memory>

#include <QRectF>

#include <QObject>

#include <QDebug>

#include "universaldraw.h"

///
/// \brief The PageFrame class is the base class for a sheet frame like the ISO 54
///
class PageFrame
{
public:
    PageFrame();

    ///
    /// \brief type returns the frame type, the base class PageFrame has the type "none".
    /// \return
    ///
    QString type() const;

    ///
    /// \brief draw draws the frame into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param where the rectangle where the frame is drawn in to(typically the dimensions of the
    /// page)
    /// \param onWhat is the page layout the frame is to be draw on
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat);

    QRectF drawingArea() const;

    QString description() const;

protected:
    ///
    /// \brief setType sets the type of the frame, the base class PageFrame has the type "none"
    /// \param newType
    ///
    void setType(const QString &newType);

    void setDescription(const QString &newDescription);

    void setDrawingArea(const QRectF &newDrawingArea);

private:
    ///
    /// \brief m_type the type name of the frame
    ///
    QString m_type = "none";

    ///
    /// \brief m_description is a more detailed description of the Frame, it is meant to be uses as
    /// a user Info or something similar
    ///
    QString m_description = "No Frame at all";

    ///
    /// \brief m_drawingArea is the area inside the frame
    ///
    QRectF m_drawingArea;
};

///
/// \brief operator << is used to print the state of the class to a debugging console, with qDebug()
/// \param debug
/// \param frame
/// \return
///
auto operator<<(QDebug debug, const PageFrame &frame) -> QDebug;

#endif // PAGEFRAME_H
