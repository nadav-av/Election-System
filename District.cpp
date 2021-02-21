#define _CRT_SECURE_NO_WARNINGS
#include "District.h"
#include "party.h"
#include "Citizen.h"
#include "Election.h"
#include "DynamicArray.h"
#include <iostream>
#include <math.h>  
#include <string>

using namespace std;

namespace elc
{


	/* ====================================================================== Ctor`s & Dtor ====================================================================== */
	//Ctor
	District::District()
	{
		_catNum = -1;
		_electors = 0;
		_votingRate = 0;
	}

	//Ctor
	District::District(string name, int catNum, int electors) : _catNum(catNum), _electors(electors)
	{
		if (_electors <= 0)
			throw "Number of electors must be bigger than 1";
		_name = name;
		_votingRate = 0;
	}

	//Copy Ctor
	District::District(const District& other)
	{
		*this = other;
	}

	//Dtor
	District::~District()
	{

	}

	//Ctor
	DevideDist::DevideDist() : District()
	{
		_name = "Country";
	}


	//Ctor
	DevideDist::DevideDist(string name, int catNum, int electors) : District(name, catNum, electors) {}


	//Copy Ctor
	DevideDist::DevideDist(const DevideDist& other) : District(other) {}

	DevideDist::DevideDist(const District& other) : District(other) {}

	//Dtor
	DevideDist::~DevideDist() {}


	/* ================================================================== Operators Overloading ================================================================== */
	//= Operator overloading
	District& District::operator=(const District& other)
	{
		_name = other._name;
		_voters = other._voters;
		_votingRate = other._votingRate;
		_catNum = other._catNum;
		_electors = other._electors;
		_elected = other._elected;
		cand = other.cand;

		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const District& dist)
	{
		
		if (typeid(dist) == typeid(District))
			os << "District id: " << dist.get_id() << " " << "District name: " << dist.get_name() << ", Normal district." << endl
			<< "   Number of electors: " << dist.get_electors_num() << endl << endl;
		
		else
		{
			os << "District id: " << dist.get_id() << " " << "District name: " << dist.get_name() << ", Devided district." << endl
			<< "   Number of electors: " << dist.get_electors_num() << endl << endl;
		}
		return os;
	}

	//= Operator overloading
	DevideDist& DevideDist::operator=(const DevideDist& other)
	{

		District::operator=(other);
		return *this;
	}

	void DevideDist::country_set_electors()
	{
		_electors = cand.size();
	}

	/* ==================================================================== Getters & Setters ==================================================================== */
	
	const int District::get_id() const
	{
		return _catNum;
	}

	const string District::get_name() const
	{
		return _name;
	}

	const int District::get_electors_num() const
	{
		return _electors;
	}


	void District::set_rate()
	{
		int count = this->get_hm_voted();
		_votingRate = (count * 100) / _voters.size();
	}


	int District::get_hm_voted()
	{
		int count = 0;
		for (int i = 0; i < _voters.size(); i++)
		{
			if (_voters[i]->_voted)
				count++;
		}
		return count;
	}

	int District::get_electors()
	{
		return _electors;
	}
	
	/* ==================================================================== Adding & Removing ==================================================================== */
	//This function add a voter to the district object (will be called from Election)
	void District::add_voter(Citizen* person)
	{
		_voters.push_back(person);
	}

	//If party was added this function will add it to _elected array as a cell to count votes in
	void District::add_party(Party* inparty)
	{
		kalpi temp;
		temp.party = inparty;
		temp.votes = 0;
		_elected.push_back(temp);
	}

	//adding a represent to the district
	void District::add_cand(Citizen* person, Party* inparty)
	{
		represent temp;
		temp.person = person;
		temp.party = inparty;
		cand.push_back(temp);
	}

	//when a citizen in the district votes we add its vote in _elected (will be called from election)
	void District::add_election(Party* inparty)
	{
		for (int i=0;i<_elected.size();i++)
		{
			if (_elected[i].party == inparty)
			{
				_elected[i].votes++;
				i = _elected.size();
			}
		}

	}

	
	/* ====================================================================== Calculating ======================================================================== */
	//Check and returns which party won
	Party* District::party_won()
	{
		int max = _elected[0].votes;
		int index = 0;
		Party* win = _elected[0].party;


		for (int i = 1; i < _elected.size(); i++)
		{
			if (max < _elected[i].votes)
			{
				max = _elected[i].votes;
				win = _elected[i].party;
			}
		}

		return win;
	}


	//calculate how many representive from given party is elected to this district
	int District::calculate_hm_represents(int partyid)
	{

		if (_votingRate != 0) {
			float sumOfVotes = (_votingRate * _voters.size()) / 100;
			sumOfVotes= round(sumOfVotes);
			float aux = (_elected[partyid].votes * 100) / sumOfVotes;
			float num = (_electors * aux) / 100;
			num = round(num);
			return num;
		}
		else
			return 0;
	}

	int District::get_num_of_votes(int partyid)
	{
		int i = 0;
		while (_elected[i].party->get_id() != partyid)
			i++;

		return _elected[i].votes;
	}


	int District::get_precent_of_votes(int partyid)
	{
		int i = 0;
		int sum_of_votes = this->get_hm_voted();
		while (_elected[i].party->get_id() != partyid)
			i++;

		if (_voters.size() != 0) {
			int num = _elected[i].votes;
			return num * 100 / sum_of_votes;
		}
		else return 0;
	}

	int District::get_rate()
	{
		return _votingRate;
	}


