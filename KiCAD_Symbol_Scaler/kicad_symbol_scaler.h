#ifndef KICAD_SYMBOL_SCALER_H
#define KICAD_SYMBOL_SCALER_H

#include <string>
#include <vector>

class KiCAD_Symbol_Scaler
{
private:
    std::vector<std::string> Lines;
    double Scale;
    std::string LibName;
public:
    KiCAD_Symbol_Scaler();
    void scale();
    const std::vector<std::string> &getLines() const;
    void setLines(const std::vector<std::string> &newLines);
    double getScale() const;
    void setScale(double newScale);
    const std::string &getLibName() const;
    void setLibName(const std::string &newLibName);
};

#endif // KICAD_SYMBOL_SCALER_H
