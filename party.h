//Class Party is the class define all Partys in the country which the elction take place in.
//See all comments about methods in cpp file
#pragma once
#include "Citizen.h"
#include "District.h"
#include "DynamicArray.h"

#include <iostream>

namespace elc
{
	class AbsElec;
	class Party
	{
		struct candidates
		{
			Citizen* cand;
			District* dist;
		};
	private:
		string _name;
		int _catNum; //id of the party
		DynamicArray<candidates> cand; 
		int sumOfElectors;
		int sumofrep;
		int sumofvotes;
	public:
		friend class District;
		friend class Election;
		friend std::ostream& operator<<(std::ostream& os, const Party& party);



		Party();
		Party(string name, Citizen* head, int catNum);
		~Party();
		Party(const Party& other);
		Party& operator=(const Party& other);
		int get_id() const;
		const string get_name() const;
		string get_name();
		const string get_head() const;
		void add_cand(Citizen* person, District* dist);

		void set_sumofvotes(int sum);
		void add_won_electors(int num);
		void set_sumofrep(int sum);
		int get_sumElectors() const;
		int get_sumofvotes() const;
		int get_sumofrep() const;

		void save(std::ostream& out) const;

		void load(std::istream& in, AbsElec& elect);
		
	};
}

