#ifndef FULLSHEETSPARTLISTOPTIONS_H
#define FULLSHEETSPARTLISTOPTIONS_H

#include <QDialog>

#include "templateoptions.h"
#include "changetitelblockfield.h"

namespace Ui {
class FullSheetsPartListOptions;
}

///
/// \brief The FullSheetsPartListOptions class is able to change all the field values of the Full sheet part list
///
class FullSheetsPartListOptions : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief FullSheetsPartListOptions constructor
    /// \param parent
    ///
    explicit FullSheetsPartListOptions(QWidget *parent = nullptr);
    ///
    /// \brief FullSheetsPartListOptions deconstructor
    ///
    ~FullSheetsPartListOptions();

    ///
    /// \brief getFULLSHEETPARTSLISTFIELDS_FREECAD is the getter function
    /// \return
    ///
    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_FREECAD() const;
    ///
    /// \brief setFULLSHEETPARTSLISTFIELDS_FREECAD is the setter function
    /// \param newFULLSHEETPARTSLISTFIELDS_FREECAD
    ///
    void setFULLSHEETPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_FREECAD);

    ///
    /// \brief getFULLSHEETPARTSLISTFIELDS_KICAD5 is the getter function
    /// \return
    ///
    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_KICAD5() const;
    ///
    /// \brief setFULLSHEETPARTSLISTFIELDS_KICAD5 is the setter function
    /// \param newFULLSHEETPARTSLISTFIELDS_KICAD5
    ///
    void setFULLSHEETPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD5);

    ///
    /// \brief getFULLSHEETPARTSLISTFIELDS_KICAD6 is the getter function
    /// \return
    ///
    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_KICAD6() const;
    ///
    /// \brief setFULLSHEETPARTSLISTFIELDS_KICAD6 is the setter function
    /// \param newFULLSHEETPARTSLISTFIELDS_KICAD6
    ///
    void setFULLSHEETPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD6);

    ///
    /// \brief resetToOrigin resets all the maps to its original values
    ///
    void resetToOrigin();

    ///
    /// \brief getFULLSHEETPARTSLISTFIELDS_PDF is the getter function
    /// \return
    ///
    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_PDF() const;
    ///
    /// \brief setFULLSHEETPARTSLISTFIELDS_PDF is the setter function
    /// \param newFULLSHEETPARTSLISTFIELDS_PDF
    ///
    void setFULLSHEETPARTSLISTFIELDS_PDF(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_PDF);

    ///
    /// \brief getBOMDIR returnsd the dir of the BOM
    /// \return
    ///
    QString getBOMDIR() const;
    ///
    /// \brief setBOMDIR sets the dir of the BOM
    /// \param newBOMDIR
    ///
    void setBOMDIR(const QString &newBOMDIR);

    unsigned int getNumLinesPerField();
    void setNumLinesPerField(unsigned int newNumLinesPerField);

    bool getImporCSV();
    void setImporCSV(bool newImporCSV);

    BOMStyles getBOMStyle();

    const QString &getSpace();
    void setSpace(const QString &newSpace);

private slots:
    ///
    /// \brief on_opt1PushButton_clicked the field optiens for the fullsheetpartlist opt1 is caled
    ///
    void on_opt1PushButton_clicked();

    ///
    /// \brief on_opt2PushButton_clicked the field optiens for the fullsheetpartlist opt2 is caled
    ///
    void on_opt2PushButton_clicked();

    ///
    /// \brief on_opt3PushButton_clicked the field optiens for the fullsheetpartlist opt3 is caled
    ///
    void on_opt3PushButton_clicked();

    ///
    /// \brief on_opt4PushButton_clicked the field optiens for the fullsheetpartlist opt4 is caled
    ///
    void on_opt4PushButton_clicked();

    ///
    /// \brief on_opt5PushButton_clicked the field optiens for the fullsheetpartlist opt5 is caled
    ///
    void on_opt5PushButton_clicked();

    ///
    /// \brief on_opt6PushButton_clicked the field optiens for the fullsheetpartlist opt6 is caled
    ///
    void on_opt6PushButton_clicked();

    void on_selectCSVBOMpushButton_clicked();

private:
    ///
    /// \brief ui is the pointer fo the qt UI
    ///
    Ui::FullSheetsPartListOptions *ui;

    ///
    /// \brief FULLSHEETPARTSLISTFIELDS_FREECAD is the map with all the FreeCAD fields
    ///
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_FREECAD;
    ///
    /// \brief FULLSHEETPARTSLISTFIELDS_FREECAD_ORG is the map with all the origpnal FreeCAD fields
    ///
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_FREECAD_ORG;

    ///
    /// \brief FULLSHEETPARTSLISTFIELDS_KICAD5 is the map with all the KiCAD 5 fields
    ///
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD5;
    ///
    /// \brief FULLSHEETPARTSLISTFIELDS_KICAD5_ORG is the map with all the origonal KiCAD 5 fields
    ///
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD5_ORG;

    ///
    /// \brief FULLSHEETPARTSLISTFIELDS_KICAD6 is the map with all the KiCAD 6 fields
    ///
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD6;
    ///
    /// \brief FULLSHEETPARTSLISTFIELDS_KICAD6_ORG is the map with all the origonal KiCAD 6 fields
    ///
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD6_ORG;

    ///
    /// \brief FULLSHEETPARTSLISTFIELDS_PDF is the map with all the PDF fields
    ///
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_PDF;
    ///
    /// \brief FULLSHEETPARTSLISTFIELDS_PDF_ORG is the map with all the origonal PDF fields
    ///
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_PDF_ORG;


    ///
    /// \brief loadStdOptions loads the standorad option in to the field maps
    ///
    void loadStdOptions();
    ///
    /// \brief loadButtonText loads all the Text that appiers on the Buttons
    ///
    void loadButtonText();

    ///
    /// \brief BOMDIR is the location/path of the bom
    ///
    QString BOMDIR = "&";

    unsigned int numLinesPerField = 1;

    bool imporCSV = false;

    void initBOMStyles();

    QString Space;
};

#endif // FULLSHEETSPARTLISTOPTIONS_H
