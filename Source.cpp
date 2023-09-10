#include <iostream>
#include<iomanip>
#include <string>
#include<fstream>
using namespace std;

struct UserProfile
{
    int User_Id;
    string User_Name;
    string Profile_Details;
    UserProfile* ptrnext; // Linked list pointer to the next user

    UserProfile(int id, const string& name, const string& details)
    {
        User_Id = id;
        User_Name = name;
        Profile_Details = details;
        ptrnext = nullptr;
    }
};
const int HASH_TABLE_SIZE = 100; // Size of the hash table for fast retrieval

class UserProfileManager //  class is implementation of a hash table using an array of linked lists
{
private:
    UserProfile* User_Profile_Hash_Table[HASH_TABLE_SIZE] = { nullptr }; // Hash table to store user profiles // an array of pointers to UserProfile objects

    UserProfile* Find_Last_Node(UserProfile* head) //finds last node in the linked list to append a new user profile.
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        while (head->ptrnext != nullptr)
        {
            head = head->ptrnext;
        }
        return head;
    }
public:

    void Add_User_Profile(int User_Id, const string& User_Name, const string& Profile_Details) // Function to add a new user profile to the hash table
    {
        // Hash the user ID to find the appropriate index in the hash table
        int index = User_Id % HASH_TABLE_SIZE;  //modulo operator to ensure that the index is within the valid range (0 to HASH_TABLE_SIZE - 1) based on the user's ID.
        UserProfile* New_User = new UserProfile(User_Id, User_Name, Profile_Details);  // Create a new user profile node

        if (User_Profile_Hash_Table[index] == nullptr) // checks if the linked list at the hashed index is empty
        {
            User_Profile_Hash_Table[index] = New_User; // if hashed index is empty new user profile becomes the first node 
        }
        else // linked list at the hashed index is not empty
        {
            UserProfile* Last_Node = Find_Last_Node(User_Profile_Hash_Table[index]);
            Last_Node->ptrnext = New_User;
        }
    }
    UserProfile* Get_User_Profile(int User_Id)  // Function to retrieve user profile based on user ID from the hash table
    {
        int index = User_Id % HASH_TABLE_SIZE; // Hash the user ID to find the appropriate index in the hash table
        UserProfile* current = User_Profile_Hash_Table[index]; // Traverse the linked list at the hashed index to find the user profile
        while (current != nullptr)
        {
            if (current->User_Id == User_Id)
            {
                return current;
            }
            current = current->ptrnext;
        }
        return nullptr; // User profile not found
    }
    void Remove_User_Profile(int User_Id) // Function to remove a user profile based on user ID from the hash table
    {
        int index = User_Id % HASH_TABLE_SIZE;  // Hash the user ID to find the appropriate index in the hash table
        if (User_Profile_Hash_Table[index] == nullptr)  // Check if the linked list is empty at the hashed index
        {
            cout << "   (--) USER PROFILE WITH ID -->> " << User_Id << " NOT FOUND (--) \n";
            return; //it means there are no user profiles with the given User_Id
        }
        if (User_Profile_Hash_Table[index]->User_Id == User_Id)   // If the first node matches the user ID, update the head of the linked list
        {
            UserProfile* temp = User_Profile_Hash_Table[index];
            User_Profile_Hash_Table[index] = User_Profile_Hash_Table[index]->ptrnext;
            delete temp;
            cout << "  (^^) USER PROFILE WITH ID -->> " << User_Id << " REMOVED (^^) \n";
            return;
        }
        UserProfile* current = User_Profile_Hash_Table[index]; // Traverse the linked list at the hashed index to find the user profile for removal
        while (current->ptrnext != nullptr)
        {
            if (current->ptrnext->User_Id == User_Id)
            {
                UserProfile* temp = current->ptrnext;
                current->ptrnext = current->ptrnext->ptrnext;
                delete temp;
                cout << "  (^^) USER PROFILE WITH ID -->> " << User_Id << " REMOVED (^^) \n";
                return;
            }
            current = current->ptrnext;
        }
        cout << "  (--) USER PROFILE WITH ID -->> " << User_Id << " NOT FOUND (--) \n";
    }
    void Display_User_Profiles(UserProfileManager& userProfileManager)
    {
        /* int numUsers;
         cout << "Enter the number of user profiles you want to display: ";
         cin >> numUsers;
         cin.ignore(); */// Clear the input buffer

        cout << "\n\t_____ USER PROFILES_____" << endl;
        cout << "\t====================================================\n";
        cout << "\t USER ID \t USER NAME \t PROFILE DETAILS  \n";
        cout << "\t====================================================\n";

        /*for (int i = 1; i <= numUsers; i++) {
            UserProfile* userProfile = userProfileManager.Get_User_Profile(i);
            if (userProfile != nullptr) {
                cout << userProfile->User_Id << "\t\t" << userProfile->User_Name << "\t" << userProfile->Profile_Details << endl;
            }
            else {
                cout << i << "\t\tNot Found\tNo Details" << endl;
            }
        }*/
        for (int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            UserProfile* current = userProfileManager.User_Profile_Hash_Table[i];
            while (current != nullptr)
            {
                cout << setw(12) << current->User_Id << setw(17) << current->User_Name << setw(22) << current->Profile_Details << endl;
                current = current->ptrnext;
            }
        }
        cout << "--------------------------------------------" << endl;
    }
    // purpose of the class is to efficiently store and manage user profiles using hash-based indexing for quick access( adding,retrieving,removing user profiles based on their IDs)
};
const int MAX_USERS = 1000; // Maximum number of users in the social network
bool Friendship_Matrix[MAX_USERS][MAX_USERS] = { false }; // Adjacency matrix to represent friendships

