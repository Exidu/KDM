#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libxl.h"
#include <iostream>
#include <QtWidgets>





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("KosmeDoc");

    if (openShowFile()) {       //einzubinden
            startupScreen();        //einzubinden
    }


    ui->treeWidget->setHeaderLabel("Maschine");

    startupWindow = true;

    import_Png("/home/sebastian/Desktop/Test_Konstrukteur/Logo.PNG");

    ShowExcel();

    connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(checkItem(QTreeWidgetItem*,QTreeWidgetItem*)));
}


MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_actionBeenden_triggered()
{
    close();
}



void MainWindow::on_actionNeue_Baugruppe_erstellen_triggered()
{


    d = new QDialog(this, Qt::Dialog | Qt::Window);

    cb = new QCheckBox();

    QSpacerItem* spacer = new QSpacerItem(0, 20);
    QSpacerItem* buttonSpace = new QSpacerItem(100, 0);
    QSpacerItem* checkSpace = new QSpacerItem(160, 0);



    d->setWindowTitle("Neue Baugruppe erstellen");
    d->setFixedSize(600, 480);

    QHBoxLayout* layout = new QHBoxLayout;
    QVBoxLayout* vlayout = new QVBoxLayout;

    QHBoxLayout* hlayout = new QHBoxLayout;
    QHBoxLayout* hlayout2 = new QHBoxLayout;


    lineBaugruppe = new QLineEdit;

    QLabel* checkLabel = new QLabel("ist Unterbaugruppe");
    QLabel* nameLabel = new QLabel("Name der Baugruppe: ");
    QLabel* fileLabel = new QLabel("Datei auswählen: ");
    QLabel* folderLabel = new QLabel("Wählen Sie den Ordner aus, in den die Baugruppe gespeichert werden soll");
    showFolderLabel = new QTextEdit();

    labelFileExcel = new QTextEdit();
    labelFilePaint = new QTextEdit();

    QPalette p = labelFileExcel->palette();
    p.setColor(QPalette::Base, QColor(240, 240, 255));
    labelFileExcel->setPalette(p);
    labelFilePaint->setPalette(p);
    showFolderLabel->setPalette(p);

    labelFileExcel->setEnabled(false);
    labelFilePaint->setEnabled(false);
    showFolderLabel->setEnabled(false);

    QLabel* paintLabel = new QLabel("Zeichnung auswählen: ");

    QPushButton* search = new QPushButton("Durchsuchen");
    QPushButton* erstellen = new QPushButton("Baugruppe erstellen");
    QPushButton* quit = new QPushButton("Abbrechen");
    QPushButton* paintSearch = new QPushButton("Durchsuchen");
    folderSearch = new QPushButton("Durchsuchen");


    vlayout->addWidget(nameLabel);
    vlayout->addWidget(lineBaugruppe);

    hlayout2->addWidget(checkLabel);
    hlayout2->addWidget(cb);
    hlayout2->addSpacerItem(checkSpace);

    hlayout->addWidget(erstellen);
    hlayout->addSpacerItem(buttonSpace);
    hlayout->addWidget(quit);




    vlayout->addItem(spacer);

    vlayout->addWidget(fileLabel);
    vlayout->addWidget(search);
    vlayout->addWidget(labelFileExcel);
    vlayout->addSpacerItem(spacer);

    vlayout->addWidget(paintLabel);
    vlayout->addWidget(paintSearch);
    vlayout->addWidget(labelFilePaint);

    vlayout->addSpacerItem(spacer);



    vlayout->addWidget(folderLabel);
    vlayout->addWidget(folderSearch);
    vlayout->addWidget(showFolderLabel);

    vlayout->addSpacerItem(spacer);

    vlayout->addLayout(hlayout2);

    vlayout->addSpacerItem(spacer);

    vlayout->addLayout(hlayout);





    QObject::connect(search, SIGNAL(clicked()), this, SLOT(searchButton()));
    QObject::connect(paintSearch, SIGNAL(clicked()), this, SLOT(paintSearchButton()));


    QObject::connect(quit, SIGNAL(clicked()), d, SLOT(close()));
    QObject::connect(erstellen, SIGNAL(clicked()), this, SLOT(erstellenBaugruppe()));


    QObject::connect(folderSearch, SIGNAL(clicked()), this, SLOT(searchFile()));




    QObject::connect(quit, SIGNAL(clicked()), d, SLOT(close()));





    layout->addLayout(vlayout);
    d->setLayout(layout);

    d->show();
}

