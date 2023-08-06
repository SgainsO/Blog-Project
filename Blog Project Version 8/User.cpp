
#include "User.h"
#include <iostream>
using namespace std;
User::User() {UserType = NORMAL;}

//Logic for validating a future password
bool User::operator==(const User & x) const{

    if(this->password == x.password && this-> userName == x.userName)
    {
        return true;
    }
    else {
        return false;
    }
}

void User::setUserType(User::UserTypes x) {this->UserType = x;};

void User::egoBooster() const{            //Does not all the ego boosting to work for super users
    cout << "You are not a super-user" <<endl;
    cout << "You have not made it in life yet" <<endl;
}



