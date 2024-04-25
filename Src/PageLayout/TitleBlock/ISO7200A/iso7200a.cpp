#include "iso7200a.h"

#include <QPointF>

ISO7200A::ISO7200A()
{
    setType("ISO7200 Style A");
    setDescription("A ISO7200 conform style from the Book \"Mechanical and Metal Trades Handbook\" "
                   "ISBN: 978-3-8085-1915-8");
    setTitleBlockArea(QRectF{ 0, 0, 180, 39.84 });
    setLanguages(QList<QString>{ "en_gb" }); //, "de_at" });
    setLanguage("en_gb");
    initLanguages();
}

void ISO7200A::draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat)
{
    setTitleBlockArea(QRectF{ where.bottomRight() - QPointF{ 180, 39.84 }, where.bottomRight() });
    into->drawRect(titleBlockArea(), .7);

    m_currentLanguage = m_languageTexts[language()];
    qDebug() << language() << "::" << m_currentLanguage["TechnicalReference"].text;
    ;

    // Grid
    // Horizontal
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x(), titleBlockArea().topLeft().y() + 9.74 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 9.74 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 70.79,
                     titleBlockArea().topLeft().y() + 19.48 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 19.48 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 131.29,
                     titleBlockArea().topLeft().y() + 29.22 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 29.22 },
            .5);
    // Vertical
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 28, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 28, titleBlockArea().topLeft().y() + 9.71 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 70.79, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 70.79, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 113.58, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 113.58,
                     titleBlockArea().topLeft().y() + 9.71 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 131.29,
                     titleBlockArea().topLeft().y() + 9.71 },
            QPointF{ titleBlockArea().topLeft().x() + 131.29, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 160.8, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 160.8,
                     titleBlockArea().topLeft().y() + 9.71 },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 143.1,
                     titleBlockArea().topLeft().y() + 29.13 },
            QPointF{ titleBlockArea().topLeft().x() + 143.1, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 162.28,
                     titleBlockArea().topLeft().y() + 29.13 },
            QPointF{ titleBlockArea().topLeft().x() + 162.28, titleBlockArea().bottomRight().y() },
            .5);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 171.14,
                     titleBlockArea().topLeft().y() + 29.13 },
            QPointF{ titleBlockArea().topLeft().x() + 171.14, titleBlockArea().bottomRight().y() },
            .5);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["ResponsibleDepartment"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 8.5 },
            m_currentLanguage["ResponsibleDepartment"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "ResponsibleDepartment", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 30, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["TechnicalReference"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 30, titleBlockArea().topLeft().y() + 8.5 },
            m_currentLanguage["TechnicalReference"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "TechnicalReference", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 72.79, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["Creator"].lable, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 72.79, titleBlockArea().topLeft().y() + 8.5 },
            m_currentLanguage["Creator"].text, 2.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .25, "osifont", "Creator", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 115.58, titleBlockArea().topLeft().y() + 1 },
            m_currentLanguage["ApprovalPerson"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 115.58,
                            titleBlockArea().topLeft().y() + 8.5 },
                   m_currentLanguage["ApprovalPerson"].text, 2.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .25, "osifont", "ApprovalPerson", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 162.8, titleBlockArea().topLeft().y() + 8.5 },
            m_currentLanguage["ClassificationKeyWords"].text, 2.5, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .25, "osifont", "ClassificationKeyWords", true);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 2, titleBlockArea().topLeft().y() + 10.71 },
            m_currentLanguage["LegalOwner"].lable, 1.8, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 35.395, titleBlockArea().topLeft().y() + 16 },
            QList<QString>{ m_currentLanguage["LegalOwner"].text,
                            m_currentLanguage["LegalOwner"].text,
                            m_currentLanguage["LegalOwner"].text },
            5, TextHeightAnchor::Top, TextWidthAnchor::Center, .5, "osifont", "LegalOwner", true);

    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 72.79,
                            titleBlockArea().topLeft().y() + 10.71 },
                   m_currentLanguage["DocumentType"].lable, 1.8, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .18);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 72.79,
                            titleBlockArea().topLeft().y() + 18.21 },
                   m_currentLanguage["DocumentType"].text, 2.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .25, "osifont", "DocumentType", true);

    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 133.29,
                            titleBlockArea().topLeft().y() + 10.71 },
                   m_currentLanguage["DocumentStatus"].lable, 1.8, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .18);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 133.29,
                            titleBlockArea().topLeft().y() + 18.21 },
                   m_currentLanguage["DocumentStatus"].text, 2.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .25, "osifont", "DocumentStatus", true);

    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 72.79,
                            titleBlockArea().topLeft().y() + 21.42 },
                   m_currentLanguage["Title"].lable, 1.8, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .18);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 72.79, titleBlockArea().topLeft().y() + 28 },
            m_currentLanguage["Title"].text, 3.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .35, "osifont", "Title", true);
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 72.79, titleBlockArea().topLeft().y() + 37 },
            QList<QString>{ m_currentLanguage["SupplementaryTitle"].text,
                            m_currentLanguage["SupplementaryTitle"].text },
            2.5, TextHeightAnchor::Bottom, TextWidthAnchor::Left, .25, "osifont",
            "SupplementaryTitle", true);

    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 133.29,
                            titleBlockArea().topLeft().y() + 21.42 },
                   m_currentLanguage["IdentificationNumber"].lable, 1.8, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .18);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 133.29,
                            titleBlockArea().topLeft().y() + 27.92 },
                   m_currentLanguage["IdentificationNumber"].text, 2.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .25, "osifont", "IdentificationNumber", true);

    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 133.29,
                            titleBlockArea().topLeft().y() + 31.13 },
                   m_currentLanguage["RevisionIndex"].lable, 1.8, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .18);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 133.29,
                            titleBlockArea().topLeft().y() + 37.63 },
                   m_currentLanguage["RevisionIndex"].text, 2.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .25, "osifont", "RevisionIndex", true);

    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 145.1,
                            titleBlockArea().topLeft().y() + 31.13 },
                   m_currentLanguage["DateOfIssue"].lable, 1.8, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .18);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 145.1,
                            titleBlockArea().topLeft().y() + 37.63 },
                   m_currentLanguage["DateOfIssue"].text, 2.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .25, "osifont", "DateOfIssue", true);

    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 164.28,
                            titleBlockArea().topLeft().y() + 31.13 },
                   m_currentLanguage["LanguageCode"].lable, 1.8, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .18);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 164.28,
                            titleBlockArea().topLeft().y() + 37.63 },
                   m_currentLanguage["LanguageCode"].text, 2.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .25, "osifont", "LanguageCode", true);

    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 173.14,
                            titleBlockArea().topLeft().y() + 31.13 },
                   m_currentLanguage["SheetNumber"].lable, 1.8, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .18);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 173.14,
                            titleBlockArea().topLeft().y() + 37.63 },
                   m_currentLanguage["SheetNumber"].text, 1.8, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .18, "osifont", "SheetNumber", true);
}

