<<<<<<< .mine
/*
 * GPUCheck.cpp
 *
 *  Created on: 05.01.2010
 *      Author: sulewski
 */
#include "GPUCheck.h"

#include "kernels.cu"

__device__ unsigned char * vram; //pointer to GPU memory


__host__ unsigned int computeGroups(unsigned int setSize) {
	unsigned int groups = setSize/THREADS+1;
	if (groups > 65000) {
		printf("\t %i groups splitting \n",groups);
		groups = 65000;
	}

	return groups;
}

void GPUCheck(myModel * model) { //initialize GPU memories

	printf("Initializing GPU \n");

	cudaError_t error = cudaMalloc((void **) &vram, VRAM);
	if(error!=cudaSuccess) { fprintf(stderr,"ERROR: %s : %s\n","Error allocating vram asfsdf" ,cudaGetErrorString(error)); exit(-1); }
	printf("reserved %i MB (%i bytes) on GPU \n",VRAM/1024/1024,VRAM);

	cpu_pr =0;
	cudaMemcpyToSymbol("pr",&cpu_pr,sizeof(unsigned int),0,cudaMemcpyHostToDevice);
	//cudaMalloc((void **) &pr,model->postfix_representation.size()*sizeof(int));
	cudaMemcpyToSymbol("constant",&model->postfix_representation[0],model->postfix_representation.size()*sizeof(int),pr,cudaMemcpyHostToDevice);
	printf("Copied postfix_representation %lu bytes to %i \n",(int)model->postfix_representation.size()*sizeof(int),pr);

	
	cpu_pg = cpu_pr+model->postfix_representation.size();
	cudaMemcpyToSymbol("pg",&cpu_pg,sizeof(unsigned int),0,cudaMemcpyHostToDevice);
	//cudaMalloc((void **) &pg,model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE)); 
	cudaMemcpyToSymbol("constant",&model->postfix_guards[0],model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE),cpu_pg*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyHostToDevice);
	printf("Copied postfix_guards %lu bytes to %i \n",(int)model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE),cpu_pg);
		if(cudaError_t e = cudaGetLastError()) {
		  cout << "Error : " << cudaGetErrorString(e) << endl;
			assert(0);
		}

	assert(cpu_pg+model->postfix_guards.size() < 63*1024);
	cudaMalloc((void **) &pe,model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE));
	cudaMemcpy(pe,&model->postfix_effects[0],model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyHostToDevice);
	printf("Copied postfix_effects %lu bytes \n",(int)model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE));

	cudaMalloc((void **) &to,model->transition_offsets.size()*sizeof(int));
	cudaMemcpy(to,&model->transition_offsets[0],model->transition_offsets.size()*sizeof(int),cudaMemcpyHostToDevice);
	printf("Copied transition_offsets %lu bytes \n",(int)model->transition_offsets.size()*sizeof(int));

	if(cudaMemcpyToSymbol(sizetTransitions_GPU,&model->sizetTransitions,sizeof(unsigned int))) {
		printf("Error copy sizetTransitions  to vram %s\n",cudaGetErrorString(cudaGetLastError()));
		exit(0);
	}

	unsigned int t = model->initial->size;
	cudaMemcpyToSymbol("stateSizeGPU",&t,sizeof(unsigned int),0,cudaMemcpyHostToDevice);
	cudaMemcpyToSymbol("checkSizeGPU",&model->checkingSpace,sizeof(unsigned int),0,cudaMemcpyHostToDevice);

	initKernel<<<1,1>>>(pg,pe, pr,to);
		if(cudaError_t e = cudaGetLastError()) {
		  cout << "Error calling kernel: " << cudaGetErrorString(e) << endl;
			assert(0);
		}
}

