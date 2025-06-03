#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "site.hpp"
#include "operation.hpp"
#include "TransactionManager.hpp"
#include "transaction.hpp"

std::list<Operation> operations;

Operation parseLine(string line)
{
    Operation op;
    switch (line[0])
    {

    case 'R':
    {
        // op = opREAD(line);
        op.opREAD(line);
        break;
    }
    case 'W':
    {
        // op = opWRITE(line);
        op.opWRITE(line);
        break;
    }
    case 'b':
    {
        // op = opBEGIN(line);
        op.opBEGIN(line);
        break;
    }
    case 'e':
    {
        // op = opEND(line);
        op.opEND(line);
        break;
    }
    case 'f':
    {
        // op = opFAIL(line);
        op.opFAIL(line);
        break;
    }
    case 'r':
    {
        // op = opRECOVER(line);
        op.opRECOVER(line);
        break;
    }
    case 'd':
    {
        // op = opDUMP(line);
        op.opDUMP(line);
        break;
    }
    default:
        std::cout << "nothing" << std::endl;
        break;
    }
    return op;
}

// void parseInput(const char *filename)
// {

//     std::ifstream file(filename);
//     std::string line;
//     int time = 0;

//     while (getline(file, line))
//     {
//         Operation op;
//         switch (line[0])
//         {

//         case 'R':
//         {
//             // op = opREAD(line);
//             op.opREAD(line);
//             break;
//         }
//         case 'W':
//         {
//             // op = opWRITE(line);
//             op.opWRITE(line);
//             break;
//         }
//         case 'b':
//         {
//             // op = opBEGIN(line);
//             op.opBEGIN(line);
//             break;
//         }
//         case 'e':
//         {
//             // op = opEND(line);
//             op.opEND(line);
//             break;
//         }
//         case 'f':
//         {
//             // op = opFAIL(line);
//             op.opFAIL(line);
//             break;
//         }
//         case 'r':
//         {
//             // op = opRECOVER(line);
//             op.opRECOVER(line);
//             break;
//         }
//         case 'd':
//         {
//             // op = opDUMP(line);
//             op.opDUMP(line);
//             break;
//         }
//         default:
//             std::cout << "nothing" << std::endl;
//             break;
//         }
//         op.timestamp = time;
//         operations.push_back(op);
//         time++;
//     }
// }

int main(int argc, char *argv[])
{
    TransactionManager tm(operations);
    // const char *filename = "tests/test1.txt";
    std::string line;
    int time = 0;
    if (argc == 2)
    {
        const char *filename = argv[1];
        // parseInput(filename);
        std::ifstream file(filename);

        while (getline(file, line))
        {
            Operation curOP = parseLine(line);
            curOP.timestamp = time;
            tm.addOperation(curOP);
            tm.run();
            time++;
        }
    }
    else
    {
        while (std::cin)
        {
            getline(std::cin, line);
            Operation curOP = parseLine(line);
            curOP.timestamp = time;
            tm.addOperation(curOP);
            tm.run();
            time++;
        }
    }
    tm.wrapUp();
}
