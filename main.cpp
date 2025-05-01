#include<bits/stdc++.h>
using namespace std;


class enter {
    string username;
    string password;

    public:
        enter() {
            username = "";
            password = "";
        }
        friend class signUp;
        friend class logIn;
        friend class menu;
};

class signUp {
    enter ent;
    public:
        void user_signUp(string);
        friend class menu;
};

class menu {
    public:
        void main_menu(string);
};

struct node {
    string interest;
    struct node *next;
};

class node1 {
    string name;
    int id;
    node1 *next;
    public:
        friend class graph;
        friend class friends;
};

struct interestNode {
    string interest;
    interestNode *next;
};

struct userNode {    
    string name;
    interestNode *interestHead;
    userNode *next;
};

struct interestCountNode {
    string interest;
    int count;
};

class hashing {
    public:
        static const int SIZE = 10;
        userNode *table[SIZE];
        interestCountNode interest[100];
        int interestSize = 0;

        hashing() {
            for(int i = 0; i < SIZE; i++) {
                table[i] = nullptr;
            }
        }
        

        int hashIndex(string userName);
        void add_interests(string userName, string interest);
        void display_interests(string userName);
        void save_to_file();
        void load_from_file();
        void add_or_increment_interest(string intr);
        void heapify(int n, int i);
        void builtMaxHeap() {
            int n = interestSize;
            for(int i = n/2-1; i >= 0; i--) {
                heapify(n, i);
            }
        }
        void famous_interest();      
};


int hashing :: hashIndex(string userName) {
    int h = 0;
    for(char ch : userName) {
        h += ch;
    }
    return h%SIZE;
}
void hashing :: add_interests(string userName, string interest) {
    int index = hashIndex(userName);
    userNode *user = table[index];
    while(user != nullptr) {
        if(user->name == userName) {
            break;
        }
        user = user->next;
    }

    if(user == nullptr) {
        user = new userNode();
        user->name = userName;
        user->interestHead = nullptr;
        user->next = table[index];
        table[index] = user;
    }

    interestNode *temp = user->interestHead;
    while(temp != nullptr) {
        if(temp->interest == interest) {
            cout << "Duplicate interest not allowed\n";
            return;
        }
        temp = temp->next;
    }

    interestNode *newInterest = new interestNode();
    newInterest->interest = interest;
    newInterest->next = nullptr;
    if(user->interestHead == nullptr) {
        user->interestHead = newInterest;
    }
    else {
        interestNode *temp = user->interestHead;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newInterest;
    }
    save_to_file();
}

void hashing :: load_from_file() {
    ifstream fin("Interests.txt");

    if(!fin) {
        return;
    }

    string line, currentUser;
    while(getline(fin, line)) {
        if(line == "#") {
            currentUser = "";
        }
        else if(line[0] == '-') {
            string interest = line.substr(2);
            add_interests(currentUser, interest);
        }
        else {
            currentUser = line;
        }
    }
    fin.close();
}

void hashing :: display_interests(string userName) {
    int index = hashIndex(userName);
    userNode *user = table[index];

    while(user != nullptr) {
        if(user->name == userName) {
            break;
        }
        user = user->next;
    }

    if(user != nullptr) {
        interestNode *temp = user->interestHead;
        cout << "Your interests are: " << endl;
        while(temp != nullptr) {
            cout << temp->interest << endl;
            temp = temp->next;
        }
    }
    else {
        cout << "No interest found!!\n";
        return;
    }
    cout << endl;
}

void hashing :: save_to_file() {
    ofstream fout("Interests.txt");
    if(!fout) {
        cout << "Error opening file for writing\n";
        return;
    }
    else {
        for(int i = 0; i < SIZE; i++) {
            userNode *user = table[i];
            while(user != nullptr) {
                fout << user->name << endl;
                interestNode *interest = user->interestHead;
                while(interest != nullptr) {
                    fout << "- " << interest->interest << endl;
                    interest = interest->next;
                }
                fout << "#" << endl;
                user = user->next;
            }
        }
    }
    fout.close();
}

void hashing :: add_or_increment_interest(string intr) {
    for(int i = 0; i < interestSize; i++) {
        if(intr == interest[i].interest) {
            interest[i].count++;
            return;
        }
    }
    interest[interestSize].interest = intr;
    interest[interestSize].count = 1;
    interestSize++;
}

void hashing :: heapify(int n, int i) {
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if((left < n) and (interest[left].count > interest[largest].count)) {
        largest = left;
    }
    if((right < n) and (interest[right].count > interest[largest].count)) {
        largest = right;
    }
    if(largest != i) {
        swap(interest[largest], interest[i]);
        heapify(n, largest);
    }
}

