objects = utility.o MessageTypes/CommonTypesSerializers.o

libFixSerializers.a: $(objects)
	ar rcs libFixSerializers.a $(objects)

utility.o : utility.h utility.c
MessageTypes/CommonTypesSerializers.o : MessageTypes/CommonTypesSerializers.c MessageTypes/CommonTypesSerializers.h

.PHONY : clean
clean :
	-rm $(objects) libFixSerializers.a