void MainWindow::on_actionNeue_Maschine_erstellen_triggered()
{



    md = new QDialog(this, Qt::Dialog | Qt::Window);

    QSpacerItem* buttonSpace = new QSpacerItem(30, 0);
    QSpacerItem* spacer = new QSpacerItem(0, 20);



    md->setWindowTitle("Neue Maschine erstellen");
    md->setFixedSize(290, 130);

    line = new QLineEdit;


    QLabel* nameLabel = new QLabel("Name der Maschine: ");

    QVBoxLayout* vlayout = new QVBoxLayout;
    QHBoxLayout* hlayout = new QHBoxLayout;

    QPushButton* MaschineErstellen = new QPushButton("Maschine erstellen");
    QPushButton* quit = new QPushButton("Abbrechen");

    hlayout->addWidget(MaschineErstellen);
    hlayout->addSpacerItem(buttonSpace);
    hlayout->addWidget(quit);


    vlayout->addWidget(nameLabel);
    vlayout->addWidget(line);
    vlayout->addSpacerItem(spacer);

    QObject::connect(quit, SIGNAL(clicked()), md, SLOT(close()));
    QObject::connect(MaschineErstellen, SIGNAL(clicked()), this, SLOT(erstellenMaschine()));

    vlayout->addLayout(hlayout);
    md->setLayout(vlayout);

    md->show();

}

void MainWindow::on_actionBaugruppe_ffnen_triggered()
{



}

void MainWindow::on_actionMaschine_ffnen_triggered()
{
    openDir();
}

void MainWindow::on_actionBaugruppe_l_schen_triggered()
{

}

void MainWindow::on_actionMaschinen_l_schen_triggered()
{

}

void MainWindow::on_actionSpeichern_triggered()
{

}

void MainWindow::on_actionSpeichern_unter_triggered() //Start SaveAs (Lorenz)
{
    saveAsDialog = new QDialog(this, Qt::Dialog | Qt::Window);

    QGridLayout* layout = new QGridLayout();
    QHBoxLayout* hlayout = new QHBoxLayout();

    QSpacerItem* spacer = new QSpacerItem(0, 10);

    QLabel* ifNewNameLabel = new QLabel("Wollen Sie die Maschine umbenennen?");
    QLabel* saveAsLabel = new QLabel("Neuer Name der Maschine");
    QLabel* openFileSystemLabel = new QLabel("Speichern unter");

    QCheckBox* ifNewName = new QCheckBox();
    QLineEdit* saveAsLine = new QLineEdit();
    saveAsPath = new QLineEdit();
    saveAsPath->setEnabled(false);

    hlayout->addWidget(saveAsPath);
    hlayout->addSpacerItem(spacer);

    QPushButton* saveAsButton = new QPushButton("Speichern");
    QPushButton* quit = new QPushButton("Abbrechen");
    QPushButton* openFileSystemButton = new QPushButton("Durchsuchen");


    layout->addWidget(ifNewNameLabel, 0, 0);
    layout->addWidget(ifNewName, 0, 1);
    layout->addWidget(saveAsLabel, 1, 0);
    layout->addWidget(saveAsLine, 1, 1);
    layout->addWidget(openFileSystemLabel, 2, 0);
    layout->addWidget(openFileSystemButton, 2, 1);
    layout->addLayout(hlayout, 4, 0, 1, 2);
    layout->addWidget(saveAsButton, 5, 0);
    layout->addWidget(quit, 5, 1);

    QObject::connect(openFileSystemButton, SIGNAL(clicked()), this, SLOT(saveAsFileSystem()));

    QObject::connect(quit, SIGNAL(clicked()), saveAsDialog, SLOT(close()));

    saveAsDialog->setWindowTitle("Speichern unter");
    saveAsDialog->setFixedSize(500, 250);
    saveAsDialog->setLayout(layout);
    saveAsDialog->show();

}



void MainWindow::saveAsFileSystem() {
    saveAsDialog->hide();
    saveAsPath->setText(QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    workspaceFolder,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks));
    saveAsDialog->show();
} //END SaveAs (Lorenz)

