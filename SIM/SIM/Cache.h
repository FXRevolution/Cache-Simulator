#pragma once
#include "Set.h"
#include <vector>
#include <cmath>
#include <iostream>


using namespace std;

namespace project
{
	/*
	cache object
	only one is created
	*/
	class Cache
	{
	public:
		Cache(long int setNum, int replacement, long int blockPS, int WB);
		~Cache();

		/*
		returns the index of a block is it is in the cache, otherwise returns -1
		*/
		int checkBlockIsCached(unsigned long long tag, long set_number)
		{
			auto blocks = sets[set_number]->getBlocksVector();

			for (int i = blocksPerSet-1; i >= 0; i--)
			{
				if (blocks[i]->getValidity() != 1)
					return -1;
				if (blocks[i]->getTag() == tag)
					return i;
			}

			return -1;
		}

		/*
		adds block to the cache if its a read operation
		*/
		void readNewBlock(unsigned long long tag, long set_number)
		{
			CacheBlock* block= new CacheBlock(tag, set_number, 1);
			memWrite += sets[set_number]->addToVectorHead(block);
			memRead++;
		}

		/*
		adds block to the cache if its a write operation
		*/
		void writeNewBlock(unsigned long long tag, long set_number)
		{
			CacheBlock* block = new CacheBlock(tag, set_number, 1);
			if (writeBack == WRITEBACK)
			{
				block->setDirty(1);
				memWrite += sets[set_number]->addToVectorHead(block);
				memRead++;
			}
			else
			{
				sets[set_number]->addToVectorHead(block);
				memRead++;
				memWrite++;

			}
		}

		/*
		for LRU replacement it moves the block to the head of the set vector
		*/
		void moveBlockToHead(int blockIndex, unsigned long long tag, long set_number, int dirty)
		{
			auto block = new CacheBlock(tag, set_number, 1);
			block->setDirty(dirty);
			
			sets[set_number]->removeBlock(blockIndex);
			sets[set_number]->addToVectorHeadDontPop(block);
			
			
		}

		void incrementMemWrites()
		{
			memWrite++;
		}

		long long getMemReads()
		{
			return memRead;
		}

		long long getMemWrites()
		{
			return memWrite;
		}

		vector<Set*> getSets()
		{
			return sets;
		}

	private:
		long long memRead, memWrite;
		long int number_of_sets;
		int replacementType;
		long int blocksPerSet;
		int writeBack;

		vector<Set*> sets;

	};

}