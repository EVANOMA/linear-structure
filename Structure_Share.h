#ifndef STRUCTURE_H
#define STRUCTURE_H

namespace StructureShare {

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
	Node<NodeEntry>::Node() :
		next(nullptr)
	{}
	template<typename NodeEntry>
	Node<NodeEntry>::Node(NodeEntry item, Node* add_on) :
		entry(item), next(add_on)
	{}
	//����Node��BNode��entry���������������ݽṹ�ö�̬�ڴ����ɵĲ��������١�
	//�������赣��ָ�뱻����ʱû��ɾ��������ڴ�
	
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
	};

	template<typename Node_entry>
	BNode<Node_entry>::BNode() :next(nullptr), front(nullptr)
	{}
	template<typename Node_entry>
	BNode<Node_entry>::BNode(Node_entry item, BNode *q1,
		BNode *q2) :
		entry(item), front(q1), next(q2)
	{}
	//��������P211
}//namespace StructureShare

#endif
#pragma once
