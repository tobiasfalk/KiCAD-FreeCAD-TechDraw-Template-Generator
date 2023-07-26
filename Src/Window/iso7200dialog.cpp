#include "iso7200dialog.h"
#include "ui_iso7200dialog.h"
#include "changetitelblockfield.h"

void ISO7200Dialog::on_opt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt1"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt1"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt1"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt1", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt1", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt1", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt1", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt2"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt2"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt2"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt2", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt2", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt2", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt2", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt3"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt3"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt3"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt3", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt3", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt3", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt3", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt4"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt4"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt4"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt4", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt4", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt4", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt4", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt5"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt5"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt5"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt5", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt5", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt5", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt5", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt6PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt6"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt6"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt6"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt6"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt6", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt6", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt6", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt6", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt7PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt7"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt7"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt7"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt7"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt7", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt7", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt7", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt7", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt8PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt8"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt8"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt8"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt8"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt8", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt8", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt8", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt8", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt9PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt9"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt9"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt9"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt9"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt9", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt9", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt9", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt9", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt10PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt10"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt10"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt10"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt10"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt10", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt10", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt10", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt10", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt11PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt11"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt11"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt11"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt11"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt11", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt11", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt11", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt11", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt12PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt12"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt12"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt12"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt12"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt12", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt12", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt12", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt12", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt13PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt13"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt13"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt13"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt13"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt13", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt13", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt13", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt13", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt14PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt14"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt14"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt14"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt14"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt14", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt14", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt14", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt14", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt15PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt15"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt15"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt15"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt15"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt15", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt15", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt15", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt15", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt16PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt16"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt16"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt16"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt16"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt16", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt16", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt16", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt16", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt17PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt17"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt17"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt17"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt17"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt17", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt17", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt17", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt17", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt18PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt18"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt18"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt18"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt18"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt18", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt18", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt18", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt18", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt19PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt19"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt19"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt19"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt19"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt19", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt19", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt19", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt19", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt20PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt20"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt20"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt20"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt20"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt20", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt20", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt20", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt20", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt21PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt21"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt21"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt21"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt21"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt21", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt21", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt21", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt21", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::on_opt22PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt22"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt22"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt22"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt22"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt22", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt22", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt22", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt22", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

void ISO7200Dialog::loadButtonText()
{
    ui->opt1PushButton->setText ("Option 1: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt1"].Label);
    ui->opt2PushButton->setText ("Option 2: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt2"].Label);
    ui->opt3PushButton->setText ("Option 3: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt3"].Label);
    ui->opt4PushButton->setText ("Option 4: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt4"].Label);
    ui->opt5PushButton->setText ("Option 5: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt5"].Label);
    ui->opt6PushButton->setText ("Option 6: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt6"].Label);
    ui->opt7PushButton->setText ("Option 7: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt7"].Label);
    ui->opt8PushButton->setText ("Option 8: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt8"].Label);
    ui->opt9PushButton->setText ("Option 9: "  + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt9"].Label);
    ui->opt10PushButton->setText("Option 10: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt10"].Label);
    ui->opt11PushButton->setText("Option 11: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt11"].Label);
    ui->opt12PushButton->setText("Option 12: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt12"].Label);
    ui->opt13PushButton->setText("Option 13: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt13"].Label);
    ui->opt14PushButton->setText("Option 14: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt14"].Label);
    ui->opt15PushButton->setText("Option 15: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt15"].Label);
    ui->opt16PushButton->setText("Option 16: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt16"].Label);
    ui->opt17PushButton->setText("Option 17: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt17"].Label);
    ui->opt18PushButton->setText("Option 18: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt18"].Label);
    ui->opt19PushButton->setText("Option 19: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt19"].Label);
    ui->opt20PushButton->setText("Option 20: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt20"].Label);
    ui->opt21PushButton->setText("Option 21: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt21"].Label);
    ui->opt22PushButton->setText("Option 22: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt22"].Label);
    ui->opt23PushButton->setText("Option 23: " + ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt23"].Label);
}

void ISO7200Dialog::loadOptions()
{
    loadButtonText();
    ui->OptLinesSpinBox->setValue(ISO7200OPTIONS->getNumOptLins());
    ui->DescriptionCheckBox->setChecked(ISO7200OPTIONS->getDescField());
    ui->DescriptionSpinBox->setValue(ISO7200OPTIONS->getNumDescLines());
}

void ISO7200Dialog::loadPreview()
{
    PREVIEW = std::shared_ptr<Preview>(new Preview());
    PREVIEW->setMinimumWidth(400);
    PREVIEW->setStyleSheet("background-color: rgb(255,255,255)");

    // Preview
    SheetSize sheetSize = SheetSize{"ISO7200", 210, 150};
    QString sheetName = "ISO7200";
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
    qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
    bool revHistory = false;
    bool foldLines = false;
    SheetSize foldLinesTaget = SheetSize{"ISO7200", 210, 250};
    bool smallPartsList = false;
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
    bool fullSheetPartsList = false;
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
    bool logo = false;
    QString logoDir = "";

    QDir dir;
    dir.mkdir(QDir::currentPath() + "/tmp");
    //TemplateGenKiCAD_5 KiCAD5(this);
    PREVIEW->setDIR(QDir::currentPath() + "/tmp");
    PREVIEW->setSHEETSIZE(sheetSize);
    PREVIEW->setSHEETNAME(sheetName);
    PREVIEW->setSHEETTITLEBLOCK(SheetTitleblock::ISO7200);
    PREVIEW->setSHEETFRAME(SheetFrame::ISO5457);
    PREVIEW->setNUMOPTLINES(numOptLines);
    PREVIEW->setTITELBLOCKFIELDS(titelblockFields);
    PREVIEW->setREVHISTORY(revHistory);
    PREVIEW->setREVHISTORYSTYLE(RevHistoryStyle::ASME_Y14_35_Width180);
    PREVIEW->setREVHISTORYFIELDS(revHistoryFields);
    PREVIEW->setFOLDLINES(foldLines);
    PREVIEW->setFOLDLINETARGET(foldLinesTaget);
    PREVIEW->setSMALLPARTSLIST(smallPartsList);
    PREVIEW->setSMALLPARTSLISTFIELDS(smallPartsListFileds);
    PREVIEW->setFULLSHEETPARTSLIST(fullSheetPartsList);
    PREVIEW->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
    PREVIEW->setLOGO(logo);
    PREVIEW->setLOGODIR(logoDir);

    PREVIEW->setISO7200OPTIONS(ISO7200OPTIONS);
    PREVIEW->setASME_Y14_35_WIDTH180OPTIONS(ASME_Y14_35_WIDTH180);
    PREVIEW->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
    PREVIEW->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);


    ui->gridLayout_4->addWidget(PREVIEW.get());
}

