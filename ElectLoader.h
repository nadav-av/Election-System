#pragma once
#include <iostream>
#include "District.h"
#include "Citizen.h"
#include "party.h"
#include "Election.h"
#include "AbsElec.h"
#include "SimpeleElc.h"
#include "DistrictLoader.h"
#include "ConstTypes.h"
using namespace std;


/*Class created to manage reading, allocationg and returning the correct successor from base abstract class AbsElc*/

namespace elc
{

	class ElectionLoader
	{
	public:

		static AbsElec* loader(istream& in)
		{
			ElecType type;
			AbsElec* elec = nullptr;
			int day, month, year;

			in.read(rcastc(&type), sizeof(type));
			
			/*Reading date here so no default Ctor will be activated and date will be invalid.*/
			in.read(rcastc(&day), sizeof(day));
			in.read(rcastc(&month), sizeof(month));
			in.read(rcastc(&year), sizeof(year));

			switch (type)
			{
			case elc::ElecType::NORMAL:
				try
				{
					elec = new Election(day, month, year);

				}
				catch (bad_alloc& ex)
				{
					cout << "Error with loading Election" << ex.what() << endl;
				}
				return elec;
				break;
			case elc::ElecType::SIMPLE:
				try
				{
					elec = new SimpleElec(day, month, year);

				}
				catch (bad_alloc& ex)
				{
					cout << "Error with loading Simple Election" << ex.what() << endl;
				}
				return elec;
				break;
			default:
				break;
			}
		}
	};
}
