#include "kicad_symbol_scaler.h"
#include <QDebug>
#include <clocale>

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

const std::vector<std::string> &KiCAD_Symbol_Scaler::getLines() const
{
    return Lines;
}

void KiCAD_Symbol_Scaler::setLines(const std::vector<std::string> &newLines)
{
    Lines = newLines;
}

double KiCAD_Symbol_Scaler::getScale() const
{
    return Scale;
}

void KiCAD_Symbol_Scaler::setScale(double newScale)
{
    Scale = newScale;
}

KiCAD_Symbol_Scaler::KiCAD_Symbol_Scaler()
{
}

void KiCAD_Symbol_Scaler::scale()
{
    std::setlocale(LC_ALL, "en_US.UTF-8");
    for(int i = 0; i < Lines.size(); i++)
    {
        if(Lines[i].find("size ") != std::string::npos)
        {
            std::string xStr = "";
            std::string yStr = "";
            int cIndex = 0;
            do
            {
                cIndex++;
                xStr += Lines[i].at(Lines[i].find("size ") + 4 + cIndex);
            }while(Lines[i].at(Lines[i].find("size ") + 4 + cIndex) != ' ');
            double x = std::stod(xStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("size ") + 5, xStr.length(), std::to_string(x));
            int xOff = 4 + std::to_string(x).length();
            cIndex = 0;
            do
            {
                cIndex++;
                yStr += Lines[i].at(Lines[i].find("size ") + xOff + cIndex);
            }while(Lines[i].at(Lines[i].find("size ") + xOff + cIndex) != ' ' && Lines[i].at(Lines[i].find("size ") + xOff + cIndex) != ')');
            double y = std::stod(yStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("size ") + xOff, yStr.length(), " " + std::to_string(y));
        }
        if(Lines[i].find("at ") != std::string::npos)
        {
            std::string xStr = "";
            std::string yStr = "";
            int cIndex = 0;
            do
            {
                cIndex++;
                xStr += Lines[i].at(Lines[i].find("at ") + 2 + cIndex);
            }while(Lines[i].at(Lines[i].find("at ") + 2 + cIndex) != ' ');
            double x = std::stod(xStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("at ") + 3, xStr.length(), std::to_string(x) + " ");

            int xOff = 3 + std::to_string(x).length();
            cIndex = 0;
            do
            {
                cIndex++;
                yStr += Lines[i].at(Lines[i].find("at ") + xOff + cIndex);
            }while(Lines[i].at(Lines[i].find("at ") + xOff + cIndex) != ' ');
            double y = std::stod(yStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("at ") + xOff, yStr.length(), " " + std::to_string(y));
        }
        if(Lines[i].find("length ") != std::string::npos)
        {
            qDebug() << Lines[i].c_str();
            std::string xStr = "";
            int cIndex = 0;
            do
            {
                cIndex++;
                xStr += Lines[i].at(Lines[i].find("length ") + 6 + cIndex);
            }while(Lines[i].at(Lines[i].find("length ") + 6 + cIndex) != ' ' && Lines[i].at(Lines[i].find("length ") + 6 + cIndex) != ')');
            double x = std::stod(xStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("length ") + 7, xStr.length(), std::to_string(x));
            qDebug() << Lines[i].c_str();
        }
        if(Lines[i].find("start ") != std::string::npos)
        {
            std::string xStr = "";
            std::string yStr = "";
            int cIndex = 0;
            do
            {
                cIndex++;
                xStr += Lines[i].at(Lines[i].find("start ") + 5 + cIndex);
            }while(Lines[i].at(Lines[i].find("start ") + 5 + cIndex) != ' ');
            double x = std::stod(xStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("start ") + 6, xStr.length(), std::to_string(x));
            int xOff = 5 + std::to_string(x).length();
            cIndex = 0;
            do
            {
                cIndex++;
                yStr += Lines[i].at(Lines[i].find("start ") + xOff + cIndex);
            }while(Lines[i].at(Lines[i].find("start ") + xOff + cIndex) != ' ' && Lines[i].at(Lines[i].find("start ") + xOff + cIndex) != ')');
            double y = std::stod(yStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("start ") + xOff, yStr.length(), " " + std::to_string(y));
        }
        if(Lines[i].find("end ") != std::string::npos)
        {
            std::string xStr = "";
            std::string yStr = "";
            int cIndex = 0;
            do
            {
                cIndex++;
                xStr += Lines[i].at(Lines[i].find("end ") + 3 + cIndex);
            }while(Lines[i].at(Lines[i].find("end ") + 3 + cIndex) != ' ');
            double x = std::stod(xStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("end ") + 4, xStr.length(), std::to_string(x));
            int xOff = 3 + std::to_string(x).length();
            cIndex = 0;
            do
            {
                cIndex++;
                yStr += Lines[i].at(Lines[i].find("end ") + xOff + cIndex);
            }while(Lines[i].at(Lines[i].find("end ") + xOff + cIndex) != ' ' && Lines[i].at(Lines[i].find("end ") + xOff + cIndex) != ')');
            double y = std::stod(yStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("end ") + xOff, yStr.length(), " " + std::to_string(y));
        }
        if(Lines[i].find("xy ") != std::string::npos)
        {
            std::string xStr = "";
            std::string yStr = "";
            int cIndex = 0;
            do
            {
                cIndex++;
                xStr += Lines[i].at(Lines[i].find("xy ") + 2 + cIndex);
            }while(Lines[i].at(Lines[i].find("xy ") + 2 + cIndex) != ' ');
            double x = std::stod(xStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("xy ") + 3, xStr.length(), std::to_string(x) + " ");

            int xOff = 3 + std::to_string(x).length();
            cIndex = 0;
            do
            {
                cIndex++;
                yStr += Lines[i].at(Lines[i].find("xy ") + xOff + cIndex);
            }while(Lines[i].at(Lines[i].find("xy ") + xOff + cIndex) != ' ' && Lines[i].at(Lines[i].find("xy ") + xOff + cIndex) != ')');
            double y = std::stod(yStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("xy ") + xOff, yStr.length(), " " + std::to_string(y));
        }
        if(Lines[i].find("mid ") != std::string::npos)
        {
            std::string xStr = "";
            std::string yStr = "";
            int cIndex = 0;
            do
            {
                cIndex++;
                xStr += Lines[i].at(Lines[i].find("mid ") + 3 + cIndex);
            }while(Lines[i].at(Lines[i].find("mid ") + 3 + cIndex) != ' ');
            double x = std::stod(xStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("mid ") + 4, xStr.length(), std::to_string(x));
            int xOff = 3 + std::to_string(x).length();
            cIndex = 0;
            do
            {
                cIndex++;
                yStr += Lines[i].at(Lines[i].find("mid ") + xOff + cIndex);
            }while(Lines[i].at(Lines[i].find("mid ") + xOff + cIndex) != ' ' && Lines[i].at(Lines[i].find("mid ") + xOff + cIndex) != ')');
            double y = std::stod(yStr) * double(Scale/1.27);
            Lines[i].replace(Lines[i].find("mid ") + xOff, yStr.length(), " " + std::to_string(y));
        }
    }
}
