#ifndef TEMPLATEGEN_H
#define TEMPLATEGEN_H

#include <QObject>
#include <QObject>
#include <QFile>

#include "templateoptions.h"

class TemplateGen : public QObject
{
    Q_OBJECT
protected:
    FinisheD finisheD;

    QString DIR;
    virtual QString getFILEENDING() = 0;

    virtual bool writeBase() = 0;

    PageSize PAGESIZE;
    QString SHEETNAME;
    PageStyle PAGESTYLE;
    bool TRIMMINGMARKS;
    qint64 NUMOPTLINES;
    QMap<QString, TitelblockField> TITELBLOCKFIELDS;
    bool REVHISTORY;
    RevHistoryStyle REVHISTORYSTYLE;
    qint64 NUMREVHISTORY;
    QMap<QString, TitelblockField> REVHISTORYFIELDS;
    bool FOLDLINES;
    PageSize FOLDLINETARGET;
    bool SMALLPARTSLIST;
    quint64 NUMPARTSSMALLPARTSLIST;
    quint64 NUMLINESMALLPARTSLIST;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS;
    bool FULLSHEETPARTSLIST;
    quint64 NUMLINESFULLSHEETPARTSLIST;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS;
    bool FULLSHEETPARTSLISTCSV;
    QString FULLSHEETPARTSLISTCSVFILE;
    BOMStyles FULLSHEETPARTLISTCSVSTYLE;
    bool LOGO;
    QString LOGODIR;
    bool DESCRIPTION;
    quint64 DESCRIPTIONNUMLINES;
    QString BOMCSVFILE;

    bool NOINIT = false;
    bool NODRAW = false;
    qint64 PARTINDEX = 0;
    qint64 SHEETINDEX = 0;
    qint64 NUMSHEETS = 1;
    qint64 NAMEINDEX = 0;
    CenteringMarks CENTERINGMARKS{true, true, true, true};
    Coordinate TOPRIGHTDRAWINGCORNER;
    Coordinate TOPLEFTDRAWINGCORNER;
    Coordinate TOPLEFTITELBLOCKCORNER;

    QList<QString> BOM;

    bool init();

    QString createFileName();

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
    /// \brief newPage creates a new emty Page
    ///
    virtual void newPage() = 0;
    ///
    /// \brief fullSheetPartsListNumPages calculaes how many paes are needed to display the BOM
    /// \return tne number of pages
    ///
    int fullSheetPartsListNumPagesKiCAD();
    QString getSheetFieldKey();


    void drawISO5457_ISO7200();

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
    virtual void drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth) = 0;
    virtual void drawCircle(Coordinate center, double radius, double lineWidth) = 0;
    virtual qint64 drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, QString font = "osifont") = 0;
    qint64 drawText(Coordinate position, QStringList text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable = false, qint64 index = 0);

    virtual void drawLogoTitelblockISO7200() = 0;

    ///
    /// \brief readBOMKiCAD reads all the parts out of the Kicad BOM file and puts it line by line in to the BOM List
    /// \param fileDIR the file directory
    /// \return the reulting lsit
    ///
    QList<QString> readBOMKiCAD(QString fileDIR);
    QList<QString> readBOMStd(QString fileDIR);
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
public:
    explicit TemplateGen(QObject *parent = nullptr);

    void draw();

    const QString &getDIR() const;
    void setDIR(const QString &newDIR);

    const PageSize &getPAGESIZE() const;
    void setPAGESIZE(const PageSize &newPAGESIZE);

    PageStyle getPAGESTYLE() const;
    void setPAGESTYLE(PageStyle newPAGESTYLE);

    qint64 getNUMOPTLINES() const;
    void setNUMOPTLINES(qint64 newNUMOPTLINES);

    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS() const;
    void setTITELBLOCKFIELDS(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS);

    bool getTRIMMINGMARKS() const;
    void setTRIMMINGMARKS(bool newTRIMMINGMARKS);

    RevHistoryStyle getREVHISTORYSTYLE() const;
    void setREVHISTORYSTYLE(RevHistoryStyle newREVHISTORYSTYLE);

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS() const;
    void setREVHISTORYFIELDS(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS);

    qint64 getNUMREVHISTORY() const;
    void setNUMREVHISTORY(qint64 newNUMREVHISTORY);

    bool getREVHISTORY() const;
    void setREVHISTORY(bool newREVHISTORY);

    bool getFOLDLINES() const;
    void setFOLDLINES(bool newFOLDLINES);

    const PageSize &getFOLDLINETARGET() const;
    void setFOLDLINETARGET(const PageSize &newFOLDLINETARGET);

    quint64 getNUMPARTSSMALLPARTSLIST() const;
    void setNUMPARTSSMALLPARTSLIST(quint64 newNUMPARTSSMALLPARTSLIST);

    bool getSMALLPARTSLIST() const;
    void setSMALLPARTSLIST(bool newSMALLPARTSLIST);

    quint64 getNUMLINESMALLPARTSLIST() const;
    void setNUMLINESMALLPARTSLIST(quint64 newNUMLINESMALLPARTSLIST);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS() const;
    void setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS);

    bool getFULLSHEETPARTSLIST() const;
    void setFULLSHEETPARTSLIST(bool newFULLSHEETPARTSLIST);

    quint64 getNUMLINESFULLSHEETPARTSLIST() const;
    void setNUMLINESFULLSHEETPARTSLIST(quint64 newNUMLINESFULLSHEETPARTSLIST);

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


    bool getDESCRIPTION() const;
    void setDESCRIPTION(bool newDESCRIPTION);

    quint64 getDESCRIPTIONNUMLINES() const;
    void setDESCRIPTIONNUMLINES(quint64 newDESCRIPTIONNUMLINES);

    const QString &getBOMCSVFILE() const;
    void setBOMCSVFILE(const QString &newBOMCSVFILE);

    bool getFULLSHEETPARTSLISTCSV() const;
    void setFULLSHEETPARTSLISTCSV(bool newFULLSHEETPARTSLISTCSV);

    const QString &getFULLSHEETPARTSLISTCSVFILE() const;
    void setFULLSHEETPARTSLISTCSVFILE(const QString &newFULLSHEETPARTSLISTCSVFILE);

    BOMStyles getFULLSHEETPARTLISTCSVSTYLE() const;
    void setFULLSHEETPARTLISTCSVSTYLE(BOMStyles newFULLSHEETPARTLISTCSVSTYLE);

signals:

};

#endif // TEMPLATEGEN_H
