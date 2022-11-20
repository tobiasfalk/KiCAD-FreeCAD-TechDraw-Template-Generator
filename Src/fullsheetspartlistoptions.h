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

private:
    ///
    /// \brief ui is the pointer fo the qt UI
    ///
    Ui::FullSheetsPartListOptions *ui;

    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_FREECAD;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_FREECAD_ORG;

    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD5;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD5_ORG;

    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD6;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD6_ORG;

    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_PDF;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_PDF_ORG;


    void loadStdOptions();
    void loadButtonText();
};

#endif // FULLSHEETSPARTLISTOPTIONS_H
