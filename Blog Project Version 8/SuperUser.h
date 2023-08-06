//
// Created by User on 10/5/2022.
//

#ifndef BLOGPART5_CPP_SUPERUSER_H
#define BLOGPART5_CPP_SUPERUSER_H
#include "User.h"


class SuperUser : public User{
public:
    SuperUser();

    SuperUser(User *pUser);

    void egoBooster()const;         //use of virtual function

    void printSuper(){ cout << "--------" <<endl;}

private:


};


#endif //BLOGPART5_CPP_SUPERUSER_H
