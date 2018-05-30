#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void data_submit();
    void data_exit();
    void view_data();
    void line_get();
    void data_search();
    void data_load();
    void data_save();

private slots:

private:
    Ui::MainWindow *ui;
    bool check_valid();
    bool check_text(QString text);
    struct person
    {
        QString name;
        QString phone_number;
        QString address;
        QString email;
        QString website;
    };
    std::vector<person> data;
    void add_data(QString);

};

#endif // MAINWINDOW_H
