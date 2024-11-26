#include "loginui.h"
#include "adminui.h"
#include "studentui.h"
#include "ui_loginui.h"
#include <QMessageBox>
#include <QDir>

LoginUI::LoginUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginUI)
{
    ui->setupUi(this);
    ui->loginBox->show();
    ui->studentRegisterBox->hide();
    ui->adminRegisterBox->hide();
}

LoginUI::~LoginUI()
{
    delete ui;
}

void LoginUI::on_register_student_clicked()
{
    ui->studentRegisterBox->show();
    ui->loginBox->hide();
}


void LoginUI::on_return_to_login_clicked()
{
    ui->loginBox->show();
    ui->studentRegisterBox->hide();
}




void LoginUI::on_register_student_register_clicked()
{
    QString name = ui->fullname_student->text();
    QString email = ui->email_student->text();
    QString password = ui->password_student->text();
    QString studentId = ui->student_id->text();
    QString academiYear = ui->academic_year->text();

    if(name.isEmpty() || email.isEmpty() || password.isEmpty() || studentId.isEmpty() || academiYear.isEmpty()) {
        QMessageBox::warning(
            this,
            "Warning",
            "Please fill all the data!"
            );
    } else {
        QString filePath = QDir::homePath() + "/StudentManagmentSystem/students.txt";
        QFile file(filePath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << email << "|"
                << password << "|"
                << name << "|"
                << studentId << "|"
                << academiYear << "|"
                << " " << "|"
                << " " << "|"
                << " " << "\n";
            file.close();
            QMessageBox::information(
                this,
                "Success",
                "Register is successfull, please login!"
                );
            ui->loginBox->show();
            ui->studentRegisterBox->hide();
        } else {
            QMessageBox::warning(
                this,
                "Warning",
                "An error has occoured, please try again!"
                );
        }
    }
}


void LoginUI::on_login_clicked()
{
    QString email = ui->email->text();
    QString password = ui->password->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both email and password!");
        return;
    }

    QStringList filePaths = {
        QDir::homePath() + "/StudentManagmentSystem/students.txt",
        QDir::homePath() + "/StudentManagmentSystem/admins.txt"
    };

    for (const QString& filePath : filePaths) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QStringList data = in.readLine().split('|');
                if (data.size() >= 2 && data[0] == email && data[1] == password) {
                    if (filePath.contains("students")) {
                        QMessageBox::information(this, "Success", "Student login successful!");
                        StudentUi *sudentUi = new StudentUi(this, email);
                        close();
                        sudentUi->show();
                    } else {
                        QMessageBox::information(this, "Success", "Admin login successful!");
                        AdminUi *adminUi = new AdminUi(this, email);
                        close();
                        adminUi->show();
                    }
                    return;
                }
            }
        }
    }

    QMessageBox::warning(this, "Error", "Invalid email or password.");
}


void LoginUI::on_return_to_login_admin_clicked()
{
    ui->loginBox->show();
    ui->adminRegisterBox->hide();
}


void LoginUI::on_register_admin_register_clicked()
{
    QString name = ui->fullname_admin->text();
    QString email = ui->email_admin->text();
    QString password = ui->password_admin->text();

    if(name.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(
            this,
            "Warning",
            "Please fill all the data!"
            );
    } else {
        QString filePath = QDir::homePath() + "/StudentManagmentSystem/admins.txt";
        QFile file(filePath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << email << "|"
                << password << "|"
                << name << "\n";
            file.close();
            QMessageBox::information(
                this,
                "Success",
                "Register is successfull, please login!"
                );
            ui->loginBox->show();
            ui->adminRegisterBox->hide();
        } else {
            QMessageBox::warning(
                this,
                "Warning",
                "An error has occoured, please try again!"
                );
        }
    }
}


void LoginUI::on_register_admin_clicked()
{
    ui->loginBox->hide();
    ui->adminRegisterBox->show();
}

