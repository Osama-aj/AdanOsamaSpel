//This is a game made by Osama & Adan.
//enjoy
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include<windows.h>
#include <cstdlib>
#include <algorithm>
using namespace std;


void stringToLower(string& str)//byt alla bokstäver till små bokstäver 
{
	int i = 0;
	while (str[i])
	{
		str[i] = tolower(str[i]);
		i++;
	}
}

//This are the enums that contains all the rooms, commands, and items for the game.
enum RoomsAndCommands
{
	bagIsEempty, hall1, livingRoom, kitchen, hall2, bathRoom, attic, cellar, searCh, bag, RedKey,
	Greenkey, HolyBook, Revolver, flashLight, Ladder, exIt, wronginput = 666
};
//Convert function in order to convert string to enum, used for the player commands.
RoomsAndCommands convert(const string& str)
{
	//These are the rooms.
	if (str == "hall1") return hall1;
	else if (str == "livingroom" || str == "living room") return livingRoom;
	else if (str == "kitchen") return kitchen;
	else if (str == "hall2") return hall2;
	else if (str == "bathroom") return bathRoom;
	else if (str == "attic") return attic;
	else if (str == "cellar") return cellar;

	//These are the items.
	else if (str == "green key") return Greenkey;
	else if (str == "red key") return RedKey;
	else if (str == "holy book") return HolyBook;
	else if (str == "revolver") return Revolver;
	else if (str == "flashlight") return flashLight;
	else if (str == "ladder") return Ladder;

	//These are the commands.
	else if (str == "bag") return bag;
	else if (str == "search") return searCh;
	else if (str == "empty") return bagIsEempty;
	else if (str == "exit") return 	exIt;
	else return wronginput;
}

//These are to check items and the obstacles in the game.
struct objekts_S
{
	bool foundOrNot = false;
}greenKey, redKey, holyBook, revolver, flashlight, ladder;

struct secondaryObjekts_S
{
	bool solved = false;
}attiDoor, treasureLock, ghost, monster, cellarIsDark, atticladder;

class TheHouse_t
{
public:
	//One function for each room.
	void hall1_t();
	void livingRoom_t();
	void kitchen_t();
	void hall2_t();
	void bathRoom_t();
	void attic_t();
	void cellar_t();

	//The function to switch rooms and interact with items.
	void doSomthing_t(int);
	void thingsToUse();
private:
};

//Our main variables.
string userInput;
TheHouse_t ourGame;
RoomsAndCommands userInputEnum = hall1;
int counter = 0;

int main()
{
	//The introduction text.
	char chosse[] = "Welcome to our game. Your goal is to find the treasure within the house you find yourself in.\n"
		"You will be able to perform actions by choosing an option from the menus presented to you.\n"
		"Select an option by writing the command within the brackets."
		"\nEnjoy.\n\n";

	for (int i = 0; chosse[i] != '\0'; i++) {
		Sleep(1);
		cout << chosse[i];
	}

	/*cout << "Welcome to our game. Your goal is to find the treasure within the house you find yourself in.\n" <<
		"You will be able to perform actions by choosing an option from the menus presented to you.\n"
		"Select an option by writing the command within the brackets."
		<< "\nEnjoy.\n\n";*/

	system("pause");
	ourGame.hall1_t(); //The game begins in the "main hall, hall1.
	while (true)
	{
		ourGame.doSomthing_t(userInputEnum);
	}
}

