#ifndef PLAINFRAMEDIALOG_H
#define PLAINFRAMEDIALOG_H

#include <QDialog>
#include "PageLayout/Frame/Plain/plainframe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PlainFrameDialog;
}
QT_END_NAMESPACE

///
/// \brief The PlainFrameDialog class creates a dialog to set the parameters of the PlainFrame
///
class PlainFrameDialog : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief PlainFrameDialog is the base constructor
    /// \param parent is the Qt parent pointer
    ///
    explicit PlainFrameDialog(QWidget *parent = nullptr);
    ~PlainFrameDialog();

    ///
    /// \brief setFrame sets the parameters to those of a existing frame
    /// \param newFrame
    ///
    void setFrame(std::shared_ptr<PlainFrame> newFrame);
    ///
    /// \brief frame returns a frame with the set parameters
    /// \return
    ///
    std::shared_ptr<PlainFrame> frame();

private slots:
    void on_LineWidthDoubleSpinBox_editingFinished();

    void on_TopDoubleSpinBox_editingFinished();

    void on_RightDoubleSpinBox_editingFinished();

    void on_LeftDoubleSpinBox_editingFinished();

    void on_BottomDoubleSpinBox_editingFinished();

private:
    ///
    /// \brief m_ui is the Qt Ui pointer
    ///
    Ui::PlainFrameDialog *m_ui;
    ///
    /// \brief m_frame is the frame with the given parameters
    ///
    std::shared_ptr<PlainFrame> m_frame;
};

#endif // PLAINFRAMEDIALOG_H
