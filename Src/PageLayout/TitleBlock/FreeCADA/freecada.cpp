#include "freecada.h"

#include <QPointF>
#include <QFileInfo>

FreeCADA::FreeCADA()
{
    setType("FreeCAD Style A");
    setDescription("Based on a FreeCAD template");
    setTitleBlockArea(QRectF{ 0, 0, 140.35, 47 });
    setLanguages(QList<QString>{ "en_gb", "de_at" });
    setLanguage("en_gb");
    initLanguages();
}

void FreeCADA::draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat)
{
    setTitleBlockArea(QRectF{ where.bottomRight() - QPointF{ 140.35, 47 }, where.bottomRight() });
    into->drawRect(titleBlockArea(), .35);

    m_currentLanguage = m_languageTexts->value(language());

    // Grid

    // Horizontal
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x(), titleBlockArea().topLeft().y() + 16.650 },
            QPointF{ titleBlockArea().topLeft().x() + 119,
                     titleBlockArea().topLeft().y() + 16.650 },
            .35);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x(), titleBlockArea().topLeft().y() + 29.650 },
            QPointF{ titleBlockArea().topLeft().x() + 119,
                     titleBlockArea().topLeft().y() + 29.650 },
            .35);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x(), titleBlockArea().topLeft().y() + 42.650 },
            QPointF{ titleBlockArea().topLeft().x() + 119,
                     titleBlockArea().topLeft().y() + 42.650 },
            .35);

    // G 3.325
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 119, titleBlockArea().topLeft().y() + 6.65 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 6.65 },
            .35);
    // F 9,985
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 119, titleBlockArea().topLeft().y() + 13.32 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 13.32 },
            .35);
    // E 16,655
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 119, titleBlockArea().topLeft().y() + 19.99 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 19.99 },
            .35);
    // D 23,32
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 119, titleBlockArea().topLeft().y() + 26.65 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 26.65 },
            .35);
    // C 29,985
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 119, titleBlockArea().topLeft().y() + 33.32 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 33.32 },
            .35);
    // B 36,655
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 119, titleBlockArea().topLeft().y() + 39.99 },
            QPointF{ titleBlockArea().bottomRight().x(), titleBlockArea().topLeft().y() + 39.99 },
            .35);
    // A 43,495
    // 47

    // Vertical
    into->drawLine(QPointF{ titleBlockArea().topLeft().x() + 17.5,
                            titleBlockArea().topLeft().y() + 16.825 },
                   QPointF{ titleBlockArea().topLeft().x() + 17.5,
                            titleBlockArea().topLeft().y() + 42.650 },
                   .35);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 38, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 38, titleBlockArea().topLeft().y() + 42.650 },
            .35);
    into->drawLine(QPointF{ titleBlockArea().topLeft().x() + 100,
                            titleBlockArea().topLeft().y() + 29.825 },
                   QPointF{ titleBlockArea().topLeft().x() + 100,
                            titleBlockArea().topLeft().y() + 42.650 },
                   .35);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 119, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 119, titleBlockArea().bottomRight().y() },
            .35);
    into->drawLine(
            QPointF{ titleBlockArea().topLeft().x() + 123.92, titleBlockArea().topLeft().y() },
            QPointF{ titleBlockArea().topLeft().x() + 123.92, titleBlockArea().bottomRight().y() },
            .35);

    // Text
    // Row 1
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 1.25, titleBlockArea().topLeft().y() + 1.5 },
            m_currentLanguage["Creator"].lable, 1.5, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .15, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 1.25, titleBlockArea().topLeft().y() + 7 },
            m_currentLanguage["Creator"].text, 3, TextHeightAnchor::Bottom, TextWidthAnchor::Left,
            .3, font(), "Creator", m_currentLanguage["Creator"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 1.25, titleBlockArea().topLeft().y() + 8.5 },
            m_currentLanguage["DateOfIssue"].lable, 1.5, TextHeightAnchor::Top,
            TextWidthAnchor::Left, .15, font());
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 1.25, titleBlockArea().topLeft().y() + 14 },
            m_currentLanguage["DateOfIssue"].text, 3, TextHeightAnchor::Bottom,
            TextWidthAnchor::Left, .3, font(), "DateOfIssue",
            m_currentLanguage["DateOfIssue"].isEditable);

    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 39.25, titleBlockArea().topLeft().y() + 1.5 },
            m_currentLanguage["Title"].text, 5, TextHeightAnchor::Top, TextWidthAnchor::Left, .5,
            font(), "Title", m_currentLanguage["Title"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 39.25,
                            titleBlockArea().topLeft().y() + 12.5 },
                   m_currentLanguage["SupplementaryTitle"].text, 3.5, TextHeightAnchor::Bottom,
                   TextWidthAnchor::Left, .35, font(), "SupplementaryTitle",
                   m_currentLanguage["SupplementaryTitle"].isEditable);

    // Row 2
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 1.25, titleBlockArea().topLeft().y() + 17.5 },
            m_currentLanguage["Size"].lable, 1.5, TextHeightAnchor::Top, TextWidthAnchor::Left, .15,
            font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 8.75,
                            titleBlockArea().topLeft().y() + 23.15 },
                   m_currentLanguage["Size"].text, 5, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .5, font(), "Size",
                   m_currentLanguage["Size"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 18.75,
                            titleBlockArea().topLeft().y() + 17.5 },
                   m_currentLanguage["UnnamedA"].lable, 1.5, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .15, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 27.75,
                            titleBlockArea().topLeft().y() + 23.15 },
                   m_currentLanguage["UnnamedA"].text, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font(), "UnnamedA",
                   m_currentLanguage["UnnamedA"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 39.25,
                            titleBlockArea().topLeft().y() + 17.5 },
                   m_currentLanguage["UnnamedB"].lable, 1.5, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .15, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 39.25,
                            titleBlockArea().topLeft().y() + 23.15 },
                   m_currentLanguage["UnnamedB"].text, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Left, .3, font(), "UnnamedB",
                   m_currentLanguage["UnnamedB"].isEditable);

    // Row 3
    into->drawText(
            QPointF{ titleBlockArea().topLeft().x() + 1.25, titleBlockArea().topLeft().y() + 30.5 },
            m_currentLanguage["Scale"].lable, 1.5, TextHeightAnchor::Top, TextWidthAnchor::Left,
            .15, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 8.75,
                            titleBlockArea().topLeft().y() + 36.15 },
                   m_currentLanguage["Scale"].text, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font(), "Scale",
                   m_currentLanguage["Scale"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 18.75,
                            titleBlockArea().topLeft().y() + 30.5 },
                   m_currentLanguage["Weight"].lable, 1.5, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .15, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 27.75,
                            titleBlockArea().topLeft().y() + 36.15 },
                   m_currentLanguage["Weight"].text, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font(), "Weight",
                   m_currentLanguage["Weight"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 39.25,
                            titleBlockArea().topLeft().y() + 30.5 },
                   m_currentLanguage["IdentificationNumber"].lable, 1.5, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .15, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 39.25,
                            titleBlockArea().topLeft().y() + 36.15 },
                   m_currentLanguage["IdentificationNumber"].text, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Left, .3, font(), "IdentificationNumber",
                   m_currentLanguage["IdentificationNumber"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 101.25,
                            titleBlockArea().topLeft().y() + 30.5 },
                   m_currentLanguage["PageNumberNumbers"].lable, 1.5, TextHeightAnchor::Top,
                   TextWidthAnchor::Left, .15, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 109.5,
                            titleBlockArea().topLeft().y() + 36.15 },
                   m_currentLanguage["PageNumberNumbers"].text, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font(), "PageNumberNumbers",
                   m_currentLanguage["PageNumberNumbers"].isEditable);

    // Disclaimer
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 1.25,
                            titleBlockArea().topLeft().y() + 44.825 },
                   m_currentLanguage["Disclaimer"].text, 1.5, TextHeightAnchor::Middle,
                   TextWidthAnchor::Left, .15, font(), "Disclaimer",
                   m_currentLanguage["Disclaimer"].isEditable);

    // ABC Side
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 121.46,
                            titleBlockArea().topLeft().y() + 3.325 },
                   m_currentLanguage["G"].lable, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 132.135,
                            titleBlockArea().topLeft().y() + 3.325 },
                   m_currentLanguage["G"].text, 3, TextHeightAnchor::Middle, TextWidthAnchor::Left,
                   .3, font(), "G", m_currentLanguage["G"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 121.46,
                            titleBlockArea().topLeft().y() + 9.985 },
                   m_currentLanguage["F"].lable, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 132.135,
                            titleBlockArea().topLeft().y() + 9.985 },
                   m_currentLanguage["F"].text, 3, TextHeightAnchor::Middle, TextWidthAnchor::Left,
                   .3, font(), "F", m_currentLanguage["F"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 121.46,
                            titleBlockArea().topLeft().y() + 16.655 },
                   m_currentLanguage["E"].lable, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 132.135,
                            titleBlockArea().topLeft().y() + 16.655 },
                   m_currentLanguage["E"].text, 3, TextHeightAnchor::Middle, TextWidthAnchor::Left,
                   .3, font(), "E", m_currentLanguage["E"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 121.46,
                            titleBlockArea().topLeft().y() + 23.32 },
                   m_currentLanguage["D"].lable, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 132.135,
                            titleBlockArea().topLeft().y() + 23.32 },
                   m_currentLanguage["D"].text, 3, TextHeightAnchor::Middle, TextWidthAnchor::Left,
                   .3, font(), "D", m_currentLanguage["D"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 121.46,
                            titleBlockArea().topLeft().y() + 29.985 },
                   m_currentLanguage["C"].lable, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 132.135,
                            titleBlockArea().topLeft().y() + 29.985 },
                   m_currentLanguage["C"].text, 3, TextHeightAnchor::Middle, TextWidthAnchor::Left,
                   .3, font(), "C", m_currentLanguage["C"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 121.46,
                            titleBlockArea().topLeft().y() + 36.655 },
                   m_currentLanguage["B"].lable, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 132.135,
                            titleBlockArea().topLeft().y() + 36.655 },
                   m_currentLanguage["B"].text, 3, TextHeightAnchor::Middle, TextWidthAnchor::Left,
                   .3, font(), "B", m_currentLanguage["B"].isEditable);
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 121.46,
                            titleBlockArea().topLeft().y() + 43.495 },
                   m_currentLanguage["A"].lable, 3, TextHeightAnchor::Middle,
                   TextWidthAnchor::Center, .3, font());
    into->drawText(QPointF{ titleBlockArea().topLeft().x() + 132.135,
                            titleBlockArea().topLeft().y() + 43.495 },
                   m_currentLanguage["A"].text, 3, TextHeightAnchor::Middle, TextWidthAnchor::Left,
                   .3, font(), "A", m_currentLanguage["A"].isEditable);

    // Picture
    if (QFileInfo::exists(m_picturePath)) {
        into->drawPicture(m_picturePath,
                          QPointF{ titleBlockArea().topLeft().x() + 117,
                                   titleBlockArea().topLeft().y() + 27.65 },
                          77, 9);
    }
}

