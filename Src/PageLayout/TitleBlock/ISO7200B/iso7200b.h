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
    virtual void draw(const std::shared_ptr<UniversalDraw> &into, const QRectF &where,
                      const QPageLayout &onWhat) override;

    // Same field keys as ISO7200A are used (subset rendered):
    // ResponsibleDepartment, TechnicalReference, Creator, DocumentType,
    // DocumentStatus, LegalOwner, Title, SupplementaryTitle, IdentificationNumber,
    // ApprovalPerson, RevisionIndex, DateOfIssue, LanguageCode, SheetNumberNumbers.
    // Differences vs. A:
    // - Block height is 27 mm (180 x 27 mm) and grid differs (narrower top rows).
    // - Picture area (if used) is smaller and placed left-of-right edge compared to A.

    // QString picturePath() const;
    // void setPicturePath(const QString &newPicturePath);

protected:
    ///
    /// \brief initLanguages initialises the Languages map(m_languageTexts)
    ///
    void initLanguages() override;

    ///
    /// \brief m_picturePath is the Path to a Picture, if it is a walyed path to a picture(.svg or
    /// .png) than it is drawn.
    ///
    // QString m_picturePath = "";
};

#endif // ISO7200B_H