void ISO7200Dialog::updatePreview()
{
    if(DIALOGRUNNING){
        // Preview
        SheetSize sheetSize = SheetSize{"ISO7200", 210, 150};
        QString sheetName = "ISO7200";
        QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
        qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
        QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
        bool revHistory = false;
        bool foldLines = false;
        SheetSize foldLinesTaget = SheetSize{"ISO7200", 210, 250};
        bool smallPartsList = false;
        QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
        bool fullSheetPartsList = false;
        QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
        bool logo = false;
        QString logoDir = "";

        QDir dir;
        dir.mkdir(QDir::currentPath() + "/tmp");
        //TemplateGenKiCAD_5 KiCAD5(this);
        PREVIEW->setDIR(QDir::currentPath() + "/tmp");
        PREVIEW->setSHEETSIZE(sheetSize);
        PREVIEW->setSHEETNAME(sheetName);
        PREVIEW->setSHEETTITLEBLOCK(SheetTitleblock::ISO7200);
        PREVIEW->setSHEETFRAME(SheetFrame::ISO5457);
        PREVIEW->setNUMOPTLINES(numOptLines);
        PREVIEW->setTITELBLOCKFIELDS(titelblockFields);
        PREVIEW->setREVHISTORY(revHistory);
        PREVIEW->setREVHISTORYSTYLE(RevHistoryStyle::ASME_Y14_35_Width180);
        PREVIEW->setREVHISTORYFIELDS(revHistoryFields);
        PREVIEW->setFOLDLINES(foldLines);
        PREVIEW->setFOLDLINETARGET(foldLinesTaget);
        PREVIEW->setSMALLPARTSLIST(smallPartsList);
        PREVIEW->setSMALLPARTSLISTFIELDS(smallPartsListFileds);
        PREVIEW->setFULLSHEETPARTSLIST(fullSheetPartsList);
        PREVIEW->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
        PREVIEW->setLOGO(logo);
        PREVIEW->setLOGODIR(logoDir);
        PREVIEW->setMinimumWidth(this->size().width()/2);

        PREVIEW->setISO7200OPTIONS(ISO7200OPTIONS);
        PREVIEW->setASME_Y14_35_WIDTH180OPTIONS(ASME_Y14_35_WIDTH180);
        PREVIEW->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
        PREVIEW->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);
        PREVIEW->update();
    }
}

ISO7200Dialog::ISO7200Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ISO7200Dialog)
{
    ui->setupUi(this);
}

ISO7200Dialog::ISO7200Dialog(std::shared_ptr<ISO7200Options> iso7200options, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ISO7200Dialog)
{
    ui->setupUi(this);
    setISO7200OPTIONS(iso7200options);
}

ISO7200Dialog::~ISO7200Dialog()
{
    delete ui;
}


void ISO7200Dialog::on_buttonBox_rejected()
{
    ISO7200OPTIONS->resetToStd();
}

void ISO7200Dialog::on_opt23PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD()["opt23"]);
    changeWindow.setFIELD_KICAD5(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5()["opt23"]);
    changeWindow.setFIELD_KICAD6(ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6()["opt23"]);
    changeWindow.setFIELD_PDF(ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF()["opt23"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ISO7200OPTIONS->setTITELBLOCKFIELD_FREECAD("opt23", changeWindow.getFIELD_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD5("opt23", changeWindow.getFIELD_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELD_KICAD6("opt23", changeWindow.getFIELD_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELD_PDF("opt23", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}

std::shared_ptr<ISO7200Options> ISO7200Dialog::getISO7200OPTIONS() const
{
    return ISO7200OPTIONS;
}

void ISO7200Dialog::setISO7200OPTIONS(const std::shared_ptr<ISO7200Options> &newISO7200OPTIONS)
{
    ISO7200OPTIONS = newISO7200OPTIONS;
    loadOptions();
    loadPreview();
    DIALOGRUNNING = true;
    updatePreview();
}


void ISO7200Dialog::on_opt16PushButton_pressed()
{
}



void ISO7200Dialog::on_OptLinesSpinBox_valueChanged(int arg1)
{
    ISO7200OPTIONS->setNumOptLins(arg1);
    updatePreview();
}


void ISO7200Dialog::on_DescriptionCheckBox_stateChanged(int arg1)
{
    ISO7200OPTIONS->setDescField(arg1);
    updatePreview();
}


void ISO7200Dialog::on_DescriptionSpinBox_valueChanged(int arg1)
{
    ISO7200OPTIONS->setNumDescLines(arg1);
    updatePreview();
}

void ISO7200Dialog::resizeEvent(QResizeEvent *)
{
    updatePreview();
}

