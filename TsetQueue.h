#ifndef CIRCLE_H
#define CIRCLE_H

namespace TsetQueue {

	const int maxqueue = 10;
	using Queue_entry = int;//队列的元素类型
	enum Error_code :int;

	//顺序实现
	class Queue {
	public:
		Queue();
		//加入队尾
		Error_code push(const Queue_entry &item);
		//删除
		Error_code pop(Queue_entry &item);
		//取出head
		Error_code get_head(Queue_entry &x)const;
		bool empty()const;
		bool full() const;
		int size() const;
		void clear();
		
	private:
		int count;
		//按同一方向移动
		int head;//队首，有元素移除向后移动
		int end;//队尾，有元素加入向后移动
		Queue_entry entry[maxqueue];
	};

	//链式节点
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

		//加入队尾
		Error_code push(const Queue_entry &item);
		//删除
		Error_code pop(Queue_entry &item);
		//取出head
		//Error_code get_head(Queue_entry &x)const;

		bool empty()const;
		void number() const;
		//清空队列
		//void clear();
		//存储的元素个数
		//int size() const;
		//删除并保存该元素
		//~Node_Queue();
	private:  
		int count = 0;
		Node<Queue_entry> *head, *end;
	};
}


#endif
#pragma once#pragma once
