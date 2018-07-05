#include "mainwindow.h"
#include "PythonSyntaxHighlighter.h"
#include <QMessageBox>
#include<QVBoxLayout>
#include<QString>
#include<QProcess>
#include<iostream>
#include <QDebug>
#include<QFile>
#include <typeinfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    isChanged = false;//文件保存与否
    this->setWindowTitle("OOP大作业1.0");//命名
    this->setWindowIcon(QIcon(":/new/prefix1/image/应用程序图标.ico"));//图标

    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(this);

    this->setCentralWidget(widget);//设置到中央编辑页面。

    text1 = new QTextEdit;//中央编辑区域的实例化
    text1->setFont(QFont("Consolas", 14));//修改字体大小。

    text2 = new QTextEdit;//输出区域实例化
    text2->setFont(QFont("Consolas",14));//输出字体大小。

    layout->addWidget(text1);
    layout->addWidget(text2);



   widget->setLayout(layout);

    /*runbutton=new QPushButton(this);
    runbutton->setGeometry(QRect(550,0,80,25));
    runbutton->setText("解释");
    connect(runbutton,SIGNAL(clicked(bool)),this,SLOT(stdcout()));*/


    //添加文件下拉菜单
    fileMenu = this->menuBar()->addMenu("文件");

    //为下拉菜单添加文件项：
    newFile = new QAction("新建",this);//实例化
    newFile->setShortcut(tr("CTRL+N"));//快捷键
    fileMenu->addAction(newFile);//添加到显示
    connect(newFile,SIGNAL(triggered()),this,SLOT(on_new()));//为当前这个文件项添加一个出发事件，当前窗体响应，执行函数为on_new().

    openFile = new QAction("打开",this);//实例化
    openFile->setShortcut(tr("CTRL+O"));
    fileMenu->addAction(openFile);
    connect(openFile,SIGNAL(triggered()),this,SLOT(on_open()));//执行函数on_open()

    saveFile = new QAction("保存",this);
    saveFile->setShortcut(tr("CTRL+S"));
    fileMenu->addAction(saveFile);
    connect(saveFile,SIGNAL(triggered()),this,SLOT(on_save()));

    saveAsFile = new QAction("另存为",this);
    saveAsFile->setShortcut(tr("CRTL+F"));
    fileMenu->addAction(saveAsFile);
    connect(saveAsFile,SIGNAL(triggered()),this,SLOT(on_saveAs()));

    quitFile = new QAction("退出",this);
    quitFile->setShortcut(tr("CTRL+Q"));
    fileMenu->addAction(quitFile);
    connect(quitFile,SIGNAL(triggered()),this,SLOT(on_quit()));


    editMenu =this->menuBar()->addMenu("编辑");

    copyEdit = new QAction("复制",this);
    copyEdit->setShortcut(tr("CTRL+C"));
    editMenu->addAction(copyEdit);
    connect(copyEdit,SIGNAL(triggered()),this,SLOT(on_copy()));

    pasteEdit = new QAction("粘贴",this);
    pasteEdit->setShortcut(tr("CTRL+V"));
    editMenu->addAction(pasteEdit);
    connect(pasteEdit,SIGNAL(triggered()),this,SLOT(on_paste()));

    cutEdit = new QAction("剪切",this);
    cutEdit->setShortcut(tr("CTRL+X"));
    editMenu->addAction(cutEdit);
    connect(cutEdit,SIGNAL(triggered()),this,SLOT(on_cut()));

    allSelectEdit = new QAction("全选",this);
    allSelectEdit->setShortcut(tr("CTRL+A"));
    editMenu->addAction(allSelectEdit);
    connect(allSelectEdit,SIGNAL(triggered()),this,SLOT(on_allSelect()));

    helpMenu = this->menuBar()->addMenu("帮助");

    aboutSoftware = new QAction("关于软件",this);
    helpMenu->addAction(aboutSoftware);
    connect(aboutSoftware,SIGNAL(triggered()),this,SLOT(on_aboutSoftware()));

    howToUse = new QAction("如何使用",this);//使用手册
    helpMenu->addAction(howToUse);
    connect(howToUse,SIGNAL(triggered()),this,SLOT(on_howToUse()));

    runMenu = this->menuBar()->addMenu("解释");

    run = new QAction("解释",this);//解释
    runMenu->addAction(run);
    connect(run,SIGNAL(triggered()),this,SLOT(on_run()));
    connect(run,SIGNAL(triggered()),this,SLOT(clear_buff()));



    connect(text1,SIGNAL(textChanged()),this,SLOT(on_changed()));//当前数据是否改变

    //markdown_highlighter*  md_high = new markdown_highlighter(text1);//c++高亮字设置
    PythonSyntaxHighlighter *pythonHighlighter = new PythonSyntaxHighlighter(text1->document());

    //md_high->SetColorText("and",Qt::green);
    //md_high->SetColorText("elif",Qt::green);
    //md_high->SetColorText("import",Qt::blue);
    //md_high->SetColorText("return",Qt::blue);
    //md_high->SetColorText("as",Qt::blue);
    //md_high->SetColorText("else",Qt::blue);
    //md_high->SetColorText("in",Qt::blue);
    //md_high->SetColorText("try",Qt::green);
    //md_high->SetColorText("assert",Qt::green);
    //md_high->SetColorText("except",Qt::green);
    //md_high->SetColorText("is",Qt::green);
    //md_high->SetColorText("while",Qt::blue);
    //md_high->SetColorText("break",Qt::blue);
    //md_high->SetColorText("finally",Qt::blue);
    //md_high->SetColorText("lambda",Qt::blue);
    //md_high->SetColorText("with",Qt::blue);
    //md_high->SetColorText("class",Qt::green);
    //md_high->SetColorText("for",Qt::green);
    //md_high->SetColorText("not",Qt::green);
    //md_high->SetColorText("yield",Qt::green);
    //md_high->SetColorText("continue",Qt::blue);
    //md_high->SetColorText("from",Qt::blue);
    //md_high->SetColorText("or",Qt::blue);
    //md_high->SetColorText("def",Qt::blue);
    //md_high->SetColorText("global",Qt::blue);
    //md_high->SetColorText("pass",Qt::green);
    //md_high->SetColorText("del",Qt::green);
    //md_high->SetColorText("if",Qt::green);
    //md_high->SetColorText("raise",Qt::green);

    p=new QProcess(this);
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(outlog()));
    connect(p, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handleError(QProcess::ProcessError)));

}

