#include "svgdraw.h"
#include "qdebug.h"
#include "qpoint.h"

SvgDraw::SvgDraw() { }

void SvgDraw::drawLine(const QPointF &start, const QPointF &end, double lineWidth)
{
    QDomElement obj = m_document.createElement("line");
    obj.setAttribute("x1", QString::number(start.x()) + m_svgUnit);
    obj.setAttribute("y1", QString::number(start.y()) + m_svgUnit);
    obj.setAttribute("x2", QString::number(end.x()) + m_svgUnit);
    obj.setAttribute("y2", QString::number(end.y()) + m_svgUnit);
    obj.setAttribute("style", "stroke:black;stroke-width:" + QString::number(lineWidth));
    m_root.appendChild(obj);
}

void SvgDraw::drawLine(const QLineF &line, double lineWidth)
{
    drawLine(line.p1(), line.p2(), lineWidth);
}

void SvgDraw::drawRect(const QPointF &start, const QPointF &end, double lineWidth, bool fill)
{
    QDomElement obj = m_document.createElement("rect");
    obj.setAttribute("x", QString::number(start.x()) + m_svgUnit);
    obj.setAttribute("y", QString::number(start.y()) + m_svgUnit);
    obj.setAttribute("width", QString::number(end.x() - start.x()) + m_svgUnit);
    obj.setAttribute("height", QString::number(end.y() - start.y()) + m_svgUnit);
    QString fillString = "none";
    if (fill) {
        fillString = "black";
    }
    obj.setAttribute("style",
                     "fill:" + fillString + ";stroke:black;stroke-width:"
                             + QString::number(lineWidth) + m_svgUnit);
    m_root.appendChild(obj);
}

void SvgDraw::drawRect(const QRectF &rect, double lineWidth, bool fill)
{
    drawRect(rect.topLeft(), rect.bottomRight(), lineWidth, fill);
}

void SvgDraw::drawPoly(const QPointF &position, const QList<QPointF> &points, double lineWidth, bool fill)
{
    QString pointsString = "";
    foreach (QPointF point, points) {
        pointsString += QString::number(position.x() + point.x()) /* + m_svgUnit*/ + ","
                + QString::number(position.y() + point.y()) /* + m_svgUnit*/ + " ";
    }
    QDomElement obj = m_document.createElement("polygon");
    obj.setAttribute("points", pointsString);
    QString style = "fill:black;stroke:black;stroke-width:";
    if (!fill) {
        style = "fill:none;stroke:black;stroke-width:";
    }
    obj.setAttribute("style", style + QString::number(lineWidth) + m_svgUnit);
    m_root.appendChild(obj);
}

void SvgDraw::drawPoly(const QPolygonF &poly, double lineWidth, bool fill)
{
    drawPoly(QPointF{ 0, 0 }, poly, lineWidth, fill);
}

void SvgDraw::drawCircle(const QPointF &center, double radius, double lineWidth, bool fill)
{
    QDomElement obj = m_document.createElement("circle");
    obj.setAttribute("cx", QString::number(center.x()) + m_svgUnit);
    obj.setAttribute("cy", QString::number(center.y()) + m_svgUnit);
    obj.setAttribute("r", QString::number(radius) + m_svgUnit);
    QString fillString = "none";
    if (fill) {
        fillString = "black";
    }
    obj.setAttribute("fill", fillString);
    obj.setAttribute("style",
                     "stroke:black;stroke-width:" + QString::number(lineWidth) + m_svgUnit);
    m_root.appendChild(obj);
}

void SvgDraw::drawText(const QPointF &position, const QString &text, double textSize,
                       TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                       double lineWidth, const QString &font, const QString &name, bool isEditable)
{
    // Skip editable fields for plain SVG when showEditable=false (used to produce "empty" templates)
    if (isEditable && !this->showEditable()) {
        return;
    }

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

    QDomElement obj = m_document.createElement("text");
    obj.setAttribute("x", QString::number(posX) + m_svgUnit);
    obj.setAttribute("y", QString::number(posY) + m_svgUnit);
    obj.setAttribute("style",
                     "fill: #000000; stroke: none; font-family: " + font
                             + "; font-size: " + QString::number(textSize * m_svgTextScaler)
                             + m_svgUnit + "; text-anchor: " + anchorString + ";");
    obj.appendChild(m_document.createTextNode(text));
    m_root.appendChild(obj);
}

