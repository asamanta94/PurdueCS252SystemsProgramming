Base.o: Base.cc
	g++ -c -g Base.cc
Der.o: Der.cc
	g++ -c -g Der.cc
test.o:
	g++ -c -g test.cc
TEST: test.o Der.o Base.o
	g++ -o TEST test.o Der.o Base.o
