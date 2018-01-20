#ifndef MY_MESSAGE_QUEUE_H
#define MY_MESSAGE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

typedef struct Message {
	size_t nType;
	std::string message;
};

template <class T>
class MessageQueue {
public:
	MessageQueue():_queue,_mutex,_condition {}
	virtual ~MessageQueue() {}
private:
	MessageQueue& operator=(const MessageQueue&) = delete;
	MessageQueue(const MessageQueue& other) = delete;
public:
	int push(T& val) {
		std::lock_guard<std::mutex> lg(_mutex);
		_queue.push(val);
		_condition.notify_one();
	}
	
	bool pop(T& record) {	
		if (empty())
		{
			return false;
		}
		std::lock_guard<std::mutex> lg(_mutex);
		record = std::move(_queue.front());
		_queue.pop();
		return true;
	}

	size_t size() {
		std::lock_guard<std::mutex> lg(_mutex);
		return _queue.size();
	}

	bool empty() {
		std::lock_guard<std::mutex> lg(_mutex);
		return _queue.empty();
	}

private:
	std::queue<T> _queue;
	mutable std::mutex _mutex;
	condition_variable _condition;
};

#endif // !MY_MESSAGE_QUEUE_H
