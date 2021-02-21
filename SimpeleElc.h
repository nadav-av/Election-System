/*Class SimpleElec defines an elecition instance which fits for simple election round as defined in excersice defenitions.*/

  //See all comments about methods in cpp file

#pragma once
#include <iostream>
#include "Party.h"
#include "District.h"
#include "Citizen.h"
#include "ConstTypes.h"
#include "Election.h"
#include "AbsElec.h"



namespace elc
{
	class SimpleElec : public AbsElec
	{
	private:
		DevideDist* country; //having a sub divided districts- contain all the citizen -> basicly its the wholoe country

	public:
		SimpleElec();
		SimpleElec(int day, int month, int year);
		SimpleElec(const SimpleElec& other);
		~SimpleElec();
		const SimpleElec& operator=(const SimpleElec& other);
		District* get_dist_by_id(int id);
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


		friend class DevideDist;
	};
}