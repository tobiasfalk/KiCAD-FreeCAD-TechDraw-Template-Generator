#include "universaldraw.h"

#include <QDebug>

UniversalDraw::UniversalDraw() { }

void UniversalDraw::drawLine(QPointF start, QPointF end, double lineWidth)
{
    qInfo() << "UniversalDraw::drawLine(QPointF start(" << start << "), QPointF end(" << end << "), double lineWidth(" << lineWidth << "))";
}

void UniversalDraw::drawLine(QLineF line, double lineWidth)
{
    qInfo() << "UniversalDraw::drawLine(QLineF line(" << line << "), double lineWidth(" << lineWidth << "))";
}

void UniversalDraw::drawRect(QPointF start, QPointF end, double lineWidth, bool fill)
{
    qInfo() << "UniversalDraw::drawRect(QPointF start("<< start << "), QPointF end(" << end << "), double lineWidth("<< lineWidth <<"), bool fill("<< fill <<"))";
}

void UniversalDraw::drawRect(QRectF rect, double lineWidth, bool fill)
{
    qInfo() << "UniversalDraw::drawRect(QRectF rect(" << rect << "), double lineWidth("<< lineWidth <<"), bool fill("<< fill <<"))";
}

void UniversalDraw::drawPoly(QPointF position, QList<QPointF> points, double lineWidth, bool fill)
{
    qInfo() << "UniversalDraw::drawPoly(QPointF position(" << position << "), QList<QPointF> points(" << points << "), double lineWidth(" << lineWidth << "), bool fill("<< fill <<"))";
}

void UniversalDraw::drawPoly(QPolygonF poly, double lineWidth, bool fill)
{
    qInfo() << "UniversalDraw::drawPoly(QPolygonF poly(" << poly << "), double lineWidth(" << lineWidth << "), bool fill(" << fill << "))";
}

void UniversalDraw::drawCircle(QPointF center, double radius, double lineWidth, bool fill)
{
    qInfo() << "UniversalDraw::drawCircle(QPointF center(" << center << "), double radius(" << radius << "), double lineWidth(" << lineWidth << "), bool fill(" << fill << "))";
}

void UniversalDraw::drawText(QPointF position, QString text, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, QString font, bool isEditable, QString name)
{
    qInfo() << "UniversalDraw::drawText(QPointF position(" << position << "), QString text(" << text << "), double textSize(" << textSize << "), TextHeightAnchor textHeightAnchor(" << int(textHeightAnchor) << "), TextWidthAnchor textWidthAnchor(" << int(textWidthAnchor) << "), double lineWidth(" << lineWidth << "), QString font(" << font << "), bool isEditable(" << isEditable << "), QString name(" << name << "))";
}

void UniversalDraw::drawPicture(QString picturePath, QPointF position, double width, double hight)
{
    qInfo() << "UniversalDraw::drawPicture(QString picturePath(" << picturePath << "), QPointF position(" << position << "), double width(" << width << "), double hight(" << hight << "))";
}

QString UniversalDraw::fileName() const
{
    return m_fileName;
}

void UniversalDraw::setFileName(const QString &newFileName)
{
    m_fileName = newFileName;
}

qreal UniversalDraw::hight() const
{
    return m_hight;
}

void UniversalDraw::setHight(qreal newHight)
{
    m_hight = newHight;
}

qreal UniversalDraw::width() const
{
    return m_width;
}

void UniversalDraw::setWidth(qreal newWidth)
{
    m_width = newWidth;
}

auto operator<<(QDebug debug, const UniversalDraw &style) -> QDebug
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "UniversalDraw(" << ")";
    return debug;
}

void test::printTest(std::shared_ptr<UniversalDraw> drawer)
{
    drawer->setHight(210);
    drawer->setWidth(297);

    drawer->drawLine(QPointF{0, 0}, QPointF{297, 210}, .5);
    drawer->drawLine(QLineF{0, 210, 297, 0}, 3);

    drawer->drawCircle(QPointF{297/2, 210/2}, 50, 1);

    drawer->drawRect(QPointF{20, 20}, QPointF{30, 30}, .3);

    drawer->drawPoly(QPointF{40, 40}, QList<QPointF>{QPointF(0,0),QPointF(0,10),QPointF(10,10),QPointF(10,5),QPointF(5,5),QPointF(5,0)}, .8, true);

    drawer->drawText(QPointF{60, 10}, "TextABCabc", 3, TextHeightAnchor::Bottom, TextWidthAnchor::Left, .3, "osifont", true, "testText1");
    drawer->drawText(QPointF{60, 20}, "TextABCabc", 5, TextHeightAnchor::Bottom, TextWidthAnchor::Left, .5, "osifont");
    drawer->drawText(QPointF{60, 20}, "TextABCabc", 1, TextHeightAnchor::Bottom, TextWidthAnchor::Left, .1, "osifont");

}
// }
