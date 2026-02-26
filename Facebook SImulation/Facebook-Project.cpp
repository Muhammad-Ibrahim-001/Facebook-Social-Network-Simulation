#include<iostream>
#include<fstream>
#include <ctime>
#include<string>
#include<cstdlib>
using namespace std;

class Helper;
class Date;
class Memory;
class User;
class Page;
class Post;
class Object;
class Comment;
class Controller;



class helper
{
public:

	static int StringLength(const char* str)
	{
		int Length = 0;
		while (*str != '\0') { Length++;str++; }
		return Length;
	}

	static void GetStringFromBuffer(char*& str, const char* buffer)
	{
		int iterator;
		str = new char[StringLength(buffer) + 1];
		for (iterator = 0;iterator <= StringLength(buffer);iterator++) { str[iterator] = buffer[iterator]; }
	}

	static int strCmp(char* str)
	{
		if (*str++ == '-' && *str++ == '1' && *str == '\0')
			return -1;
		return 0;
	}
	static char* ConcatenateString(const char* str1, char* str2)
	{
		int sizeOne = StringLength(str1);
		int sizeTwo = StringLength(str2) + 1;
		int end = sizeOne + sizeTwo;
		char* str = new char[sizeOne + sizeTwo];

		for (int i = 0;i < end;i++)
		{
			if (i < sizeOne)
				str[i] = str1[i];
			else if (i >= sizeOne)
				str[i] = str2[i - sizeOne];
		}
		return str;
	}
	static char* ToString(int num, int choice)
	{
		int count = 0;
		int temp = num;
		while (temp != 0)
		{
			temp /= 10;
			count++;
		}
		if (choice == 1)
		{
			char* Ch = new char[count + 2];
			Ch[0] = 'c';
			int i = count;
			while (num != 0)
			{
				int rem = num % 10;
				Ch[i] = char(rem + '0');
				i--;
				num /= 10;
			}
			Ch[count + 1] = '\0';
			return Ch;
		}
		else
		{
			char* Ch = new char[count + 5];
			Ch[0] = 'p';
			Ch[1] = 'o';
			Ch[2] = 's';
			Ch[3] = 't';

			int i = 4 + count - 1;
			while (num != 0)
			{
				int rem = num % 10;
				Ch[i] = char(rem + '0');
				i--;
				num /= 10;
			}
			Ch[count + 4] = '\0';
			return Ch;
		}
	}
};

class Date
{
	static Date Today;
	int day;
	int month;
	int year;
public:
	Date();
	void setDay(int);
	void setMonth(int);
	void setYear(int);
	int getDay();
	int getYear();
	int getMonth();
	static void setToday(int, int, int);
	static int getTodayDay();
	static int getTodayMonth();
	static int getTodayYear();
};
Date Date::Today = Date();
Date::Date()
{
	day = 00;
	month = 00;
	year = 00;
}
void Date::setDay(int Day) { day = Day; }
void Date::setMonth(int Month) { month = Month; }
void Date::setYear(int Year) { year = Year; }
int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }
int Date::getTodayDay() { return Today.day; }
int Date::getTodayMonth() { return Today.month; }
int Date::getTodayYear() { return Today.year; }
void Date::setToday(int d, int m, int y)
{
	Today.day = d;
	Today.month = m;
	Today.year = y;
}

class Object
{
protected:
	int NumberOfSharedPosts;
	Post** PostShared;
	char* ID;
public:
	Object();
	virtual ~Object();
	char* getID();
	virtual void viewDetails() = 0;
	virtual void AddPostToTimeLine(Post*) = 0;
	virtual void getName() = 0;
	virtual void sortTimeline() = 0;
};
Object::Object()
{
	PostShared = nullptr;
	ID = nullptr;
	NumberOfSharedPosts = 0;
}
Object::~Object()
{
	if (ID) delete[] ID;

}
char* Object::getID()
{
	return ID;
}



class Comment {
	char* ID;
	Object* PostedBy;
	char* Comment_discription;
public:
	Comment();
	Comment(const char*, Object*, const char*);
	~Comment();
	void printComments();
};
Comment::Comment()
{
	ID = nullptr;
	Comment_discription = nullptr;
	PostedBy = nullptr;
}
Comment::~Comment()
{
	if (ID) delete[] ID;
	if (Comment_discription) delete[] Comment_discription;
}
Comment::Comment(const char* id, Object* commentedby, const char* desc)
{

	helper::GetStringFromBuffer(ID, id);
	PostedBy = commentedby;
	helper::GetStringFromBuffer(Comment_discription, desc);
}
void Comment::printComments() { cout << "\t\t";PostedBy->getName();cout << " : \" " << Comment_discription << "\"" << endl; }


