#ifndef UTILITY_TOOLS_DB_CONNECTION_POOL_H
#define UTILITY_TOOLS_DB_CONNECTION_POOL_H

#include <list>
#include <mutex>

namespace Pool {
	template<class Typename>
	class DBConnectionPool {
	public:
		DBConnectionPool(int counts);
		virtual ~DBConnectionPool();
	private:
		int min;
		int max;

		//空闲队列
		std::list<Typename> idleQueue;
		//使用中的队列
		std::list<Typename> busyQueue;

		std::mutex idleMutex;
		std::mutex busyMutex;

	private:
		int getIdleConnections();
		int getBusyConnections();
		Typename getConnection();
		void close();

	};

	template<class Typename>
	inline DBConnectionPool<Typename>::DBConnectionPool(int counts)
	{
	}
	template<class Typename>
	inline DBConnectionPool<Typename>::~DBConnectionPool()
	{
		close();
	}
	template<class Typename>
	inline int DBConnectionPool<Typename>::getIdleConnections()
	{
		std::lock_guard<std::mutex> lg(idleMutex);
		return idleQueue.size();
	}
	template<class Typename>
	inline int DBConnectionPool<Typename>::getBusyConnections()
	{
		std::lock_guard<std::mutex> lg(busyMutex);
		return busyQueue.size();
	}
	template<class Typename>
	inline Typename DBConnectionPool<Typename>::getConnection()
	{
		if (getIdleConnections() <= 0)
		{
			return NULL;
		}
		//从空闲队列中取出一个连接，并从空闲队列中删除
		std::lock_guard<std::mutex> lg(idleMutex);
		Typename connection = idleQueue.front();
		idleQueue.pop_front();

		//std::lock_guard<std::mutex> lg_busy(busyMutex);
		//将此空闲连接加入到工作中队列中
		busyQueue.push_back(connection);

		return connection;
	}
	template<class Typename>
	inline void DBConnectionPool<Typename>::close()
	{
		if (getIdleConnections()>0) {
			std::lock_guard<std::mutex> lg(idleMutex);
			int size = getIdleConnections();
			for (size_t i = 0;i<size;i++) {
				idleQueue.clear();
			}
			idleQueue.clear();
		}
	}
}

#endif // !UTILITY_TOOLS_DB_CONNECTION_POOL_H
