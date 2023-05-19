#ifndef ASME_Y14_35_WIDTH180_H
#define ASME_Y14_35_WIDTH180_H

#include <QDialog>
#include <QDir>

#include "templateoptions.h"
#include "asme_y14_35_width180options.h"
#include "changetitelblockfield.h"

#include "preview.h"

namespace Ui {
class ASME_Y14_35_Width180Dialog;
}

///
/// \brief The ASME_Y14_35_Width180Dialog classcontains all options for the ASME Y14.35 Revision history style, whit this class it is alsow posible to change them with a window.
///
class ASME_Y14_35_Width180Dialog : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief ASME_Y14_35_Width180Dialog constructor
    /// \param parent is the Qt Parent parameter
    ///
    explicit ASME_Y14_35_Width180Dialog(QWidget *parent = nullptr);
    ///
    /// \brief ASME_Y14_35_Width180Dialog constructor
    /// \param parent is the Qt Parent parameter
    ///
    explicit ASME_Y14_35_Width180Dialog(std::shared_ptr<ASME_Y14_35_Width180Options> newASME_Y14_35_WIDTH180OPTIONS, QWidget *parent = nullptr);
    ///
    /// \brief ASME_Y14_35_Width180Dialog deconstructor
    ///
    ~ASME_Y14_35_Width180Dialog();

    std::shared_ptr<ASME_Y14_35_Width180Options> getASME_Y14_35_WIDTH180OPTIONS() const;
    void setASME_Y14_35_WIDTH180OPTIONS(const std::shared_ptr<ASME_Y14_35_Width180Options> &newASME_Y14_35_WIDTH180OPTIONS);

private slots:
    ///
    /// \brief on_buttonBox_rejected is the event when the reject button is clicked
    ///
    void on_buttonBox_rejected();

    ///
    /// \brief on_headPushButton_clicked is the event when the head option buttion is clicked
    ///
    void on_headPushButton_clicked();

    ///
    /// \brief on_revOpt1PushButton_clicked is the event when the option 1 buttion is clicked
    ///
    void on_revOpt1PushButton_clicked();

    ///
    /// \brief on_revOpt2PushButton_clicked is the event when the option 2 buttion is clicked
    ///
    void on_revOpt2PushButton_clicked();

    ///
    /// \brief on_revOpt3PushButton_clicked is the event when the option 3 buttion is clicked
    ///
    void on_revOpt3PushButton_clicked();

    ///
    /// \brief on_revOpt4PushButton_clicked is the event when the option 4 buttion is clicked
    ///
    void on_revOpt4PushButton_clicked();

    ///
    /// \brief on_revOpt5PushButton_clicked is the event when the option 5 buttion is clicked
    ///
    void on_revOpt5PushButton_clicked();

    void on_buttonBox_accepted();

    void on_numRevSpinBox_valueChanged(int arg1);

    void on_numLinesRevSpinBox_valueChanged(int arg1);

private:
    ///
    /// \brief ui is the pointer fo the qt UI
    ///
    Ui::ASME_Y14_35_Width180Dialog *ui;

    void resizeEvent(QResizeEvent*);

    std::shared_ptr<ASME_Y14_35_Width180Options> ASME_Y14_35_WIDTH180OPTIONS;

    std::shared_ptr<Preview> PREVIEW;
    std::shared_ptr<ISO7200Options> ISO7200OPTIONS =  std::shared_ptr<ISO7200Options>(new ISO7200Options(this));
    std::shared_ptr<FullSheetsPartListOptions> FULLSHEETPARTLISTOPIONS = std::shared_ptr<FullSheetsPartListOptions>(new FullSheetsPartListOptions(this));
    std::shared_ptr<SmallPartsListOptions> SMALLPARTSLISTSOPTIONS = std::shared_ptr<SmallPartsListOptions>(new SmallPartsListOptions(this));

    bool DIALOGRUNNING = false;

    ///
    /// \brief loadButtonText loads the lable as text to display
    ///
    void loadButtonText();

    void loadPreview();

    void updatePreview();
};

#endif // ASME_Y14_35_WIDTH180_H
