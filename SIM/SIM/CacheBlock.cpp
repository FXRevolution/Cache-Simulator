#include "stdafx.h"
#include "CacheBlock.h"

namespace project
{
	CacheBlock::CacheBlock(unsigned long long tg, int set, int val)
	{
		tag = tg;
		setNumber = set;
		valid = val;
		dirty = 0;
	}


	CacheBlock::~CacheBlock()
	{
	}

}