void MainWindow::searchButton() {
    QString selfilter = tr("EXCEL (*.xls *.xlsx)");

    fileNameExcel = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Excel (*.xls *.xlsx)"), &selfilter);
    ExcelFile = new QFile(fileNameExcel);


    labelFileExcel->setText(fileNameExcel);

}

void MainWindow::paintSearchButton() {
    QString selfilter = tr("PNG (*.png);; JPEG (*.jpg *.jpeg)");

    fileNamePaint = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("PNG (*.png);; JPEG (*.jpg *.jpeg)"), &selfilter);
    PaintFile = new QFile(fileNameExcel);

    labelFilePaint->setText(fileNamePaint);
}



void MainWindow::erstellenMaschine() {
    QDir check(workspaceFolder + "/" + line->text());
        if(check.exists()){
            QMessageBox msgBox;
             msgBox.setText("<h3>Fehler beim Erstellen der Maschine</h3>");
             msgBox.setInformativeText("Maschinenname existiert bereits");
             msgBox.setStandardButtons(QMessageBox::Ok);
             msgBox.setWindowTitle("Error 1");
             msgBox.setDefaultButton(QMessageBox::Ok);
             msgBox.exec();
        }else{
            QString name = line->text();
            QDir dir(workspaceFolder);
            std::cout << workspaceFolder.toStdString();
            dir.mkdir(name);
            md->close();
            ui->actionNeue_Baugruppe_erstellen->setEnabled(true);
            AddRoot(name);
            machine = true;
            import_Png("");
        }


}

void MainWindow::erstellenBaugruppe() {
    QString name = lineBaugruppe->text();
    if (fileNameExcel.size() != 0 & fileNamePaint.size() != 0) {
        if (folderNameSearch.size() != 0) {
            QDir dir(folderNameSearch);
            dir.mkdir(name);

            if (machine) {
               AddChild(itm, name);
               machine = false;
            } else {
                if (cb->isChecked()) {
                    AddChild(ui->treeWidget->currentItem(), name);
                } else {
                    AddChild(itm, name);
                }
            }
            ExcelFile->copy(folderNameSearch + "/" + name + "/" + name + ".xls");
            PaintFile->copy(folderNameSearch + "/" + name + "/" + name + ".png");

            fileNameExcel = "";
            fileNamePaint = "";
            folderNameSearch = "";
            d->close();
        } else {
            QMessageBox::warning(this, "Warnung", "Sie haben keinen Speicherort für die Baugruppe ausgewählt");
        }

    } else if(fileNameExcel.size() == 0 & fileNamePaint.size() == 0){
        if (folderNameSearch.size() != 0) {
            QDir dir(folderNameSearch);
            dir.mkdir(name);

            if (machine) {
               AddChild(itm, name);
               machine = false;
            } else {
                if (cb->isChecked()) {
                    AddChild(ui->treeWidget->currentItem(), name);
                } else {
                    AddChild(itm, name);
                }
            }
            fileNameExcel = "";
            fileNamePaint = "";
            folderNameSearch = "";
            d->close();
        } else {
            QMessageBox::warning(this, "Warnung", "Sie haben keinen Speicherort für die Baugruppe ausgewählt");
        }

    } else if(fileNameExcel.size() != 0 & fileNamePaint.size() == 0){
        QMessageBox::warning(this, "Warnung", "Sie haben keine PNG-Datei ausgewählt.");

    } else if(fileNamePaint.size() != 0 & fileNameExcel.size() == 0){
        QMessageBox::warning(this, "Warnung", "Sie haben keine Excel-Datei ausgewählt.");

    }


}

void MainWindow::AddRoot(QString name)
{
    itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, name);
    ui->treeWidget->addTopLevelItem(itm);




}


void MainWindow::AddChild(QTreeWidgetItem* parent, QString name)
{
    itm2 = new QTreeWidgetItem();
    itm2->setText(0, name);
    parent->addChild(itm2);

}





void MainWindow::enableBaugruppe() {
    QObject::connect(cb, SIGNAL(clicked()), this, SLOT(disableBaugruppe()));
    QObject::connect(folderSearch, SIGNAL(clicked()), this, SLOT(searchFile()));
}

void MainWindow::disableBaugruppe() {
    QObject::connect(cb, SIGNAL(clicked()), this, SLOT(enableBaugruppe()));
}

