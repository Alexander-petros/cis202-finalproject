#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTableView>
#include <vector>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->data_enter->setHidden(true);
    ui->data_table->setVisible(false);
    ui->Phone_edit->setInputMask("(999)999-9999");
    ui->search_widget->setHidden(true);
    ui->load_prompt->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::check_text(QString text)
{
    if (text.isEmpty())
    {
        return false;
    }
    if (text.isNull())
    {
        return false;
    }
    return true;
}

bool MainWindow::check_valid()
{
    QString text;
    text = ui->Name_edit->text();
    if (!check_text(text))
    {
        ui->status_label->setStyleSheet("QLabel { color : red; }");
        ui->status_label->setText("Invalid Name");
        return false;
    }
    text = ui->Address_edit->text();
    if (!check_text(text))
    {
        ui->status_label->setStyleSheet("QLabel { color : red; }");
        ui->status_label->setText("Invalid Address");
        return false;
    }
    text = ui->Phone_edit->text();
    if (!check_text(text))
    {
        ui->status_label->setStyleSheet("QLabel { color : red; }");
        ui->status_label->setText("Invalid Phone Number");
        return false;
    }
    text = ui->Email_edit->text();
    if (!check_text(text))
    {
        ui->status_label->setStyleSheet("QLabel { color : red; }");
        ui->status_label->setText("Invalid Email");
        return false;
    }
    text = ui->Web_edit->text();
    if (!check_text(text))
    {
        ui->status_label->setStyleSheet("QLabel { color : red; }");
        ui->status_label->setText("Invalid Website");
        return false;
    }
    return true;
}

void MainWindow::line_get()
{
    if (check_valid())
    {
        data.push_back(person());
        QString name = ui->Name_edit->text();
        QString phone = ui->Phone_edit->text();
        QString address = ui->Address_edit->text();
        QString email = ui->Email_edit->text();
        QString web = ui->Web_edit->text();
        int last = data.size() -1;
        data[last].name = name;
        data[last].phone_number = phone;
        data[last].address = address;
        data[last].email = email;
        data[last].website = web;
        ui->status_label->setStyleSheet("QLabel { color : black; }");
        ui->status_label->setText("Submitted");
        ui->Name_edit->clear();
        ui->Phone_edit->clear();
        ui->Address_edit->clear();
        ui->Email_edit->clear();
        ui->Web_edit->clear();
        ui->Phone_edit->setText("5555555555");
    }
}

void MainWindow::data_submit()
{
    static int line_num = 0;
    line_num++;
    line_get();
}
void MainWindow::data_exit()
{
    ui->data_enter->setHidden(true);
}

void MainWindow::view_data()
{
    ui->data_table->setVisible(true);
    int person_count = data.size();
    ui->data_table->setRowCount(person_count);
    ui->data_table->setColumnCount(5);
    for (unsigned long i = 0; i < data.size(); i++)
    {
        ui->data_table->setItem(i,0,new QTableWidgetItem(data[i].name));
        ui->data_table->setItem(i,1,new QTableWidgetItem(data[i].phone_number));
        ui->data_table->setItem(i,2,new QTableWidgetItem(data[i].address));
        ui->data_table->setItem(i,3,new QTableWidgetItem(data[i].email));
        ui->data_table->setItem(i,4,new QTableWidgetItem(data[i].website));
    }
}

void MainWindow::data_search()
{
    bool name_found = false;
    for (unsigned long i = 0; i < data.size(); i++)
    {
        if (data[i].name == ui->search_name->text())
        {
            name_found = true;
            ui->search_status->setStyleSheet("QLabel { color : black; }");
            ui->search_status->setText("Name found!");
            ui->data_table->clearContents();
            ui->data_table->setRowCount(1);
            ui->data_table->setVisible(true);
            ui->data_table->setItem(0,0,new QTableWidgetItem(data[i].name));
            ui->data_table->setItem(0,1,new QTableWidgetItem(data[i].phone_number));
            ui->data_table->setItem(0,2,new QTableWidgetItem(data[i].address));
            ui->data_table->setItem(0,3,new QTableWidgetItem(data[i].email));
            ui->data_table->setItem(0,4,new QTableWidgetItem(data[i].website));
        }
    }
    if (!name_found)
    {
        ui->search_status->setStyleSheet("QLabel { color : red; }");
        ui->search_status->setText("Name not found");
    }
}

void MainWindow::add_data(QString line)
{
    int pos = 0;
    QString buffer;
    data.push_back(person());
    int last = data.size() -1;
    for (int i = 0; i < line.size(); i++)
    {
        if (!(line.at(i) == ";"))
        {
            buffer += line.at(i);
        }
        else
        {
            switch (pos)
            {
            case(0):
                data[last].name = buffer;
                buffer = "";
                break;
            case(1):
                data[last].phone_number = buffer;
                buffer = "";
                break;
            case(2):
                data[last].address = buffer;
                buffer = "";
                break;
            case(3):
                data[last].email = buffer;
                buffer = "";
                break;
            case(4):
                data[last].website = buffer;
                buffer = "";
                break;
            }
            pos++;
        }
    }
}

void MainWindow::data_load()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open File"), "/home/", tr("Text Files(*.txt)"));
    QFile data_txt(filename);
    if (!data_txt.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("Can not open file");
    }
    else
    {
        QTextStream in(&data_txt);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            add_data(line);
        }
    }
    data_txt.close();
}
void MainWindow::data_save()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                            tr("Open File"), "/home/", tr("Text Files(*.txt)"));

    QFile data_txt(filename);
    if(!data_txt.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug("Can not open file");
    }
    else
    {
        QTextStream out(&data_txt);
        for (unsigned long i = 0; i < data.size(); i++)
        {
            out << data[i].name << ";";
            out << data[i].phone_number << ";";
            out << data[i].address << ";";
            out << data[i].email << ";";
            out << data[i].website << ";";
            out << "\n";
        }
    }
    data_txt.close();

}
