#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"

/*���������-����������*/

struct UserLoginExp: public std::exception
{
	const char* what() const noexcept override { return "error: user login is bisy"; }
};
struct UserPasswordExp : public std::exception
{
	const char* what() const noexcept override { return "error: the password length musy be from 4 to 8 digits or letters"; }
};

/*����� Chat �������� � ���� �������� ���������� ����������� ����*/

class Chat
{
public:
	void start() { _isChatWork = true; }; // ������ ������ ����, ��������� _isChatWork � true
	bool isChatWork() const { return _isChatWork; } // ���������� ������� ��������� ���� ��������/�� ��������
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; } // ���� ������� ������������ ������� �� ����������������� ���� - ���������� nullptr
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
	void changePassword(); // ��������� ������ �������� ������������

	std::shared_ptr<User> getUserByLogin(const std::string& login) const; // ����� ������������ �� ������
};
