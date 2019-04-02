/*
Author:Wu
Date:2019/4/2

Class BandE simulates Bessie and Elsie wash dishes. Here are 3 main processes in BandE, soap, wash and checknumlist. 
Function soap lists all possibilities that Bessie would make. Function wash lists all numberlists that Elsie could get from the possibilities.
Function checknumlist would find the max prefix of the numberlists and show the corresponding possibility.
*/

#pragma once
#include"ListNode.h"
#ifndef printlist
#define printlist //If the progress is not nesessery, you may add '//' at the start of this line, which would save a lot time.
#endif // !printlist

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE*ptxt = nullptr;//在main中打开，在bande的析构中关闭
FILE*presult = nullptr;//在main中打开，在bande的析构中关闭
static uint totalplate = 0;//单纯记录盘子数量，供printtxt调用

class Stack : public List//一堆盘子,改为使用list结构，因为stack无法确定拷贝时的栈长度,如果都已最大长度拷贝，降低空间利用率
{
public:
	Stack()
	{
		this->Clear();
	}
	~Stack()
	{
		if (LastNode)
		{
			singlenode *tmp = LastNode;
			for (uint i = 0; i < Length; i++)
			{
				if(LastNode)
					tmp = LastNode->Pre;
				delete LastNode;
				LastNode = tmp;
			}
			Length = 0;
		}
	}
	//uint visualpop()//先入后出，但是不会消除数据
	//{
	//	if (Length > 0)
	//	{
	//		static singlenode* tmp = LastNode;
	//		if (tmp != nullptr)
	//		{
	//			if (Length > 0)
	//			{
	//				if (tmp->Pre)
	//				{
	//					tmp = tmp->Pre;
	//				}
	//				else
	//				{
	//					;						;
	//				}
	//				Length--;
	//			}
	//		}
	//		return *((uint*)tmp->Value);
	//	}
	//	else
	//	{
	//		printf("pop failed, stack leak");
	//		system("pause"); 
	//	}
	//}
	void push(uint * num)
	{
		if (Add(num) != SUCCESS)
			printf("Push %8u fail", *(uint *)num);
	}
	void print()
	{
		singlenode *tmp = LastNode;
		for (uint i = 1; i <= Length; i++)
		{
			printf("%8u", *((uint *)tmp->Value));
			tmp = tmp->Pre;
		}
	}
	void printtxt(FILE * file)
	{
		singlenode *tmp = LastNode;
		for (uint i = 1; i <= Length; i++)
		{
			fprintf(file,"%8u", *((uint *)tmp->Value));
			tmp = tmp->Pre;
		}
	}
};

class PStacks//盘子堆放的一种情况，可能包含多堆盘子
{
public:
	~PStacks()//先析构栈，再析构链表
	{
		for (uint i = stacklist.GetLength(); i > 0; i--)
		{
			((Stack *)(stacklist.Get(i)))->~Stack();
			delete stacklist.Get(i);//泄露1，没有delete stacklist
		}
		stacklist.~List();
	}
	uint getstackquantity()
	{
		return stacklist.GetLength();
	}
	void addplate(uint stacknum, uint * platenum)//堆放一个盘子
	{
		if (stacknum > 0)
		{
			if (stacknum <= stacklist.GetLength())//放在现有盘子上
			{
				Stack *tmp = (Stack *)stacklist.Get(stacknum);
				if (tmp)
				{
					tmp->push(platenum);
				}
				else
				{
					printf("addplate fail. stack is null, stacknum is %10d", stacknum);
				}
			}
			else if (stacknum == stacklist.GetLength() + 1)//放在新的stack上
			{
				Stack * tmp = new Stack;
				if (tmp)
				{
					if (stacklist.Add(tmp) == SUCCESS)
						tmp->push(platenum);
					else
					{
						printf("creating new plate stack failed. stacknum is %10d", stacknum);
						system("pause");
					}
				}
				else
				{
					printf("creating new plate stack failed. stacknum is %10d", stacknum);
					system("pause");
				}
			}
			else
			{
				printf("addplate fail. Stack number is out of range!stacknum is %10d", stacknum);
				system("pause");
			}
		}
	}
	void popplate(uint *numbers,uint length)
	{
		uint t = 0;
		if (length >= totalplate)//确认有足够空间
		{
			memset(numbers, 0, length);
			if (this->stacklist.GetLength() > 0)//确认有stack进行pop
			{
				for (uint i = stacklist.GetLength(); i >=1 ; i--)//循环每个stack
				{
					Stack* tmp = (Stack*)stacklist.Get(i);
					if (tmp)
					{
						for (uint r = tmp->GetLength(); r >=1 ; r--)//pop每个stack中的每个plate
						{
							numbers[t] = *((uint*)tmp->Get(r));
							if (t<length)
							{
								t++;
							}
						}
					}
				}
			}
			else
			{
				memset(numbers, 0, length);
			}
		}
		else
		{
			printf("Can not pop platenumber out. Array's length is not enough");
		}
	}
	void copyto(PStacks * tmp)
	{
		for (uint i = 1; i <= stacklist.GetLength(); i++)
		{
 			Stack * tmpstack = new Stack;
			((Stack *)stacklist.Get(i))->copyto(tmpstack);
			tmp->stacklist.Add(tmpstack);
		}
	}
	void print()
	{
		for (uint i = 1; i <= stacklist.GetLength(); i++)
		{
			printf("\n\t");
			for (uint t = 0; t < (totalplate - ((Stack*)(stacklist.Get(i)))->GetLength());t++)
				printf("\t");
			((Stack*)stacklist.Get(i))->print();
		}
	}
	void printtxt(FILE * file)
	{
		for (uint i = 1; i <= stacklist.GetLength(); i++)
		{
			fprintf(file,"\n\t");
			for (uint t = 0; t < 2*(totalplate - ((Stack*)(stacklist.Get(i)))->GetLength()); t++)
				fprintf(file,"\t");
			((Stack*)stacklist.Get(i))->printtxt(file);
		}
	}
private:
	List stacklist;//盘子堆的list
};

