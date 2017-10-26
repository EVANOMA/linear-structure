#include<iostream>
using namespace std;

#include "TsetQueue.h"
namespace TsetQueue {
	
	enum Error_code {
		success, overflow
		, underflow
	};
	Queue::Queue()
		/*Post:The Queue is initialized to be empty*/
	{
		count = 0;
		head = 0;
		end = maxqueue - 1;//Ϊ�����ڵ�1��pushʱ���ڵ�һ��λ��
	}
	bool Queue::empty()const
	{
		//����ѭ�������޷�ͨ��head��end�����λ���ж�����洢��Ԫ�ظ���
		return count == 0;
	}
	bool Queue::full()const
	{
		return count == maxqueue;
	}
	Error_code Queue::push(const Queue_entry &item)
	{
		if (count >= maxqueue) return overflow;
		++count;
		//ѭ������
		end = ((end + 1) == maxqueue) ? 0 : (end + 1);
		entry[end] = item;
		return success;
	}
	Error_code Queue::pop(Queue_entry &item)
	{
		if (count <= 0) return underflow;
		--count;
		//ѭ������
		item = entry[head];
		head = ((head + 1) == maxqueue) ? 0 : (head + 1);
		return success;
	}
	Error_code Queue::get_head(Queue_entry &item)const
	{
		if (count <= 0) return underflow;
		item = entry[head];
		return success;
	}
	int Queue::size()const
	{
		return count;
	}
	void Queue::clear()
	{
		count = head = end = 0;
	}
	//��ʽʵ��
	template<typename Node_entry>
	Node<Node_entry>::Node()
	{
		next = nullptr;
	}
	template<typename Node_entry>
	Node<Node_entry>::Node(Node_entry item, Node* add_on)
	{
		entry = item;
		next = add_on;
	}

	Node_Queue::Node_Queue()
	{
		head =end= nullptr;
	}
	bool Node_Queue::empty()const
	{
		return count == 0;
	}
	void Node_Queue::number()const
	{
		cout << count << endl;
	}
	Error_code Node_Queue::push(const Queue_entry &item)
	{
		Node<Queue_entry>* new_end = new Node<Queue_entry>(item);
		if (new_end == nullptr) return overflow;
		//���Ԫ�����ʱ����Ϊ��
		if (end == nullptr) head = end = new_end;
		else {
			//�Ƚ��½ڵ�Ͷ��е�β�ڵ���������
			end->next = new_end;
			end = new_end;
		}
		++count;
		return success;
	}
	Error_code Node_Queue::pop(Queue_entry &item)
	{
		Node<Queue_entry> *old_top = head;
		if (head == nullptr)  return underflow;
		//ָ��ջ������һ���ڵ�
		item = old_top->entry;
		head = old_top->next;
		delete old_top;
		--count;
		return success;
	}
	
}

