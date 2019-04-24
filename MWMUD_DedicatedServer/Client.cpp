#include "Client.h"

Client::Client(sf::TcpSocket* socket)
{
	this->socket = socket;
}

Client::~Client()
{
	delete socket;
}

bool Client::sentData()
{
	sf::Packet incPacket;
	if (socket->receive(incPacket) == sf::Socket::Status::Done)
	{
		dataPacket = incPacket;
		return true;
	}

	return false;
}

const sf::Packet& Client::getDataPacket() { return dataPacket; }