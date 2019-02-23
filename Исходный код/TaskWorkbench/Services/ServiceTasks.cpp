/*
 * ServiceTasks.cpp
 *
 *  Created on: 21 нояб. 2017 г.
 *      Author: Дмитрий
 */

#include "ServiceTasks.h"

const string ServiceTasks::PATH_FREE_TASKID = "./Resources/FreeTaskId.txt";

ServiceTasks::ServiceTasks() {
}

ServiceTasks::~ServiceTasks() {
}

bool ServiceTasks::compTaskByTaskId(Task& first, Task& second) {
	return first.getTaskId() < second.getTaskId();
}
bool ServiceTasks::compTaskByContent(Task& first, Task& second) {
	return (first.getContent().compare(second.getContent()) == -1 ? true : false);
}
bool ServiceTasks::compTaskByAssignmentDate(Task& first, Task& second) {
	return (first.getAssignmentDate().comparisonDate(second.getAssignmentDate())
			== -1 ? true : false);
}
bool ServiceTasks::compTaskByPlannedDate(Task& first, Task& second) {
	return (first.getPlannedDate().comparisonDate(second.getPlannedDate())
			== -1 ? true : false);
}
bool ServiceTasks::compTaskByDateDelivery(Task& first, Task& second) {
	return (first.getDateDelivery().comparisonDate(second.getDateDelivery())
			== -1 ? true : false);
}
bool ServiceTasks::compTaskByNotation(Task& first, Task& second) {
	return (first.getNotation().compare(second.getNotation()) == -1 ?
			true : false);
}

bool ServiceTasks::recompTaskByTaskId(Task& first, Task& second){
	return first.getTaskId() > second.getTaskId();
}
bool ServiceTasks::recompTaskByContent(Task& first, Task& second){
	return (first.getContent().compare(second.getContent()) == 1 ? true : false);
}
bool ServiceTasks::recompTaskByUserId(Task& first, Task& second){
	return first.getUserId() > second.getUserId();
}
bool ServiceTasks::recompTaskByAssignmentDate(Task& first, Task& second){
	return (first.getAssignmentDate().comparisonDate(second.getAssignmentDate())
			== 1 ? true : false);
}
bool ServiceTasks::recompTaskByPlannedDate(Task& first, Task& second){
	return (first.getPlannedDate().comparisonDate(second.getPlannedDate())
			== 1 ? true : false);
}
bool ServiceTasks::recompTaskByDateDelivery(Task& first, Task& second){
	return (first.getDateDelivery().comparisonDate(second.getDateDelivery())
			== 1 ? true : false);
}
bool ServiceTasks::recompTaskByNotation(Task& first, Task& second){
	return (first.getNotation().compare(second.getNotation()) == 1 ?
				true : false);
}

list<Task>::iterator ServiceTasks::findTaskByTaskId(
		list<Task>::iterator begin, list<Task>::iterator end,
		unsigned int taskId){
	for (; begin != end; begin++)
		if (to_string((*begin).getTaskId()).find(to_string(taskId))!=string::npos)
			return begin;
	return end;
}
list<Task>::iterator ServiceTasks::findTaskByContent(
		list<Task>::iterator begin, list<Task>::iterator end,
		string content){
	for (; begin != end; begin++)
		if ((*begin).getContent().find(content)!=string::npos)
			return begin;
	return end;
}
list<Task>::iterator ServiceTasks::findTaskByUserId(
		list<Task>::iterator begin, list<Task>::iterator end,
		unsigned int userId){
	for (; begin != end; begin++)
		if (to_string((*begin).getUserId()).find(to_string(userId))!=string::npos)
			return begin;
	return end;
}
list<Task>::iterator ServiceTasks::findTaskByAssignmentDate(
		list<Task>::iterator begin, list<Task>::iterator end,
		Date assignmentDate){
	for (; begin != end; begin++)
		if ((*begin).getAssignmentDate().comparisonDate(assignmentDate)==0)
			return begin;
	return end;
}
list<Task>::iterator ServiceTasks::findTaskByPlannedDate(
		list<Task>::iterator begin, list<Task>::iterator end,
		Date plannedDate){
	for (; begin != end; begin++)
		if ((*begin).getPlannedDate().comparisonDate(plannedDate)==0)
			return begin;
	return end;
}
list<Task>::iterator ServiceTasks::findTaskByDateDelivery(
		list<Task>::iterator begin, list<Task>::iterator end,
		Date dateDelivery){
	for (; begin != end; begin++)
		if ((*begin).getDateDelivery().comparisonDate(dateDelivery)==0)
			return begin;
	return end;
}
list<Task>::iterator ServiceTasks::findTaskByNotation(
		list<Task>::iterator begin, list<Task>::iterator end,
		string notation){
	for (; begin != end; begin++)
		if ((*begin).getNotation().find(notation)!=string::npos)
			return begin;
	return end;
}

