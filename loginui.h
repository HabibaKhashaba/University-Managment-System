#ifndef LOGINUI_H
#define LOGINUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginUI;
}
QT_END_NAMESPACE

class LoginUI : public QMainWindow
{
    Q_OBJECT

public:
    LoginUI(QWidget *parent = nullptr);
    ~LoginUI();

private slots:
    void on_register_student_clicked();

    void on_return_to_login_clicked();

    void on_register_student_register_clicked();

    void on_login_clicked();

    void on_return_to_login_admin_clicked();

    void on_register_admin_register_clicked();

    void on_register_admin_clicked();

private:
    Ui::LoginUI *ui;
};
#endif // LOGINUI_H
