#include "bloomHash.h"


template <class T> bloomHash<T>::bloomHash(unsigned int elementLength_){
	insertCounter = 0;
	elementLength = elementLength_;
	srand(time(0));
	for (int b = 0; b < NUMOFBITS; b++ ) {
		vector<unsigned long long> * rands = new vector<unsigned long long>();
		for (int i = 0; i < elementLength; i++ )	rands->push_back(rand());
		randoms.push_back(rands);
	}
	bits[0] = 128;
	bits[1] = bits[0]>>1;
	bits[2] = bits[1]>>1;
	bits[3] = bits[2]>>1;
	bits[4] = bits[3]>>1;
	bits[5] = bits[4]>>1;
	bits[6] = bits[5]>>1;
	bits[7] = bits[6]>>1;


	printf("reserving %llu GB for bithash table \n",HASHTABLESIZE/8/1024/1024/1024);
	boolHashtable.reserve(HASHTABLESIZE/8);
	memset(&boolHashtable[0],0,HASHTABLESIZE/8);
}

template <class T> unsigned long long bloomHash<T>::getHash(T state, unsigned long long * randomVec) {
	if(NUMOFBITS==0) return true;

#define jenkins
#ifdef jenkins
	unsigned long long largeprime = 3203431780337; //prime

	unsigned long long hash;

	hash = largeprime;
	for (int i = 0; i < elementLength; i++ ) hash ^= randomVec[i]*(state[i]+1);
	hash = hash % (HASHTABLESIZE);
	
#else //hsieh
	unsigned int len = elementLength;
	unsigned char * data = state;

	uint32_t hash = len, tmp;
	int rem;

	rem = len & 3;
	len >>= 2;


	/* Main loop */
	for (;len > 0; len--) {
		hash  += get16bits (data);
		tmp    = (get16bits (data+2) << 11) ^ hash;
		hash   = (hash << 16) ^ tmp;
		data  += 4;
		hash  += hash >> 11;
	}

	/* Handle end cases */
	switch (rem) {
		case 3: hash += get16bits (data);
						hash ^= hash << 16;
						hash ^= data[2] << 18;
						hash += hash >> 11;
						break;
		case 2: hash += get16bits (data);
						hash ^= hash << 11;
						hash += hash >> 17;
						break;
		case 1: hash += *data;
						hash ^= hash << 10;
						hash += hash >> 1;
	}

	/* Force "avalanching" of final 127 bits */
	hash ^= hash << 3;
	hash += hash >> 5;
	hash ^= hash << 4;
	hash += hash >> 17;
	hash ^= hash << 25;
	hash += hash >> 6;

#endif

	return hash;

}

template <class T> bool bloomHash<T>::insert(T element){
	if(NUMOFBITS==0) return true;

	unsigned long long hashes[NUMOFBITS];
	for (int b = 0; b < NUMOFBITS; b++) {
		hashes[b] = getHash(element,&(*randoms[b])[0]);
	}
	unsigned char b = 0;
	//unsigned int * hashes = (unsigned int *) longhashes;
	while (b < NUMOFBITS && 	(boolHashtable[hashes[b]>>3] & bits[hashes[b]&7] )) b++;
	if (b == NUMOFBITS) return false;

	insertCounter++;
	for (b = 0; b < NUMOFBITS; b++) boolHashtable[hashes[b]>>3] |= bits[hashes[b]&7];
	return true;
}

template <class T> T bloomHash<T>::getByPos(unsigned int pos, int * dst) {
	return NULL;
}

