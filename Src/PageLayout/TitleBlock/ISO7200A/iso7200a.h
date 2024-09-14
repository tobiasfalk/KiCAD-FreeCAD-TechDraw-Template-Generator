#ifndef ISO7200A_H
#define ISO7200A_H

#include "PageLayout/TitleBlock/titleblock.h"

///
/// \brief The ISO7200ATextStruct struct is used to link a lable to a given Text
///
struct ISO7200ATextStruct
{
    QString lable;
    QString text;
    bool isEditable = true;
};

///
/// \brief The ISO7200A class draws a ISO 7200 conform title-block
///
class ISO7200A : public TitleBlock
{
public:
    ///
    /// \brief ISO7200A is the base constructor
    ///
    ISO7200A();

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

    QMap<QString, ISO7200ATextStruct> currentLanguage() const;
    void setCurrentLanguage(const QMap<QString, ISO7200ATextStruct> &newCurrentLanguage);
    void updateCurrentLanguage();
    ///
    /// \brief setLanguage sets the to be used, if it is not part of m_languages than it does
    /// nothing
    /// \param newLanguage
    ///
    virtual void setLanguage(const QString &newLanguage) override;

    std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> languageTexts() const;
    void setLanguageTexts(const std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>>
                                  &newLanguageTexts);

    QString picturePath() const;
    void setPicturePath(const QString &newPicturePath);

protected:
    //   Key/varName, values
    ///
    /// \brief m_currentLanguage is the Map with the current language texts
    ///
    QMap<QString, ISO7200ATextStruct> m_currentLanguage;

    ///
    /// \brief m_languageText a map with all the language texts
    ///
    std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> m_languageTexts =
            std::make_shared<QMap<QString, QMap<QString, ISO7200ATextStruct>>>();

    ///
    /// \brief initLanguages initialises the Languages map(m_languageTexts)
    ///
    virtual void initLanguages();

    ///
    /// \brief m_picturePath is the Path to a Picture, if it is a waled path to a picture(.svg or
    /// .png) than it is drawn.
    ///
    QString m_picturePath = "";

private:
};

#endif // ISO7200A_H
