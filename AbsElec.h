/*Class AbsElec is the class abstarct class defines the election base things common for both types of election.*/

  //See all comments about methods in cpp file

#pragma once
#include <iostream>
#include "Party.h"
#include "District.h"
#include "Citizen.h"
#include "ConstTypes.h"
#include "DynamicArray.h"

namespace elc
{


	class AbsElec
	{
	protected:
		int _day;
		int _month;
		int _year;
		DynamicArray<Citizen*> voters;
		DynamicArray<Party*> parties; 
	
	public:
		AbsElec();
		AbsElec(int day, int month, int year);
		AbsElec(const AbsElec& other);
		virtual ~AbsElec();
		const AbsElec& operator=(const AbsElec& other);
		friend std::istream& operator>>(std::istream& is, AbsElec& elect);

		void display();
		virtual District* get_dist_by_id(int id) = 0;
		virtual void add_voter(const Citizen& person) = 0;
		virtual void add_district(const District& dis, int type) = 0;
		virtual void add_party(const Party& par) = 0;
		virtual void add_candidate(Citizen* person, Party* partyref, District* distref);
		virtual void add_vote(int citid, int partyid) = 0;


		void isExist(int id);
		Citizen* get_citizen_by_id(int id);

		int get_year();
		void printwinner();
		virtual void get_res() = 0;
		virtual void print_districts() = 0;
		void print_citizens();
		virtual void print_parties() = 0;

		Party* get_party_by_id(int id);

		virtual void save(std::ostream& out) const = 0;

		virtual void save_type(std::ostream& out) const = 0;
		virtual void save_dist_shallow(std::ostream& out) const = 0;
		virtual void save_dist_deep(std::ostream& out) const = 0;

		virtual void load(std::istream& in) = 0;

		friend class Citizen;
		friend class District;
		friend class Party;

	};
}