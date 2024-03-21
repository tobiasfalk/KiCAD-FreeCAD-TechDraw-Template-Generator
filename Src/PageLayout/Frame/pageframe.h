#ifndef PAGEFRAME_H
#define PAGEFRAME_H

#include <QRectF>

#include <QObject>

#include <QDebug>

#include "universaldraw.h"

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
    /// \brief draw draws the frame into the given drawer and into the given rectangal
    /// \param into the universal drawer that is drawen in to
    /// \param where the rectangle where the frame is drawen in to(typicaly the dimasions of the
    /// page)
    ///
    void draw(UniversalDraw &into, QRectF where);

protected:
    ///
    /// \brief setType sets the type of the frame, the base class PageFrame has the type "none"
    /// \param newType
    ///
    void setType(const QString &newType);

private:
    ///
    /// \brief m_type the type name of the frame
    ///
    QString m_type = "none";
};

///
/// \brief operator << is used to print the state of the class to a debuging consol, with qDebug()
/// \param debug
/// \param frame
/// \return
///
auto operator<<(QDebug debug, const PageFrame &frame) -> QDebug;

#endif // PAGEFRAME_H
