#define _CRT_SECURE_NO_WARNINGS
#include "AbsElec.h"
#include "SimpeleElc.h"
#include "Election.h"
#include "Citizen.h"
#include "District.h"
#include "ConstTypes.h"
#include "Party.h"
#include <iostream>
#include "DistrictLoader.h"
#include "DynamicArray.h"
#include <string>


namespace elc
{

	/* ====================================================================== Ctor`s & Dtor ====================================================================== */
	//Ctor
	Election::Election(int day, int month, int year) : AbsElec(day, month, year)
	{

	}

	//Ctor (0,0,0 for controlling purposes)
	Election::Election() : Election(0, 0, 0) {}


	//Dtor
	Election::~Election()
	{
	}

	Election::Election(const Election& other)
	{
		*this = other;
	}

	/* ================================================================== Operators Overloading ================================================================== */
	
	const Election& Election::operator=(const Election& other) {

		AbsElec::operator=(other);

		if (other.districts.size() != 0)
		{
			districts = other.districts;
		}

		return *this;
	}

	/* ==================================================================== Getters & Setters ==================================================================== */

	District* Election::get_dist_by_id(int id) {
		bool check = false;
		District* temp = nullptr;
		int i = 0;
		while (!check) {
			if (id == districts[i]->get_id()) {
				temp = districts[i];
				check = true;
			}
			else
				i++;
		}
		if (check == false)
			throw "This district does not exsists.";
		return temp;
	}
	/* ==================================================================== Adding & Removing ==================================================================== */
	
	//adding voter to array
	void Election::add_voter(const Citizen& person)
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
		District* dist = person.get_district();

		dist->add_voter(cell); //go to the relevant district and add the citizen to its voters array
	}

	//adding district to array
	void Election::add_district(const District& dis, int type)
	{
		District* cell = nullptr;
		try
		{
			if (type == static_cast<int>(DisType::NORMAL))
			{
				cell = new District(dis);
			}
			if (type == static_cast<int>(DisType::DIVIDED))
			{
				cell = new DevideDist(dis);
			}

		}
		catch (bad_alloc& ex)
		{
			cout << "Error with adding new District to the array" << ex.what() << endl;
			return;
		}
		
		


		districts.push_back(cell);

		for (int i = 0; i < parties.size(); i++)
		{
			cell->add_party(parties[i]);
		}

	}

	//adding party to array
	void Election::add_party(const Party& par)
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


		for (int i = 0; i < districts.size();i++) //go to all the districts and add the party in its elected array
			districts[i]->add_party(cell);
	}


	//adding a vote (also checks if citizen already voted
	void Election::add_vote(int citid, int partyid)
	{

		DynamicArray<Citizen*>::iterator iter = voters.begin();
		DynamicArray<Citizen*>::iterator iterEnd = voters.end();

		for (; iter != iterEnd; iter++)
		{
			if ((*iter)->get_id() == citid)
			{

				if ((*iter)->get_voted())
					throw "Citizen already voted";

				else
				{
					(*iter)->set_voted();
					District* dist = (*iter)->get_district();
					Party* party = get_party_by_id(partyid);
					dist->add_election(party);
					parties[partyid]->set_sumofvotes(1);
				}

				iter = iterEnd; //so it will stop after this rounnd (in for loop - iter++ then != is false)
				iter--;
			}
		}
	}


	/* ==================================================================== Saving & Loading ===================================================================== */
	

	void Election::save(std::ostream& out) const
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


	void Election::save_type(std::ostream& out) const
	{
		ElecType type = ElecType::NORMAL;
		out.write(rcastcc(&type), sizeof(type));

	}

	void Election::save_dist_shallow(std::ostream& out) const
	{

		int dsize = districts.size();
		out.write(rcastcc(&dsize), sizeof(dsize));
		for (int i = 0; i < dsize; i++)
		{
			districts[i]->save_shallow(districts[i], out);
		}
	}

	void Election::save_dist_deep(std::ostream& out) const
	{
		int dsize = districts.size();
		for (int i = 0; i < dsize; i++)
		{
			districts[i]->save_deep(out);
		}
	}


	void Election::load(std::istream& in)
	{
		int dsize;
		in.read(rcastc(&dsize), sizeof(dsize));
		DynamicArray<District*> new_dist(dsize);
		districts = new_dist;
		districts.set_logic_size(dsize);
		for (int i = 0; i < dsize; i++)
		{
			districts[i] = DistrictLoader::load(in);
			districts[i]->load_shallow(in, *this);
		}

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
			catch (bad_alloc& ex)
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

		for (int i = 0; i < dsize; i++)
		{
			districts[i]->load_deep(in, *this);
		}

	}
	
	/* ======================================================================== Printing ========================================================================= */
	void Election::print_districts()
	{
		for (int i = 0; i < districts.size(); i++)
		{
			std::cout << i + 1 << ". " << *(districts[i]);
		}
		std::cout << std::endl;
	}


	void Election::print_parties()
	{
		if (parties.size() == 0)
			cout << "none." << endl;
		else
		{
			for (int i = 0; i < parties.size(); i++)
			{
				std::cout << std::endl << "====================================================================================" << std::endl << std::endl;
				std::cout << i + 1 << ". " << *(parties[i]) << std::endl;
				std::cout << "Districts representives: " << std::endl;
				for (int j = 0; j < districts.size(); j++)
				{
					std::cout << std::endl;
					std::cout << "District Name: " << districts[j]->get_name() << std::endl;
					districts[j]->print_rep(i);
				}
			}
		}
	
	}


	//Get result of all the election round by districts and by national order.
	void Election::get_res()
	{
		if (parties.size() == 0)
			throw "There is no parties yet, you need to add them in order to calculate results";
		if (districts.size() == 0)
			throw "There is no districts yet, you need to add them in order to calculate results";
		if (voters.size() == 0)
			throw "There is no citizens added yet, you need to add them in order to calculate results";

		for (int i = 0; i < districts.size(); i++)
		{
			std::cout << std::endl << "====================================================================================" << std::endl;
			districts[i]->set_rate();
			districts[i]->give_electors();
			for (int j = 0; j < parties.size(); j++)
			{
				int hm = districts[i]->calculate_hm_represents(j);
				parties[j]->set_sumofrep(hm);
				districts[i]->print_chosen(hm, j);
				int numofVotes = districts[i]->get_num_of_votes(j);
				int precent = districts[i]->get_precent_of_votes(j);
				int votingRate = districts[i]->get_rate();

				std::cout << "The party Got: " << numofVotes << " Votes which is " << precent << "% of the votes in the district, that had: " << votingRate << "% voting rate" << std::endl;
			}
		}

		printwinner();
	}


}