bool checkGPUmemory(myModel * model){
	
	void * tmp = malloc(model->postfix_representation.size()*sizeof(int));
	cudaMemcpyFromSymbol(tmp,"constant",model->postfix_representation.size()*sizeof(int),cpu_pr*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyDeviceToHost);
	assert(memcmp(tmp,&model->postfix_representation[0],model->postfix_representation.size()*sizeof(int)) == 0 );
	free(tmp);

	tmp = malloc(model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE));
	cudaMemcpyFromSymbol(tmp,"constant",model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE),cpu_pg*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyDeviceToHost);
	assert(memcmp(tmp,&model->postfix_guards[0],model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE)) == 0 );
	free(tmp);

	tmp = malloc(model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE));
	cudaMemcpy(tmp,pe,model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyDeviceToHost);
	assert(memcmp(tmp,&model->postfix_effects[0],model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE)) == 0 );
	free(tmp);

	tmp = malloc(model->transition_offsets.size()*sizeof(int));
	cudaMemcpy(tmp,to,model->transition_offsets.size()*sizeof(int),cudaMemcpyDeviceToHost);
	assert(memcmp(tmp,&model->transition_offsets[0],model->transition_offsets.size()*sizeof(int)) == 0 );
	free(tmp);

	unsigned int t =0;
	cudaMemcpyFromSymbol(&t,"stateSizeGPU",sizeof(unsigned int),0,cudaMemcpyDeviceToHost);
	assert(t == model->initial->size);

	cout << "GPU Memory Check successfull " << endl;

	return true;
}

void checkGuardsPostfix(unsigned char * stateset,unsigned char * enabledset,unsigned int setSize, myModel * model){
#ifdef _CHECK
	checkGPUmemory(model);
#endif

	if (cudaMemcpy(vram,&stateset[0],setSize*model->checkingSpace,cudaMemcpyHostToDevice))
		printf("Error copying states to vram %i\n",cudaGetLastError());

	unsigned int groups = computeGroups(setSize);
	unsigned int done = 0;
	unsigned int doing = groups*THREADS;
	if (doing > setSize) doing = setSize;

	while (done < setSize) {
		printf("\t done %i computing %i states utilizing %i groups \n",done,doing,groups);
		checkGuardsKernel<<<groups,THREADS>>>(&vram[done*model->checkingSpace], doing);
		if(cudaError_t e = cudaGetLastError()) {
		  cout << "Error calling kernel: " << cudaGetErrorString(e) << endl;
			assert(0);
		}
		doing = setSize-doing-done;
		done += groups*THREADS;
		groups = computeGroups(doing);
	}

	if (cudaMemcpy(&enabledset[0],vram,setSize*model->checkingSpace,cudaMemcpyDeviceToHost)) {
		assert(0);
	}

}

unsigned int enableEffectsPostfix(unsigned char * childset, unsigned int setSize, myModel * model){
#ifdef _CHECK
	checkGPUmemory(model);
#endif
	if (cudaMemcpy(vram,childset,setSize*(model->initial->size+model->sizetTransitions),cudaMemcpyHostToDevice)) {
		printf("Error copying %i (%i bytes) children to vram %s\n",setSize,setSize*(model->initial->size+1),cudaGetErrorString(cudaGetLastError()));
		exit(0);
	}

	unsigned int groups = computeGroups(setSize);

	unsigned int done = 0;
	unsigned int doing = groups*THREADS;
	if (doing > setSize) doing = setSize;

	while (done < setSize) {
		printf("\t done %i computing %i states utilizing %i groups \n",done,doing,groups);
		enableEffectKernel<<<groups,THREADS>>>(&vram[done*(model->initial->size+model->sizetTransitions)], doing );
		if(cudaGetLastError()) printf("Error calling kernel %i\n",cudaGetLastError());
		done += doing;
		doing = setSize-done;
		cout << " left " << doing << " children" <<endl; 
		groups = computeGroups(doing);
		if (groups == 65000) doing = groups*THREADS;
	}

	if (cudaMemcpy(childset,vram,setSize*(model->initial->size+model->sizetTransitions),cudaMemcpyDeviceToHost)){
		printf("Error copying %i (%i bytes) children from vram %s\n",setSize,setSize*(model->initial->size+1),cudaGetErrorString(cudaGetLastError()));
		exit(0);
	}

	return true;
}

