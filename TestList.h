#ifndef CIRCLE_H
#define CIRCLE_H


namespace tsetlist {
	
	//链式节点
	template<typename ListEntry>
	struct Node {
		ListEntry entry;
		Node<ListEntry> *next;
		//通过下标找到对应的结点
		Node();
		Node(ListEntry item, Node<ListEntry> *add_on = NULL);
		~Node();
	};
	
	//链表
	template<typename ListEntry>
	class List {
	public:
		List();		
		~List();
		//访问
		bool empty()const;
		void size()const;
		void retrieve(int position, ListEntry &item)const;
		//修改
		void clear();
		
		void insert(int position, const ListEntry &item);
		void replace(int position, const ListEntry &item);
		void remove(int position, ListEntry &item);
		
		//Error_code traverse(void(*visit)(ListEntry&));		
		//List(const List<ListEntry>&copy);
		//void operator=(const List<ListEntry>&copy);
	protected:
		int List_count=0;
		Node<ListEntry> *head = nullptr;
		/*保存上次查找的位置，如果访问位于其后面的元素可以减少访问时间。*/
		mutable int current_position=0;
		mutable Node<ListEntry>*current=nullptr;
		//为了方便其他函数调用，返回值为Node<ListEntry>*
		//该函数不能处理异常
		Node<ListEntry>* set_position(int position)const;
	};
	//双向节点
	template<typename Node_entry>
	struct BNode {
		Node_entry entry;
		//由于所有的指针在内存中所占的大小相同。为了避免循环定义，C++允许在定义类型前使用类型指针
		BNode<Node_entry> *next;
		BNode<Node_entry> *front;
		BNode();
		BNode(Node_entry item, BNode<Node_entry> *q1 = nullptr,
			BNode<Node_entry> *q2 = nullptr);
		~BNode();
	};
	//双向链表
	template<typename ListEntry>
	class BList {
	public:
		BList();
		~BList();
		//访问
		bool empty()const;
		void size()const;
		void retrieve(int position, ListEntry &item)const;
		//修改
		void clear();

		void insert(int position, const ListEntry &item);
		void replace(int position, const ListEntry &item);
		void remove(int position, ListEntry &item);

		//Error_code traverse(void(*visit)(ListEntry&));		
		//List(const List<ListEntry>&copy);
		//void operator=(const List<ListEntry>&copy);
	private:
		int BList_count = 0;
		//由于允许随机访问，可以只保留指向当前的指针
		mutable int current_position = 0;
		mutable BNode<ListEntry>*current = nullptr;
		//为了方便其他函数调用，返回值不为Error_code
		BNode<ListEntry>* set_position(int position)const;
	};
	//有序表
	template<typename ListEntry>
	class OrderList{
	public:
		OrderList();
		void insert(const ListEntry &item);
		~OrderList();
	private:
		//由于派生类只能访问基类的公有/受保护成员
		//如有需要，必须通过基类函数修改
		//由于该类没有遵循is-a原则，应该使用复合?
		List<ListEntry> l1;
		Node<ListEntry>* find_position(const ListEntry &item);
	};
}//namespace tsetlist
#endif
#pragma once
/*
#include "TestList.cpp"


List<int> l1;
for (int i = 0;i < 4;++i)
l1.insert(i, i);
l1.replace(2, 7);
int i = 3, item = 0;
for (int i = 0;i < 4;++i) {
l1.retrieve(i, item);
cout << item << endl;
}
l1.clear();

BList<int> l1;
for (int i = 0;i < 4;++i)
l1.insert(i, i);
l1.replace(2, 7);
int i = 3, item = 0;
l1.replace(3, item);
for (i = 0;i < 3;++i) {
l1.retrieve(i, item);
cout << item << endl;
}
l1.clear();
return 0;
*/