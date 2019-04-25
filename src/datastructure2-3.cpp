//============================================================================
// Name        : datastructure2-3.cpp
// Author      : Hyunju Kim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>//����3��
#include <fstream>
#include <cstdlib>
using namespace std;

bool isOpen(char ch);//���°�ȣ Ȯ���ϴ� �Լ�
bool isClosed(char ch);//�ݴ°�ȣ Ȯ���ϴ� �Լ�
bool matches(char ch, char openSymbol);//ch�Է�
void errorcheck(bool, char ch, char, int position, int line_num);//���� Ȯ�� �� ����ϴ� �Լ�


typedef char ItemType;
const int MAX_STACK_SIZE=100;       // ������ �ִ� ũ�� ����


class Stack
{
	int top;                       // ���ÿ��� ���� ���� �ִ� ����� �迭��ġ
    ItemType data[MAX_STACK_SIZE]; // ��Ҹ� �����ϴ� �迭

public:
    Stack();		               // ���� ������
    ~Stack();                  	   // ���� �Ҹ���
    bool isEmpty();				   // ����ִ��� Ȯ���ϴ� �Լ�
    bool isFull();				   // �� ���ִ��� Ȯ���ϴ� �Լ�
    void push(char ch);            // ���ÿ� ��� ����
    ItemType pop(); 	           // ���� �ֱٿ� ���ÿ� ���Ե� ��Ҹ� �����ϰ� ��ȯ
    ItemType peek(); 	           // ���� �ֱٿ� ���ÿ� ���Ե� ��Ҹ� ��ȯ
};


inline void error(char const *message)//���ڿ� �޾Ƽ� ���
{
	cout<< message <<endl;
	exit(1);
}


Stack::Stack(){ top=-1;}//���� ������
Stack::~Stack(){}//���� �Ҹ���

bool Stack:: isEmpty()//������� Ȯ���ϴ� �Լ�
{

	return top == -1;//��������� -1��ȯ
}

bool Stack::isFull()//�� ���ִ��� Ȯ��
{
	return top == MAX_STACK_SIZE-1;//�� ���ֱ� ������ ��ü �迭ũ��-1
}

void Stack::push(char ch)//ch�� stack�� �Է�
{
	if(isFull())//�� ��������
	{
		error("���� Full");
	}
	//data[top++]=e;�� ���� �ǹ�
	else//���������Ƿ�
	{
		top++;//top�� ������Ŵ
		data[top]=ch;//ch���� data[top]�� �ֱ�
	}
}


ItemType Stack::pop()
{
	if(isEmpty())
	{
		error("���� Empty");
	}
	return data[top--];//�ϳ� �������Ƿ� top 1����
}

ItemType Stack::peek()
{
	if(isEmpty())
	{
		error("���� Empty");
	}
	return data[top];//���� top�� ���� ���� ��ȯ
}



