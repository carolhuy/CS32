#include "ChatTracker.h"
#include <string>
#include <vector>
#include<list>
#include<iterator>
#include<functional>
using namespace std;

//get biggest prime number 
int findPrime(int num) {
	int prime = num;
	for (int i = 2; i <= num / 2; ++i) {
		if (prime % i == 0) {
			--prime;
			findPrime(prime);
			break;
		}
	}
	return prime;
}
class ChatTrackerImpl
{
public:
	ChatTrackerImpl(int maxBuckets);
	void join(string user, string chat);
	int terminate(string chat);
	int contribute(string user);
	int leave(string user, string chat);
	int leave(string user);
	//hash function to convert from string key to bucket number 
	int getHash(std::string key);

private:
	struct Info
	{
		Info(string u, string c) : user(u), chat(c), count(0) {}
		string user;
		string chat;
		int count;
	};
	//vector with buckets that store lists 
	vector<list<Info>> m_info;
	vector<Info> m_usersWhoLeft;
	int numBuckets;
};

ChatTrackerImpl::ChatTrackerImpl(int maxBuckets)
{
	//get prime number of buckets 
	int primeNum = findPrime(maxBuckets);
	numBuckets = primeNum;
	//setting size of vector equal to prime number of buckets 
	m_info.resize(primeNum);
}

//hash function to convert from string key to bucket number 
int ChatTrackerImpl::getHash(std::string key) {
	std::hash<std::string> str_hash;
	unsigned int hashValue = str_hash(key);
	unsigned int bucketNum = hashValue % numBuckets;
	return bucketNum;
}

void ChatTrackerImpl::join(string user, string chat)
{
	//find which bucket to put in 
	int bucketLocation = getHash(user);

	//check if location has something in it
	if (!m_info[bucketLocation].empty()) {
		//end of vector 
		auto p = m_info[bucketLocation].end();
		while (p != m_info[bucketLocation].begin())
		{
			//move through list 
			p--;
			//if user has joined the chat before 
			if (p->user == user && p->chat == chat)
			{
				//store information of chat previously joined 
				Info info = *p;

				//delete previously joined chat 
				m_info[bucketLocation].erase(p);

				//push back to indicate current chat, with old chat contribution info 
				m_info[bucketLocation].push_back(info);
				return;
			}
		}

	}
	//if bucket is empty or if user has not joined chat before, add to end of list 
	m_info[bucketLocation].push_back(Info(user, chat));
}

int ChatTrackerImpl::terminate(string chat)
{
	//store total number of contributions for a chat 
	int total = 0;

	//have to go through all the buckets since not sure which users are in which chat 
	for (int i = 0; i < numBuckets; ++i) {
		auto p = m_info[i].begin();
		while (p != m_info[i].end())
		{
			if (p->chat==chat)
			{
				total += p->count;
				p = m_info[i].erase(p);
			}
			else
				p++;
		}
	}
	auto ptr = m_usersWhoLeft.begin();
	while (ptr != m_usersWhoLeft.end())
	{
		if (ptr->chat == chat)
		{
			total += ptr->count;
			ptr = m_usersWhoLeft.erase(ptr);
		}
		else
			ptr++;
	}
	return total;
}

int ChatTrackerImpl::contribute(string user)
{
	//find which bucket user located
	int bucketLocation = getHash(user);

	//go through the bucket 
	auto p = m_info[bucketLocation].end();
	while (p != m_info[bucketLocation].begin())
	{
		p--;
		//find current chat of the user 
		if (p->user == user)
		{
			//both the user's count of contributions to that user's current chat and that current chat's count of contributions are increased by one. 
			p->count++;
			//Return the resulting user's count of contributions to that current chat.
			return p->count;
		}
	}
	//If the user has no current chat, return 0
	return 0;
}

int ChatTrackerImpl::leave(string user, string chat)
{
	//find which bucket user located
	int bucketLocation = getHash(user);

	//going through the bucket 
	auto p = m_info[bucketLocation].end();
	while (p != m_info[bucketLocation].begin())
	{
		p--;
		//if user is in chat 
		if (p->user == user && p->chat == chat)
		{
			int count = p->count;
			//record which user left - used for terminate total contributions later on 
			m_usersWhoLeft.push_back(*p);
			//user not associated with chat 
			m_info[bucketLocation].erase(p);
			//user's current contributions to chat
			return count;
		}
	}
	//user is not in that chat 
	return -1;
}

int ChatTrackerImpl::leave(string user)
{
	//find which bucket user located
	int bucketLocation = getHash(user);

	//going through bucket to find user 
	auto p = m_info[bucketLocation].end();
	while (p != m_info[bucketLocation].begin())
	{
		p--;
		if (p->user == user)
		{
			//get user contributions 
			int count = p->count;

			//store contributions of chat 
			m_usersWhoLeft.push_back(*p);

			//remove user from current chat 
			m_info[bucketLocation].erase(p);
			return count;
		}
	}
	//user has no chat  
	return -1;
}

//*********** ChatTracker functions **************

// These functions simply delegate to ChatTrackerImpl's functions.
// You probably don't want to change any of this code.

ChatTracker::ChatTracker(int maxBuckets)
{
	m_impl = new ChatTrackerImpl(maxBuckets);
}

ChatTracker::~ChatTracker()
{
	delete m_impl;
}

void ChatTracker::join(string user, string chat)
{
	m_impl->join(user, chat);
}

int ChatTracker::terminate(string chat)
{
	return m_impl->terminate(chat);
}

int ChatTracker::contribute(string user)
{
	return m_impl->contribute(user);
}

int ChatTracker::leave(string user, string chat)
{
	return m_impl->leave(user, chat);
}

int ChatTracker::leave(string user)
{
	return m_impl->leave(user);
}
