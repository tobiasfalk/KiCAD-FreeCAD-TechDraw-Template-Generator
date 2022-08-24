#ifndef KICAD_SYMBOL_SCALER_H
#define KICAD_SYMBOL_SCALER_H

#include <string>
#include <vector>

class KiCAD_Symbol_Scaler
{
private:
    std::vector<std::string> Lines;
    double Scale;
public:
    KiCAD_Symbol_Scaler();
    void scale();
    const std::vector<std::string> &getLines() const;
    void setLines(const std::vector<std::string> &newLines);
    double getScale() const;
    void setScale(double newScale);
};

#endif // KICAD_SYMBOL_SCALER_H
