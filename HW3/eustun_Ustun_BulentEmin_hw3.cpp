// Bulent Emin Ustun - 27822
#include "BST.h"
#include "AVL.h"
#include <string>
#include <sstream>
#include <chrono>

struct Contacts
{

	std::string name;
	std::string surname;
	std::string number;
	std::string city;
};

std::string Uppercase(std::string &s) // Turn every charachter to the uppercase
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

	std::cout << "Please enter the contact file name: ";
	std::cin >> contact_file_name;

	std::fstream input_file;

	input_file.open(contact_file_name);

	Contacts notFound;
	notFound.city = "notFound";
	notFound.name = "notFound";
	notFound.surname = "notFound";
	notFound.number = "notFound";

	std::cout << "Loading the phonebook into a BST." << std::endl;

	BinarySearchTree<Contacts> phone_contactsBST(notFound);

	std::string line;

	auto starting_time = std::chrono::high_resolution_clock::now();

	while (std::getline(input_file, line))
	{ // Reading file for creating the BST tree

		Contacts contact1;

		std::string _name, _surname, _number, _city;

		std::istringstream oneByone(line);

		oneByone >> _name >> _surname >> _number >> _city;

		contact1.name = Uppercase(_name);
		contact1.surname = Uppercase(_surname);
		contact1.number = _number;
		contact1.city = _city;

		phone_contactsBST.insert(contact1);
	}
	auto stopping_time = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time - starting_time);

	std::cout << "Phonebook creation in BST took " << time.count() << " milliseconds. . ." << std::endl;

	phone_contactsBST.isTreeBalanced();
	phone_contactsBST.numberOfsides();

	std::cout << "Loading the phonebook into an AVL." << std::endl;

	AvlTree<Contacts> phone_contactsAVL(notFound);

	std::string line2;
	input_file.clear();
	input_file.seekg(0);
	auto starting_time2 = std::chrono::high_resolution_clock::now();
	while (std::getline(input_file, line2))
	{ // Reading file for creating the AVL tree

		Contacts contact2;

		std::string _name, _surname, _number, _city;

		std::istringstream oneByone(line2);

		oneByone >> _name >> _surname >> _number >> _city;

		contact2.name = Uppercase(_name);
		contact2.surname = Uppercase(_surname);
		contact2.number = _number;
		contact2.city = _city;

		phone_contactsAVL.insert(contact2);
	}
	auto stopping_time2 = std::chrono::high_resolution_clock::now();
	auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time2 - starting_time2);

	std::cout << "Phonebook creation in AVL took " << time2.count() << " milliseconds. . ." << std::endl;

	phone_contactsAVL.isTreeBalanced();
	phone_contactsAVL.numberOfsides();

	std::cout << std::endl;

	int choice;
	bool flag = true; // Checking condition for while loop, when user enters 6, the flag turns false.

	while (flag)
	{

		std::cout << "Choose which action to perform from 1 to 6:" << std::endl;
		std::cout << "1 - Search a phonebook contact" << std::endl;
		std::cout << "2 - Adding a phonebook contact" << std::endl;
		std::cout << "3 - Deleting a phonebook contact" << std::endl;
		std::cout << "4 - Print the phonebook to a file(inorder)" << std::endl;
		std::cout << "    Print the phonebook to a file (preorder)" << std::endl;
		std::cout << "5 - Draw the phonebook as a Tree to a file" << std::endl;
		std::cout << "6 - Press 6 to exit" << std::endl;

		std::cin >> choice;

		if (choice == 1)
		{ // Searching
			std::cout << std::endl;
			// BST PART
			std::string searchFor;

			std::cout << "Search for a contact: ";
			std::cin.clear();
			std::cin.seekg(0);
			std::getline(std::cin, searchFor);

			searchFor = Uppercase(searchFor);

			std::cout << std::endl;
			std::cout << "Searching an item in the phonebook (BST) . . .";
			std::cout << std::endl
					  << std::endl;
			std::cout << "Phonebook: Searching for: (" << searchFor << ")" << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			auto starting_time3 = std::chrono::high_resolution_clock::now();
			phone_contactsBST.find(searchFor);
			auto stopping_time3 = std::chrono::high_resolution_clock::now();
			auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time3 - starting_time3);
			std::cout << std::endl;

			// AVL PART

			std::cout << "Searching an item in the phonebook (AVL)  . . .";
			std::cout << std::endl
					  << std::endl;
			std::cout << "Phonebook: Searching for: (" << searchFor << ")" << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			auto starting_time4 = std::chrono::high_resolution_clock::now();
			phone_contactsAVL.find(searchFor);
			auto stopping_time4 = std::chrono::high_resolution_clock::now();
			auto time4 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time4 - starting_time4);
			std::cout << std::endl;

			std::cout << "The search in BST took " << time3.count() << " milliseconds. . ." << std::endl;
			std::cout << "The search in AVL took " << time4.count() << " milliseconds. . ." << std::endl
					  << std::endl;
		}

		else if (choice == 2)
		{ // Inserting
			std::cout << std::endl;
			std::cin.clear();
			std::cin.seekg(0);

			std::string nameAndSurname, phone_number, _city;
			std::cout << "Enter the information of the contact to be added: " << std::endl;
			std::cout << "Name: ";

			std::getline(std::cin, nameAndSurname);

			std::cout << std::endl;
			std::cout << "Tel: ";
			std::cin >> phone_number;
			std::cout << std::endl;
			std::cout << "City: ";
			std::cin >> _city;
			std::cout << std::endl;
			int onlyName = nameAndSurname.find(' ');

			std::string _name = nameAndSurname.substr(0, onlyName);
			std::string _surname = nameAndSurname.substr(onlyName + 1);

			Contacts new_contact;
			new_contact.name = Uppercase(_name);
			new_contact.surname = Uppercase(_surname);
			new_contact.number = phone_number;
			new_contact.city = _city;

			std::cout << "Adding an item to the phonebook BST..." << std::endl;
			std::cout << "---------------------------------------" << std::endl;
			std::cout << "---------------------------------------" << std::endl;
			std::cout << "Contact has been added successfully to the BST" << std::endl
					  << std::endl;

			auto starting_time5 = std::chrono::high_resolution_clock::now();
			phone_contactsBST.insert(new_contact);
			auto stopping_time5 = std::chrono::high_resolution_clock::now();
			auto time5 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time5 - starting_time5);

			std::cout << "Adding an item to the phonebook AVL..." << std::endl;
			std::cout << "---------------------------------------" << std::endl;
			std::cout << "---------------------------------------" << std::endl;
			std::cout << "Contact has been added successfully to the AVL Tree" << std::endl
					  << std::endl;

			auto starting_time6 = std::chrono::high_resolution_clock::now();
			phone_contactsAVL.insert(new_contact);
			auto stopping_time6 = std::chrono::high_resolution_clock::now();
			auto time6 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time6 - starting_time6);

			std::cout << "Adding a contact to the Binary Tree took " << time5.count() << " milliseconds. . ." << std::endl;
			std::cout << "Adding a contact to the AVL Tree took " << time6.count() << " milliseconds. . ." << std::endl
					  << std::endl
					  << std::endl;
		}

		else if (choice == 3)
		{ // Deleting

			std::cout << std::endl;
			std::cin.clear();
			std::cin.seekg(0);

			std::cout << "Deleting an item from the phonebook ..." << std::endl;
			std::cout << "Enter the fullname of the contact to be deleted: ";
			std::string name_delete;
			std::getline(std::cin, name_delete);
			std::cout << std::endl;
			name_delete = Uppercase(name_delete);

			auto starting_time7 = std::chrono::high_resolution_clock::now();
			phone_contactsBST.remove(name_delete);
			auto stopping_time7 = std::chrono::high_resolution_clock::now();
			auto time7 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time7 - starting_time7);

			auto starting_time8 = std::chrono::high_resolution_clock::now();
			phone_contactsAVL.remove(name_delete);
			auto stopping_time8 = std::chrono::high_resolution_clock::now();
			auto time8 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time8 - starting_time8);

			if (global_variable_is_in_tree != -1){
				std::cout << "Deletion from the Binary Tree took " << time7.count() << " milliseconds. . ." << std::endl;

				std::cout << "Deletion from the AVL Tree took " << time8.count() << " milliseconds. . ." << std::endl;
			}
			global_variable_is_in_tree = 0;

			std::cout << std::endl;
		}

		else if (choice == 4)
		{ // In order and Pre order

			std::cout << std::endl;

			phone_contactsBST.printTreeInOrder();

			phone_contactsAVL.printTreeInOrder();

			phone_contactsBST.printTreePreOrder();

			phone_contactsAVL.printTreePreOrder();

			std::cout << std::endl;
		}

		else if (choice == 5)
		{ // Draw Tree

			std::cout << std::endl;
			auto starting_time11 = std::chrono::high_resolution_clock::now();
			phone_contactsBST.drawTree();
			auto stopping_time11 = std::chrono::high_resolution_clock::now();
			auto time11 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time11 - starting_time11);

			auto starting_time12 = std::chrono::high_resolution_clock::now();
			phone_contactsAVL.drawTree();
			auto stopping_time12 = std::chrono::high_resolution_clock::now();
			auto time12 = std::chrono::duration_cast<std::chrono::milliseconds>(stopping_time12 - starting_time12);

			std::cout << "Drawing tree to file from the Binary Tree took " << time11.count() << " milliseconds. . ." << std::endl;
			std::cout << "Drawing tree to file from AVL Tree took " << time12.count() << " milliseconds. . ." << std::endl
					  << std::endl;
		}

		else if (choice == 6)
		{ // Terminating...
			std::cout << "Exiting the program..." << std::endl;
			break;
		}
	}

	phone_contactsAVL.makeEmpty();
	phone_contactsBST.makeEmpty();

	input_file.close();

	return 0;
}