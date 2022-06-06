#include "ListRand.hpp"

bool ListRand::clear_list(void)
{
	while (Tail)
	{
		if (!Tail)
			return (true);
		Tail = Tail->m_prev;
		Tail->m_next->m_prev = nullptr;
		delete Tail->m_next;
		Tail->m_next = nullptr;
	}
};

ListRand::ListRand(ListNode *const fst_ptr, ListNode *const lst_ptr)
	: Head(fst_ptr), Tail(lst_ptr)
{
	Count = 0;
}

ListRand::~ListRand() {}

void ListRand::Serialize(std::ofstream &out_file)
{
	Serializator serializator = Serializator();
	if (!serializator.serialize_list(Head, out_file))
	{
		std::cerr << "serialize error!" << std::endl;
		out_file.close();
		clear_list();
		exit(1);
	}
	else
		clear_list();

	//TODO: удалить
	std::cout << "EEEEEEEEEEEEEEEEE" << std::endl;
	while (Head)
	{
		std::cout << "===" << Head->m_data << std::endl;
		Head = Head->m_next;
	}
}

void ListRand::Deserialize(std::ifstream &in_file)
{
	Deserializator deserializator = Deserializator();
	Head = deserializator.deserialize_list(in_file, Tail, Count);
	if (Head == nullptr)
	{
		std::cerr << "deserialize error!" << std::endl;
		exit(1);
	}

	ListNode *tail_ptr = Tail;
	while (tail_ptr)
	{
		std::cout << YELLOW << "Node with data: " << NORM;
		std::cout << tail_ptr->m_data;
		if (tail_ptr->m_rand)
		{
			std::cout << PURPLE " refers to node with data: " << NORM
				<< tail_ptr->m_rand->m_data;
		}
		std::cout << std::endl;
		tail_ptr = tail_ptr->m_prev;
	}

	std::cout << "========================================" << std::endl;

	ListNode *head_ptr = Head;
	while (head_ptr)
	{
		std::cout << YELLOW << "Node with data: " << NORM;
		std::cout << head_ptr->m_data;
		if (head_ptr->m_rand)
		{
			std::cout << PURPLE " refers to node with data: " << NORM
			  << head_ptr->m_rand->m_data;
		}
		std::cout << std::endl;
		head_ptr = head_ptr->m_next;
	}
	std::cout << CYANE "Count: " NORM << Count << std::endl;
}