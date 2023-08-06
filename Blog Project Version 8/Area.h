//
// Area header fie
//

#ifndef BLOGPART3_CPP_AREA_H
#define BLOGPART3_CPP_AREA_H

#include <iostream>
#include "Post.h"
#include <vector>

using namespace std;

class Area {
public:

    friend ostream& operator <<(ostream& outputStream, const Area& area);
    bool equivilantPostChecker(const Post &) const; //Sees if a post has already been used

    int vecSize() const;

    // return the name of the Area
    string getName() const {
        return this->Name; //changed all objects to use the this key word
    };

    int getDeletedRuns() const{return this-> deletedRuns;};

    string getDescription() const {return this->Description;};


    void editPost(int i, const string & tit, const string & user,const string & text);

    void finalizeReactions(int love, int like, int dlike, int hate, int pIndex);

    void SaveReactions(){}

    //set the name of the Area
    void setName(string nm) {this -> Name = nm;};

    int getMaxNumPosts() const {return this->MAX_NUM_POSTS; //changed all objects to use the this key word
    };


    void DeletePost(int toErase); //erases the requested part of the vector


    void setDescription(string na){this -> Description = na;};

    // return the index of the last post
    int getIndxLastPost() const {return this -> indxLastPost;};

    int getPostArraySize() const {return Posts.size();};

    // add post
    int AddPost(Post p);

    // get post
    bool getPost(int i, Post &p);


private:
    string Name; //name of Area
    string Description; //The description of the area
    vector<Post> Posts;
    int deletedRuns = 0;
    int MAX_NUM_POSTS = 10;
    int indxLastPost = -1; //array index of last post in arary
};



#endif //BLOGPART3_CPP_AREA_H