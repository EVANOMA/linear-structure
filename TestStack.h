//未定义TESTSTACK_H则执行其中的代码
#ifndef TESTSTACK_H
#define TESTSTACK_H//定义TESTSTACK_H

#include "D:/code/test1/test1/Structure_Share.h"
namespace tsetstack {

	//所有类型命名,例如类, 结构体, 类型定义 (typedef), 枚举, 类型模板参数
	//以大写字母开始, 每个单词首字母均大写, 不包含下划线. 

	//尽量使用using代替typedef
	using StackEntry = int;//栈的元素类型
	using StructureShare::Node;

	//顺序实现
	class Stack {		
	public:
		Stack();
		//只改变count
		void pop(StackEntry &item);//被抛出的程序依然在栈中，需要和top函数结合使用
		void push(const StackEntry &item);
		//返回指向栈顶的元素
		void top(StackEntry &item)const;
		bool empty()const;
		bool full()const;
		void number()const;
		void clear();
	private:
		//类数据成员要接下划线
		//每个类数据成员都应该用注释说明用途
		int stack_count = 0;//存储的数量
		//由于静态变量的初始化放在.cc文件
		//但是需要在类内使用
		//所以使用constexpr来说明等式右边为常量
		static constexpr int stack_size=3;
		StackEntry entry[stack_size];
	};
	
	//链栈
	template<typename StackEntry>
	class NodeStack {
	public:
		NodeStack();
		//只改变count
		void pop(StackEntry &item);//被抛出的程序依然在栈中
		void push(const StackEntry &item);
		void clear();
		//返回指向栈顶的元素
		//Error_code top(StackEntry &item)const;
		bool empty()const;
		int number()const;
	protected:
		int stack_count = 0;//存储的数量
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
			//将新节点放在原栈顶节点的前面
			new_top = new Node<StackEntry>(item, top_node);
			//动态内存分配失败
			//bad_alloc只能使用默认初始化
			if (new_top == nullptr) throw bad_alloc();
			//throw语句的作用类似于return的作用
			//编译器将执行完catch语句后退出该函数
		}
		catch (bad_alloc err) {
			cout << err.what() << endl;
		}
		//将与用户交互的代码和函数的其他操作分离
		//使top_node指向新的栈顶节点
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
		//指向栈顶的下一个节点
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
