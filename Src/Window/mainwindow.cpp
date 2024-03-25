#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    preView = std::make_shared<PreView>();

    ui->PreViewGridLayout->addWidget(preView.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_GeneratePushButton_clicked() { }

void MainWindow::resizeEvent(QResizeEvent *event)
{
    preView->setMinimumWidth(ui->centralwidget->size().width() - 800);
    QWidget::resizeEvent(event);
}
