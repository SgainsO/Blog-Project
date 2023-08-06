#include <iostream>
#include <vector>
#include <fstream>
#include "Post.h"
#include "Area.h"
#include "User.h"
#include "SuperUser.h"
// students - you need to put program header here
/* Name: (Jaskaran Chawla)
 * Date: (10/08/2022)
 * Section: (0011)
Assignment: (6)
 Due Date: (10/18/2022)
About this project: (Modify a previous assignment for reactional inputs)
Assumptions: (write any assumptions made here
 All work below was performed by (Jaskaran Chawla) */
using namespace std;


//number of Areas
const int NUM_AREAS = 5;    //2 changed to 5 for adding more Area


//////////////////////////////////////////////////////
//structure for post
/*struct Post {
    string Title; //title
    string Text; //text
    string User; //User
}; */

void DisplayStructer(Post, int);


//Area class
void SaveToFile(vector<Area> * areas);

////////////////////////////////////////////////////
// sets up Areas
void initAreas(vector<Area> *);

Post GetAreaAndAttributes(int & index, string & title, string & user, string & text,
                            const vector<Area> * areas, bool ignoreArea = false);

bool isTitle = false;

bool Validator(string, int, bool, Area);

void GetIndexs(int &, int &, vector<Area> *, bool useP = false);

//display menu
void displayMenu();

//User selects an action
void promptAction(string &strCh);

void DeleteAnArray(vector<Area> * areas);

//implement Action
void implementAction(vector<Area> *, string strCh, User *, SuperUser *, bool);

void DisplayBlogAreas(vector<Area> * areas);

void DisplayPostsABlog(Area a);

//ensures user only uses valid areas
void CheckIfAreaOutOfRange(int &);

//get a valid blog area id
int getValidBlogArea();

void GetFileData(vector<Area> * areas);

void login(vector<User*> & user, User & giveTo, SuperUser & sGto, bool& isSup);

bool Validator(string, int);  //THIS CHANGE MIGHT HAVE BROKE SOMETHING

void PopUserVector(vector<User*> & areas, const User&);

void deleteArray(vector<User*> users);


int main() {
    vector<User*> users;
    vector<Area> areas;
    User programUser;
    SuperUser SProUser;
    bool isSuper = false;               //Returns wheter a superuser is detected
    User EMPTY;
    PopUserVector(users, EMPTY);
    login(users, programUser, SProUser, isSuper);   //Stores both a super and non super user class
    Area a;




    if(isSuper)
    {
        cout << "------VIP DETECETED-------"<<endl;
    }


    //initAreas(&areas);
    GetFileData(&areas);  //Reads in data from a previous use
    //welcome
    cout << "------------------"<<endl;
    cout << "Hello " << programUser.getName() <<endl;
    cout << "Welcome to my Blog " << endl;

    string UserAction;
    do {
        promptAction(UserAction);
        implementAction(&areas,UserAction, &programUser, &SProUser, isSuper);

    } while ((UserAction != "Q") && (UserAction != "q"));
    //continue until user decides to quit



    deleteArray(users);
    return 0;
}

// sets up areas

//display menu
void displayMenu() {
    // display menu options to user
    cout << "Please select from the following options..." << endl;
    cout << " A  - Display Blog areas" << endl;
    cout << " B  - Display all posts for a blog" << endl;
    cout << " C  - Add a post to a blog" <<endl;
    cout << " D  - Display a post for a blog" << endl;
    cout << " E  - Edit a post" << endl;
    cout << " F  - Delete a post" << endl;      //new delete a post
    cout << " G  - Store Reaction" << endl;
    cout << " H  - Delete an area" << endl;
    cout << " X  - Ego Boost"<< endl;
    cout << " Q  - Quit" << endl;




}
void deleteArray(vector<User*> users)
{
    for(int i = (users.size()-1); i >= 0; i--){
        delete users[i];
    }



}