//Each room has its own function that contains options for the player to choose from, the answer is then converted and passed through a switch.
//Naturally, each room has its own set of options and switch.
void TheHouse_t::hall1_t()
{
	//Here's the description of the room, as well as the available options.
	cout << "\n" << "____________________________________________________________________________________________" << "\n" <<
		"\n" << "You are in the main hall." << "\n" <<
		"\n" << "What would you like to do?" << "\n"
		<< "\n" << "Search the room. [search]"
		<< "\n" << "Go to the living room. [livingroom]"
		<< "\n" << "Go up to the upper hall. [hall2]"
		<< "\n" << "Go down to the cellar. [cellar]"
		<< "\n" << "Open your bag. [bag]\n";

	//Here the answer, or command, is converted and then sent through the switch.
	getline(cin, userInput);
	stringToLower(userInput);//byt alla bokstäver till små bokstäver
	userInputEnum = convert(userInput);
	system("cls");
	switch (userInputEnum)
	{
	case livingRoom:
	case hall2:
	case exIt:
		cout << "\n" << "You leave the room." << "\n";
		break;
	case cellar:
		if (cellarIsDark.solved)
			cout << "\n" << "You leave the room." << "\n";
		else
		{
			cout << "\n" << "It is too dark down there. A light source is required." << "\n";
			userInputEnum = hall1;
		}
		break;
	case searCh:

		if (revolver.foundOrNot)
		{
			if (counter >= 2)
			{
				cout << "\n\n\n\tFU*K OFF\n\n\n\n";
				exit(1);
			}
			else
			{
				cout << "\n" << "You already found the revolver here. It is in your inventory." << "\n";
				counter++;
			}

		}
		else
		{
			cout << "\n" << "You found a revolver. It is now in your inventory." << "\n";
			revolver.foundOrNot = true;
		}
		userInputEnum = hall1;
		break;
	case bag:
		ourGame.thingsToUse();
		if (userInputEnum == flashLight && flashlight.foundOrNot)
		{
			if (!cellarIsDark.solved)
			{
				cout << "\n" << "You use the flashlight to light up the cellar." << "\n";
				cellarIsDark.solved = true;
				userInputEnum = cellar;
			}
			else
			{
				cout << "\n" << "The flashlight is already on." << "\n";
				userInputEnum = hall1;
			}

		}
		else if (userInputEnum == bagIsEempty)
		{
			cout << endl;
			userInputEnum = hall1;
		}
		else
		{
			cout << "\n" << "This item has no use in here." << "\n";
			userInputEnum = hall1;
		}
		break;
	case wronginput:
		cout << "\n" << "Wrong command." << "\n";
		userInputEnum = hall1;
		break;
	default:
		cout << "\n" << "Try one of the options." << "\n";
		userInputEnum = hall1;
		break;
	}
}

void TheHouse_t::livingRoom_t()
{
	cout << "\n" << "____________________________________________________________________________________________" << "\n" <<
		"\n" << "You are in the living room." << "\n" <<
		"\n" << "What would you like to do?" << "\n"
		<< "\n" << "Search the room. [search]"
		<< "\n" << "Go to the kitchen. [kitchen]"
		<< "\n" << "Go back to the main hall. [hall1]"
		<< "\n" << "Open your bag. [bag]\n";

	getline(cin, userInput);
	stringToLower(userInput);
	userInputEnum = convert(userInput);
	system("cls");
	switch (userInputEnum)
	{
	case kitchen:
	case hall1:
	case exIt:
		cout << "\n" << "You leave the room." << "\n";
		break;
	case searCh:
		if (flashlight.foundOrNot)
			cout << "\n" << "You already found the flashlight. It is in your inventory." << "\n";
		else
		{
			cout << "\n" << "You found a flashlight. It is now in your inventory." << "\n";
			flashlight.foundOrNot = true;
		}
		userInputEnum = livingRoom;
		break;
	case bag:
		ourGame.thingsToUse();
		if (userInputEnum == bagIsEempty)
		{
			cout << endl;
			userInputEnum = livingRoom;
		}
		else
		{
			cout << "\n" << "This item has no use in here." << "\n";
			userInputEnum = livingRoom;
		}
		break;
	case wronginput:
		cout << "\n" << "Wrong command." << "\n";
		userInputEnum = hall1;
	default:
		cout << "\n" << "Try one of the options." << "\n";
		userInputEnum = livingRoom;
		break;
	}
}

