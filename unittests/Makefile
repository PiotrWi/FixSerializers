all: utilityTests commonTypesSerializersTests
	./utilityTests
	./commonTypesSerializersTests

utilityTests : utilityTests.cpp
	g++ utilityTests.cpp -o utilityTests -L.. -lFixSerializers

commonTypesSerializersTests : commonTypesSerializersTests.cpp
	g++ commonTypesSerializersTests.cpp -o commonTypesSerializersTests -L.. -lFixSerializers

clean:
	rm utilityTests commonTypesSerializersTests