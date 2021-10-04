#ifndef MAPREDUCE_H_
#define MAPREDUCE_H_

#include "Map.h"
#include "Reduce.h"

#include <functional>
#include <string>



class MapReduce 
{
	char *InputPath;
	char *OutputPath;
	TMapFunction MapFunction;
	TReduceFunction ReduceFunction;
		
	vector<PtrMap> Mappers;
	vector<PtrReduce> Reducers;
	
	vector<pthread_t> ThreadsSplit;
	vector<pthread_t> ThreadsMap;
	vector<pthread_t> ThreadsReduce;


	public:
		MapReduce(char * input, char *output, TMapFunction map, TReduceFunction reduce, int nreducers=1);
		TError Run();

	private:
		TError Split(char *input);
		TError SplitParalell();
		TError Map();
		TError Suffle();
		TError Reduce();
		
		inline void AddMap(PtrMap map) { Mappers.push_back(map); };
		inline void AddReduce(PtrReduce reducer) { Reducers.push_back(reducer); };
		inline void AddThread(pthread_t thid, vector<pthread_t> pool) { pool.push_back(thid); };
		// inline void AddMapThread(p)
};
typedef class MapReduce TMapReduce, *PtrMapReduce;


#endif /* MAPREDUCE_H_ */
