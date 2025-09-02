#include "iso7200a.h"

#include <QPointF>
#include <QFileInfo>

ISO7200A::ISO7200A()
{
    setType("ISO7200 Style A");
    setDescription("A ISO7200 conform style from the Book \"Mechanical and Metal Trades Handbook\" "
                   "ISBN: 978-3-8085-1915-8; it is also an example out of the ISO 7200 Standard");
    setTitleBlockArea(QRectF{ 0, 0, 180, 36 });
    setLanguages(QList<QString>{ "en_gb", "de_at" });
    setLanguage("en_gb");
    initLanguages();
}

void ISO7200A::draw(const std::shared_ptr<UniversalDraw> &into, const QRectF &where, const QPageLayout &onWhat)
{
        // Anchor the ISO7200A title block in the bottom-right corner of 'where'.
        // The block has a fixed size of 180 x 36 mm.
        setTitleBlockArea(QRectF{ where.bottomRight() - QPointF{ 180, 36 }, where.bottomRight() });
        into->drawRect(titleBlockArea(), .7); // outer border

    m_currentLanguage = m_languageTexts->value(language());

        // Grid: mimic ISO 7200 style A layout using horizontal and vertical lines.
        // Horizontal separations at y: 9, 18, 27 (from top of block).
    // Horizontal
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x(), titleBlockArea().topLeft().y() + 9 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 9 }, .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 69, titleBlockArea().topLeft().y() + 18 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 18 }, .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 129, titleBlockArea().topLeft().y() + 27 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 27 }, .5);
        // Vertical separations create columns for labels/values and right-side cells.
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 26, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 26, titleBlockArea().topLeft().y() + 9 }, .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 69, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 69, titleBlockArea().bottomRight().y() }, .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 113, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 113, titleBlockArea().topLeft().y() + 9 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 129, titleBlockArea().topLeft().y() + 9 },
            QPointF{ titleBlockArea().topLeft().x() + 129, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 156, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 156, titleBlockArea().topLeft().y() + 9 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 136, titleBlockArea().topLeft().y() + 27 },
            QPointF{ titleBlockArea().topLeft().x() + 136, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 161, titleBlockArea().topLeft().y() + 27 },
            QPointF{ titleBlockArea().topLeft().x() + 161, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 171, titleBlockArea().topLeft().y() + 27 },
            QPointF{ titleBlockArea().topLeft().x() + 171, titleBlockArea().bottomRight().y() },
            .5);

        // Text: labels (small, top-anchored) above values (editable by key).
        // Keys correspond to backend variable mapping (see header comment).
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["ResponsibleDepartment"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["ResponsibleDepartment"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "ResponsibleDepartment",
            m_currentLanguage["ResponsibleDepartment"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 28, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["TechnicalReference"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 28, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["TechnicalReference"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "TechnicalReference",
            m_currentLanguage["TechnicalReference"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["Creator"].lable, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["Creator"].text, 2.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .25, font(), "Creator", m_currentLanguage["Creator"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 115, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["ApprovalPerson"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 115, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["ApprovalPerson"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "ApprovalPerson",
            m_currentLanguage["ApprovalPerson"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 158, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["ClassificationKeyWords"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "ClassificationKeyWords",
            m_currentLanguage["ClassificationKeyWords"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["LegalOwner"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 14 },
            QList<QString>{ m_currentLanguage["LegalOwner"].text,
                            m_currentLanguage["LegalOwner"].text,
                            m_currentLanguage["LegalOwner"].text },
            5, TextHeightAnchor::Top, TextWidthAnchor::Left, .5, font(), "LegalOwner",
            m_currentLanguage["LegalOwner"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["DocumentType"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 16.5 },
            m_currentLanguage["DocumentType"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "DocumentType",
            m_currentLanguage["DocumentType"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["DocumentStatus"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 16.5 },
            m_currentLanguage["DocumentStatus"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "DocumentStatus",
            m_currentLanguage["DocumentStatus"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["Title"].lable, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 26 },
            m_currentLanguage["Title"].text, 3.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .35, font(), "Title", m_currentLanguage["Title"].isEditable);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 28 },
            QList<QString>{ m_currentLanguage["SupplementaryTitle"].text,
                            m_currentLanguage["SupplementaryTitle"].text },
            2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, .25, font(), "SupplementaryTitle",
            m_currentLanguage["SupplementaryTitle"].isEditable);

    // into->drawText(
    //         QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 19 },
    //         m_currentLanguage["IdentificationNumber"].lable, 1.8, TextHeightAnchor::Top,
    //         TextWidthAnchor::Left, .18);
    // into->drawText(
    //         QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 25.5
    //         }, m_currentLanguage["IdentificationNumber"].text, 3.5, TextHeightAnchor::Bottom,
    //         TextWidthAnchor::Left, .35, font(), "IdentificationNumber",
    //         m_currentLanguage["IdentificationNumber"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["IdentificationNumber"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 154.5,
                            titleBlockArea().topLeft().y() + 25.5 },
                   m_currentLanguage["IdentificationNumber"].text, 3.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Center, .35, font(), "IdentificationNumber",
                   m_currentLanguage["IdentificationNumber"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["RevisionIndex"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 34.5 },
            m_currentLanguage["RevisionIndex"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "RevisionIndex",
            m_currentLanguage["RevisionIndex"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 138, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["DateOfIssue"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 138, titleBlockArea().topLeft().y() + 34.5 },
            m_currentLanguage["DateOfIssue"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "DateOfIssue",
            m_currentLanguage["DateOfIssue"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 163, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["LanguageCode"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 163, titleBlockArea().topLeft().y() + 34.5 },
            m_currentLanguage["LanguageCode"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "LanguageCode",
            m_currentLanguage["LanguageCode"].isEditable);

    // into->drawText(
    //         QPointF{ titleBlockArea().topLeft().x() + 173, titleBlockArea().topLeft().y() + 28 },
    //         m_currentLanguage["SheetNumberNumbers"].lable, 1.8, TextHeightAnchor::Top,
    //         TextWidthAnchor::Left, .18);
    // into->drawText(
    //         QPointF{ titleBlockArea().topLeft().x() + 173, titleBlockArea().topLeft().y() + 34.5
    //         }, m_currentLanguage["SheetNumberNumbers"].text, 1.8, TextHeightAnchor::Bottom,
    //         TextWidthAnchor::Left, .18, font(), "SheetNumberNumbers",
    //         m_currentLanguage["SheetNumberNumbers"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 172, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["SheetNumberNumbers"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 172, titleBlockArea().topLeft().y() + 34.5 },
            m_currentLanguage["SheetNumberNumbers"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "SheetNumberNumbers",
            m_currentLanguage["SheetNumberNumbers"].isEditable);

        // Optional company logo or mark; drawn if file exists.
        if (QFileInfo::exists(m_picturePath)) {
        into->drawPicture(m_picturePath,
                          QPointF{ titleBlockArea().topLeft().x() + 67,
                                   titleBlockArea().bottomRight().y() - 2 },
                          65, 23);
    }
}

const QMap<QString, ISO7200ATextStruct> &ISO7200A::currentLanguage() const
{
        return m_currentLanguage;
}

void ISO7200A::setLanguage(const QString &newLanguage)
{
    TitleBlock::setLanguage(newLanguage);

    m_currentLanguage = m_languageTexts->value(language());
}

const std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> &ISO7200A::languageTexts() const
{
        return m_languageTexts;
}

void ISO7200A::setLanguageTexts(
        const std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> &newLanguageTexts)
{
    m_languageTexts = newLanguageTexts;
}

void ISO7200A::setCurrentLanguage(const QMap<QString, ISO7200ATextStruct> &newCurrentLanguage)
{
    m_currentLanguage = newCurrentLanguage;
}

void ISO7200A::updateCurrentLanguage()
{
    m_currentLanguage = m_languageTexts->value(language());
}

void ISO7200A::initLanguages()
{
    m_languageTexts->clear();
    QMap<QString, ISO7200ATextStruct> en_gb = {
        { "ResponsibleDepartment", ISO7200ATextStruct{ "Resp. dept.", "AB 131" } },
        { "TechnicalReference", ISO7200ATextStruct{ "Technical reference.", "Susan Müller" } },
        { "Creator", ISO7200ATextStruct{ "Created by", "Kristin Brown" } },
        { "ApprovalPerson", ISO7200ATextStruct{ "Approved by", "John Davis" } },
        { "ClassificationKeyWords", ISO7200ATextStruct{ "", "42A" } },
        { "LegalOwner", ISO7200ATextStruct{ "Legal owner", "John Smith Co." } },
        { "DocumentType", ISO7200ATextStruct{ "Type of document", "Assembly drawing" } },
        { "DocumentStatus", ISO7200ATextStruct{ "Document status", "released" } },
        { "Title", ISO7200ATextStruct{ "Title, additional title", "Circular saw shaft" } },
        { "SupplementaryTitle", ISO7200ATextStruct{ "", "complete with bearing" } },
        { "IdentificationNumber", ISO7200ATextStruct{ "", "A225-03300-012" } },
        { "RevisionIndex", ISO7200ATextStruct{ "Rev.", "A" } },
        { "DateOfIssue", ISO7200ATextStruct{ "Release date", "2014-01-15" } },
        { "LanguageCode", ISO7200ATextStruct{ "L.", "en" } },
        { "SheetNumberNumbers", ISO7200ATextStruct{ "Sheet", "1/3" } }
    };
    m_languageTexts->insert("en_gb", en_gb);
    QMap<QString, ISO7200ATextStruct> de_at = {
        { "ResponsibleDepartment", ISO7200ATextStruct{ "Verantwortl. Abteilung.", "AB 131" } },
        { "TechnicalReference", ISO7200ATextStruct{ "Technische Referenz", "Susan Müller" } },
        { "Creator", ISO7200ATextStruct{ "Erstellt durch", "Christian Schmid" } },
        { "ApprovalPerson", ISO7200ATextStruct{ "Genehmigt von", "Wolfgang Maier" } },
        { "ClassificationKeyWords", ISO7200ATextStruct{ "", "42A" } },
        { "LegalOwner", ISO7200ATextStruct{ "Gesetzlicher Eigentümer", "Schuler AG Bergstadt" } },
        { "DocumentType", ISO7200ATextStruct{ "Dokumentenart", "Zusammenbauzeichnung" } },
        { "DocumentStatus", ISO7200ATextStruct{ "Documentenstatus", "freigegeben" } },
        { "Title", ISO7200ATextStruct{ "Titel, Zusätzlicher Titel", "Kreissägewelle" } },
        { "SupplementaryTitle", ISO7200ATextStruct{ "", "komplette mit Lagerung" } },
        { "IdentificationNumber", ISO7200ATextStruct{ "", "A225-03300-012" } },
        { "RevisionIndex", ISO7200ATextStruct{ "Änd.", "A" } },
        { "DateOfIssue", ISO7200ATextStruct{ "Ausgabedatum", "2014-01-15" } },
        { "LanguageCode", ISO7200ATextStruct{ "Spr.", "de" } },
        { "SheetNumberNumbers", ISO7200ATextStruct{ "Blatt", "1/3" } }
    };
    m_languageTexts->insert("de_at", de_at);
}

const QString &ISO7200A::picturePath() const
{
        return m_picturePath;
}

void ISO7200A::setPicturePath(const QString &newPicturePath)
{
    m_picturePath = newPicturePath;
}
