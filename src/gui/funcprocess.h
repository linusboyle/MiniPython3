#ifndef FUNCPROCESS_H
#define FUNCPROCESS_H

#include<QMainWindow>
#include<QProcess>
#include "mainwindow.h"

class funcprocess : public QMainWindow
{
    Q_OBJECT

public:
    funcprocess(QMainWindow *parent=0);
    ~funcprocess();
public slots:
    void onfunc();
    void onOutput();
private:
    QProcess *m_Process;

}

#endif // FUNCPROCESS_H
