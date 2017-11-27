//未定义CIRCLE_H则执行其中的代码
#ifndef EIGHTQUEEN_H
#define EIGHTQUEEN_H//定义CIRCLE_H
//一般不将头文件放入命名空间内部
//一旦这样做意味着把头文件的内容定义在命名空间内
#include "D:/code/test1/test1/TestStack.h"

namespace eightqueen {

	//坐标
	struct coordinate {
		int x;//横坐标
		int y;//纵坐标
			  //编译器只有在没有任何构造函数的情况下才会合成默认构造函数
		coordinate();
		coordinate(int i, int j = 0);
		//无论是否定义拷贝构造函数编译器都会合成默认拷贝构造函数
		//用于实参传递给参数列表和返回类型
	};
	using tsetstack::NodeStack;
	//支持遍历的栈
	template<typename StackEntry>
	class ProStack : public NodeStack<StackEntry> {
	public:
		using NodeStack::NodeStack;
		void read(int i, StackEntry &item)const;
	};

	class Queen {
		friend bool find(Queen& q, int x = 1, int y = 0);
	public:
		Queen(int a, int b);
		void put(coordinate& c);
		void out(coordinate& c);
		void clear();
		bool check(coordinate& c1)const;
		void count()const;
	private:
		int queen_longth;//长度
		int queen_width;//宽度
		int queen_count = 0;//记录符合条件的答案个数
		ProStack<coordinate> queen_stack;
	};
}//namespace eightqueen	

#endif
#pragma once