class Post
{
protected:
	char* ID;
	char* Text;
	int numberofComments;
	int NumberofLikes;
	Object* sharedBy;
	Object** LikedBy;
	Comment** CommentsOnPost;
	static int TPosts;
public:
	Date date;
	Post();
	Post(const Post&);
	~Post();
	void ReadDataFromFile(ifstream&);
	void AddLikedBy(Object*);
	virtual void viewPost(bool);
	void viewLikeBy();
	void AddComment(const char*, Object*, const char*);
	char* getID();
	bool checkDate();
	bool checckEqual();
	void setSharedBy(Object*);
	static int getTPosts();
	static void setTPosts(int);
	char* getText();
	void viewComments();
};
int Post::TPosts = 0;
Post::Post() :date()
{
	ID = nullptr;
	LikedBy = nullptr;
	sharedBy = nullptr;
	Text = nullptr;
	CommentsOnPost = nullptr;
	numberofComments = 0;
	NumberofLikes = 0;
}
Post::Post(const Post& obj)
{
	helper::GetStringFromBuffer(ID, obj.ID);
	helper::GetStringFromBuffer(Text, obj.Text);
	sharedBy = obj.sharedBy;
	numberofComments = obj.numberofComments;
	NumberofLikes = obj.NumberofLikes;
	CommentsOnPost = new Comment * [10];
	LikedBy = new Object * [10];
	for (int i = 0;i < numberofComments;i++)
	{
		CommentsOnPost[i] = obj.CommentsOnPost[i];
	}
	for (int i = 0;i < NumberofLikes;i++)
	{
		LikedBy[i] = obj.LikedBy[i];
	}
	date = obj.date;
}
Post::~Post()
{
	if (ID)	delete[] ID;
	if (Text) delete[] Text;
	if (LikedBy) delete[] LikedBy;
	for (int i = 0;i < numberofComments;i++)
	{
		delete CommentsOnPost[i];
	}
	sharedBy = nullptr;
	LikedBy = nullptr;
}
void Post::ReadDataFromFile(ifstream& fin)
{
	char buffer[80];
	int Temp;

	fin >> buffer;
	helper::GetStringFromBuffer(ID, buffer);

	fin >> Temp;
	date.setDay(Temp);

	fin >> Temp;
	date.setMonth(Temp);

	fin >> Temp;
	date.setYear(Temp);
	fin.ignore(1, '\n');
	fin.getline(buffer, 80, '\n');
	helper::GetStringFromBuffer(Text, buffer);
}
void Post::setSharedBy(Object* var)
{
	sharedBy = var;
}
void Post::AddLikedBy(Object* Like)
{
	if (NumberofLikes == 0)
		LikedBy = new Object * [10];
	if (NumberofLikes <= 10)
		LikedBy[NumberofLikes++] = Like;
	else { cout << "Maximum Like On a Post limit Reached" << endl; }
}
void Post::viewPost(bool choice = 0)
{
	sharedBy->getName();
	if (date.getTodayMonth() == date.getMonth() && date.getTodayYear() == date.getYear())
	{
		if ((date.getTodayDay() - date.getDay()) == 0)
		{
			cout << "(1H)" << endl;
		}
		else
		{
			cout << "(" << date.getTodayDay() - date.getDay() << "D)" << endl;
		}
	}
	else
	{
		cout << "(" << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << ")" << endl;

	}
	cout << "\t" << Text << endl;
	if (choice == 0)
		viewComments();
}
void Post::viewLikeBy()
{
	for (int i = 0;i < NumberofLikes;i++)
	{
		LikedBy[i]->viewDetails();
	}
}
void Post::AddComment(const char* ID, Object* userCommented, const char* description)
{
	if (numberofComments == 0)
	{
		CommentsOnPost = new Comment * [10];
	}
	if (numberofComments <= 10)
		CommentsOnPost[numberofComments++] = new Comment(ID, userCommented, description);
	else { cout << "Number Of Comments on a post reached its Limits" << endl; }
}
int Post::getTPosts()
{
	return TPosts;
}
void Post::setTPosts(int temp)
{
	TPosts = temp;
}
char* Post::getID()
{
	return ID;
}
bool Post::checkDate()
{
	if ((date.getTodayDay() - date.getDay() >= 0) && (date.getTodayDay() - date.getDay() <= 3) && (date.getTodayMonth() == date.getMonth()) && date.getTodayYear() == date.getYear())
	{
		return 1;
	}
	return 0;
}
bool Post::checckEqual()
{
	if (date.getTodayMonth() == date.getMonth() && date.getDay() == date.getTodayDay() && date.getTodayYear() != date.getYear())
	{
		return 1;
	}
	return 0;
}
char* Post::getText()
{
	return Text;
}
void Post::viewComments()
{
	for (int i = 0;i < numberofComments;i++)
		CommentsOnPost[i]->printComments();
}



