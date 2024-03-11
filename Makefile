objects = utility.o MessageTypes/CommonTypesSerializers.o MessageTypes/FixHeader.o MessageTypes/Logon.o

libFixSerializers.a: $(objects)
	ar rcs libFixSerializers.a $(objects)

utility.o : utility.h utility.c
MessageTypes/CommonTypesSerializers.o : MessageTypes/CommonTypesSerializers.c MessageTypes/CommonTypesSerializers.h
MessageTypes/FixHeader.o: MessageTypes/FixHeader.c MessageTypes/FixHeader.h
MessageTypes/Logon.o: MessageTypes/Logon.c MessageTypes/Logon.h

.PHONY : clean
clean :
	-rm $(objects) libFixSerializers.a