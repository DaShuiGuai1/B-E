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

FILE*ptxt = nullptr;//��main�д򿪣���bande�������йر�
FILE*presult = nullptr;//��main�д򿪣���bande�������йر�
static uint totalplate = 0;//������¼������������printtxt����

class Stack : public List//һ������,��Ϊʹ��list�ṹ����Ϊstack�޷�ȷ������ʱ��ջ����,���������󳤶ȿ��������Ϳռ�������
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
	//uint visualpop()//�����������ǲ�����������
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

class PStacks//���Ӷѷŵ�һ����������ܰ����������
{
public:
	~PStacks()//������ջ������������
	{
		for (uint i = stacklist.GetLength(); i > 0; i--)
		{
			((Stack *)(stacklist.Get(i)))->~Stack();
			delete stacklist.Get(i);//й¶1��û��delete stacklist
		}
		stacklist.~List();
	}
	uint getstackquantity()
	{
		return stacklist.GetLength();
	}
	void addplate(uint stacknum, uint * platenum)//�ѷ�һ������
	{
		if (stacknum > 0)
		{
			if (stacknum <= stacklist.GetLength())//��������������
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
			else if (stacknum == stacklist.GetLength() + 1)//�����µ�stack��
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
		if (length >= totalplate)//ȷ�����㹻�ռ�
		{
			memset(numbers, 0, length);
			if (this->stacklist.GetLength() > 0)//ȷ����stack����pop
			{
				for (uint i = stacklist.GetLength(); i >=1 ; i--)//ѭ��ÿ��stack
				{
					Stack* tmp = (Stack*)stacklist.Get(i);
					if (tmp)
					{
						for (uint r = tmp->GetLength(); r >=1 ; r--)//popÿ��stack�е�ÿ��plate
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
	List stacklist;//���Ӷѵ�list
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
		uint tmp = AllPStacks.GetLength();//й¶���2��û�п���lengthʵʱ�仯
		for (uint i = 1; i <= tmp; i++)
		{
			((PStacks*)(AllPStacks.Get(1)))->~PStacks();//ɾ��ÿ�������ÿ�ѵ�ÿ������
			delete AllPStacks.Get(1);//ɾ��ÿ�������ÿ��
			AllPStacks.Del(1);//ɾ��ÿ�����
			//й¶���3������delete��del����
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
		for (uint q = 1; q < platenum[0]+1; q++)//ѭ�����ӱ��
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
			for (uint t = 1; t <= len; t++)//ѭ�����п��ܵĶѷ����
			{
				for (i = 1; i <= ((PStacks *)AllPStacks.Get(t))->getstackquantity() + 1/*��ѭ�����Ѵ��ڵĶѷ����ʱ�����������Ҳ�ѷŵ����*/; i++)//ѭ��ÿ������е�ÿ������
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
				delete AllPStacks.Get(1);//й¶4������delete
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
			for (uint i = 1 ; i <= AllPStacks.GetLength(); i++)//ѭ���������
			{
				PStacks * tmpstacks = ((PStacks*)AllPStacks.Get(i));
				if(tmpstacks)//ÿ�������pop������plateseq
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
	uint *platenum;//��������������ͱ��
	List plateseq;//Eϴ�����Ӻ�õ������п��ܵ����������
	List AllPStacks;//B���п��ܵİڷŷ�ʽ
	uint *Prefix;//E�İڷŷ�ʽ�ܵõ������prefix
};