unsigned int getHashesGPU(unsigned char * hashes, unsigned int setSize, myModel * model){
#ifdef _CHECK
	checkGPUmemory(model);
#endif
	unsigned int groups = computeGroups(setSize);

	unsigned int done = 0;
	unsigned int doing = groups*THREADS;
	if (doing > setSize) doing = setSize;

	while (done < setSize) {
		printf("\t done %i computing %i states utilizing %i groups \n",done,doing,groups);
		getHashesKernel<<<groups,THREADS>>>(&vram[done*(model->initial->size+model->sizetTransitions)],doing);
		if(cudaGetLastError()) printf("Error calling kernel %i\n",cudaGetLastError());
		done += doing;
		doing = setSize-done;
		cout << " left " << doing << " children" <<endl; 
		groups = computeGroups(doing);
		if (groups == 65000) doing = groups*THREADS;
	}

	if (cudaMemcpy(hashes,vram,setSize*(model->initial->size+model->sizetTransitions),cudaMemcpyDeviceToHost)){
		printf("Error copying %i (%i bytes) children from vram %s\n",setSize,setSize*(model->initial->size+1),cudaGetErrorString(cudaGetLastError()));
		exit(0);
	}

	return setSize;
}

=======
/*
 * GPUCheck.cpp
 *
 *  Created on: 05.01.2010
 *      Author: sulewski
 */
#include "GPUCheck.h"

#include "Timer.h"

extern Timer runningTime;


__device__ unsigned char * vram; //pointer to GPU memory


#include "kernels.cu"

#define MAXGROUPS 65000 

void GPUCheck(myModel * model) { //initialize GPU memories

	unsigned int t = model->initial->size;
	CUDA_SAFE_CALL(cudaMemcpyToSymbol("stateSizeGPU",&t,sizeof(unsigned int),0,cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL(cudaMemcpyToSymbol("checkSizeGPU",&model->checkingSpace,sizeof(unsigned int),0,cudaMemcpyHostToDevice));

	cpu_pr =0;
	CUDA_SAFE_CALL(cudaMemcpyToSymbol("pr",&cpu_pr,sizeof(unsigned int),0,cudaMemcpyHostToDevice));
	CUDA_SAFE_CALL(cudaMemcpyToSymbol("constant",&model->postfix_representation[0],model->postfix_representation.size()*sizeof(int),pr,cudaMemcpyHostToDevice));
	cout << runningTime ; printf("Copied postfix_representation %lu bytes to %i \n",(int)model->postfix_representation.size()*sizeof(int),pr);
	
	cpu_pg = cpu_pr+model->postfix_representation.size()*sizeof(int);
	assert(cpu_pg+model->postfix_guards.size() < CONSTANTMEM);
	CUDA_SAFE_CALL(cudaMemcpyToSymbol("pg",&cpu_pg,sizeof(unsigned int),0,cudaMemcpyHostToDevice));
	cout << runningTime ; printf("Copying postfix_guards %lu bytes to %i \n",(int)model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE),(unsigned int) cpu_pg*sizeof(POSTFIX_EFFECTS_TYPE));
	CUDA_SAFE_CALL(cudaMemcpyToSymbol("constant",&model->postfix_guards[0],model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE),cpu_pg*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyHostToDevice));
	cout << runningTime ; printf("Copied postfix_guards %lu bytes to %i \n",(int)model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE),(unsigned int) cpu_pg*sizeof(POSTFIX_EFFECTS_TYPE));

	CUDA_SAFE_CALL(cudaMalloc((void **) &pe,model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE)));
	CUDA_SAFE_CALL(cudaMemcpy(pe,&model->postfix_effects[0],model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyHostToDevice));
	cout << runningTime ; printf("Copied postfix_effects %lu bytes \n",(int)model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE));

	CUDA_SAFE_CALL(cudaMalloc((void **) &to,model->transition_offsets.size()*sizeof(int)));
	CUDA_SAFE_CALL(cudaMemcpy(to,&model->transition_offsets[0],model->transition_offsets.size()*sizeof(int),cudaMemcpyHostToDevice));
	cout << runningTime ; printf("Copied transition_offsets %lu bytes \n",(int)model->transition_offsets.size()*sizeof(int));

	CUDA_SAFE_CALL(cudaMemcpyToSymbol(sizetTransitions_GPU,&model->sizetTransitions,sizeof(unsigned int))) ;
	CUDA_SAFE_CALL(cudaMemcpyToSymbol(metricTransitionGPU,&model->metric_transition,sizeof(unsigned int))) ;


	//cout<<"copying precondition_predicates"<<endl;
	vector<unsigned int>flat_precond;
	for ( int i = 0 ; i < model->initial->size*16; i++ ) flat_precond.push_back(0);
	map<unsigned int, vector<unsigned int> >::iterator it = model->precondition_predicates.begin();
	while ( it != model->precondition_predicates.end()){
		vector<unsigned int>::iterator it2 = (*it).second.begin();
		if (it2 != (*it).second.end()) flat_precond[(*it).first*2]=flat_precond.size();
		if (it2 != (*it).second.end()) flat_precond[(*it).first*2+1]=(*it).second.size();
		while (it2 != (*it).second.end()){
			flat_precond.push_back(*it2);
			it2++;
		}
		it++;
	}
