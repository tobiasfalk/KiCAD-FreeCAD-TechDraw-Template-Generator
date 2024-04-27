#include "iso7200a.h"

#include <QPointF>

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

void ISO7200A::draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat)
{
    setTitleBlockArea(QRectF{ where.bottomRight() - QPointF{ 180, 36 }, where.bottomRight() });
    into->drawRect(titleBlockArea(), .7);

    m_currentLanguage = m_languageTexts[language()];

    // Grid
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
    // Vertical
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

    // Text
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["ResponsibleDepartment"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["ResponsibleDepartment"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "ResponsibleDepartment", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 28, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["TechnicalReference"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 28, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["TechnicalReference"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "TechnicalReference", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["Creator"].lable, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["Creator"].text, 2.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .25, "osifont", "Creator", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 115, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["ApprovalPerson"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 115, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["ApprovalPerson"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "ApprovalPerson", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 158, titleBlockArea().topLeft().y() + 7.5 },
            m_currentLanguage["ClassificationKeyWords"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "ClassificationKeyWords", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["LegalOwner"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 34.5, titleBlockArea().topLeft().y() + 14 },
            QList<QString>{ m_currentLanguage["LegalOwner"].text,
                            m_currentLanguage["LegalOwner"].text,
                            m_currentLanguage["LegalOwner"].text },
            5, TextHeightAnchor::Top, TextWidthAnchor::Center, .5, "osifont", "LegalOwner", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["DocumentType"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 16.5 },
            m_currentLanguage["DocumentType"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "DocumentType", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 10 },
            m_currentLanguage["DocumentStatus"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 16.5 },
            m_currentLanguage["DocumentStatus"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "DocumentStatus", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["Title"].lable, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 26 },
            m_currentLanguage["Title"].text, 3.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .35, "osifont", "Title", true);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 71, titleBlockArea().topLeft().y() + 28 },
            QList<QString>{ m_currentLanguage["SupplementaryTitle"].text,
                            m_currentLanguage["SupplementaryTitle"].text },
            2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, .25, "osifont", "SupplementaryTitle",
            true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 19 },
            m_currentLanguage["IdentificationNumber"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 25.5 },
            m_currentLanguage["IdentificationNumber"].text, 3.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .35, "osifont", "IdentificationNumber", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["RevisionIndex"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 131, titleBlockArea().topLeft().y() + 34.5 },
            m_currentLanguage["RevisionIndex"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "RevisionIndex", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 138, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["DateOfIssue"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 138, titleBlockArea().topLeft().y() + 34.5 },
            m_currentLanguage["DateOfIssue"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "DateOfIssue", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 163, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["LanguageCode"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 163, titleBlockArea().topLeft().y() + 34.5 },
            m_currentLanguage["LanguageCode"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "LanguageCode", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 173, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["PageNumberNumbers"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 173, titleBlockArea().topLeft().y() + 34.5 },
            m_currentLanguage["PageNumberNumbers"].text, 1.8, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .18, "osifont", "PageNumberNumbers", true);
}

void ISO7200A::initLanguages()
{
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
        { "PageNumberNumbers", ISO7200ATextStruct{ "Sheet", "1/3" } }
    };
    m_languageTexts.insert("en_gb", en_gb);
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
        { "PageNumberNumbers", ISO7200ATextStruct{ "Blatt", "1/3" } }
    };
    m_languageTexts.insert("de_at", de_at);
}
