#include "svgdraw.h"
#include "qdebug.h"
#include "qpoint.h"

SvgDraw::SvgDraw() { }

void SvgDraw::drawLine(QPointF start, QPointF end, double lineWidth)
{
    QDomElement obj = m_document.createElement("line");
    obj.setAttribute("x1", QString::number(start.x()));
    obj.setAttribute("y1", QString::number(start.y()));
    obj.setAttribute("x2", QString::number(end.x()));
    obj.setAttribute("y2", QString::number(end.y()));
    obj.setAttribute("style", "stroke:black;stroke-width:" + QString::number(lineWidth));
    m_root.appendChild(obj);
}

void SvgDraw::drawLine(QLineF line, double lineWidth)
{
    drawLine(line.p1(), line.p2(), lineWidth);
}

void SvgDraw::drawRect(QPointF start, QPointF end, double lineWidth, bool fill)
{
    QDomElement obj = m_document.createElement("rect");
    obj.setAttribute("x", QString::number(start.x()));
    obj.setAttribute("y", QString::number(start.y()));
    obj.setAttribute("width", QString::number(end.x() - start.x()));
    obj.setAttribute("height", QString::number(end.y() - start.y()));
    QString fillString = "none";
    if (fill) {
        fillString = "black";
    }
    obj.setAttribute("style",
                     "fill:" + fillString
                             + ";stroke:black;stroke-width:" + QString::number(lineWidth));
    m_root.appendChild(obj);
}

void SvgDraw::drawRect(QRectF rect, double lineWidth, bool fill)
{
    drawRect(rect.topLeft(), rect.bottomRight(), lineWidth, fill);
}

void SvgDraw::drawPoly(QPointF position, QList<QPointF> points, double lineWidth, bool fill)
{
    QString pointsString = "";
    foreach (QPointF point, points) {
        pointsString += QString::number(position.x() + point.x()) + ","
                + QString::number(position.y() + point.y()) + " ";
    }
    QDomElement obj = m_document.createElement("polygon");
    obj.setAttribute("points", pointsString);
    QString style = "fill:black;stroke:black;stroke-width:";
    if (!fill) {
        style = "fill:none;stroke:black;stroke-width:";
    }
    obj.setAttribute("style", style + QString::number(lineWidth));
    m_root.appendChild(obj);
}

void SvgDraw::drawPoly(QPolygonF poly, double lineWidth, bool fill)
{
    drawPoly(QPointF{ 0, 0 }, poly, lineWidth, fill);
}

void SvgDraw::drawCircle(QPointF center, double radius, double lineWidth, bool fill)
{
    QDomElement obj = m_document.createElement("circle");
    obj.setAttribute("cx", QString::number(center.x()));
    obj.setAttribute("cy", QString::number(center.y()));
    obj.setAttribute("r", QString::number(radius));
    QString fillString = "none";
    if (fill) {
        fillString = "black";
    }
    obj.setAttribute("fill", fillString);
    obj.setAttribute("style", "stroke:black;stroke-width:" + QString::number(lineWidth));
    m_root.appendChild(obj);
}

void SvgDraw::drawText(QPointF position, QString text, double textSize,
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

    QDomElement obj = m_document.createElement("text");
    obj.setAttribute("x", QString::number(posX));
    obj.setAttribute("y", QString::number(posY));
    obj.setAttribute("style",
                     "fill: #000000; stroke: none; font-family: " + font
                             + "; font-size: " + QString::number(textSize * (1 + double(7) / 18))
                             + "; text-anchor: " + anchorString + ";");
    obj.appendChild(m_document.createTextNode(text));
    m_root.appendChild(obj);
}

void SvgDraw::drawPicture(QString picturePath, QPointF position, double width, double height,
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
        qDebug() << "Scale: " << scale;

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
            qDebug() << "i: " << i << " Name: " << name
                     << " exists:" << (name.contains("xmlns") && !(rootNnames.contains(name)));
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
                          "translate(" + QString::number(position.x()) + " "
                                  + QString::number(position.y()) + ") scale("
                                  + QString::number(scale) + ")");

        // Add to the document
        m_root.appendChild(root);
    } else if (picturePath.endsWith(".png")) {
        qDebug() << "Nope";

        // int pngEndPid = picturePath.lastIndexOf("/");
        // if (pngEndPid == -1) {
        //     pngEndPid = picturePath.lastIndexOf("\\");
        // }

        // QString pngName = picturePath;
        // pngName = pngName.remove(0, pngEndPid + 1);
        // QString destPath = "./" + this->fileName().remove(".svg") + "_svg_" + pngName;

        // qDebug() << "Copy: " << QFile::copy(picturePath, destPath) << "::" << picturePath
        //          << "::" << destPath;

        // QDomElement obj = m_document.createElement("image");
        // obj.setAttribute("x", QString::number(position.x()));
        // obj.setAttribute("y", QString::number(position.y()));
        // obj.setAttribute("width", QString::number(width));
        // obj.setAttribute("height", QString::number(height));
        // obj.setAttribute("preserveAspectRatio", "xMinYMin meet");
        // obj.setAttribute("xlink:href", destPath);
        // m_root.appendChild(obj);

        QImage image(picturePath);
        // image.fill(0x00FFFFFF); // partly transparent background

        // Get QPainter that paints to the image

        // QByteArray ba;
        // QBuffer buffer(&ba);
        // buffer.open(QIODevice::WriteOnly);
        // image.save(&buffer, "PNG");

        // QDomElement obj = m_document.createElement("line");
        // obj.setAttribute("width", QString::number(width));
        // obj.setAttribute("height", QString::number(height));
        // obj.setAttribute("preserveAspectRatio", "xMinYMin meet");
        // obj.setAttribute("xlink:href", "data:image/png;base64," + ba);
        // m_root.appendChild(obj);

        QPixmap qtPixmap;
        qtPixmap.load(picturePath, "PNG");

        // Prepare a QImage with desired characteritisc
        // int widthPx = qtPixmap.width(); // 24mm bei 2400dpi(KiCAD scale 0.125)
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

        QRectF target(position, QSizeF(widthCalc, heightCalc));
        // Draw the Logo
        painter.drawImage(target, image);

        painter.end();

        // qDebug() << "Buffer: " << buffer.data();

        QString data = buffer.data();
        // qDebug() << "Data Org: " << data;

        int endId = data.indexOf("<image");

        data = data.remove(0, endId);

        int startId = data.indexOf("</g>");

        data = data.remove(startId, data.length() - 1);

        // qDebug() << "A";
        // qDebug() << "Data: " << data;
        // qDebug() << "B";

        // data.replace("preserveAspectRatio=\"none\"", "preserveAspectRatio=\"xMinYMin meet\"");

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
                            "0 0 " + QString::number(this->width()) + " "
                                    + QString::number(this->height()));

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

std::shared_ptr<QFile> SvgDraw::file() const
{
    return m_file;
}

QDomDocument SvgDraw::document() const
{
    return m_document;
}