void MainWindow::searchFile() {
    folderNameSearch = QFileDialog::getExistingDirectory (0, "Open Directory", homePath, QFileDialog::ShowDirsOnly);
    showFolderLabel->setText(folderNameSearch);
}




void MainWindow::startupScreen() { //ANFANG StartupScreen (Lorenz)



    QSpacerItem* buttonSpace = new QSpacerItem(60, 15);
    QSpacerItem* spacer = new QSpacerItem(60, 0);

    workDialog = new QDialog(this, Qt::Window | Qt::Dialog |
                             Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);


    QLabel* workLabel = new QLabel("Legen Sie hier Ihren Workspace fest: ");
    QLabel* againLabel = new QLabel("Beim nächsten Start nichtmehr anzeigen  ");

    folderLabel = new QTextEdit();

    folderLabel->setEnabled(false);

    againBox = new QCheckBox();



    QPushButton* search = new QPushButton("Durchsuchen");
    quit = new QPushButton("OK");
    quit->setEnabled(false);


    QVBoxLayout* vlayout = new QVBoxLayout;
    QHBoxLayout* upperLayout = new QHBoxLayout;
    QHBoxLayout* lowerLayout = new QHBoxLayout;

    QObject::connect(search, SIGNAL(clicked()), this, SLOT(folderName()));

    upperLayout->addWidget(workLabel);
    upperLayout->addWidget(search);

    lowerLayout->addWidget(againLabel);
    lowerLayout->addSpacerItem(spacer);
    lowerLayout->addWidget(againBox);


    workDialog->setWindowTitle("Workspace festlegen");
    workDialog->setFixedSize(500, 170);


    vlayout->addLayout(upperLayout);
    vlayout->addWidget(folderLabel);
    vlayout->addLayout(lowerLayout);

    vlayout->addSpacerItem(buttonSpace);
    vlayout->addWidget(quit);


    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(workClose()));

    QObject::connect(againBox, SIGNAL(clicked()), this, SLOT(neverShowAgain()));

    QFile file("config.ini");

    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << workspaceFolder << endl;
    }

    workDialog->setLayout(vlayout);
    workDialog->show();
}


void MainWindow::folderName() {
    workDialog->hide();
    workspaceFolder = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    workspaceFolder,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    folderLabel->setText(workspaceFolder);
    if(workspaceFolder.size() != 0) {
        quit->setEnabled(true);
    }

    workDialog->show();
}


void MainWindow::workClose() {
    workDialog->close();

    writeFile();

}

void MainWindow::writeFile() {
    if (workspaceFolder.size() != 0) {
        QFile file("config.ini");
        file.remove("config.ini");
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << workspaceFolder << endl;
        }
    }

    if (startupWindow == false) {
        if (workspaceFolder.size() != 0) {
            QFile file("config.ini");
            file.remove("config.ini");
            if (file.open(QIODevice::ReadWrite)) {
                QTextStream stream(&file);
                stream << "false; " << workspaceFolder << endl;
            }
        }
    } else {
        if (workspaceFolder.size() != 0) {
            QFile file("config.ini");

            if (file.open(QIODevice::ReadWrite)) {
                QTextStream stream(&file);
                stream << "true; " << workspaceFolder << endl;
            }
        }
    }
}

void MainWindow::neverShowAgain() {
    startupWindow = false;
    QObject::connect(againBox, SIGNAL(clicked()), this, SLOT(showAgain()));
}

void MainWindow::showAgain() {
    startupWindow = true;
    QObject::connect(againBox, SIGNAL(clicked()), this, SLOT(neverShowAgain()));
}

bool MainWindow::openShowFile() {
    QFile file("config.ini");
    if(!file.open(QIODevice::ReadOnly)) {

    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        workspaceFolder = fields[1].trimmed();
        file.close();
        if (fields[0].contains("true")) {
            return(true);
        } else {
            return(false);
        }

    }


}//ENDE StartupScreen (Lorenz)




void MainWindow::openDir()
{
        directoryName = QFileDialog::getExistingDirectory(this);
          if (!directoryName.isEmpty())
               loadDirectory(directoryName);
}
// Sprint 2 26.11.2013 Eitzenberger
void MainWindow::loadDirectory(const QString &directory) {
        Q_ASSERT(QDir(directory).exists());
        QDir folder(directory);
        machine = true;
        ui->actionNeue_Baugruppe_erstellen->setEnabled(true);
        AddRoot(folder.dirName());
        loadSubdirectory(directory);
        import_Png("");

}

