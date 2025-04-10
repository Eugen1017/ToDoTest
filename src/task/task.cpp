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
