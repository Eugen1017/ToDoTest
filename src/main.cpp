#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include "database.h"
#include "auth.h"
#include "loginform.h"
#include "registrationform.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	Database db("task_manager.db");
	Auth auth(db);

	// Вибір між формою реєстрації та входу
	QWidget mainWidget;
	QVBoxLayout layout(&mainWidget);

	QPushButton registerButton("Register");
	QPushButton loginButton("Login");

	layout.addWidget(&registerButton);
	layout.addWidget(&loginButton);

	RegistrationForm registrationForm(auth);
	registrationForm.setWindowTitle("User Registration");

	LoginForm loginForm(auth);
	loginForm.setWindowTitle("User Login");

	QObject::connect(&registerButton, &QPushButton::clicked, [&](){
		registrationForm.show();
	});

	QObject::connect(&loginButton, &QPushButton::clicked, [&](){
		loginForm.show();
	});

	mainWidget.setWindowTitle("Task Manager");
	mainWidget.setLayout(&layout);
	mainWidget.resize(300 * 2, 200 * 2);
	mainWidget.show();

	return app.exec();
}