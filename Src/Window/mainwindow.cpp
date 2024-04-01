#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pagestyle.h"
#include "universaldrawthread.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_preView = std::make_shared<PreView>();

    m_ui->PreViewGridLayout->addWidget(m_preView.get());

    for (int i = 0; i < 10; i++) {

        UniversalDrawThread *thread = new UniversalDrawThread(
                "./mulTest_" + QString::number(i), PageStyle{}, DrawingFormate::FreeCADSvg);

        connect(thread, &UniversalDrawThread::resultReady, this, &MainWindow::handleResults);

        thread->start();
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_GeneratePushButton_clicked() { }

void MainWindow::handleResults(UniversalDrawThread *thread)
{
    qDebug() << thread->fileName();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_preView->setMinimumWidth(m_ui->centralwidget->size().width() - 800);
    QWidget::resizeEvent(event);
}