void TheHouse_t::kitchen_t()
{
	cout << "\n" << "____________________________________________________________________________________________" << "\n" <<
		"\n" << "You are in the kitchen." << "\n" <<
		"\n" << "What would you like to do?" << "\n"
		<< "\n" << "Search the room. [search]"
		<< "\n" << "Go back to the living room. [livingroom]"
		<< "\n" << "Open your bag. [bag]\n";

	getline(cin, userInput);
	stringToLower(userInput);
	userInputEnum = convert(userInput);
	system("cls");

	switch (userInputEnum)
	{
	case livingRoom:
	case exIt:
		cout << "\n" << "You leave the room." << "\n";
		break;
	case searCh:
		if (ladder.foundOrNot)
			cout << "\n" << "You already found the ladder. It is in your inventory." << "\n";
		else
		{
			cout << "\n" << "You found a ladder. It is now in your inventory." << "\n";
			ladder.foundOrNot = true;
		}
		userInputEnum = kitchen;
		break;
	case bag:
		ourGame.thingsToUse();
		if (userInputEnum == bagIsEempty)
		{
			cout << endl;
			userInputEnum = kitchen;
		}
		else
		{
			cout << "\n" << "This item has no use here." << "\n";
			userInputEnum = kitchen;
		}
		break;
	case wronginput:
		cout << "\n" << "Wrong command." << "\n";
		userInputEnum = hall1;
	default:
		cout << "\n" << "Try one of the options." << "\n";
		userInputEnum = kitchen;
		break;
	}
}

void TheHouse_t::hall2_t()
{
	cout << "\n" << "____________________________________________________________________________________________" << "\n" <<
		"\n" << "You are in the upper hall." << "\n" <<
		"\n" << "What would you like to do?" << "\n"
		<< "\n" << "Enter the bathroom. [bathroom]"
		<< "\n" << "Go back down to the main hall. [hall1]"
		<< "\n" << "Go up to the attic. [attic]"
		<< "\n" << "Open your bag. [bag]\n";

	getline(cin, userInput);
	stringToLower(userInput);
	userInputEnum = convert(userInput);
	system("cls");

	switch (userInputEnum)
	{
	case bathRoom:
	case hall1:
	case exIt:
		cout << "\n" << "You exit the room." << "\n";
		break;
	case attic:
		if (atticladder.solved)
		{
			if (attiDoor.solved)
				cout << "\n" << "You enter the attic." << "\n";
			else
			{
				cout << "\n" << "The door is locked. You require a key to open it." << "\n";
				userInputEnum = hall2;
			}
		}
		else
		{
			cout << "\n" << "The door is locked. You require a key to open it." << "\n";
			userInputEnum = hall2;
		}
		break;
	case bag:
		ourGame.thingsToUse();
		if (userInputEnum == Greenkey && greenKey.foundOrNot)
		{
			if (atticladder.solved)
			{
				if (!attiDoor.solved)
				{
					cout << "\n" << "You have opened the locked door to the attic." << "\n";
					attiDoor.solved = true;
					userInputEnum = hall2;
				}
				else
				{
					cout << "\n" << "It is already open." << "\n";
					userInputEnum = hall2;
				}

			}
			else
			{
				cout << "\n" << "You can't reach, it's too high up." << "\n";
				userInputEnum = hall2;
			}

		}
		else if (userInputEnum == Ladder && ladder.foundOrNot)
		{
			if (!atticladder.solved)
			{
				cout << "\n" << "You put the ladder down and reach the door, though it appears to be locked." << "\n";
				atticladder.solved = true;
				userInputEnum = hall2;
			}
			else
			{
				cout << "\n" << "You have already used the ladder." << "\n";
				userInputEnum = hall2;
			}

		}
		else if (userInputEnum == bagIsEempty)
		{
			cout << endl;
			userInputEnum = hall2;
		}
		else
		{
			cout << "\n" << "This item has no use here." << "\n";
			userInputEnum = hall2;
		}
		break;
	case wronginput:
		cout << "\n" << "Wrong command." << "\n";
		userInputEnum = hall1;
	default:
		cout << "\n" << "Try one of the options." << "\n";
		userInputEnum = hall2;
		break;
	}
}

