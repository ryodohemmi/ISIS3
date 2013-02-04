#include <iostream>
#include "PvlToken.h"
#include "IException.h"
#include "Preference.h"

using namespace Isis;
using namespace std;

int main(int argc, char *argv[]) {
  Preference::Preferences(true);

  PvlToken dog("Dog");
  dog.AddValue("drools");

  cout << "Info on dog" << endl;
  cout << "  key:        " << dog.GetKey() << endl;
  cout << "  upperkey:   " << dog.GetKeyUpper() << endl;
  cout << "  valuesize:  " << dog.ValueSize() << endl;
  cout << "  value:      " << dog.GetValue() << endl;
  cout << "  uppervalue: " << dog.GetValueUpper() << endl;
  cout << endl;

  cout << "Adding another value to dog" << endl;
  dog.AddValue("wags tail");
  cout << "  valuesize:  " << dog.ValueSize() << endl;
  cout << "  value:      " << dog.GetValue(1) << endl;
  cout << "  uppervalue: " << dog.GetValueUpper(1) << endl;
  cout << endl;

  cout << "Clearing dog values" << endl;
  dog.ValueClear();
  cout << "  valuesize:  " << dog.ValueSize() << endl;
  cout << endl;

  cout << "Testing Throws in dog" << endl;

  try {
    dog.GetValue(-1);
  }
  catch(IException &e) {
    e.print();
  }

  try {
    dog.GetValue(1);
  }
  catch(IException &e) {
    e.print();
  }

  return 0;
}