void ISO7200A::initLanguages()
{
    QMap<QString, ISO7200ATextStruct> en_gb = {
        { "ResponsibleDepartment", ISO7200ATextStruct{ "Resp. dept.", "AB 131" } },
        { "TechnicalReference", ISO7200ATextStruct{ "Technical reference.", "Susan Miller" } },
        { "Creator", ISO7200ATextStruct{ "Created by", "Kristin Brown" } },
        { "ApprovalPerson", ISO7200ATextStruct{ "Approved by", "John Davis" } },
        { "ClassificationKeyWords", ISO7200ATextStruct{ "", "42A" } },
        { "LegalOwner", ISO7200ATextStruct{ "Legal owner", "John Smith Co." } },
        { "DocumentType", ISO7200ATextStruct{ "Type of document", "Assembly drawing" } },
        { "DocumentStatus", ISO7200ATextStruct{ "Document status", "released" } },
        { "Title", ISO7200ATextStruct{ "Title, additional title", "Circular saw shaft" } },
        { "SupplementaryTitle", ISO7200ATextStruct{ "", "complete with bearing" } },
        { "IdentificationNumber", ISO7200ATextStruct{ "Drawing number", "A225-03300-012" } },
        { "RevisionIndex", ISO7200ATextStruct{ "Changes", "A" } },
        { "DateOfIssue", ISO7200ATextStruct{ "Release date", "2014-01-15" } },
        { "LanguageCode", ISO7200ATextStruct{ "L.", "en" } },
        { "SheetNumber", ISO7200ATextStruct{ "Sheet", "1/3" } }
    };
    m_languageTexts.insert("en_gb", en_gb);
}