class FriendNetwork
{
public:
    void Add_Friendship(int userId1, int userId2) // Function to add a friendship between two users
    {
        Friendship_Matrix[userId1][userId2] = true;   // Update the friendship matrix to add and indicate the friendship between userId1 and userId2
        Friendship_Matrix[userId2][userId1] = true;
    }
    bool Are_Friends(int userId1, int userId2) // Function to check if two users are friends
    {
        return Friendship_Matrix[userId1][userId2];   // Check the friendship matrix to see if there is a friendship between userId1 and userId2
    }
};
struct CommentNode
{
    int commentId;
    string commentContent;
    CommentNode* Left;  // Pointer to the left child (reply)
    CommentNode* Right; // Pointer to the right sibling (next comment)

    CommentNode(int id, const string& content)
    {
        commentId = id;
        commentContent = content;
        Left = nullptr;
        Right = nullptr;
    }
};
struct PostNode
{
    int Post_Id;
    string Post_Content;
    CommentNode* Comments; // Pointer to the comments linked list for this post
    PostNode* Left;
    PostNode* Right;
    PostNode(int id, const string& content)
    {
        Post_Id = id;
        Post_Content = content;
        Comments = nullptr;
        Left = nullptr;
        Right = nullptr;
    }
};
PostNode* Post_Roots[MAX_USERS] = { nullptr }; // Array to store the roots of post trees for each user
class PostManager
{
public:
    void Add_Post(int User_Id, int Post_Id, const string& Post_Content)
    {
        PostNode* newPost = new PostNode(Post_Id, Post_Content);

        if (Post_Roots[User_Id] == nullptr)
        {
            Post_Roots[User_Id] = newPost; // // If the user has no posts, set the new post as the root
        }
        else
        {
            PostNode* currentPost = Post_Roots[User_Id]; // Find the last post node in the user's post tree
            while (currentPost->Right != nullptr) //traverses the user's post tree to find the last post node (the rightmost node in the tree)
            {
                currentPost = currentPost->Right;
            }
            currentPost->Right = newPost; // Add the new post as the Right child of the last post node
        }
    }
    void Add_Comment(int User_Id, int Post_Id, int commentId, const string& commentContent)
    {
        PostNode* Current_Post = Post_Roots[User_Id]; //pointer Current_Post to root of user's post tree to find post with the given Post_Id

        while (Current_Post != nullptr)
        {
            if (Current_Post->Post_Id == Post_Id)
            {
                // Post with the given Post_Id is found, create a new comment and add it to the comments linked list
                CommentNode* New_Comment = new CommentNode(commentId, commentContent);
                New_Comment->Right = Current_Post->Comments;
                Current_Post->Comments = New_Comment;
                return; // Exit the function after adding the comment
            }
            Current_Post = Current_Post->Right;
        }

        // If the function reaches this point, the post with the given Post_Id was not found
        cout << "   (_) POST WITH ID " << Post_Id << " NOT FOUND FOR USER ID " << User_Id << "  (_)" << endl;
    }
    void Show_User_Posts(int userId)
    {
        PostNode* currentPost = Post_Roots[userId];

        if (currentPost == nullptr)
        {
            cout << "   (_) NO POST FOUND FOR USER ID " << userId << "  (_)" << endl;
            return;
        }
        cout << "\t_____POST FOR USER ID___ " << userId << ":" << endl;
        cout << "\t===============================================" << endl;
        cout << setw(17) << "POST ID" << setw(25) << "POST CONTENT" << endl;
        cout << "\t===============================================" << endl;
        while (currentPost != nullptr)
        {
            cout << setw(13) << currentPost->Post_Id << setw(25) << currentPost->Post_Content << endl;
            currentPost = currentPost->Right;
        }
        cout << "-------------------------------------------------------" << endl;
    }
    // class has adjacency matrix for representing friendships and linked lists for storing comments under posts
    // The FriendNetwork class manages friendships between users
    // PostManager class manages posts and comments for each user
};
const int MAX_FEED_SIZE = 10; // Maximum size of the news feed  will be displayed in news feed for each user
struct MinHeapNode
{
    int User_Id;
    PostNode* Post;
    MinHeapNode(int id, PostNode* p)
    {
        User_Id = id;
        Post = p;
    }
};
class NewsFeedManager
{
private:
    MinHeapNode* Min_Heap[MAX_FEED_SIZE]; // representing MinHeap used for storing posts
    int Heap_Size = 0; //representing current size of MinHeap (number of elements present in Min_Heap array)

