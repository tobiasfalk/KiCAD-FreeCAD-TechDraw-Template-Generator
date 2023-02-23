#ifndef TEMPLATEGEN_H
#define TEMPLATEGEN_H

#include <QObject>
#include <QObject>
#include <QFile>

#include "templateoptions.h"
#include "iso7200options.h"
#include "asme_y14_35_width180.h"
#include "smallpartslistoptions.h"
#include "fullsheetspartlistoptions.h"

///
/// \brief The TemplateGen class is the base class for all the TemplateGenXXXX classes
///
class TemplateGen : public QObject
{
    Q_OBJECT
protected:
    ///
    /// \brief finisheD is a struct that is there to check if all the Variables are set.
    ///
    FinisheD finisheD;

    ///
    /// \brief DIR is the path where the Template is saved to
    ///
    QString DIR;

    ///
    /// \brief SHEETSIZE contains the size of the sheet and the string/name of this size
    ///
    SheetSize SHEETSIZE;
    ///
    /// \brief SHEETNAME contains the name of the SHEET
    ///
    QString SHEETNAME;
    ///
    /// \brief SHEETSTYLE contains the Syle of the Sheet
    ///
    SheetStyle SHEETSTYLE;
    ///
    /// \brief TITELBLOCKFIELDS is a map that contains all the
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS;
    ///
    /// \brief REVHISTORY says if the revision history, in the upper right corner, should be drawn or not
    ///
    bool REVHISTORY;
    ///
    /// \brief REVHISTORYSTYLE defines the style of the Revison Histrory
    ///
    RevHistoryStyle REVHISTORYSTYLE;
    ///
    /// \brief REVHISTORYFIELDS are the revhistory fields and the options
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS;
    ///
    /// \brief FOLDLINES says if the Foldlines should be drawn or not
    ///
    bool FOLDLINES;
    ///
    /// \brief FOLDLINETARGET is the sheetsize to where it should be folded down to
    ///
    SheetSize FOLDLINETARGET;
    ///
    /// \brief SMALLPARTSLIST says if a small parts list shoud be drawn
    ///
    bool SMALLPARTSLIST;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS;
    bool FULLSHEETPARTSLIST;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS;
    //bool FULLSHEETPARTSLISTCSV;
    bool LOGO;
    QString LOGODIR;
    QString BOMCSVFILE;

    bool NOINIT = false;
    bool NODRAW = false;
    qint64 PARTINDEX = 0;
    qint64 SHEETINDEX = 0;
    qint64 NUMSHEETS = 1;
    qint64 NAMEINDEX = 0;

    QList<QString> BOMKicad;
    QList<BOMColumn> BOMStd;


    // Drawing Field
    Coordinate TOPRIGHTDRAWINGCORNER;
    Coordinate TOPLEFTDRAWINGCORNER;
    Coordinate BOTTOMLEFTDRAWINGCORNER;
    Coordinate BOTTOMRIGHTDRAWINGCORNER;
    // Titleblock
    Coordinate TOPLEFTTITELBLOCKCORNER;
    Coordinate TOPRIGHTTITELBLOCKCORNER;
    Coordinate BOTTOMLEFTTITELBLOCKCORNER;
    Coordinate BOTTOMRIGHTTITELBLOCKCORNER;
    // Rev. Histrory
    Coordinate TOPLEFTREVHISTORY;
    Coordinate TOPRIGHTREVHISTORY;
    Coordinate BOTTOMLEFTREVHISTORY;
    Coordinate BOTTOMRIGHTREVHISTORY;
    // Full Sheet Part List Histrory
    Coordinate TOPLEFTFULLPARTLIST;
    Coordinate TOPRIGHTFULLPARTLIST;
    Coordinate BOTTOMLEFTFULLPARTLIST;
    Coordinate BOTTOMRIGHTFULLPARTLIST;


    // Boarder Centering Marks
    CenteringMarks CENTERINGMARKS{true, true, true, true};
    double LEFTCENTERMARKDEPTH;
    double RIGHTCENTERMARKDEPTH;
    double TOPCENTERMARKDEPTH;
    double BOTTOMCENTERMARKDEPTH;





    bool init();

    bool initBorder();

    bool initTitleblock();

    bool initRevHistory();

    bool initFullSheetPartList();

    virtual QString getFILEENDING() = 0;

    QString createFileName();

    virtual bool writeBase() = 0;

    void drawVerFoldLine(double x, double depth);
    void drawHorFoldLine(double y, double depth);

    void drawTrimmingMarksISO5457();
    void drawDrawingBorderISO5457();
    void drawTitelblockISO7200();
    void drawRevHistoryASME_Y14_35_Width180();
    void drawFoldLines(double depth);
    void drawSmallPartsList();
    void drawFullSheetPartsList();
    ///
    /// \brief drawFullSheetPartsListCSVKiCAD draws the Ful sheet parts list with filled values from a CSV file generated ba KiCAD
    ///
    void drawFullSheetPartsListCSVKiCAD();
    ///
    /// \brief drawFullSheetPartsListCSVStd draws the Ful sheet parts list with filled values from a CSV file
    ///
    void drawFullSheetPartsListCSVStd();

    ///
    /// \brief newSheet creates a new emty Sheet
    ///
    virtual bool newSheet() = 0;
    ///
    /// \brief fullSheetPartsListNumSheets calculaes how many paes are needed to display the BOM
    /// \return tne number of sheets
    ///
    int fullSheetPartsListNumSheetsKiCAD();
    QString getSheetFieldKey();


    void drawISO5457_ISO7200();
    void drawBlank();

    void drawProjectionMethod(Coordinate at, ProjectionMethodType what);
    void drawDot(Coordinate at, double lineWidth);
    void drawDotLine(Coordinate start, Coordinate end, double lineWidth);
    void drawSlimDotLine(Coordinate start, Coordinate end, double lineWidth);

