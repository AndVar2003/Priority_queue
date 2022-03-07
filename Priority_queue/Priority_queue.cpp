#include <iostream>
#include "PrQueue.h"
using namespace std;

void queue_size(PrQueue& queue)
{
	int tmp;
	cout << "1. Low" << endl;
	cout << "2. Medium" << endl;
	cout << "3. High" << endl;
	cout << "Choose priority:";
	cin >> tmp;
	switch (tmp)
	{
	case 1:
		cout << queue.GetLowSize() << endl;
		break;
	case 2:
		cout << queue.GetMediumSize() << endl;
		break;
	case 3:
		cout << queue.GetHighSize() << endl;
		break;
	default:
		cout << "Error! Invalid priority!" << endl;
		break;
	}
}
void push_element(PrQueue& queue)
{
	int value;
	int tmp;
	cout << "Enter number:";
	cin >> value;
	cout << "\n1. Low" << endl;
	cout << "2. Medium" << endl;
	cout << "3. High" << endl;
	cout << "Choose priority:";
	cin >> tmp;
	system("Cls");
	Priority prior = Priority(tmp);
	try
	{
		queue.Push(value, prior);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
}
void swap_move(PrQueue& queue_a, PrQueue& queue_b)
{
	PrQueue tmp(move(queue_a));
	queue_a = move(queue_b);
	queue_b = move(tmp);
}
void swap_copy(PrQueue& queue_a, PrQueue& queue_b)
{
	PrQueue tmp(queue_a);
	queue_a = queue_b;
	queue_b = tmp;
}
int main()
{
	PrQueue q_one, q_two;
	q_one.Push(1, Priority(1));
	q_one.Push(4, Priority(3));
	q_one.Push(2, Priority(2));
	q_one.Push(5, Priority(3));
	q_two.Push(8, Priority(3));
	int op;
	while (true)
	{
		cout << "1. Swap queue with move" << endl;
		cout << "2. Swap queue with copy" << endl;
		cout << "3. Get size" << endl;
		cout << "4. Get size(specific priority)" << endl;
		cout << "5. Empty check" << endl;
		cout << "6. Push" << endl;
		cout << "7. Pop" << endl;;
		cout << "8. Get First info and priority" << endl;
		cout << endl;
		cout << "0. Exit" << endl;
		cout << endl;
		cout << "Queue(-es) status: " << endl;
		if (q_one.GetSize() > 0)
		{
			cout << "First queue" << endl;
			for (int i = 0; i < q_one.GetSize(); i++)
				cout << q_one[i] << " ";
			cout << endl;
		}
		if (q_two.GetSize() > 0)
		{
			cout << "Second queue" << endl;
			for (int i = 0; i < q_two.GetSize(); i++)
				cout << q_two[i] << " ";
			cout << endl;
		}
		cout << endl;
		cout << "Choose option:";
		cin >> op;
		system("Cls");
		if (op == 0)
			break;
		switch (op)
		{
		case 1:
			swap(q_one, q_two);
			break;
		case 2:
			swap_copy(q_one, q_two);
			break;
		case 3:
			cout << "First queue size - " << q_one.GetSize() << endl;
			break;
		case 4:
			queue_size(q_one);
			break;
		case 5:
			if (q_one.IsEmpty() == 1)
				cout << "First queue is empty!" << endl;
			else
				cout << "First queue isn't empty!" << endl;
			break;
		case 6:
			push_element(q_one);
			break;
		case 7:
			q_one.Pop();
			break;
		case 8:
			if (q_one.GetSize() > 0)
				cout << "First element value - " << q_one.GetFirst() << " , priority - " << q_one.GetFirstPriority() << endl;
			if (q_two.GetSize() > 0)
				cout << "First element value - " << q_two.GetFirst() << " , priority - " << q_two.GetFirstPriority() << endl;
			break;
		default:
			cout << "Error! Incorrect option!Try again!" << endl;
			break;
		}
		system("pause");
		system("Cls");
	}
	return 0;
}

