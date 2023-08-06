

#ifndef UNTITLED_USER_H
#define UNTITLED_USER_H
#include <iostream>
#include <string>

using namespace std;

class User {
public:
    User();
    enum UserTypes {NORMAL,SUPERUSER};

    void setName(string x){this->name = x;} //Setters and Getters

    void setUserName(string x){this->userName = x;}

    void setPassword(string x){this->password =x;}

    void setUserType(User::UserTypes x);

    virtual void egoBooster()const;

    UserTypes getUserType()const {return this->UserType;}

    string getName() const{return name;}

    string getUserName() const{return userName;}

    string getPassword() const{return password;}

    bool operator==(const User & x) const;
protected:

    UserTypes UserType;
    string name;
    string userName;          //alias
    string password;
};


#endif //UNTITLED_USER_H
