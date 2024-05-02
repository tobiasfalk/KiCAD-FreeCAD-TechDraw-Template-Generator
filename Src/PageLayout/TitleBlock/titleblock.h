#ifndef TITLEBLOCK_H
#define TITLEBLOCK_H
#include <memory>

#include <QRectF>

#include <QObject>

#include <QDebug>

#include "UniversalDraw/universaldraw.h"

///
/// \brief The TitleBlock class is the bases for all Title-blocks and if used for drawing will do
/// nothing
///
class TitleBlock
{
public:
    ///
    /// \brief TitleBlock is the base constructor
    ///
    TitleBlock();

    ///
    /// \brief type returns the type of title-block
    /// \return
    ///
    QString type() const;

    ///
    /// \brief description returns the description of the title-block
    /// \return
    ///
    QString description() const;

    ///
    /// \brief draw draws the title-block into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param where the rectangle where the title-block is drawn in to(typically the drawing area
    /// of the frame) \param onWhat is the page layout the frame is to be draw on, this is to get
    /// the name for example
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat);

    ///
    /// \brief titleBlockArea returns a rectangle witch describes the outer dimensions of the
    /// title-block and where it is
    /// \return
    ///
    QRectF titleBlockArea() const;

    ///
    /// \brief language returns the current selected language
    /// \return
    ///
    QString language() const;
    ///
    /// \brief setLanguage sets the to be used, if it is not part of m_languages than it does
    /// nothing
    /// \param newLanguage
    ///
    virtual void setLanguage(const QString &newLanguage);

    ///
    /// \brief languages returns a list of available languages
    /// \return
    ///
    QList<QString> languages() const;

protected:
    ///
    /// \brief setType sets the type of the frame, the base class TitleBlock has the type "none"
    /// \param newType the new Type
    ///
    void setType(const QString &newType);
    ///
    /// \brief setDescription sets the description of the title-block, this is used in the
    /// constructor of a frame derivative
    /// \param newDescription the new description
    ///
    void setDescription(const QString &newDescription);
    ///
    /// \brief setTitleBlockArea sets a rectangle witch describes the outer dimensions of the
    /// title-block and where it is
    /// \param newTitleBlockArea the new area in mm
    ///
    void setTitleBlockArea(const QRectF &newTitleBlockArea);

    ///
    /// \brief setLanguages sets a list of avalible languages, see m_language for more details
    /// \param newLanguages
    ///
    void setLanguages(const QList<QString> &newLanguages);

private:
    ///
    /// \brief m_type the type name of the title-block
    ///
    QString m_type = "none";

    ///
    /// \brief m_description is a more detailed description of the title-block, it is meant to be
    /// uses as a user Info or something similar
    ///
    QString m_description = "No Title-block at all";

    ///
    /// \brief m_titleBlockArea the Area the TitleBlock is placed,
    ///
    QRectF m_titleBlockArea;

    ///
    /// \brief m_language is the selected language of the template, it structure is
    /// <ISO 639 language code>_<ISO 3166 country code>, examples: de_at, en_us or en_gb
    ///
    QString m_language = "none";

    ///
    /// \brief m_languages is a list of all available languages
    ///
    QList<QString> m_languages = { "none" };
};

#endif // TITLEBLOCK_H
