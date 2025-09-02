#include "freecadsvg.h"

FreeCADSvg::FreeCADSvg() { }

void FreeCADSvg::drawText(const QPointF &position, const QString &text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, const QString &font, const QString &name, bool isEditable)
{
    // Compute SVG text-anchor and baseline adjustments
    QString anchorString = "";
    double posX = position.x();
    double posY = position.y();

    if (textWidthAnchor == TextWidthAnchor::Left) {
        anchorString = "start";
    } else if (textWidthAnchor == TextWidthAnchor::Center) {
        anchorString = "middle";
    } else if (textWidthAnchor == TextWidthAnchor::Right) {
        anchorString = "end";
    }

    if (textHeightAnchor == TextHeightAnchor::Top) {
        posY += textSize;
    } else if (textHeightAnchor == TextHeightAnchor::Middle) {
        posY += (textSize / 2);
    } else if (textHeightAnchor == TextHeightAnchor::Bottom) {
    }

    if (isEditable) {
        // Editable fields get freecad:editable set to the field name
        QDomElement obj = m_document.createElement("text");
        obj.setAttribute("x", QString::number(posX));
        obj.setAttribute("y", QString::number(posY));
        obj.setAttribute("freecad:editable", name);
        obj.setAttribute("style",
                         "fill: #000000; stroke: none; font-family: " + font + "; font-size: "
                                 + QString::number(textSize * (1 + double(7) / 18))
                                 + "; text-anchor: " + anchorString + ";");

        // FreeCAD auto-fill attribute mapping (adds freecad:autofill where applicable)
        QList<QString> keyWords = {
            "SheetNumberNumbers", "LegalOwner", "DateOfIssue",  "Title", "Scale",
            "Creator",           "SheetNumber", "NumberOfPages"
        };

        if (keyWords.contains(name)) {
            if (name == "SheetNumberNumbers") {
                obj.setAttribute("freecad:autofill", "sheet");
            } else if (name == "SheetNumber") {
                obj.setAttribute("freecad:autofill", "page_number");
            } else if (name == "NumberOfPages") {
                obj.setAttribute("freecad:autofill", "page_count");
            } else if (name == "LegalOwner") {
                obj.setAttribute("freecad:autofill", "organization");
            } else if (name == "DateOfIssue") {
                obj.setAttribute("freecad:autofill", "date");
            } else if (name == "Title") {
                obj.setAttribute("freecad:autofill", "title");
            } else if (name == "Scale") {
                obj.setAttribute("freecad:autofill", "scale");
            } else if (name == "Creator") {
                obj.setAttribute("freecad:autofill", "author");
            }
        }
    // Actual text content is nested in a tspan for compatibility
    QDomElement obj2 = m_document.createElement("tspan");
        obj2.setAttribute("x", QString::number(posX));
        obj2.setAttribute("y", QString::number(posY));
        obj2.setAttribute("style",
                          "fill: #000000; stroke: none; font-family: " + font + "; font-size: "
                                  + QString::number(textSize * (1 + double(7) / 18))
                                  + "; text-anchor: " + anchorString + ";");
        obj2.appendChild(m_document.createTextNode(text));
        obj.appendChild(obj2);
        m_root.appendChild(obj);
    } else {
        QDomElement obj = m_document.createElement("text");
        obj.setAttribute("x", QString::number(posX));
        obj.setAttribute("y", QString::number(posY));
        obj.setAttribute("style",
                         "fill: #000000; stroke: none; font-family: " + font + "; font-size: "
                                 + QString::number(textSize * (1 + double(7) / 18))
                                 + "; text-anchor: " + anchorString + ";");
        obj.appendChild(m_document.createTextNode(text));
        m_root.appendChild(obj);
    }
}
