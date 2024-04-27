#include "titleblock.h"

TitleBlock::TitleBlock()
{
    setTitleBlockArea(QRect{ 0, 0, 0, 0 });
}

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
    qInfo() << "TitleBlock None, into: " << into.get();
    qInfo() << "TitleBlock None, On What: " << onWhat;
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

QList<QString> TitleBlock::languages() const
{
    return m_languages;
}

void TitleBlock::setLanguages(const QList<QString> &newLanguages)
{
    m_languages = newLanguages;
}

QString TitleBlock::language() const
{
    return m_language;
}

void TitleBlock::setLanguage(const QString &newLanguage)
{
    if (m_languages.contains(newLanguage)) {
        m_language = newLanguage;
    }
}
