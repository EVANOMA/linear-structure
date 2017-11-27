#include<iostream>
using namespace std;

#include "eightqueen.h"

namespace eightqueen {

	//������ʹ��default��Ϊ����
	coordinate::coordinate() = default;
	//�ڶ���ʱ����Ҫ��ʾĬ��ʵ��
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
		//��ջ�����¶�ȡ
		for (int i = number;i > 0;--i) {
			//���read����û������Ϊconst������������Ϊ�ڸ�const�����л�ı���ĳ�Ա
			queen_stack.read(i, c2);
			//����ƽ��x���y��
			if (c1.x == c2.x || c1.y == c2.y
				//�����ڶԽ�����
				//k=1,b=c2.y-c2.x				
				|| c1.y == c1.x + c2.y - c2.x
				//k=-1,b=c2.y+c2.x
				|| c1.y == c2.y + c2.x - c1.x)
				return false;
		}
		return true;
	}
	//�������
	//������ֵ��Ϊ����������Ϣ���ݺͼ��ٵݹ�����
	//�ӵڶ��п�ʼ���
	bool find(Queen& q, int x, int y)
	{
		coordinate c1;
		//ȫ���洢������˳��ݹ�
		if (x == q.queen_longth) {
			++q.queen_count;//˵��������1�ַ��õķ���
							//ÿ���1���𰸾����
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
				//���غ�����������е�ʣ��ڵ�
				if (find(q, x + 1))
					condition = true;
				//���۶Դ�ɾ��ԭ�ȴ˲㱻����Ľڵ�
				//������������֮��Ľڵ�
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
