//ay
// Created by User on 10/5/2022.
//

#include "SuperUser.h"

SuperUser::SuperUser() : User()
{
    UserType = SUPERUSER;
}

void SuperUser::egoBooster() const    //Only allows superusers to get the confidence boost
{
    cout << "Hello " << userName << " you are indeed a super user" <<endl;
    cout << "You made it in life, congrats" <<endl;
}

SuperUser::SuperUser(User *pUser) {
    name = pUser->getName();
    userName = pUser->getUserName();
    password = pUser->getPassword();

}


