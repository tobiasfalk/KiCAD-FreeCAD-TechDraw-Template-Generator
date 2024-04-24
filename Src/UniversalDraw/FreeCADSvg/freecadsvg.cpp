#include "freecadsvg.h"

FreeCADSvg::FreeCADSvg() { }

void FreeCADSvg::drawText(QPointF position, QString text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, QString font, QString name, bool isEditable)
{
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
        QDomElement obj = m_document.createElement("text");
        obj.setAttribute("x", QString::number(posX));
        obj.setAttribute("y", QString::number(posY));
        obj.setAttribute("freecad:editable", name);
        obj.setAttribute("style",
                         "fill: #000000; stroke: none; font-family: " + font + "; font-size: "
                                 + QString::number(textSize * (1 + double(7) / 18))
                                 + "; text-anchor: " + anchorString + ";");
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
