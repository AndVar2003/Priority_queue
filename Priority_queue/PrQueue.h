#pragma once
#ifndef __queue_defined__
#define __queue_defined__
#include <iostream>
using namespace std;

constexpr auto START_LINE_PRIORITY = __LINE__;
enum class Priority {
	low = 1,
	medium,
	high
};
constexpr auto PRIORITY_COUNT = __LINE__ - START_LINE_PRIORITY - 3;
const string PRIORITY_NAMES[] = { "low", "medium", "high" };

typedef int InfoType;
class PrQueue
{
private:
	struct PrQItem {
		InfoType info;
		Priority type;
		PrQItem* next;
		PrQItem(InfoType Ainfo, Priority atype) : info(Ainfo),type(atype), next(NULL) {}
	};
	PrQItem* front, * rear_high, * rear_medium, * rear_low;
	unsigned size;
	unsigned size_high;
	unsigned size_medium;
	unsigned size_low;
	void Erase(); 
	void Clone(const PrQueue&);
	void move(PrQItem*&, PrQItem*&);
	void move(PrQueue&& other);

public:
	PrQueue() : front(NULL), rear_high(NULL), rear_medium(NULL), rear_low(NULL), size(0) {};
	PrQueue(const PrQueue&); 
	PrQueue(PrQueue&&) noexcept;
	~PrQueue();
	PrQueue& operator = (const PrQueue&);
	PrQueue& operator = (PrQueue&&) noexcept;
	void Push(InfoType Ainfo, Priority atype);
	bool Pop();
	InfoType GetFirst()const;
	string GetFirstPriority()const;
	bool IsEmpty()const;
	unsigned GetSize() const;
	unsigned GetHighSize()const;
	unsigned GetMediumSize()const;
	unsigned GetLowSize()const;
	const InfoType& GetByIndex(unsigned) const;
	InfoType operator [] (unsigned) const;
};
#endif

