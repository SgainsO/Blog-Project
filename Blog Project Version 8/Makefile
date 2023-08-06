output: BlogPart7.o Post.o Area.o User.o SuperUser.o
	g++ -std=c++11  BlogPart7.o Post.o Area.o User.o SuperUser.o -o output

BlogPart7.o: BlogPart7.cpp
	g++ -std=c++11 -c BlogPart7.cpp

Post.o: Post.cpp Post.h
	g++ -std=c++11  -c Post.cpp

Area.o: Area.cpp Area.h
	g++ -std=c++11 -c Area.cpp

SuperUser.o: SuperUser.cpp SuperUser.h
	g++ -std=c++11 -c SuperUser.cpp
User.o: User.cpp User.h
	g++ -std=c++11 -c User.cpp
clean:
	rm *.o