    void Min_Heapify(int i)
    {
        int Smallest_Root = i;
        int Left_Child = 2 * i + 1;
        int Right_Child = 2 * i + 2;
        //  compares posts' IDs of current root and its left child
        if (Left_Child < Heap_Size && Min_Heap[Left_Child]->Post->Post_Id < Min_Heap[Smallest_Root]->Post->Post_Id)
        {
            Smallest_Root = Left_Child; // if child have smaller post ID, the index of the smallest one is stored in Smallest_Root
        }
        //  compares posts' IDs of current root and its right child
        if (Right_Child < Heap_Size && Min_Heap[Right_Child]->Post->Post_Id < Min_Heap[Smallest_Root]->Post->Post_Id)
        {
            Smallest_Root = Right_Child; // if child have smaller post ID, the index of the smallest one is stored in Smallest_Root
        }

        if (Smallest_Root != i) //If index i is not smallest it violates the MinHeap property
        {
            swap(Min_Heap[i], Min_Heap[Smallest_Root]); //elements at indices i and Smallest_Root are swapped
            Min_Heapify(Smallest_Root); // Min_Heapify is called recursively on the index Smallest_Root to fix the MinHeap property
        }
    }

public:
    void Add_To_Feed(int User_Id, PostNode* Post) //responsible for adding posts to the MinHeap, maintaining the MinHeap property
    {
        if (Heap_Size < MAX_FEED_SIZE)
        { //If MinHeap is not full new MinHeapNode is created with the given User_Id and Post
            Min_Heap[Heap_Size] = new MinHeapNode(User_Id, Post);
            int i = Heap_Size;
            Heap_Size++;
            while (i > 0 && Min_Heap[(i - 1) / 2]->Post->Post_Id > Min_Heap[i]->Post->Post_Id)
            { //inserted into the MinHeap using the MinHeapify process to preserve the MinHeap property
                swap(Min_Heap[(i - 1) / 2], Min_Heap[i]);
                i = (i - 1) / 2;
            }
        }
        else if (Post->Post_Id > Min_Heap[0]->Post->Post_Id) // if MinHeap is already full
        { //if new post's ID is greater than smallest post ID in the MinHeap(root)
            Min_Heap[0]->Post = Post; //replaces the root's post with the new post
            Min_Heapify(0); //fix MinHeap property
        }
    }
    void Generate_News_Feed(int User_Id)
    {
        Heap_Size = 0;  // Reset the heap
        PostNode* Current_Post = Post_Roots[User_Id]; // Add the user's own posts to the news feed
        while (Current_Post != nullptr)
        {
            Add_To_Feed(User_Id, Current_Post);
            Current_Post = Current_Post->Right;
        }
        for (int i = 1; i <= MAX_USERS; i++)   // Add the posts from the user's friends to the news feed
        {
            if (Friendship_Matrix[User_Id][i])
            {
                Current_Post = Post_Roots[i];
                while (Current_Post != nullptr)
                {
                    Add_To_Feed(i, Current_Post);
                    Current_Post = Current_Post->Right;
                }
            }
        }
        // Print the news feed
        cout << "\t___ NEWS FEED FOR USER ___ " << User_Id << ":" << endl;
        cout << "\t==========================================\n";
        cout << "\t POST ID \t POST CONTENT \n";
        cout << "\t==========================================\n";
        for (int i = 0; i < Heap_Size; i++)
        {
            cout << "\t" << Min_Heap[i]->Post->Post_Id << " \t\t " << Min_Heap[i]->Post->Post_Content << endl;
            CommentNode* currentComment = Min_Heap[i]->Post->Comments;
            while (currentComment != nullptr)
            {
                cout << "\t COMMENT ID -->>  " << currentComment->commentId << " | CONTENT =>  " << currentComment->commentContent << endl;
                currentComment = currentComment->Right;
            }
        }
    }
    // MinHeap to store posts it allows users to view their news feeds, including posts and associated comments, from their own posts and the posts of their friends
};

