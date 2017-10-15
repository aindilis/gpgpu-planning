/*
 * GPUCheck.h
 *
 *  Created on: 05.01.2010
 *      Author: sulewski
 */

#ifndef GPUCHECK_H_
#define GPUCHECK_H_

#define BITSETSIZE 255

#include "myModel.h"
#include <list>
#include <vector>
#include <cuda.h>
#include <cutil.h>

#define THREADS 512
#define VRAM (900*1024*1024)

using namespace std;

void GPUCheck(myModel * model);


bool checkGuards(unsigned char * state);
void checkGuardsPostfix(unsigned char * stateset,unsigned char * enabledset, unsigned int setSize,myModel * model);

unsigned int enableEffectsPostfix(unsigned char * childset, unsigned int setSize, myModel * model);

unsigned int getHashesGPU(unsigned char * hashes, unsigned int setSize,myModel * model);




#endif /* GPUCHECK_H_ */
