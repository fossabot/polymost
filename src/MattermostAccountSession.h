#ifndef MATTERMOST_ACCOUNT
#define MATTERMOST_ACCOUNT

#include <string>
#include "include/IProtocolSession.h"
#include "include/ICore.h"
#include "include/ITeam.h"
#include <json.hpp>

class PolyMost;
using namespace Polychat;

class Polychat::IAccount;
/**
 * Represents a user on Mattermost. Can be the logged in user
 * or just another team member.
 */
class MattermostAccountSession : public Polychat::IProtocolSession {
private:
	IAccount& coreAccount;
	
	// For logged in accounts
	std::string token = "";
	bool tokenIsValid = false;
	
	// The server this account is on.
	std::string host;
	bool ssl;
	unsigned int port;

	Polychat::ICore& core;

	// The websocket that is used for realtime updates.
	// NOTE: This is per account because the servers
	// only support 1 account per connection.
	std::shared_ptr<Polychat::IWebSocket> webSocketConnection;

	/**
	 * Update the teams.
	 */
	void updateTeams();

	void updateConversations(ITeam& team);

	static CONVERSATION_TYPE getTypeFromChar(char);
public:
	MattermostAccountSession(Polychat::IAccount& coreAccount, std::string host,
		unsigned int port, bool ssl, std::string token, Polychat::ICore& core);

	void setToken(std::string token) {
		this->token = token;
		tokenIsValid = true;
	}

	std::string getToken() {
		return token;
	}

	virtual IAccount& getAccount() {
		return coreAccount;
	}

	virtual void refresh(std::shared_ptr<IConversation> currentlyViewedConversation);

	virtual void updatePosts(IConversation& conversation, int limit);

	virtual bool isValid();
};

#endif // !MATTERMOST_ACCOUNT
