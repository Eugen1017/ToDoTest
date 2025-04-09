#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include "auth.h"


class LoginForm : public QWidget {
	Q_OBJECT

public:
	LoginForm(Auth &auth, QWidget *parent = nullptr);
	~LoginForm();

private slots:
	void handleLogin();

private:
	Auth &auth;
	QLineEdit *usernameEdit;
	QLineEdit *passwordEdit;
	QPushButton *loginButton;
};

#endif