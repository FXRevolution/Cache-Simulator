#pragma once

namespace project
{
/*
program constants and definitions
*/
#define BLOCKSIZE 64
#define LRU 0
#define FIFO 1
#define WRITETHROUGH 0
#define WRITEBACK 1
#define NOT_IN_CACHE -1

	/*
	Block object. differentiated by the bock tag.
	located in the set numbered in the onject
	each block maps to only one set
	block defines if it is valid or dirty when using writeback configuration
	*/
	class CacheBlock
	{
	public:
		CacheBlock(unsigned long long tg, int set, int val);
		~CacheBlock();

		long long getTag()
		{
			return tag;
		}

		long getSet()
		{
			return setNumber;
		}

		int getValidity()
		{
			return valid;
		}

		int getDirty()
		{
			return dirty;
		}

		void setDirty(int dirt)
		{
			dirty = dirt;
		}

		void setValidity(int val)
		{
			valid = val;
		}

	private:
		long long tag;
		long setNumber;
		int valid;
		int dirty;
	};

}