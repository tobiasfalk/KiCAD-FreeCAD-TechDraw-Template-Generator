#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <utility>

#include <QFileDialog>
#include <QMainWindow>

#include "universaldraw.h"
#include "PreView/preview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
} // namespace Ui
QT_END_NAMESPACE

///
/// \brief The MainWindow class
///
/// The MainWindow class creates and manages the main Window
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief MainWindow it is the constructor of this class and initelizes tis class
    /// \param parent is the Qt parent object pointer
    ///
    explicit MainWindow(QWidget *parent = nullptr);
    ///
    /// \brief is the deconstructor
    ///
    ~MainWindow() override;

private slots:
    void on_GeneratePushButton_clicked();

private:
    ///
    /// \brief ui is the pointer to the ui and through this all the elements of the ui are accesed
    /// through this
    ///
    Ui::MainWindow *ui;

    std::shared_ptr<PreView> preView;

    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
