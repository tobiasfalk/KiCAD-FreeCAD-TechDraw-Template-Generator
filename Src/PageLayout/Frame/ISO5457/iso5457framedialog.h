#ifndef ISO5457FRAMEDIALOG_H
#define ISO5457FRAMEDIALOG_H

#include <QDialog>

#include "PageLayout/Frame/ISO5457/iso5457frame.h"

namespace Ui {
class ISO5457FrameDialog;
}

///
/// \brief The ISO5457FrameDialog class creates a dialog for setting the options of the ISO5457Frame
///
class ISO5457FrameDialog : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief ISO5457FrameDialog the base constructor
    /// \param parent the Qt Parent pointer
    ///
    explicit ISO5457FrameDialog(QWidget *parent = nullptr);
    ~ISO5457FrameDialog();

    ///
    /// \brief frame returns a frame with the given settings
    /// \return
    ///
    std::shared_ptr<ISO5457Frame> frame() const;
    ///
    /// \brief setFrame takes the given settings a a base
    /// \param newFrame
    ///
    void setFrame(const std::shared_ptr<ISO5457Frame> &newFrame);

private:
    ///
    /// \brief m_ui the Qt Ui pointer
    ///
    Ui::ISO5457FrameDialog *m_ui;
    ///
    /// \brief m_frame is the frame with the given parameters
    ///
    std::shared_ptr<ISO5457Frame> m_frame;
};

#endif // ISO5457FRAMEDIALOG_H
