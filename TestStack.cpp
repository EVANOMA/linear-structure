#include<iostream>
using namespace std;

#include "TestStack.h"

namespace tsetstack {
	
	//˳��ʵ��
	constexpr int Stack::stack_size;

	Stack::Stack()
	{
		for (int i = 0;i < 2;++i)
			push(i);
	}
	void Stack::push(const StackEntry &item)
	{
		if (stack_count >= stack_size) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "stack overflow" << endl;
			return;
		}			
		entry[stack_count++] = item;
	}

	void Stack::pop(StackEntry &item)
	{
		if (stack_count == 0) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "stack underflow" << endl;
			return;
		}  
		item = entry[--stack_count];
	}

	void Stack::top(StackEntry &item)const
	{
		if (stack_count == 0) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "stack underflow" << endl;
			return;
		}
		item = entry[stack_count];
	}
	bool Stack::empty()const
	{
		return stack_count == 0;
	}
	bool Stack::full()const
	{
		return stack_count == stack_size;
	}
	void Stack::number()const
	{
		cout << stack_count << endl;
	}
	//���ڶ�ջ�Ĳ��������ж�stack_count
	//�������轫����Ԫ�ع���
	void Stack::clear()
	{
		stack_count = 0;
	}
	
}//namespace tsetstack






