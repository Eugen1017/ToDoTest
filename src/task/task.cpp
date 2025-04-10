#include "task.h"
#include <sstream>

Task::Task(int id, const std::string &title, bool isCompleted, std::time_t dueDate)
		: id(id), title(title), isCompleted(isCompleted), dueDate(dueDate) {}

int Task::getId() const {
	return id;
}

std::string Task::getTitle() const {
	return title;
}

bool Task::getIsCompleted() const {
	return isCompleted;
}

std::time_t Task::getDueDate() const {
	return dueDate;
}

void Task::setTitle(const std::string &newTitle) {
	title = newTitle;
}

void Task::marksAsCompleted() {
	isCompleted = true;
}

void Task::setDueDate(std::time_t newDueDate) {
	dueDate = newDueDate;
}

std::string Task::toSQLInsert() const {
	std::ostringstream query;

	query << "INSERT INTO tasks (id, title, is_completed, due_date) VALUES ("
			<< id << ", "
		    << title << ", "
		  	<< (isCompleted ? 1 : 0) << ", "
			<< dueDate << ");";

	return query.str();
}

std::string Task::toSQLDelete() const {
	std::ostringstream query;
	query << "DELETE FROM tasks WHERE title = '" << title << "';";

	return query.str();
}

Task Task::fromSQLRow(char **row) {
	int id = std::stoi(row[0]);
	std::string title = row[1];
	bool isCompleted = std::stoi(row[2]) != 0;
	std::time_t dueDate = static_cast<std::time_t>(std::stoi(row[3]));

	return Task(id, title, isCompleted, dueDate);
}
