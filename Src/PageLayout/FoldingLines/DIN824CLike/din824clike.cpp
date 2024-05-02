#include "din824clike.h"

DIN824CLike::DIN824CLike()
{
    setType("DIN 824 C Like");
    setDescription(
            "This creates folding lines where the algorithm is based on the DIN 824 standard");
}

void DIN824CLike::draw(std::shared_ptr<UniversalDraw> into, QPageLayout onWhat)
{
    double len = onWhat.fullRect(QPageLayout::Millimeter).width();
    while ((len -= toWhat().fullRect(QPageLayout::Millimeter).width()) > 0) {
        drawVerFoldLine(into, onWhat, len, depth(), .35);
    }
    // Horizontal
    double indexHeight = onWhat.fullRect(QPageLayout::Millimeter).height()
            - toWhat().fullRect(QPageLayout::Millimeter).height();
    while (indexHeight > 0) {
        drawHorFoldLine(into, onWhat, indexHeight, depth(), .35);
        indexHeight -= toWhat().fullRect(QPageLayout::Millimeter).height();
    }
}
