#include "stdafx.h"
#include "Set.h"

namespace project
{
	/*
	initiate the set object
	create a set vector with the specified number of blocks
	*/
	Set::Set(long int count, long int set)
	{
		blockCount = count;
		setNum = set;

		for (int i = 0; i < count; i++)
		{
			blocks.push_back(new CacheBlock(i, set, 0));
		}
	}


	Set::~Set()
	{
	}
}