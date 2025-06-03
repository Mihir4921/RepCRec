RepCRec: main.cpp
	g++ main.cpp site.cpp transaction.cpp operation.cpp TransactionManager.cpp -o main

clean:
	rm -f main *~
