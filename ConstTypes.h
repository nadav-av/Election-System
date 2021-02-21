#pragma once
namespace elc
{
	enum class Operation { EXIT = 0, ADD_DISTRICT = 1, ADD_CITIZEN, ADD_PARTY, ADD_CANDIDATE, PRINT_DISTRICTS, PRINT_CITIZENS, PRINT_PARTIES, VOTE, SHOW_RESULTS, SAVE_ROUND=11, LOAD_ROUND=12};
	enum class ElecType { NORMAL = 1, SIMPLE = 2 };
	enum class DisType { NORMAL = 1, DIVIDED = 2 };
	enum class StartOp { NEW_ROUND = 1, LOAD_ROUND =2 ,EXIT= 3 };
	
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

}