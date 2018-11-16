#include "stdafx.h"
#include "Cache.h"

namespace project
{
	/*
	initiate the cache object
	create a set vector with the specified number of Sets
	*/
	Cache::Cache(long int setNum, int replacement, long int blockPS, int WB)
	{
		number_of_sets = setNum;
		replacementType = replacement;
		blocksPerSet = blockPS;
		writeBack = WB;
		memRead = 0;
		memWrite = 0;

		
		for (int i = 0; i < number_of_sets; i++)
		{
			sets.push_back(new Set(blocksPerSet, i));
		}
	}

	Cache::~Cache()
	{
	}


}