//2 Sprint 26.11.2013 Eitzenberger
void MainWindow::loadSubdirectory(const QString directory) {
    int count = 0;
    QDir *rootDir = new QDir(directory);
    QTreeWidgetItem * subitm = new QTreeWidgetItem;
    QFileInfoList fileList = rootDir->entryInfoList();

    foreach(QFileInfo fileInfo,fileList) {
        QTreeWidgetItem* child = new QTreeWidgetItem();
        child->setText(0,fileInfo.fileName());
        if(fileInfo.isDir()&&fileInfo.fileName() != "." && fileInfo.fileName()!= "..") {
            child->setText(2,fileInfo.filePath());
            itm->addChild(child);
            subitm = itm->child(count);
            loadSubdirectory(fileInfo.absoluteFilePath(),subitm);
        }
    }

}
void MainWindow::loadSubdirectory(const QString directory,QTreeWidgetItem* item) {
    QDir *rootDir = new QDir(directory);
    QFileInfoList fileList = rootDir->entryInfoList();

    foreach(QFileInfo fileInfo,fileList) {
        QTreeWidgetItem* child = new QTreeWidgetItem();
        child->setText(0,fileInfo.fileName());
        if(fileInfo.isDir()&&fileInfo.fileName() != "." && fileInfo.fileName()!= "..") {
            child->setText(2,fileInfo.filePath());
            AddChild(item,fileInfo.fileName());
            QDirIterator root(fileInfo.absoluteFilePath(),QDir::Dirs | QDir::NoSymLinks, QDirIterator::Subdirectories);
            if(!root.hasNext()) {
                loadSubdirectory(fileInfo.absoluteFilePath(),item);
            }
            else
                loadSubdirectory(fileInfo.absoluteFilePath(),item->child(0));
        }

    }
}


void MainWindow::import_Png(QString path) {
    QGraphicsScene* scene = new QGraphicsScene;

    scene->addPixmap(QPixmap(path));

    ui->graphicsView->scale(0.13, 0.08);


    ui->graphicsView->setScene(scene);
}




/* Anfang Maus-Zoom */
void MainWindow::wheelEvent (QWheelEvent * event)
{
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

        double scaleFactor = 1.15;
        if(event->delta() > 0) {
            // Zoom in
            ui->graphicsView->scale(scaleFactor, scaleFactor);
        } else {
            ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
}
/* Ende Maus-Zoom */


void MainWindow::checkItem(QTreeWidgetItem* curr,QTreeWidgetItem* old) {
    if (curr == itm) {
        ui->actionMaschine_umbenennen->setEnabled(true);
    } else {
        ui->actionMaschine_umbenennen->setEnabled(false);
    }
}


void MainWindow::on_actionMaschine_umbenennen_triggered()
{
    rd = new QDialog;
    rd->resize(230, 140);

    QLabel* renameMachineLabel = new QLabel("Neuer Maschinenname");
    renameMachineEdit = new QLineEdit;
    QVBoxLayout* renameMachineLayout = new QVBoxLayout;
    QHBoxLayout* renameMachineLayoutH = new QHBoxLayout;
    QSpacerItem* spacer = new QSpacerItem(0, 20);

    QPushButton* rename = new QPushButton("Umbenennen");
    QPushButton* renameMachineCancel = new QPushButton("Abbrechen");

    renameMachineLayoutH->addWidget(rename);
    renameMachineLayoutH->addWidget(renameMachineCancel);

    renameMachineLayout->addWidget(renameMachineLabel);
    renameMachineLayout->addWidget(renameMachineEdit);
    renameMachineLayout->addSpacerItem(spacer);
    renameMachineLayout->addLayout(renameMachineLayoutH);

    rd->setLayout(renameMachineLayout);

    QObject::connect(rename, SIGNAL(clicked()), this, SLOT(renameMachineFunk()));


    rd->show();

}


void MainWindow::renameMachineFunk() {
      QString newMachineName = renameMachineEdit->text();
      itm->setText(0, newMachineName);
      if (line->text().size() != 0) {
        QDir dir;
        QString oldFolderMachinePath = workspaceFolder + "/" + line->text();
        QString newFolderMachinePath = workspaceFolder + "/" + newMachineName;
        dir.rename(oldFolderMachinePath, newFolderMachinePath);
        std::cout << oldFolderMachinePath.toStdString();
      } else {
        QDir folder(directoryName);
        QString oldFolderMachinePath = folder.path();
        QString newFolderMachinePath = workspaceFolder + "/" + newMachineName;
        folder.rename(oldFolderMachinePath, newFolderMachinePath);
      }

     rd->close();
}


void MainWindow::on_actionOptionen_triggered() //Start options (Lorenz)
{
    QGroupBox* horizontalGroupBox = new
            QGroupBox(tr("Dialogfenster \"Workspace auswählen\""));
    optionsDialog = new QDialog(this, Qt::Window | Qt::Dialog);

    QLabel* showWorkAgain = new QLabel("Beim nächsten Start wieder anzeigen");
    ifShowWorkAgain = new QCheckBox();

    QPushButton* okButton = new QPushButton("Ok");
    QPushButton* quit = new QPushButton("Abbrechen");

    QGridLayout* workLayout = new QGridLayout();
    QHBoxLayout* hlayout = new QHBoxLayout();
    QGridLayout* layout = new QGridLayout();

    workLayout->addWidget(showWorkAgain, 0, 0);
    workLayout->addWidget(ifShowWorkAgain, 0, 1);
    workLayout->addLayout(hlayout, 1, 0, 1, 2);

    horizontalGroupBox->setLayout(workLayout);
    layout->addWidget(horizontalGroupBox, 0, 0, 1, 2);

    layout->addWidget(okButton, 1, 0);
    layout->addWidget(quit, 1, 1);

    optionsDialog->setLayout(layout);
    optionsDialog->setFixedSize(500, 150);
    optionsDialog->setWindowTitle("Optionen");
    optionsDialog->show();

    QObject::connect(ifShowWorkAgain, SIGNAL(clicked()), this, SLOT(showWorkAgain()));

    QObject::connect(quit, SIGNAL(clicked()), optionsDialog, SLOT(close()));
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(optionClose()));
}

