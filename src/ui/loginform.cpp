#include "loginform.h"
#include <QVBoxLayout>
#include <QMessageBox>

LoginForm::LoginForm(Auth& auth, QWidget *parent)
	: QWidget(parent), m_auth(auth) {
	QVBoxLayout* layout = new QVBoxLayout(this);

	m_usernameField = new QLineEdit(this);
	m_usernameField->setPlaceholderText("Username");

	m_passwordField = new QLineEdit(this);
	m_passwordField->setPlaceholderText("Password");
	m_passwordField->setEchoMode(QLineEdit::Password);

	m_loginButton = new QPushButton("Login", this);

	layout->addWidget(m_usernameField);
	layout->addWidget(m_passwordField);
	layout->addWidget(m_loginButton);

	connect(m_loginButton, &QPushButton::clicked, this, &LoginForm::handleLogin);
}

void LoginForm::handleLogin() {
	QString username = m_usernameField->text();
	QString password = m_passwordField->text();

	if (m_auth.loginUser(username.toStdString(), password.toStdString())) {
		QMessageBox::information(this, "Login", "Login successful!");
		emit loginSuccessful(); // Відправляємо сигнал успішного входу
		this->close();
	} else {
		QMessageBox::warning(this, "Login", "Invalid username or password!");
	}
}