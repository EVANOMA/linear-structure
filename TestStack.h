//δ����CIRCLE_H��ִ�����еĴ���
#ifndef CIRCLE_H
#define CIRCLE_H//����CIRCLE_H

namespace tsetstack {

	//������������,������, �ṹ��, ���Ͷ��� (typedef), ö��, ����ģ�����
	//�Դ�д��ĸ��ʼ, ÿ����������ĸ����д, �������»���. 

	//����ʹ��using����typedef
	using StackEntry = int;//ջ��Ԫ������

	//˳��ʵ��
	class Stack {		
	public:
		Stack();
		//ֻ�ı�count
		void pop(StackEntry &item);//���׳��ĳ�����Ȼ��ջ�У���Ҫ��top�������ʹ��
		void push(const StackEntry &item);
		//����ָ��ջ����Ԫ��
		void top(StackEntry &item)const;
		bool empty()const;
		bool full()const;
		void number()const;
		void clear();
	private:
		//�����ݳ�ԱҪ���»���
		//ÿ�������ݳ�Ա��Ӧ����ע��˵����;
		int stack_count = 0;//�洢������
		//���ھ�̬�����ĳ�ʼ������.cc�ļ�
		//������Ҫ������ʹ��
		//����ʹ��constexpr��˵����ʽ�ұ�Ϊ����
		static constexpr int stack_size=3;
		StackEntry entry[stack_size];
	};

	//��ʽ�ڵ�
	template<typename NodeEntry>
	//����ֻ�����ݳ�Աʱʹ�� struct
	struct Node {
		NodeEntry entry;
		Node<NodeEntry> *next;
		Node();
		Node(NodeEntry item, Node<NodeEntry> *add_on = NULL);
	};
	//���ڱ�������ʵ����ģ��ʱ��Ҫ���ն���
	//��ģ����Ķ������������һ�����ͷ�ļ�ʱ���������.cpp�ļ�ʹ��ʱֻ��Ҫinclude��Ӧ��.h�ļ�
	//����������.cpp�ļ��У�ʹ��ʱ��Ҫinclude��Ӧ��.cpp�ļ�
	//ջʽʵ��
	template<typename NodeEntry>
	Node<NodeEntry>::Node()
	{
		next = nullptr;
	}
	template<typename NodeEntry>
	Node<NodeEntry>::Node(NodeEntry item, Node* add_on)
	{
		entry = item;
		next = add_on;
	}
	//��ջ
	template<typename StackEntry>
	class NodeStack {
	public:
		NodeStack();
		//ֻ�ı�count
		void pop(StackEntry &item);//���׳��ĳ�����Ȼ��ջ��
		void push(const StackEntry &item);
		void clear();
		//����ָ��ջ����Ԫ��
		//Error_code top(StackEntry &item)const;
		bool empty()const;
		int number()const;
	protected:
		int stack_count = 0;//�洢������
		Node<StackEntry>* top_node=nullptr;
	};

	template<typename StackEntry>
	NodeStack<StackEntry>::NodeStack()
	{}
	template<typename StackEntry>
	bool NodeStack<StackEntry>::empty()const
	{
		return stack_count == 0;
	}
	template<typename StackEntry>
	int NodeStack<StackEntry>::number()const
	{
		return stack_count;
	}
	template<typename StackEntry>
	void NodeStack<StackEntry>::clear()
	{
		if (stack_count == 0) return;
		while (stack_count) {
			auto old_top = top_node;
			top_node = old_top->next;
			delete old_top;
			--stack_count;
		}
	}
	template<typename StackEntry>
	void NodeStack<StackEntry>::push(const StackEntry &item)
	{
		Node<StackEntry> *new_top = nullptr;
		try {
			//���½ڵ����ԭջ���ڵ��ǰ��
			new_top = new Node<StackEntry>(item, top_node);
			//��̬�ڴ����ʧ��
			//bad_allocֻ��ʹ��Ĭ�ϳ�ʼ��
			if (new_top == nullptr) throw bad_alloc();
			//throw��������������return������
			//��������ִ����catch�����˳��ú���
		}
		catch (bad_alloc err) {
			cout << err.what() << endl;
		}
		//�����û������Ĵ���ͺ�����������������
		//ʹtop_nodeָ���µ�ջ���ڵ�
		top_node = new_top;
		++stack_count;
	}
	template<typename StackEntry>
	void NodeStack<StackEntry>::pop(StackEntry &item)
	{
		if (top_node == nullptr) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "stack underflow" << endl;
			return;
		}
		auto old_top = top_node;
		//ָ��ջ������һ���ڵ�
		item = old_top->entry;
		top_node = old_top->next;
		delete old_top;
		--stack_count;
	}


}//namespace tsetstack

/*

*/
#endif
#pragma once
