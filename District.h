//Class District is the class define all Districts and DevideDist in the country where the election takes place.
//See all comments about methods in cpp file

#pragma once
#include <iostream>

#include "ConstTypes.h"
#include "DynamicArray.h"

namespace elc
{
	class AbsElec;
	class Citizen;
	class Party;
	struct represent
	{
		Party* party;
		Citizen* person;
	};

	struct kalpi
	{
		Party* party;
		int votes;
	};

	class District
	{
	protected:

		string _name;
		int _catNum; // id of the district
		int _electors;
		DynamicArray<Citizen*> _voters; 
		float _votingRate;
		DynamicArray<kalpi> _elected;
		DynamicArray<represent> cand;

	public:
		friend class Party;
		friend class Election;
		friend std::ostream& operator<<(std::ostream& os, const District& dist);

		District();
		District(string name, int catNum, int electors);
		District(const District& other);
		virtual ~District();
		District& operator=(const District& other);

		const int get_id() const;
		const string get_name() const;
		const int get_electors_num() const;
	
		void add_voter(Citizen* person);
		void add_cand(Citizen* person, Party* inparty);
		void add_party(Party* inparty);
		void add_election(Party* inparty);


		void set_rate();
		int get_hm_voted();
		Party* party_won();
		int get_electors();
		int calculate_hm_represents(int partyid);
		void print_chosen(int howmany, int partyid);
		int get_num_of_votes(int partyid);
		int get_precent_of_votes(int partyid);
		int get_rate();

		void print_rep(int partyid);


		virtual void give_electors();

		void save_shallow(District* dist, std::ostream& out) const;
		void save_deep(std::ostream& out) const;

		void load_shallow(std::istream& in, AbsElec& elect);
		void load_deep(std::istream& in, AbsElec& elect);



	};


	class DevideDist : public District //DevideDist have same fields, but its calculates and grants the electors differently
	{

	public:

		DevideDist();
		DevideDist(string name, int catNum, int electors);
		DevideDist(const DevideDist& other);
		DevideDist(const District& other);
		DevideDist& operator=(const DevideDist& other);
		~DevideDist();
		void country_set_electors();
		virtual void give_electors() override;


	};

}
