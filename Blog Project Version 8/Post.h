//
// Created by User on 9/6/2022.
//

#ifndef BLOGSTART_POST_H
#define BLOGSTART_POST_H
#include <string>
#include <iostream>
using namespace std;
class Post
{

public:
    Post();

    Post(string title, string text, string user);

    struct Reactions
    {
        int loveInt;
        int likeInt;
        int dislikeInt;
        int hateInt;
    };

    friend ostream& operator <<(ostream& outputStream, const Post& p);

    bool operator ==(const Post& otherPost) const;

    string getTitle( ) const {return this->title;}    //Access Private Data

    string getText( ) const {return this->text;}

    string getUser( ) const {return this->user;}

    void editTitle(string tit){ this->title = tit;}     //Edit private data

    void edittext(string tex){ this->text = tex;}

    void editUser(string u){ this -> user = u;}

    void Pop_Structer(int lo, int li, int dl, int h);

    void SaveRToFile() const;

    void displayStructure()const;

    void ReturnGallery(int & love, int & like, int & dislike, int & hate) const         //Gives post details to next variables
    {love = rGallery.loveInt; like = rGallery.likeInt; dislike = rGallery.dislikeInt; hate = rGallery.hateInt;}

    void enterReaction();



private:                                          //Only accesible through public functions
    string title;
    string text;
    string user;
    Reactions rGallery;

};


#endif //BLOGSTART_POST_H