void TheHouse_t::bathRoom_t()
{
	cout << "\n" << "____________________________________________________________________________________________" << "\n" <<
		"\n" << "You are in the bathroom." << "\n" <<
		"\n" << "What would you like to do?" << "\n"
		<< "\n" << "Search the room. [search]"
		<< "\n" << "Go back to the hall. [hall2]"
		<< "\n" << "Open your bag. [bag]\n";

	getline(cin, userInput);
	stringToLower(userInput);
	userInputEnum = convert(userInput);
	system("cls");

	switch (userInputEnum)
	{
	case hall2:
	case exIt:
		cout << "\n" << "You exit the room." << "\n";
		break;
	case searCh:
		if (greenKey.foundOrNot)
			cout << "\n" << "You have already searched this room." << "\n";
		else
		{
			cout << "\n" << "You find a green key. It is now in your inventory." << "\n";
			greenKey.foundOrNot = true;
		}

		userInputEnum = bathRoom;
		break;
	case bag:
		ourGame.thingsToUse();
		if (userInputEnum == bagIsEempty)
		{
			cout << endl;
			userInputEnum = bathRoom;
		}
		else
		{
			cout << "\n" << "This item has no use in here." << "\n";
			userInputEnum = bathRoom;
		}
		break;
	case wronginput:
		cout << "\n" << "Wrong command." << "\n";
		userInputEnum = hall1;
	default:
		cout << "\n" << "Try one of the options." << "\n";
		userInputEnum = bathRoom;
		break;
	}
}

void TheHouse_t::attic_t()
{
	cout << "\n" << "____________________________________________________________________________________________" << "\n" <<
		"\n" << "You are in the attic and you spot a monster." << "\n" <<
		"\n" << "What would you like to do?\n"
		<< "\n" << "Search the room. [search]"
		<< "\n" << "Go back to the hall. [hall2]"
		<< "\n" << "Open your bag. [bag]\n";

	getline(cin, userInput);
	stringToLower(userInput);
	userInputEnum = convert(userInput);
	system("cls");

	switch (userInputEnum)
	{
	case hall2:
	case exIt:
		cout << "\n" << "You leave the room." << "\n";
		break;
	case searCh:
		if (monster.solved)
		{
			if (redKey.foundOrNot || holyBook.foundOrNot)
				cout << "\n" << "You have already found the items in this room." << "\n";
			else
			{
				cout << "\n" << "You found a holy book and a red key. They are now in your inventory." << "\n";
				redKey.foundOrNot = true;
				holyBook.foundOrNot = true;
			}

			userInputEnum = attic;
		}
		else
		{
			cout << "\n" << "The monster wakes up and instantly charges at you." << "\n";
			cout << "\n" << "You are dead. GAME OVER." << "\n";
			exit(1);
		}
		break;
	case bag:
		ourGame.thingsToUse();

		if (!monster.solved)
		{
			if (userInputEnum == Revolver && revolver.foundOrNot)
			{
				cout << "\n" << "You use your revolver and shoot the monster. It dies instantly." << "\n";
				monster.solved = true;
				userInputEnum = attic;
			}
			else
			{
				cout << "\n" << "You try to fight the monster but your choice of weapon proves to be poor. It charges at you." << "\n";
				cout << "\n" << "You are dead. GAME OVER." << "\n";
				exit(1);

			}
		}
		else
		{
			cout << "\n" << "The monster is already dead." << "\n";
			userInputEnum = attic;
		}
		break;
	case wronginput:
		cout << "\n" << "Wrong command." << "\n";
		userInputEnum = hall1;
	default:
		cout << "\n" << "Try one of the options." << "\n";
		userInputEnum = attic;
		break;
	}
}

