#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "auth.h"

class LoginForm : public QWidget {
	Q_OBJECT

public:
	explicit LoginForm(Auth& auth, QWidget *parent = nullptr);

	signals:
		void loginSuccessful(); // Сигнал для успішного входу

	private slots:
		void handleLogin();

private:
	Auth& m_auth;
	QLineEdit* m_usernameField;
	QLineEdit* m_passwordField;
	QPushButton* m_loginButton;
};

#endif // LOGINFORM_H