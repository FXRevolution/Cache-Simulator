// SIM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cache.h"
#include "CacheBlock.h"
#include "Set.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>


using namespace std;
using namespace project;

void printReport(int hits, int misses, Cache* cache);


int main(int argc, char* argv[])
{

	clock_t begin = clock();

	ifstream memoryAccesses;		//Trace File

	long cache_size,
		associativity,
		replacement,
		writeback,
		number_of_sets,
		blocks_per_set,
		hits = 0,
		misses = 0,
		set_number,
		indexMax;

	string	fileURL,
			fileLine;
	
	unsigned long long	address,
						tag,
						counter = 0;

	char accessType;	// R for read W for write

	int num_index_bits,				//bits in the index column
		blockIndex,					//position of block in the set
		block_offset_bits = (int)log2(BLOCKSIZE);		//based on blocksize;


	/*
	parse the arguments and initialize cache_size, associativity, replacement, writeback policy, and file location
	*/
	for (int i = 1; i < argc; i++)
	{
		if (i == 1)
			cache_size = stoi(argv[i]);
		if(i==2)
			associativity = stoi(argv[i]);
		if(i==3)
			replacement = stoi(argv[i]);
		if(i==4)
			writeback = stoi(argv[i]);
		if (i == 5)
			fileURL = argv[i];
	}

	blocks_per_set = associativity;

	number_of_sets = cache_size / (associativity*BLOCKSIZE);

	Cache* cache = new Cache(number_of_sets, replacement, blocks_per_set, writeback);

	memoryAccesses.open(fileURL);		//open Trace file

	num_index_bits = (int)log2l(number_of_sets);	//number of bits needed to count the sets

	indexMax = (long)pow(2, num_index_bits) - 1;	//used to get the set number from the address
		
	
	/*
	if file not found exit the program
	remeber to use \\ when entering file location
	fileURL string takes into account escape characters
	*/
	if (!memoryAccesses) 
	{

		cerr << fileURL << " Unable to open file datafile.txt" << endl;
		exit(1);   // call system to stop
	}

	/*
	parse the string
	*/
	while (memoryAccesses >> fileLine)
	{
		counter++;
		
		//every odd string is the access type Read or Write
		if(counter%2==1)
			accessType = fileLine[0];

		//for every even string get the address
		if (counter % 2 == 0)
		{
			address = (unsigned long long)strtoll(fileLine.c_str(), 0, 16);

			//remove the byte offset
			address = address >> block_offset_bits;
			//get the set number from the adress
			set_number = address & indexMax;
			//remove the index bits to get the tag
			tag = address >> num_index_bits;

			//first check if the block is in the cache
			blockIndex = cache->checkBlockIsCached(tag, set_number);
			
			/*
			if not in the cache add the tag to the cache to the head of the set
			this is a cache miss
			*/
			if (blockIndex == NOT_IN_CACHE)
			{
				if (accessType == 'R')
					cache->readNewBlock(tag, set_number);
				if (accessType == 'W')
					cache->writeNewBlock(tag, set_number);

				misses++;
			}

			/*
			if its in the cache, LRU replacement requires moving the block to the head of the set
			add memory reads and writes
			this is a hit
			*/
			else
			{
				hits++;

				if (replacement == LRU)
				{
					if(accessType == 'W' && writeback==WRITEBACK)
						cache->moveBlockToHead(blockIndex, tag, set_number, 1);
					else
						cache->moveBlockToHead(blockIndex, tag, set_number, cache->getSets()[set_number]->getBlocksVector()[blockIndex]->getDirty());
				}
				if (accessType == 'W' && writeback==WRITETHROUGH)
				{
					cache->incrementMemWrites();
				}
			}


			
		}

	}

	printReport(hits, misses, cache);


	clock_t end = clock();

	cout << (double)(end - begin) / CLOCKS_PER_SEC << endl << endl;

	return 0;
}



void printReport(int hits, int misses, Cache* cache)
{
	auto sets = cache->getSets();

	cout << endl << " Hits = " << dec << hits << " Misses = " << misses << endl;
	cout << " Hit Ratio = " << (double)hits / (double)(hits + misses) << endl;
	cout << " Miss Ratio = " << (double)misses / (double)(misses + hits) << endl;
	cout << " Memory Writes = " << cache->getMemWrites() << endl;
	cout << " Memory Reads = " << cache->getMemReads() << endl << endl;
}