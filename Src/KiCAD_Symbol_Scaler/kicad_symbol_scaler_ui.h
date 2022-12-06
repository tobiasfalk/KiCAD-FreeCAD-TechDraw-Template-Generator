#ifndef KICAD_SYMBOL_SCALER_UI_H
#define KICAD_SYMBOL_SCALER_UI_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class KiCAD_Symbol_Scaler_UI;
}

///
/// \brief The KiCAD_Symbol_Scaler_UI class is the Qt UI class for the KiCAD Symbol scaler class
///
class KiCAD_Symbol_Scaler_UI : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief KiCAD_Symbol_Scaler_UI is the constructor class of the class
    /// \param parent
    ///
    explicit KiCAD_Symbol_Scaler_UI(QWidget *parent = nullptr);
    ///
    /// \brief ~KiCAD_Symbol_Scaler_UI is the deconstructor class of the class
    ///
    ~KiCAD_Symbol_Scaler_UI();

private slots:
    ///
    /// \brief on_folderPushButton_clicked is the Qt slot that is caled when button for selction the path to the KiCAD Symbol librarys
    ///
    void on_folderPushButton_clicked();

    ///
    /// \brief on_pushButton_clicked is the Qt slot that is caled when the scale button is pusched and scales all the Symbol librarys that can be found in the given folder/path
    ///
    void on_pushButton_clicked();

private:
    ///
    /// \brief ui is the pointer to the UI
    ///
    Ui::KiCAD_Symbol_Scaler_UI *ui;
    ///
    /// \brief FOLDER is the path to the folder with all the KiCAD Symbol librarys
    ///
    QString FOLDER = "";
};

#endif // KICAD_SYMBOL_SCALER_UI_H
