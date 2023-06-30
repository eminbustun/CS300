// Bulent Emin Ustun - 27822
// I did this homework using Visual Studio Code
#include "BST.h"
#include "HP.h"
#include <string>
#include <sstream>
#include <chrono>

class Contacts
{

public:
	std::string name;
	std::string surname;
	std::string number;
	std::string city;

	bool operator==(const Contacts &rhs) const // for hashing we need to overload it
	{

		return (this->name + this->surname == rhs.name + rhs.surname); 
	}

	bool operator!=(const Contacts &rhs) const // for hashing we need to overload it
	{

		return !(*this == rhs);
	}
};

std::string Uppercase(std::string &s) // Turn every charachter to the uppercase // same function I used in Homework_3
{
	int len = s.length();
	for (int k = 0; k < len; k++)
	{
		s[k] = toupper(s[k]);
	}

	return s;
}

int main()
{

	std::string contact_file_name;

	std::cout << "Enter the contact file name: ";
	std::cin >> contact_file_name;

	std::fstream input_file;

	input_file.open(contact_file_name);

	Contacts notFound;
	notFound.city = "notFound";
	notFound.name = "notFound";
	notFound.surname = "notFound";
	notFound.number = "notFound";

	HashTable<Contacts> phone_contactsHP(notFound);

	std::string line;

	while (std::getline(input_file, line))
	{

		Contacts contact1;

		std::string _name, _surname, _number, _city;

		std::istringstream oneByone(line);

		oneByone >> _name >> _surname >> _number >> _city;

		contact1.name = Uppercase(_name);
		contact1.surname = Uppercase(_surname);
		contact1.number = _number;
		contact1.city = _city;

		phone_contactsHP.insert(contact1);
	}

	std::cout << std::endl;
	phone_contactsHP.status();

	std::string line2;
	input_file.clear();
	input_file.seekg(0);

	BinarySearchTree<Contacts> phone_contactsBST(notFound);

	while (std::getline(input_file, line2))
	{ // Reading file for creating the BST tree

		Contacts contact1;

		std::string _name, _surname, _number, _city;

		std::istringstream oneByone(line2);

		oneByone >> _name >> _surname >> _number >> _city;

		contact1.name = Uppercase(_name);
		contact1.surname = Uppercase(_surname);
		contact1.number = _number;
		contact1.city = _city;

		phone_contactsBST.insert(contact1);
	}

	std::cout << std::endl;

	int choice;
	bool flag = true; // Checking condition for while loop, when user enters 6, the flag turns false.

	while (flag)
	{

		std::cout << "Choose which action to perform from 1 to 4:" << std::endl;
		std::cout << "1 - Search a phonebook contact" << std::endl;
		std::cout << "2 - Adding a phonebook contact" << std::endl;
		std::cout << "3 - Deleting a phonebook contact" << std::endl;
		std::cout << "4 - Press 4 to exit" << std::endl;

		std::cin >> choice;

		if (choice == 1)
		{ // Searching
			std::cin.clear();
			std::cin.seekg(0);
			std::cout << std::endl;
			// BST PART
			std::string searchFor;

			std::cout << "Enter name to search for: ";

			std::getline(std::cin, searchFor);

			searchFor = Uppercase(searchFor);

			std::cout << std::endl;
			std::cout << "Searching for an item in the phonebook (BST) . . .";
			std::cout << std::endl;
			std::cout << "Phonebook: Searching for: (" << searchFor << ")" << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			std::cout << "------------------------------------------" << std::endl;

			phone_contactsBST.find(searchFor);

			int k = 500;
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < k; i++)
			{
				phone_contactsBST.findTIMING(searchFor);
			}
			auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

			BSTTime = std::chrono::duration_cast<std::chrono::milliseconds>(BSTTime);

			std::cout << std::endl;

			std::cout << "BST Search Time: " << BSTTime.count() / k << std::endl << std::endl;

			int a = searchFor.find(' ');

			std::string first = searchFor.substr(0, a);

			std::string second = searchFor.substr(a + 1);

			// HP PART

			searchFor = first + second;

			std::cout << "Searching for an item in the phonebook (HashTable)  . . .";
			std::cout << std::endl;
			std::cout << "Phonebook: Searching for: (" << first + " " + second << ")" << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			std::cout << "------------------------------------------" << std::endl;

			phone_contactsHP.search(searchFor);
			std::cout << std::endl;
			auto start_HP = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < k; i++)
			{
				phone_contactsHP.searchTIMING(searchFor);
			}
			auto HPTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start_HP);


			std::cout << "Hash Table Search Time: " << HPTime.count() / k << std::endl;

			

			double spedUp = double(BSTTime.count()) / HPTime.count();

			std::cout << "Sped Up: " << spedUp << std::endl;

			std::cout << std::endl;
		}

		if (choice == 2) // inserting
		{

			std::cin.clear();
			std::cin.seekg(0);

			std::cout << std::endl
					  << "Enter the information of the contact to be added: " << std::endl;

			std::string nameAndSurname;

			std::cout << "Name: ";
			std::getline(std::cin, nameAndSurname);
			std::cout << std::endl;

			std::string telNo;

			std::cout << "Tel: ";
			std::cin >> telNo;
			std::cout << std::endl;

			std::string city;

			std::cout << "City: ";
			std::cin >> city;
			std::cout << std::endl;

			int position = nameAndSurname.find(' ');

			std::string first = nameAndSurname.substr(0, position);

			std::string second = nameAndSurname.substr(position + 1);

			Contacts will_be_inserted;
			will_be_inserted.name = Uppercase(first);
			will_be_inserted.surname = Uppercase(second);
			will_be_inserted.number = telNo;
			will_be_inserted.city = city;

			std::cout << "Adding an item to the phonebook BST . . ." << std::endl;
			std::cout << "------------------------------------" << std::endl;
			std::cout << "------------------------------------" << std::endl;
			auto starting_time = std::chrono::high_resolution_clock::now();
			phone_contactsBST.insert(will_be_inserted);
			auto stopping_time = std::chrono::high_resolution_clock::now();
			auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(stopping_time - starting_time);
			std::cout << "Contact has been added successfully to the BST Tree" << std::endl
					  << std::endl;

			std::cout << "Adding an item to the phonebook (Hashtable) . . ." << std::endl;
			std::cout << "------------------------------------" << std::endl;
			std::cout << "------------------------------------" << std::endl;
			auto starting_time2 = std::chrono::high_resolution_clock::now();
			phone_contactsHP.insert(will_be_inserted);
			auto stopping_time2 = std::chrono::high_resolution_clock::now();
			auto time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stopping_time2 - starting_time2);
			std::cout << "Contact has been added successfully to the Hashtable" << std::endl
					  << std::endl;

			std::cout << "Adding a contact to the Binary Tree took " << time.count() << " nanoseconds . . ." << std::endl;
			std::cout << "Adding a contact to the Hashtable took " << time2.count() << " nanoseconds . . ." << std::endl
					  << std::endl;
		}

		if (choice == 3) // Deleting
		{

			std::cout << std::endl;
			std::cin.clear();
			std::cin.seekg(0);
			std::cout << "Deleting an item from the phonebook . . ." << std::endl;

			std::string nameToBeDeleted;

			std::cout << "Enter the full name of the contact to be deleted: ";
			std::getline(std::cin, nameToBeDeleted);
			std::cout << std::endl;
			nameToBeDeleted = Uppercase(nameToBeDeleted);

			auto starting_time3 = std::chrono::high_resolution_clock::now();

			phone_contactsBST.remove(nameToBeDeleted);

			auto ending_time3 = std::chrono::high_resolution_clock::now();
			auto time3 = std::chrono::duration_cast<std::chrono::nanoseconds>(ending_time3 - starting_time3);

			std::cout << std::endl;

			int a = nameToBeDeleted.find(' ');

			std::string first = nameToBeDeleted.substr(0, a);

			std::string second = nameToBeDeleted.substr(a + 1);

			// HP PART

			nameToBeDeleted = first + second;

			auto starting_time4 = std::chrono::high_resolution_clock::now();
			phone_contactsHP.deleteContact(nameToBeDeleted);
			auto ending_time4 = std::chrono::high_resolution_clock::now();
			auto time4 = std::chrono::duration_cast<std::chrono::nanoseconds>(ending_time4 - starting_time4);

			std::cout << "Deletion from the Binary Tree took " << time3.count() << " nanoseconds. . ." << std::endl;
			std::cout << "Deletion from the Hashtable took " << time4.count() << " nanoseconds . . ." << std::endl
					  << std::endl;
		}

		if (choice == 4)
		{
			flag = false;
			break;
		}
	}


	phone_contactsBST.makeEmpty();//  
								 // Clearing
	phone_contactsHP.clearAll();//

	return 0;
}
