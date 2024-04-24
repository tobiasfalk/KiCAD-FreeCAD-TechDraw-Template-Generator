#include "titleblock.h"

TitleBlock::TitleBlock() { }

QString TitleBlock::type() const
{
    return m_type;
}

void TitleBlock::setType(const QString &newType)
{
    m_type = newType;
}

QString TitleBlock::description() const
{
    return m_description;
}

void TitleBlock::draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat)
{
    qDebug() << "TitleBlock, into: " << into.get();
    qDebug() << "On What: " << onWhat;
}

void TitleBlock::setDescription(const QString &newDescription)
{
    m_description = newDescription;
}

QRectF TitleBlock::titleBlockArea() const
{
    return m_titleBlockArea;
}

void TitleBlock::setTitleBlockArea(const QRectF &newTitleBlockArea)
{
    m_titleBlockArea = newTitleBlockArea;
}
