#include "vex.h"
#include <vector>
#include <string>

using namespace vex;
using namespace std;

/**
 * @brief This contains any information you want to print to the brain
 */
struct Info
{
    string name;
    long double data;
};

class BrainInfo
{
public:
    /// @brief This method prints out data to the brain screen
    /// @param infoToPrint This is an array of objects with the name of the data and the data itself that you want to print
    void printInfo(vector<Info> infoToPrint)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.setPenWidth(10);
        for (Info info : infoToPrint)
        {
            Controller.Screen.print(info.name);
            Controller.Screen.print(" ");
            Controller.Screen.print(info.data);
        }
    }
};