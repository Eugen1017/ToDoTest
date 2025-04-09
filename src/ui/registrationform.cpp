#include "registrationform.h"
#include <QVBoxLayout>
#include <QLabel>

RegistrationForm::RegistrationForm(Auth &auth, QWidget *parent) : QWidget(parent), auth(auth) {
	QVBoxLayout *layout = new QVBoxLayout(this);

	QLabel *usernameLabel = new QLabel("Username:", this);
	usernameEdit = new QLineEdit(this);

	QLabel *passwordLabel = new QLabel("Password:", this);
	passwordEdit = new QLineEdit(this);
	passwordEdit->setEchoMode(QLineEdit::Password);

	registerButton = new QPushButton("Register", this);
	connect(registerButton, &QPushButton::clicked, this, &RegistrationForm::handleRegister);

	layout->addWidget(usernameLabel);
	layout->addWidget(usernameEdit);
	layout->addWidget(passwordLabel);
	layout->addWidget(passwordEdit);
	layout->addWidget(registerButton);

	setLayout(layout);
}

RegistrationForm::~RegistrationForm() {
	// Деструктор може бути порожнім або містити код для очищення ресурсів
}

void RegistrationForm::handleRegister() {
	QString username = usernameEdit->text();
	QString password = passwordEdit->text();

	if (username.isEmpty() || password.isEmpty()) {
		QMessageBox::warning(this, "Registration Failed", "Please fill in all fields.");
		return;
	}

	if (auth.registerUser(username.toStdString(), password.toStdString())) {
		QMessageBox::information(this, "Registration Success", "User registered successfully.");
	} else {
		QMessageBox::warning(this, "Registration Failed", "Registration failed. User may already exist.");
	}
}