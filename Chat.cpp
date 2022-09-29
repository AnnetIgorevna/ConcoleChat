#include "Chat.h"
#include <iostream>

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
		std::cout << "\n1 - Show all users \n2 - Show all messages" 
			<< "\n3 - Add message to chat \n4 - Change password \n5 - Sign Out" << std::endl;
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
			changePassword();
			break;
		case '5':
			_currentUser = nullptr;
			break;
		default:
			std::cout << "Wrong choice! Choose 1 - 5" << std::endl;
			break;
		}
	} while (_currentUser);

}

void Chat::logIn()
{
	std::string login, password;
	std::string operation;

	do {
		std::cout << "Enter your login: " << std::endl;
		std::cin >> login;
		_currentUser = getUserByLogin(login);
		if (_currentUser == nullptr)
		{
			std::cout << "The login entered is incorrect. To exit press 0, to continue press any key:" << std::endl;
			std::cin >> operation;
			if (operation == "0")
				return;
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
					if (operation == "0")
					{
						_currentUser = nullptr;
						return;
					}
				}
			} while (password != _currentUser->getUserPassword());
		}
	} while (!_currentUser);

}

void Chat::signUp()
{
	std::string login, password, name;
	bool passwordOk = false;

	std::cout << "Enter your login: " << std::endl;
	std::cin >> login;
	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}
	while (!(passwordOk))
	{
		std::cout << "Enter your password: " << std::endl;
		std::cin >> password;
		if (password.length() < 4 || password.length() > 8)
			throw UserPasswordExp();
		else
			passwordOk = true;
	}
	std::cout << "Enter your name: " << std::endl;
	std::cin >> name;

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
			from = (_currentUser->getUserLogin() == message.getFrom()) ? "Me" : getUserByLogin(message.getFrom())->getUserLogin();
			if (message.getTo() == "all")
			{
				to = "all";
			}
			else
			{
				to = (_currentUser->getUserLogin() == message.getTo()) ? "Me" : getUserByLogin(message.getTo())->getUserLogin();
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
			std::cout << "Me";
		}
		else
		{
			std::cout << user.getUserLogin();
		}
		std::cout << std::endl;
	}
	std::cout << "******************************" << std::endl;
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

void Chat::changePassword()
{
	std::string password;
	std::cout << "Enter new password: " << std::endl;
	std::cin >> password;
	if (password.length() < 4 || password.length() > 8)
		throw UserPasswordExp();
	else
	{
		for (auto& user : _users)
		{
			if (_currentUser->getUserLogin() == user.getUserLogin())
				user.setUserPassword(password);
		}
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