//	cout << "flat_precon= ";
//	for ( int i = 0 ; i < flat_precond.size() ; i++ ) cout << i << ":" << flat_precond[i] << endl;
//	cout << endl;

	cudaMalloc((void **) &preconditions_gpu,flat_precond.size()*sizeof(int));
	cudaMemcpy(preconditions_gpu,&flat_precond[0],flat_precond.size()*sizeof(int),cudaMemcpyHostToDevice);
	if(cudaError_t e = cudaGetLastError()) {
		cout << "Error : " << cudaGetErrorString(e) << endl;
		assert(0);
	}
	cout << runningTime ;
	printf("Copied precondition_predicates %lu bytes \n",(int)flat_precond.size()*sizeof(int));

	cudaError_t error = cudaMalloc((void **) &vram, VRAM);
	if(error!=cudaSuccess) { fprintf(stderr,"ERROR: %s : %s\n","Error allocating vram asfsdf" ,cudaGetErrorString(error)); exit(-1); }
	cout << runningTime ;
	printf("reserved %i MB (%i bytes) on GPU \n",VRAM/1024/1024,VRAM);


	initKernel<<<1,1>>>(pg,pe, pr,to,preconditions_gpu);
	if(cudaError_t e = cudaGetLastError()) {
	  cout << "Error calling kernel: " << cudaGetErrorString(e) << endl;
		assert(0);
	}
}

