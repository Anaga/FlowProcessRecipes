#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   void on_pushButton_New_clicked();

   void on_pushButton_Save_clicked();

   void on_pushButton_Open_clicked();

   void on_pushButton_Run_clicked();

   void open();

   void saveAs();

   void about();

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();

    QTreeWidget *treeWidget;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

};

#endif // MAINWINDOW_H
