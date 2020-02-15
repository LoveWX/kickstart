#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

class StreamPool
{
public:
	StreamPool();
	~StreamPool();
	void InsertStream(int streamID);
	void DeleteStream(int count = 1);
	void DeleteStream1(int count = 1);
	void print();
private:
	mutex mtx;
	condition_variable cv;
	bool toExitThread = false;
	thread threads[3];
	int capacity[5];//�ƺ����������5����Ϊ-1����Ϊ�ڱ������
	void ClusterThread(int i);
	int currCluster;
	int *cluster[4];
	int count[4];
	const int maxCount = 10;
};

StreamPool::StreamPool()
{
	currCluster = 0;//ʵ�����ǵ�ǰʹ�õ����һ��cluster���±֮꣬���ĳcluster��capacity==-1
	cluster[0] = new int[maxCount];
	cluster[1] = nullptr;
	cluster[2] = nullptr;
	cluster[3] = nullptr;
	capacity[0] = 0;
	capacity[1] = -1;
	capacity[2] = -1;
	capacity[3] = -1;
	capacity[4] = -1;
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	count[3] = 0;
	threads[0] = thread(&StreamPool::ClusterThread, this, 1);
	threads[1] = thread(&StreamPool::ClusterThread, this, 2);
	threads[2] = thread(&StreamPool::ClusterThread, this, 3);
	this_thread::sleep_for(chrono::microseconds(100));//��֤��ʼִ��֮ǰ�������̶߳���blockס
}

StreamPool::~StreamPool()
{
	unique_lock<mutex> lck(mtx);
	capacity[0] = -1;
	capacity[1] = -1;
	capacity[2] = -1;
	capacity[3] = -1;
	toExitThread = true;
	lck.unlock();
	cv.notify_all();
	threads[2].join();
	threads[1].join();
	threads[0].join();
	if (cluster[0] != nullptr)
	{
		delete[] cluster[0];
	}
	if (cluster[1] != nullptr)
	{
		delete[] cluster[1];
	}
	if (cluster[2] != nullptr)
	{
		delete[] cluster[2];
	}
	if (cluster[3] != nullptr)
	{
		delete[] cluster[3];
	}
}

void StreamPool::print()
{
	cout << "currCluster=" << currCluster << endl;
	cout << "index:capacity count:" << endl;
	for (int i = 0; i <= currCluster; i++)
	{
		cout << i << ':' << capacity[i] << ' ' << count[i] << ':';
		for (int j = 0; j < count[i]; j++)
		{
			if (cluster[i] != nullptr)
			{
				cout << cluster[i][j] << ' ';
			}
			else
			{
				cout << "# ";
			}
		}
		cout << endl;
	}
}

void StreamPool::InsertStream(int streamID)
{
	cout << "InsertStream:" << streamID << ':';
	int i;
	for (i = 0; i <= currCluster; i++)
	{
		if (count[i] < maxCount)
		{
			break;
		}
	}
	if (i <= currCluster)
	{
		cluster[i][count[i]++] = streamID;
		cout << i << endl;
		//������������ʱ֮��������ڵ�ǰcluster��ʱ��һ��cluster�Ѿ������
		//������ﲻ����ʱ����������insert������������ʱ���ڵ�ǰcluster��ʱ�ᴥ���ȴ�
		this_thread::sleep_for(chrono::milliseconds(10));

		//�����λ���������һ��ʹ�õ�cluster�ϣ����Ҳ��ǵ�4��������ǡ�ò�����cluster������Ϊ8ʱ����Ҫ֪ͨ��׼����һ��cluster
		if (i == currCluster && count[i] == 8)
		{
			unique_lock<mutex> lck(mtx);
			capacity[i] = 8;
			lck.unlock();
			if (i != 3)
			{
				cv.notify_all();
			}
		}
		return;
	}
	if (currCluster == 3)
	{
		cout << "StreamPool is full" << endl;
		return;
	}
	//��Ҫ����µ�cluster�Ƿ��Ѿ����
	cout << "Check new cluster " << i;
	unique_lock<mutex> lck(mtx);
	while (capacity[i] == -1)
	{
		cv.wait(lck);
	}
	lck.unlock();
	cv.notify_all();
	cout << " Check new cluster :" << capacity[0] << ' ' << capacity[1] << ' ' << capacity[2] << ' ' << capacity[3] << endl;
	cluster[++currCluster[0]] = streamID;
	count[currCluster] = 1;
	cout << currCluster << endl;
	this_thread::sleep_for(chrono::milliseconds(10));
}