class Page :public Object
{
private:
	char* Title;
	static int TPages;
public:
	Page();
	~Page();
	void getName();
	void viewDetails();
	static int getTPages();
	static void setTPages(int);
	void AddPostToTimeLine(Post*);
	void ReadDataFromFile(ifstream&);
	void viewTimeline();
	Post** getPostShared();
	int getTotalPostShared();
	void sortTimeline();
};
int Page::TPages = 0;
Page::Page() {
	Title = nullptr;
}
Page::~Page()
{
	if (Title)	delete Title;
	for (int i = 0; i < NumberOfSharedPosts; i++)
	{
		delete PostShared[i];
	}
}
void Page::viewDetails()
{
	cout << ID << " - "
		<< Title << endl;
}
void Page::AddPostToTimeLine(Post* post)
{
	if (NumberOfSharedPosts == 0)
		PostShared = new Post * [10];
	if (NumberOfSharedPosts <= 10)
		PostShared[NumberOfSharedPosts++] = post;
	else { cout << "Timeline Posts Limit Reached" << endl; }
}
void Page::viewTimeline()
{
	for (int i = 0;i < NumberOfSharedPosts;i++)
	{
		PostShared[i]->viewPost();
	}
}
void Page::ReadDataFromFile(ifstream& fin)
{
	char buffer[80];

	fin >> buffer;
	helper::GetStringFromBuffer(ID, buffer);

	fin.ignore(1, '\t');

	fin.getline(buffer, 80);
	helper::GetStringFromBuffer(Title, buffer);
}
int  Page::getTPages()
{
	return TPages;
}
void Page::setTPages(int temp)
{
	TPages = temp;
}
void Page::getName()
{
	cout << Title;
}
Post** Page::getPostShared()
{
	return PostShared;
}
int Page::getTotalPostShared()
{
	return NumberOfSharedPosts;
}
void Page::sortTimeline()
{
	for (int i = 0;i < NumberOfSharedPosts;i++)
	{
		for (int j = i + 1;j < NumberOfSharedPosts;j++)
		{
			if (PostShared[i]->date.getYear() < PostShared[j]->date.getYear())
			{
				Post* Temp = PostShared[i];
				PostShared[i] = PostShared[j];
				PostShared[j] = Temp;
			}
			else if (PostShared[i]->date.getYear() == PostShared[j]->date.getYear() && PostShared[i]->date.getMonth() < PostShared[j]->date.getMonth())
			{
				Post* Temp = PostShared[i];
				PostShared[i] = PostShared[j];
				PostShared[j] = Temp;
			}
			else if (PostShared[i]->date.getYear() == PostShared[j]->date.getYear() && PostShared[i]->date.getMonth() == PostShared[j]->date.getMonth() && PostShared[i]->date.getDay() < PostShared[j]->date.getDay())
			{
				Post* Temp = PostShared[i];
				PostShared[i] = PostShared[j];
				PostShared[j] = Temp;
			}
		}
	}
}


class Memory :public Post
{
	Post* originalPost;
public:
	Memory(Post*, Object*, const char*);
	void viewPost(bool);
};


