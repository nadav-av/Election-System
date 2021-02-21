#pragma once

//Class Citizen is the class define all citizens in the country which the elction take place in.
//See all comments about methods in cpp file

#include "District.h"
#include <iostream>


namespace elc
{
	class AbsElec;
	class Citizen
	{
	private:
		int _id;
		string _name;
		int _yob;
		District* _district;
		bool _voted; //boolean value to detemain if citizen already voted or not



	public:
		friend class Party;
		friend class District;
		friend class Election;

		friend std::ostream& operator<<(std::ostream& os, const Citizen& person);
		//Ctors and Dtors:
		Citizen();
		Citizen(int id, string name, int yob, District* dist);
		Citizen(const Citizen& other);
		~Citizen();

		//Operators:
		Citizen& operator=(const Citizen& other);
		District* get_district() const;
		int get_id();
		int get_id() const;
		int get_yob() const;
		const string get_name() const;
		const string get_name();
		bool get_voted();
		void set_voted();
		
		void id_exception();

		void save(std::ostream& out) const;
		void load(std::istream& in, AbsElec& elect);
	};
}