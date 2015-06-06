all:	
	protoc --cpp_out=./ a.proto
	g++ -o reflection reflection.cc a.pb.cc -I /usr/local/include/ -lprotobuf -L /usr/local/lib/

clean:
	rm *.pb.* *.o reflection

