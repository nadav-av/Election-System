#include "ConstTypes.h"
#include <iostream>
#include "AbsElec.h"
#include "SimpeleElc.h"
#include "Election.h"
#include "DynamicArray.h"
#include <string>

using namespace std;

extern int minYear;
namespace elc
{

	/* ====================================================================== Ctor`s & Dtor ====================================================================== */
	AbsElec::AbsElec() : AbsElec(0, 0, 0) {}

	AbsElec::AbsElec(int day, int month, int year) : _day(day), _month(month), _year(year)
	{
		if (year < 0)
		{
			throw "Invalid Year.";
		}
		if (month > 12 || month < 1) throw "Invalid month.";
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day > 31 || day < 0) throw "Invalid day at the month.";
		}
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30 || day < 0) throw "Invalid day at the month.";
		}
		if (month == 2)
		{
			if( day > 28 || day < 0) throw "Invalid day at the month.";
		}

		minYear = year - 18;

	}

	AbsElec::AbsElec(const AbsElec& other)
	{
		*this = other;
	}
	/* ================================================================== Operators Overloading ================================================================== */
	
	const AbsElec& AbsElec::operator=(const AbsElec& other)
	{
		_day = other._day;
		_month = other._month;
		_year = other._year;

		if (other.voters.size() != 0) {
			voters = other.voters;
		}

		if (other.parties.size() != 0) {
			parties = other.parties;
		}

		return *this;
	}

	//>> operator overloading for std::cin
	std::istream& operator>>(std::istream& is, AbsElec& elect)
	{
		is >> elect._day >> elect._month >> elect._year;
		minYear = elect._year - 18;
		return is;
	}

	AbsElec::~AbsElec() {}
	
	/* ==================================================================== Getters & Setters ==================================================================== */
	
	Party* AbsElec::get_party_by_id(int id) {
		bool check = false;
		Party* temp = nullptr;
		int i = 0;
		while (!check) {
			if (id == parties[i]->get_id()) {
				temp = parties[i];
				check = true;
			}
			else
				i++;
		}
		if (!check)
			throw "This party does not exsists.";
		else return temp;
	}

	//returning citizen by its given id
	Citizen* AbsElec::get_citizen_by_id(int id)
	{
		
		for (int i = 0; i < voters.size(); i++)
		{
			if (voters[i]->get_id() == id)
				return voters[i];
		}
		throw "This person does not exsists in the citizens list. ";
	}


	int AbsElec::get_year()
	{
		return _year;
	}


	/* ==================================================================== Adding & Removing ==================================================================== */
	

	//Add a candidat (person) to a party and to district where he is working
	void AbsElec::add_candidate(Citizen* person, Party* partyref, District* distref)
	{
		partyref->add_cand(person, distref);
		distref->add_cand(person, partyref);
	}
	
	/* ====================================================================== Calculating ======================================================================== */
	
	//check if a Voter exist in voters array
	void AbsElec::isExist(int id)
	{
		bool check = false;
		int i = 0;
		while(!check && i<voters.size())
		{
			if (voters[i]->get_id() == id)
				check =  true;
			i++;
		}
		if (!check)
			throw "This Person does not exsits in the citizens list.";

		return;
	}
	
	/* ======================================================================== Printing ========================================================================= */

	void AbsElec::print_citizens()
	{
		if (voters.size() == 0)
			cout << "none.";
		else
		{
			for (int i = 0; i < voters.size(); i++)
			{
				std::cout << i + 1 << ". " << *(voters[i]);
			}
		}
		std::cout << std::endl;
	}

	//Print the order of places won in the national election
	void AbsElec::printwinner() {

		int i, j, index = 0, max, negative;
		Party* party = nullptr;
		for (i = 0; i < parties.size(); i++) {
			max = parties[i]->get_sumElectors();
			index = i;
			for (j = 0; j < parties.size(); j++)
			{
				if (max < parties[j]->get_sumElectors())
				{
					max = parties[j]->get_sumElectors();
					index = j;
				}
			}
			if (i == 0)
			{
				std::cout << std::endl << "====================================================================================" << std::endl << "The winner is: " << std::endl;
			}
			if (i == 1)
				std::cout << std::endl << "====================================================================================" << std::endl << "Other parties: " << std::endl;
			party = this->get_party_by_id(index);
			std::cout << "Party " << party->get_name() << " Got total of: " << party->get_sumofvotes() << " votes." << " Got total of: " << party->get_sumofrep() << " representives in all districts. And a total of " << parties[index]->get_sumElectors() << " electors." << std::endl;
			std::cout << "Party Leader: " << party->get_head() << std::endl;
			negative = party->get_sumElectors() * -1 - 1;
			int zero = party->get_sumofrep() * -1;
			party->add_won_electors(negative); //To find max between every party, sum of electors of a party that alrady was "maxed" goes to -1.
			party->set_sumofrep(zero); //Number of representives needs to be 0 before next check of result.
			index = 0;
		}

		for (i = 0; i < parties.size(); i++) {
			int zero = parties[i]->get_sumElectors() * -1;
			parties[i]->add_won_electors(zero);
		}
	}

	void AbsElec::display()
	{
		std::cout << "Please pick one of the following:" << std::endl;
		std::cout << "  1. Press 1 to add district. " << std::endl;
		std::cout << "  2. Press 2 to add citizen. " << std::endl;
		std::cout << "  3. Press 3 to add party. " << std::endl;
		std::cout << "  4. Press 4 add a party member. " << std::endl;
		std::cout << "  5. Press 5 to show all districts. " << std::endl;
		std::cout << "  6. Press 6 to show all citizens. " << std::endl;
		std::cout << "  7. Press 7 to show all parties. " << std::endl;
		std::cout << "  8. Press 8 to enter citizen vote. " << std::endl;
		std::cout << "  9. Press 9 to show current result. " << std::endl << std::endl;
		std::cout << "  10.Press 0 to finish this round, and exit the program. " << std::endl;
		std::cout << "  11.Save election round to file. " << std::endl;
		std::cout << "  12.Load round from file. " << std::endl;
	}
	
}
