#include "funcprocess.h".h"
#include <QTextEdit>

funcprocess::(Q *parent)
    : QWidget(parent),m_Process(new QProcess)
{
    ui.setupUi(this);
    ui.lineEdit->setText(tr("ping localhost"));
    ui.textEdit->setLineWrapMode(QTextEdit::NoWrap);
    m_Process->setProcessChannelMode(QProcess::MergedChannels);
    connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(onTest()));
    connect(m_Process,SIGNAL(readyReadStandardOutput()),this,SLOT(onOutput()));
}

Test2::~Test2()
{
    m_Process->terminate();
}

void Test2::onTest()
{
    QString qsCmd = ui.lineEdit->text();
    m_Process->start( qsCmd);
}

void Test2::onOutput()
{
    QByteArray qbt = m_Process->readAllStandardOutput();
    QString msg = QString::fromLocal8Bit(qbt);
    ui.textEdit->append(msg);
    ui.textEdit->update();
}
