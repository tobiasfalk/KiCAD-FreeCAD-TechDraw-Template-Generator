#ifndef KICAD_SYMBOL_SCALER_UI_H
#define KICAD_SYMBOL_SCALER_UI_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class KiCAD_Symbol_Scaler_UI;
}

class KiCAD_Symbol_Scaler_UI : public QDialog
{
    Q_OBJECT

public:
    explicit KiCAD_Symbol_Scaler_UI(QWidget *parent = nullptr);
    ~KiCAD_Symbol_Scaler_UI();

private slots:
    void on_folderPushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::KiCAD_Symbol_Scaler_UI *ui;
    QString FOLDER = "";
};

#endif // KICAD_SYMBOL_SCALER_UI_H
