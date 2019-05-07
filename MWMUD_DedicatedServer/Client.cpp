#include "Client.h"

#include <iostream>

#include "Dispatcher.h"

Client::Client(sf::TcpSocket* socket)
{
	this->socket = socket;
}

Client::~Client()
{
	delete socket;
}

const std::string Client::getName() { return name; }
const sf::IpAddress Client::getIp() { return socket->getRemoteAddress(); }

bool Client::isLoggedIn() { return loggedIn; }

bool Client::logIn(std::string name)
{
	if (loggedIn) return false;

	Dispatcher::enqueueEvent(new ServerEvent::Message::Broadcast(name + " has logged in."));

	this->name = name;
	loggedIn = true;
	return true;
}

bool Client::logOut()
{
	if (!loggedIn) return false;

	Dispatcher::enqueueEvent(new ServerEvent::Message::Broadcast(name + " has logged out."));

	name = "";
	loggedIn = false;
	return true;
}

bool Client::sentData()
{
	sf::Packet incPacket;
	if (socket->receive(incPacket) == sf::Socket::Status::Done)
	{
		incPacket >> data;
		return true;
	}

	return false;
}

const std::string Client::getData()
{
	std::string temp = data;
	data.clear();
	return temp;
}

void Client::sendPacket(sf::Packet& packet) const
{
	socket->send(packet);
}

void Client::sendMessage(std::string msg) const
{
	sf::Packet packet;
	packet << msg;
	socket->send(packet);
}