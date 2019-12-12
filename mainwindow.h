#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_opendir_triggered();

    void on_pushButton_clicked();

    void on_comboBox_stage_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();
    void readProcess();
    void finishedProcess();

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;

public:
    QProcess *exec_shell;
    QString PathName;
    QString stage_name;
    QString extra_param;
    QString cmd;
    QString shell_output;
};

#endif // MAINWINDOW_H
