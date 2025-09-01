#include "titleblock.h"

TitleBlock::TitleBlock()
{
    setTitleBlockArea(QRect{ 0, 0, 0, 0 });
}

const QString &TitleBlock::type() const
{
    return m_type;
}

void TitleBlock::setType(const QString &newType)
{
    m_type = newType;
}

const QString &TitleBlock::description() const
{
    return m_description;
}

void TitleBlock::draw(const std::shared_ptr<UniversalDraw> &into, const QRectF &where, const QPageLayout &onWhat)
{
    qInfo() << "TitleBlock None, into: " << into.get();
    qInfo() << "TitleBlock None, On What: " << onWhat;
}

void TitleBlock::setDescription(const QString &newDescription)
{
    m_description = newDescription;
}

const QRectF &TitleBlock::titleBlockArea() const
{
    return m_titleBlockArea;
}

void TitleBlock::setTitleBlockArea(const QRectF &newTitleBlockArea)
{
    m_titleBlockArea = newTitleBlockArea;
}

const QList<QString> &TitleBlock::languages() const
{
    return m_languages;
}

void TitleBlock::setLanguages(const QList<QString> &newLanguages)
{
    m_languages = newLanguages;
}

void TitleBlock::initLanguages()
{

}

const QString &TitleBlock::font() const
{
    return m_font;
}

void TitleBlock::setFont(const QString &newFont)
{
    m_font = newFont;
}

const QString &TitleBlock::language() const
{
    return m_language;
}

void TitleBlock::setLanguage(const QString &newLanguage)
{
    if (m_languages.contains(newLanguage)) {
        m_language = newLanguage;
    }
}
