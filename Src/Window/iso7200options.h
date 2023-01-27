#ifndef ISO7200OPTIONS_H
#define ISO7200OPTIONS_H

#include <QDialog>

#include "templateoptions.h"

namespace Ui {
class ISO7200Options;
}

class ISO7200Options : public QDialog
{
    Q_OBJECT
private slots:
    ///
    /// \brief on_opt1PushButton_clicked is the event when the option 1 buttion is clicked
    ///
    void on_opt1PushButton_clicked();
    ///
    /// \brief on_opt2PushButton_clicked is the event when the option 2 buttion is clicked
    ///
    void on_opt2PushButton_clicked();
    ///
    /// \brief on_opt3PushButton_clicked is the event when the option 3 buttion is clicked
    ///
    void on_opt3PushButton_clicked();
    ///
    /// \brief on_opt4PushButton_clicked is the event when the option 4 buttion is clicked
    ///
    void on_opt4PushButton_clicked();
    ///
    /// \brief on_opt5PushButton_clicked is the event when the option 5 buttion is clicked
    ///
    void on_opt5PushButton_clicked();
    ///
    /// \brief on_opt6PushButton_clicked is the event when the option 6 buttion is clicked
    ///
    void on_opt6PushButton_clicked();
    ///
    /// \brief on_opt7PushButton_clicked is the event when the option 7 buttion is clicked
    ///
    void on_opt7PushButton_clicked();
    ///
    /// \brief on_opt8PushButton_clicked is the event when the option 8 buttion is clicked
    ///
    void on_opt8PushButton_clicked();
    ///
    /// \brief on_opt9PushButton_clicked is the event when the option 9 buttion is clicked
    ///
    void on_opt9PushButton_clicked();
    ///
    /// \brief on_opt10PushButton_clicked is the event when the option 10 buttion is clicked
    ///
    void on_opt10PushButton_clicked();
    ///
    /// \brief on_opt11PushButton_clicked is the event when the option 11 buttion is clicked
    ///
    void on_opt11PushButton_clicked();
    ///
    /// \brief on_opt12PushButton_clicked is the event when the option 12 buttion is clicked
    ///
    void on_opt12PushButton_clicked();
    ///
    /// \brief on_opt13PushButton_clicked is the event when the option 13 buttion is clicked
    ///
    void on_opt13PushButton_clicked();
    ///
    /// \brief on_opt14PushButton_clicked is the event when the option 14 buttion is clicked
    ///
    void on_opt14PushButton_clicked();
    ///
    /// \brief on_opt15PushButton_clicked is the event when the option 15 buttion is clicked
    ///
    void on_opt15PushButton_clicked();
    ///
    /// \brief on_opt16PushButton_clicked is the event when the option 16 buttion is clicked
    ///
    void on_opt16PushButton_clicked();
    ///
    /// \brief on_opt17PushButton_clicked is the event when the option 17 buttion is clicked
    ///
    void on_opt17PushButton_clicked();
    ///
    /// \brief on_opt18PushButton_clicked is the event when the option 18 buttion is clicked
    ///
    void on_opt18PushButton_clicked();
    ///
    /// \brief on_opt19PushButton_clicked is the event when the option 19 buttion is clicked
    ///
    void on_opt19PushButton_clicked();
    ///
    /// \brief on_opt20PushButton_clicked is the event when the option 20 buttion is clicked
    ///
    void on_opt20PushButton_clicked();
    ///
    /// \brief on_opt21PushButton_clicked is the event when the option 21 buttion is clicked
    ///
    void on_opt21PushButton_clicked();
    ///
    /// \brief on_opt22PushButton_clicked is the event when the option 22 buttion is clicked
    ///
    void on_opt22PushButton_clicked();

    ///
    /// \brief on_buttonBox_rejected is the event when the rejekt buttion is clicked, it resets all the field maps to its origin
    ///
    void on_buttonBox_rejected();

    ///
    /// \brief on_opt23PushButton_clicked is the event when the option 23 buttion is clicked
    ///
    void on_opt23PushButton_clicked();

private:
    ///
    /// \brief ui is the pointer fo the qt UI
    ///
    Ui::ISO7200Options *ui;

    ///
    /// \brief TITELBLOCKFIELDS_FREECAD is the map with all the FreeCAD fields
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_FREECAD;
    ///
    /// \brief TITELBLOCKFIELDS_FREECAD_ORG is the map with all the origpnal FreeCAD fields
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_FREECAD_ORG;

