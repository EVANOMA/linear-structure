#ifndef CIRCLE_H
#define CIRCLE_H

namespace TsetQueue {

	const int maxqueue = 10;
	using Queue_entry = int;//���е�Ԫ������
	enum Error_code :int;

	//˳��ʵ��
	class Queue {
	public:
		Queue();
		//�����β
		Error_code push(const Queue_entry &item);
		//ɾ��
		Error_code pop(Queue_entry &item);
		//ȡ��head
		Error_code get_head(Queue_entry &x)const;
		bool empty()const;
		bool full() const;
		int size() const;
		void clear();
		
	private:
		int count;
		//��ͬһ�����ƶ�
		int head;//���ף���Ԫ���Ƴ�����ƶ�
		int end;//��β����Ԫ�ؼ�������ƶ�
		Queue_entry entry[maxqueue];
	};

	//��ʽ�ڵ�
	template<typename Node_entry>
	struct Node {
		Node_entry entry;
		Node<Node_entry> *next;
		Node();
		Node(Node_entry item, Node<Node_entry> *add_on = NULL);
	};
	class Node_Queue {
	public:
		Node_Queue();

		//�����β
		Error_code push(const Queue_entry &item);
		//ɾ��
		Error_code pop(Queue_entry &item);
		//ȡ��head
		//Error_code get_head(Queue_entry &x)const;

		bool empty()const;
		void number() const;
		//��ն���
		//void clear();
		//�洢��Ԫ�ظ���
		//int size() const;
		//ɾ���������Ԫ��
		//~Node_Queue();
	private:  
		int count = 0;
		Node<Queue_entry> *head, *end;
	};
}


#endif
#pragma once#pragma once
