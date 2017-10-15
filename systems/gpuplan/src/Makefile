<<<<<<< .mine
#OPTIONS = -g
OPTIONS = -O3

#CUDAOPTIONS = -G0
CUDAOPTIONS = --ptxas-options=-v -arch=sm_13

#CHECK = -D_CHECK
#DEBUG = -D_DEBUGING

all: parser openList.o myModel.o GPUCheck.o StatesContainer.o myState.o
	nvcc ${OPTIONS} ${CUDAOPTIONS} ${FAST} ${CHECK} ${DEBUG} -o gdl-parser parser.cc myModel.o GPUCheck.o StatesContainer.o openList.o myState.o
  
parser: lex-gdl.l gdl.y
	flex -o lex.gdl.cc lex-gdl.l
	bison -o gdl.tab.cc gdl.y
  
openList.o: openList.cc openList.h
	nvcc ${OPTIONS} ${FAST}  ${DEBUG} -c -o openList.o openList.cc

myState.o: myState.cc myState.h
	nvcc ${OPTIONS} ${FAST}  ${DEBUG} -c -o myState.o myState.cc

myModel.o: myModel.cc myModel.h
	g++ ${OPTIONS} ${FAST}  ${DEBUG} -c -o myModel.o myModel.cc

GPUCheck.o: GPUCheck.cu
	nvcc ${OPTIONS} ${CUDAOPTIONS} ${FAST} ${CHECK} ${DEBUG} -c -o GPUCheck.o GPUCheck.cu
  
StatesContainer.o: StatesContainer.cpp StatesContainer.h
	g++ ${OPTIONS} ${FAST} ${CHECK} ${DEBUG}  -c -o StatesContainer.o StatesContainer.cpp
  
clean:
	rm myModel.o
	rm myState.o
	rm GPUCheck.o
	rm StatesContainer.o
	
=======
#OPTIONS = -g -lpthread 
OPTIONS = -O3 -lpthread 

GCCOPTIONS = -std=c++0x


#NVDEBUG = -G0
CUDAOPTIONS = ${NVDEBUG} --ptxas-options=-v -arch=sm_20 -I/home/sulewski/cudasdk22/common/inc/

#CHECK = -D_CHECK
#DEBUG = -D_DEBUGING

all: dve-parser gdl-parser 

gdl-parser: parser myModelGDL.o GPUCheckGDL.o StatesContainerLockFree.o myState.o timer.o
	make -C lockfree
	nvcc -D_PLANER ${OPTIONS} ${CUDAOPTIONS} ${FAST} ${CHECK} ${DEBUG} -lz -lssl -o gdl-parser parser.cc myModelGDL.o GPUCheckGDL.o StatesContainerLockFree.o myState.o timer.o -Llockfree/ -ldbs 

dve-parser: parser myModelDVE.o GPUCheckDVE.o StatesContainerLockFree.o myState.o timer.o
	make -C lockfree
	nvcc ${OPTIONS} ${CUDAOPTIONS} ${FAST} ${CHECK} ${DEBUG} -lz -lssl -o dve-parser parser.cc myModelDVE.o GPUCheckDVE.o StatesContainerLockFree.o myState.o timer.o -Llockfree/ -ldbs
  
parser: lex-gdl.l gdl.y lex-dve.l dve.y
	flex -o lex.gdl.cc lex-gdl.l
	bison -o gdl.tab.cc gdl.y
	flex -o lex.dve.cc lex-dve.l
	bison -o dve.tab.cc dve.y
  
myState.o: myState.cc myState.h
	nvcc ${OPTIONS} ${FAST}  ${DEBUG} -c -o myState.o myState.cc

timer.o: Timer.cc Timer.h
	g++ ${OPTIONS} ${FAST}  ${DEBUG} -c -o timer.o Timer.cc

myModelDVE.o: myModel.cc myModel.h
	g++ ${OPTIONS} ${FAST}  ${DEBUG} -c -o myModelDVE.o myModel.cc

myModelGDL.o: myModel.cc myModel.h 
	g++ -D_PLANER ${OPTIONS} ${FAST}  ${DEBUG} -c -o myModelGDL.o myModel.cc

GPUCheckDVE.o: GPUCheck.cu kernels.cu
	nvcc ${OPTIONS} ${CUDAOPTIONS} ${FAST} ${CHECK} ${DEBUG} -c -o GPUCheckDVE.o GPUCheck.cu

GPUCheckGDL.o: GPUCheck.cu kernels.cu
	nvcc -D_PLANER ${OPTIONS} ${CUDAOPTIONS} ${FAST} ${CHECK} ${DEBUG} -c -o GPUCheckGDL.o GPUCheck.cu
  
StatesContainerLockFree.o: StatesContainerLockFree.cpp StatesContainer.h
	g++ ${OPTIONS} ${GCCOPTIONS} ${FAST} ${CHECK} ${DEBUG}  -lz -lssl -c -o StatesContainerLockFree.o StatesContainerLockFree.cpp
  
clean:
	rm lockfree/libdbs.a
	rm myModelDVE.o
	rm myModelGDL.o
	rm myState.o
	rm GPUCheckDVE.o
	rm GPUCheckGDL.o
	rm StatesContainer*.o
	rm dve-parser
	rm gdl-parser
	
>>>>>>> .r254
