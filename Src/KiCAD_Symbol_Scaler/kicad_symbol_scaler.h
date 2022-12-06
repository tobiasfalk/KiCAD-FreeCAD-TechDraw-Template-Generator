#ifndef KICAD_SYMBOL_SCALER_H
#define KICAD_SYMBOL_SCALER_H

#include <string>
#include <vector>

///
/// \brief The KiCAD_Symbol_Scaler class is the pure C++ class that scales a list of KiCAD Symbols a given factor
///
class KiCAD_Symbol_Scaler
{
private:
    ///
    /// \brief Lines is a Vector that Contains all the lines of the Symbol library
    ///
    std::vector<std::string> Lines;
    ///
    /// \brief Scale is the scale that the Symbols are scaled with
    ///
    double Scale;
    ///
    /// \brief LibName is a String that contanins the name of the Symbol library
    ///
    std::string LibName;
public:
    ///
    /// \brief KiCAD_Symbol_Scaler is the construktor of the class
    ///
    KiCAD_Symbol_Scaler();
    ///
    /// \brief scale is the function that runs the scaling of the Symbol library
    ///
    void scale();
    ///
    /// \brief getLines retunrs the Vector of the Symbol library lines
    /// \return the Vector
    ///
    const std::vector<std::string> &getLines() const;
    ///
    /// \brief setLines sets the Vector with all the Symbol library lines
    /// \param newLines the Vector
    ///
    void setLines(const std::vector<std::string> &newLines);
    ///
    /// \brief getScale retuns the scale that the Symbol Library is scaled with
    /// \return the scale
    ///
    double getScale() const;
    ///
    /// \brief setScale sets the scale that the Symbol Library is scaled with
    /// \param newScale the scale
    ///
    void setScale(double newScale);
    ///
    /// \brief getLibName returns the name of the Symbol Library
    /// \return the name
    ///
    const std::string &getLibName() const;
    ///
    /// \brief setLibName sets the name of the Symbol Library
    /// \param newLibName the name
    ///
    void setLibName(const std::string &newLibName);
};

#endif // KICAD_SYMBOL_SCALER_H
