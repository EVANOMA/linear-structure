#ifndef TESTQUEUE_H
#define TESTQUEUE_H

#include "D:/code/test1/test1/Structure_Share.h"

namespace tsetqueue {

	const int maxqueue = 10;
	using StructureShare::Node;

	//顺序实现
	template<typename QueueEntry>
	class Queue {
	public:
		Queue();
		//加入队尾
		void push(const QueueEntry &item);
		//删除
		void pop(QueueEntry &item);
		//取出head
		void get_head(QueueEntry &x)const;
		bool empty()const;
		bool full() const;
		int size() const;
		void clear();		
	private:
		int count;
		//按同一方向移动
		int head;//队首，有元素移除向后移动
		int end;//队尾，有元素加入向后移动
		QueueEntry entry[maxqueue];
	};

	template<typename QueueEntry>
	Queue<QueueEntry>::Queue() :
		queue_count(0), head(0),
		end(maxqueue - 1)//为了能在第1次push时放在第一个位置
	{}
	template<typename QueueEntry>
	bool Queue<QueueEntry>::empty()const
	{
		//由于循环数组无法通过head和end的相对位置判断数组存储的元素个数
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
		//循环数组
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
		//循环数组
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

	//栈式实现
	template<typename QueueEntry>
	class NodeQueue {
	public:
		NodeQueue();
		~NodeQueue();
		void push(const QueueEntry &item);//加入队尾
		void pop(QueueEntry &item);//从队头删除
		//void get_head(QueueEntry &x)const;
		void clear();
		//访问
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
		//如果元素入队时队列为空
		if (end == nullptr) head = end = new_end;
		else {
			//先将新节点和队列的尾节点连接起来
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
		//指向栈顶的下一个节点
		item = old_top->entry;
		if (head == end)//如果只剩最后1个节点注意要更新end指针
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
