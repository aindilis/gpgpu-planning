#include "cuda.h"
#include "GPUCheck.h"

#include "defines.h"

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
	  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((unsigned int)(((const unsigned char *)(d))[1])) << 8)\
		                       +(unsigned int)(((const unsigned char *)(d))[0]) )
#endif
#define tId  (blockIdx.x * blockDim.x + threadIdx.x)


__constant__ POSTFIX_EFFECTS_TYPE constant[63*1024/4];
__constant__ unsigned int sizetTransitions_GPU;
__constant__ POSTFIX_EFFECTS_TYPE pr; //postfix representation on the GPU
__constant__ POSTFIX_EFFECTS_TYPE pg; //postfix guards on the gpu
unsigned int cpu_pr;
unsigned int cpu_pg;
__device__ POSTFIX_EFFECTS_TYPE * pe; //postfix effects on the gpu
__device__ unsigned int * to; //transition offsetts on the gpu
__constant__ unsigned int stateSizeGPU;
__constant__ unsigned int checkSizeGPU;

__global__ void initKernel(POSTFIX_EFFECTS_TYPE pg_new, POSTFIX_EFFECTS_TYPE * pe_new, unsigned int pr_new, unsigned int * to_new) {
	//pg = pg_new;
	pe = pe_new;
//	pr = pr_new;
	to = to_new;
}
	
__device__ unsigned int getValue(unsigned char * state, unsigned int * type_stack, unsigned int * offset_stack, unsigned int depth){
	if (type_stack[depth] == CONSTANT) return offset_stack[depth];
	if (type_stack[depth] == VARIABLE_BYTE) return state[offset_stack[depth]>>3];
	return state[offset_stack[depth]>>3] & (unsigned char) 128 >> (offset_stack[depth]&7);
}

