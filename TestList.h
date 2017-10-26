#ifndef CIRCLE_H
#define CIRCLE_H


namespace tsetlist {
	
	//��ʽ�ڵ�
	template<typename ListEntry>
	struct Node {
		ListEntry entry;
		Node<ListEntry> *next;
		//ͨ���±��ҵ���Ӧ�Ľ��
		Node();
		Node(ListEntry item, Node<ListEntry> *add_on = NULL);
		~Node();
	};
	
	//����
	template<typename ListEntry>
	class List {
	public:
		List();		
		~List();
		//����
		bool empty()const;
		void size()const;
		void retrieve(int position, ListEntry &item)const;
		//�޸�
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
		/*�����ϴβ��ҵ�λ�ã��������λ��������Ԫ�ؿ��Լ��ٷ���ʱ�䡣*/
		mutable int current_position=0;
		mutable Node<ListEntry>*current=nullptr;
		//Ϊ�˷��������������ã�����ֵΪNode<ListEntry>*
		//�ú������ܴ����쳣
		Node<ListEntry>* set_position(int position)const;
	};
	//˫��ڵ�
	template<typename Node_entry>
	struct BNode {
		Node_entry entry;
		//�������е�ָ�����ڴ�����ռ�Ĵ�С��ͬ��Ϊ�˱���ѭ�����壬C++�����ڶ�������ǰʹ������ָ��
		BNode<Node_entry> *next;
		BNode<Node_entry> *front;
		BNode();
		BNode(Node_entry item, BNode<Node_entry> *q1 = nullptr,
			BNode<Node_entry> *q2 = nullptr);
		~BNode();
	};
	//˫������
	template<typename ListEntry>
	class BList {
	public:
		BList();
		~BList();
		//����
		bool empty()const;
		void size()const;
		void retrieve(int position, ListEntry &item)const;
		//�޸�
		void clear();

		void insert(int position, const ListEntry &item);
		void replace(int position, const ListEntry &item);
		void remove(int position, ListEntry &item);

		//Error_code traverse(void(*visit)(ListEntry&));		
		//List(const List<ListEntry>&copy);
		//void operator=(const List<ListEntry>&copy);
	private:
		int BList_count = 0;
		//��������������ʣ�����ֻ����ָ��ǰ��ָ��
		mutable int current_position = 0;
		mutable BNode<ListEntry>*current = nullptr;
		//Ϊ�˷��������������ã�����ֵ��ΪError_code
		BNode<ListEntry>* set_position(int position)const;
	};
	//�����
	template<typename ListEntry>
	class OrderList{
	public:
		OrderList();
		void insert(const ListEntry &item);
		~OrderList();
	private:
		//����������ֻ�ܷ��ʻ���Ĺ���/�ܱ�����Ա
		//������Ҫ������ͨ�����ຯ���޸�
		//���ڸ���û����ѭis-aԭ��Ӧ��ʹ�ø���?
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