void ServiceTasks::addTask(list<Task> &ListTasks, list<UserAccount> &ListUserAccounts, list<unsigned int> &ListFreeTaskId){
	system("cls");
	unsigned int maxTaskIdInListNow = (*ListTasks.begin()).getUserId();
	if (ListFreeTaskId.size() == 0) {
		for (Task t : ListTasks) {
			if (maxTaskIdInListNow < t.getTaskId())
				maxTaskIdInListNow = t.getTaskId();
		}
		maxTaskIdInListNow++;
	} else {
		maxTaskIdInListNow = *ListFreeTaskId.begin();
		ListFreeTaskId.pop_front();
	}
	Task newTask;
	newTask.setTaskId(maxTaskIdInListNow);
	cout << "Введите данные о новом задании c идентификатором "
			<< newTask.getTaskId() << "\n" << endl;
	cin >> newTask;
	if(newTask.getAssignmentDate().comparisonDate(newTask.getPlannedDate()) < 1){
		bool FalseInputUserId = false;
		for(UserAccount ua:ListUserAccounts)
			if(newTask.getUserId()==ua.getUserId()){
				FalseInputUserId = true;
				cout << "Подтвердите создание нового задания (да/нет)"
						<< endl;
				cout << newTask << endl;
				string confirmation(inputString(cin));
				if (confirmation == "да")
					ListTasks.push_back(newTask);
				if (confirmation != "да" && confirmation != "нет")
					showExceptionScreen();
			}
		if(!FalseInputUserId)
			showNotFindUserId(newTask.getUserId());
	}
	else
		showNotCompDate();
}

void ServiceTasks::editingContentTask(list<Task>::iterator &findTask){
	cout<<"Задание"<<endl;
	(*findTask).setContent(inputLine(cin));
}

void ServiceTasks::editingUserIdTask(list<Task>::iterator &findTask, list<UserAccount> &ListUserAccounts){
	cout<<"Идентификатор пользователя, которому будет пренадлежать задание"<<endl;
	unsigned int valueUserId = inputUnsignedInt(cin);
	bool FalseInputUserId = false;
	for(UserAccount ua:ListUserAccounts)
		if(ua.getUserId() == valueUserId){
			(*findTask).setUserId(valueUserId);
			FalseInputUserId = true;
			break;
		}
	if(!FalseInputUserId)
		showNotFindUserId(valueUserId);
}

void ServiceTasks::editingPlannedDateTask(list<Task>::iterator &findTask){
	cout<<"Планируемая дата сдачи заданя"<<endl;
	Date valuePlannedDate;
	cin >> valuePlannedDate;
	if((*findTask).getAssignmentDate().comparisonDate(valuePlannedDate) < 1)
		(*findTask).setPlannedDate(valuePlannedDate);
	else
		showNotCompDate();
}

void ServiceTasks::editingDateDeliveryTask(list<UserAccount>::iterator &activeAccount,list<Task>::iterator &findTask){
	if((*activeAccount).getUserId() != 0&&(*findTask).getPlannedDate().comparisonDate(Date::getTodayDate()) < 1){
		showNotPlannedDate();
	}
	else{
		cout << "Дата сдачи задания ";
		Date todayDate(Date::getTodayDate());
		cout << todayDate << endl;
		(*findTask).setDateDelivery(Date::getTodayDate());
		system("pause");
	}
}

void ServiceTasks::editingNotationTask(list<Task>::iterator &findTask){
	cout << "Примечане" <<endl;
	(*findTask).setNotation(inputLine(cin));
}

void ServiceTasks::editingAllDataTask(list<Task>::iterator &findTask, list<UserAccount> &ListUserAccounts){
	Task valueInputTask;
	valueInputTask.setTaskId((*findTask).getTaskId());
	cout<<"Задания"<<endl;
	valueInputTask.setContent(inputLine(cin));
	cout<<"Идентификатор пользователя, которому будет пренадлежать задание"<<endl;
	valueInputTask.setUserId(inputUnsignedInt(cin));
	bool FalseInputUserId = false;
	for(UserAccount ua:ListUserAccounts)
		if(ua.getUserId() == valueInputTask.getUserId()){
			FalseInputUserId = true;
			break;
		}
	if(!FalseInputUserId)
		showNotFindUserId(valueInputTask.getUserId());
	if(FalseInputUserId){
		valueInputTask.setAssignmentDate((*findTask).getAssignmentDate());
		cout<<"Планируемая дата сдачи заданя"<<endl;
		Date valuePlannedDate;
		cin >> valuePlannedDate;
		if((*findTask).getAssignmentDate().comparisonDate(valuePlannedDate) < 1){
			valueInputTask.setPlannedDate(valuePlannedDate);
			cout << valueInputTask.getPlannedDate() << endl;
			cout<<"Примечание"<<endl;
			valueInputTask.setNotation(inputLine(cin));
			(*findTask) = valueInputTask;
		}
		else
			showNotCompDate();
	}
}

