#ifndef TESTQUEUE_H
#define TESTQUEUE_H

#include "D:/code/test1/test1/Structure_Share.h"

namespace tsetqueue {

	const int maxqueue = 10;
	using StructureShare::Node;

	//˳��ʵ��
	template<typename QueueEntry>
	class Queue {
	public:
		Queue();
		//�����β
		void push(const QueueEntry &item);
		//ɾ��
		void pop(QueueEntry &item);
		//ȡ��head
		void get_head(QueueEntry &x)const;
		bool empty()const;
		bool full() const;
		int size() const;
		void clear();		
	private:
		int count;
		//��ͬһ�����ƶ�
		int head;//���ף���Ԫ���Ƴ�����ƶ�
		int end;//��β����Ԫ�ؼ�������ƶ�
		QueueEntry entry[maxqueue];
	};

	template<typename QueueEntry>
	Queue<QueueEntry>::Queue() :
		queue_count(0), head(0),
		end(maxqueue - 1)//Ϊ�����ڵ�1��pushʱ���ڵ�һ��λ��
	{}
	template<typename QueueEntry>
	bool Queue<QueueEntry>::empty()const
	{
		//����ѭ�������޷�ͨ��head��end�����λ���ж�����洢��Ԫ�ظ���
		return queue_count == 0;
	}
	template<typename QueueEntry>
	bool Queue<QueueEntry>::full()const
	{
		return queue_count == maxqueue;
	}
	template<typename QueueEntry>
	void Queue<QueueEntry>::push(const QueueEntry &item)
	{
		if (queue_count >= maxqueue) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "Queue is full" << endl;
			return;
		}
		++queue_count;
		//ѭ������
		end = ((end + 1) == maxqueue) ? 0 : (end + 1);
		entry[end] = item;
	}
	template<typename QueueEntry>
	void Queue<QueueEntry>::pop(QueueEntry &item)
	{
		if (queue_count <= 0) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "Queue is empty" << endl;
			return;
		}
		--queue_count;
		//ѭ������
		item = entry[head];
		head = ((head + 1) == maxqueue) ? 0 : (head + 1);
	}
	template<typename QueueEntry>
	void Queue<QueueEntry>::get_head(QueueEntry &item)const
	{
		if (queue_count <= 0) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "Queue is empty" << endl;
			return;
		}
		item = entry[head];
	}
	template<typename QueueEntry>
	int Queue<QueueEntry>::size()const
	{
		return queue_count;
	}
	template<typename QueueEntry>
	void Queue<QueueEntry>::clear()
	{
		queue_count = head = end = 0;
	}

	//ջʽʵ��
	template<typename QueueEntry>
	class NodeQueue {
	public:
		NodeQueue();
		~NodeQueue();
		void push(const QueueEntry &item);//�����β
		void pop(QueueEntry &item);//�Ӷ�ͷɾ��
		//void get_head(QueueEntry &x)const;
		void clear();
		//����
		bool empty()const;
		int size() const;
	//private:  
		int queue_count = 0;
		Node<QueueEntry> *head, *end;
	};

	template<typename QueueEntry>
	NodeQueue<QueueEntry>::NodeQueue() :
		head(nullptr), end(nullptr)
	{}
	template<typename QueueEntry>
	NodeQueue<QueueEntry>::~NodeQueue()
	{
		clear();
	}
	template<typename QueueEntry>
	bool NodeQueue<QueueEntry>::empty()const
	{
		return queue_count == 0;
	}
	template<typename QueueEntry>
	int NodeQueue<QueueEntry>::size()const
	{
		return queue_count;
	}
	template<typename QueueEntry>
	void NodeQueue<QueueEntry>::push(const QueueEntry &item)
	{
		Node<QueueEntry>* new_end = nullptr;
		try {
			new_end = new Node<QueueEntry>(item);
			if (new_end == nullptr) throw bad_alloc();
		}
		catch (bad_alloc err) {
			cout << err.what() << endl;
		}
		//���Ԫ�����ʱ����Ϊ��
		if (end == nullptr) head = end = new_end;
		else {
			//�Ƚ��½ڵ�Ͷ��е�β�ڵ���������
			end->next = new_end;
			end = new_end;
		}
		++queue_count;
	}
	template<typename QueueEntry>
	void NodeQueue<QueueEntry>::pop(QueueEntry &item)
	{
		auto old_top = head;
		if (head == nullptr) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "Queue is empty" << endl;
			return;
		}
		//ָ��ջ������һ���ڵ�
		item = old_top->entry;
		if (head == end)//���ֻʣ���1���ڵ�ע��Ҫ����endָ��
			head = end = nullptr;
		else
		   head = old_top->next;
		delete old_top;
		--queue_count;
	}
	template<typename QueueEntry>
	void NodeQueue<QueueEntry>::clear()
	{
		if (queue_count == 0) return;
		auto old_head = head;
		while (head) {
			head = head->next;
			delete old_head;
		}
		queue_count = 0;
		end = nullptr;
	}
}//namespace tsetqueue


#endif
 /*
 #include "TsetQueue.h"
 using namespace tsetqueue;

 int main() {
 Queue q1;
 for (int i = 0;i < 5;++i)
 q1.push(i);
 Queue_entry item = 0;
 while (!q1.empty()) {
 q1.pop(item);
 cout << item << endl;
 }
 return 0;

 }
 */
#pragma once
