#ifndef LOADESAVESETTINGS_H
#define LOADESAVESETTINGS_H

#include <QObject>

#include "templateoptions.h"

class LoadeSaveSettings : public QObject
{
    Q_OBJECT
private:
    FinisheD finisheD;

    SheetSize SHEETSIZE;
    QString SHEETNAME;
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_FREECAD;
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_KICAD5;
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_KICAD6;
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_PDF;
    qint64 NUMOPTLINES;
    bool TRIMMINGMARKS;
    bool REVHISTORY;
    qint64 NUMREVHISTORY;
    RevHistoryStyle REVHISTORYSTYLE;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_FREECAD;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_KICAD5;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_KICAD6;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_PDF;
    bool FOLDLINES;
    SheetSize FOLDLINESTARGET;
    bool SMALLPARTSLIST;
    quint64 NUMLINESSMALLPARTSLIST;
    quint64 NUMPARTSSMALLPARTSLIST;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_FREECAD;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_KICAD5;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_KICAD6;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_PDF;
    bool FULLSHEETPARTSLIST;
    quint64 NUMLINESFULLSHEETPARTSLIST;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_FREECAD;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD5;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD6;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_PDF;

    bool LOGO;
    QString LOGODIR;

    QString getSheetStyleString();
    //SheetStyle toSheetStyle(QString style);

    QString getRevHistoryStyleString();
    RevHistoryStyle toRevHistoryStyle(QString style);

    QString stringListToString(QStringList list);

    QString setProjectionMethod(ProjectionMethodType methode);
    ProjectionMethodType getProjectionMethod(QString methode);
public:
    explicit LoadeSaveSettings(QObject *parent = nullptr);

    void saveSettings(QString dir);
    void loadSettings(QString dir);

    const SheetSize &getSHEETSIZE() const;
    void setSHEETSIZE(const SheetSize &newSHEETSIZE);

//    SheetStyle getSHEETSTYLE() const;
//    void setSHEETSTYLE(SheetStyle newSHEETSTYLE);

    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS_FREECAD() const;
    void setTITELBLOCKFIELDS_FREECAD(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_FREECAD);

    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS_KICAD5() const;
    void setTITELBLOCKFIELDS_KICAD5(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD5);

    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS_KICAD6() const;
    void setTITELBLOCKFIELDS_KICAD6(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD6);

    qint64 getNUMOPTLINES() const;
    void setNUMOPTLINES(qint64 newNUMOPTLINES);

    qint64 getNUMREVHISTORY() const;
    void setNUMREVHISTORY(qint64 newNUMREVHISTORY);

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_FREECAD() const;
    void setREVHISTORYFIELDS_FREECAD(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_FREECAD);

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_KICAD5() const;
    void setREVHISTORYFIELDS_KICAD5(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD5);

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_KICAD6() const;
    void setREVHISTORYFIELDS_KICAD6(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD6);

    bool getTRIMMINGMARKS() const;
    void setTRIMMINGMARKS(bool newTRIMMINGMARKS);

    bool getREVHISTORY() const;
    void setREVHISTORY(bool newREVHISTORY);

    bool getFOLDLINES() const;
    void setFOLDLINES(bool newFOLDLINES);

    const SheetSize &getFOLDLINESTARGET() const;
    void setFOLDLINESTARGET(const SheetSize &newFOLDLINESTARGET);

    bool getSMALLPARTSLIST() const;
    void setSMALLPARTSLIST(bool newSMALLPARTSLIST);

    quint64 getNUMLINESSMALLPARTSLIST() const;
    void setNUMLINESSMALLPARTSLIST(quint64 newNUMLINESSMALLPARTSLIST);

    quint64 getNUMPARTSSMALLPARTSLIST() const;
    void setNUMPARTSSMALLPARTSLIST(quint64 newNUMPARTSSMALLPARTSLIST);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS_FREECAD() const;
    void setSMALLPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_FREECAD);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS_KICAD5() const;
    void setSMALLPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_KICAD5);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS_KICAD6() const;
    void setSMALLPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_KICAD6);

    bool getFULLSHEETPARTSLIST() const;
    void setFULLSHEETPARTSLIST(bool newFULLSHEETPARTSLIST);

    quint64 getNUMLINESFULLSHEETPARTSLIST() const;
    void setNUMLINESFULLSHEETPARTSLIST(quint64 newNUMLINESFULLSHEETPARTSLIST);

    bool getLOGO() const;
    void setLOGO(bool newLOGO);

    const QString &getLOGODIR() const;
    void setLOGODIR(const QString &newLOGODIR);

    RevHistoryStyle getREVHISTORYSTYLE() const;
    void setREVHISTORYSTYLE(RevHistoryStyle newREVHISTORYSTYLE);

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_FREECAD() const;
    void setFULLSHEETPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_FREECAD);

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_KICAD5() const;
    void setFULLSHEETPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD5);

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_KICAD6() const;
    void setFULLSHEETPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD6);

    const QString &getSHEETNAME() const;
    void setSHEETNAME(const QString &newSHEETNAME);

    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS_PDF() const;
    void setTITELBLOCKFIELDS_PDF(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_PDF);

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_PDF() const;
    void setREVHISTORYFIELDS_PDF(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_PDF);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS_PDF() const;
    void setSMALLPARTSLISTFIELDS_PDF(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_PDF);

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_PDF() const;
    void setFULLSHEETPARTSLISTFIELDS_PDF(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_PDF);

signals:

};

#endif // LOADESAVESETTINGS_H
