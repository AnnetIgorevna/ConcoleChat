#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"

/*Структура, содержащая исключение*/

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "error: user login is bisy"; }
};

/*Класс Chat содержит в себе основную реализацию консольного чата*/

class Chat
{
public:
	void start() { _isChatWork = true; }; // начало работы чата, установка _isChatWork в true
	bool isChatWork() const { return _isChatWork; } // возвращает текущее состояние чата работает/не работает
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; } 
	void showLoginMenu(); // показать меню регистрации
	void showUserMenu(); // показать меню пользователя
private:
	bool _isChatWork = false; // переменная, отвечающая за прекращение работы чата (в начале работы чата переходит в true)
	std::vector<User> _users; // вектор - массив, содержащий всех зарегистрированных пользователей
	std::vector<Message> _messages; // вектор - массив, содержащий все отправленные в чат сообщения
	std::shared_ptr<User> _currentUser = nullptr; // указатель на текущего пользователя

	void logIn(); // меню авторизации пользователя
	void signUp(); // меню регистрации нового пользователя
	void showChat(); // показать все сообщения в чате
	void showAllUsersLogin(); // показать всех пользователей, зарегистрованных в чате
	void addMessage(); // написать сообщение всем / конкретному пользователю

//	std::vector<User> getAllUsers() { return _users; } 
//	std::vector<Message> getAllMessages() { return _messages; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const; // найти пользователя по логину
//	std::shared_ptr<User> getUserByName(const std::string& name) const; // найти пользователя по имени
};
