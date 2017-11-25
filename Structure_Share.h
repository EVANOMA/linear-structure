#ifndef STRUCTURE_H
#define STRUCTURE_H

namespace StructureShare {

	//链式节点
	template<typename NodeEntry>
	//仅当只有数据成员时使用 struct
	struct Node {
		NodeEntry entry;
		Node<NodeEntry> *next;
		Node();
		Node(NodeEntry item, Node<NodeEntry> *add_on = NULL);
	};
	//由于编译器在实例化模板时需要掌握定义
	//当模板类的定义和声明建议一起放在头文件时，在另外的.cpp文件使用时只需要include对应的.h文件
	//如果定义放在.cpp文件中，使用时需要include对应的.cpp文件
	//栈式实现
	template<typename NodeEntry>
	Node<NodeEntry>::Node() :
		next(nullptr)
	{}
	template<typename NodeEntry>
	Node<NodeEntry>::Node(NodeEntry item, Node* add_on) :
		entry(item), next(add_on)
	{}
	//由于Node和BNode的entry都是由其他的数据结构用动态内存生成的并负责销毁。
	//所以无需担心指针被销毁时没有删除分配的内存
	
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
	};

	template<typename Node_entry>
	BNode<Node_entry>::BNode() :next(nullptr), front(nullptr)
	{}
	template<typename Node_entry>
	BNode<Node_entry>::BNode(Node_entry item, BNode *q1,
		BNode *q2) :
		entry(item), front(q1), next(q2)
	{}
	//数组链表P211
}//namespace StructureShare

#endif
#pragma once
