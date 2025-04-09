#include "loginform.h"
#include <QVBoxLayout>
#include <QLabel>

LoginForm::LoginForm(Auth &auth, QWidget *parent) : QWidget(parent), auth(auth) {
	QVBoxLayout *layout = new QVBoxLayout(this);

	QLabel *usernameLabel = new QLabel("Username:", this);
	usernameEdit = new QLineEdit(this);

	QLabel *passwordLabel = new QLabel("Password:", this);
	passwordEdit = new QLineEdit(this);
	passwordEdit->setEchoMode(QLineEdit::Password);

	loginButton = new QPushButton("login", this);

	connect(loginButton, &QPushButton::clicked, this, &LoginForm::handleLogin);

	layout->addWidget(usernameLabel);
	layout->addWidget(usernameEdit);
	layout->addWidget(passwordLabel);
	layout->addWidget(passwordEdit);
	layout->addWidget(loginButton);

	setLayout(layout);
}

LoginForm::~LoginForm() {
	//It can be empty, but if needed, it can contain code to clean up resources.
}

void LoginForm::handleLogin() {
	QString username = usernameEdit->text();
	QString password = passwordEdit->text();

	if (username.isEmpty() || password.isEmpty()) {
		QMessageBox::warning(this, "Login failde", "Please, fill in all fields");
		return;
	}

	if (auth.loginUser(username.toStdString(), password.toStdString())) {
		QMessageBox::warning(this, "Login Success", "Login successful.");
	} else {
		QMessageBox::warning(this, "Login Failed", "Login failed. Incorrect username or password.");
	}

}