void ServiceTasks::deleteTask(list<Task> &ListTasks, list<unsigned int> &ListFreeTaskId){
	system("cls");
	cout
			<< "ВВедите идентификатор  задания, данные которого необходимо удалить"
			<< endl;
	unsigned int inputTaskId = inputUnsignedInt(cin);
	ListTasks.sort(ServiceTasks::compTaskByTaskId);
	list<Task>::iterator findTask = ServiceTasks::findTaskByTaskId(ListTasks.begin(),ListTasks.end(),inputTaskId);
	if (findTask != ListTasks.end()) {
		cout
				<< "Подтвердите удаление учетной записи пользователя и всех его заданий (да/нет)"
				<< endl;
		cout << (*findTask) << endl;
		string confirmation(inputString(cin));
		if (confirmation == "да") {
			ServiceTasks::deleteTaskByIterator(ListTasks, findTask, ListFreeTaskId);
		}
		if (confirmation != "да" && confirmation != "нет")
			showExceptionScreen();
	}
	else{
		showNotFindData();
	}

}

void ServiceTasks::deleteTaskByIterator(list<Task> &ListTasks, list<Task>::iterator &findTask, list<unsigned int> &ListFreeTaskId){
	ListFreeTaskId.push_back((*findTask).getTaskId());
	ListTasks.remove((*findTask));
}

void ServiceTasks::deleteAllTask(list<Task> &ListTasks, list<unsigned int> &ListFreeTaskId){
	cout
			<< "Подтвердите удаление всех учетных записей пользователей и всех заданий (да/нет)"
			<< endl;
	string confirmation(inputString(cin));
	if (confirmation == "да") {
		while(true){
			list<Task>::iterator begin = ListTasks.begin();
			list<Task>::iterator end = ListTasks.end();
			if(begin == end)
				break;
			ServiceTasks::deleteTaskByIterator(ListTasks, begin, ListFreeTaskId);
		}
	}
	if (confirmation != "да" && confirmation != "нет")
		showExceptionScreen();
}

void ServiceTasks::showOverdueTasks(list<Task> &ListTasks){
	if(ListTasks.size()!=0){
		ListTasks.sort(ServiceTasks::compTaskByTaskId);
		system("cls");
		list<Task> findListTasks;
		list<Task>::iterator begin = ListTasks.begin();
		list<Task>::iterator end = ListTasks.end();
		for(Task t:ListTasks)
			if(t.getDateDelivery().getYear()==0&&t.getPlannedDate()-Date::getTodayDate()<1)
				findListTasks.push_back(t);
		if(findListTasks.size() != 0){
			showList(findListTasks);
			system("pause");
		}
		else
			showNotFindData();
	}
	else
		showNotData();
}

void ServiceTasks::showTasksByUserId(list<Task> &ListTasks){
	if(ListTasks.size()!=0){
		ListTasks.sort();
		system("cls");
		list<Task> findListTasks;
		list<Task>::iterator begin = ListTasks.begin();
		list<Task>::iterator end = ListTasks.end();
		unsigned int userId;
		cout
				<< "Введите идентификатор для поиска нужной записи"
				<< endl;
		userId = inputUnsignedInt(cin);
		while (true) {
			begin = ServiceTasks::findTaskByUserId(begin,end,userId);
			if (begin == end)
				break;
			findListTasks.push_back(*begin);
			begin++;
		}
		if (findListTasks.size() != 0) {
			showList(findListTasks);
			system("pause");
		} else
			showNotFindData();
	}
	else
		showNotData();
}

void ServiceTasks::showOverdueTasksToThreeDays(list<Task> &ListTasks){
	if(ListTasks.size()!=0){
		ListTasks.sort(ServiceTasks::compTaskByTaskId);
		system("cls");
		list<Task> findListTasks;
		list<Task>::iterator begin = ListTasks.begin();
		list<Task>::iterator end = ListTasks.end();
		for(Task t:ListTasks)
			if(t.getDateDelivery().getYear()==0&&t.getPlannedDate()-Date::getTodayDate()>0&&t.getPlannedDate()-Date::getTodayDate()<4)
				findListTasks.push_back(t);
		if(findListTasks.size() != 0){
			showList(findListTasks);
			system("pause");
		}
		else
			showNotFindData();
	}
	else
		showNotData();
}