class BandE//Bessie and Elsie
{
public:
	BandE(uint const * plates, uint length)
	{
		platenum = new uint[length];
		totalplate = plates[0];
		Prefix = nullptr;
		memcpy(platenum, plates, length * sizeof(uint));
		plateseq.Clear();
		AllPStacks.Clear();
	}
	~BandE()
	{
		if (plateseq.GetLength() == 0)
		{
			delete Prefix;
		}
		else
		{
			delete[] Prefix;
		}
		if (platenum[0] == 0)
			delete platenum;
		else
			delete[]platenum;
		uint tmp = AllPStacks.GetLength();//泄露情况2，没有考虑length实时变化
		for (uint i = 1; i <= tmp; i++)
		{
			((PStacks*)(AllPStacks.Get(1)))->~PStacks();//删除每种情况的每堆的每个盘子
			delete AllPStacks.Get(1);//删除每种情况的每堆
			AllPStacks.Del(1);//删除每种情况
			//泄露情况3：忘了delete和del操作
		}
		AllPStacks.~List();
		for (uint i = 1; i <= plateseq.GetLength(); i++)
		{
			delete[](uint*)(plateseq.Get(i));
		}
		plateseq.~List();
		fclose(ptxt);
		fclose(presult);
	}
	void soap()//Bessie does
	{
		AllPStacks.Clear();
		for (uint q = 1; q < platenum[0]+1; q++)//循环盘子编号
		{
			uint len = AllPStacks.GetLength();
			PStacks *tmpP = nullptr;
			uint i = 1;
			if (len == 0)
			{
				tmpP = new PStacks;
				if (tmpP)
				{
					tmpP->addplate(1, &platenum[q]);
					if (AllPStacks.Add(tmpP) != SUCCESS)
						printf("Allstacks add fail!");
				}
				//print();
			}
			for (uint t = 1; t <= len; t++)//循环所有可能的堆放情况
			{
				for (i = 1; i <= ((PStacks *)AllPStacks.Get(t))->getstackquantity() + 1/*当循环完已存在的堆放情况时，最后添加在右侧堆放的情况*/; i++)//循环每种情况中的每堆盘子
				{
					tmpP = new PStacks;
					if (tmpP)
					{
						void *get = AllPStacks.Get(t);
						if (get)
							((PStacks *)get)->copyto(tmpP);
						else
							printf("get %4u of AllPstacks fail", t);
						tmpP->addplate(i, &platenum[q]);
						if (AllPStacks.Add(tmpP) != SUCCESS)
							printf("Allstacks add fail!");
					}
				}
			}
#ifdef printlist
			//Sprint();
#endif // printlist
			for (uint i = 1; i <= len; i++)
			{
				((PStacks *)AllPStacks.Get(1))->~PStacks();
				delete AllPStacks.Get(1);//泄露4：忘记delete
				uint ret = AllPStacks.Del(1);
				if(ret!=SUCCESS)
					printf("Delete AllPstacks Failed! Code:%4d",ret);
			}
#ifdef printlist
			//Sprint();
			//fprintf(ptxt, "\n\n Soap number %8u(turn %8u) plate:\n\n", platenum[q], q);
			Sprinttxt();
#endif // printlist
		}
	}
	void wash()//Elsie does
	{
		plateseq.Clear();
		if (AllPStacks.GetLength()>0)
		{
			for (uint i = 1 ; i <= AllPStacks.GetLength(); i++)//循环所有情况
			{
				PStacks * tmpstacks = ((PStacks*)AllPStacks.Get(i));
				if(tmpstacks)//每种情况均pop，存于plateseq
				{
					uint *tmpint = new uint[platenum[0]];
					tmpstacks->popplate(tmpint, platenum[0]);
					plateseq.Add(tmpint);
				}
				else
				{
					printf("wash fail. %4uth stacks is empty!", i);
					system("pasue");
				}
			}
		}
#ifdef printlist
		//Wprint();
		Wprinttxt();
#endif // printlist
		
	}
	void CheckNumList()//get max prefix from stacks
	{
		if (plateseq.GetLength() > 0)
		{
			delete Prefix;
			Prefix = new uint[plateseq.GetLength()];
			memset(Prefix, 0, plateseq.GetLength()*sizeof(uint));
			uint max = 0;
			for (uint i = 1; i <= plateseq.GetLength(); i++)
			{
				Prefix[i - 1] = GetmaxPrefix((uint*)plateseq.Get(i), platenum[0]);
			}
			for (uint i = 0; i < plateseq.GetLength(); i++)
			{
				if (Prefix[i] > max)
					max = Prefix[i];
			}
			printf("\nThe max prefix is (%8u)!\n", max);
			printf("\nThe following stacks are:\n");
			fprintf(presult,"\nThe max prefix is (%8u)!\n", max);
			fprintf(presult,"\nThe following stacks are:\n");
			for (uint i = 1,t=1; i <= plateseq.GetLength(); i++)
			{
				if (Prefix[i - 1] == max)
				{
//#ifdef printlist
					printf("\n\n\tStacks %8u:", t);
//#endif
					fprintf(presult,"\n\n\tStacks %8u:", t);
					PStacks* tmpstack = (PStacks*)AllPStacks.Get(i);
					if (tmpstack)
					{
//#ifdef printlist
						tmpstack->print();
//#endif
						tmpstack->printtxt(presult);
//#ifdef printlist
						printf("\n\t\tThe sequence is :\n\t");
//#endif // printlist
						fprintf(presult,"\n\t\tThe sequence is :\n\t");
						for (uint u = 0; u < platenum[0]; u++)
						{
//#ifdef printlist
							printf("%8u", ((uint*)plateseq.Get(i))[u]);
//#endif
							fprintf(presult, "%8u",((uint*)plateseq.Get(i))[u]);
						}
					}
					t++;
				}
			}
		}
	}
	uint GetmaxPrefix(const uint*numbers,const uint len)
	{
		uint ret = 0;
		uint tmp[2] = { 0,0 };
		if (numbers && len == platenum[0] && len > 0)
		{
			tmp[0] = 1;
			for (uint i = 0; i < len - 1; i++)
			{
				if (numbers[i] < numbers[i + 1])
				{
					tmp[0]++;
				}
				else
				{
					if (tmp[0] > tmp[1])
						tmp[1] = tmp[0];
					tmp[0] = 0;
				}
			}
		}
		else
			;
		ret = tmp[1];
		return ret;
	}