void FreeCADA::initLanguages()
{
    m_languageTexts->clear();
    QMap<QString, ISO7200ATextStruct> en_gb = {
        { "Creator", ISO7200ATextStruct{ "DESIGNED BY:", "Designed by Name" } },
        { "DateOfIssue", ISO7200ATextStruct{ "DATE:", "Date" } },
        { "Title", ISO7200ATextStruct{ "", "Title" } },
        { "SupplementaryTitle", ISO7200ATextStruct{ "", "Subtitle" } },
        { "Size", ISO7200ATextStruct{ "SIZE:", "A4" } },
        { "UnnamedA", ISO7200ATextStruct{ "-:", "-" } },
        { "UnnamedB", ISO7200ATextStruct{ "-:", "-" } },
        { "Scale", ISO7200ATextStruct{ "SCALE:", "Scale" } },
        { "Weight", ISO7200ATextStruct{ "WEIGHT (kg):", "Weight" } },
        { "IdentificationNumber", ISO7200ATextStruct{ "DRAWING NUMBER:", "Drawing number" } },
        { "PageNumberNumbers", ISO7200ATextStruct{ "SHEET:", "Sheet" } },
        { "Disclaimer",
          ISO7200ATextStruct{ "",
                              "This drawing is our property; it can't be reproduced or "
                              "communicated without our written consent." } },
        { "A", ISO7200ATextStruct{ "A", "_" } },
        { "B", ISO7200ATextStruct{ "B", "_" } },
        { "C", ISO7200ATextStruct{ "C", "_" } },
        { "D", ISO7200ATextStruct{ "D", "_" } },
        { "E", ISO7200ATextStruct{ "E", "_" } },
        { "F", ISO7200ATextStruct{ "F", "_" } },
        { "G", ISO7200ATextStruct{ "G", "_" } },
    };
    m_languageTexts->insert("en_gb", en_gb);
    QMap<QString, ISO7200ATextStruct> de_de = {
        { "Creator", ISO7200ATextStruct{ "ERSTELLT DURCH:", "Designed by Name" } },
        { "DateOfIssue", ISO7200ATextStruct{ "DATUM:", "Date" } },
        { "Title", ISO7200ATextStruct{ "", "Title" } },
        { "SupplementaryTitle", ISO7200ATextStruct{ "", "Subtitle" } },
        { "Size", ISO7200ATextStruct{ "GRÖẞE:", "A4" } },
        { "UnnamedA", ISO7200ATextStruct{ "-:", "-" } },
        { "UnnamedB", ISO7200ATextStruct{ "-:", "-" } },
        { "Scale", ISO7200ATextStruct{ "MAẞSTAB:", "Scale" } },
        { "Weight", ISO7200ATextStruct{ "GEWICHT (kg):", "Weight" } },
        { "IdentificationNumber", ISO7200ATextStruct{ "ZEICHNUNGS NUMMER:", "Drawing number" } },
        { "PageNumberNumbers", ISO7200ATextStruct{ "BLATT:", "Sheet" } },
        { "Disclaimer",
          ISO7200ATextStruct{ "",
                              "This drawing is our property; it can't be reproduced or "
                              "communicated without our written consent." } },
        { "A", ISO7200ATextStruct{ "A", "_" } },
        { "B", ISO7200ATextStruct{ "B", "_" } },
        { "C", ISO7200ATextStruct{ "C", "_" } },
        { "D", ISO7200ATextStruct{ "D", "_" } },
        { "E", ISO7200ATextStruct{ "E", "_" } },
        { "F", ISO7200ATextStruct{ "F", "_" } },
        { "G", ISO7200ATextStruct{ "G", "_" } },
    };
    m_languageTexts->insert("de_de", de_de);
}