bool checkGPUmemory(myModel * model){
	
	void * tmp = malloc(model->postfix_representation.size()*sizeof(int));
	cudaMemcpyFromSymbol(tmp,"constant",model->postfix_representation.size()*sizeof(int),cpu_pr*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyDeviceToHost);
	assert(memcmp(tmp,&model->postfix_representation[0],model->postfix_representation.size()*sizeof(int)) == 0 );
	free(tmp);

	tmp = malloc(model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE));
	cudaMemcpyFromSymbol(tmp,"constant",model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE),cpu_pg*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyDeviceToHost);
	assert(memcmp(tmp,&model->postfix_guards[0],model->postfix_guards.size()*sizeof(POSTFIX_EFFECTS_TYPE)) == 0 );
	free(tmp);

	tmp = malloc(model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE));
	cudaMemcpy(tmp,pe,model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE),cudaMemcpyDeviceToHost);
	assert(memcmp(tmp,&model->postfix_effects[0],model->postfix_effects.size()*sizeof(POSTFIX_EFFECTS_TYPE)) == 0 );
	free(tmp);

	tmp = malloc(model->transition_offsets.size()*sizeof(int));
	cudaMemcpy(tmp,to,model->transition_offsets.size()*sizeof(int),cudaMemcpyDeviceToHost);
	assert(memcmp(tmp,&model->transition_offsets[0],model->transition_offsets.size()*sizeof(int)) == 0 );
	free(tmp);

	unsigned int t =0;
	cudaMemcpyFromSymbol(&t,"stateSizeGPU",sizeof(unsigned int),0,cudaMemcpyDeviceToHost);
	assert(t == model->initial->size);
	cudaMemcpyFromSymbol(&t,"pg",sizeof(unsigned int),0,cudaMemcpyDeviceToHost);
	assert(t == cpu_pg);

	cout << "GPU Memory Check successfull " << endl;

	return true;
}

void callKernel(unsigned int setSize,unsigned int elementSize, void(*kernel)(unsigned char * , unsigned int)){
	unsigned int maxElements = MAXGROUPS*THREADS;
	unsigned int toDo = setSize;
	unsigned int done = 0;
	unsigned int groups = 0;

	while (toDo > 0) {
		unsigned int doNow = toDo;
		if (doNow > maxElements) doNow = maxElements;
		groups = doNow / THREADS +1;
		cout << "\t done " << done << " states; computing " << doNow << " states utilizing " << groups << " groups " << endl;
		cudaEvent_t evt;
		cudaEventCreate(&evt);
		kernel<<<groups,THREADS>>>(&vram[done*elementSize], doNow);
		CUT_CHECK_ERROR("Kernel execution failed");
		cudaEventRecord(evt, NULL);
		while (cudaEventQuery(evt) == cudaErrorNotReady)
		{
			  usleep(500);
		}
		cudaEventDestroy(evt);
		done += doNow;
		toDo -= doNow;
	}
	assert (done == setSize);
}

void checkGuardsPostfix(unsigned char * stateset,unsigned char * enabledset,unsigned int setSize, myModel * model){
#ifdef _CHECK
	checkGPUmemory(model);
#endif

	CUDA_SAFE_CALL(cudaMemcpy(vram,&stateset[0],setSize*model->checkingSpace,cudaMemcpyHostToDevice));

	callKernel(setSize,model->checkingSpace,checkGuardsKernel);

	CUDA_SAFE_CALL(cudaMemcpy(&enabledset[0],vram,setSize*model->checkingSpace,cudaMemcpyDeviceToHost)); 

}

unsigned int enableEffectsPostfix(unsigned char * childset, unsigned int setSize, myModel * model){
#ifdef _CHECK
	checkGPUmemory(model);
#endif
	CUDA_SAFE_CALL(cudaMemcpy(vram,childset,setSize*(model->initial->size+model->sizetTransitions),cudaMemcpyHostToDevice)) ;

	callKernel(setSize,model->initial->size+model->sizetTransitions,enableEffectKernel);
if (model->metric_transition != -1)	callKernel(setSize,model->initial->size+model->sizetTransitions,computeMetricKernel);

	CUDA_SAFE_CALL(cudaMemcpy(childset,vram,setSize*(model->initial->size+model->sizetTransitions),cudaMemcpyDeviceToHost));

	return true;
}

unsigned int getHashesGPU(unsigned char * hashes, unsigned int setSize, myModel * model){
#ifdef _CHECK
	checkGPUmemory(model);
#endif

	callKernel(setSize,model->initial->size+model->sizetTransitions,getHashesKernel);
	CUDA_SAFE_CALL(cudaMemcpy(hashes,vram,setSize*(model->initial->size+model->sizetTransitions),cudaMemcpyDeviceToHost));
	return setSize;
}

>>>>>>> .r254
