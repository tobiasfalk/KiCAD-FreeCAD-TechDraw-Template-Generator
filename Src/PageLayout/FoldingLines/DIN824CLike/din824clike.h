#ifndef DIN824CLIKE_H
#define DIN824CLIKE_H
#include <memory>

#include <QRectF>

#include <QObject>

#include <QDebug>

#include "UniversalDraw/universaldraw.h"

#include "PageLayout/FoldingLines/foldinglines.h"

///
/// \brief The DIN824CLike class creates folding lines where the algorithm is based on the DIN 824
/// standard
///
class DIN824CLike : public FoldingLines
{
public:
    ///
    /// \brief DIN824CLike the base constructor
    ///
    DIN824CLike();

    ///
    /// \brief draw draws the folding lines into the given drawer and into the given rectangle
    /// \param into the universal drawer that is drawn in to
    /// \param onWhat is the page layout the folding lines is to be draw on
    ///
    virtual void draw(std::shared_ptr<UniversalDraw> into, QPageLayout onWhat) override;
};

#endif // DIN824CLIKE_H