//User Action
void promptAction(string &strCh) {
    //display menu options to screen
    displayMenu();

    //prompt user for choice
    cout << "What would you like to do?" << endl;
    cin >> strCh;
}

void GetDataForEdit( string & title, string & userName, string & text){
    cout << "Please enter a title" << endl;
    cin.ignore();                       //Gets rid of stray "/n"
    getline(cin, title);
    cout << "Please enter a user name" <<endl;
    getline(cin, userName);
    cout << "please enter in the text" << endl;
    getline(cin, text);
}

//implement Users Action
void implementAction(vector<Area> * areas, string strCh, User * use, SuperUser * sup, bool isSuper) {
    bool titleCopy;
    int Aindex = 0, pindex = 0, ranAmount = 0;
    string title, user, text;
    User * u = nullptr;           //Establish an empty user
    if(isSuper) {
        u = sup;                  //set empty user to the super user location
        u->setUserType(User::SUPERUSER);    //Manually set user to superuser
    }
    else
        u = use;
    user = u->getUserName();
    // if user selected A
    if ((strCh == "A") || (strCh == "a")) {
        DisplayBlogAreas(areas);
    } else if ((strCh == "B") || (strCh == "b")) {
        cout << "Display all posts for a blog..." << endl;
        int blogId = getValidBlogArea();
        DisplayPostsABlog(areas->at(blogId));
    } else if ((strCh == "C") || (strCh == "c")) {  //Adds a post
        GetIndexs(pindex, Aindex, areas);                       //Finds the correct post to edit
        Post userPost;
            //Makes a new post class for the new posts
        userPost = GetAreaAndAttributes(Aindex,title,user,text, areas);
        areas->at(Aindex).AddPost(userPost);
        cout <<"Post Added"<<endl;
    } else if ((strCh == "D") || (strCh == "d")) {
        Post postToDisplay;
        GetIndexs(pindex, Aindex, areas, true);           //Finds both indexes so post can be displayed to screen
        //cout <<"Please enter in a valid post id for area: " << areas[Aindex].getName()<<endl;
        areas->at(Aindex).getPost(pindex, postToDisplay);
        DisplayStructer(postToDisplay, pindex);
    } else if((strCh == "E") || (strCh == "e")){
        Post placeHold;
        Post secondHold;
        GetIndexs(pindex, Aindex, areas, true);                       //Finds the correct post to edit
        areas->at(Aindex).getPost(pindex, placeHold);
        DisplayStructer(placeHold, pindex);
        secondHold = GetAreaAndAttributes(Aindex,title,user,text, areas);  //get user input
        areas->at(Aindex).editPost(pindex, secondHold.getTitle(), user, text);
        secondHold = {"","",""};
        cout <<"Post Edited"<<endl;
    }else if((strCh == "F") || (strCh == "f")){  //Delete Post
        GetIndexs(pindex, Aindex, areas, true);
        areas->at(Aindex).DeletePost(pindex);  //use vector functions to get rid of an area
        cout << "Post deleted" << endl;
    }else if((strCh == "G") || (strCh == "g")){
        Post displayF;
        int love, like, dlike, hate;                               //Make variables to hold structure data
        GetIndexs(pindex, Aindex, areas, true);
        areas->at(Aindex).getPost(pindex, displayF);
        cout <<displayF <<endl;
        displayF.enterReaction();
        displayF.ReturnGallery(love, like, dlike, hate);       //Give the reactions to variable so they can be transffered
        areas->at(Aindex).finalizeReactions(love, like, dlike, hate, pindex);
    }else if((strCh =="H") || strCh== "h"){

        if(u->getUserType() == 1)     //Only allows superusers to this function
        {
            string resp;
            cout << "This change is permenant, are you sure you would like to delete the area?" <<endl;
            cout << "Enter X if yes" << endl;
            cin >> resp;
            if(resp == "X" || resp == "x")
            {
                DeleteAnArray(areas);
            }
        }
        else
            cout << "You must be a superuser to enter into this area " <<endl;


    }else if((strCh =="X") ||(strCh== "x")){
        u->egoBooster();            // Boosts the ego of superusers
    }else if ((strCh == "Q") || (strCh == "q")) {
        SaveToFile(areas);
        cout << "Bye..." << endl;

    }


    else {
        //user has selected an invalid option
        cout << strCh << " is not a valid option." << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////

void DeleteAnArray(vector<Area> * areas){
    int resp;
    bool clear = false;          //validating bool
    cout << "Which area would you like to delete?" <<endl;
    cin >> resp;
    while(!clear) {
        if (resp > areas->size() || resp < 0)
            cout << "Please enter a valid index" <<endl;
        else
        {
            areas->erase(areas->begin() + resp);
            clear = true;       //erase the aray
        }
    }
}






void login(vector<User*> & user, User & giveTo, SuperUser & sGto, bool& isSuper)
{
    bool usingTectia; //Compensate for using a bad compiler

    int bigVali = 0;

    while (bigVali == 0) {
        User toCon;
        User *temp = &toCon;
        bool validatorBool = false;

        string inputLogin, inputPass, test;
        while (!validatorBool) {
            cout << "Login: " << endl;
            getline(cin, inputLogin);
            validatorBool = Validator(inputLogin, 10);
        }
        temp->setUserName(inputLogin);
        validatorBool = false;
        while (!validatorBool) {
            cout << "Password: " << endl;
            getline(cin, inputPass);
            validatorBool = Validator(inputPass, 20);
        }

        temp->setPassword(inputPass);
        bigVali = true;
        for(int i = 0;i <= (user.size()-1);i++){
            User * U = user[i];
            isSuper = U->getUserType();  //returns true is super user is detected
            if (*U == *temp) {
                if(isSuper){
                    sGto = U;
                    bigVali = 1;
                }
                else{
                    giveTo = *U;
                    bigVali = 1;
                    return;
                }
                bigVali = 1;
            } else{
                bigVali = false;
            }
        }
    }
}

void PopUserVector(vector<User*> & users, const User&){
    ifstream chek;
    string fileUser, fileLogin, filePassword;
    chek.open("userInfo.txt");
    if(!chek) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    User* u = NULL;
    int i = 0;
    while(chek)
    {
        getline(chek, fileUser);         //Get the file information
        getline(chek, fileLogin);
        getline(chek, filePassword);
        if(fileLogin == "Super") {//In the case of Sudo
            u = new SuperUser;
        }
        else {
            u = new User;
        }
        u->setName(fileUser);               //transfer file data to class
        u->setUserName(fileLogin);
        u->setPassword(filePassword);
        users.push_back(u);               //Fills the class vector
        if( chek.eof() ) break;
    }
    chek.close();

}

bool Validator(string title, int spacechecker) {
    int nWhiteSpaceCounter = 0;

    for (int i = 0; i < title.length(); i++)
    {
        if(isspace(title[i]) == false)
        {
            nWhiteSpaceCounter += 1;
        }

    }

    if((nWhiteSpaceCounter == 0) || (nWhiteSpaceCounter > spacechecker) )
        cout << "Please enter in a string with at least 1 character and at most " << spacechecker << " characters." <<endl;
    else
        return true;
}


void GetIndexs(int & pIndex,int & Aindex ,vector<Area> * areas, bool useP)
{
    do
    {
        cout << "Please enter in a Blog Area Index" << endl;
        cin >> Aindex;
    } while (Aindex < 0 || Aindex >= NUM_AREAS);

    while(areas->at(Aindex).getIndxLastPost() == -1){
        cout << "Please enter in a Blog Area Index" <<endl;
        cin >> Aindex;
    }

    if(useP) {          //Turns code off if finding pindex is unneccesary
        cout << "Please enter in a valid post id for area: " << areas->at(Aindex).getName() << endl;
        cin >> pIndex;
        while (areas->at(Aindex).getIndxLastPost() < pIndex || pIndex < 0) {
            cout << "Please enter in a valid post id for area: ";
            cin >> pIndex;
        }
    }

}

void DisplayStructer(Post o, int index){        //Prints out the entire structure.
    cout << "Post Index:" <<index << endl;
    cout << o <<endl;

}

/*bool Validator(string title, int spacechecker)
{
    int nWhiteSpaceCounter = 0;

    for (int i = 0; i < title.length(); i++)
    {
        if(isspace(title[i]) == false)
        {
            nWhiteSpaceCounter += 1;
        }

    }

   if((nWhiteSpaceCounter == 0) || (nWhiteSpaceCounter > spacechecker) )
       cout << "Please enter in a string with at least 1 character and at most " << spacechecker << " characters." <<endl;
   else
       return true;
}
*/




Post GetAreaAndAttributes(int & index, string & title, string & user, string & text, const vector<Area> * areas,
                          bool ignoreArea){
    bool validatorBool = false;
    Post P;
    bool vb2 = true;
    string title2;
    Area a;
   /* if (!ignoreArea) {
        cout << "Please enter in a Blog Area Index " << endl;      //gets required data
        cin >> index;
    }else if(ignoreArea){
        cout << "Choose new values" <<endl;
    } */
    CheckIfAreaOutOfRange(index);
    cin.ignore();                  //removes the /n from cin allowing getLine to function
    cout << "Please enter in the title..." << endl;

    while(!validatorBool || vb2) {
        getline(cin, title2);
        validatorBool = Validator(title2, 20);
        if(validatorBool) {
            P.editTitle(title2);                //Edit title before the loop finishes so it can be compared
            a = areas->at(index);
            vb2 = a.equivilantPostChecker(P);
            if (vb2) {
                cout << "Please choose a unique title..." << endl;
            }
        }
    }

    validatorBool = false;                     //Allows validator bool to run for the next functions
    /*while(validatorBool == false) {
        getline(cin, user);
        validatorBool = Validator(user, 10);
    } */
    P.editUser(user);
    cout << "Please enter in the text..." << endl;
    validatorBool = false;
    while (validatorBool == false){
        getline(cin, text);
        validatorBool = Validator(text, 500);
    }
    P.edittext(text);
    return P;
}

void CheckIfAreaOutOfRange(int & areaRequest) {
    while (NUM_AREAS < areaRequest) {
        cout << "please enter a valid area" << endl;
        cin >> areaRequest;
    }

}



////////////////////////////
void DisplayBlogAreas(vector<Area> * areas) {
    cout << "Display Blog areas..." << endl;
    //user has selected to display blog areas
    for (int i = 0; i < areas->size(); i++) {
        cout << "Area Index:" << i << endl;
        cout << areas->at(i) << endl;
        cout << "******************" << endl;
    }

}

//////////////////
void DisplayPostsABlog(Area a) {
    cout << "Posts for " << a.getName() << endl;
    int numOfIndex = a.getIndxLastPost() - a.getDeletedRuns();   //Accounts for runs that have been deleted
    //user has selected to display blog areas
    for (int i = 0; i <= numOfIndex; i++) {
        Post p;
        bool found = a.getPost(i, p);
        if (found) {
            cout << "Post Index:" << i << endl;
            cout << p << endl;     //Use of overloaded operator
            cout << "******************" << endl;
        }
    }

}

//////////////
int getValidBlogArea() {
    int area = -1;
    //prompt and read in Blog Area Index
    cout << "Please enter in a Blog Area Index" << endl;
    cin >> area;
    if(cin.fail()){           //prevents code from crashing when given alphabeticals
        cin.ignore();
        cin.clear();
        cout << "Only numerical inputs area accepted" <<endl;
    }
    //input validation loop
    while ((area < 0) || (area >= NUM_AREAS)) {
        cout << "Please enter in a Blog Area Index" << endl;
        cin >> area;
        if(cin.fail()){           //prevents code from crashing when given alphabeticals
            cin.ignore();
            cin.clear();
            cout << "Only numerical inputs area accepted" <<endl;
        }
    }
    //return valid Blog Area Index
    return area;
}

////////////////////////
/////////////////////////
// add post

//Operator overload functions

ostream& operator <<(ostream& outputStream, const Area& area){
   outputStream << "Area: " << area.getName() << endl
   << "Description: " << area.getDescription() <<endl;
       return outputStream;
}


ostream& operator <<(ostream& outputStream, const Post& p){
    outputStream <<"Title: " << p.getTitle() << endl
                  <<"User: " <<p.getUser() << endl          //Outputs all when the operator is used
                  <<"Text: " <<p.getText()<<endl;
    int mathCheck = p.rGallery.hateInt+p.rGallery.dislikeInt;
    mathCheck += p.rGallery.likeInt;
    mathCheck += p.rGallery.loveInt;
    if (mathCheck == 0) {                                   //Standard input for if there is nothing in the structure
        outputStream << "There are no reactions" << endl;
    } else {
        p.displayStructure();
    }


    return outputStream;
}
////////File Operation Functions//////////
void SaveToFile(vector<Area> * areas)
{
    Post toTransfer;
    int love, like, hate, dislike;
    string in = "fu";
    ofstream saveFile, descriptions;     //Makes instances of the files which will link them to the program
    saveFile.open("Output.txt");      // Opens text file
    descriptions.open("desc.txt");
    if(!saveFile) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    saveFile.flush(); //Frees up memory
    for(int i = 0; i < areas->size(); i++)
    {
        for (int j = 0; j <= areas->at(i).getIndxLastPost(); j++)
        {    saveFile << i <<endl;
             areas->at(i).getPost(j, toTransfer);
             saveFile << toTransfer.getTitle() <<endl;
             saveFile << toTransfer.getUser() <<endl;
             saveFile << toTransfer.getText() <<endl;
             toTransfer.ReturnGallery(love, like, dislike, hate);
             saveFile << love << " "<< like << " "
             << dislike << " " << hate << endl;
             saveFile.flush();
        }
    descriptions << i << endl;
    descriptions << areas->at(i).getName() << endl;
    descriptions << areas->at(i).getDescription() <<endl;
    descriptions.flush();
    }
    descriptions.close();
    saveFile.close();
    cout << "Saved" <<endl;
}

void GetFileData(vector<Area> * areas)
{
ifstream init;
ifstream descIm;
int tempRpop[4] = {0,0,0,0};    //stores reaction inputs
init.open("Output.txt");
descIm.open("desc.txt");
    if(!init) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
int index = 0;
    int t = 0;
Post tempPost;
string desc, intempt,title, userName, text, temp, ptitle;

Area Atemp;
while(descIm>>index)
{
    descIm.ignore();
    getline(descIm,ptitle);
    getline(descIm, desc);
    Atemp.setName(ptitle);
    Atemp.setDescription(desc);
    areas->push_back(Atemp);
}


while(init)   //Read in every index of the line in the file
{
    init >> index;
    init.ignore();
    getline(init, title);    //allows the variables to include spaces
    getline(init,userName);
    getline(init,text);
    //init.ignore();
    init >> tempRpop[0] >> tempRpop[1];
    init >> tempRpop[2] >> tempRpop[3];
    tempPost.editTitle(title);
    tempPost.editUser(userName);
    tempPost.edittext(text);
    tempPost.Pop_Structer(tempRpop[0], tempRpop[1], tempRpop[2], tempRpop[3]);
    areas->at(index).AddPost(tempPost);     //Adds the post to memory
}


init.close();         //closes the file
descIm.close();
}













///////////////////////////////////////
const std::string WHITESPACE = " \n\r\t\f\v";

///////////////////////////
//Left trim - remove all white space characters on the left
string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

//Right trim - remove all white space characters on the right
string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

//Trim - remove all white space characters on the left or right
string trim(const std::string &s) {
    return rtrim(ltrim(s));
}