int main()
{
	char ch;//���� ��ȣ
	int line_num=1, position=0;//���� �� 1���� ����, ��ġ 0���� ����
	Stack stack;//Ŭ���� ����
	bool balanced = true;//������ ��������� balanced
	char openSymbol;//���ʰ�ȣ �ǹ�
	int p=0, l=0;//�迭 �ε���, �ʱ�ȭ
	char pl[50][55]={'\0'};//�迭 �ʱ�ȭ
	int i, j, c1=0, c2=0;//�ݺ��� ���ư� ����, üũ�ϴ� c1, c2

	//���� filename���� ���� �Է�, �����̿��Դ� cin.get����

	while(cin.get(ch) && balanced)//cin.get(ch)�Է�
	{
		position++;//�Է��� �����ڸ��� ��ġ�� ����

		if(ch=='\n')//���Ͱ� ������
		{
			line_num++, l++;//�ټ� �߰�, �迭�� �� l�� �߰�
			position=0, p=0;//position�� p�� �ʱ�ȭ
		}

		if (isOpen(ch))//���°�ȣ�� ��
		{
			stack.push(ch);//���ÿ� ����
			 p=position, l=line_num;//position�� line_num ���� p�� l�� �ֱ�

			pl[l][p]=ch;//ch�� pl[l][p]�� �ֱ�
		}

		else if(isClosed(ch))//�ݴ� ��ȣ�� ��
		{
			if(stack.isEmpty())//����ִ��� Ȯ��, ���� ����ִٸ�, ���� ��ȣ�� ���� ���̹Ƿ� error 1 �Ǵ� 2 �Ǵ� 3���� �ش�
			{
				openSymbol=0;//openSymbol�� �ʱ�ȭ
				balanced=false;//¦�� ���� �ʴ�

				if(!balanced)//¦�� ���� �ʴٸ�
				{
					errorcheck(balanced, ch, openSymbol, position, line_num);//errorcheck�Լ� ����
				}
				break;
			}

			else//������� �ʰ� ����ִٸ�
			{
				openSymbol=stack.pop();//������ pop�� char�� openSymbol�� �ֱ�(���ʰ�ȣ)
				balanced=matches(ch, openSymbol);//ch�� openSymbol(���ʰ�ȣ)�� ¦�� ������ Ȯ��, ������ 1, �ٸ��� -1

				if(balanced)//¦�� �´ٸ�
				{
					for(i=l; i>0; i--)//������μ����� �ݺ��� ������ ���μ� �������ֱ�
					{
						if(c1==1)//���� �ֱٿ� �Է¹��� ���°�ȣ�� �ʱ�ȭ�ϰ� for�� �ݺ��� ���������� ���� ����
						{
							break;//�� �� Ȯ�� �Ʊ� ������ �ݺ��� Ż��
						}

						for(j=55; j>0; j--)
						{
							if(pl[i][j]==openSymbol)//pl[i][j]�� openSymbol�� ������
							{
								pl[i][j]='\0',	c1=1;//p[i][j]=null�� �ʱ�ȭ, c1=1�� ����
								break;
							}
						}
					}
				}

				else if(!balanced)//������� �ʰ� ���ִµ� balance�� ���� �ʴٸ�
				{
					errorcheck(balanced, ch, openSymbol, position, line_num);//���� ��ȣ üũ
				}
			}
		}
		c1=0;//�ٽ� ch�Է¹޾Ƽ� while�� �� ���̱� ������ 0���� �ʱ�ȭ
	}

	if(stack.isEmpty() && balanced)//������ �� ����������� ¦�� �� �´ٴ� ��
	{
		cout<<"1"<<endl;//�� �����ϱ� 1 ���
	}

	else if(!balanced){ }//������ ������ ������ pass

	else if(!stack.isEmpty())//������ ������� ������
	{
		openSymbol=stack.pop();//openSymbol�� stack�� �ִ� �� pop�� �ؼ� ����

		for(i=l; i>0; i--)
		{
			if(c2==1)//cout�ϰ� ���� �ٽ� ����ã�Ƽ� �ݺ��� ���� �ʵ��� ����
			{
				break;
			}

			for(j=55; j>0; j--)
			{
				if(pl[i][j]=='(' && pl[i][j]==openSymbol)
				{
					cout<<"error 4: ( at position " << j << " in line " << i;
					c2=1;
					break;
				}

				else if(pl[i][j]=='{' && pl[i][j]==openSymbol)
				{
					cout<<"error 5: { at position " << j << " in line " << i;
					c2=1;
					break;
				}

				else if(pl[i][j]=='[' && pl[i][j]==openSymbol)
				{
					cout<<"error 6: [ at position " << j << " in line " << i;
					c2=1;
					break;
				}
			}
		}
	}

	else
	{
		errorcheck(balanced, ch, openSymbol, position, line_num);
	}

	return 0;
}



bool isOpen(char ch)//���� ��ȣ�� ������ ��
{
	if((ch =='(') || (ch =='{') || (ch == '['))
	{
		return true;//������ ��
	}

	else
	{
		return false;//�ƴϸ� ����
	}
}

bool isClosed(char ch)//�ݴ� ��ȣ�� ������ ��
{
	if((ch == ')') || (ch == '}') ||(ch == ']'))
	{
		return true;//�̰� �� �ϳ��� ����
	}

	else
	{
		return false;//�ƴϸ� ����
	}
}

bool matches(char ch, char openSymbol)//¦�� �´��� Ȯ���ϱ�
{
	if(((openSymbol == '(') && ch == ')') || ((openSymbol == '{') && ch == '}') || ((openSymbol == '[') && ch == ']'))
	{
		return true;
	}

	else
	{
		return false;
	}
}

void errorcheck(bool balanced, char ch, char openSymbol, int position, int line_num)
{//ch�� openSymbol�� ���ؼ� error 1, �Ǵ� 2, �Ǵ� 3 ��ȣ ����ϱ�
	if((ch == ')') && (openSymbol != '('))
	{
		cout << "error 1: ) at position " << position << " in line " << line_num;
	}

	else if((ch == '}') && (openSymbol != '{'))
	{
		cout << "error 2: } at position " << position << " in line " << line_num;
	}

	else if((ch == ']') && (openSymbol != '['))
	{
		cout<<"error 3: ] at position " << position << " in line " << line_num;
	}
}
