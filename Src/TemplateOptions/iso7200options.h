#ifndef ISO7200OPTIONS_H
#define ISO7200OPTIONS_H

#include <QObject>

#include "templateoptions.h"

namespace Ui {
class ISO7200Options;
}

class ISO7200Options : public QObject
{
    Q_OBJECT
private slots:

private:

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
    explicit ISO7200Options(QObject *parent = nullptr);

    ///
    /// \brief ISO7200Options deconstructor
    ///
    ~ISO7200Options();

    void resetToStd();

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
    void setTITELBLOCKFIELD_FREECAD(QString key, TitelblockField field);

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
    void setTITELBLOCKFIELD_KICAD5(QString key, TitelblockField field);

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
    void setTITELBLOCKFIELD_KICAD6(QString key, TitelblockField field);
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
    void setTITELBLOCKFIELD_PDF(QString key, TitelblockField field);

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
