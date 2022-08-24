#include "kicad_symbol_scaler_ui.h"
#include "ui_kicad_symbol_scaler_ui.h"

#include "kicad_symbol_scaler.h"

KiCAD_Symbol_Scaler_UI::KiCAD_Symbol_Scaler_UI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KiCAD_Symbol_Scaler_UI)
{
    ui->setupUi(this);
}

KiCAD_Symbol_Scaler_UI::~KiCAD_Symbol_Scaler_UI()
{
    delete ui;
}

void KiCAD_Symbol_Scaler_UI::on_folderPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(dir.size() > 0)
    {
        FOLDER = dir;
        ui->folderLabel->setText(dir);
    }
}


void KiCAD_Symbol_Scaler_UI::on_pushButton_clicked()
{
    if(FOLDER.size() > 0)
    {
        QDir directory(FOLDER);
        QStringList symLibs = directory.entryList(QStringList() << "*.kicad_sym",QDir::Files);
        QDir().mkdir(FOLDER + "/Org/");
        foreach(QString lib, symLibs)
        {
            QFile::copy(FOLDER + "/" + lib, FOLDER + "/Org/" + lib);
            QFile::remove(FOLDER + "/" + lib);

            QFile fileOrg(FOLDER + "/Org/" + lib);
            if(fileOrg.open(QIODevice::ReadOnly))
            {
                QStringList linesQ= QString(fileOrg.readAll()).split('\n');
                std::vector<std::string> lines;
                foreach (QString line, linesQ)
                {
                    lines.push_back(line.toStdString());
                }

                KiCAD_Symbol_Scaler scaler;
                scaler.setLines(lines);
                scaler.setScale(ui->scaleToDoubleSpinBox->value());
                scaler.setLibName(lib.toStdString());
                scaler.scale();
                lines = scaler.getLines();

                QFile file(FOLDER + "/" + QString::number(scaler.getScale()).replace('.', '_') + "_" + lib);
                if(file.open(QIODevice::WriteOnly))
                {
                    foreach (std::string line, lines)
                    {
                        file.write(QString::fromStdString(line).toLatin1() + "\n");
                    }
                }
            }


        }
    }
}

