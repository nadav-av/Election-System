#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include "Election.h"
#include "District.h"
#include <iostream>
#include <cstdlib>
#include "DynamicArray.h"
#include <string>


using namespace std;

namespace elc
{


	/* ====================================================================== Ctor`s & Dtor ====================================================================== */
	//Ctor (-1 for controlling purposes)
	Party::Party()
	{
		_catNum = -1;
		sumOfElectors = 0;
		sumofrep = 0;
		sumofvotes = 0;

	}

	//Ctor

	Party::Party(string name, Citizen * head, int catNum)
	{
		_name = name;
		_catNum = catNum;
		candidates temp;
		temp.cand = head;
		temp.dist = head->get_district();
		cand.push_back(temp);
		sumOfElectors = 0;
		sumofrep = 0;
		sumofvotes = 0;
	}
	

	//Dtor
	Party::~Party()
	{
	
	}

	//Copy Ctor
	Party::Party(const Party& other)
	{
		*this = other;
	}
	/* ================================================================== Operators Overloading ================================================================== */

	//= Operator overloading
	Party& Party::operator=(const Party& other)
	{
		_name = other._name;
		_catNum = other._catNum;
		cand = other.cand;
		sumOfElectors = other.sumOfElectors;
		sumofrep = other.sumofrep;
		sumofvotes = other.sumofvotes;

		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Party& party)
	{
		os << "Party ID: " << party.get_id() << " " << "Party name: " << party.get_name() << " " << "Party leader: " << party.get_head() << std::endl;
		return os;
	}
	
	/* ==================================================================== Getters & Setters ==================================================================== */

	int Party::get_id() const {
		return _catNum;
	}

	const string Party::get_name() const {
		return _name;
	}

	string Party::get_name() {
		return _name;
	}

	const string Party::get_head() const {
		return cand[0].cand->get_name();
	}

	int Party::get_sumElectors() const
	{
		return sumOfElectors;
	}


	int Party::get_sumofvotes() const {

		return sumofvotes;
	}

	int Party::get_sumofrep() const {

		return sumofrep;
	}

	void Party::set_sumofvotes(int sum)
	{
		sumofvotes += sum;
	}

	void Party::add_won_electors(int num)
	{
		sumOfElectors += num;
	}

	void Party::set_sumofrep(int sum) {
		sumofrep += sum;
	}


	/* ==================================================================== Adding & Removing ==================================================================== */
	//this function will add a member of the party when it will be added in Election
	void Party::add_cand(Citizen* person, District* dist)
	{
		candidates temp;
		temp.cand = person;
		temp.dist = dist;

		cand.push_back(temp);

	}


	/* ==================================================================== Saving & Loading ===================================================================== */


	void Party::save(std::ostream& out) const
	{
		out.write(rcastcc(&_catNum), sizeof(_catNum));
		size_t len = _name.size();
		out.write(rcastcc(&len), sizeof(len));
		out.write(rcastcc(_name.c_str()), len);
		out.write(rcastcc(&sumOfElectors), sizeof(sumOfElectors));
		out.write(rcastcc(&sumofrep), sizeof(sumofrep));
		out.write(rcastcc(&sumofvotes), sizeof(sumofvotes));
		int csize = cand.size();
		out.write(rcastcc(&csize), sizeof(csize));
		for (int i = 0; i < csize; i++)
		{
			int candID = cand[i].cand->get_id();
			int distId = cand[i].dist->get_id();
			out.write(rcastcc(&candID), sizeof(candID));
			out.write(rcastcc(&distId), sizeof(distId));
		}

	}


	void Party::load(std::istream& in, AbsElec& elect)
	{
		in.read(rcastc(&_catNum), sizeof(_catNum));
		size_t len;
		in.read(rcastc(&len), sizeof(len));
		_name.resize(len);
		in.read(rcastc(&_name[0]), len);
		in.read(rcastc(&sumOfElectors), sizeof(sumOfElectors));
		in.read(rcastc(&sumofrep), sizeof(sumofrep));
		in.read(rcastc(&sumofvotes), sizeof(sumofvotes));
		int csize;
		in.read(rcastc(&csize), sizeof(csize));
		DynamicArray<candidates> new_cand(csize);
		cand = new_cand;
		cand.set_logic_size(csize);
		for (int i = 0; i < csize; i++)
		{
			int citiID;
			in.read(rcastc(&citiID), sizeof(citiID));
			int distId;
			in.read(rcastc(&distId), sizeof(distId));
			cand[i].cand = elect.get_citizen_by_id(citiID);
			cand[i].dist = elect.get_dist_by_id(distId);
		}
	}


}

	

	



	

	
	

	