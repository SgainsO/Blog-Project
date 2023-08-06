//
// Area implementation file
//

#include "Area.h"

int Area::AddPost(Post p) {
    //validate that less than MAX_NUM_POSTS have been added
    // to this blog
    if (this->indxLastPost + 1 < this->MAX_NUM_POSTS) {
        //incr indxLastPost
        this->Posts.push_back(p);
        this->indxLastPost++;
        //set indxLastPost to p
        this->Posts[indxLastPost] = p;
        //return 1 - added]
        return 1;
    } else
        //invalid no room for new post
        return -1;
}

////////////////////// equivilancy function

bool Area :: equivilantPostChecker(const Post & toCheck) const      //Sees if a post has already been used
{
    for(int i = 0;i < this->Posts.capacity() ;i++){          //Loops through all stored posts to check for repeats
        if(this->Posts[i] == toCheck)   //Application of overloaded operators
        {

            return true;
            break;
        }

    }
    return false;
}

/*int Area :: vecSize() const      //Sees if a post has already been used
{
    cout << Posts.size() <<endl;
    return Posts.size();
} */

void Area ::editPost(int i, const std::string &tit, const std::string &user,
                     const std::string &text) {
    //Const refrences to save on data
    string tempVar; //Temporary string
    this -> Posts[i].editTitle(tit);    //accesing a post array function.
    this -> Posts[i].editUser(user);
    this -> Posts[i].edittext(text);
}

bool Area ::getPost(int i, Post &p){
    if (i <= this->indxLastPost) // i is valid
    {
        p = this->Posts[i]; //set post
        return true; //return true
    } else { //i is not valid
        return false; //return false
    }
}

void Area ::DeletePost(int toErase)
{this->Posts.erase(this->Posts.begin()+ toErase);
    //this->deletedRuns++;
    this->indxLastPost--;
}

void Area :: finalizeReactions(int love, int like, int dlike, int hate, int pIndex){
    Posts[pIndex].Pop_Structer(love, like, dlike,hate);
}