	void Sprint()// print all stacks
	{
		for (uint i = 1; i <= AllPStacks.GetLength(); i++)
		{
			printf("\n\tThe stacks(%4u) are:\n",i);
			((PStacks*)AllPStacks.Get(i))->print();
		}
	}
	void Sprinttxt()//Print record to txt
	{
		for (uint i = 1; i <= AllPStacks.GetLength(); i++)
		{
			fprintf(ptxt,"\n\tThe stacks(%4u) are:\n", i);
			((PStacks*)AllPStacks.Get(i))->printtxt(ptxt);
		}
	}
	void Wprint()//print all prefix
	{
		printf("\nThe result is :(total %8u)\n", AllPStacks.GetLength());
		for (uint i = 1; i <= plateseq.GetLength(); i++)
		{
			printf("\nSequence %8u:\n", i);
			for (uint t = 0; t < platenum[0]; t++)
			{
				printf("%8u",((uint*)plateseq.Get(i))[t]);
			}
		}
	}
	void Wprinttxt()
	{
		fopen_s(&ptxt, "Numbers.txt", "w");
		fprintf(ptxt,"\nThe result is :(total %8u)\n", AllPStacks.GetLength());
		for (uint i = 1; i <= plateseq.GetLength(); i++)
		{
			fprintf(ptxt,"\nSequence %8u:\n", i);
			for (uint t = 0; t < platenum[0]; t++)
			{
				fprintf(ptxt,"%8u", ((uint*)plateseq.Get(i))[t]);
			}
		}
	}
private:
	uint *platenum;//输入的盘子数量和编号
	List plateseq;//E洗完盘子后得到的所有可能的排序的链表
	List AllPStacks;//B所有可能的摆放方式
	uint *Prefix;//E的摆放方式能得到的最大prefix
};