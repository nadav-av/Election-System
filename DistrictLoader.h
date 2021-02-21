#pragma once
#include <iostream>
#include "District.h"
#include "Election.h"
#include "AbsElec.h"
#include "SimpeleElc.h"
#include "ConstTypes.h"
using namespace std;


/*Class created to manage reading, allocationg and returning the correct successor from District class*/


namespace elc
{
	class DistrictLoader
	{
	public:
		static District* load(istream& in)
		{
			District* res = nullptr;
			DisType type;
			in.read(rcastc(&type), sizeof(type));
			switch (type)
			{
			case elc::DisType::NORMAL:
				try
				{
					res = new District();

				}
				catch (bad_alloc& ex)
				{
					cout << "Error with loading District" << ex.what() << endl;
				}
				break;
			case elc::DisType::DIVIDED:
				try
				{
					res = new DevideDist();

				}
				catch (bad_alloc& ex)
				{
					cout << "Error with loading Devided District" << ex.what() << endl;
				}
				break;
			default:
				res = nullptr;
				break;
			}

			return res;
		}
	};
}