Memory::Memory(Post* PointTO, Object* userShared, const char* text)
{
	TPosts++;
	char* pID = helper::ToString(TPosts, 2);
	originalPost = PointTO;
	sharedBy = userShared;
	helper::GetStringFromBuffer(Text, text);
	helper::GetStringFromBuffer(ID, pID);
	LikedBy = nullptr;
	CommentsOnPost = nullptr;
	numberofComments = 0;
	NumberofLikes = 0;
	date.setDay(date.getTodayDay());
	date.setMonth(date.getTodayMonth());
	date.setYear(date.getTodayYear());
}
void Memory::viewPost(bool choice=0)
{
	sharedBy->getName();
	if (this->checkDate())
		cout << "(1h)" << endl;
	cout << "\t" << Text << endl;
	cout << "\t~~~~~~~" << Date::getTodayYear() - originalPost->date.getYear() << "Years Ago ~~~~~~~" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	originalPost->viewPost(1);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	viewComments();
	viewLikeBy();
}



class User :public Object
{
	char* Fname;
	char* Lname;
	int totalpages;
	int totalfriends;
	int totalMemories;
	User** FriendList;
	Page** LikedPages;
	static int TUsers;
public:
	User();
	~User();
	void ReadDataFromFile(ifstream&);
	void LikePage(Page*&);
	void viewTimeline();
	void getName();
	void viewDetails();
	void sortTimeline();
	void ViewHomePage();
	void ViewFriendList();
	void ViewLikedPages();
	void AddFriend(User*&);
	static int getTUsers();
	static void setTUsers(int);
	void AddPostToTimeLine(Post*);
	void SeeMemories();
	Post* ShareMemories(Post*, const char*);
};
int User::TUsers = 0;
User::User()
{
	totalfriends = 0;
	totalpages = 0;
	ID = nullptr;
	Fname = nullptr;
	Lname = nullptr;
	FriendList = nullptr;
	LikedPages = nullptr;
	totalMemories = 0;
}
User::~User()
{
	for (int i = 0; i < NumberOfSharedPosts; i++)
	{
		delete PostShared[i];
	}
	if (Fname)	delete[] Fname;
	if (Lname)	delete[] Lname;
	if (FriendList) delete[] FriendList;
	if (LikedPages) delete[] LikedPages;
}
void User::ViewHomePage()
{
	for (int i = 0;i < NumberOfSharedPosts;i++)
	{
		if (PostShared[i]->checkDate())
			PostShared[i]->viewPost();
	}
	for (int i = 0;i < totalfriends;i++)
	{
		for (int j = 0;j < FriendList[i]->NumberOfSharedPosts;j++)
		{
			if (FriendList[i]->PostShared[j]->checkDate())
				FriendList[i]->PostShared[j]->viewPost();
		}
	}
	for (int i = 0;i < totalpages;i++)
	{
		for (int j = 0;j < LikedPages[i]->getTotalPostShared();j++)
		{
			if (LikedPages[i]->getPostShared()[j]->checkDate())
				LikedPages[i]->getPostShared()[j]->viewPost();
		}

	}
}
void User::viewDetails()
{
	cout << ID << " - " << Fname << " " << Lname << endl;
}
void User::ReadDataFromFile(ifstream& fin)
{
	char buffer[20];

	fin >> buffer;
	helper::GetStringFromBuffer(ID, buffer);

	fin >> buffer;
	helper::GetStringFromBuffer(Fname, buffer);

	fin >> buffer;
	helper::GetStringFromBuffer(Lname, buffer);
}
void User::AddFriend(User*& obj)
{
	if (totalfriends == 0)
		FriendList = new User * [10];
	if (totalfriends <= 10)
		FriendList[totalfriends++] = obj;
	else { cout << "Maximum Friends Limit reached" << endl; }
}
void User::LikePage(Page*& obj)
{
	if (totalpages == 0)
		LikedPages = new Page * [10];
	if (totalpages <= 10)
		LikedPages[totalpages++] = obj;
	else { cout << "Maximum Post Likes have been reached" << endl; }
}
void User::ViewFriendList()
{
	for (int i = 0;i < totalfriends;i++)
		cout << FriendList[i]->ID << " - " << FriendList[i]->Fname << " " << FriendList[i]->Lname << endl;
}
void User::ViewLikedPages()
{
	for (int i = 0;i < totalpages;i++)
		LikedPages[i]->viewDetails();
}
void User::AddPostToTimeLine(Post* post)
{

	if (NumberOfSharedPosts == 0)
		PostShared = new Post * [10];
	PostShared[NumberOfSharedPosts++] = post;

}
void User::viewTimeline()
{
	for (int i = 0;i < NumberOfSharedPosts;i++)
	{
		PostShared[i]->viewPost();
	}
}
void User::sortTimeline()
{
	for (int i = 0;i < NumberOfSharedPosts;i++)
	{
		for (int j = i + 1;j < NumberOfSharedPosts;j++)
		{
			if (PostShared[i]->date.getYear() < PostShared[j]->date.getYear())
			{
				Post* Temp = PostShared[i];
				PostShared[i] = PostShared[j];
				PostShared[j] = Temp;
			}
			else if (PostShared[i]->date.getYear() == PostShared[j]->date.getYear() && PostShared[i]->date.getMonth() < PostShared[j]->date.getMonth())
			{
				Post* Temp = PostShared[i];
				PostShared[i] = PostShared[j];
				PostShared[j] = Temp;
			}
			else if (PostShared[i]->date.getYear() == PostShared[j]->date.getYear() && PostShared[i]->date.getMonth() == PostShared[j]->date.getMonth() && PostShared[i]->date.getDay() < PostShared[j]->date.getDay())
			{
				Post* Temp = PostShared[i];
				PostShared[i] = PostShared[j];
				PostShared[j] = Temp;
			}
		}
	}
}
int User::getTUsers()
{
	return TUsers;
}
void User::setTUsers(int temp)
{
	TUsers = temp;
}
void User::getName()
{
	cout << Fname << " " << Lname;
}
void User::SeeMemories()
{
	cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago." << endl;
	for (int i = 0;i < NumberOfSharedPosts;i++)
	{
		if (PostShared[i]->checckEqual())
		{
			cout << "On this Day" << endl;
			cout << Date::getTodayYear() - PostShared[i]->date.getYear() << "Years Ago" << endl << endl;
			cout << "----";PostShared[i]->viewPost();
			cout << "--------------------------------------------------------------------------------------" << endl;
		}
	}
	cout << "\n\n\n\n";

}
Post* User::ShareMemories(Post* postMemory, const char* text)
{
	if (postMemory->checckEqual())
	{
		PostShared[NumberOfSharedPosts++] = new Memory(postMemory, this, text);
		return PostShared[NumberOfSharedPosts - 1];
	}
	else {
		cout << "No post have been Found As a memory" << endl;
		return nullptr;
	}
}







