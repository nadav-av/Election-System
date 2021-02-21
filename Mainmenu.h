#include "District.h"
#include "party.h"
#include "Citizen.h"
#include "Election.h"
#include "ConstTypes.h"
#include "ElectLoader.h"
#include "AbsElec.h"
#include "SimpeleElc.h"
#include "DynamicArray.h"
#include "fstream"
#include <iostream>
#include <string>
using namespace std;

extern int minYear;

/*Class created to manage the basic functions of the election system*/

namespace elc
{

	class Mainmenu
	{
	public:
		AbsElec& elect;
		int distid;
		int partyid;

	public:
		Mainmenu(AbsElec* _elect);
		~Mainmenu();
		int input();
		void func1();
		void func2();
		void func3();
		void func4();
		void func5();
		void func6();
		void func7();
		void func8();
		void func9();
		void func11();
		Mainmenu* func12();
	};
}
