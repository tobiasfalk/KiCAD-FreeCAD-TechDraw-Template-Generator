#include "iso7200options.h"
#include "ui_iso7200options.h"

void ISO7200Options::on_opt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt1"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt1"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt1"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt1"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt1"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt1"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt1"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt2"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt2"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt2"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt2"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt2"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt2"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt2"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt3"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt3"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt3"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt3"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt3"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt3"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt3"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt4"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt4"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt4"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt4"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt4"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt4"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt4"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt5"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt5"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt5"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt5"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt5"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt5"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt5"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt6PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt6"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt6"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt6"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt6"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt6"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt6"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt6"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt6"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt7PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt7"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt7"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt7"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt7"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt7"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt7"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt7"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt7"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt8PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt8"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt8"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt8"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt8"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt8"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt8"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt8"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt8"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt9PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt9"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt9"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt9"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt9"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt9"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt9"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt9"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt9"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt10PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt10"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt10"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt10"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt10"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt10"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt10"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt10"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt10"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt11PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt11"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt11"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt11"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt11"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt11"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt11"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt11"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt11"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt12PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt12"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt12"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt12"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt12"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt12"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt12"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt12"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt12"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt13PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt13"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt13"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt13"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt13"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt13"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt13"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt13"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt13"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt14PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt14"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt14"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt14"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt14"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt14"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt14"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt14"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt14"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt15PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt15"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt15"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt15"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt15"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt15"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt15"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt15"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt15"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt16PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt16"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt16"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt16"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt16"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt16"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt16"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt16"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt16"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt17PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt17"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt17"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt17"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt17"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt17"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt17"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt17"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt17"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt18PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt18"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt18"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt18"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt18"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt18"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt18"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt18"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt18"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt19PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt19"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt19"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt19"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt19"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt19"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt19"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt19"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt19"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt20PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt20"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt20"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt20"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt20"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt20"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt20"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt20"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt20"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt21PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt21"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt21"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt21"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt21"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt21"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt21"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt21"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt21"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::on_opt22PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(TITELBLOCKFIELDS_FREECAD["opt22"]);
    changeWindow.setFIELD_KICAD5(TITELBLOCKFIELDS_KICAD5["opt22"]);
    changeWindow.setFIELD_KICAD6(TITELBLOCKFIELDS_KICAD6["opt22"]);
    changeWindow.setFIELD_PDF(TITELBLOCKFIELDS_PDF["opt22"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        TITELBLOCKFIELDS_FREECAD["opt22"] = changeWindow.getFIELD_FREECAD();
        TITELBLOCKFIELDS_KICAD5["opt22"] = changeWindow.getFIELD_KICAD5();
        TITELBLOCKFIELDS_KICAD6["opt22"] = changeWindow.getFIELD_KICAD6();
        TITELBLOCKFIELDS_PDF["opt22"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void ISO7200Options::loadStdOptions()
{
    // FreeCAD
    //                      key                     label                                       Value                                       Name
    TITELBLOCKFIELDS_FREECAD.insert("opt1",  TitelblockField{"Option 1",                        QStringList{"."},                           "Option 1"});
    TITELBLOCKFIELDS_FREECAD.insert("opt2",  TitelblockField{"Option 2",                        QStringList{"."},                           "Option 2"});
    TITELBLOCKFIELDS_FREECAD.insert("opt3",  TitelblockField{"Option 3",                        QStringList{"."},                           "Option 3"});
    TITELBLOCKFIELDS_FREECAD.insert("opt4",  TitelblockField{"Surface treatment",               QStringList{"."},                           "Surface treatment"});
    TITELBLOCKFIELDS_FREECAD.insert("opt5",  TitelblockField{"Weight",                          QStringList{"."},                           "Weight"});
    TITELBLOCKFIELDS_FREECAD.insert("opt6",  TitelblockField{"Standard",                        QStringList{"."},                           "Standard"});
    TITELBLOCKFIELDS_FREECAD.insert("opt7",  TitelblockField{"Option 7",                        QStringList{"."},                           "Option 7"});
    TITELBLOCKFIELDS_FREECAD.insert("opt8",  TitelblockField{"Raw dimensions",                  QStringList{"."},                           "Raw dimensions"});
    TITELBLOCKFIELDS_FREECAD.insert("opt9",  TitelblockField{"Scale",                           QStringList{"."},                           "Scale"});
    TITELBLOCKFIELDS_FREECAD.insert("opt10", TitelblockField{"Created by",                      QStringList{"."},                           "Created by"});
    TITELBLOCKFIELDS_FREECAD.insert("opt11", TitelblockField{"Valid from to",                   QStringList{"."},                           "Valid from to"});
    TITELBLOCKFIELDS_FREECAD.insert("opt12", TitelblockField{"Document state",                  QStringList{"."},                           "Document state"});
    TITELBLOCKFIELDS_FREECAD.insert("opt13", TitelblockField{"Approved by",                     QStringList{"."},                           "Approved by"});
    TITELBLOCKFIELDS_FREECAD.insert("opt14", TitelblockField{"Project",                         QStringList{"."},                           "Project"});
    TITELBLOCKFIELDS_FREECAD.insert("opt15", TitelblockField{"Document type",                   QStringList{"."},                           "Document type"});
    TITELBLOCKFIELDS_FREECAD.insert("opt16", TitelblockField{"Legal owner",                     QStringList{"."},                           "Legal owner"});
    TITELBLOCKFIELDS_FREECAD.insert("opt17", TitelblockField{"Title, Supplementary title",      QStringList{"."},                           "Title, Supplementary title"});
    TITELBLOCKFIELDS_FREECAD.insert("opt18", TitelblockField{"Document number",                 QStringList{"."},                           "Document number"});
    TITELBLOCKFIELDS_FREECAD.insert("opt19", TitelblockField{"Rev.",                            QStringList{"."},                           "Rev."});
    TITELBLOCKFIELDS_FREECAD.insert("opt20", TitelblockField{"Date of issue",                   QStringList{"."},                           "Date of issue"});
    TITELBLOCKFIELDS_FREECAD.insert("opt21", TitelblockField{"Lang.",                           QStringList{"EN"},                          "Lang."});
    TITELBLOCKFIELDS_FREECAD.insert("opt22", TitelblockField{"Sheet",                           QStringList{"."},                           "Sheet"});
    TITELBLOCKFIELDS_FREECAD_ORG = TITELBLOCKFIELDS_FREECAD;

    // KiCAD 5
    //                      key                     label                                      Value                                        Name
    TITELBLOCKFIELDS_KICAD5.insert("opt1",  TitelblockField{"Option 1",                        QStringList{"Option 1 Value"},               "Option 1"});
    TITELBLOCKFIELDS_KICAD5.insert("opt2",  TitelblockField{"Option 2",                        QStringList{"Option 2 Value"},               "Option 2"});
    TITELBLOCKFIELDS_KICAD5.insert("opt3",  TitelblockField{"Option 3",                        QStringList{"Option 2 Value"},               "Option 3"});
    TITELBLOCKFIELDS_KICAD5.insert("opt4",  TitelblockField{"Surface treatment",               QStringList{"Surface treatment Value"},      "Surface treatment"});
    TITELBLOCKFIELDS_KICAD5.insert("opt5",  TitelblockField{"Weight",                          QStringList{"Weight Value"},                 "Weight"});
    TITELBLOCKFIELDS_KICAD5.insert("opt6",  TitelblockField{"Standard",                        QStringList{"Standard Value"},               "Standard"});
    TITELBLOCKFIELDS_KICAD5.insert("opt7",  TitelblockField{"Option 7",                        QStringList{"Option 7 Value"},               "Option 7"});
    TITELBLOCKFIELDS_KICAD5.insert("opt8",  TitelblockField{"Raw dimensions",                  QStringList{"Raw dimensions Value"},         "Raw dimensions"});
    TITELBLOCKFIELDS_KICAD5.insert("opt9",  TitelblockField{"Scale",                           QStringList{"Scale Value"},                  "Scale"});
    TITELBLOCKFIELDS_KICAD5.insert("opt10", TitelblockField{"Created by",                      QStringList{"%C0"},                          "Created by"});
    TITELBLOCKFIELDS_KICAD5.insert("opt11", TitelblockField{"Valid from to",                   QStringList{"%D to -"},                      "Valid from to"});
    TITELBLOCKFIELDS_KICAD5.insert("opt12", TitelblockField{"Document state",                  QStringList{"-"},                            "Document state"});
    TITELBLOCKFIELDS_KICAD5.insert("opt13", TitelblockField{"Approved by",                     QStringList{"%C1"},                          "Approved by"});
    TITELBLOCKFIELDS_KICAD5.insert("opt14", TitelblockField{"Project",                         QStringList{"%C2"},                          "Project"});
    TITELBLOCKFIELDS_KICAD5.insert("opt15", TitelblockField{"Document type",                   QStringList{"%C3"},                          "Document type"});
    TITELBLOCKFIELDS_KICAD5.insert("opt16", TitelblockField{"Legal owner",                     QStringList{"%Y"},                           "Legal owner"});
    TITELBLOCKFIELDS_KICAD5.insert("opt17", TitelblockField{"Title, Supplementary title",      QStringList{"%T"},                           "Title, Supplementary title"});
    TITELBLOCKFIELDS_KICAD5.insert("opt18", TitelblockField{"Document number",                 QStringList{"%F"},                           "Document number"});
    TITELBLOCKFIELDS_KICAD5.insert("opt19", TitelblockField{"Rev.",                            QStringList{"%R"},                           "Rev."});
    TITELBLOCKFIELDS_KICAD5.insert("opt20", TitelblockField{"Date of issue",                   QStringList{"%D"},                           "Date of issue"});
    TITELBLOCKFIELDS_KICAD5.insert("opt21", TitelblockField{"Lang.",                           QStringList{"EN"},                           "Lang."});
    TITELBLOCKFIELDS_KICAD5.insert("opt22", TitelblockField{"Sheet",                           QStringList{"%S/%N"},                        "Sheet"});
    TITELBLOCKFIELDS_KICAD5_ORG = TITELBLOCKFIELDS_KICAD5;

    // KiCAD 6
    //                      key                     label                                      Value                                        Name
    TITELBLOCKFIELDS_KICAD6.insert("opt1",  TitelblockField{"Option 1",                        QStringList{"${opt1Val}"},                  "Option 1"});
    TITELBLOCKFIELDS_KICAD6.insert("opt2",  TitelblockField{"Option 2",                        QStringList{"${opt2Val}"},                  "Option 2"});
    TITELBLOCKFIELDS_KICAD6.insert("opt3",  TitelblockField{"Option 3",                        QStringList{"${opt3Val}"},                  "Option 3"});
    TITELBLOCKFIELDS_KICAD6.insert("opt4",  TitelblockField{"Surface treatment",               QStringList{"${surfaceTreatmentValue}"},    "Surface treatment"});
    TITELBLOCKFIELDS_KICAD6.insert("opt5",  TitelblockField{"Weight",                          QStringList{"${weightValue}"},              "Weight"});
    TITELBLOCKFIELDS_KICAD6.insert("opt6",  TitelblockField{"Standard",                        QStringList{"${standardValue}"},            "Standard"});
    TITELBLOCKFIELDS_KICAD6.insert("opt7",  TitelblockField{"Option 7",                        QStringList{"${opt7Val}"},                  "Option 7"});
    TITELBLOCKFIELDS_KICAD6.insert("opt8",  TitelblockField{"Raw dimensions",                  QStringList{"${rawDimValue}"},              "Raw dimensions"});
    TITELBLOCKFIELDS_KICAD6.insert("opt9",  TitelblockField{"Scale",                           QStringList{"${scaleVal}"},                 "Scale"});
    TITELBLOCKFIELDS_KICAD6.insert("opt10", TitelblockField{"Created by",                      QStringList{"${createdBy}"},                "Created by"});
    TITELBLOCKFIELDS_KICAD6.insert("opt11", TitelblockField{"Valid from to",                   QStringList{"${validFromTo}"},              "Valid from to"});
    TITELBLOCKFIELDS_KICAD6.insert("opt12", TitelblockField{"Document state",                  QStringList{"${docState}"},                 "Document state"});
    TITELBLOCKFIELDS_KICAD6.insert("opt13", TitelblockField{"Approved by",                     QStringList{"${approvedBy}"},               "Approved by"});
    TITELBLOCKFIELDS_KICAD6.insert("opt14", TitelblockField{"Project",                         QStringList{"${project}"},                  "Project"});
    TITELBLOCKFIELDS_KICAD6.insert("opt15", TitelblockField{"Document type",                   QStringList{"${docType}"},                  "Document type"});
    TITELBLOCKFIELDS_KICAD6.insert("opt16", TitelblockField{"Legal owner",                     QStringList{"${COMPANY}"},                  "Legal owner"});
    TITELBLOCKFIELDS_KICAD6.insert("opt17", TitelblockField{"Title, Supplementary title",      QStringList{"${TITLE}"},                    "Title, Supplementary title"});
    TITELBLOCKFIELDS_KICAD6.insert("opt18", TitelblockField{"Document number",                 QStringList{"${docNumber}"},                "Document number"});
    TITELBLOCKFIELDS_KICAD6.insert("opt19", TitelblockField{"Rev.",                            QStringList{"${REVISION}"},                 "Rev."});
    TITELBLOCKFIELDS_KICAD6.insert("opt20", TitelblockField{"Date of issue",                   QStringList{"${ISSUE_DATE}"},               "Date of issue"});
    TITELBLOCKFIELDS_KICAD6.insert("opt21", TitelblockField{"Lang.",                           QStringList{"${lang}"},                     "Lang."});
    TITELBLOCKFIELDS_KICAD6.insert("opt22", TitelblockField{"Sheet",                           QStringList{"${#}/${##}"},                  "Sheet"});
    TITELBLOCKFIELDS_KICAD6_ORG = TITELBLOCKFIELDS_KICAD6;

    // PDF
    //                      key                     label                                       Value                                       Name
    TITELBLOCKFIELDS_PDF.insert("opt1",  TitelblockField{"Option 1",                        QStringList{""},                           "Option 1"});
    TITELBLOCKFIELDS_PDF.insert("opt2",  TitelblockField{"Option 2",                        QStringList{""},                           "Option 2"});
    TITELBLOCKFIELDS_PDF.insert("opt3",  TitelblockField{"Option 3",                        QStringList{""},                           "Option 3"});
    TITELBLOCKFIELDS_PDF.insert("opt4",  TitelblockField{"Surface treatment",               QStringList{""},                           "Surface treatment"});
    TITELBLOCKFIELDS_PDF.insert("opt5",  TitelblockField{"Weight",                          QStringList{""},                           "Weight"});
    TITELBLOCKFIELDS_PDF.insert("opt6",  TitelblockField{"Standard",                        QStringList{""},                           "Standard"});
    TITELBLOCKFIELDS_PDF.insert("opt7",  TitelblockField{"Option 7",                        QStringList{""},                           "Option 7"});
    TITELBLOCKFIELDS_PDF.insert("opt8",  TitelblockField{"Raw dimensions",                  QStringList{""},                           "Raw dimensions"});
    TITELBLOCKFIELDS_PDF.insert("opt9",  TitelblockField{"Scale",                           QStringList{""},                           "Scale"});
    TITELBLOCKFIELDS_PDF.insert("opt10", TitelblockField{"Created by",                      QStringList{""},                           "Created by"});
    TITELBLOCKFIELDS_PDF.insert("opt11", TitelblockField{"Valid from to",                   QStringList{""},                           "Valid from to"});
    TITELBLOCKFIELDS_PDF.insert("opt12", TitelblockField{"Document state",                  QStringList{""},                           "Document state"});
    TITELBLOCKFIELDS_PDF.insert("opt13", TitelblockField{"Approved by",                     QStringList{""},                           "Approved by"});
    TITELBLOCKFIELDS_PDF.insert("opt14", TitelblockField{"Project",                         QStringList{""},                           "Project"});
    TITELBLOCKFIELDS_PDF.insert("opt15", TitelblockField{"Document type",                   QStringList{""},                           "Document type"});
    TITELBLOCKFIELDS_PDF.insert("opt16", TitelblockField{"Legal owner",                     QStringList{""},                           "Legal owner"});
    TITELBLOCKFIELDS_PDF.insert("opt17", TitelblockField{"Title, Supplementary title",      QStringList{""},                           "Title, Supplementary title"});
    TITELBLOCKFIELDS_PDF.insert("opt18", TitelblockField{"Document number",                 QStringList{""},                           "Document number"});
    TITELBLOCKFIELDS_PDF.insert("opt19", TitelblockField{"Rev.",                            QStringList{""},                           "Rev."});
    TITELBLOCKFIELDS_PDF.insert("opt20", TitelblockField{"Date of issue",                   QStringList{""},                           "Date of issue"});
    TITELBLOCKFIELDS_PDF.insert("opt21", TitelblockField{"Lang.",                           QStringList{"EN"},                          "Lang."});
    TITELBLOCKFIELDS_PDF.insert("opt22", TitelblockField{"Sheet",                           QStringList{""},                           "Sheet"});
    TITELBLOCKFIELDS_PDF_ORG = TITELBLOCKFIELDS_PDF;
}

void ISO7200Options::loadButtonText()
{
    ui->opt1PushButton->setText ("Option 1: "  + TITELBLOCKFIELDS_FREECAD["opt1"].Label);
    ui->opt2PushButton->setText ("Option 2: "  + TITELBLOCKFIELDS_FREECAD["opt2"].Label);
    ui->opt3PushButton->setText ("Option 3: "  + TITELBLOCKFIELDS_FREECAD["opt3"].Label);
    ui->opt4PushButton->setText ("Option 4: "  + TITELBLOCKFIELDS_FREECAD["opt4"].Label);
    ui->opt5PushButton->setText ("Option 5: "  + TITELBLOCKFIELDS_FREECAD["opt5"].Label);
    ui->opt6PushButton->setText ("Option 6: "  + TITELBLOCKFIELDS_FREECAD["opt6"].Label);
    ui->opt7PushButton->setText ("Option 7: "  + TITELBLOCKFIELDS_FREECAD["opt7"].Label);
    ui->opt8PushButton->setText ("Option 8: "  + TITELBLOCKFIELDS_FREECAD["opt8"].Label);
    ui->opt9PushButton->setText ("Option 9: "  + TITELBLOCKFIELDS_FREECAD["opt9"].Label);
    ui->opt10PushButton->setText("Option 10: " + TITELBLOCKFIELDS_FREECAD["opt10"].Label);
    ui->opt11PushButton->setText("Option 11: " + TITELBLOCKFIELDS_FREECAD["opt11"].Label);
    ui->opt12PushButton->setText("Option 12: " + TITELBLOCKFIELDS_FREECAD["opt12"].Label);
    ui->opt13PushButton->setText("Option 13: " + TITELBLOCKFIELDS_FREECAD["opt13"].Label);
    ui->opt14PushButton->setText("Option 14: " + TITELBLOCKFIELDS_FREECAD["opt14"].Label);
    ui->opt15PushButton->setText("Option 15: " + TITELBLOCKFIELDS_FREECAD["opt15"].Label);
    ui->opt16PushButton->setText("Option 16: " + TITELBLOCKFIELDS_FREECAD["opt16"].Label);
    ui->opt17PushButton->setText("Option 17: " + TITELBLOCKFIELDS_FREECAD["opt17"].Label);
    ui->opt18PushButton->setText("Option 18: " + TITELBLOCKFIELDS_FREECAD["opt18"].Label);
    ui->opt19PushButton->setText("Option 19: " + TITELBLOCKFIELDS_FREECAD["opt19"].Label);
    ui->opt20PushButton->setText("Option 20: " + TITELBLOCKFIELDS_FREECAD["opt20"].Label);
    ui->opt21PushButton->setText("Option 21: " + TITELBLOCKFIELDS_FREECAD["opt21"].Label);
    ui->opt22PushButton->setText("Option 22: " + TITELBLOCKFIELDS_FREECAD["opt22"].Label);
}

ISO7200Options::ISO7200Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ISO7200Options)
{
    ui->setupUi(this);
    loadStdOptions();
    loadButtonText();
}

ISO7200Options::~ISO7200Options()
{
    delete ui;
}

const QMap<QString, TitelblockField> &ISO7200Options::getTITELBLOCKFIELDS_FREECAD() const
{
    return TITELBLOCKFIELDS_FREECAD;
}


void ISO7200Options::on_buttonBox_rejected()
{
    TITELBLOCKFIELDS_FREECAD = TITELBLOCKFIELDS_FREECAD_ORG;
}

const QMap<QString, TitelblockField> &ISO7200Options::getTITELBLOCKFIELDS_PDF() const
{
    return TITELBLOCKFIELDS_PDF;
}

void ISO7200Options::setTITELBLOCKFIELDS_PDF(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_PDF)
{
    TITELBLOCKFIELDS_PDF = newTITELBLOCKFIELDS_PDF;
    TITELBLOCKFIELDS_PDF_ORG = newTITELBLOCKFIELDS_PDF;
}

const QMap<QString, TitelblockField> &ISO7200Options::getTITELBLOCKFIELDS_KICAD6() const
{
    return TITELBLOCKFIELDS_KICAD6;
}

void ISO7200Options::setTITELBLOCKFIELDS_KICAD6(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD6)
{
    TITELBLOCKFIELDS_KICAD6 = newTITELBLOCKFIELDS_KICAD6;
    TITELBLOCKFIELDS_KICAD6_ORG = newTITELBLOCKFIELDS_KICAD6;
}

const QMap<QString, TitelblockField> &ISO7200Options::getTITELBLOCKFIELDS_KICAD5() const
{
    return TITELBLOCKFIELDS_KICAD5;
}

void ISO7200Options::setTITELBLOCKFIELDS_KICAD5(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD5)
{
    TITELBLOCKFIELDS_KICAD5 = newTITELBLOCKFIELDS_KICAD5;
    TITELBLOCKFIELDS_KICAD5_ORG = newTITELBLOCKFIELDS_KICAD5;
}

void ISO7200Options::setTITELBLOCKFIELDS_FREECAD(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_FREECAD)
{
    TITELBLOCKFIELDS_FREECAD = newTITELBLOCKFIELDS_FREECAD;
    TITELBLOCKFIELDS_FREECAD_ORG = newTITELBLOCKFIELDS_FREECAD;
    loadButtonText();
}