void TheHouse_t::cellar_t()
{
	cout << "\n" << "____________________________________________________________________________________________" << "\n" <<
		"\n" << "You are in the cellar. You spot a ghost and the treasure chest." << "\n" <<
		"\n" << "What would you like to do?" << "\n"
		<< "\n" << "Make a run for the treasure chest. [search]"
		<< "\n" << "Go back to the main hall. [hall1]"
		<< "\n" << "Open your bag. [bag]\n";

	getline(cin, userInput);
	stringToLower(userInput);
	userInputEnum = convert(userInput);
	system("cls");

	switch (userInputEnum)
	{
	case hall1:
	case exIt:
		cout << "\n" << "You leave the room." << "\n";
		break;
	case searCh:
		if (ghost.solved)
		{
			if (treasureLock.solved)
			{
				system("cls");
				cout << "\n" << "You open the chest. You find your treasure. You use it to buy dumb and expensive things, congratulations." << "\n";
				cout << "THE END. Thank you for playing." << "\n";
				exit(1);
			}
			else
			{
				cout << "\n" << "The chest is locked. You need a key to open it." << "\n";
				userInputEnum = cellar;
			}
		}
		else
		{
			system("cls");
			cout << "\n" << "The ghost howls and scares you to death." << "\n";
			cout << "\n" << "GAME OVER" << "\n";
			exit(1);
		}
		break;
	case bag:
		ourGame.thingsToUse();
		if (ghost.solved)
		{
			if (userInputEnum == RedKey && redKey.foundOrNot)
			{
				if (treasureLock.solved)
				{
					cout << "\n" << "It's already open." << "\n";
					userInputEnum = cellar;
				}
				else
				{
					cout << "\n" << "You've opened the chest." << "\n";
					treasureLock.solved = true;
					userInputEnum = cellar;

				}
			}
			else if (userInputEnum == HolyBook && holyBook.foundOrNot)
			{
				cout << "\n" << "The ghost is no longer in your way." << "\n";
				userInputEnum = cellar;
			}
			else
			{
				cout << "\n" << "This item has no use in here." << "\n";
				userInputEnum = cellar;
			}
		}
		else
		{
			if (userInputEnum == HolyBook && holyBook.foundOrNot)
			{
				cout << "\n" << "The ghost is horrified by the divine nature of your book, it backs away and grants you access to the chest." << "\n";
				ghost.solved = true;
				userInputEnum = cellar;
			}
			else
			{
				cout << "\n" << "The ghost howls and scares you to death." << "\n";
				cout << "\n" << "GAME OVER" << "\n";
				exit(1);
			}
		}
		break;
	case wronginput:
		cout << "\n" << "Wrong command," << "\n";
		userInputEnum = hall1;
	default:
		cout << "\n" << "Try one of the options." << "\n";;
		userInputEnum = cellar;
		break;
	}
}

void TheHouse_t::doSomthing_t(int choise)
{
	switch (choise)
	{
	case hall1:
		ourGame.hall1_t();
		break;
	case livingRoom:
		ourGame.livingRoom_t();
		break;
	case kitchen:
		ourGame.kitchen_t();
		break;
	case hall2:
		ourGame.hall2_t();
		break;
	case bathRoom:
		ourGame.bathRoom_t();
		break;
	case attic:
		ourGame.attic_t();
		break;
	case cellar:
		ourGame.cellar_t();
		break;
	case exIt:
		exit(0);
	default:
		break;
	}
}

//This is the inventory that holds the items, the "bag".
void TheHouse_t::thingsToUse()
{

	if (greenKey.foundOrNot || redKey.foundOrNot || holyBook.foundOrNot || revolver.foundOrNot || flashlight.foundOrNot || ladder.foundOrNot)
	{
		cout << "\n" << "Your bag contains the following items..." << "\n";
		if (greenKey.foundOrNot)
			cout << "\n" << "Green Key" << "\n";
		if (redKey.foundOrNot)
			cout << "\n" << "Red Key" << "\n";
		if (holyBook.foundOrNot)
			cout << "\n" << "Holy Book" << "\n";
		if (revolver.foundOrNot)
			cout << "\n" << "Revolver" << "\n";
		if (flashlight.foundOrNot)
			cout << "\n" << "Flashlight" << "\n";
		if (ladder.foundOrNot)
			cout << "\n" << "Ladder" << "\n";
		cout << "\n" << "Choose an item you'd like to use by writing its name." << "\n";
		getline(cin, userInput);
		stringToLower(userInput);
		userInputEnum = convert(userInput);
		system("cls");
	}
	else
	{
		cout << "\n" << "Your bag is empty." << "\n";
		userInputEnum = bagIsEempty;
	}
}
