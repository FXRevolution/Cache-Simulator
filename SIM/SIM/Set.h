#pragma once
#include "CacheBlock.h"
#include <vector>
#include <time.h>
#include<iostream>

namespace project
{
	/*
	set object, there is a defined number of sets and set instances are not deleted
	holds a vector of block objects
	*/
	class Set
	{
	public:
		Set(long int count, long int set);
		~Set();

		/*
		inserts block at head of vector, removes the back
		*/
		int addToVectorHead(CacheBlock* block)
		{
			blocks.push_back(block);
			if (blocks.front()->getDirty())
			{
				blocks.erase(blocks.begin());
				return 1;
			}
			blocks.erase(blocks.begin());
			return 0;
		}

		/*
		inserts block to the head of the vector, doesn't remove the back
		*/
		void addToVectorHeadDontPop(CacheBlock* block)
		{
			blocks.push_back(block);
		}

		void removeBlock(int blockIndex)
		{
			blocks.erase(blocks.begin() + blockIndex);
		}

		std::vector<CacheBlock*> getBlocksVector()
		{
			return blocks;
		}

	private:
		long int setNum;
		long int blockCount;
		std::vector<CacheBlock*> blocks;
	};

}