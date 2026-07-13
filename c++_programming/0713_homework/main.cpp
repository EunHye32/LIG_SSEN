#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

int main()
{
  PersonService service;
  service.add();
  service.add();
  service.add();
  service.get();
  service.printAll();
  service.edit();
  service.printAll();
  service.del();
  service.del();
  service.printAll();

  return 0;
}