void StreamPool::DeleteStream1(int clusterID)
{
	cout << "DeleteStream:" << clusterID << ':';
	if (clusterID < 0 || clusterID>3 || count[clusterID] == 0)
	{
		cout << "delete err" << endl;
		return;
	}
	if (capacity[clusterID] != -1 && count[clusterID] > 0)
	{
		cout << cluster[clusterID][--count[clusterID]] << endl;
		this_thread::sleep_for(chrono::milliseconds(10));

		//ɾ����λ���������һ��ʹ�õ�cluster�ϣ����Ҳ��ǵ�3��������ǡ��ɾ�����cluster������Ϊ0ʱ����Ҫ�����һ��cluster�Ƿ��Ѿ�ɾ����
		if (clusterID == currCluster && clusterID != 3 && count[clusterID] == 0)
		{
			cout << "DeleteStream:" << clusterID << ":want to change currCluster";
			unique_lock<mutex> lck(mtx);
			capacity[clusterID] = 0;
			while (capacity[clusterID + 1] != -1)
			{
				cv.wait(lck);
			}
			lck.unlock();
			cv.notify_all();
			--currCluster;
		}

		//ɾ�����cluster������Ϊ7ʱ����Ҫ֪ͨ��ɾ����һ��cluster
		if (count[clusterID] == 7)
		{
			unique_lock<mutex> lck(mtx);
			capacity[clusterID] = 7;
			lck.unlock();
			cv.notify_all();//֪ͨ��һ��cluster���Թر�,���Ը����ж��ǲ����ڵ����ڶ���cluster��if(clusterID==currCluster-1)
			cout << "DeleteStream:" << clusterID << ":try to delete Cluster" << endl;
		}
		//ɾ����λ���������һ��ʹ�õ�cluster�ϣ����Ҳ��ǵ�0��������ǡ��ɾ�����cluster������Ϊ0ʱ����Ҫ֪ͨ������ɾ�����cluster
		//�����п��ܳ��������ر�cluster���������Ҫ��ѭ���ж�һ��
		else if (clusterID == currCluster && clusterID != 0 && count[clusterID] == 0)
		{
			unique_lock<mutex> lck(mtx);
			capacity[clusterID] = 0;
			lck.unlock();
			cv.notify_all();
		}
	}
}

void StreamPool::DeleteStream(int clusterID)
{
	cout << "DeleteStream:" << clusterID << ':';
	if (clusterID < 0 || clusterID>3 || count[clusterID] == 0)
	{
		cout << "delete err" << endl;
		return;
	}
	if (capacity[clusterID] != -1 && count[clusterID] > 0)
	{
		cout << cluster[clusterID][--count[clusterID]] << endl;
		this_thread::sleep_for(chrono::milliseconds(10));

		if (count[clusterID] == 0)
		{
			unique_lock<mutex> lck(mtx);
			capacity[clusterID] = 0;
			if (clusterID == currCluster)//ɾ����λ���������һ��ʹ�õ�cluster�ϣ�����ǡ��ɾ�����cluster������Ϊ0ʱ����Ҫ�����һ��cluster�Ƿ��Ѿ�ɾ����
			{
				while (capacity[clusterID + 1] != -1)
				{
					cv.wait(lck);
				}
			}
			for (; currCluster > 0 && count[currCluster] == 0 && count[currCluster - 1] <= 7; --currCluster) {}
			lck.unlock();
			cv.notify_all();//if(clusterID==0)����Ҫnotify
		}
		//ɾ�����cluster������Ϊ7ʱ����Ҫ֪ͨȥɾ����һ��cluster
		else if (count[clusterID] == 7)
		{
			unique_lock<mutex> lck(mtx);
			capacity[clusterID] = 7;
			if (clusterID == currCluster - 1 && capacity[currCluster] == 0)
			{
				--currCluster;
			}
			lck.unlock();
			cv.notify_all();//֪ͨ��һ��cluster���Թر�,���Ը����ж��ǲ����ڵ����ڶ���cluster��if(clusterID==currCluster-1)
			cout << "DeleteStream:" << clusterID << ":try to delete Cluster" << endl;
		}
		//ɾ����λ���������һ��ʹ�õ�cluster�ϣ����Ҳ��ǵ�0��������ǡ��ɾ�����cluster������Ϊ0ʱ����Ҫ֪ͨ������ɾ�����cluster
		//�����п��ܳ��������ر�cluster�����������ֻ��Ҫnotifyһ�Σ����
	}
}


