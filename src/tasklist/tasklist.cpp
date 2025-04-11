#include "tasklist.h"
#include <QMessageBox>


TaskList::TaskList(Database &database) : db(database) {}

int TaskList::collectTasksCallback(void *data, int argc, char **argv, char **calNames) {
	auto *tasks = static_cast<std::vector<Task> *>(data);

	int id = std::stoi(argv[0]);
	std::string title = argv[1];
	bool isCompleted = std::stoi(argv[2]) != 0;
	std::time_t dueDate = static_cast<std::time_t>(std::stoi(argv[3]));

	tasks->emplace_back(id, title, isCompleted, dueDate);

	return 0;
}

std::vector<Task> TaskList::getTasks(int userId) {
	std::vector<Task> tasks;

	std::string sql = "SELECT id, title, is_completed, due_date FROM tasks WHERE user_id = " + std::to_string(userId);

	if (!db.query(sql, TaskList::collectTasksCallback, &tasks)) {
		QMessageBox::warning(nullptr, "Database Error", QString("Failed to execute query: %1").arg(QString::fromStdString(sql)));
	}

	return tasks;
}