    ///
    /// \brief drawLineAdv draws part of a line betwen two points
    /// \param start
    /// \param end
    /// \param length
    /// \param lineWidth
    /// \return returns the end point of the drawn line
    ///
    Coordinate drawLineAdv(Coordinate start, Coordinate end, double length, double lineWidth);


    virtual void drawLine(Coordinate start, Coordinate end, double lineWidth) = 0;
    virtual void drawRect(Coordinate start, Coordinate end, double lineWidth) = 0;
    virtual void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill = true) = 0;
    virtual void drawCircle(Coordinate center, double radius, double lineWidth, double circleArc = 5) = 0;
    virtual qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont") = 0;
    qint64 drawText(Coordinate position, QStringList text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, qint64 index = 0);

    virtual void drawLogoTitelblockISO7200() = 0;

    ///
    /// \brief readBOMKiCAD reads all the parts out of the Kicad BOM file and puts it line by line in to the BOM List
    /// \param fileDIR the file directory
    /// \return the reulting lsit
    ///
    QList<QString> readBOMKiCAD(QString fileDIR);
    QList<BOMColumn> readBOMStd(QString fileDIR);
    ///
    /// \brief splitBOMlineKiCAD splits the KiCAD BOM line int to it diferant options/values
    /// \param line the line to be splited
    /// \param opt1Val
    /// \param opt2Val
    /// \param opt3Val
    /// \param opt4Val
    /// \param opt5Val
    /// \param opt6Val
    /// \return the number of lines neded
    ///
    int splitBOMlineKiCAD(QString line, QStringList &opt1Val, QStringList &opt2Val, QStringList &opt3Val, QStringList &opt4Val, QStringList &opt5Val, QStringList &opt6Val);
    ///
    /// \brief splitBOMValKiCAD splits the text of val in to peaces that fit in to a field of the lenght of targetLength
    /// \param val
    /// \param targetLenght
    /// \return
    ///
    QStringList splitBOMValKiCAD(QString val, double targetLenght);
    QStringList splitBOMValStd(QString val, double targetLenght);

    std::shared_ptr<ISO7200Options> ISO7200OPTIONS;
    std::shared_ptr<ASME_Y14_35_Width180> ASME_Y14_35_WIDTH180;
    std::shared_ptr<FullSheetsPartListOptions> FULLSHEETPARTLISTOPIONS;
    std::shared_ptr<SmallPartsListOptions> SMALLPARTSLISTSOPTIONS;
public:
    explicit TemplateGen(QObject *parent = nullptr);

    void draw();

    const QString &getDIR() const;
    void setDIR(const QString &newDIR);

    const SheetSize &getSHEETSIZE() const;
    void setSHEETSIZE(const SheetSize &newSHEETSIZE);

    SheetStyle getSHEETSTYLE() const;
    void setSHEETSTYLE(SheetStyle newSHEETSTYLE);

    qint64 getNUMOPTLINES() const;
    void setNUMOPTLINES(qint64 newNUMOPTLINES);

    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS() const;
    void setTITELBLOCKFIELDS(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS);

    RevHistoryStyle getREVHISTORYSTYLE() const;
    void setREVHISTORYSTYLE(RevHistoryStyle newREVHISTORYSTYLE);

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS() const;
    void setREVHISTORYFIELDS(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS);

    bool getREVHISTORY() const;
    void setREVHISTORY(bool newREVHISTORY);

    bool getFOLDLINES() const;
    void setFOLDLINES(bool newFOLDLINES);

    const SheetSize &getFOLDLINETARGET() const;
    void setFOLDLINETARGET(const SheetSize &newFOLDLINETARGET);

    bool getSMALLPARTSLIST() const;
    void setSMALLPARTSLIST(bool newSMALLPARTSLIST);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS() const;
    void setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS);

    bool getFULLSHEETPARTSLIST() const;
    void setFULLSHEETPARTSLIST(bool newFULLSHEETPARTSLIST);

    quint64 getNUMSHEETSFULLSHEETPARTSLIST() const;
    void setNUMSHEETSFULLSHEETPARTSLIST(quint64 newNUMSHEETSFULLSHEETPARTSLIST);

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS() const;
    void setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS);

    bool getLOGO() const;
    void setLOGO(bool newLOGO);

    const QString &getLOGODIR() const;
    void setLOGODIR(const QString &newLOGODIR);

    const QString &getSHEETNAME() const;
    void setSHEETNAME(const QString &newSHEETNAME);

    const QString &getBOMCSVFILE() const;
    void setBOMCSVFILE(const QString &newBOMCSVFILE);

    std::shared_ptr<ISO7200Options> getISO7200OPTIONS() const;
    void setISO7200OPTIONS(const std::shared_ptr<ISO7200Options> &newISO7200OPTIONS);

    std::shared_ptr<ASME_Y14_35_Width180> getASME_Y14_35_WIDTH180() const;
    void setASME_Y14_35_WIDTH180(const std::shared_ptr<ASME_Y14_35_Width180> &newASME_Y14_35_WIDTH180);

    std::shared_ptr<FullSheetsPartListOptions> getFULLSHEETPARTLISTOPIONS() const;
    void setFULLSHEETPARTLISTOPIONS(const std::shared_ptr<FullSheetsPartListOptions> &newFULLSHEETPARTLISTOPIONS);

    std::shared_ptr<SmallPartsListOptions> getSMALLPARTSLISTSOPTIONS() const;
    void setSMALLPARTSLISTSOPTIONS(const std::shared_ptr<SmallPartsListOptions> &newSMALLPARTSLISTSOPTIONS);

signals:

};

#endif // TEMPLATEGEN_H
