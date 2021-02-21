/*Class Election defines an elecition instance which fits for normal election round as defined in excersice defenitions.*/


  //See all comments about methods in cpp file

#pragma once
#include <iostream>
#include "Party.h"
#include "District.h"
#include "Citizen.h"
#include "ConstTypes.h"
#include "AbsElec.h"
#include "DynamicArray.h"


namespace elc
{

	class Election : public AbsElec
	{
		protected:
		DynamicArray<District*> districts; //Array containing all pointers to ditsricts of country
		

		public:

			Election();
			Election(int day, int month, int year);
			Election(const Election& other);
			~Election();
			const Election& operator=(const Election& other);
			District* get_dist_by_id(int id) ;
			void add_voter(const Citizen& person);
			void add_district(const District& dis, int type);
			void add_party(const Party& par);
			void add_vote(int citid, int partyid);

			void get_res();
			void print_districts();
			void print_parties();


			virtual void save(std::ostream& out) const;
			virtual void save_type(std::ostream& out) const;
			virtual void save_dist_shallow(std::ostream& out) const;
			virtual void save_dist_deep(std::ostream& out) const;
			virtual void load(std::istream& in);


	};

}

