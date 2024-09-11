#include "htmldraw.h"

HtmlDraw::HtmlDraw()
{
    // m_svgTextScaler = .1;
    m_svgUnit = "px";
}

bool HtmlDraw::start()
{
    m_file = std::shared_ptr<QFile>(new QFile(this->fileName()));
    if (m_file->open(QIODeviceBase::WriteOnly)) {
        m_file->write("<!DOCTYPE html>\n");
        m_file->write("<html>\n");
        m_file->write("<body>\n");
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

bool HtmlDraw::end()
{
    QString out = m_document.toString();
    // out = out.simplified();

    while (out.contains("\n ")) {
        out = out.replace("\n ", "\n");
    }

    *m_xmlTextstream << out;
    // FILE->write(")\n");
    m_xmlTextstream->flush();

    m_file->write("</body>\n");
    m_file->write("</html>\n");

    bool ret = m_file->flush();
    m_file->close();
    return ret;
}
