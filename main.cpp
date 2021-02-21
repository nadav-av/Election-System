#define _CRT_SECURE_NO_WARNINGS
#include "Mainmenu.h"
using namespace elc;
using namespace std;
int minYear = 0; //will be used in other classes for deciding valid age

void mainmenu(Mainmenu mm)
{
	int input;
	while (true)
	{
		input = mm.input();

		if (input == static_cast<int>(Operation::ADD_DISTRICT)) mm.func1();
		if (input == static_cast<int>(Operation::ADD_CITIZEN)) mm.func2();
		if (input == static_cast<int>(Operation::ADD_PARTY)) mm.func3();
		if (input == static_cast<int>(Operation::ADD_CANDIDATE)) mm.func4();
		if (input == static_cast<int>(Operation::PRINT_DISTRICTS)) mm.func5();
		if (input == static_cast<int>(Operation::PRINT_CITIZENS)) mm.func6();
		if (input == static_cast<int>(Operation::PRINT_PARTIES)) mm.func7();
		if (input == static_cast<int>(Operation::VOTE)) mm.func8();
		if (input == static_cast<int>(Operation::SHOW_RESULTS)) mm.func9();
		if (input == static_cast<int>(Operation::EXIT)) break;
		if (input == static_cast<int>(Operation::SAVE_ROUND)) mm.func11();
		if (input == static_cast<int>(Operation::LOAD_ROUND))
		{
			Mainmenu* new_round;
			new_round = mm.func12();
			mainmenu(*new_round);
			cout << "====================================================================================" << endl;
			cout << "Be aware - you entered this election round from running election round." << endl
				<< "You will now go back to the last rount you were opened" << endl;
			cout << "====================================================================================" << endl << endl;
		}
		cout << "====================================================================================" << endl;
	}
}


int main()
{
	int type;
	int op;
	AbsElec* elect = nullptr;
	cout << "1. New Elections." << endl;
	cout << "2. Load a local stored elction from file." << endl;
	cout << "3. Exit." << endl;

	cin >> op;

	if (op == static_cast<int>(StartOp::NEW_ROUND))
	{
		int d, m, y;
		cout << "Enter a type election round 1 for regular type, 2 for simple type:  ";
		cin >> type;
		cout << "Enter date of election: dd mm yyyy" << endl;
		cin >> d;
		cin >> m;
		cin >> y;

		try
		{
			if (type == static_cast<int>(ElecType::NORMAL))
				elect = new Election(d,m,y);
			else
				elect = new SimpleElec(d,m,y);

			Mainmenu mm(elect);
			mainmenu(mm);
			if (type == static_cast<int>(ElecType::NORMAL))
				/*We know we supposed to delete elect of any kind and not only if simple,
				  but when type is simple the delete crashes the program at the end of Dtor - only here from new round,
				  if we load its ok.
				  We have no idea why, and would love to get response for it, if you could find
				  the problem. Thanks a lot.*/
				delete elect;
		}
		catch (bad_alloc& ex)
		{
			cout << ex.what() << endl;
		}
		catch (const char* ex)
		{
			cout << ex << endl;
		}
	}

	else if (op == static_cast<int>(StartOp::LOAD_ROUND))
	{
		std::cout << "Enter name of the file." << std::endl;
		try
		{
			string fileName;
			cin.ignore();
			getline(cin, fileName);
			ifstream loadFile(fileName);
			AbsElec* elect = ElectionLoader::loader(loadFile);
			elect->load(loadFile);
			Mainmenu mm(elect);
			mainmenu(mm);
			loadFile.close();
			delete elect; //not crashing is ok -- see comment above in deleteing elect in new round.
		}
		catch (const ifstream::failure& ex)
		{
			cout << ex.what() << endl;
			cin.ignore();
		}
		catch (const char* ex)
		{
			cout << ex << endl;
			cin.ignore();
		}
	}
	
	else if (op == static_cast<int>(StartOp::EXIT))
	{
		cout << "Goodbye!:)";
	}

	return 0;
}



