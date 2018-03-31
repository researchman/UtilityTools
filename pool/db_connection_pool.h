#ifndef UTILITY_TOOLS_DB_CONNECTION_POOL_H
#define UTILITY_TOOLS_DB_CONNECTION_POOL_H

#include <list>
#include <mutex>

namespace pool {
	template<class Typename>
	class DBConnectionPool {
	public:
		DBConnectionPool(int counts);
		virtual ~DBConnectionPool();
	private:
		int min;
		int max;

		//���ж���
		std::list<Typename> idleQueue;
		//ʹ���еĶ���
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
		//�ӿ��ж�����ȡ��һ�����ӣ����ӿ��ж�����ɾ��
		std::lock_guard<std::mutex> lg(idleMutex);
		Typename connection = idleQueue.front();
		idleQueue.pop_front();

		//std::lock_guard<std::mutex> lg_busy(busyMutex);
		//���˿������Ӽ��뵽�����ж�����
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
