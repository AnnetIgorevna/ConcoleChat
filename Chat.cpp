#include "Chat.h"

#include <iostream>


//std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
//{
//	for (auto& user : _users)
//	{
//		if (name == user.getUserName())
//			return std::make_shared<User>(user);
//	}
//	return nullptr;
//}

void Chat::showLoginMenu()
{
	_currentUser = nullptr;
	char operation;
	std::cout << "\n*** Welcome to Console Chat! ***" << std::endl;
	
	do
	{
		std::cout << " \n1 - Autorization \n2 - Registration \n0 - Exit" << std::endl;
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			logIn();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}	
			break;
		case '0':
			_isChatWork = false;
			break;
		default:
			std::cout << "Wrong choice! Choose 0, 1 or 2" << std::endl;
			break;
		}
	} while (!_currentUser && _isChatWork);
}

void Chat::showUserMenu()
{
	std::cout << "\n*** You have entered the User menu ***" << std::endl;
	char operation;

	do
	{
		std::cout << "\n1 - Show all users \n2 - Show all messages \n3 - Add message to chat \n4 - Sign Out" << std::endl;
		std::cin >> operation;
		switch (operation)
		{
		case '1':
			showAllUsersLogin();
			break;
		case '2':
			showChat();
			break;
		case '3':
			addMessage();
			break;
		case '4':
			_currentUser = nullptr;
			break;
		default:
			std::cout << "Wrong choice! Choose 1 - 4" << std::endl;
			break;
		}
	} while (_currentUser);

}

void Chat::logIn()
{
	std::string login, password;
	char operation;

	do {
		std::cout << "Enter your login: " << std::endl;
		std::cin >> login;
		_currentUser = getUserByLogin(login);
		if (_currentUser == nullptr)
		{
			std::cout << "The login entered is incorrect. To exit press 0, to continue press any key:" << std::endl;
			std::cin >> operation;
			if (operation == 0)
				break;
		}
		else
		{
			do
			{
				std::cout << "Enter your password: " << std::endl;
				std::cin >> password;
				if (password != _currentUser->getUserPassword())
				{
					std::cout << "The password entered is incorrect. To exit press 0, to continue press any key:" << std::endl;
					std::cin >> operation;
					if (operation == 0)
						break;
				}
			} while (password != _currentUser->getUserPassword());
		}
	} while (!_currentUser);
}

void Chat::signUp()
{
	std::string login, password, name;

	std::cout << "Enter your login: " << std::endl;
	std::cin >> login;
	std::cout << "Enter your password: " << std::endl;
	std::cin >> password;
	std::cout << "Enter your name: " << std::endl;
	std::cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	User user = User(login, password, name);
	_users.push_back(user);
	_currentUser = std::make_shared<User>(user);

	std::cout << "\nHello, " << user.getUserLogin() << "! Welcome to chat!" << std::endl;
}

void Chat::showChat()
{
	std::string from, to;

	if (!(_messages.size()))
	{
		std::cout << "It's no messages in this chat!" << std::endl;
		return;
	}
	std::cout << "\n*** This is all messages in this chat ***" << std::endl;

	for (auto& message : _messages)
	{
		if (_currentUser->getUserLogin() == message.getFrom() || _currentUser->getUserLogin() == message.getTo() || message.getTo() == "all")
		{
			from = (_currentUser->getUserLogin() == message.getFrom()) ? "me" : getUserByLogin(message.getFrom())->getUserLogin();
			if (message.getTo() == "all")
			{
				to = "all";
			}
			else
			{
				to = (_currentUser->getUserLogin() == message.getTo()) ? "me" : getUserByLogin(message.getTo())->getUserLogin();
			}
			std::cout << "From: " << from << "\nTo: " << to << std::endl;
			std::cout << "Text: " << message.getText() << std::endl << std::endl;
		}
	}
	std::cout << "*** End of chat ***" << std::endl;
}

void Chat::showAllUsersLogin()
{
	std::cout << "\n*** All users in this Chat ***" << std::endl;
	
	for (auto& user : _users)
	{
		if (_currentUser->getUserLogin() == user.getUserLogin())
		{
			std::cout << "me";
		}
		else
		{
			std::cout << user.getUserLogin();
		}
		std::cout << std::endl;
	}
	std::cout << "****************************" << std::endl;
}

void Chat::addMessage()
{
	std::string to, text;

	std::cout << "\nTo (login of user or all): " << std::endl;
	std::cin >> to;
	std::cout << "Enter the text: " << std::endl;
	std::cin.ignore();
	std::getline(std::cin, text);

	if (!(to == "all" || getUserByLogin(to)))
	{
		std::cout << "Error send message: can't find user with name " << to << std::endl;
		return;
	}
	
	if (to == "all")
	{
		_messages.push_back(Message{ _currentUser->getUserLogin(), "all", text });
	}
	else
	{
		_messages.push_back(Message{ _currentUser->getUserLogin(), getUserByLogin(to)->getUserLogin(), text });
	}
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : _users)
	{
		if (login == user.getUserLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

