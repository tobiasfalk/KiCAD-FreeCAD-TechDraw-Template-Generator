#ifndef PAGEFRAME_H
#define PAGEFRAME_H
#include <memory>

#include <QRectF>

#include <QObject>

#include <QDebug>

#include "UniversalDraw/universaldraw.h"

///
/// \brief The PageFrame class is the base class for a sheet frame like the ISO 5457
///
class PageFrame
{
public:
    ///
    /// \brief PageFrame is the base constructor
    ///
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

    ///
    /// \brief drawingArea returns a rectangle with the inside of the frame, where drawing should be
    /// placed. It is used as orientation for all the other options like the TitleBlock
    /// \return the rectangle, in mm
    ///
    QRectF drawingArea() const;

    ///
    /// \brief description returns a description of the frame
    /// \return the description
    ///
    QString description() const;

    ///
    /// \brief noDrawingAreaIndent returns true if there should be nothing that intrudes in to the
    /// drawing area, for example the Centering Marks of ISO5457Frame
    /// \return
    ///
    bool noDrawingAreaIndent() const;
    ///
    /// \brief setNoDrawingAreaIndent if set to true there should be nothing that intrudes in to the
    /// drawing area, for example the Centering Marks of ISO5457Frame
    /// \param newNoDrawingAreaIndent
    ///
    void setNoDrawingAreaIndent(bool newNoDrawingAreaIndent);

    QString font() const;
    void setFont(const QString &newFont);

protected:
    ///
    /// \brief setType sets the type of the frame, the base class PageFrame has the type "none"
    /// \param newType
    ///
    void setType(const QString &newType);

    ///
    /// \brief setDescription sets the description of the frame, this is used in the constructor of
    /// a frame derivative
    /// \param newDescription the new description
    ///
    void setDescription(const QString &newDescription);

    ///
    /// \brief setDrawingArea sets a rectangle with the inside of the frame, where drawing should be
    /// placed. It is used as orientation for all the other options like the TitleBlock. this is
    /// used in the constructor of a frame derivative
    /// \param newDrawingArea the new area
    ///
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

    ///
    /// \brief noDrawingAreaIndent if the Frame has something going in to the Drawing area, like
    /// the Centering marks on ISO5457Frame, this can turn them of(true)
    ///
    bool m_noDrawingAreaIndent = false;

    ///
    /// \brief m_font contains the name of the font to use
    ///
    QString m_font = "osifont";
};

///
/// \brief operator << is used to print the state of the class to a debugging console, with qDebug()
/// \param debug
/// \param frame
/// \return
///
auto operator<<(QDebug debug, const PageFrame &frame) -> QDebug;

#endif // PAGEFRAME_H
