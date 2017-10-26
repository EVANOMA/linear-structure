#include<iostream>
using namespace std;

#include "TestList.h"
namespace tsetlist {

	//��ʽ�ڵ�
	template<typename ListEntry>
	Node<ListEntry>::Node():
		next(nullptr)
	{}
	template<typename ListEntry>
	Node<ListEntry>::Node(ListEntry item, Node* add_on):
		entry(item),next(add_on)
	{}
	template<typename ListEntry>
	Node<ListEntry>::~Node()
	{}

	template<typename ListEntry>
	List< ListEntry>::List():
		List_count(0), current_position(0), current(nullptr)
	{}	
	//����������ִ��˳��͹��캯���෴
	//��ִ�к����壬Ȼ������ʽ�������׶ΰ���ʼ�����������ٳ�Ա
	//������ʽ��������ָ���Ա����ɾ����ָ����
	template<typename ListEntry>
	List< ListEntry>::~List()
	{
		clear();
	}
	template<typename ListEntry>
	void List< ListEntry>::size()const
	{
		cout <<List_count << endl;
	}
	template<typename ListEntry>
	bool List< ListEntry>::empty()const
	{
		returnBList_count == 0;
	}
	//���
	template<typename ListEntry>
	void List< ListEntry>::clear()
	{
		if (List_count == 0)return;//����Ҫreturn 0
		auto q = head;
		while (List_count) {
			head = head->next;
			delete q;
			--List_count;
			q = head;
		}
	}
	//ͨ���±��ҵ���Ӧ�Ľ��
	template<typename ListEntry>
	Node<ListEntry>* List< ListEntry>::set_position(int position)const
	{
		//���������������������ȱ�֤����Ϊ��
		if (List_count == 0) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "List is empty" << endl;
			return nullptr;
		}
		Node<ListEntry> *q ;		
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
	//ɾ��
	template<typename ListEntry>
	void List< ListEntry>::remove(int position, ListEntry &item)
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position="<< position << " ,List_count=" <<List_count << endl;
			return;
		}
		Node<ListEntry> *previous, *t_node;
		if (position > 0) {
			previous = set_position(position - 1);
			t_node = previous->next;
		}
		//ɾ��ͷ�ڵ�
		else t_node = head;

		auto following = t_node->next;
		//��Ҫɾ���Ľڵ�󲻴��ڽڵ�
		if (following == nullptr) 
			item = t_node->entry;
		else if (position == 0) {
			head = following;
			item = t_node->entry;
		}
		else {
			previous->next = following;
			item = t_node->entry;
		}
		delete t_node;
		--List_count;
	}
	//������position��ǰ��
	template<typename ListEntry>
	void List< ListEntry>::insert(int position, const ListEntry &item)
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" <<List_count << endl;
			return;
		}
		Node<ListEntry> *previous, *following;
		if (position > 0) {
			previous = set_position(position - 1);
			following = previous->next;
		}
		else//position== 0 ���뵽��1���ڵ��ǰ��
			following = head;
		//�����½ڵ�
		Node<ListEntry> *new_node = nullptr;
		try {
			//���½ڵ����ԭջ���ڵ��ǰ��
			new_node = new Node<ListEntry>(item, following);
			//��̬�ڴ����ʧ��
			//bad_allocֻ��ʹ��Ĭ�ϳ�ʼ��
			if (new_node == nullptr) throw bad_alloc();
		}
		catch (bad_alloc err) {
			cout << err.what() << endl;
		}
		if (position == 0) {
			head = new_node;
			head->next = following;
		}
		else {
			previous->next = new_node;
			new_node->next = following;
		}			
		//������Ϊ��ʱ��set_position��Ҫ�ڴ˸���������¼
		if (List_count == 0) {
			current_position = position;
			current = new_node;
		}
		++List_count;
	}
	//�滻
	template<typename ListEntry>
	void List< ListEntry>::replace(int position, const ListEntry &item)
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" <<List_count << endl;
			return;
		}
		auto now_node = set_position(position);
		now_node->entry = item;
	}
	//����
	template<typename ListEntry>
	void List< ListEntry>::retrieve(int position, ListEntry &item)const
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" <<List_count << endl;
			return;
		}
		auto now_node = set_position(position);
		item = now_node->entry;
	}
	//˫��ڵ�
	template<typename Node_entry>
	BNode<Node_entry>::BNode():next(nullptr),front(nullptr) 
	{}
	template<typename Node_entry>
	BNode<Node_entry>::BNode(Node_entry item, BNode *q1,
		BNode *q2):
		entry(item), front(q1), next(q2)
	{}
	template<typename Node_entry>
	BNode<Node_entry>::~BNode()
	{}
	//˫������
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
		cout <<BList_count << endl;
	}
	template<typename ListEntry>
	bool BList< ListEntry>::empty()const
	{
		return BList_count == 0;
	}
	//���
	//��ʱ��������
	template<typename ListEntry>
	void BList< ListEntry>::clear()
	{
		if (BList_count == 0)return;//����Ҫreturn 0
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
		//���ǵø���BList�����ݳ�Ա
		BList_count = 0;
		current_position = 0;
		current = nullptr;
	}
	//ͨ���±��ҵ���Ӧ�Ľ��
	template<typename ListEntry>
	BNode<ListEntry>* BList< ListEntry>::set_position(int position)const
	{
		//���������������������ȱ�֤����Ϊ��
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
	//ɾ��
	//�����˱�ɾ���Ľڵ�
	//set_position������Ҫ����current
	template<typename ListEntry>
	void BList< ListEntry>::remove(int position, ListEntry &item)
	{
		if (position<0 || position>List_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position <<" ,BList_count="<<BList_count<< endl;
			return;
		}
		auto t_node = set_position(position);
		auto previous = t_node->front;
		auto following= t_node->next;
		
		item = t_node->entry;
		delete t_node;
		//��Ҫɾ���Ľڵ�󲻴��ڽڵ�
		if (following == nullptr) 					
			current = previous;
		//ɾ����1���ڵ�
		if (position == 0) {
			following->front = nullptr;
			current = following;
		}
		else {
			following->front = previous;
			previous->next=following;
			current = following;
		}
		--BList_count;
	}
	//������position��ǰ��
	template<typename ListEntry>
	void BList< ListEntry>::insert(int position, const ListEntry &item)
	{
		if (position<0 || position>BList_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,BList_count=" <<BList_count << endl;
			return;
		}
		BNode<ListEntry> *previous, *following, *new_node=nullptr;
		//�����һ���ڵ�
		if (BList_count == 0) {
			try {
				//���½ڵ����ԭջ���ڵ��ǰ��
				new_node = new BNode<ListEntry>(item, nullptr, nullptr);
				//��̬�ڴ����ʧ��
				//bad_allocֻ��ʹ��Ĭ�ϳ�ʼ��
				if (new_node == nullptr) throw bad_alloc();
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}			
			//������Ϊ��ʱ��set_position��Ҫ�ڴ˸���������¼
			current_position = position;
			current = new_node;
		}			
		//���뵽��1��ǰ�� 
		else if (position == 0) {
			following = set_position(0);
			try {
				//���½ڵ����ԭջ���ڵ��ǰ��
				new_node = new BNode<ListEntry>(item, nullptr, following);
				//��̬�ڴ����ʧ��
				//bad_allocֻ��ʹ��Ĭ�ϳ�ʼ��
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
				//���½ڵ����ԭջ���ڵ��ǰ��
				new_node = new BNode<ListEntry>(item, previous, following);
				//��̬�ڴ����ʧ��
				//bad_allocֻ��ʹ��Ĭ�ϳ�ʼ��
				if (new_node == nullptr) throw bad_alloc();
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
			previous->next = new_node;
			//��ĩβ����
			if(following!=nullptr)
			   following->front= new_node;
		}	
		++BList_count;
	}
	//�滻
	template<typename ListEntry>
	void BList< ListEntry>::replace(int position, const ListEntry &item)
	{
		if (position<0 || position>BList_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,List_count=" <<BList_count << endl;
			return;
		}
		auto now_node = set_position(position);
		now_node->entry = item;
	}
	//����
	template<typename ListEntry>
	void BList< ListEntry>::retrieve(int position, ListEntry &item)const
	{
		if (position<0 || position>BList_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "range_error:position=" << position << " ,BList_count=" <<BList_count << endl;
			return;
		}
		BNode<ListEntry> *now_node = set_position(position);
		item = now_node->entry;
	}

	//�ҵ�����λ�õ�ǰ1���ڵ�
	template<typename ListEntry>
	Node<ListEntry>* OrderList<ListEntry>::find_position(const ListEntry &item)
	{
		//����Ϊ��ʱֱ�ӷ���
		if (List_count == 0) 
			return nullptr;
		Node<ListEntry>* q;
		if (item >= current->entry) {
			q = current;
			while (item > q->entry) {
				q = q->next;
				++current_position;
			}
		}			
		else {
			q = head;
			current_position = 0;
			while (item > q->entry) {
				q = q->next;
				++current_position;
			}
		}			
		current = q;
		return q;
	}
	template<typename ListEntry>
	OrderList< ListEntry>::OrderList():
		l1()
	{}
	//������position��ǰ��
	template<typename ListEntry>
	void OrderList< ListEntry>::insert(const ListEntry &item)
	{
		auto previous = find_position(item);
		decltype(previous) following = nullptr;
		if(previous!=nullptr)
		   following = previous->next;
		//�����½ڵ�
		Node<ListEntry> *new_node = nullptr;
		try {
			//���½ڵ����ԭջ���ڵ��ǰ��
			new_node = new Node<ListEntry>(item, following);
			//��̬�ڴ����ʧ��
			//bad_allocֻ��ʹ��Ĭ�ϳ�ʼ��
			if (new_node == nullptr) throw bad_alloc();
		}
		catch (bad_alloc err) {
			cout << err.what() << endl;
		}
		//������Ϊ��ʱ��set_position��Ҫ�ڴ˸���������¼
		if (previous == nullptr) 
			l1.current = new_node;
		//���뵽��1��ǰ��
		else if (l1.current_position == 0) 
			head = new_node;
		else 
			previous->next = new_node;		
		++count;
	}

}//namespace tsetlist
using namespace tsetlist;

int main() {
	OrderList<int> l1;
	
	l1.insert(4);
	
	
	/*
	l1.insert(1);
	l1.insert(2);
	l1.replace(2, 7);
	int i = 3, item = 0;
	for (int i = 0;i < 3;++i) {
		l1.retrieve(i, item);
		cout << item << endl;
	}
	l1.clear();
	*/
	
}


