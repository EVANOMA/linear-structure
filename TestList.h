#ifndef TESTLIST_H
#define TESTLIST_H

#include "D:/code/test1/test1/Structure_Share.h"

namespace testlist {
	
	using StructureShare::Node;
	using StructureShare::BNode;

	//链表
	template<typename ListEntry>
	class List {
	public:
		List();		
		virtual ~List();
		List(List<ListEntry>&);
		//访问
		bool empty()const;
		int size()const;
		void retrieve(int position, ListEntry &item)const;
		//修改
		void clear();		
		void insert(int position, const ListEntry &item);
		void replace(int position, const ListEntry &item);
		void remove(int position);
		
		//void traverse(void(*visit)(ListEntry&));		
		//void operator=(const List<ListEntry>&copy);
	protected:
		int List_count=0;
		Node<ListEntry> *head = nullptr;
		/*保存上次查找的位置，如果访问位于其后面的元素可以减少访问时间。*/
		mutable int current_position=0;
		mutable Node<ListEntry> *current=nullptr;
		//为了方便其他函数调用，返回值为Node<ListEntry>*
		//该函数不能处理异常
		Node<ListEntry>* set_position(int position)const;
	};
	
	template<typename ListEntry>
	List< ListEntry>::List() :
		List_count(0), current_position(0), current(nullptr)
	{}
	//析构函数的执行顺序和构造函数相反
	//先执行函数体，然后在隐式的析构阶段按初始化的逆序销毁成员
	//由于隐式销毁内置指针成员不会删除所指对象
	template<typename ListEntry>
	List< ListEntry>::~List()
	{
		clear();
	}
	template<typename ListEntry>
	List<ListEntry>::List(List<ListEntry>& copy)
	{
		List_count = copy.List_count;
		current_position = 0;
		if (List_count == 0) {
			head = nullptr;
			current = nullptr;
			return;
		}
		auto old_node = copy.head;
		head = new Node<ListEntry>(old_node->entry);
		auto new_node = head;
		//为了方便图的遍历
		current = head;
		while (old_node->next) {
			try {
				old_node = old_node->next;
				new_node->next = new Node<ListEntry>(old_node->entry);
				if (new_node == nullptr) throw bad_alloc();
				new_node = new_node->next;
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
		}
	}
	template<typename ListEntry>
	int List< ListEntry>::size()const
	{
		return List_count;
	}
	template<typename ListEntry>
	bool List< ListEntry>::empty()const
	{
		return List_count == 0;
	}
	//清空
	template<typename ListEntry>
	void List< ListEntry>::clear()
	{
		if (List_count == 0)return;//不需要return 0
		auto q = head;
		while (List_count) {
			head = head->next;
			delete q;
			--List_count;
			q = head;
		}
	}
	//通过下标找到对应的结点
	template<typename ListEntry>
	Node<ListEntry>* List< ListEntry>::set_position(int position)const
	{
		//除插入外其他操作必须先保证链表不为空
		if (List_count == 0) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "List is empty" << endl;
			return nullptr;
		}
		Node<ListEntry> *q;
		if (position >= current_position) {
			q = current;
			for (int i = current_position;i < position;++i)
				q = q->next;
		}
		else {
			q = head;
			for (int i = 0;i < position;++i)
				q = q->next;
		}
		current_position = position;
		current = q;
		return q;
	}
	//删除
	template<typename ListEntry>
	void List< ListEntry>::remove(int position)
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" << List_count << endl;
			return;
		}
		Node<ListEntry> *previous, *t_node;
		if (position > 0) {
			previous = set_position(position - 1);
			t_node = previous->next;
		}
		//删除头节点
		else t_node = head;

		auto following = t_node->next;
		if (position == 0)
			head = following;
		//需要删除的节点后存在节点
		else if (following != nullptr)
			previous->next = following;
		delete t_node;
		--List_count;
	}
	//插入在position的前面
	template<typename ListEntry>
	void List<ListEntry>::insert(int position, const ListEntry &item)
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" << List_count << endl;
			return;
		}
		Node<ListEntry> *previous, *following;
		if (position > 0) {
			previous = set_position(position - 1);
			following = previous->next;
		}
		else//position== 0 插入到第1个节点的前面
			following = head;
		//创建新节点
		Node<ListEntry> *new_node = nullptr;
		try {
			//将新节点放在原栈顶节点的前面
			new_node = new Node<ListEntry>(item, following);
			//动态内存分配失败
			//bad_alloc只能使用默认初始化
			if (new_node == nullptr) throw bad_alloc();
		}
		catch (bad_alloc err) {
			cout << err.what() << endl;
		}
		if (position == 0) {
			head = new_node;
			head->next = following;
			//在链表为空时或者插入到头节点前面时，
			//set_position需要在此更新搜索记录
			current_position = position;
			current = new_node;
		}
		else {
			previous->next = new_node;
			new_node->next = following;
		}
		++List_count;
	}
	//替换
	template<typename ListEntry>
	void List< ListEntry>::replace(int position, const ListEntry &item)
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" << List_count << endl;
			return;
		}
		auto now_node = set_position(position);
		now_node->entry = item;
	}
	//访问
	template<typename ListEntry>
	void List< ListEntry>::retrieve(int position, ListEntry &item)const
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" << List_count << endl;
			return;
		}
		auto now_node = set_position(position);
		item = now_node->entry;
	}

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

	template<typename ListEntry>
	BList< ListEntry>::BList()
	{}
	template<typename ListEntry>
	BList< ListEntry>::~BList()
	{
		clear();
	}
	template<typename ListEntry>
	void BList< ListEntry>::size()const
	{
		cout << BList_count << endl;
	}
	template<typename ListEntry>
	bool BList< ListEntry>::empty()const
	{
		return BList_count == 0;
	}
	//清空
	//有时好像会出错
	template<typename ListEntry>
	void BList< ListEntry>::clear()
	{
		if (BList_count == 0)return;//不需要return 0
		BNode<ListEntry> *q1 = current;
		BNode<ListEntry> *q2 = current->front;
		BNode<ListEntry> *q3 = q2;
		while (q1) {
			current = current->next;
			delete q1;
			q1 = current;
		}
		while (q3) {
			q2 = q2->front;
			delete q3;
			q3 = q2;
		}
		//最后记得更新BList的数据成员
		BList_count = 0;
		current_position = 0;
		current = nullptr;
	}
	//通过下标找到对应的结点
	template<typename ListEntry>
	BNode<ListEntry>* BList< ListEntry>::set_position(int position)const
	{
		//除插入外其他操作必须先保证链表不为空
		if (BList_count == 0) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "List is empty" << endl;
			return nullptr;
		}
		BNode<ListEntry> *q = current;
		if (position >= current_position) {
			for (int i = current_position;i < position;++i)
				q = q->next;
		}
		else {
			for (int i = current_position;i > position;--i)
				q = q->front;
		}
		current_position = position;
		current = q;
		return q;
	}
	//删除
	//保存了被删除的节点
	//set_position函数需要更新current
	template<typename ListEntry>
	void BList< ListEntry>::remove(int position, ListEntry &item)
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,BList_count=" << BList_count << endl;
			return;
		}
		auto t_node = set_position(position);
		auto previous = t_node->front;
		auto following = t_node->next;

		item = t_node->entry;
		delete t_node;
		//需要删除的节点后不存在节点
		if (following == nullptr)
			current = previous;
		//删除第1个节点
		if (position == 0) {
			following->front = nullptr;
			current = following;
		}
		else {
			following->front = previous;
			previous->next = following;
			current = following;
		}
		--BList_count;
	}
	//插入在position的前面
	template<typename ListEntry>
	void BList< ListEntry>::insert(int position, const ListEntry &item)
	{
		if (position<0 || position>BList_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,BList_count=" << BList_count << endl;
			return;
		}
		BNode<ListEntry> *previous, *following, *new_node = nullptr;
		//插入第一个节点
		if (BList_count == 0) {
			try {
				//将新节点放在原栈顶节点的前面
				new_node = new BNode<ListEntry>(item, nullptr, nullptr);
				//动态内存分配失败
				//bad_alloc只能使用默认初始化
				if (new_node == nullptr) throw bad_alloc();
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
			//在链表为空时，set_position需要在此更新搜索记录
			current_position = position;
			current = new_node;
		}
		//插入到第1个前面 
		else if (position == 0) {
			following = set_position(0);
			try {
				//将新节点放在原栈顶节点的前面
				new_node = new BNode<ListEntry>(item, nullptr, following);
				//动态内存分配失败
				//bad_alloc只能使用默认初始化
				if (new_node == nullptr) throw bad_alloc();
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
			following->front = new_node;
		}
		else {
			previous = set_position(position - 1);
			following = previous->next;
			try {
				//将新节点放在原栈顶节点的前面
				new_node = new BNode<ListEntry>(item, previous, following);
				//动态内存分配失败
				//bad_alloc只能使用默认初始化
				if (new_node == nullptr) throw bad_alloc();
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
			previous->next = new_node;
			//在末尾插入
			if (following != nullptr)
				following->front = new_node;
		}
		++BList_count;
	}
	//替换
	template<typename ListEntry>
	void BList< ListEntry>::replace(int position, const ListEntry &item)
	{
		if (position<0 || position>BList_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" << BList_count << endl;
			return;
		}
		auto now_node = set_position(position);
		now_node->entry = item;
	}
	//访问
	template<typename ListEntry>
	void BList< ListEntry>::retrieve(int position, ListEntry &item)const
	{
		if (position<0 || position>BList_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,BList_count=" << BList_count << endl;
			return;
		}
		BNode<ListEntry> *now_node = set_position(position);
		item = now_node->entry;
	}
	
}//namespace testlist
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