all: utilityTests commonTypesSerializersTests fixHeaderTests
	./utilityTests
	./commonTypesSerializersTests
	./fixHeaderTests

utilityTests : utilityTests.cpp
	g++ utilityTests.cpp -o utilityTests -L.. -lFixSerializers

commonTypesSerializersTests : commonTypesSerializersTests.cpp
	g++ commonTypesSerializersTests.cpp -o commonTypesSerializersTests -L.. -lFixSerializers

fixHeaderTests : fixHeaderTests.cpp
	g++ fixHeaderTests.cpp -o fixHeaderTests -L.. -lFixSerializers

clean:
	rm utilityTests commonTypesSerializersTests fixHeaderTests
