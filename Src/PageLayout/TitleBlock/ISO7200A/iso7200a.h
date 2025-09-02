#ifndef ISO7200A_H
#define ISO7200A_H

#include "PageLayout/TitleBlock/titleblock.h"

typedef TitleBlockTextStruct ISO7200ATextStruct;

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
    virtual void draw(const std::shared_ptr<UniversalDraw> &into, const QRectF &where,
                      const QPageLayout &onWhat) override;

    // Field keys used in this title block (for mapping and backends):
    // ResponsibleDepartment, TechnicalReference, Creator, ApprovalPerson,
    // ClassificationKeyWords, LegalOwner, DocumentType, DocumentStatus,
    // Title, SupplementaryTitle, IdentificationNumber, RevisionIndex,
    // DateOfIssue, LanguageCode, SheetNumberNumbers.
    // Notes:
    // - Coordinates are in millimeters; origin for this block is set to the
    //   bottom-right corner of the given 'where' rect minus the block size
    //   (180 x 36 mm). All grid lines and text anchors are relative to that.
    // - The optional picture (m_picturePath) is drawn inside the block if the
    //   referenced file exists (supports .svg and .png via UniversalDraw).

    const QMap<QString, ISO7200ATextStruct> &currentLanguage() const;
    void setCurrentLanguage(const QMap<QString, ISO7200ATextStruct> &newCurrentLanguage);
    void updateCurrentLanguage();
    ///
    /// \brief setLanguage sets the to be used, if it is not part of m_languages than it does
    /// nothing
    /// \param newLanguage
    ///
    virtual void setLanguage(const QString &newLanguage) override;

    const std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> &languageTexts() const;
    void setLanguageTexts(const std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>>
                                  &newLanguageTexts);

    const QString &picturePath() const;
    void setPicturePath(const QString &newPicturePath);

protected:
    //   Key/varName, values

    ///
    /// \brief initLanguages initialises the Languages map(m_languageTexts)
    ///
    virtual void initLanguages() override;

    ///
    /// \brief m_picturePath is the Path to a Picture, if it is a waled path to a picture(.svg or
    /// .png) than it is drawn.
    ///
    QString m_picturePath = "";

private:
};

#endif // ISO7200A_H