void SvgDraw::drawPicture(const QString &picturePath, const QPointF &position, double width, double height,
                          int dpiVector)
{
    double resulutionPMM = dpiVector * (1 / 25.4);
    if (picturePath.endsWith(".svg")) {
        // QSvgRenderer renderer(picturePath);
        // QSize size = renderer.defaultSize();

        // Read file
        QFile file(picturePath);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            qWarning() << "Cannot read file" << file.errorString();
            exit(0);
        }

        QDomDocument xmlBOM;
        xmlBOM.setContent(&file);
        QDomElement root = xmlBOM.documentElement();

        double scale = width / root.attribute("width").remove("mm").toDouble();
        double widthSvg = scale * root.attribute("width").remove("mm").toDouble();
        double heightSvg = scale * root.attribute("height").remove("mm").toDouble();

        if (heightSvg > height) {
            scale = height / root.attribute("height").remove("mm").toDouble();
            widthSvg = scale * root.attribute("width").remove("mm").toDouble();
            heightSvg = scale * root.attribute("height").remove("mm").toDouble();
        }

        QDomNamedNodeMap nodes = root.attributes();
        QStringList names;

        // create list of standard added namspaces
        QStringList rootNnames;
        rootNnames.append("xmlns:freecad");
        rootNnames.append("xmlns:dc");
        rootNnames.append("xmlns:cc");
        rootNnames.append("xmlns:rdf");
        rootNnames.append("xmlns:svg");
        rootNnames.append("xmlns:xlink");
        rootNnames.append("xmlns");

        // Add missing Namespaces
        for (int i = 0; i < nodes.count(); i++) {
            QString name = nodes.item(i).toAttr().name();
            names.append(name);
            if (name.contains("xmlns") && !(rootNnames.contains(name))) {
                m_root.setAttribute(name, root.attribute(name));
            }
        }

        // Remove Attributs
        int i = 0;
        foreach (QString name, names) {
            root.removeAttribute(name);
            i++;
        }

        // Rename and add transfom Attribute
        root.setTagName("g");
        root.setAttribute("transform",
                          "translate(" + QString::number(position.x() - widthSvg) + m_svgUnit + " "
                                  + QString::number(position.y() - heightSvg) + m_svgUnit
                                  + ") scale(" + QString::number(scale) + ")");

        // Add to the document
        m_root.appendChild(root);
    } else if (picturePath.endsWith(".png")) {

        QImage image(picturePath);

        QPixmap qtPixmap;
        qtPixmap.load(picturePath, "PNG");

        // Prepare a QImage with desired characteritisc
        double widthCalc = width;

        int heightPx = qtPixmap.height();
        double heightCalc = heightPx / (qtPixmap.width() / widthCalc); // px/mm

        if (heightCalc > height) {
            heightCalc = height;
            widthCalc = qtPixmap.width() / (qtPixmap.height() / heightCalc); // 2400dpi to p/mm
        }

        QBuffer buffer;
        QSvgGenerator svgGen(QSvgGenerator::SvgVersion::SvgTiny12);
        svgGen.setOutputDevice(&buffer);
        // svgGen.setFileName("abc.svg");
        QPainter painter(&svgGen);

        QRectF target(QPointF{ position.x() - widthCalc, position.y() - heightCalc },
                      QSizeF(widthCalc, heightCalc));
        // Draw the Logo
        painter.drawImage(target, image);

        painter.end();

        QString data = buffer.data();

        int endId = data.indexOf("<image");

        data = data.remove(0, endId);

        int startId = data.indexOf("</g>");

        data = data.remove(startId, data.length() - 1);

        QDomDocument xmlBOM;
        xmlBOM.setContent(data);
        QDomElement root = xmlBOM.documentElement();
        root.setAttribute("preserveAspectRatio", "xMinYMin meet");

        m_root.appendChild(root);
    }
}

bool SvgDraw::start()
{
    m_file = std::shared_ptr<QFile>(new QFile(this->fileName()));
    if (m_file->open(QIODeviceBase::WriteOnly)) {
        m_file->write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
        m_xmlTextstream = std::shared_ptr<QTextStream>(new QTextStream(m_file.get()));
        m_root = m_document.createElement("svg");
        m_root.setAttribute("xmlns:freecad",
                            "http://www.freecadweb.org/wiki/index.php?title=Svg_Namespace");
        m_root.setAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
        m_root.setAttribute("xmlns:cc", "http://creativecommons.org/ns#");
        m_root.setAttribute("xmlns:rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
        m_root.setAttribute("xmlns:svg", "http://www.w3.org/2000/svg");
        m_root.setAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");
        m_root.setAttribute("xmlns", "http://www.w3.org/2000/svg");
        m_root.setAttribute("version", "1.1");
        m_root.setAttribute("id", "svg2");
        m_root.setAttribute("width", QString::number(this->width()) + "mm");
        m_root.setAttribute("height", QString::number(this->height()) + "mm");
        m_root.setAttribute("viewBox",
                            "0 0 " + QString::number(this->width()) + m_svgUnit + " "
                                    + QString::number(this->height()) + m_svgUnit);

        m_document.appendChild(m_root);
        return true;
    } else {
        qCritical() << "Could not open File";
        return false;
    }
}

bool SvgDraw::end()
{
    QString out = m_document.toString();
    // out = out.simplified();

    while (out.contains("\n ")) {
        out = out.replace("\n ", "\n");
    }

    *m_xmlTextstream << out;
    // FILE->write(")\n");
    m_xmlTextstream->flush();
    bool ret = m_file->flush();
    m_file->close();
    return ret;
}

const std::shared_ptr<QFile> &SvgDraw::file() const
{
    return m_file;
}

const QDomDocument &SvgDraw::document() const
{
    return m_document;
}
