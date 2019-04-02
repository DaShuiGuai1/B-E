#ifndef listnode
#define listnode
#define FAIL 0x00
#define SUCCESS 0x80
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
class singlenode
{
	public:
		void * Value = nullptr;
		singlenode * Next = nullptr;
		singlenode * Pre = nullptr;
		singlenode * This = this;
};
class List
{
	protected:
		unsigned int Length = 0;
		singlenode * LastNode = nullptr;
		singlenode * OriginNode = nullptr;
	public:
		singlenode * GetNext(singlenode * );
		unsigned int Add(void * value);
		unsigned int Insert(unsigned int , void * value);
		unsigned int Change(unsigned int , void * value);
		void * Get(unsigned int );
		unsigned int Del(unsigned int );
		unsigned int GetLength();
		void copyto(List *tmp)
		{
			if (tmp)
			{
				singlenode * tmpnode=OriginNode;
				//tmp->Length = this->Length;
				for (uint i = 1; i <= Length; i++)
				{
					tmp->Add(tmpnode->Value);
					tmpnode = tmpnode->Next;
				}
			}
		}
		void Clear()
		{
			this->~List();
			Length = 0;
			LastNode = nullptr;
			OriginNode = nullptr;
		}
		~List()//如果list存储的是
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
};
inline unsigned int List::Add(void *value)
{
	unsigned int ret = FAIL;
	if (value != nullptr)
	{
		singlenode * tmp = new singlenode;
		if (tmp != nullptr)
		{
			tmp->Value = value;
			if (0 == Length)
			{
				tmp->Pre = nullptr;
				OriginNode = tmp;
			}
			else
			{
				tmp->Pre = LastNode->This;
				LastNode->Next= tmp;
			}
			Length++;
			LastNode = tmp;
			ret = SUCCESS;
		}
		else
			ret = 0x20;
	}
	else
	{
		ret = 0x10;
	}
	return ret;
}
inline unsigned int List::Insert(unsigned int index, void *value)
{
	unsigned int ret = FAIL;
	singlenode * tmpnode = LastNode;
	if (Length > 0 && index > 0 && Length >= index)
	{
		for (unsigned int i = 0; i < Length - index; i++)
			tmpnode = tmpnode->Pre;
		singlenode * inode = new singlenode;
		if (inode != nullptr)
		{
			if (tmpnode->Pre == nullptr)
			{
				inode->Next = tmpnode->This;
				tmpnode->Pre = inode->This;
				inode->Value = value;
				OriginNode = tmpnode;
			}
			else
			{
				inode->Pre = tmpnode->Pre;
				inode->Next = tmpnode->This;
				inode->Value = value;
			}
			Length++;
			ret = SUCCESS;
		}
		else
			ret = 0x20;
	}
	else
		ret = 0x10;
	return ret;
}
inline unsigned int List::Change(unsigned int index, void *value)
{
	unsigned int ret = FAIL;
	singlenode *tmpnode = LastNode;
	if (tmpnode != nullptr)
	{
		if (Length > 0 && index > 0 && Length >= index)
		{
			for (unsigned int i = 0; i < Length - index; i++)
			{
				tmpnode = tmpnode->Pre;
			}
			tmpnode->Value = value;
			ret = SUCCESS;
		}
		else
			ret = 0x20;
	}
	else
		ret = 0x10;
	return ret;
}
inline unsigned int List::Del(unsigned int index)
{
	unsigned int ret = FAIL;
	singlenode*tmpnode = nullptr;
	if (index <= Length / 2)
	{
		tmpnode = OriginNode;
	}
	else
	{
		tmpnode = LastNode;
	}
	if (tmpnode != nullptr)
	{
		if (Length > 0 && index > 0 && Length >= index)
		{
			if (index > Length / 2)
			{
				for (unsigned int i = 0; i < Length - index; i++)
				{
					if (tmpnode->Pre)
						tmpnode = tmpnode->Pre;
					else
					{
						ret = 0x30;
						return ret;
					}
				}
			}
			else
			{
				for (unsigned int i = 1; i < index; i++)
				{
					if (tmpnode->Next)
					{
						tmpnode = tmpnode->Next;
					}
				}
			}
			//删除时应考虑删除首节点、末节点、首末节点及其他节点de情况
			if (tmpnode->Pre != nullptr && tmpnode->Next != nullptr)//not original or last
			{
				tmpnode->Next->Pre = tmpnode->Pre;
				tmpnode->Pre->Next = tmpnode->Next;
			}
			else if (tmpnode->Pre == nullptr && tmpnode->Next == nullptr)
			{
				OriginNode = nullptr;
				LastNode = nullptr;
			}
			else
			{
				if (tmpnode->Next == nullptr)//if delete lastnode
				{
					tmpnode->Pre->Next = nullptr;
					LastNode = tmpnode->Pre;
				}
				if (tmpnode->Pre == nullptr)//if delete originnode
				{
					OriginNode = tmpnode->Next;
					tmpnode->Next->Pre = nullptr;
				}
			}
			delete tmpnode->This;
			tmpnode->This = nullptr;
			Length--;
			ret = SUCCESS;
		}
		else
			ret = 0x10;
	}
	else
		ret = 0x20;
	return ret;
}
inline void * List::Get(unsigned int index)
{
	singlenode * tmpnode = nullptr;
	void * tmp = nullptr;
	{
		if (Length > 0 && index > 0 && Length >= index)
		{
			if (index < Length / 2)
			{
				tmpnode = OriginNode;
				tmp = tmpnode->Value;
				for (unsigned int i = 0; i < index - 1; i++)
				{
					tmp = tmpnode->Next->Value;
					tmpnode = tmpnode->Next;
				}
			}
			else
			{
				tmpnode = LastNode;
				tmp = tmpnode->Value;
				for (unsigned int i = 0; i < Length - index; i++)
				{
					tmp = tmpnode->Pre->Value;
					tmpnode = tmpnode->Pre;
				}
			}
		}
		else
			tmp = nullptr;
	}
	return tmp;
}
inline unsigned int List::GetLength()
{
	return this->Length;
}
inline singlenode * List::GetNext(singlenode * node)
{
	if (node)
	{
		return node->Next;
	}
	else
	{
		//printf("GetNext failed. Null pointer.");
	}
}
#endif