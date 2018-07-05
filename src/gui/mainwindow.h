#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QLabel>
#include<QStatusBar>
#include<QWidget>
#include<QPushButton>
#include<QString>
#include<QProcess>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QProcess *p;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QByteArray outputbuff;
    bool isChanged;//检查保存与否
    QString fileNameString;//文件名字

    QTextEdit *text1;
    QTextEdit *text2;//第二个输出表格

    int printf(const char *format,...)
    {char buf[1000]; int i;
     va_list vlist;
     va_start(vlist,format);
     i=vsprintf(buf,format,vlist);
     va_end(vlist);
     text2->append(QString(buf));
     return i;
    }

    QMenu *fileMenu;//文件下拉菜单
    QAction *newFile;//新建文件。
    QAction *openFile;//打开文件。
    QAction *saveFile;//保存文件。
    QAction *saveAsFile;//另存为。
    QAction *quitFile;//退出。

    QMenu *editMenu;//编辑菜单
    QAction *copyEdit;
    QAction *pasteEdit;
    QAction *cutEdit;
    QAction *allSelectEdit;

    QMenu *helpMenu;//帮助菜单
    QAction *aboutSoftware;
    QAction *howToUse;

    QMenu *runMenu;
    QAction *run;

   // QPushButton *runbutton;

private slots:
    void on_new();
    void on_open();
    void on_save();
    void on_saveAs();
    void on_quit();

    void on_copy();
    void on_paste();
    void on_cut();
    void on_allSelect();

    void on_howToUse();
    void on_aboutSoftware();
    void on_changed();//菜单栏

    void on_run();
    void clear_buff();
    //void showTextInfo();
    //void stdcout();

    void outlog();
    void handleError(QProcess::ProcessError);
signals:
    void outlogtext(QString ver);


};

#endif // MAINWINDOW_H
