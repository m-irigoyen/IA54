#ifndef NETWORK_H_
#define NETWORK_H_

/**
*	The Nework class handles TCP communication with unity. It can send and receive messages.
*	Messages begin with "BEG " an end with " END". How the messages are sent is not the user's concern.
*
*	We use TCP : so we're sure every message will be recieved.
*/

#include <string>
#include <iostream>
#include <deque>
#include "SFML\Network.hpp"

using namespace std;

class Network
{
public:
	Network();

	bool closeConnection();
	bool initConnection(int portNumber = 13374);

	void listen();	// listen for incomming messages

	bool sendData(string data);
	bool receiveData(deque<string>* data);

private:
	sf::TcpSocket unitySocket;
	sf::TcpListener listener;
	bool initialized;

	deque<string> receivedMessages;

	//Message formatting stuff
	void cleanMessage(string& message);	// Removes empty spaces at the front and back of the string
	bool isValidMessage(string message);
	bool trimMessage(string& message);
};

#endif