void hashing :: famous_interest() {
    for(int i = 0; i < SIZE; i++) {
        userNode *user = table[i];
        while(user != nullptr) {
            interestNode *temp = user->interestHead;
            while(temp != nullptr) {
                add_or_increment_interest(temp->interest);
                temp = temp->next;
            }
            user = user->next;
        }
    }

    if(interestSize == 0) {
        cout << "No interests found!\n";
        return;
    }

    builtMaxHeap();
    cout << "Most famous interest is: " << interest[0].interest << " with " << interest[0].count << " users!" << endl;
}

class graph {
    int user_count;
    node1 *head[100];
    public:
        friend class friends;
        graph() {
            ifstream fin("User.txt");
            string line;
            int i = 0;
                while(getline(fin, line)) {
                    head[i] = new node1();
                    stringstream ss(line);
                    string user;
                    getline(ss, user, '|');
                    head[i]->name = user;
                    head[i]->id = i;
                    head[i]->next = NULL;
                    i++;
                }
                user_count = i;
        }
        void create(string, string);
        void display();
        void load_graph();
        void request(string);
};

void graph :: create(string u, string v) {
    int user_id = -1;
    int friend_id = -1;
    for(int i = 0; i < user_count; i++) {
        if(head[i]->name == u) {
            user_id = i;
        }
        else if(head[i]->name == v) {
            friend_id = i;
        }
    }
    if(u == v) {
        return;
    }
        node1 *curr = new node1();
        curr->id = friend_id;
        curr->name = v;
        curr->next = NULL;

        node1 *temp = new node1();
        temp = head[user_id];
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = curr;
}

void graph :: display() {
    for(int i = 0; i < user_count; i++) {
        node1 *temp = head[i]->next;
        cout << head[i]->name << "'s friends are: " << endl;
        if(temp != NULL) {
            while(temp != NULL) {
                cout << "\t" << temp->name << endl;
                temp = temp->next;
            }
        }
        else {
            cout << head[i]->name << " don't have any friends\n";
        }
        cout << endl;
    }
}

void graph :: request(string userName) {
    int id = -1;
    for(int i = 0; i < user_count; i++) {
        if(head[i]->name == userName) {
            id = i;
            break;
        }
    }

    cout << endl;
    cout << "Notifications: " << endl;
    char ch;
    for(int i = 0; i < user_count; i++) {
        if(head[i]->name == userName) continue;
        bool choice = false;
        
        node1 *temp = head[i]->next;
        if(temp != NULL) {
            while(temp != NULL) {
                if(temp->name == userName) {
                    choice = true;
                    break;
                }
                temp = temp->next;
            }
        }
        node1 *temp1 = head[id]->next;
        if(temp1 != NULL) {
            while(temp1 != NULL) {
                if(temp1->name == head[i]->name) {
                    choice = false;
                    break;
                }
                temp1 = temp1->next;
            }
        }
        if(choice == true) {
            cout << head[i]->name << " wants to be your friend!!" << endl;
            cout << "Do you want to accept?" << endl;
            cin >> ch;
            if(ch == 'y' || ch == 'Y') {
                create(userName, head[i]->name);
                ofstream fout("graph.txt", ios::app);
                fout << userName << "|" << head[i]->name << endl;
                fout.close();
            }
        }

    }
}

void graph :: load_graph() {
    ifstream fin("graph.txt");
    string line;
    while(getline(fin, line)) {
        stringstream ss(line);
        string u, v;
        getline(ss, u, '|');
        getline(ss, v);
        create(u, v);
    }
} 

class friends {
    graph &g;
    public:
        friends(graph &g_ref) : g(g_ref) {}
        void send_friend_request(string);
        void view_friends(string);
        void mutual_friends(string);
        void suggest_friends(string, hashing &ht);
        bool check_friend(string, string);
};

bool friends :: check_friend(string userName, string frnd) {
    int id = -1;
    for(int i = 0; i < g.user_count; i++) {
        if(g.head[i]->name == userName) {
            id = i;
            break;
        }
    }

    node1 *temp = g.head[id]->next;
    if(temp != NULL) {
        while(temp != NULL) {
            if(temp->name == frnd) {
                return false;
            }
            temp = temp->next;
        }
    }
    return true;
}