__device__ unsigned int evaluatePostfixGPU(unsigned char  * state,POSTFIX_EFFECTS_TYPE * postfix, unsigned int length, bool checkonly){
	if (!length) return true;
	unsigned int depth = 0;
	unsigned int postpos = 0;
	unsigned int type_stack[20];
	unsigned int offset_stack[20];
	unsigned int var1, var2 =0;

//	memset(type_stack,0,20*sizeof(int));
//	memset(offset_stack,0,20*sizeof(int));
	
	while (postpos < length) {
		//if (postfix[postpos] == CONSTANT || postfix[postpos] == VARIABLE_BYTE || postfix[postpos] == VARIABLE_BIT ) {
		if (postfix[postpos] == CONSTANT) {
			//printf("\n depth %i , storing type %i ",depth,postfix[postpos]);
			type_stack[depth] = postfix[postpos];
			offset_stack[depth] = postfix[postpos+1];
			depth++;
			postpos += 2;
			continue;
		}
		if (postfix[postpos] == VARIABLE_BYTE) {
			//printf("\n depth %i , storing type %i ",depth,postfix[postpos]);
			type_stack[depth] = postfix[postpos];
			offset_stack[depth] = postfix[postpos+1];
			depth++;
			postpos += 2;
			continue;
		}
		if (postfix[postpos] == VARIABLE_BIT ) {
			//printf("\n depth %i , storing type %i ",depth,postfix[postpos]);
			type_stack[depth] = postfix[postpos];
			offset_stack[depth] = postfix[postpos+1];
			depth++;
			postpos += 2;
			continue;
		}
		var2 = getValue(state,type_stack,offset_stack,depth-1);
		if (postfix[postpos] == ARRAY) {
			type_stack[depth-1] = VARIABLE_BYTE;
			offset_stack[depth-1] = postfix[postpos+1] + var2; //array offset + variable on stack
			//printf("\n array type_stack[%i] = VARIABLE_BYTE offset_stack = %i \n",depth-1,offset_stack[depth-1]);
			postpos += 2;
			continue;
		}
		else if (postfix[postpos] == ASSIGN){
			if (type_stack[depth-2] == VARIABLE_BYTE) 
				state[offset_stack[depth-2]>>3] = var2;
			else if (var2)
				state[offset_stack[depth-2]>>3] += ((unsigned char)128 >> (offset_stack[depth-2]&7)); 
				//state[offset_stack[depth-2]>>3] += bits[offset_stack[depth-2]&7]; 
			else 
				state[offset_stack[depth-2]>>3] &= ~((unsigned char) 128 >> (offset_stack[depth-2]&7));;
				//state[offset_stack[depth-2]>>3] &= ~bits[offset_stack[depth-2]&7]; 
			//printf("assigning state[%i] = %i \n",offset_stack[depth-2],state[offset_stack[depth-2]]);
			depth--;
			postpos++;
			continue;
		}
		type_stack[depth-1] = CONSTANT;
		if (postfix[postpos] == NOT) {
			offset_stack[depth-1] = not(var2); //array offset + variable on stack
			postpos += 1;
			continue;
		}
		else if (postfix[postpos] == NEG) {
			offset_stack[depth-1] = -1 * var2; //array offset + variable on stack
			postpos += 1;
			continue;
		}

		var1 = getValue(state,type_stack,offset_stack,depth-2);
		type_stack[depth-2] = CONSTANT;
		if (postfix[postpos] == AND){
			offset_stack[depth-2] = (var1 && var2) ;
		}
		else if (postfix[postpos] == PLUS){
			if (var1+var2 > 255) {return false;}
			offset_stack[depth-2] = var1 + var2;
		}
		else if (postfix[postpos] == MINUS){
			offset_stack[depth-2] = var1 - var2;
			//printf("\n storing  %i - %i = %i at pos %i \n",var1, var2,offset_stack[depth-2],depth-2);
		}
		else if (postfix[postpos] == MULT){
			offset_stack[depth-2] = var1 * var2;
			//printf("\n storing  %i * %i = %i at pos %i \n",var1, var2,offset_stack[depth-2],depth-2);
		}
		else if (postfix[postpos] == MOD){
			offset_stack[depth-2] = var1 % var2;
			//printf("\n storing %i - %i at pos %i \n",sum1, sum2,depth-2);
		}
		else if (postfix[postpos] == EQ){
			offset_stack[depth-2] = (var1 == var2) ;
			//printf("\n storing  %i == %i = %i at pos %i \n",var1, var2,offset_stack[depth-2],depth-2);
		}
		else if (postfix[postpos] == NEQ){
			offset_stack[depth-2] = (var1 != var2) ;
			//printf("\n storing  %i != %i at pos %i \n",var1, var2,depth-2);
		}
		else if (postfix[postpos] == LE){
			offset_stack[depth-2] = (var1 <= var2) ;
		}
		else if (postfix[postpos] == LESS){
			offset_stack[depth-2] = (var1 < var2) ;
		}
		else if (postfix[postpos] == GREATER){
			offset_stack[depth-2] = (var1 > var2) ;
		}
		else if (postfix[postpos] == GE){
			offset_stack[depth-2] = (var1 >= var2) ;
		}
		else if (postfix[postpos] == OR){
			offset_stack[depth-2] = (var1 || var2) ;
		}
		else if (postfix[postpos] == BINAND){
			offset_stack[depth-2] = (var1 & var2) ;
			//printf("\n storing  %i & %i = %i at pos %i \n",var1, var2,offset_stack[depth-2],depth-2);
		}
		else if (postfix[postpos] == BINOR){
			offset_stack[depth-2] = (var1 | var2) ;
		}
		depth--;
		postpos++;
	}
	//printf("depth= %i ",depth);
	if (checkonly) return offset_stack[0];
	else return true;
}

 __global__ void checkGuardsKernel(unsigned char * stateset, unsigned int setSize){

	if (tId < setSize) {
		unsigned char * state = &stateset[tId*checkSizeGPU];
		char enabled[200];
		int p;
		//for (p = 0; p < checkSizeGPU; p++) enabled[p] =0;
		memset(enabled,0,checkSizeGPU);
		//for (p = 0; p < constant[pr+0]; p++) {
		p = constant[pr+0];
		while(p) { //go through each process
			unsigned int ps = state[constant[pr+1+((p-1)*2)]];
			unsigned int tnum = constant[pr+1+((p-1)*2)-1];
			unsigned int tmp = ((p-1)>0)*tnum*3;
			unsigned int start_guard = constant[pr+1+(constant[pr+0]*2)+ps*3+tmp];
			unsigned int guards = constant[pr+1+(constant[pr+0]*2)+ps*3+1+tmp];
			unsigned int guard_offset = constant[pr+1+(constant[pr+0]*2)+ps*3+2+tmp];
			unsigned int gsize;
			while (guards) { //check each guard of the process
				gsize = constant[pg+guard_offset];
				if (!gsize || evaluatePostfixGPU(state,&constant[pg+guard_offset+1],gsize,true)) {
					enabled[start_guard>>3] += (unsigned char) 128 >> (start_guard &7 );
				}
				start_guard++;
				guard_offset += gsize+1;
				guards--;
			}
			p--;
		}
		for (p = 0; p < checkSizeGPU; p++) state[p] = enabled[p];
//		memcpy(state,enabled,checkSizeGPU);
	}
};