//ֻ��ClusterThread(1),ClusterThread(2),ClusterThread(3)
void StreamPool::ClusterThread(int i)
{
	string slog = "In ClusterThread ";
	slog += to_string(i);
	slog += ":begin";
	cout << slog << endl;
	unique_lock<mutex> lck(mtx, defer_lock);
	while (true)
	{
		lck.lock();
		slog = string("In ClusterThread ") + to_string(i) + ":wait to malloc";
		cout << slog << endl;
		cv.wait(lck, [this, i] {return toExitThread || (capacity[i - 1] >= 8 && capacity[i] == -1);});
		slog = string("In ClusterThread ") + to_string(i) + ":start to malloc";
		cout << slog << endl;
		if (toExitThread)
		{
			slog = string("In ClusterThread ") + to_string(i) + ":to exit1";
			cout << slog << endl;
			lck.unlock();
			//cv.notify_all();
			break;
		}
		cluster[i] = new int[maxCount];//ʧ�ܵĻ�����Ҫ����һ��
		capacity[i] = 0;
		lck.unlock();
		cv.notify_all();

		lck.lock();
		slog = string("In ClusterThread ") + to_string(i) + ":wait to free";
		cout << slog << endl;
		cv.wait(lck, [this, i] {return toExitThread || (capacity[i - 1] <= 7 && capacity[i] == 0 && (capacity[i + 1] == -1));});
		delete[] cluster[i];
		cluster[i] = nullptr;
		capacity[i] = -1;
		lck.unlock();
		cv.notify_all();
		if (toExitThread)
		{
			slog = string("In ClusterThread ") + to_string(i) + ":to exit2";
			cout << slog << endl;
			break;
		}
	}
}

int main()
{
	StreamPool sp;
	sp.print();
	for (int i = 0; i < 40; i++)
	{
		sp.InsertStream(i);
	}
	sp.print();
	for (int i = 0; i < 13; i++)
	{
		sp.DeleteStream(3);
	}
	sp.print();
	for (int i = 0; i < 13; i++)
	{
		sp.DeleteStream(2);
	}
	sp.print();
	for (int i = 0; i < 14; i++)
	{
		sp.DeleteStream(1);
	}
	sp.print();
	for (int i = 0; i < 12; i++)
	{
		sp.InsertStream(i);
	}
	sp.print();
	for (int i = 0; i < 2; i++)
	{
		sp.DeleteStream(2);
	}
	sp.DeleteStream(1);
	sp.DeleteStream(1);
	sp.DeleteStream(1);
	sp.InsertStream(88);
	sp.DeleteStream(1);
	sp.InsertStream(77);
	sp.DeleteStream(1);
	sp.InsertStream(66);
	sp.DeleteStream(1);
	sp.print();
	for (int i = 0; i < 30; i++)
	{
		sp.InsertStream(i+10);
	}
	sp.print();
	for (int i = 0; i < 10; i++)
	{
		sp.DeleteStream(1);
	}
	sp.print();
	for (int i = 0; i < 10; i++)
	{
		sp.DeleteStream(2);
	}
	sp.print();
	for (int i = 0; i < 10; i++)
	{
		sp.DeleteStream(0);
	}
	sp.print();
	for (int i = 0; i < 11; i++)
	{
		sp.DeleteStream(3);
	}
	sp.print();
	sp.DeleteStream(2);
	sp.print();
	return 0;
}