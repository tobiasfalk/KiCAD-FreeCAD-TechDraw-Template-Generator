#ifndef LOADESAVESETTINGS_H
#define LOADESAVESETTINGS_H

#include <QObject>

#include "templateoptions.h"

class LoadeSaveSettings : public QObject
{
    Q_OBJECT
private:
    FinisheD finisheD;

    PageSize SHEETSIZE;
    QString SHEETNAME;
    PageStyle SHEETSTYLE;
    QMap<QString, TitelblockField> TITELBLOCKFIELDS;
    qint64 NUMOPTLINES;
    bool TRIMMINGMARKS;
    bool REVHISTORY;
    qint64 NUMREVHISTORY;
    RevHistoryStyle REVHISTORYSTYLE;
    QMap<QString, TitelblockField> REVHISTORYFIELDS;
    bool FOLDLINES;
    PageSize FOLDLINESTARGET;
    bool SMALLPARTSLIST;
    quint64 NUMLINESSMALLPARTSLIST;
    quint64 NUMPARTSSMALLPARTSLIST;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS;
    bool FULLSHEETPARTSLIST;
    quint64 NUMLINESFULLSHEETPARTSLIST;
    quint64 NUMSHEETSFULLSHEETPARTSLIST;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS;

    bool LOGO;
    QString LOGODIR;

    QString getSheetStyleString();
    PageStyle toSheetStyle(QString style);

    QString getRevHistoryStyleString();
    RevHistoryStyle toRevHistoryStyle(QString style);

    QString stringListToString(QStringList list);
public:
    explicit LoadeSaveSettings(QObject *parent = nullptr);

    void saveSettings(QString dir);
    void loadSettings(QString dir);

    const PageSize &getSHEETSIZE() const;
    void setSHEETSIZE(const PageSize &newSHEETSIZE);

    PageStyle getSHEETSTYLE() const;
    void setSHEETSTYLE(PageStyle newSHEETSTYLE);

    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS() const;
    void setTITELBLOCKFIELDS(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS);

    qint64 getNUMOPTLINES() const;
    void setNUMOPTLINES(qint64 newNUMOPTLINES);

    qint64 getNUMREVHISTORY() const;
    void setNUMREVHISTORY(qint64 newNUMREVHISTORY);

    const QMap<QString, TitelblockField> &getREVHISTROYFIELDS() const;
    void setREVHISTROYFIELDS(const QMap<QString, TitelblockField> &newREVHISTROYFIELDS);

    bool getTRIMMINGMARKS() const;
    void setTRIMMINGMARKS(bool newTRIMMINGMARKS);

    bool getREVHISTORY() const;
    void setREVHISTORY(bool newREVHISTORY);

    bool getFOLDLINES() const;
    void setFOLDLINES(bool newFOLDLINES);

    const PageSize &getFOLDLINESTARGET() const;
    void setFOLDLINESTARGET(const PageSize &newFOLDLINESTARGET);

    bool getSMALLPARTSLIST() const;
    void setSMALLPARTSLIST(bool newSMALLPARTSLIST);

    quint64 getNUMLINESSMALLPARTSLIST() const;
    void setNUMLINESSMALLPARTSLIST(quint64 newNUMLINESSMALLPARTSLIST);

    quint64 getNUMPARTSSMALLPARTSLIST() const;
    void setNUMPARTSSMALLPARTSLIST(quint64 newNUMPARTSSMALLPARTSLIST);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS() const;
    void setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS);

    bool getFULLSHEETPARTSLIST() const;
    void setFULLSHEETPARTSLIST(bool newFULLSHEETPARTSLIST);

    quint64 getNUMLINESFULLSHEETPARTSLIST() const;
    void setNUMLINESFULLSHEETPARTSLIST(quint64 newNUMLINESFULLSHEETPARTSLIST);

    quint64 getNUMSHEETSFULLSHEETPARTSLIST() const;
    void setNUMSHEETSFULLSHEETPARTSLIST(quint64 newNUMSHEETSFULLSHEETPARTSLIST);

    bool getLOGO() const;
    void setLOGO(bool newLOGO);

    const QString &getLOGODIR() const;
    void setLOGODIR(const QString &newLOGODIR);

    RevHistoryStyle getREVHISTORYSTYLE() const;
    void setREVHISTORYSTYLE(RevHistoryStyle newREVHISTORYSTYLE);

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS() const;
    void setREVHISTORYFIELDS(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS);

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS() const;
    void setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS);

    const QString &getSHEETNAME() const;
    void setSHEETNAME(const QString &newSHEETNAME);

signals:

};

#endif // LOADESAVESETTINGS_H
