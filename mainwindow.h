#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void AddRoot(QString name);
    void AddChild(QTreeWidgetItem *parent, QString name);
    void ShowExcel();


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QLineEdit* line;
    QLineEdit* lineBaugruppe;
    QDialog* md;
    QDialog* d;
    QDialog* rd;
    QString name;
    QCheckBox* cb;
    QString fileNameExcel;
    QString fileNamePaint;
    QString folderNameSearch;
    QString homePath;
    QLineEdit* renameMachineEdit;
    QTextEdit* labelFileExcel;
    QTextEdit* labelFilePaint;
    QTextEdit* showFolderLabel;
    QFile* ExcelFile;
    QFile* PaintFile;
    QTreeWidgetItem* itm;
    QTreeWidgetItem* itm2;
    QTreeWidgetItem* itm3;
    QTreeWidgetItem* itm4;
    QTreeWidgetItem* itm5;
    QTreeWidgetItem* itm6;
    QPushButton* folderSearch;
    bool machine = false;

    int _numScheduledScalings;





    QDialog* workDialog;
    QTextEdit* folderLabel;
    bool startupWindow;
    QString workspaceFolder;
    QString renameMachine;
    QString nameMachineLine;
    QCheckBox* againBox;
    QPushButton* quit;

    QDialog* saveAsDialog; //einzubinden
    QCheckBox* ifShowWorkAgain; //einzubinden
    QDialog* optionsDialog; //einzubinden
    QLineEdit* saveAsPath;
    QString directoryName;






private slots:
    void on_actionBeenden_triggered();

    void on_actionNeue_Baugruppe_erstellen_triggered();

    void on_actionNeue_Maschine_erstellen_triggered();

    void on_actionBaugruppe_ffnen_triggered();

    void on_actionMaschine_ffnen_triggered();

    void on_actionBaugruppe_l_schen_triggered();

    void on_actionMaschinen_l_schen_triggered();

    void on_actionSpeichern_triggered();

    void on_actionSpeichern_unter_triggered();

    void searchButton();

    void paintSearchButton();

    void erstellenMaschine();

    void erstellenBaugruppe();

    void enableBaugruppe();

    void disableBaugruppe();

    void searchFile();

    void startupScreen();

    void folderName();

    void workClose();

    void neverShowAgain();

    void showAgain();

    bool openShowFile();

    void saveAsFileSystem(); //einzubinden

    void openDir();

    void loadDirectory(const QString& directory);

    void loadSubdirectory(QString directory);

    void loadSubdirectory(QString directory,QTreeWidgetItem* s);

    void import_Png(QString path);

    void renameMachineFunk();

    void checkItem(QTreeWidgetItem *, QTreeWidgetItem *);

    void on_actionMaschine_umbenennen_triggered();

    void on_actionOptionen_triggered(); //einzubinden

    void showWorkAgain(); //einzubinden

    void notShowWorkAgain(); //einzubinden

    void writeFile(); //einzubinden

    void optionClose(); //einzubinden





private:
    Ui::MainWindow *ui;

    void wheelEvent(QWheelEvent* event);


};

#endif // MAINWINDOW_H
