#ifndef TEMPLATEOPTIONS_H
#define TEMPLATEOPTIONS_H

#include <QString>
#include <QList>

#include <QDebug>

struct FinisheD
{
    bool diR = false;
    bool sheetsizeE = false;
    bool sheetnamE = true;
    bool sheetstylE = false;
    bool numoptlineS = false;
    bool titelblockfieldS = false;
    bool trimmingmarkS = false;
    bool revhistorY = false;
    bool revhistorystylE = false;
    bool numrevhistorY = false;
    bool revhistoryfieldS = false;
    bool foldlineS = false;
    bool foldlinestargeT = false;
    bool smallpartslisT = false;
    bool numpartssmallpartslisT = false;
    bool numlinessmallpartslisT = false;
    bool smallpartslistfieldS = false;
    bool fullsheetpartslisT= false;
    bool fullsheetpartslistcsV= false;
    bool fullsheetpartslistcsvstylE= false;
    bool fullsheetpartslistcsvfilE= false;
    bool numlinesfullsheetpartslisT = false;
    bool fullsheetpartlistfieldS = false;
    bool logO = false;
    bool logodiR = false;
    bool descriptioN = false;
    bool descriptionnumlineS = false;
};

class SheetSize
{
public:
    QString sizeString;
    double width;
    double height;
};

class Coordinate
{
public:
    double X; // width
    double Y; // height

    const Coordinate operator + (const Coordinate& obj);
    const Coordinate operator - (const Coordinate& obj);
    const Coordinate operator * (const Coordinate& obj); // A * B => A.X * B.X and A.Y * B.Y
    const Coordinate operator / (const Coordinate& obj); // A / B => A.X / B.X and A.Y / B.Y
};

class CenteringMarks
{
public:
    bool Top;
    bool Bottom;
    bool Left;
    bool Right;
};

enum class ProjectionMethodType
{
    None,
    FirstAngle,
    ThirdAngle,
};

class TitelblockField
{
public:
    QString Label;
    QStringList Value;
    QString Name;
    ProjectionMethodType ProjectionMethod;
};

enum class SheetStyle
{
    ISO5457_ISO7200,
    BLANK,
};

enum class RevHistoryStyle
{
    ASME_Y14_35_Width180,
};

enum class TextHeightAnchor
{
    Top,
    Middle,
    Bottom,
};

enum class TextWidthAnchor
{
    Left,
    Center,
    Right,
};

enum class BOMStyles
{
    Standard,
    KiCAD,
};

class BOMColumn
{
public:
    double Width;
    QString Title;
    QList<QString> Values;
};


QStringList NumToABC(qint64 num);
int ggT(int zahl1, int zahl2);
int kgV(int zahl1, int zahl2);
bool allFinisheD(FinisheD finisheD);
void printFinisheD(FinisheD finisheD);
double lineLenght(Coordinate start, Coordinate end);

#endif // TEMPLATEOPTIONS_H
