#include <iostream>
#include <vector>
#include "book.h"
#include "user.h"
#include "registereduser.h"
using namespace std;

//Constructor
RegisteredUser::RegisteredUser(string id, string pass) : User(id, pass, "Registered User") {}