    ///
    /// \brief TITELBLOCKFIELDS_KICAD5 is the map with all the KiCAD 5 fields
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_KICAD5;
    ///
    /// \brief TITELBLOCKFIELDS_KICAD5_ORG is the map with all the origonal KiCAD 5 fields
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_KICAD5_ORG;

    ///
    /// \brief TITELBLOCKFIELDS_KICAD6 is the map with all the KiCAD 6 fields
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_KICAD6;
    ///
    /// \brief TITELBLOCKFIELDS_KICAD6_ORG is the map with all the origonal KiCAD 6 fields
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_KICAD6_ORG;

    ///
    /// \brief TITELBLOCKFIELDS_PDF is the map with all the PDF fields
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_PDF;
    ///
    /// \brief TITELBLOCKFIELDS_PDF_ORG is the map with all the origonal PDF fields
    ///
    QMap<QString, TitelblockField> TITELBLOCKFIELDS_PDF_ORG;


    ///
    /// \brief loadStdOptions loads the standorad option in to the field maps
    ///
    void loadStdOptions();
    ///
    /// \brief loadButtonText loads all the Text that appiers on the Buttons
    ///
    void loadButtonText();

    ///
    /// \brief trimmingMarks a boolean to save if trimming marks should be showm or not
    ///
    bool trimmingMarks;

    ///
    /// \brief numOptLins is a int that saves how many optional lines should be drawn
    ///
    unsigned int numOptLins;

    ///
    /// \brief descField a boolean to save if trimming marks should be showm or not
    ///
    bool descField;

    ///
    /// \brief numDescLines saves how many lines the description field should have
    ///
    unsigned int numDescLines;

public:
    ///
    /// \brief ISO7200Options constructor
    /// \param parent qt parent pointer
    ///
    explicit ISO7200Options(QWidget *parent = nullptr);
    ///
    /// \brief ISO7200Options deconstructor
    ///
    ~ISO7200Options();

    ///
    /// \brief getTITELBLOCKFIELDS_FREECAD is the getter function
    /// \return
    ///
    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS_FREECAD() const;
    ///
    /// \brief setTITELBLOCKFIELDS_FREECAD is the setter function
    /// \param newTITELBLOCKFIELDS_FREECAD
    ///
    void setTITELBLOCKFIELDS_FREECAD(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_FREECAD);

    ///
    /// \brief getTITELBLOCKFIELDS_KICAD5 is the getter function
    /// \return
    ///
    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS_KICAD5() const;
    ///
    /// \brief setTITELBLOCKFIELDS_KICAD5 is the setter function
    /// \param newTITELBLOCKFIELDS_KICAD5
    ///
    void setTITELBLOCKFIELDS_KICAD5(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD5);

    ///
    /// \brief getTITELBLOCKFIELDS_KICAD6 is the getter function
    /// \return
    ///
    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS_KICAD6() const;
    ///
    /// \brief setTITELBLOCKFIELDS_KICAD6 is the setter function
    /// \param newTITELBLOCKFIELDS_KICAD6
    ///
    void setTITELBLOCKFIELDS_KICAD6(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD6);
    ///
    /// \brief getTITELBLOCKFIELDS_PDF is the getter function
    /// \return
    ///
    const QMap<QString, TitelblockField> &getTITELBLOCKFIELDS_PDF() const;
    ///
    /// \brief setTITELBLOCKFIELDS_PDF is the setter function
    /// \param newTITELBLOCKFIELDS_PDF
    ///
    void setTITELBLOCKFIELDS_PDF(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_PDF);

    ///
    /// \brief getTrimmingMarks returns true if trimmin marks should be drawn
    /// \return is a boolena
    ///
    bool getTrimmingMarks();
    ///
    /// \brief setTrimmingMarks sets if  trimmin marks should be drawn
    /// \param newTrimmingMarks a boolean
    ///
    void setTrimmingMarks(bool newTrimmingMarks);

    ///
    /// \brief getNumOptLins returns the number of optional lines
    /// \return a unsigned int
    ///
    unsigned int getNumOptLins();
    ///
    /// \brief setNumOptLins sets the number of optional lines, at max 3
    /// \param newNumOptLins
    ///
    void setNumOptLins(unsigned int newNumOptLins);

    ///
    /// \brief getNumDescLines returns the number of lines the desc field should have
    /// \return
    ///
    unsigned int getNumDescLines();
    ///
    /// \brief setNumDescLines sets the number of lines the desc field should have
    /// \param newNumDescLines
    ///
    void setNumDescLines(unsigned int newNumDescLines);

    bool getDescField();
    void setDescField(bool newDescField);
};

#endif // ISO7200OPTIONS_H