void MainWindow::showWorkAgain() {
    startupWindow = true;
    QObject::connect(ifShowWorkAgain, SIGNAL(clicked()), this, SLOT(notShowWorkAgain()));
}

void MainWindow::notShowWorkAgain() {
    startupWindow = false;
    QObject::connect(ifShowWorkAgain, SIGNAL(clicked()), this, SLOT(showWorkAgain()));
}

void MainWindow::optionClose() {
    optionsDialog->close();

    writeFile();
}//End options (Lorenz)


void MainWindow::ShowExcel(){
    QStringList header;
    libxl::Book* book = xlCreateBook();


    if(book->load("/home/sebastian/Desktop/Test_Konstrukteur/BG01.xls")){

        libxl::Sheet *sheet = book->getSheet(0);


        if(sheet){
            ui->tableWidget->setRowCount(sheet->lastRow());
            ui->tableWidget->setColumnCount(sheet->lastCol());


            /*header<<"Pos"<<"Menge"<<"Artikelnummer"<<"Bennenung"<<"Name";
            ui->tableWidget->setHorizontalHeaderLabels(header);*/


            for(int row = 0; row < sheet->lastRow(); row++)
            {
                for(int col = 0; col < sheet->lastCol(); col++)
                {
                    libxl::CellType cellType = sheet->cellType(row,col);
                    switch(cellType){

                    case libxl::CELLTYPE_EMPTY:{
                        break;
                    } case libxl::CELLTYPE_NUMBER:
                    {
                        int num = sheet->readNum(row,col);
                        QString st = QString::number(num);
                        QTableWidgetItem* itm = new QTableWidgetItem(st);
                        ui->tableWidget->setItem(row, col, itm);
                        break;
                    } case libxl::CELLTYPE_STRING:
                    {
                        QTableWidgetItem* itm = new QTableWidgetItem(sheet->readStr(row,col));
                        ui->tableWidget->setItem(row,col,itm);
                        break;
                    }case libxl::CELLTYPE_BOOLEAN:{
                        break;
                    }case libxl::CELLTYPE_BLANK:{
                        break;
                    }case libxl::CELLTYPE_ERROR:{
                        std::cout<<"ERROR";

                    }

                    }


                }

            }
        }
        book->release();
        ui->tableWidget->show();
    }

}
