#include "iso5457frame.h"

QStringList NumToABC(qint64 num)
{
    QStringList ret;
    num--;
    QList<QString> abc = { "A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M",
                           "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    QList<qint64> abcNum = { 0 };
    for (int i = 0; i < num; i++) {
        abcNum[0]++;
        for (int n = 0; n < abcNum.length(); n++) {
            if (abcNum[n] == 24 && n == abcNum.length() - 1) {
                abcNum[n] = 0;
                abcNum.append(0);
            } else if (abcNum[n] == 24) {
                abcNum[n] = 0;
                abcNum[n + 1]++;
            }
        }
    }

    foreach (qint64 i, abcNum) {
        ret.prepend(abc[i]);
    }
    return ret;
}

ISO5457Frame::ISO5457Frame()
{
    setType("ISO5457");
}

void ISO5457Frame::draw(std::shared_ptr<UniversalDraw> into, QRectF where, QPageLayout onWhat)
{
    setDrawingArea(QRectF{ QPointF{ 20, 10 }, QPointF{ where.width() - 10, where.height() - 10 } });
    // Inseid and Outseid Rectangal
    {
        into->drawRect(QPointF{ 15, 5 }, QPointF{ where.width() - 5, where.height() - 5 }, 0.35);
        into->drawRect(QPointF{ 20, 10 }, QPointF{ where.width() - 10, where.height() - 10 }, 0.7);
    }

    // draw Trimming Marks
    if (m_showTrimmingMarks) {

        QList<QPointF> trimmingMarkLT{ QPointF{ 0, 0 }, QPointF{ 10, 0 }, QPointF{ 10, 5 },
                                       QPointF{ 5, 5 }, QPointF{ 5, 10 }, QPointF{ 0, 10 } };
        QList<QPointF> trimmingMarkRT{ QPointF{ 0, 0 },  QPointF{ -10, 0 }, QPointF{ -10, 5 },
                                       QPointF{ -5, 5 }, QPointF{ -5, 10 }, QPointF{ 0, 10 } };
        QList<QPointF> trimmingMarkRB{ QPointF{ 0, 0 },   QPointF{ -10, 0 },  QPointF{ -10, -5 },
                                       QPointF{ -5, -5 }, QPointF{ -5, -10 }, QPointF{ 0, -10 } };
        QList<QPointF> trimmingMarkLB{ QPointF{ 0, 0 },  QPointF{ 10, 0 },  QPointF{ 10, -5 },
                                       QPointF{ 5, -5 }, QPointF{ 5, -10 }, QPointF{ 0, -10 } };
        into->drawPoly(QPointF{ 0, 0 }, trimmingMarkLT, 0, true);
        into->drawPoly(QPointF{ where.width(), 0 }, trimmingMarkRT, 0, true);
        into->drawPoly(QPointF{ where.width(), where.height() }, trimmingMarkRB, 0, true);
        into->drawPoly(QPointF{ 0, where.height() }, trimmingMarkLB, 0, true);
    }

    // Centermarks
    if (!noDrawingAreaIndent()) {
        if (m_topCenteringLines) {
            into->drawLine(QPointF{ where.width() / 2, 5 }, QPointF{ where.width() / 2, 20 }, 0.7);
        } else {
            into->drawLine(QPointF{ where.width() / 2, 5 }, QPointF{ where.width() / 2, 10 }, 0.7);
        }
        if (m_bottomCenteringLines) {
            into->drawLine(QPointF{ where.width() / 2, where.height() - 5 },
                           QPointF{ where.width() / 2, where.height() - 20 }, 0.7);
        } else {
            into->drawLine(QPointF{ where.width() / 2, where.height() - 5 },
                           QPointF{ where.width() / 2, where.height() - 10 }, 0.7);
        }

        if (m_leftCenteringLines) {
            into->drawLine(QPointF{ 15, where.height() / 2 }, QPointF{ 30, where.height() / 2 },
                           0.7);
        } else {
            into->drawLine(QPointF{ 15, where.height() / 2 }, QPointF{ 20, where.height() / 2 },
                           0.7);
        }
        if (m_rigthCenteringLines) {
            into->drawLine(QPointF{ where.width() - 5, where.height() / 2 },
                           QPointF{ where.width() - 20, where.height() / 2 }, 0.7);
        } else {
            into->drawLine(QPointF{ where.width() - 5, where.height() / 2 },
                           QPointF{ where.width() - 10, where.height() / 2 }, 0.7);
        }
    }

    // Top and Bottom Framegrid
    {
        double halfSheetWidth = where.width() / 2;
        // Lines
        qint64 index = 1;
        qint64 indexNumDigets = QString::number((int)(where.width() - 30) / 50).length();
        // Left
        double spaceLeft = 20 + 3.5;
        double lineX = halfSheetWidth - 50;
        QList<double> indexListLeft;
        double lastLine = lineX;
        while (lineX > spaceLeft) {
            // Top
            into->drawLine(QPointF{ lineX, 5 }, QPointF{ lineX, 10 }, 0.35);
            // Bottom
            into->drawLine(QPointF{ lineX, where.height() - 5 },
                           QPointF{ lineX, where.height() - 10 }, 0.35);
            lastLine = lineX;
            lineX -= 50;
            indexListLeft.prepend(lineX + 25);
        }

        // Left Text
        foreach (double pos, indexListLeft) {
            if (pos <= spaceLeft) {
                pos = 10 + (lastLine - 10) / 2;
            }
            into->drawText(QPointF{ pos, 7.5 }, QString::number(index), 3.5,
                           TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
            if (where.height() >= 297 && where.width() >= 297) {
                into->drawText(QPointF{ pos, where.height() - 7.5 }, QString::number(index), 3.5,
                               TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
            }
            index++;
        }

        // Middle Text
        //  Left
        into->drawText(QPointF{ halfSheetWidth - 25, 7.5 }, QString::number(index), 3.5,
                       TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
        if (where.height() >= 297 && where.width() >= 297) {
            into->drawText(QPointF{ halfSheetWidth - 25, where.height() - 7.5 },
                           QString::number(index), 3.5, TextHeightAnchor::Middle,
                           TextWidthAnchor::Center, 0.35, font());
        }
        index++;
        // Right
        into->drawText(QPointF{ halfSheetWidth + 25, 7.5 }, QString::number(index), 3.5,
                       TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
        if (where.height() >= 297 && where.width() >= 297) {
            into->drawText(QPointF{ halfSheetWidth + 25, where.height() - 7.5 },
                           QString::number(index), 3.5, TextHeightAnchor::Middle,
                           TextWidthAnchor::Center, 0.35, font());
        }
        index++;

        // Right
        double spaceRight = (double)10 + (3.5 * (double)indexNumDigets);
        double spaceRightBottom = (double)10 + (3.5 * onWhat.pageSize().name().length());
        double lastBottomLine = halfSheetWidth;
        double lastTopLine = halfSheetWidth;
        lineX = halfSheetWidth + 50;
        while (lineX < where.width()) {
            // Top
            if (lineX <= (double)where.width() - (double)spaceRight) {
                into->drawLine(QPointF{ lineX, 5 }, QPointF{ lineX, 10 }, 0.35);
                lastTopLine = lineX;
            }

            if (lineX >= (double)where.width() - (double)spaceRight - 50
                && lineX <= (double)where.width() - (double)spaceRight) {
                into->drawText(
                        QPointF{ lastTopLine + ((where.width() - 5) - lastTopLine) / 2, 7.5 },
                        QString::number(index), 3.5, TextHeightAnchor::Middle,
                        TextWidthAnchor::Center, 0.35, font());
            } else if (lineX + 25 <= where.width()) {
                into->drawText(QPointF{ lineX + 25, 7.5 }, QString::number(index), 3.5,
                               TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
            }
            // Bottom
            if (m_showPageSize) {
                if (lineX < where.width() - spaceRightBottom) {
                    into->drawLine(QPointF{ lineX, where.height() - 5 },
                                   QPointF{ lineX, where.height() - 10 }, 0.35);
                    lastBottomLine = lineX;
                }

                if (lineX >= where.width() - 55) {
                    into->drawText(QPointF{ lastBottomLine + (where.width() - lastBottomLine) / 2,
                                            where.height() - 7.5 },
                                   onWhat.pageSize().name(), 3.5, TextHeightAnchor::Middle,
                                   TextWidthAnchor::Center, 0.35, font());
                } else if (where.height() >= 297 && lineX < where.width() - spaceRightBottom - 50) {
                    into->drawText(QPointF{ lineX + 25, where.height() - 7.5 },
                                   QString::number(index), 3.5, TextHeightAnchor::Middle,
                                   TextWidthAnchor::Center, 0.35, font());
                }
            } else {
                if (lineX <= (double)where.width() - (double)spaceRight) {
                    into->drawLine(QPointF{ lineX, where.height() - 5 },
                                   QPointF{ lineX, where.height() - 10 }, 0.35);
                    lastTopLine = lineX;
                }

                if (where.height() >= 297 && where.width() >= 297 && where.height() >= 297
                    && lineX >= (double)where.width() - (double)spaceRight - 50
                    && lineX <= (double)where.width() - (double)spaceRight) {
                    into->drawText(QPointF{ lastTopLine + ((where.width() - 5) - lastTopLine) / 2,
                                            where.height() - 7.5 },
                                   QString::number(index), 3.5, TextHeightAnchor::Middle,
                                   TextWidthAnchor::Center, 0.35, font());
                } else if (where.height() >= 297 && where.width() >= 297
                           && lineX + 25 <= where.width()) {
                    into->drawText(QPointF{ lineX + 25, where.height() - 7.5 },
                                   QString::number(index), 3.5, TextHeightAnchor::Middle,
                                   TextWidthAnchor::Center, 0.35, font());
                }
            }
            lineX += 50;
            index++;
        }
    }

    // Left and Right Framgrid
    {
        double halfSheetHeight = where.height() / 2;
        // Lines
        qint64 index = 1;
        qint64 indexNumDigets = NumToABC((where.height() - 30) / 50).length();
        // Top
        double spaceTop = 10 + 3.5;
        double lineY = halfSheetHeight - 50;
        QList<double> indexListTop;
        double lastLine = lineY;
        while (lineY > spaceTop) {
            into->drawLine(QPointF{ 15, lineY }, QPointF{ 20, lineY }, 0.35);
            into->drawLine(QPointF{ where.width() - 5, lineY },
                           QPointF{ where.width() - 10, lineY }, 0.35);
            lastLine = lineY;
            lineY -= 50;
            indexListTop.prepend(lineY + 25);
        }

        foreach (double pos, indexListTop) {
            if (pos <= spaceTop) {
                pos = (10 + (lastLine - 10) / 2);
            }
            into->drawText(QPointF{ where.width() - 7.5, pos }, NumToABC(index), 3.5,
                           TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
            if (where.width() >= 297 && where.height() >= 297) {
                into->drawText(QPointF{ 17.5, pos }, NumToABC(index), 3.5, TextHeightAnchor::Middle,
                               TextWidthAnchor::Center, 0.35, font());
            }
            index++;
        }
        // Middle
        into->drawText(QPointF{ where.width() - 7.5, halfSheetHeight - 25 }, NumToABC(index), 3.5,
                       TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
        if (where.width() >= 297 && where.height() >= 297) {
            into->drawText(QPointF{ 17.5, halfSheetHeight - 25 }, NumToABC(index), 3.5,
                           TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
        }
        index++;
        into->drawText(QPointF{ where.width() - 7.5, halfSheetHeight + 25 }, NumToABC(index), 3.5,
                       TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
        if (where.width() >= 297 && where.height() >= 297) {
            into->drawText(QPointF{ 17.5, halfSheetHeight + 25 }, NumToABC(index), 3.5,
                           TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
        }
        index++;

        // Bottom
        double spaceBottom = 10 + (5.5 * indexNumDigets);
        lineY = halfSheetHeight + 50;
        while (lineY < where.height() - spaceBottom) {
            // Left
            double textY = 0;
            into->drawLine(QPointF{ 15, lineY }, QPointF{ 20, lineY }, 0.35);
            if (where.width() >= 297 && where.height() >= 297) {
                if (lineY > where.height() - 60) {
                    textY = lineY + ((where.height() - 10) - lineY) / 2;
                    into->drawText(QPointF{ 17.5, textY }, NumToABC(index), 3.5,
                                   TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
                } else {
                    into->drawText(QPointF{ 17.5, lineY + 25 }, NumToABC(index), 3.5,
                                   TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
                }
            }
            // Right
            if (lineY < where.height() - spaceBottom) {
                into->drawLine(QPointF{ where.width() - 5, lineY },
                               QPointF{ where.width() - 10, lineY }, 0.35);
            }
            if (lineY <= where.height() - 60) {
                into->drawText(QPointF{ where.width() - 7.5, lineY + 25 }, NumToABC(index), 3.5,
                               TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
            } else if (lineY > where.height() - 60) { //
                textY = lineY + ((where.height() - 10) - lineY) / 2;
                into->drawText(QPointF{ where.width() - 7.5, textY }, NumToABC(index), 3.5,
                               TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35, font());
            }
            lineY += 50;
            index++;
        }
    }
}

void ISO5457Frame::decideBottomAndTopCenteringLine(double TitleBlockWidth, double TitleBlockHeight,
                                                   QRectF where)
{
    qDebug() << "TitleBlockWidth: " << TitleBlockWidth;
    m_bottomCenteringLines = true;
    m_rigthCenteringLines = true;
    if (TitleBlockWidth > (where.width() - 20.0) / 2) {
        m_bottomCenteringLines = false;
        if (TitleBlockHeight > where.height() - 30) {
            m_topCenteringLines = false;
        }
    }
    if (TitleBlockHeight + 10 > (where.height() - 20.0) / 2) {
        m_rigthCenteringLines = false;
        if (TitleBlockWidth > where.width() - 40) {
            m_leftCenteringLines = false;
        }
    }
}

bool ISO5457Frame::showPageSize() const
{
    return m_showPageSize;
}

void ISO5457Frame::setShowPageSize(bool newShowPageSize)
{
    m_showPageSize = newShowPageSize;
}

bool ISO5457Frame::showTrimmingMarks() const
{
    return m_showTrimmingMarks;
}

void ISO5457Frame::setShowTrimmingMarks(bool newShowTrimmingMarks)
{
    m_showTrimmingMarks = newShowTrimmingMarks;
}
