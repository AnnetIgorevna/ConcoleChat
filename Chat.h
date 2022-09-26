#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"

/*���������, ���������� ����������*/

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "error: user login is bisy"; }
};

/*����� Chat �������� � ���� �������� ���������� ����������� ����*/

class Chat
{
public:
	void start() { _isChatWork = true; }; // ������ ������ ����, ��������� _isChatWork � true
	bool isChatWork() const { return _isChatWork; } // ���������� ������� ��������� ���� ��������/�� ��������
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; } 
	void showLoginMenu(); // �������� ���� �����������
	void showUserMenu(); // �������� ���� ������������
private:
	bool _isChatWork = false; // ����������, ���������� �� ����������� ������ ���� (� ������ ������ ���� ��������� � true)
	std::vector<User> _users; // ������ - ������, ���������� ���� ������������������ �������������
	std::vector<Message> _messages; // ������ - ������, ���������� ��� ������������ � ��� ���������
	std::shared_ptr<User> _currentUser = nullptr; // ��������� �� �������� ������������

	void logIn(); // ���� ����������� ������������
	void signUp(); // ���� ����������� ������ ������������
	void showChat(); // �������� ��� ��������� � ����
	void showAllUsersLogin(); // �������� ���� �������������, ���������������� � ����
	void addMessage(); // �������� ��������� ���� / ����������� ������������

//	std::vector<User> getAllUsers() { return _users; } 
//	std::vector<Message> getAllMessages() { return _messages; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const; // ����� ������������ �� ������
//	std::shared_ptr<User> getUserByName(const std::string& name) const; // ����� ������������ �� �����
};