	void District::give_electors()
	{
		Party* party = this->party_won();
		party->add_won_electors(_electors);
		cout << "From District: " << this->get_name() << " " << this->get_electors() << " Electors will go to: " << party->get_name() << endl;
	}

	void DevideDist::give_electors()
	{
		for (int i = 0; i < _elected.size(); i++)
		{
			int partyid = _elected[i].party->get_id();
			float prec = this->get_precent_of_votes(partyid);
			float electors = (prec / 100) * _electors;
			electors = round(electors);
			_elected[i].party->add_won_electors(electors);
			cout << "From: " << this->get_name() << " " << electors << " Electors will go to: " << _elected[i].party->get_name() << endl;
		}
	}
	/* ==================================================================== Saving & Loading ===================================================================== */
	
	void District::save_shallow(District* dist, ostream& out) const
	{

		if (typeid(*dist) == typeid(District))
		{
			DisType type = DisType::NORMAL;
			out.write(rcastcc(&type), sizeof(type));
		}
		if (typeid(*dist) == typeid(DevideDist))
		{
			DisType type = DisType::DIVIDED;
			out.write(rcastcc(&type), sizeof(type));
		}
		size_t size = _name.size();
		out.write(rcastcc(&size), sizeof(size_t));
		out.write(rcastcc(_name.c_str()), _name.size());
		out.write(rcastcc(&_catNum), sizeof(_catNum));
		out.write(rcastcc(&_electors), sizeof(_electors));
		out.write(rcastcc(&_votingRate), sizeof(_votingRate));
	}

	void District::load_shallow(istream& in, AbsElec& elect)
	{
		size_t len;
		in.read(rcastc(&len), sizeof(size_t));
		_name.resize(len);
		in.read(rcastc(&_name[0]), len);
		in.read(rcastc(&_catNum), sizeof(_catNum));
		in.read(rcastc(&_electors), sizeof(_electors));
		in.read(rcastc(&_votingRate), sizeof(_votingRate));
	}

	void District::save_deep(ostream& out) const
	{
		int vsize = _voters.size();
		out.write(rcastcc(&vsize), sizeof(vsize));									
		for (int i = 0; i < vsize; i++)
		{
			int citId = _voters[i]->get_id();
			out.write(rcastcc(&citId), sizeof(citId));

		}

		int esize = _elected.size();
		out.write(rcastcc(&esize), sizeof(esize));
		for (int j = 0; j < esize; j++)
		{
			int partyid = _elected[j].party->get_id();
			out.write(rcastcc(&partyid), sizeof(partyid));
			int votes = _elected[j].votes;
			out.write(rcastcc(&votes), sizeof(votes));
		}

		int csize = cand.size();
		out.write(rcastcc(&csize), sizeof(csize));
		for (int k = 0; k < csize; k++)
		{
			int partyid = cand[k].party->get_id();
			out.write(rcastcc(&partyid), sizeof(partyid));
			int citId = cand[k].person->get_id();
			out.write(rcastcc(&citId), sizeof(citId));
		}

	}


	void District::load_deep(istream& in, AbsElec& elect)
	{
		int vsize;
		in.read(rcastc(&vsize), sizeof(vsize));
		for (int i = 0; i < vsize; i++)
		{
			int citId;
			in.read(rcastc(&citId), sizeof(citId));
			_voters.push_back(elect.get_citizen_by_id(citId));
		}

		int esize;
		in.read(rcastc(&esize), sizeof(esize));
		DynamicArray<kalpi> new_elected(esize);
		_elected = new_elected;
		_elected.set_logic_size(esize);
		for (int j = 0; j < esize; j++)
		{
			int partyid;
			in.read(rcastc(&partyid), sizeof(partyid));
			_elected[j].party = elect.get_party_by_id(partyid);
			int votes;
			in.read(rcastc(&votes), sizeof(votes));
			_elected[j].votes = votes;
		}

		int csize;
		in.read(rcastc(&csize), sizeof(csize));
		DynamicArray<represent> new_cand(csize);
		cand = new_cand;
		cand.set_logic_size(csize);
		for (int k = 0; k < csize; k++)
		{
			int partyid;
			in.read(rcastc(&partyid), sizeof(partyid));
			cand[k].party = elect.get_party_by_id(partyid);
			int citId;
			in.read(rcastc(&citId), sizeof(citId));
			cand[k].person = elect.get_citizen_by_id(citId);
		}

	}
	
	/* ======================================================================== Printing ========================================================================= */

	//Print the chosen electors out of cand (only the ones that got elected to represent- by order)
	void District::print_chosen(int howmany, int partyid)
	{
		int i = 0, counter = 0;
		std::cout << endl;
		Party* party = nullptr;
		for (int j = 0; j < _elected.size(); j++)
		{
			if (_elected[j].party->get_id() == partyid)
				party = _elected[j].party;
		}
		std::cout << "The representatives of party " << party->get_name() << ":" << std::endl;
		while (counter < howmany && i < cand.size())
		{
			if (cand[i].party->get_id() == partyid) {
				std::cout << counter + 1 << ". " << cand[i].person->get_name() << std::endl;
				counter++;
			}

			i++;
		}
		if (counter == 0)
			std::cout << "none." << std::endl;

	}

	//Prints all potential reprisentives of the district
	void District::print_rep(int partyid)
	{
		bool check = false;
		int count = 1;
		for (int i = 0; i < cand.size(); i++)
		{
			if (cand[i].party->get_id() == partyid)
			{
				std::cout << "               " << count << ". " << cand[i].person->get_name() << std::endl;
				count++;
				check = true;
			}
		}
		if (!check)
		{
			std::cout << "                  None." << std::endl;
		}
	}






}