MainWindow::~MainWindow()
{

}

void MainWindow::clear_buff()
{
    outputbuff.clear();
    return;
}

void MainWindow::on_new()
{
    if(isChanged){
        QMessageBox::information(this,"提示","文件尚未保存");
    }else{
        text1->setText("");//新建的话把文本内容置空。
    }
}

void MainWindow::on_open()
{
    if(isChanged){
        QMessageBox::information(this,"提示","文件尚未保存");
    }else{
        fileNameString = QFileDialog::getOpenFileName(this,"打开");//当前窗体，打开文件的对话框的标题是：“打开”
        if(fileNameString==NULL){
            return ;
        }
        FILE *pf = fopen(fileNameString.toStdString().data(),"r+");//可读可写的方式打开。
        if(pf==NULL)
            return ;
        char buf[1024];
        QString str;
        while(!feof(pf)){
            fgets(buf,sizeof(buf),pf);
            str+=buf;
        }
        text1->setText(str);
        fclose(pf);
    }



}

void MainWindow::on_save()
{
    fileNameString = QFileDialog::getSaveFileName(this,"保存");
    if(fileNameString==NULL)
        return ;
    FILE *pf = fopen(fileNameString.toStdString().data(),"w+");
    if(pf==NULL)
        return ;

    QString str = text1->toPlainText();
    fputs(str.toStdString().data(),pf);
    fclose(pf);
    isChanged = true;

}

void MainWindow::on_saveAs()
{
        QString fileName =QFileDialog::getSaveFileName(this,"另存为");
        if(fileName.isEmpty())
            return;
        else
            return on_save();
}//另存为函数定义

void MainWindow::on_quit()
{

    if(isChanged){
        QMessageBox::information(this,"提示","文件尚未保存，点击右上角×，取消保存");
    }else{
        this->close();
    }
}

void MainWindow::on_copy()
{
    text1->copy();
}

void MainWindow::on_paste()
{
    text1->paste();
}

void MainWindow::on_cut()
{
    text1->cut();
}

void MainWindow::on_allSelect()
{
    text1->selectAll();
}

void MainWindow::on_howToUse()
{
    QMessageBox::information(this,"如何使用","把代码输进去，然后点解释——bang！");
}

void MainWindow::on_aboutSoftware()
{
    QMessageBox::information(this,"关于软件","2018 all right reserved,作者；吕传承，陈熠豪，张子禾，韩志磊");
}

void MainWindow::on_changed()
{
    isChanged = true;
}


void MainWindow::on_run()
{
    QFile input_file("in.txt");

    //QFile output_file("out.txt");

    QString input = text1->toPlainText();

    if (!input_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&input_file);

    out << input;

    //p->setStandardInputFile("in.txt");

    QStringList argument;
    QString program="./minipy";
    argument<<"in.txt";

    p->start(program,argument);
    p->closeWriteChannel();
}

/*void MainWindow::on_run()
{
    QString in =text1->toPlainText();

    //text2->setPlainText(in);

    p->start("1.exe");

    p->write(in.toStdString().c_str());

    p->closeWriteChannel();

    //    p->waitForStarted();
}*/

void MainWindow::outlog()
{
    outputbuff.append(p->readAllStandardOutput());
    QString abc=outputbuff;
    qDebug()<<abc<<abc.length();
    //qDebug()<<tmp<<tmp.length();
    qDebug()<<abc.remove(QRegExp("\0"));
    emit outlogtext(abc);
    text2->document()->setPlainText(abc);
}

void MainWindow::handleError(QProcess::ProcessError error)
{
     switch(error) {
     case QProcess::FailedToStart:
        qDebug() << "Failed to start, may be due to insufficient permissions";
        break;
     case QProcess::Crashed:
        qDebug() << "Program crashed.";
        break;
     default:
        break;
     //debug each case..
    }
}
