#include "Network.h"

Network::Network() : initialized(false)
{
}

bool Network::closeConnection()
{
	if (this->initialized)
	{
		this->unitySocket.disconnect();
		this->initialized = false;

		std::cout << "Network::closeConnection() : Disconnected" << std::endl;
		return true;
	}
	return false;
}

bool Network::sendData(string data)
{
	if (!this->initialized)
	{
		std::cout << "ERROR : Network::send : Socket connection hasn't been initialized. Aborting..." << std::endl;
		return false;
	}

	// Sending the data
	this->unitySocket.send(data.data(), data.length());

	return true;
}

bool Network::receiveData(deque<string>* data)
{
	this->listen();

	if (this->receivedMessages.empty())
		return false;

	// Transmitting messages
	*data = this->receivedMessages;
	this->receivedMessages.clear();
	return true;
}

void Network::cleanMessage(string& message)
{	
	while (message.back() == ' '
		|| message.back() == '\n'
		|| message.back() == '\r')
		message.pop_back();

	while (message.front() == ' '
		|| message.front() == '\n'
		|| message.front() == '\r')
		message.erase(message.begin());
}

bool Network::isValidMessage(string message)
{
	if (message.front() == 'B' && message.back() == 'E')
		return true;

	cout << "Invalid message : " << message.front() << ", " << message.back() << endl;
	return false;
}

bool Network::trimMessage(string & message)
{
	this->cleanMessage(message);
	if (this->isValidMessage(message))
	{
		message.pop_back();
		message.erase(message.begin());
		this->cleanMessage(message);
		return true;
	}
	cout << "Network::trimMessage : after trimming, couldn't validate message " << endl;
	return false;
}

bool Network::initConnection(int portNumber)
{
	// bind the listener to a port
	if (listener.listen(portNumber) != sf::Socket::Done)
	{
		std::cout << "ERROR : Network::initConnection : listening to port number " << portNumber << " failed. Aborting..." << std::endl;
		return false;
	}

	std::cout << "Network::initConnection : listener bound on port " << portNumber << endl;

	// accept a new connection
	if (listener.accept(this->unitySocket) != sf::Socket::Done)
	{
		std::cout << "ERROR : Network::initConnection : Couldn't accept client. Aborting..." << std::endl;
		return false;
	}

	std::cout << "Network::initConnection : Accepted connection on port " << portNumber << std::endl;
	this->unitySocket.setBlocking(false);

	return true;
}

void Network::listen()
{
	char data[100];
	std::size_t bytesReceived;

	if (this->unitySocket.receive(data, 100, bytesReceived) != sf::Socket::Done)
	{
		//std::cout << "Network::listen : failed to read socket" << endl;
		return;
	}


	// Cleaning and formatting
	string message(data);
	message.resize(bytesReceived);

	std::cout << "Network::Listen : Received " << bytesReceived << " bytes : " << message << endl;

	if (this->trimMessage(message))
	{
		this->receivedMessages.push_back(message);
	}
	else
	{
		std::cout << "Network::Listen : ERROR : Received invalid message : " << message << std::endl;
	}
}
