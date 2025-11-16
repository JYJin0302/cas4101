CXX=g++

EXEC    = PrimalDual

main:
	$(CXX) -o solve $(EXEC).cpp PD-SF.cpp SF-Functions.cpp SF-Solution.cpp -std=c++20

clean:
	/bin/rm -f $(EXEC) $(EXEC)*.o $(EXEC)*.s