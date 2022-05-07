# make -f mf.mk
final: 
	g++	--std=c++11	Program.cpp -o	final
clean:
	rm final	NewMap.json
