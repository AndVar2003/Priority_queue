#include "PrQueue.h"
#include <exception>
using namespace std;
void PrQueue::Erase()
{
	while (Pop());
	size = 0;
	size_high = 0;
	size_medium = 0;
	size_low = 0;
}

void PrQueue::Clone(const PrQueue& Q)
{
	PrQItem* tmp = Q.front;
	for (unsigned i = 0; i < Q.size; i++)
	{
		Push(tmp->info, tmp->type);
		tmp = tmp->next;
	}
}

PrQueue::PrQueue(const PrQueue& Q)
{
	size = 0;
	Clone(Q);
}

PrQueue& PrQueue::operator=(const PrQueue& Q)
{
	if (this != &Q) {
		Erase();
		Clone(Q);
	}
	return *this;
}

PrQueue& PrQueue::operator=(PrQueue&& other) noexcept
{
	if (&other == this)
		return *this;
	Erase();
	move(front, other.front);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);
	size = other.size;
	size_high = other.size_high;
	size_medium = other.size_medium;
	size_low = other.size_low;

	other.size_high = 0;
	other.size_medium = 0;
	other.size_low = 0;
	other.size = 0;
	return *this;
}


void PrQueue::Push(InfoType Ainfo, Priority atype)
{
	if (int(atype) < 1 || int(atype) > PRIORITY_COUNT)
		throw exception("Error! Invalid priority input!");
	PrQItem* tmp1 = new PrQItem(Ainfo, atype);
	if (atype == Priority(1))// low
	{
		if (rear_low != NULL)
			rear_low->next = tmp1;
		else
			if (size == 0)
				front = tmp1;
			else
				if (rear_medium != NULL)
					rear_medium->next = tmp1;
				else
					rear_high->next = tmp1;
		rear_low = tmp1;
		size_low++;
	}
	
	if (atype == Priority(2))// medium
	{
		if (rear_high != NULL && rear_low == NULL)
			if (rear_medium != NULL)
				rear_medium->next = tmp1;
			else
				rear_high->next = tmp1;

		if (rear_high == NULL && rear_low == NULL)
			if (rear_medium != NULL)
				rear_medium->next = tmp1;
			else
				front = tmp1;

		if (rear_high == NULL && rear_low != NULL)
		{
			if (rear_medium != NULL)
			{
				PrQItem* tmp2 = rear_medium->next;
				rear_medium->next = tmp1;
				tmp1->next = tmp2;
			}
			else
			{
				PrQItem* tmp2 = front;
				front = tmp1;
				tmp1->next = tmp2;
			}
		}
		if (rear_high != NULL && rear_low != NULL)
		{
			{
				if (rear_medium != NULL)
				{
					PrQItem* tmp2 = rear_medium->next;
					rear_medium->next = tmp1;
					tmp1->next = tmp2;
				}
				else
				{
					PrQItem* tmp2 = rear_high->next;
					rear_high->next = tmp1;
					tmp1->next = tmp2;
				}
			}
		}

		rear_medium = tmp1;
		size_medium++;
	}

	if (atype == Priority(3))// high
	{
		if (rear_medium != NULL || rear_low != NULL)
		{
			if (rear_high != NULL)
			{
				PrQItem* tmp2 = rear_high->next;
				rear_high->next = tmp1;
				tmp1->next = tmp2;
			}
			else
			{
				PrQItem* tmp2 = front;
				front = tmp1;
				tmp1->next = tmp2;
			}

		}
		if (rear_medium == NULL && rear_low == NULL)
		{
			if (size > 0)
				rear_high->next = tmp1;
			else
				front = tmp1;
		}
		rear_high = tmp1;
		size_high++;
	}

	size++;
}


bool PrQueue::Pop()
{
	if (size == 0)
		return false;
	PrQItem* tmp = front;
	front = front->next;
	delete tmp;
	size--;
	if (size == 0) 
	{
		rear_low = NULL;
		rear_medium = NULL;
		rear_high = NULL;
	}
	return true;
}

PrQueue::~PrQueue()
{
	Erase();
}

bool PrQueue::IsEmpty() const
{
	return (size == 0);
}

const InfoType& PrQueue::GetByIndex(unsigned k) const
{
	if ((k < 0) || (k >= size))
		throw std::exception("Impossible to execute operator[]: invalid index");
	PrQItem* tmp = front;
	for (unsigned i = 0; i < k; i++)
		tmp = tmp->next;
	return tmp->info;
}

InfoType PrQueue::operator[](unsigned k) const
{
	return (InfoType&)GetByIndex(k);
}

unsigned PrQueue::GetSize() const
{
	return size;
}

unsigned PrQueue::GetHighSize() const
{
	return size_high;
}

unsigned PrQueue::GetMediumSize() const
{
	return size_medium;
}

unsigned PrQueue::GetLowSize() const
{
	return size_low;
}

InfoType PrQueue::GetFirst() const
{
	if (size == 0)
		throw exception("Impossible to execute GetFirst:queue is empty");
	return front->info;
}

string PrQueue::GetFirstPriority() const
{
	return PRIORITY_NAMES[(int)front->type - 1];
}

void PrQueue::move(PrQItem*& a, PrQItem*& b)
{
	a = b;
	b = nullptr;
}

void PrQueue::move(PrQueue&& other)
{
	move(front, other.front);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);

	size = other.size;
	size_high = other.size_high;
	size_medium = other.size_medium;
	size_low = other.size_low;

	other.size_high = 0;
	other.size_medium = 0;
	other.size_low = 0;
	other.size = 0;
}

PrQueue::PrQueue(PrQueue&& other) noexcept
{
	move(front, other.front);
	move(rear_high, other.rear_high);
	move(rear_medium, other.rear_medium);
	move(rear_low, other.rear_low);

	size = other.size;
	size_high = other.size_high;
	size_medium = other.size_medium;
	size_low = other.size_low;

	other.size_high = 0;
	other.size_medium = 0;
	other.size_low = 0;
	other.size = 0;
}