
#include <iostream>
using namespace std;
struct node
{
	int data;
	struct node* next;
	struct node* prev;
};

node* AddHead(node* head, node*& tail, int x)
{
	node* tmp = new node();
	tmp->data = x;
	tmp->prev = nullptr;
	tmp->next = nullptr;

	if (head == nullptr)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		node* element = head;
		while ((element->next != nullptr) && (element->data != x))
		{
			element = element->next;
		}
		if (element->data != x)
		{
			head->prev = tmp;
			tmp->next = head;
			head = tmp;
		}
	}
	return head;
}

void Print_head_tail(node* head, node* tail)
{
	if (head != nullptr)
		if (head->next == tail) std::cout << "empty list\n";
		else
		{
			while (head != tail)
			{
				std::cout << "| " << head->data << " |<->";
				head = head->next;
			}
			std::cout << "| " << head->data << " |\n";
		}
	else std::cout << "empty list\n";
}

void Print_tail_head(node* head, node* tail)
{
	if (head == nullptr) std::cout << "empty list\n";
	else
	{
		while (tail != head)
		{
			std::cout << "| " << tail->data << " |<->";
			tail = tail->prev;
		}
		std::cout << "| " << tail->data << " |\n";
	}
}

node* deletelist(node* head, node*& tail)
{
	if (head != nullptr)
	{
		while (head->next != nullptr) 
		{
			head = head->next;				
			delete(head->prev);
		}
		delete(head);		
	}
	tail = nullptr;
	return nullptr;
}

node* Delete(node* head, node*& tail, int x)
{
	if (head != nullptr)
	{
		int i = 0; node* element = head;
		while (element->next != nullptr)
		{
			i += 1; element = element->next; 
		}
		i += 1;
		if (x > i)
		{
			std::cout << "x above then cout of nodes"; return head;
		}  

		if (x == 1)
		{
			if (head->next != nullptr)
			{
				head = head->next;
				delete(head->prev);
				head->prev = nullptr;
			}
			else head = deletelist(head, tail);
		}
		else
		{
			if (x == i)
			{
				element->prev->next = nullptr;
				delete(element);
			}
			else
			{
				element = head;
				for (auto i = 1; i != x; ++i) element = element->next;

				element->next->prev = element->prev;
				element->prev->next = element->next;
				delete(element);
			}
		}
	}
	return head;
};

bool foundnode(node* first, int x)
{
	bool flag = false; node* element = first;
	while (element != nullptr)
	{
		if (element->data == x)return true;
		element = element->next;
	}
	return flag;
}



void unionlist(node* first, node* second, node*& third, node*& thirdend)
{
	node* element = second;
	while (first != nullptr)
	{
		while (element != nullptr)
		{
			if (first->data == element->data)
			{
				third = AddHead(third, thirdend, first->data);
				first = first->next;
				element = second;
			}
			else
			{
				element = element->next;
			}
		}
		if (element == nullptr)
		{
			first = first->next;
			element = second;
		}
	}
}

int main()
{
	node* first = nullptr; node* firstend = nullptr;
	node* second = nullptr; node* secondend = nullptr;
	node* third = nullptr;	node* thirdend = nullptr;
	int x;
	first = AddHead(first, firstend, rand() % 10);
	first = AddHead(first, firstend, rand() % 10);
	first = AddHead(first, firstend, rand() % 10);
	first = AddHead(first, firstend, rand() % 10);
	second = AddHead(second, secondend, rand() % 10);
	second = AddHead(second, secondend, rand() % 10);
	second = AddHead(second, secondend, rand() % 10);
	second = AddHead(second, secondend, rand() % 10);
	second = AddHead(second, secondend, rand() % 10);
	std::cout << "___First list___\n";
	Print_head_tail(first, firstend);
	std::cout << "___Second list___\n";
	Print_tail_head(second, secondend);

	//Пересечение первого и второго списка||
	unionlist(first, second, third, thirdend);
	std::cout << "___Union of first and second lists___\n";
	Print_head_tail(third, thirdend);
	//Удаление x-го по порядку элемента||
	std::cout << "___Enter the sequence number of the item to be deleted in the first list___\n";
	std::cin >> x;
	first = Delete(first, firstend, x);
	std::cout << "___First list___\n";
	Print_head_tail(first, firstend);
	//Добавление в начало||
	std::cout << "___Enter the sequence number of the item to be include in the first list___\n";
	std::cin >> x;
	Print_head_tail(AddHead(first, firstend, x), firstend);
	//Удаление списка||
	first = deletelist(first, firstend);
	std::cout << "___First list___\n";
	Print_head_tail(first, firstend);

	return 0;
}







