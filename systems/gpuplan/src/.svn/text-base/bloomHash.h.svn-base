
#ifndef BLOOMHASH_H_
#define BLOOMHASH_H_

#include "stdint.h" /* Replace with <stdint.h> if appropriate */
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
	  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
		                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

template <class T>
class bloomHash{
	private:
		unsigned int elementLength;
		vector<vector<unsigned long long>* > randoms; //vector of random numbers
		unsigned char bits[8]; //help vector for faster bitt access
		vector<char> boolHashtable;
		unsigned long long insertCounter;

		unsigned long long getHash(T element, unsigned long long * randomVec);
	public:		
		bloomHash(unsigned int elementLength);
		bool insert(T element);
		T getByPos(unsigned int pos, int * dst);
};

#include "bloomHash.cpp"

#endif //bloomHash
