all:
	g++ planar_link.cpp -fPIC -shared -o libplink.so
	g++ -L./ -Wl,-rpath,./ three_link_test.cpp -o three_link_test -lm -lplink 
