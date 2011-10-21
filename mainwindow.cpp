#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scaleFactor=1.0;
    ui->setupUi(this);

    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);

    ui->scrollArea->setWidget(ui->label);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    //setCentralWidget(ui->scrollArea);

    setWindowTitle(tr("Image Viewer"));
        resize(500, 400);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openfile()));
    connect(ui->actionAbout_Program, SIGNAL(triggered()), this, SLOT(aboutProg()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitApp()));
    connect(ui->actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui->actionNormal_Size, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(ui->actionFitToWindow, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(zoomOut()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(prev()));


    ui->actionFitToWindow->setEnabled(false);
    ui->actionFitToWindow->setCheckable(true);
    ui->actionFitToWindow->setShortcut(tr("Ctrl+F"));

    ui->actionNormal_Size->setShortcut(tr("Ctrl+S"));
    ui->actionNormal_Size->setEnabled(false);

    ui->actionZoomOut->setShortcut(tr("Ctrl+-"));
    ui->actionZoomOut->setEnabled(false);

    ui->actionZoomIn->setShortcut(tr("Ctrl++"));
    ui->actionZoomIn->setEnabled(false);

    ui->actionExit->setShortcut(tr("Ctrl+Q"));

    ui->actionOpen->setShortcut(tr("Ctrl+O"));

    namefilter.append("*.png");
    namefilter.append("*.jpg");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::next()
{
    ci++;
    if (ci>=fnlist.count())
    {
        ci=0;
    }
    openImg(fnlist[ci]);
}

void MainWindow::prev()
{
    ci--;
    if (ci<0)
    {
        ci=fnlist.count()-1;
    }
    openImg(fnlist[ci]);
}

void MainWindow::openImg(QString fileName)
{
    QImage image(fileName);
    if (image.isNull()) {
        QMessageBox::information(this, tr("Image Viewer"),
                                 tr("Cannot load %1.").arg(fileName));
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;


    ui->actionFitToWindow->setEnabled(true);
    updateActions();

    if (!ui->actionFitToWindow->isChecked())
        ui->label->adjustSize();
    fitToWindow();



    QFileInfo *fi=new QFileInfo(fileName);
    pdr=new QDir(fi->absoluteDir());


    fnlist=pdr->entryList(namefilter);
    for (int i=0;i<fnlist.count();i++)
    {
        fnlist[i]=pdr->absoluteFilePath(fnlist[i]);
    }
    ci=fnlist.indexOf(fileName);

}

void MainWindow::openfile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                         tr("Open File"), QDir::currentPath());
         if (!fileName.isEmpty()) {
             openImg(fileName) ;
         }
}



void MainWindow::updateActions()
 {
     ui->actionZoomIn->setEnabled(!ui->actionFitToWindow->isChecked());
     ui->actionZoomOut->setEnabled(!ui->actionFitToWindow->isChecked());
     ui->actionNormal_Size->setEnabled(!ui->actionFitToWindow->isChecked());
 }

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
 {
     scrollBar->setValue(int(factor * scrollBar->value()
                             + ((factor - 1) * scrollBar->pageStep()/2)));
 }

void MainWindow::scaleImage(double factor)
 {
     Q_ASSERT(ui->label->pixmap());
     scaleFactor *= factor;
     ui->label->resize(scaleFactor * ui->label->pixmap()->size());

     adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
     adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);

     ui->actionZoomIn->setEnabled(scaleFactor < 3.0);
     ui->actionZoomOut->setEnabled(scaleFactor > 0.333);
 }
void MainWindow::aboutProg()
 {
     QMessageBox::about(this, tr("About Project51"),
             tr("<p>The <b>Project51</b> </p>"));
 }

void MainWindow::help()
 {
     QMessageBox::about(this, tr("Project51 Help"),
             tr("<p>The <b>Project51 Help</b> </p>"));
 }

void MainWindow::exitApp()
 {
    QApplication::exit();
 }

void MainWindow::fitToWindow()
 {
     bool fitToWindow = ui->actionFitToWindow->isChecked();
     ui->scrollArea->setWidgetResizable(fitToWindow);
     if (!fitToWindow) {
         normalSize();
     }
     updateActions();
 }

void MainWindow::normalSize()
 {
     ui->label->adjustSize();
     scaleFactor = 1.0;
 }

void MainWindow::zoomIn()
 {
     scaleImage(1.25);
 }

 void MainWindow::zoomOut()
 {
     scaleImage(0.8);
 }


