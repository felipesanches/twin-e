echo "Build test code for 'movements.c'..."
g++ -c movements_test.c -o movements_test.o -I./ -I../../src -g
echo "Build 'movements.c'..."
g++ ../../src/movements.c movements_test.o -I./ -I../../src -g -lgtest -lpthread -o testAll
echo "Run tests:\n\n"
./testAll