void friends :: send_friend_request(string userName) {
    ifstream fin("User.txt");
    char ch;
    string user;
    vector <string> user_name;
     
    while(getline(fin, user)) {
        stringstream ss(user);
        string username;
        getline(ss, username, '|');
        user_name.push_back(username);
    }

    if(user_name.size() == 0) {
        cout << "No Available Users\n";
        return;
    }
    else {
        cout << "Available Users: " << endl;
        for(int i = 0; i < user_name.size(); i++) {
            if(user_name[i] != userName) {
                cout << i+1 << ". " << user_name[i] << endl;
            }
        }
    }
    user = "";
    do { 
        cout << "Enter Friend's Username: ";
        cin >> user;
        if(check_friend(userName, user)) {
            for(int i = 0; i < user_name.size(); i++) {
                if(user_name[i] != userName) {
                    if(user == user_name[i]) {
                        ofstream fout("graph.txt", ios::app);
                        fout << userName << "|" << user << endl;
                        fout.close();
                        g.create(userName, user);
                    }
                }
            }
        }
        else {
            cout << "You are already friends\n";
        }
        cout << "Do you want to add more friends? (y/n): ";
        cin >> ch;
    } while(ch == 'y' || ch == 'Y');
    fin.close();
}

void friends :: view_friends(string userName) {
    int id = -1;
    for(int i = 0; i < g.user_count; i++) {
        if(userName == g.head[i]->name) {
            id = i;
            break;
        }
    }
    node1 *temp = g.head[id]->next;
    if(temp != NULL) {
        cout << g.head[id]->name << "'s friends are: " << endl;
        while(temp != NULL) {
            cout << "\t" << temp->name << endl;
            temp = temp->next;
        }
    } 
    else {
        cout << "You don't have any friends\n";
        return;
    }
}

void friends :: mutual_friends(string userName) {
    int k = 0;
    string mutual;
    cout << "Enter the friends username: ";
    cin >> mutual;
    int user_id;
    int friend_id;
    for(int i = 0; i < g.user_count; i++) {
        if(userName == g.head[i]->name) {
            user_id = i;
        }
        if(g.head[i]->name == mutual) {
            friend_id = i;
        }
    }
    vector <string> user_friends;
    vector <string> mutual_friends;
    node1 *temp = g.head[user_id]->next;
    if(temp != NULL) {
        while(temp != NULL) {
            user_friends.push_back(temp->name);
            temp = temp->next;
        }
    }
    else {
        cout << "You don't have any friends\n";
        return;
    }
    temp = g.head[friend_id]->next;
    if(temp != NULL) {
        while(temp != NULL) {
            mutual_friends.push_back(temp->name);
            temp = temp->next;
        }
    }
    else {
        cout << g.head[friend_id]->name << " don't have any friends\n";
        return;
    }
    cout << "Mutuals are: " << endl;
    for(int i = 0; i < user_friends.size(); i++) {
        for(int j = 0; j < mutual_friends.size(); j++) {
            if(user_friends[i] == mutual_friends[j]) {
                cout << user_friends[i] << endl;
                k++;
            }
        }
    }
    if(k == 0) {
        cout << "There are no mutuals\n";
    }
}

void friends :: suggest_friends(string userName, hashing &ht) {
    int id = -1;
    for(int i = 0; i < g.user_count; i++) {
        if(g.head[i]->name == userName) {
            id = i;
        }
    }

    vector <pair<int, string>> suggested_friends;
    vector <string> directFriend;
    node1 *temp = g.head[id]->next;
    while(temp != NULL) {
        directFriend.push_back(temp->name);
        temp = temp->next;
    }

    for(int i = 0; i < g.user_count; i++) {
        string candidate_name = g.head[i]->name;

        if(candidate_name == userName) {
            continue;
        }

        bool alreadyFriend = false;
        for(string f : directFriend) {
            if(f == candidate_name) {
                alreadyFriend = true;
                break;
            }
        }

        if(alreadyFriend) {
            continue;
        }

        int mutual_interest = 0;
        vector <string> user_interests;
        int index = ht.hashIndex(userName);
        userNode *user = ht.table[index];

        while(user != nullptr) {
            if(user->name == userName) {
                break;
            }
            user = user->next;
        }

        if(user != nullptr) {
            interestNode *temp = user->interestHead;
            while(temp != nullptr) {
                user_interests.push_back(temp->interest);
                temp = temp->next;
            }
        }

        int index1 = ht.hashIndex(g.head[i]->name);
        userNode *user1 = ht.table[index1];

        while(user1 != nullptr) {
            if(user1->name == g.head[i]->name) {
                break;
            }
            user1 = user1->next;
        }

        if(user1 != nullptr) {
            interestNode *temp = user1->interestHead;
            while(temp != nullptr) {
                for(string f : user_interests) {
                    if(f == temp->interest) {
                        mutual_interest++;
                    }
                }
                temp = temp->next;
            }
        }


        int mutualCount = 0;
        node1 *friend1 = g.head[i]->next;
        while(friend1 != NULL) {
            for(string f : directFriend) {
                if(f == friend1->name)  {
                    mutualCount++;
                }
            }
            friend1 = friend1->next;
        }

        float score = 2 * mutualCount + mutual_interest;
        int total_possible_mutual_friends = directFriend.size();
        int total_user_interest = user_interests.size();
        float total_score = (2 * total_possible_mutual_friends) + total_user_interest;

        if(score > 0 && total_score > 0) {
            int percentage = (score / total_score) * 100;
            suggested_friends.push_back({percentage, candidate_name});
        }
    }

    for(int i = 0; i < suggested_friends.size(); i++) {
        for(int j = 0; j < suggested_friends.size()-i-1; j++) {
            if(suggested_friends[j+1].first > suggested_friends[j].first) {
                swap(suggested_friends[j+1], suggested_friends[j]);
            }
        }
    }

    if(suggested_friends.empty()) {
        cout << "No friend suggestion available\n";
        return;
    }
    else {
        cout << "Suggested Friends: " << endl;
        for(auto &p : suggested_friends) {
            cout << p.second << " (" << p.first << "% Compatibility)" << endl;
        }
    }
}

