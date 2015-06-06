cc=g++
include=-I /usr/local/include
lib=-L/usr/local/lib/ -lprotobuf
objects=a.pb.o reflection.o
deps=$(patsubst %.o,%.d,$(objects))
pb_files=$(patsubst %.proto,%.pb.cc,$(wildcard *.proto))



	
bin=reflection

$(bin): $(objects)
	$(cc) $^ $(lib) -o$@ 
-include $(deps)

$(pb_files): %.pb.cc: %.proto	
	protoc --cpp_out=./ $<

%.o: %.cc %.d
	$(cc) -c  $(include) $< -o $@

%.d: %.cc
	$(cc) -MM $(include) $< -o$@ 
			 
reflection.d:$(pb_files)

clean:
	-rm *.pb.*
	-rm *.o
	-rm *.d
	-rm $(bin)
	
