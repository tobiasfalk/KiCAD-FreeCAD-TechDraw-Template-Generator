#ifndef FREECADA_H
#define FREECADA_H

#include "PageLayout/TitleBlock/titleblock.h"
#include "PageLayout/TitleBlock/ISO7200A/iso7200a.h"

///
/// \brief The FreeCADA class draws a FreeCAD-styled ISO 7200 title block variant
///
class FreeCADA : public ISO7200A
{
public:
    ///
    /// \brief FreeCADA the base constructor
    ///
    FreeCADA();

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

    // Field keys used by this FreeCAD-like layout:
    // Creator, DateOfIssue, Title, SupplementaryTitle, Size, UnnamedA, UnnamedB,
    // Scale, Weight, IdentificationNumber, SheetNumberNumbers, Disclaimer, A..G.
    // Notes:
    // - Fixed size 140.35 x 47 mm, bottom-right anchored.
    // - Right side has stacked cells labeled A..G with separate label and value.
    // - Uses the same UniversalDraw semantics (editable flags honored by backends).

protected:
    ///
    /// \brief initLanguages initialises the Languages map(m_languageTexts)
    ///
    void initLanguages() override;
};

#endif // FREECADA_H
