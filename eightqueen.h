//δ����CIRCLE_H��ִ�����еĴ���
#ifndef EIGHTQUEEN_H
#define EIGHTQUEEN_H//����CIRCLE_H

#include "D:/code/test1/test1/TestStack.h"

	namespace eightqueen {
		//����
		struct coordinate {
			int x;//������
			int y;//������
				  //������ֻ����û���κι��캯��������²Ż�ϳ�Ĭ�Ϲ��캯��
			coordinate();
			coordinate(int i, int j = 0);
			//�����Ƿ��忽�����캯������������ϳ�Ĭ�Ͽ������캯��
			//����ʵ�δ��ݸ������б�ͷ�������
			coordinate& operator =(const coordinate&);
		};
		using tsetstack::NodeStack;
		//֧�ֱ�����ջ
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
			int queen_longth;//����
			int queen_width;//���
			int queen_count = 0;//��¼���������Ĵ𰸸���
			ProStack<coordinate> queen_stack;
		};
	}//namespace eightqueen

#endif
#pragma once
