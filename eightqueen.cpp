#include<iostream>
using namespace std;

#include "eightqueen.h"

namespace eightqueen {

	//在类外使用default不为内联
	coordinate::coordinate() = default;
	//在定义时不需要显示默认实参
	coordinate::coordinate(int i, int j) :
		x(i), y(j)
	{}

	template<typename StackEntry>
	void ProStack<StackEntry>::read(int i, StackEntry &item)const
	{
		if (i >stack_count) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "stack overflow:i=" << i << ", stack_count=" << stack_count << endl;
			return;
		}
		else {
			auto head = top_node;
			i = stack_count - i;
			while (i) {
				head = head->next;
				--i;
			}
			item = head->entry;
		}
	}

	Queen::Queen(int a, int b) :
		queen_longth(a), queen_width(b), queen_stack()
	{}
	void Queen::put(coordinate& c)
	{
		queen_stack.push(c);
	}
	void Queen::out(coordinate& c)
	{
		queen_stack.pop(c);
	}
	void Queen::count()const
	{
		cout << queen_count << endl;
	}
	void Queen::clear()
	{
		queen_stack.clear();
	}
	bool Queen::check(coordinate& c1)const
	{
		int number = queen_stack.number();
		coordinate c2;
		//从栈顶向下读取
		for (int i = number;i > 0;--i) {
			//如果read函数没有声明为const，编译器会认为在该const函数中会改变类的成员
			queen_stack.read(i, c2);
			//不能平行x轴或y轴
			if (c1.x == c2.x || c1.y == c2.y
				//不能在对角线上
				//k=1,b=c2.y-c2.x				
				|| c1.y == c1.x + c2.y - c2.x
				//k=-1,b=c2.y+c2.x
				|| c1.y == c2.y + c2.x - c1.x)
				return false;
		}
		return true;
	}
	//深度优先
	//将返回值设为布尔方便信息传递和减少递归的深度
	//从第二列开始检查
	bool find(Queen& q, int x, int y)
	{
		coordinate c1;
		//全部存储完毕则退出递归
		if (x == q.queen_longth) {
			++q.queen_count;//说明增加了1种放置的方法
							//每获得1个答案就输出
			cout << "plan " << q.queen_count << ":" << endl;
			for (int i = q.queen_longth;i > 0;--i) {
				q.queen_stack.read(i, c1);
				cout << c1.x << "," << c1.y << endl;
			}
			cout << "finish" << endl;
			return true;
		}
		bool condition = false;
		for (int j = 0;j < q.queen_width;++j) {
			coordinate c1(x, j);
			if (q.check(c1)) {
				q.put(c1);
				//返回后继续遍历该列的剩余节点
				if (find(q, x + 1))
					condition = true;
				//无论对错都删除原先此层被加入的节点
				//继续遍历该列之后的节点
				q.out(c1);
			}
		}
		if (condition == false)
			return false;
		else
			return true;
	}
}//namespace eightqueen	


/*


*/
