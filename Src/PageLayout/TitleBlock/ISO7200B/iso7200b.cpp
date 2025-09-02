#include "iso7200b.h"

#include <QFileDialog>

ISO7200B::ISO7200B()
{
    setType("ISO7200 Style B");
    setDescription("A ISO7200 conform style from the Book \"Leiterplatten Stromlaufplan, Layout "
                   "und Fertigung\" ISBN: 978-3-446-47583-0; it is also an example out of the ISO "
                   "7200 Standard");
    setTitleBlockArea(QRectF{ 0, 0, 180, 27 });
    setLanguages(QList<QString>{ "en_gb", "de_de" }); //
    setLanguage("de_at");
    initLanguages();
}

void ISO7200B::draw(const std::shared_ptr<UniversalDraw> &into, const QRectF &where, const QPageLayout &onWhat)
{
        // ISO7200 style B variant: fixed size 180 x 27 mm, bottom-right anchored.
        setTitleBlockArea(QRectF{ where.bottomRight() - QPointF{ 180, 27 }, where.bottomRight() });
        into->drawRect(titleBlockArea(), .7);

    m_currentLanguage = m_languageTexts->value(language());

        // Grid: two main rows (0-9, 9-18) and lower row (18-27) with narrow right cells.
    // Horizontal
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x(), titleBlockArea().topLeft().y() + 9 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 9 }, .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 30, titleBlockArea().topLeft().y() + 18 },
            QPointF{ titleBlockArea().topLeft().x() + 69, titleBlockArea().topLeft().y() + 18 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 129, titleBlockArea().topLeft().y() + 18 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 18 }, .5);
    // Vertical
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 30, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 30, titleBlockArea().bottomRight().y() }, .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 69, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 69, titleBlockArea().bottomRight().y() }, .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 129, titleBlockArea().topLeft().y() + 9 },
            QPointF{ titleBlockArea().topLeft().x() + 129, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 136, titleBlockArea().topLeft().y() + 18 },
            QPointF{ titleBlockArea().topLeft().x() + 136, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 135, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 135, titleBlockArea().topLeft().y() + 9 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 161, titleBlockArea().topLeft().y() + 18 },
            QPointF{ titleBlockArea().topLeft().x() + 161, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 171, titleBlockArea().topLeft().y() + 18 },
            QPointF{ titleBlockArea().topLeft().x() + 171, titleBlockArea().bottomRight().y() },
            .5);

        // Text: similar keys as style A but arranged for the shorter height.
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["ResponsibleDepartment"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["ResponsibleDepartment"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "ResponsibleDepartment", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 32, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["TechnicalReference"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 32, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["TechnicalReference"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "TechnicalReference", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["DocumentType"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["DocumentType"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "DocumentType", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 137, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["DocumentStatus"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 137, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["DocumentStatus"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "DocumentStatus", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["LegalOwner"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 14 },
            QList<QString>{ m_currentLanguage["LegalOwner"].text,
                            m_currentLanguage["LegalOwner"].text,
                            m_currentLanguage["LegalOwner"].text },
            2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, .25, font(), "LegalOwner", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 32, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["Creator"].lable, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 32, titleBlockArea().topLeft().y() + 16.5 },
            m_currentLanguage["Creator"].text, 2.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .25, font(), "Creator", true);

    // into->drawText(
    //         QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 10 },
    //         m_currentLanguage["Title"].lable, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left,
    //         .18 , font());
    // into->drawText(
    //         QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 14 },
    //         m_currentLanguage["Title"].text, 5, TextHeightAnchor::Top, TextWidthAnchor::Left, .5,
    //         "osifont", "Title", true);
    // into->drawText(
    //         QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 21 },
    //         m_currentLanguage["SupplementaryTitle"].text, 2.5, TextHeightAnchor::Top,
    //         TextWidthAnchor::Left, .25, font(), "SupplementaryTitle", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["Title"].lable, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 17 },
            m_currentLanguage["Title"].text, 3.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .35, font(), "Title", true);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 19 },
            QList<QString>{ m_currentLanguage["SupplementaryTitle"].text,
                            m_currentLanguage["SupplementaryTitle"].text },
            2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, .25, font(), "SupplementaryTitle",
            true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["IdentificationNumber"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 154.5,
                            titleBlockArea().topLeft().y() + 16.5 },
                   m_currentLanguage["IdentificationNumber"].text, 3.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Center, .35, font(), "IdentificationNumber", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 32, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["ApprovalPerson"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 32, titleBlockArea().topLeft().y() + 25.5 },
            m_currentLanguage["ApprovalPerson"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "ApprovalPerson", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["RevisionIndex"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 25.5 },
            m_currentLanguage["RevisionIndex"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "RevisionIndex", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 138, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["DateOfIssue"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 138, titleBlockArea().topLeft().y() + 25.5 },
            m_currentLanguage["DateOfIssue"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "DateOfIssue", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 163, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["LanguageCode"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 163, titleBlockArea().topLeft().y() + 25.5 },
            m_currentLanguage["LanguageCode"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "LanguageCode", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 172, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["SheetNumberNumbers"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 172, titleBlockArea().topLeft().y() + 25.5 },
            m_currentLanguage["SheetNumberNumbers"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, font(), "SheetNumberNumbers", true);

        // Optional logo picture when available.
        if (QFileInfo::exists(m_picturePath)) {
        into->drawPicture(m_picturePath,
                          QPointF{ titleBlockArea().topLeft().x() + 28,
                                   titleBlockArea().bottomRight().y() - 2 },
                          26, 14);
    }
}

void ISO7200B::initLanguages()
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
        { "SheetNumberNumbers", ISO7200ATextStruct{ "Sheet", "100/300" } }
    };
    m_languageTexts->insert("en_gb", en_gb);
    QMap<QString, ISO7200ATextStruct> de_de = {
        { "ResponsibleDepartment", ISO7200ATextStruct{ "Verantwortl. Abt.", "AB 131" } },
        { "TechnicalReference", ISO7200ATextStruct{ "Techn. Referenz", "Susan Müller" } },
        { "Creator", ISO7200ATextStruct{ "Erstellt durch:", "Christian Schmid" } },
        { "ApprovalPerson", ISO7200ATextStruct{ "Genehmigt von:", "Wolfgang Maier" } },
        { "ClassificationKeyWords", ISO7200ATextStruct{ "", "42A" } },
        { "LegalOwner", ISO7200ATextStruct{ "Gesetzlicher Eigentümer", "Schuler AG Bergstadt" } },
        { "DocumentType", ISO7200ATextStruct{ "Dokumentenart", "Zusammenbauzeichnung" } },
        { "DocumentStatus", ISO7200ATextStruct{ "Documentenstatus", "freigegeben" } },
        { "Title", ISO7200ATextStruct{ "Titel", "Kreissägewelle" } },
        { "SupplementaryTitle", ISO7200ATextStruct{ "", "komplette mit Lagerung" } },
        { "IdentificationNumber", ISO7200ATextStruct{ "", "A225-03300-012" } },
        { "RevisionIndex", ISO7200ATextStruct{ "Änd.", "A" } },
        { "DateOfIssue", ISO7200ATextStruct{ "Ausgabedatum", "2014-01-15" } },
        { "LanguageCode", ISO7200ATextStruct{ "Spr.", "de" } },
        { "SheetNumberNumbers", ISO7200ATextStruct{ "Blatt", "1/3" } }
    };
    m_languageTexts->insert("de_de", de_de);
}

// QString ISO7200B::picturePath() const
// {
//     return m_picturePath;
// }

// void ISO7200B::setPicturePath(const QString &newPicturePath)
// {
//     m_picturePath = newPicturePath;
// }
