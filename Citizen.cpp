#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "District.h"
#include "Election.h"
#include "DynamicArray.h"
#include "ConstTypes.h"
#include <iostream>
#include <string>

extern int minYear;
using namespace std;

namespace elc
{
	/* ====================================================================== Ctor`s & Dtor ====================================================================== */
	//Ctor (-1 and null ptr for controlling purposes when adding to Election fields.
	Citizen::Citizen()
	{
		_id = -1;
		_yob = -1;
		_district = nullptr;
		_voted = false;
	}

	//Ctor (overloading)
	Citizen::Citizen(int id, string name, int yob, District* dist)
	{
		_id = id;
		this->id_exception();
		_yob = yob;
		if (_yob > minYear)
			throw "Citizen is too young, and cannot be added.";
		if (_yob < 0)
			throw "Year of born cannot be negetive number.";
		_district = dist;
		_name = name;
		_voted = false;
	}

	//Copy Ctor
	Citizen::Citizen(const Citizen& other)
	{
		*this = other;
	}

	//Dtor
	Citizen::~Citizen()
	{

	}

	/* ================================================================== Operators Overloading ================================================================== */
	
	//= Operator overloading
	Citizen& Citizen::operator=(const Citizen& other)
	{
		_id = other._id;
		_yob = other._yob;
		_district = other._district;
		_voted = other._voted;
		_name = other._name;

		return *this;

	}

	std::ostream& operator<<(std::ostream& os, const Citizen& person)
	{
		os << "Id number: " << person.get_id() << " " << person.get_name() << " " << "Year of born: " << person.get_yob() << " ";
		if (person.get_district()->get_id() != -1) {
			cout << "District: " << person.get_district()->get_name();
		}
		cout << endl;
		return os;
	}

	/* ==================================================================== Getters & Setters ==================================================================== */

	District* Citizen::get_district() const
	{
		return _district;
	}

	int Citizen::get_id() const
	{
		return _id;
	}

	int Citizen::get_yob() const
	{
		return _yob;
	}

	const string Citizen::get_name() const
	{
		return _name;
	}


	const string Citizen::get_name()
	{
		return _name;
	}

	bool Citizen::get_voted()
	{
		return _voted;
	}

	void Citizen::set_voted()
	{
		_voted = true;
	}

	int Citizen::get_id()
	{
		return _id;
	}


	void Citizen::id_exception()
	{
		int temp = _id;
		int count=0;
		while (temp)
		{
			temp /= 10;
			count++;
		}
		if (count != 9)
			throw "ID number is wrong. Cannot add this voter.";

		return;
	}



	/* ==================================================================== Saving & Loading ===================================================================== */
	
	void Citizen::save(ostream& out) const
	{
		out.write(rcastcc(&_id), sizeof(_id));
		out.write(rcastcc(&_yob), sizeof(_yob));
		out.write(rcastcc(&_voted), sizeof(_voted));
		int distId = _district->get_id();
		out.write(rcastcc(&distId), sizeof(distId));
		size_t size = _name.size();
		out.write(rcastcc(&size), sizeof(size_t));
		out.write(rcastcc(_name.c_str()), _name.size());


	}

	void Citizen::load(istream& in, AbsElec& elect)
	{
		int distId = 0;
		size_t len = 0;
		in.read(rcastc(&_id), sizeof(_id));
		in.read(rcastc(&_yob), sizeof(_yob));
		in.read(rcastc(&_voted), sizeof(_voted));
		in.read(rcastc(&distId), sizeof(distId));
		_district = elect.get_dist_by_id(distId);
		in.read(rcastc(&len), sizeof(size_t));
		_name.resize(len);
		in.read(rcastc(&_name[0]), len);


	}

	
}


	

	

	

	

	


	
