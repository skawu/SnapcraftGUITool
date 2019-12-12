#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->ui->comboBox_stage->addItem(tr(" "));
    this->ui->comboBox_stage->addItem("pull");
    this->ui->comboBox_stage->addItem("build");
    this->ui->comboBox_stage->addItem("stage");
    this->ui->comboBox_stage->addItem("prime");
    this->ui->comboBox_stage->addItem("snap");
    this->ui->comboBox_stage->addItem("clean");

    exec_shell = new QProcess(this);
#ifdef Q_OS_WIN32
    QString program = "C:/Windows/SysWOW64/cmd.exe";
#endif
#ifdef Q_OS_UNIX
    QString program =  "/bin/bash";
#endif
    exec_shell->setProgram(program);
    exec_shell->start();

    connect(exec_shell, SIGNAL(readyReadStandardOutput()), this, SLOT(readProcess()));
    connect(exec_shell, SIGNAL(finished(int)), this, SLOT(finishedProcess()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_opendir_triggered()
{
    QDir dir;

    PathName = QFileDialog::getExistingDirectory(this, tr("选择目录"),
                                                 "E:/Myworkspace/data/",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
#ifdef Q_OS_WIN32
    PathName.replace("/","\\"); //单斜杠转换双斜杠,方便后续存储bin文件
#endif
    ui->label_selectDir->setText(PathName);    //文件名称显示

    dir.cd(PathName);
}

void MainWindow::on_pushButton_clicked()
{
    QDir dir;

    PathName = QFileDialog::getExistingDirectory(this, tr("选择目录"),
                                                 "E:/Myworkspace/data/",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
#ifdef Q_OS_WIN32
    PathName.replace("/","\\"); //单斜杠转换双斜杠,方便后续存储bin文件
#endif
    ui->label_selectDir->setText(PathName);    //文件名称显示

    // 控制台切换目录
    QString cmd = "cd " + PathName + " \n";
    exec_shell->write(cmd.toLocal8Bit());


    QDir::setCurrent(PathName);
}

void MainWindow::on_comboBox_stage_currentIndexChanged(const QString &arg1)
{
    stage_name = arg1;
}

void MainWindow::on_pushButton_2_clicked()
{
    extra_param = this->ui->lineEdit_extraParam->text();


    // 拼接命令
    cmd = "snapcraft " + stage_name + " " + extra_param + "\n";
    this->ui->label_status_cur_dir->setText(cmd);

    // 执行命令
    exec_shell->write(cmd.toLocal8Bit());
}

void MainWindow::readProcess(){
    QString output = QString::fromLocal8Bit(exec_shell->readAll());
    shell_output += output;
    this->ui->textBrowser_2->append(output);
}

void MainWindow::finishedProcess(){
    qDebug() << __FUNCTION__ << __LINE__;
}

void MainWindow::on_pushButton_clear_clicked()
{
    this->ui->textBrowser_2->clear();
}

void MainWindow::on_actionguanyu_triggered()
{
    QMessageBox::information(nullptr, tr("关于"), tr("郑州煤机液压电控有限公司 \n\n Snapcraft 打包工具"));
}
