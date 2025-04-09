#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include "auth.h"

class RegistrationForm : public QWidget {
	Q_OBJECT

public:
	RegistrationForm(Auth &auth, QWidget *parent = nullptr);
	~RegistrationForm(); // Додано деструктор

	private slots:
		void handleRegister();

private:
	Auth &auth;
	QLineEdit *usernameEdit;
	QLineEdit *passwordEdit;
	QPushButton *registerButton;
};

#endif // REGISTRATIONFORM_H