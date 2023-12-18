#pragma once
using namespace std;
template <typename T> class Tlist
{
	struct TNode
	{
		T value;
		TNode* pNext;
	};
	TNode* pFirst;
	size_t sz;
public:
	Tlist() : pFirst(nullptr), sz(0) { };

	Tlist(const Tlist& l) : pFirst(nullptr), sz(l.sz) {
		if (l.pFirst == nullptr)
			return;
		TNode* pNew = pFirst = new TNode{ *l.pFirst };
		for (; pNew->pNext != nullptr; pNew = pNew->pNext)
			pNew->pNext = new TNode(*pNew->pNext);
	};

	Tlist(Tlist&& l)  {
		pFirst = nullptr;
		swap(*this, l);
	};

	Tlist& operator=(const Tlist& l)
	{
		if (this != &Tlist)
		{
			Tlist tmp(Tlist);
			swap(*this, tmp);
		}
		return *this;
	};

	~Tlist()
	{
		TNode* p;
		while (pFirst != nullptr) {
			p = pFirst;
			pFirst = pFirst->pNext;
			delete p;
		}
	};
	size_t size() const  {
		return sz;
	};
	bool IsEmpty() const  {
		return sz == 0;
	};
	T& Front() {
		return pFirst->value;
	};
	void PushFront(const T& val)
	{
		TNode* node = new TNode{ val, pFirst };
		pFirst = node;
		sz++;
	};

	void PushBack(const T& val)
	{
		TNode* pNew = new TNode{ val, nullptr};
		TNode* p = ToPos(sz);
		p->pNext = pNew;
		sz++;
	}

	void PopFront()  {
		TNode* p = pFirst;
		pFirst = pFirst->pNext;
		delete p;
		sz--;
	};
	TNode& operator[](size_t pos)
	{
		TNode* p = ToPos(pos);
		return p->value;
	};
	void PushAfter(size_t pos, const T& val)
	{
		TNode* p = ToPos(pos);
		TNode* pNew = new TNode{ val, p->pNext };
		p->pNext = pNew;
		sz++;
	};

	TNode* ToPos(size_t pos)
	{
		TNode* res = pFirst;
		for (int i = 1; i < pos; i++)
		{
			res = res->pNext;
		}
		return res;
	};

	void Check_Value(size_t pos)
	{
		TNode p = *ToPos(pos);
		cout << p.value;
	};

	void EraseAfter(size_t pos)
	{
		TNode* p = ToPos(pos);
		TNode* pDel = p->pNext;
		p->pNext = pDel->pNext;
		delete pDel;
		sz--;
	};
};

