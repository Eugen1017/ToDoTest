#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include "database.h"
#include "auth.h"
#include "loginform.h"
#include "registrationform.h"
#include "taskmanagerform.h" // Додано для роботи з TaskManagerForm

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

	TaskManagerForm taskManagerForm(db, auth); // Додано TaskManagerForm
	taskManagerForm.setWindowTitle("Task Manager");

	QObject::connect(&registerButton, &QPushButton::clicked, [&]() {
		registrationForm.show();
	});

	QObject::connect(&loginButton, &QPushButton::clicked, [&]() {
		loginForm.show();
	});

	// Переход до Task Manager після успішного входу
	QObject::connect(&loginForm, &LoginForm::loginSuccessful, [&]() {
		loginForm.hide();
		taskManagerForm.show();
	});

	mainWidget.setWindowTitle("Task Manager");
	mainWidget.setLayout(&layout);
	mainWidget.resize(300 * 2, 200 * 2);
	mainWidget.show();

	return app.exec();
}