class Controller
{
private:
	User* CurrentUser;
	User** AllUsers;
	Page** AllPages;
	Post** AllPosts;
	int totalComments;
public:
	Controller();
	~Controller();
	void Run();
	void LoadAllData();
	void LoadAllComments(const char*);
	void LoadAllUsers(const char*);
	void LoadAllPages(const char*);
	void LoadAllPosts(const char*);
	void LikeAPost(const char*);
	void PostAComment(const char*, const char*);
	void setCurrentDate(int, int, int);
	void setCurrentUser(const char*);
	void LinkUsersandPages(const char*);
	Post* SearchPostByID(const char*);
	User* SearchUserByID(const char*);
	Page* SearchPageByID(const char*);
	Object& searchObjByID(const char*);
	void ShareMemories(const char*, const char*);
};
Controller::Controller()
{
	totalComments = 0;
	AllUsers = nullptr;
	AllPages = nullptr;
	AllPosts = nullptr;
	CurrentUser = nullptr;
}
Controller::~Controller()
{
	int TUsers = AllUsers[0]->getTUsers();
	int TPages = AllPages[0]->getTPages();
	for (int i = 0;i < TUsers;i++) { delete AllUsers[i]; }
	for (int i = 0;i < TPages;i++) { delete AllPages[i]; }
}
void Controller::LoadAllData()
{
	LoadAllUsers("Users.txt");
	LoadAllPages("Pages.txt");
	LoadAllPosts("Posts.txt");
	LoadAllComments("comments.txt");
	LinkUsersandPages("FriendListAndLikedPages.txt");
}
void Controller::LoadAllUsers(const char* UserFile)
{
	ifstream fin(UserFile);
	int Tusers;

	fin >> Tusers;
	AllUsers = new User * [Tusers];

	for (int i = 0;i < Tusers;i++)
	{
		AllUsers[i] = new User();
		AllUsers[i]->ReadDataFromFile(fin);
	}
	AllUsers[0]->setTUsers(Tusers);
}
void Controller::LoadAllPages(const char* PagesFile)
{
	ifstream fin(PagesFile);
	int Tpages;

	fin >> Tpages;
	AllPages = new Page * [Tpages];

	for (int i = 0;i < Tpages;i++)
	{
		AllPages[i] = new Page();
		AllPages[i]->ReadDataFromFile(fin);
	}
	AllPages[0]->setTPages(Tpages);
}
void Controller::LoadAllPosts(const char* PostsFile)
{
	ifstream fin(PostsFile);
	int Tposts, j = 0;
	char buffer[20];

	fin >> Tposts;
	AllPosts = new Post * [Tposts];

	for (int i = 0;i < Tposts;i++)
	{
		AllPosts[i] = new Post();
		AllPosts[i]->ReadDataFromFile(fin);

		fin >> buffer;

		AllPosts[i]->setSharedBy(&searchObjByID(buffer));
		Object* Temp = &searchObjByID(buffer);
		Temp->AddPostToTimeLine(AllPosts[i]);

		fin >> buffer;

		while (helper::strCmp(buffer) != -1)
		{
			AllPosts[i]->AddLikedBy(&searchObjByID(buffer));
			fin >> buffer;
		}
	}
	AllPosts[0]->setTPosts(Tposts);
}
void Controller::LoadAllComments(const char* CommentFile)
{
	ifstream fin(CommentFile);
	char bufferID[80];
	char buffer[80];

	fin >> totalComments;
	for (int i = 0;i < totalComments;i++)
	{
		fin >> bufferID;


		fin >> buffer;
		Post* temp = SearchPostByID(buffer);

		fin >> buffer;
		Object* temporary = &searchObjByID(buffer);

		fin.ignore(1, '\t');
		fin.getline(buffer, 80);

		temp->AddComment(bufferID, temporary, buffer);
	}
}
void Controller::LinkUsersandPages(const char* Linkingfile)
{
	ifstream fin(Linkingfile);
	char buffer[80];

	while (!fin.eof())
	{
		fin >> buffer;

		if (helper::strCmp(buffer) == -1) { break; }

		User* temp = SearchUserByID(buffer);

		if (temp)
		{
			fin >> buffer;

			while (helper::strCmp(buffer) != -1)
			{
				User* Temp2 = SearchUserByID(buffer);

				if (Temp2) { temp->AddFriend(Temp2); }

				else { cout << "Not Found" << endl;break; }

				fin >> buffer;
			}
		}
		else
		{
			cout << "Not Found!!" << endl;
		}

		fin >> buffer;

		while (helper::strCmp(buffer) != -1)
		{
			Page* temp2 = SearchPageByID(buffer);

			if (temp2)
			{
				temp->LikePage(temp2);
				fin >> buffer;
			}
			else
			{
				cout << "Not found" << endl;
				break;
			}
		}
	}
}
Page* Controller::SearchPageByID(const char* str)
{
	bool flag = false;
	int total = AllPages[0]->getTPages();

	for (int i = 0;i < total;i++)
	{
		for (int j = 0;str[j] != '\0';j++)
		{
			if (str[j] != AllPages[i]->getID()[j]) { flag = false;break; }
			else { flag = true; }
		}
		if (flag == true) { return AllPages[i]; }
	}
	return nullptr;
}
User* Controller::SearchUserByID(const char* str)
{
	bool flag = false;
	int total = AllUsers[0]->getTUsers();


	for (int i = 0;i < total;i++)
	{
		for (int j = 0;str[j] != '\0';j++)
		{
			if (str[j] != AllUsers[i]->getID()[j]) { flag = false;break; }
			else { flag = true; }
		}
		if (flag == true) { return AllUsers[i]; }
	}

	return nullptr;
}
Object& Controller::searchObjByID(const char* Str)
{
	if (*Str == 'u')
	{
		return *SearchUserByID(Str);
	}
	else
	{
		return *SearchPageByID(Str);
	}
}
Post* Controller::SearchPostByID(const char* str)
{
	bool flag = false;
	int total = Post::getTPosts();


	for (int i = 0;i < total;i++)
	{
		for (int j = 0;str[j] != '\0';j++)
		{
			if (str[j] != AllPosts[i]->getID()[j]) { flag = false;break; }
			else { flag = true; }
		}
		if (flag == true) { return AllPosts[i]; }
	}

	return nullptr;
}
void Controller::setCurrentUser(const char* ID)
{
	CurrentUser = SearchUserByID(ID);
	if (CurrentUser) { CurrentUser->getName();cout << " successfully set as Current User" << endl << endl << endl; }
	else { cout << "No user Has been Found with this ID" << endl; }
}
void Controller::setCurrentDate(int d, int m, int y)
{
	Date::setToday(d, m, y);
	cout << "Current Has been Set to " << d << "/" << m << "/" << y << endl;
}
void Controller::PostAComment(const char* str, const char* text)
{
	Post* temp = SearchPostByID(str);
	if (temp)
	{

		//char* CID=helper::ConcatenateString;
		char* CommentID = helper::ToString(++totalComments, 1);
		temp->AddComment(CommentID, CurrentUser, text);
	}
	else
	{
		cout << "No Post was Found with this ID" << endl;
	}
}
void Controller::LikeAPost(const char* post_id)
{
	Post* post = SearchPostByID(post_id);
	if (post) post->AddLikedBy(CurrentUser);
	else cout << "No Post with this ID Has Been Posted" << endl;
}
void Controller::ShareMemories(const char* Npost, const char* Desc)
{
	int total = Post::getTPosts() + 1;
	Post** temp = new Post * [total];
	for (int i = 0;i < total - 1;i++)
	{
		temp[i] = AllPosts[i];
	}
	delete[] AllPosts;
	AllPosts = temp;
	Post* tempo = SearchPostByID(Npost);

	AllPosts[total - 1] = CurrentUser->ShareMemories(tempo, Desc);
}
void Controller::Run()
{
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Command:                       Set current System Date 17 4 2024" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	int DAY = 17, MONTH = 4, YEAR = 2024;
	//cout << "Set current Date" << endl;
	//cin >> DAY;
	//cin >> MONTH;
	//cin >> YEAR;
	setCurrentDate(DAY, MONTH, YEAR);
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Command:                        Set current user u7" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	char buffer[4] = "u7";
	//cout << "Enter User ID :";
	//cin >> buffer;
	setCurrentUser(buffer);
	CurrentUser->viewDetails();
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Command:                        View Friend List" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	CurrentUser->getName();cout << " - Friend List" << endl << endl << endl;
	CurrentUser->ViewFriendList();
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         View Liked Pages" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	CurrentUser->getName();cout << " - Liked Pages" << endl << endl << endl;
	CurrentUser->ViewLikedPages();
	cout << "---------------------------------------------------------------------------------------------------------------\n\n\n\n" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         View Timeline" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	CurrentUser->getName();cout << " - TimeLine" << endl << endl << endl;
	CurrentUser->viewTimeline();
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         View Liked List" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	char Postbuffer[7] = "post5";
	//cout << "Enter the Post Id:";
	//cin >> Postbuffer;
	Post* post = SearchPostByID(Postbuffer);
	if (post)	post->viewLikeBy();
	else cout << "No Post with this ID Has Been Posted" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         Like A Post" << endl;
	cout << "Comand:                         View Liked List" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	//cout << "Enter the Post Id:";
	//cin >> Postbuffer;
	LikeAPost(Postbuffer);
	post->viewLikeBy();
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         View Page" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	char buffer2[4] = "p1";
	//cout << "Enter Page : ";
	//cin >> buffer2;
	Page* CurrentPage = SearchPageByID(buffer2);
	CurrentPage->viewTimeline();
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         View Home" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	CurrentUser->ViewHomePage();
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         Post Comment" << endl;
	cout << "Comand:                         View Post" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;

	char bufferComment[80] = "Good luck For Your Result";
	char PostId[7] = "post4";
	//cin >> PostId;
	//cin.getline(bufferComment, 80);
	PostAComment(PostId, bufferComment);
	SearchPostByID(PostId)->viewPost();
	char bufferComment2[80] = "Thank You for the wishes";
	char PostId2[7] = "post8";
	//cin >> PostId2;
	//cin.getline(bufferComment2, 80);
	PostAComment(PostId2, bufferComment2);
	SearchPostByID(PostId2)->viewPost();

	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         View Home" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	CurrentUser->ViewHomePage();

	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         SeeYourMemories()" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	CurrentUser->SeeMemories();

	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         ShareYourMemories()" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;

	ShareMemories("post10", "Never thought I will be specialist in this field...");
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Comand:                         viewTimeline()" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl;
	CurrentUser->sortTimeline();
	CurrentUser->viewTimeline();
}
int main()
{
	Controller mainApp;
	mainApp.LoadAllData();
	mainApp.Run();
}
