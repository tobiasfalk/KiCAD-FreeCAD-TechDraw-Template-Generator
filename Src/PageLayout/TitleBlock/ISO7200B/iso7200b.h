#ifndef ISO7200B_H
#define ISO7200B_H

#include "PageLayout/TitleBlock/titleblock.h"
#include "PageLayout/TitleBlock/ISO7200A/iso7200a.h"

///
/// \brief The ISO7200B class draws a ISO 7200 conform title-block
///
class ISO7200B : public ISO7200A
{
public:
    ///
    /// \brief ISO7200B is the base constructor
    ///
    ISO7200B();

    ///
    /// \brief draw draws the title-block into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param where the rectangle where the title-block is drawn in to(typically the drawing area
    /// of the frame)
    /// \param onWhat is the page layout the frame is to be draw on, this is to get
    /// the name for example
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QRectF where,
                      QPageLayout onWhat) override;

    QString picturePath() const;
    void setPicturePath(const QString &newPicturePath);

protected:
    ///
    /// \brief initLanguages initialises the Languages map(m_languageTexts)
    ///
    void initLanguages() override;

    ///
    /// \brief m_picturePath is the Path to a Picture, if it is a walyed path to a picture(.svg or
    /// .png) than it is drawn.
    ///
    QString m_picturePath = "";
};

#endif // ISO7200B_H
