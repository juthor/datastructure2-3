//============================================================================
// Name        : datastructure2-3.cpp
// Author      : Hyunju Kim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>//문제3번
#include <fstream>
#include <cstdlib>
using namespace std;

bool isOpen(char ch);//오픈괄호 확인하는 함수
bool isClosed(char ch);//닫는괄호 확인하는 함수
bool matches(char ch, char openSymbol);//ch입력
void errorcheck(bool, char ch, char, int position, int line_num);//에러 확인 및 출력하는 함수


typedef char ItemType;
const int MAX_STACK_SIZE=100;       // 스택의 최대 크기 설정


class Stack
{
	int top;                       // 스택에서 가장 위에 있는 요소의 배열위치
    ItemType data[MAX_STACK_SIZE]; // 요소를 저장하는 배열

public:
    Stack();		               // 스택 생성자
    ~Stack();                  	   // 스택 소멸자
    bool isEmpty();				   // 비어있는지 확인하는 함수
    bool isFull();				   // 다 차있는지 확인하는 함수
    void push(char ch);            // 스택에 요소 삽입
    ItemType pop(); 	           // 가장 최근에 스택에 삽입된 요소를 삭제하고 반환
    ItemType peek(); 	           // 가장 최근에 스택에 삽입된 요소를 반환
};


inline void error(char const *message)//문자열 받아서 출력
{
	cout<< message <<endl;
	exit(1);
}


Stack::Stack(){ top=-1;}//스택 생성자
Stack::~Stack(){}//스택 소멸자

bool Stack:: isEmpty()//비었는지 확인하는 함수
{

	return top == -1;//비어있으면 -1반환
}

bool Stack::isFull()//다 차있는지 확인
{
	return top == MAX_STACK_SIZE-1;//다 차있기 때문에 전체 배열크기-1
}

void Stack::push(char ch)//ch을 stack에 입력
{
	if(isFull())//다 차있으면
	{
		error("스택 Full");
	}
	//data[top++]=e;랑 같은 의미
	else//안차있으므로
	{
		top++;//top을 증가시킴
		data[top]=ch;//ch값을 data[top]에 넣기
	}
}


ItemType Stack::pop()
{
	if(isEmpty())
	{
		error("스택 Empty");
	}
	return data[top--];//하나 지웠으므로 top 1감소
}

ItemType Stack::peek()
{
	if(isEmpty())
	{
		error("스택 Empty");
	}
	return data[top];//현재 top이 가진 값을 반환
}



int main()
{
	char ch;//넣을 괄호
	int line_num=1, position=0;//라인 수 1부터 시작, 위치 0부터 시작
	Stack stack;//클래스 선언
	bool balanced = true;//스택이 비어있으면 balanced
	char openSymbol;//왼쪽괄호 의미
	int p=0, l=0;//배열 인덱스, 초기화
	char pl[50][55]={'\0'};//배열 초기화
	int i, j, c1=0, c2=0;//반복문 돌아갈 변수, 체크하는 c1, c2

	//파일 filename으로 부터 입력, 구름이에게는 cin.get으로

	while(cin.get(ch) && balanced)//cin.get(ch)입력
	{
		position++;//입력이 들어오자마자 위치값 증가

		if(ch=='\n')//엔터가 들어오면
		{
			line_num++, l++;//줄수 추가, 배열에 들어갈 l값 추가
			position=0, p=0;//position와 p값 초기화
		}

		if (isOpen(ch))//여는괄호일 때
		{
			stack.push(ch);//스택에 저장
			 p=position, l=line_num;//position와 line_num 각각 p와 l에 넣기

			pl[l][p]=ch;//ch를 pl[l][p]에 넣기
		}

		else if(isClosed(ch))//닫는 괄호일 때
		{
			if(stack.isEmpty())//비어있는지 확인, 만약 비어있다면, 왼쪽 괄호가 없는 것이므로 error 1 또는 2 또는 3번에 해당
			{
				openSymbol=0;//openSymbol값 초기화
				balanced=false;//짝이 맞지 않다

				if(!balanced)//짝이 맞지 않다면
				{
					errorcheck(balanced, ch, openSymbol, position, line_num);//errorcheck함수 실행
				}
				break;
			}

			else//비어있지 않고 들어있다면
			{
				openSymbol=stack.pop();//스택의 pop할 char을 openSymbol에 넣기(왼쪽괄호)
				balanced=matches(ch, openSymbol);//ch와 openSymbol(왼쪽괄호)의 짝이 같은지 확인, 맞으면 1, 다르면 -1

				if(balanced)//짝이 맞다면
				{
					for(i=l; i>0; i--)//현재라인수부터 반복문 돌려서 라인수 감소해주기
					{
						if(c1==1)//가장 최근에 입력받은 오픈괄호를 초기화하고 for문 반복문 빠져나오기 위한 조건
						{
							break;//한 번 확인 됐기 때문에 반복문 탈출
						}

						for(j=55; j>0; j--)
						{
							if(pl[i][j]==openSymbol)//pl[i][j]가 openSymbol과 같으면
							{
								pl[i][j]='\0',	c1=1;//p[i][j]=null로 초기화, c1=1로 변경
								break;
							}
						}
					}
				}

				else if(!balanced)//비어있지 않고 차있는데 balance도 맞지 않다면
				{
					errorcheck(balanced, ch, openSymbol, position, line_num);//에러 번호 체크
				}
			}
		}
		c1=0;//다시 ch입력받아서 while문 돌 것이기 때문에 0으로 초기화
	}

	if(stack.isEmpty() && balanced)//스택이 다 비워져있으면 짝이 다 맞다는 말
	{
		cout<<"1"<<endl;//다 맞으니까 1 출력
	}

	else if(!balanced){ }//위에서 적었기 때문에 pass

	else if(!stack.isEmpty())//스택이 비어있지 않으면
	{
		openSymbol=stack.pop();//openSymbol에 stack에 있는 값 pop을 해서 저장

		for(i=l; i>0; i--)
		{
			if(c2==1)//cout하고 나서 다시 에러찾아서 반복문 돌지 않도록 제한
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



bool isOpen(char ch)//여는 괄호가 들어왔을 때
{
	if((ch =='(') || (ch =='{') || (ch == '['))
	{
		return true;//맞으면 참
	}

	else
	{
		return false;//아니면 거짓
	}
}

bool isClosed(char ch)//닫는 괄호가 들어왔을 때
{
	if((ch == ')') || (ch == '}') ||(ch == ']'))
	{
		return true;//이것 중 하나면 참임
	}

	else
	{
		return false;//아니면 거짓
	}
}

bool matches(char ch, char openSymbol)//짝이 맞는지 확인하기
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
{//ch와 openSymbol을 비교해서 error 1, 또는 2, 또는 3 번호 출력하기
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