__global__ void enableEffectKernel(unsigned char * stateset, unsigned int setSize){
	if (tId < setSize) {

		unsigned char * state = &stateset[tId*(stateSizeGPU+sizetTransitions_GPU)];
		unsigned int transition=0; 
		memcpy(&transition, &stateset[(tId+1)*(stateSizeGPU+sizetTransitions_GPU)-sizetTransitions_GPU],sizetTransitions_GPU);
		//unsigned char trans_helper[4] = {0,0,0,0};
		//for (transition =0; transition < sizetTransitions_GPU; transition++) 
		//	trans_helper[transition] = stateset[(tId+1)*(stateSizeGPU+sizetTransitions_GPU)-sizetTransitions_GPU+transition];
		//memcpy(&transition,trans_helper,4);
		unsigned int effects = pe[to[transition]+2];
		//printf("number of effects %i ",effects);
		unsigned int effect_length = pe[to[transition]+3];
		unsigned int effect_offset = to[transition]+4;
	__syncthreads();

		state[pe[to[transition]]] = pe[to[transition]+1]; //set new state for process
		while (effects) {
			//printf("\n evaluating effect starting at %i , length %i ",effect_offset,effect_length);
			if (!evaluatePostfixGPU(state,&pe[effect_offset],effect_length,false)) ;
			effects--;
			effect_offset += effect_length+1;
			effect_length = pe[effect_offset-1];
		}
	}
}

__global__ void getHashesKernel(unsigned char * stateset, unsigned int setSize){
	if (tId < setSize) {

		unsigned int hash = stateSizeGPU, tmp;
		int rem = stateSizeGPU & 3;
		for ( int i = 0; i < 2; i++ ){
			unsigned char * data = &stateset[tId*(stateSizeGPU+sizetTransitions_GPU)];
			unsigned int len = stateSizeGPU >>2;

			/* Main loop */
			for (;len > 0; len--) {
				hash  += get16bits (data);
				tmp    = (get16bits (data+2) << 11) ^ hash;
				hash   = (hash << 16) ^ tmp;
				data  += 4;
				hash  += hash >> 11;
			}

			/* Handle end cases */
			if (rem) {
				if (rem == 3) {
					hash += get16bits (data);
					hash ^= hash << 16;
					hash ^= data[2] << 18;
					hash += hash >> 11;
				}
				else if (rem == 2) {
					hash += get16bits (data);
					hash ^= hash << 11;
					hash += hash >> 17;
				}
				else if (rem == 1) {
					hash += *data;
					hash ^= hash << 10;
					hash += hash >> 1;
				}
			}

			/* Force "avalanching" of final 127 bits */
			hash ^= hash << 3;
			hash += hash >> 5;
			hash ^= hash << 4;
			hash += hash >> 17;
			hash ^= hash << 25;
			hash += hash >> 6;

			hash %= HASHTABLESIZE;

			memcpy(&stateset[tId*(stateSizeGPU+sizetTransitions_GPU)+i*sizeof(unsigned int)],&hash,sizeof(unsigned int));
		}

	}

}
