#ifndef ISO7200DIALOG_H
#define ISO7200DIALOG_H

#include <QDialog>
#include <QFileDialog>

#include "templateoptions.h"
#include "iso7200options.h"

#include "preview.h"

namespace Ui {
class ISO7200Dialog;
}

class ISO7200Dialog : public QDialog
{
    Q_OBJECT
private slots:
    ///
    /// \brief on_opt1PushButton_clicked is the event when the option 1 buttion is clicked
    ///
    void on_opt1PushButton_clicked();
    ///
    /// \brief on_opt2PushButton_clicked is the event when the option 2 buttion is clicked
    ///
    void on_opt2PushButton_clicked();
    ///
    /// \brief on_opt3PushButton_clicked is the event when the option 3 buttion is clicked
    ///
    void on_opt3PushButton_clicked();
    ///
    /// \brief on_opt4PushButton_clicked is the event when the option 4 buttion is clicked
    ///
    void on_opt4PushButton_clicked();
    ///
    /// \brief on_opt5PushButton_clicked is the event when the option 5 buttion is clicked
    ///
    void on_opt5PushButton_clicked();
    ///
    /// \brief on_opt6PushButton_clicked is the event when the option 6 buttion is clicked
    ///
    void on_opt6PushButton_clicked();
    ///
    /// \brief on_opt7PushButton_clicked is the event when the option 7 buttion is clicked
    ///
    void on_opt7PushButton_clicked();
    ///
    /// \brief on_opt8PushButton_clicked is the event when the option 8 buttion is clicked
    ///
    void on_opt8PushButton_clicked();
    ///
    /// \brief on_opt9PushButton_clicked is the event when the option 9 buttion is clicked
    ///
    void on_opt9PushButton_clicked();
    ///
    /// \brief on_opt10PushButton_clicked is the event when the option 10 buttion is clicked
    ///
    void on_opt10PushButton_clicked();
    ///
    /// \brief on_opt11PushButton_clicked is the event when the option 11 buttion is clicked
    ///
    void on_opt11PushButton_clicked();
    ///
    /// \brief on_opt12PushButton_clicked is the event when the option 12 buttion is clicked
    ///
    void on_opt12PushButton_clicked();
    ///
    /// \brief on_opt13PushButton_clicked is the event when the option 13 buttion is clicked
    ///
    void on_opt13PushButton_clicked();
    ///
    /// \brief on_opt14PushButton_clicked is the event when the option 14 buttion is clicked
    ///
    void on_opt14PushButton_clicked();
    ///
    /// \brief on_opt15PushButton_clicked is the event when the option 15 buttion is clicked
    ///
    void on_opt15PushButton_clicked();
    ///
    /// \brief on_opt16PushButton_clicked is the event when the option 16 buttion is clicked
    ///
    void on_opt16PushButton_clicked();
    ///
    /// \brief on_opt17PushButton_clicked is the event when the option 17 buttion is clicked
    ///
    void on_opt17PushButton_clicked();
    ///
    /// \brief on_opt18PushButton_clicked is the event when the option 18 buttion is clicked
    ///
    void on_opt18PushButton_clicked();
    ///
    /// \brief on_opt19PushButton_clicked is the event when the option 19 buttion is clicked
    ///
    void on_opt19PushButton_clicked();
    ///
    /// \brief on_opt20PushButton_clicked is the event when the option 20 buttion is clicked
    ///
    void on_opt20PushButton_clicked();
    ///
    /// \brief on_opt21PushButton_clicked is the event when the option 21 buttion is clicked
    ///
    void on_opt21PushButton_clicked();
    ///
    /// \brief on_opt22PushButton_clicked is the event when the option 22 buttion is clicked
    ///
    void on_opt22PushButton_clicked();

    ///
    /// \brief on_buttonBox_rejected is the event when the rejekt buttion is clicked, it resets all the field maps to its origin
    ///
    void on_buttonBox_rejected();

    ///
    /// \brief on_opt23PushButton_clicked is the event when the option 23 buttion is clicked
    ///
    void on_opt23PushButton_clicked();

    void on_opt16PushButton_pressed();

    void on_trimmingMarksCheckBox_stateChanged(int arg1);

    void on_OptLinesSpinBox_valueChanged(int arg1);

    void on_DescriptionCheckBox_stateChanged(int arg1);

    void on_DescriptionSpinBox_valueChanged(int arg1);

private:
    ///
    /// \brief ui is the pointer fo the qt UI
    ///
    Ui::ISO7200Dialog *ui;

    void resizeEvent(QResizeEvent*);

    std::shared_ptr<ISO7200Options> ISO7200OPTIONS;

    std::shared_ptr<Preview> PREVIEW;
    std::shared_ptr<ASME_Y14_35_Width180Options> ASME_Y14_35_WIDTH180 = std::shared_ptr<ASME_Y14_35_Width180Options>(new ASME_Y14_35_Width180Options(this));
    std::shared_ptr<FullSheetsPartListOptions> FULLSHEETPARTLISTOPIONS = std::shared_ptr<FullSheetsPartListOptions>(new FullSheetsPartListOptions(this));
    std::shared_ptr<SmallPartsListOptions> SMALLPARTSLISTSOPTIONS = std::shared_ptr<SmallPartsListOptions>(new SmallPartsListOptions(this));

    bool DIALOGRUNNING = false;

    ///
    /// \brief loadButtonText loads all the Text that appiers on the Buttons
    ///
    void loadButtonText();

    void loadOptions();

    void loadPreview();

    void updatePreview();

public:
    ///
    /// \brief ISO7200Dialog constructor
    /// \param parent qt parent pointer
    ///
    explicit ISO7200Dialog(QWidget *parent = nullptr);
    ///
    /// \brief ISO7200Dialog constructor
    /// \param parent qt parent pointer
    ///
    explicit ISO7200Dialog(std::shared_ptr<ISO7200Options> iso7200options, QWidget *parent = nullptr);
    ///
    /// \brief ISO7200Dialog deconstructor
    ///
    ~ISO7200Dialog();

    std::shared_ptr<ISO7200Options> getISO7200OPTIONS() const;

    void setISO7200OPTIONS(const std::shared_ptr<ISO7200Options> &newISO7200OPTIONS);
};

#endif // ISO7200DIALOG_H
