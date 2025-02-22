#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
using namespace std;
int main ()
{
string data;
// Instantiation of an ifstream object
ifstream inStrm;
// Connection of the existing file to the ifstream object
inStrm.open ("IntegerFile");
if (!inStrm.is_open())
{
cout << "integerFile cannot be opened!";
assert (false);
}
// Reading from the ifstream object and writing to the cout object
while(getline(inStrm, data, "$"))
{

cout << data ;
}
// Disconnection of the IntegerFile from the ifstream
inStrm.close ();
// Destruction of the ifstream object is done after return
return 0;
}