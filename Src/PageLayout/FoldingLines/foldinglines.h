#ifndef FOLDINGLINES_H
#define FOLDINGLINES_H
#include <memory>

#include <QRectF>

#include <QObject>

#include <QDebug>

#include "UniversalDraw/universaldraw.h"

///
/// \brief The FoldingLines class is the base class for a folding line drawing algorithm
///
class FoldingLines
{
public:
    ///
    /// \brief FoldingLines the basic constructor
    ///
    FoldingLines();

    ///
    /// \brief draw draws the folding lines into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param onWhat is the page layout the folding lines is to be draw on
    ///
    virtual void draw(const std::shared_ptr<UniversalDraw> &into, const QPageLayout &onWhat);

    ///
    /// \brief depth returns the the length of the line from the border on in to the page
    /// \return
    ///
    ///
    /// \brief depth returns the length of the folding line from the border into the page
    /// \return the depth in mm
    ///
    double depth() const;
    ///
    /// \brief setDepth sets the the length of the line from the border on in to the page
    /// \param newDepth
    ///
    ///
    /// \brief setDepth sets the length of the folding line from the border into the page
    /// \param newDepth the new depth in mm
    ///
    void setDepth(double newDepth);

    ///
    /// \brief type returns the name/type of the folding line algorithm
    /// \return type name
    ///
    const QString &type() const;
    ///
    /// \brief setType sets the name/type of the folding line algorithm
    /// \param newType
    ///
    void setType(const QString &newType);

    ///
    /// \brief description returns a description for the folding line algorithm
    /// \return the description
    ///
    const QString &description() const;
    ///
    /// \brief setDescription sets the description for the folding line algorithm
    /// \param newDescription
    ///
    void setDescription(const QString &newDescription);

    ///
    /// \brief toWhat returns the page layout the page should be folded down to
    /// \return the target page layout
    ///
    const QPageLayout &toWhat() const;
    ///
    /// \brief setToWhat sets the page layout the page should be folded down to
    /// \param newToWhat the target page layout
    ///
    void setToWhat(const QPageLayout &newToWhat);

protected:
    ///
    /// \brief drawVerFoldLine draws two lines on the Top and Bottom of the page at position x
    /// \param into
    /// \param onWhat
    /// \param x
    /// \param depth line length from border into page (mm)
    /// \param width line width (mm)
    ///
    void drawVerFoldLine(const std::shared_ptr<UniversalDraw> &into, const QPageLayout &onWhat, double x,
                         double depth, double width);
    ///
    /// \brief drawHorFoldLine draws two lines on the Left and Right of the page at position y
    /// \param into
    /// \param onWhat
    /// \param y
    /// \param depth line length from border into page (mm)
    /// \param width line width (mm)
    ///
    void drawHorFoldLine(const std::shared_ptr<UniversalDraw> &into, const QPageLayout &onWhat, double y,
                         double depth, double width);

private:
    ///
    /// \brief m_type the type name of the FoldingLine algorithm
    ///
    QString m_type = "none";

    ///
    /// \brief m_description is a more detailed description of the FoldingLine algorithm, it is
    /// meant to be uses as a user Info or something similar
    ///
    QString m_description = "No Folding Lines at all";

    ///
    /// \brief m_depth is the the length of the line from the border on in to the page
    ///
    double m_depth = 5;

    ///
    /// \brief m_toWhat the page to what it should be folded down to
    ///
    QPageLayout m_toWhat = QPageLayout(
            QPageSize{ QSizeF{ 210, 297 }, QPageSize::Millimeter, "A4", QPageSize::ExactMatch },
            QPageLayout::Portrait, QMarginsF(0, 0, 0, 0));
};

#endif // FOLDINGLINES_H
