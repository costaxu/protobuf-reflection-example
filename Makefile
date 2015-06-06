cc=g++
include=-I /usr/local/include
lib=-L/usr/local/lib/ -lprotobuf
objects=$(patsubst %.cc,%.o,$(wildcard *.cc))
objects=a.pb.o reflection.o

deps=$(patsubst %.o,%.d,$(objects))
pb_files=$(patsubst %.proto,%.pb.cc,$(wildcard *.proto))



	
bin=reflection

$(bin): $(objects)
	$(cc) $^ $(lib) -o$@ 
-include $(deps)

$(pb_files): %.pb.cc: %.proto	
	protoc --cpp_out=./ $<

$(objects):%.o: %.cc %.d
	$(cc) -c  $(include) $< -o $@

$(deps):%.d: %.cc
	$(cc) -MM $(include) $< -o$@ 
clean:
	-rm *.pb.*
	-rm *.o
	-rm *.d
	-rm $(bin)
	