struct Notification
{
    string Message;
    Notification* ptrnext;
    Notification(const string& msg)
    {
        Message = msg;
        ptrnext = nullptr;
    }
};
class NotificationStack
{
private:
    Notification* Top;

public:
    NotificationStack()
    {
        Top = nullptr;
    }
    void Push_Notification(const string& Message) //  push a new notification onto the stack
    {
        Notification* New_Notification = new Notification(Message);
        New_Notification->ptrnext = Top;
        Top = New_Notification;
    }

    void Pop_Notification()  // Function to pop the top notification from the stack
    {
        if (Top == nullptr)
        {
            cout << "   (!!) STACK IS EMPTY (!!) \n (!!) CANNOT POP ANY NOTIFICATION (!!) \n";
            return;
        }
        Notification* temp = Top; //notification is added to top of stack
        Top = Top->ptrnext; //pointer is updated to point to new notification
        delete temp;
    }

    bool Is_Empty()  // Function to check if the stack is empty
    {
        return Top == nullptr; //returns true if Top pointer is nullptr, indicating empty stack
    }

    void Display_Notification()   // Function to display all notifications in the stack
    { // starts from top of stack and traverses through linked list of notifications, printing the message of each notification
        Notification* current = Top;
        while (current != nullptr)
        {
            cout << current->Message << endl;
            current = current->ptrnext;
        }
    }
    bool Ask_User_To_Show_Notifications()
    {
        char response;
        cout << "Do you want to see your notifications? (Y/N): ";
        cin >> response;
        return (response == 'Y' || response == 'y');
    }
    void Show_User_Notifications(int userId)
    {
        cout << "Notifications for User ID " << userId << ":" << endl;
        Notification* current = Top;
        bool foundNotifications = false;

        while (current != nullptr)
        {
            if (current->Message.find("User ID: " + to_string(userId)) != string::npos)
            {
                cout << current->Message << endl;
                foundNotifications = true;
            }
            current = current->ptrnext;
        }

        if (!foundNotifications)
        {
            cout << "No notifications found for User ID " << userId << endl;
        }
    }
    // notification stack and allows users to push and pop notifications, display all notifications in the stack
    // show notifications specific to a given user ID 
    // Notifications are stored in a linked list fashion, and each notification contains a message and a pointer to the next notification
};
void Display_Menu()
{
    cout << "____SOCIAL NETWORK SIMULATION PLATFORM___" << endl;
    cout << "1. ADD USER PROFILE " << endl;
    cout << "2. GET USER PROFILES " << endl;
    cout << "3. REMOVE USER PROFILE " << endl;
    cout << "4. ADD FRIENDSHIP" << endl;
    cout << "5. CHECK FRIENDSHIP" << endl;
    cout << "6. ADD POST" << endl;
    cout << "7. DISPLAY ALL POSTS OF USER" << endl;
    cout << "8. ADD COMMENT TO POST" << endl;
    cout << "9. GENERATE NEWS FEED" << endl;
    cout << "10. DISPLAY NOTIFICATIONS" << endl;
    cout << "11. EXIT" << endl;
    cout << "__________________\n";
    cout << "   ENTER YOUR CHOICE  ";
}
int main()
{
    UserProfileManager obj_Profile_Manager;
    FriendNetwork obj_Friend_Network;
    PostManager obj_Post_Manager;
    NewsFeedManager obj_News_Feed_Manager;
    NotificationStack obj_User_Notifications;

    int opt;
    while (true)
    {
        Display_Menu();
        cin >> opt;
        cin.ignore(); // Clear the input buffer

        switch (opt)
        {
        case 1:
        {
            int User_Id;
            string User_Name, Profile_Details;
            cout << "Enter User ID:         ";
            cin >> User_Id;
            cin.ignore();
            cout << "Enter User Name:       ";
            getline(cin, User_Name);
            cout << "Enter Profile Details: ";
            getline(cin, Profile_Details);
            obj_Profile_Manager.Add_User_Profile(User_Id, User_Name, Profile_Details);
            break;
        }
        case 2:
        {
            obj_Profile_Manager.Display_User_Profiles(obj_Profile_Manager);
            int User_Id;
            cout << "Enter User ID: ";
            cin >> User_Id;
            cin.ignore();
            UserProfile* userProfile = obj_Profile_Manager.Get_User_Profile(User_Id);
            cout << "\t====================================================\n";
            cout << "\t USER ID \t USER NAME \t PROFILE DETAILS  \n";
            cout << "\t====================================================\n";
            if (userProfile != nullptr)
            {
                cout << setw(12) << userProfile->User_Id << setw(17) << userProfile->User_Name << setw(22) << userProfile->Profile_Details << endl;
            }
            else
            {
                cout << "\t\t(_) USER PROFILE NOT FOUND (_) " << endl;
            }
            break;
        }
        case 3:
        {
            int User_Id;
            cout << "Enter User ID to remove: ";
            cin >> User_Id;
            cin.ignore();
            obj_Profile_Manager.Remove_User_Profile(User_Id);

            break;
        }
        case 4:
        {
            int userId1, userId2;
            cout << "\tEnter User ID 1: ";
            cin >> userId1;
            cout << "\tEnter User ID 2: ";
            cin >> userId2;
            obj_Friend_Network.Add_Friendship(userId1, userId2);
            break;
        }
        case 5:
        {
            int userId1, userId2;
            cout << "\tEnter User ID 1: ";
            cin >> userId1;
            cout << "\tEnter User ID 2: ";
            cin >> userId2;
            cout << "\t\t USER  " << userId1 << " AND " << userId2 << " ARE FRIENDS ???   " << (obj_Friend_Network.Are_Friends(userId1, userId2) ? " * Yes * " : " !!! No !!!") << endl;
            break;
        }
        case 6:
        {
            int User_Id, Post_Id;
            string Post_Content;
            cout << "\tEnter User ID:                ";
            cin >> User_Id;
            cout << "\tEnter Post ID:                ";
            cin >> Post_Id;
            cin.ignore();
            cout << "\tEnter Post Content (string):  ";
            getline(cin, Post_Content);
            obj_Post_Manager.Add_Post(User_Id, Post_Id, Post_Content);
            break;
        }
        case 7:
        {
            int targetUserId;
            cout << "Enter User ID to see posts: ";
            cin >> targetUserId;
            obj_Post_Manager.Show_User_Posts(targetUserId);
            break;
        }
        case 8:
        {
            int User_Id, Post_Id, commentId;
            string Comment_Content;
            cout << "\tEnter User ID:                  ";
            cin >> User_Id;
            cout << "\tEnter Post ID:                  ";
            cin >> Post_Id;
            cout << "\tEnter Comment ID:               ";
            cin >> commentId;
            cin.ignore();
            cout << "\tEnter Comment Content (string): ";
            getline(cin, Comment_Content);
            obj_Post_Manager.Add_Comment(User_Id, Post_Id, commentId, Comment_Content);
            break;
        }
        case 9:
        {
            int User_Id;
            cout << "\tEnter User ID: ";
            cin >> User_Id;
            obj_News_Feed_Manager.Generate_News_Feed(User_Id);
            break;
        }
        case 10:
        {
            cout << "   ---- NOTIFICATIONS -----" << endl;
            obj_User_Notifications.Display_Notification();
            // Sample data: Push some notifications onto the stack
            obj_User_Notifications.Push_Notification("Notification 1: Hello, User 1!");
            obj_User_Notifications.Push_Notification("Notification 2: Important update for User 2.");
            obj_User_Notifications.Push_Notification("Notification 3: Welcome User 1.");

            // Allow user to push notifications and see notifications
            int userId;
            char choice;

            do
            {
                cout << "Enter User ID: ";
                cin >> userId;

                if (userId == 1 || userId == 2)
                {
                    cout << "   WANNA PUSH NOTIFICATION? (y/n): ";
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y')
                    {
                        string notificationMsg;
                        cout << "ENTER NOTIFICATION MESSAGE ";
                        cin.ignore();
                        getline(cin, notificationMsg);
                        obj_User_Notifications.Push_Notification(notificationMsg);
                    }

                    cout << "   WANNA SEE NOTIFICATIONS? (Y/N): ";
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y')
                    {
                        cout << "____NOTIFICATIONS FOR USER___ " << userId << ":" << endl;
                        cout << "-----------------------------------------" << endl;
                        obj_User_Notifications.Display_Notification();
                        cout << "-----------------------------------------" << endl;
                    }
                }
                else
                {
                    cout << "   (!!) NO NOTOFICATION FOR USER  " << userId << " (!!) " << endl;
                }

                cout << "\n WANNA CONTINUE ? (Y/N): ";
                cin >> choice;

            } while (choice == 'y' || choice == 'Y');
            break;
        }
        case 11:
            cout << "   #### EXITING ####" << endl;
            return 0;
        default:
            cout << "   ..... INVALID ....." << endl;
            break;
        }

        cout << endl;
    }
    system("Pause");
    return 0;
}