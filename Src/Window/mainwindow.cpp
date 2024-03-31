#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_preView = std::make_shared<PreView>();

    m_ui->PreViewGridLayout->addWidget(m_preView.get());
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_GeneratePushButton_clicked() { }

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_preView->setMinimumWidth(m_ui->centralwidget->size().width() - 800);
    QWidget::resizeEvent(event);
}
