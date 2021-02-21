#include "District.h"
#include "party.h"
#include "Citizen.h"
#include "Election.h"
#include "ConstTypes.h"
#include "ElectLoader.h"
#include "AbsElec.h"
#include "SimpeleElc.h"
#include "DynamicArray.h"
#include "fstream"
#include <iostream>
#include <string>
#include "Mainmenu.h"
using namespace std;

extern int minYear;

namespace elc
{

	Mainmenu::Mainmenu(AbsElec* _elect) : elect(*_elect), distid(-1), partyid(-1)
	{

		if (typeid(elect) == typeid(SimpleElec))
		{
			DevideDist dist;
			elect.add_district(dist, 2);
		}
	}

	Mainmenu::~Mainmenu()
	{

	}


	void Mainmenu::func1()
	{
		if (typeid(elect) == typeid(SimpleElec)) {
			cout << "Can't choose 1 in Divided district, please choose again:" << endl;
		}
		else {
			int type = 0;
			string name;
			int num;
			cin.ignore();
			cout << "enter name: ";
			getline(cin, name);
			cout << endl << "enter number of electors: ";
			cin >> num;
			cin.ignore();
			cout << endl << "enter type of district 1 for united 2 for divided:";
			cin >> type;
			while (type != static_cast<int>(DisType::NORMAL) && type != static_cast<int>(DisType::DIVIDED))
			{
				cout << "Wrong input- please enter 1 or 2 only:";
				cin >> type;
				cout << endl;
			}
			cin.ignore();

			if (type == static_cast<int>(DisType::NORMAL))
			{
				try
				{
					distid++;
					District dist(name, distid, num);
					elect.add_district(dist, type);
				}
				catch (const char* ex)
				{
					cout << ex << endl;
				}

			}

			else if (type == static_cast<int>(DisType::DIVIDED))
			{
				try
				{
					distid++;
					DevideDist dist(name, distid, num);
					elect.add_district(dist, type);
				}
				catch (const char* ex)
				{
					cout << ex << endl;
				}

			}

		}
	}
	void Mainmenu::func2()
	{
		string name;
		District* distref;
		int id;
		int yob;
		int distidofcit;
		cin.ignore();
		cout << "enter name: ";
		getline(cin, name);
		cout << endl << "enter id: ";
		cin >> id;
		cout << endl << "enter year of born: ";
		cin >> yob;

		try
		{
			if (typeid(elect) == typeid(Election))
			{
				cout << endl << "enter district id: ";
				cin >> distidofcit;
				cin.ignore();
				distref = elect.get_dist_by_id(distidofcit);
			}
			else distref = elect.get_dist_by_id(-3);


			Citizen person(id, name, yob, distref);
			elect.add_voter(person);

		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}
	}
	void Mainmenu::func3()
	{
		string name;
		Citizen* person;
		int id;
		cout << "enter name: ";
		cin.ignore();
		getline(cin, name);
		cout << endl << "enter id of head of the party: ";
		cin >> id;
		cin.ignore();
		try
		{
			person = elect.get_citizen_by_id(id);
			partyid++;
			Party party(name, person, partyid);
			elect.add_party(party);
		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}

	}
	void Mainmenu::func4()
	{
		Citizen* person;
		District* distref;
		Party* partyref;
		int id;
		int distidofcit;
		int partyIdofcit;
		cin.ignore();
		cout << "please enter id of party member: ";
		cin >> id;
		try
		{

			person = elect.get_citizen_by_id(id);
			cout << endl << "please enter id of the party: ";
			cin >> partyIdofcit;
			partyref = elect.get_party_by_id(partyIdofcit);
			if (typeid(elect) == typeid(Election))
			{
				cout << endl << "please enter id of district where the candidate will represent the party: ";
				cin >> distidofcit;
				distref = elect.get_dist_by_id(distidofcit);
			}
			else distref = elect.get_dist_by_id(-3);
			elect.add_candidate(person, partyref, distref);

		}
		catch (const char* ex)
		{
			cout << ex << endl;

		}

	}
	void Mainmenu::func5()
	{
		try
		{
			elect.print_districts();
		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}
	}
	void Mainmenu::func6()
	{
		elect.print_citizens();
	}
	void Mainmenu::func7()
	{
		elect.print_parties();

	}
	void Mainmenu::func8()
	{
		Party* partyref;
		int id, partyidofcit;
		cout << "please enter id of citizen:  ";
		cin >> id;
		cout << endl << "please id party:  ";
		cin >> partyidofcit;
		try
		{
			elect.isExist(id);
			partyref = elect.get_party_by_id(partyidofcit);
			elect.add_vote(id, partyidofcit);

		}
		catch (const char* ex)
		{
			cout << ex << endl;
			cin.ignore();

		}
	}
	void Mainmenu::func9()
	{
		try
		{
			elect.get_res();
		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}
	}


	void Mainmenu::func11()
	{
		std::cout << "Enter name of the file." << std::endl;
		string name;
		cin >> name;
		try
		{
			ofstream saveFile(name, ios::binary);
			elect.save(saveFile);
			saveFile.close();
		}
		catch (const ofstream::failure& ex)
		{
			cout << ex.what() << endl;
		}
	}


	Mainmenu* Mainmenu::func12()
	{
		std::cout << "Enter name of the file." << std::endl;
		string fileName;
		cin.ignore();
		getline(cin, fileName);
		try
		{
			ifstream loadFile(fileName);
			AbsElec* new_elect = ElectionLoader::loader(loadFile);
			new_elect->load(loadFile);
			loadFile.close();
			Mainmenu* new_round = new Mainmenu(new_elect);
			return new_round;
		}
		catch (const ifstream::failure& ex)
		{
			cout << ex.what() << endl;
		}
	}


	int Mainmenu::input()
	{
		int input;

		minYear = elect.get_year() - 18; // Do this constently, so even if serveral elections rounds was loaded minYear is up to date with current one
		elect.display();

		cin >> input;
		bool rangeFlag = false;
		while (!rangeFlag)
		{
			try
			{
				if (input > 12 || input < 0)
				{
					throw "Error input, please choose again. ";
				}
				else rangeFlag = true;
			}
			catch (const char* ex)
			{
				cout << ex << endl;
				cin >> input;
			}
		}

		return input;
	}

}