void signUp :: user_signUp(string fname) {
    menu m;
    cout << endl;
    cout << "*************Welcome To Vibesta*************" << endl;
    cout << "#### Vibes that stay, Moments that slay ####" << endl;
    cout << "Enter the Username: ";
    cin >> ent.username;
    cout << "Create a Password: ";
    cin >> ent.password;
    ifstream fin(fname, ios::in);
    string line;
    while(getline(fin, line)) {
        stringstream ss(line);
        string fileUsername, filePassword;
        getline(ss, fileUsername, '|');
        getline(ss, filePassword);
        if(fileUsername == ent.username && filePassword == ent.password) {
            cout << "User already exist\n";
            fin.close();
            return;
        } 
    }
    ofstream fout(fname, ios::app);
    fout << ent.username << "|" << ent.password << endl;

    m.main_menu(ent.username);

    fout.close();   
}

class logIn {
    enter ent;
    public:
        bool user_login(string);
};

bool logIn :: user_login(string fname) {
    menu m;
    cout << "*************Welcome To Vibesta*************" << endl;
    cout << "#### Vibes that stay, Moments that slay ####" << endl;
    cout << "Enter the Username: ";
    cin >> ent.username;
    cout << "Enter the Password: ";
    cin >> ent.password;
    string line;
    ifstream fin(fname);
    while(getline(fin, line)) {
        stringstream ss(line);
        string fileUsername, filePassword;
        getline(ss, fileUsername, '|');
        getline(ss, filePassword);

        if(ent.username == fileUsername && ent.password == filePassword) {
            cout << "Login Successfully\n";
            m.main_menu(ent.username);
            return true;
        }
    }
    cout << "Login was unsuccessful\n";
    return false;
}

int countUsers() {
    int user_count = 0;
    ifstream fin("User.txt");
    string line;
    while(getline(fin, line)) {
        user_count = user_count + 1;
    }
    return user_count;
}

void menu :: main_menu(string username) {
    hashing ht;
    graph g;
    friends f(g);
    g.load_graph();
    ht.load_from_file();
    g.request(username);
    int ch;
    do {
        string interest;
        int choice;
        cout << endl;
        cout << "*************MAIN MENU*************" << endl;
        cout << "1.Add Interest\n2.Display My Interests\n3.Send Friend Request\n4.View Friends\n5.View Mutual Friends\n6.Suggest Friends\n7.Famous Interest\n8.Exit\n";
        cin >> choice;
        switch(choice) {
            case 1:
                cout << "Enter your interest: ";
                cin.ignore();
                getline(cin, interest);
                ht.add_interests(username, interest);
                ht.display_interests(username);
                break;
            case 2:
                ht.display_interests(username);
                break;
            case 3:
                f.send_friend_request(username);
                break;
            case 4:
                f.view_friends(username);
                break;
            case 5:
                f.mutual_friends(username);
                break;
            case 6:
                f.suggest_friends(username, ht);
                break;
            case 7:
                ht.famous_interest();
                break;
            case 8:
                return;
                break;
            case 9:
                g.display();
                break; 
            case 10:
                cout << "Total number of users: " << countUsers() << endl;
                break;           
            default:
                cout << "Incorrect Option\n";
                break;
        } 
        cout << "Press 1 for Main Menu\n";
        cin >> ch;
    } while(ch == 1);
}


int main() {
    char ch;
    do {
        string fname;
        int choice;
        signUp s;
        logIn l;
        cout << "************ACCOUNT************" << endl;
        cout << "1.Log in\n2.Sign up\n3.Exit\n";
        cin >> choice;
        switch(choice) {
            case 1:
                l.user_login("User.txt");
                break;
            case 2:
                s.user_signUp("User.txt");
                break;
            case 3:
                return 0;
                break;
            default:
                cout << "Incorrect option choosed\n";
                break;
        }
        cout << "Want to visit again?" << endl;
        cin >> ch;
    } while(ch == 'y' || ch == 'Y');

return 0;
}
