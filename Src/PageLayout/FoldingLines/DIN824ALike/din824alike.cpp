#include "din824alike.h"

DIN824ALike::DIN824ALike()
{
    setType("DIN 824 A Like");
    setDescription(
            "This creates folding lines where the algorithm is based on the DIN 824 standard");
}

void DIN824ALike::draw(std::shared_ptr<UniversalDraw> into, QPageLayout onWhat)
{
    double len = 0; // length of the remaining block
    int num = 0; // number of blocks
    do {
        num++;
        len = (onWhat.fullRect(QPageLayout::Millimeter).width()
               - toWhat().fullRect(QPageLayout::Millimeter).width())
                / num;
    } while (len > 190 || num % 2 != 0);

    for (int i = 1; i <= num; i++) {
        drawVerFoldLine(into, onWhat, 20 + len * i, depth(), .35);
    }

    if (onWhat.fullRect(QPageLayout::Millimeter).height() > 297) {
        into->drawLine(QPointF{ 105, 0 }, QPointF{ 105, depth() }, .35);
    }

    // Horizontal
    double indexHeight = onWhat.fullRect(QPageLayout::Millimeter).height()
            - toWhat().fullRect(QPageLayout::Millimeter).height();
    while (indexHeight > 0) {
        drawHorFoldLine(into, onWhat, indexHeight, depth(), .35);
        indexHeight -= toWhat().fullRect(QPageLayout::Millimeter).height();
    }
}
