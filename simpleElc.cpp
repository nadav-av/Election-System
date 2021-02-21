#include "ConstTypes.h"
#include "DistrictLoader.h"
#include "AbsElec.h"
#include "SimpeleElc.h"
#include "Election.h"
#include <iostream>
#include "DynamicArray.h"
#include <string>


namespace elc
{



	/* ====================================================================== Ctor`s & Dtor ====================================================================== */
	SimpleElec::SimpleElec() : SimpleElec(0, 0, 0) {}

	SimpleElec::SimpleElec(int day, int month, int year) : AbsElec(day, month, year)
	{
		country = nullptr;
	}

	SimpleElec::SimpleElec(const SimpleElec& other)
	{
		*this = other;
	}

	SimpleElec::~SimpleElec()
	{
		delete country;
	}

	/* ================================================================== Operators Overloading ================================================================== */
	const SimpleElec& SimpleElec::operator=(const SimpleElec& other)
	{
		country = other.country;
		AbsElec::operator=(other);
		return *this;
	}
	/* ==================================================================== Getters & Setters ==================================================================== */

	District* SimpleElec::get_dist_by_id(int id) {

		return country;
	}

	/* ==================================================================== Adding & Removing ==================================================================== */
	void SimpleElec::add_voter(const Citizen& person)
	{

		Citizen* cell;
		try
		{
			cell = new Citizen(person);

		}
		catch (bad_alloc& ex)
		{
			cout << "Error with adding new citizen to the array" << ex.what() << endl;
			return;
		}

		voters.push_back(cell);

		country->add_voter(cell); //go to the relevant district and add the citizen to its voters array

	}
	void SimpleElec::add_party(const Party& par)
	{

		Party* cell;
		try
		{
			cell = new Party(par);

		}
		catch (bad_alloc& ex)
		{
			cout << "Error with adding new Party to the array" << ex.what() << endl;
			return;
		}
		
		parties.push_back(cell);

		country->add_party(cell);
	}

	void SimpleElec::add_district(const District& dis, int type)
	{
		if (country == nullptr) {

			try
			{
				country = new DevideDist[1];

			}
			catch (bad_alloc& ex)
			{
				cout << "Error with creating the 'Backstage' Districts which represent the whole country" << ex.what() << endl;
				return;
			}
		}
	}

	void SimpleElec::add_vote(int citid, int partyid) {

		for (int i=0;i<voters.size(); i++)
		{
			if ((voters[i])->get_id() == citid)
			{

				if (voters[i]->get_voted())
				{
					throw "Citizen already voted";
				}
			
				else
				{
					voters[i]->set_voted();
					Party* party = get_party_by_id(partyid);
					country->add_election(party);
					parties[partyid]->set_sumofvotes(1);
				}

				i= voters.size();
			}
		}
	}


	
	/* ==================================================================== Saving & Loading ===================================================================== */
	
	void SimpleElec::save(std::ostream& out) const
	{
		this->save_type(out);
		out.write(rcastcc(&_day), sizeof(_day));
		out.write(rcastcc(&_month), sizeof(_month));
		out.write(rcastcc(&_year), sizeof(_year));
		this->save_dist_shallow(out);

		int vsize = voters.size();
		out.write(rcastcc(&vsize), sizeof(vsize));
		for (int i = 0; i < vsize; i++)
		{
			voters[i]->save(out);
		}

		int psize = parties.size();
		out.write(rcastcc(&psize), sizeof(psize));
		for (int i = 0; i < psize; i++)
		{
			parties[i]->save(out);
		}

		this->save_dist_deep(out);
	}


	void SimpleElec::save_type(std::ostream& out) const
	{
		ElecType type = ElecType::SIMPLE;
		out.write(rcastcc(&type), sizeof(type));

	}

	void SimpleElec::save_dist_shallow(std::ostream& out) const
	{
		country->save_shallow(country, out);
	}

	void SimpleElec::save_dist_deep(std::ostream& out) const
	{
		country->save_deep(out);

	}


	void SimpleElec::load(std::istream& in)
	{
		country = dynamic_cast<DevideDist*>(DistrictLoader::load(in));
		country->load_shallow(in, *this);

		int vsize;
		in.read(rcastc(&vsize), sizeof(vsize));
		for (int i = 0; i < vsize; i++)
		{
			try
			{
				Citizen* person = new Citizen();
				person->load(in, *this);
				voters.push_back(person);
			}
			catch(bad_alloc& ex)
			{
				cout << ex.what() << endl;
			}
		
		}

		int psize;
		in.read(rcastc(&psize), sizeof(psize));
		for (int i = 0; i < psize; i++)
		{

			try
			{
				Party* par = new Party();
				par->load(in, *this);
				parties.push_back(par);
			}
			catch (bad_alloc& ex)
			{
				cout << ex.what() << endl;
			}
		
		}

		country->load_deep(in, *this);

	}
	
	
	/* ======================================================================== Printing ========================================================================= */
	//Get result of all the election round by districts and by national order.
	void SimpleElec::get_res()
	{

		std::cout << std::endl << "====================================================================================" << std::endl;
		country->country_set_electors();
		country->set_rate();
		country->give_electors();
		for (int j = 0; j < parties.size(); j++)
		{
			int hm = country->calculate_hm_represents(j);
			parties[j]->set_sumofrep(hm);
			country->print_chosen(hm, j);
			int numofVotes = country->get_num_of_votes(j);
			int precent = country->get_precent_of_votes(j);
			int votingRate = country->get_rate();

			std::cout << "The party Got: " << numofVotes << " Votes which is " << precent << "% of the votes in the whole country, that had: " << votingRate << "% voting rate" << std::endl;
		}


		printwinner();
	}

	void SimpleElec::print_districts()
	{
		throw "No districts in simple election round mode";
	}

	void SimpleElec::print_parties()
	{
		if (parties.size() == 0)
			cout << "none." << endl;
		else
		{
			for (int i = 0; i < parties.size(); i++)
			{
				std::cout << std::endl << "====================================================================================" << std::endl << std::endl;
				std::cout << i + 1 << ". " << *(parties[i]) << std::endl;
				std::cout << "Representives: " << std::endl;
				country->print_rep(i);

			}
		}
	
	}




	
}

	
	




