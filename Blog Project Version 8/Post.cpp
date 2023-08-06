#include "Post.h"
#include <iostream>
#include <fstream>
//Post class Constructor

Post::Post(string ti, string tex,  string nam)   //Defines the blogstart variables
{
    enum Reactions{};

    this-> text = tex;

    this -> title = ti;

    this -> user = nam;

}

Post::Post(){ }    //Empty constructor in case a post is supposed to start of empty

bool Post::operator==(const Post &otherPost) const{
    if(this->title == otherPost.getTitle())
        return true;         //checks if another title exists
    else
        return false;
}

void Post::Pop_Structer(int lo, int li, int dl, int h)    //put values into a structure
{
    this->rGallery.loveInt = lo;
    this->rGallery.likeInt = li;
    this->rGallery.dislikeInt = dl;
    this->rGallery.hateInt = h;
}

void Post::displayStructure()const {
    cout << "Love:" << rGallery.loveInt << " ";
    cout << "Liked:" << rGallery.likeInt << " ";
    cout << "Dislike:" << rGallery.dislikeInt << " ";
    cout << "Hate:" << rGallery.hateInt << endl;
}

void Post::enterReaction()
{
    int rInput;

    cout<<"love = 0 "
          "like = 1 "
          "dislike = 2"
          "hate = 3" <<endl;

    bool runner = true;
    while(runner)
    {
        cin >> rInput;
        switch (rInput) {
            case 0:
                rGallery.loveInt +=1;
                runner = false;
                break;                               //Prevents break from running where it shouldn't be
            case 1:
                rGallery.likeInt+= 1;
                runner = false;
                break;
            case 2:
                rGallery.dislikeInt += 1;
                runner = false;
                break;
            case 3:
                rGallery.hateInt +=1;
                runner = false;
                break;
            default:
                cout << "Please enter a correct input" <<endl;


        }
    }

}

void Post::SaveRToFile() const
{
    ofstream s;
    s.open("Output.txt", std::ios_base::app); //appends the file instead of overwrite
    s <<rGallery.loveInt << rGallery.likeInt
             <<rGallery.dislikeInt <<rGallery.hateInt;
    s.close();

}

