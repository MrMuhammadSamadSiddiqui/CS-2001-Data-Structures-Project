#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<limits>
#include <windows.h>
#include <conio.h>
#include <iomanip>
using namespace std;
const string username = "Abdul Samad" ; 
const string password  = "12Ab45"  ; 
class Slot;
class Teacher;
class Classroom;
class Course_Name;
class Section;
class Time;
static int r  = 0 ; 


string to_lowercase(string a) {
    string ret = "";
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != ' '&&a[i]!='.') {
        if (a[i] >= 'A' && a[i] <= 'Z') ret += a[i] + 32;
        else ret += a[i];
        }
    }
    return ret;
}

class Section {
public:
    string name;
    string full_name;
    Section* left;
    Section* right;
    Slot* slots=nullptr;
    Section() :left(nullptr),right(nullptr),slots(nullptr) {}
    Section(string a) :left(nullptr),right(nullptr), slots(nullptr), full_name(a) {
        name=to_lowercase(full_name);
    }
    void add_slot(Slot* newone);
    bool check_collision(Time* t);
    void print_slots_list(string day);
    void print_info(string day){
        cout<<"----- SECTION: "<<full_name<<" -----"<<endl;
        if(this->slots!=nullptr){
            cout<<"----- SLOT LIST -----"<<endl;
            this->print_slots_list( day);
        }
        else cout<<"NO CLASSES RIGHT NOW"<<endl;
    }
};

bool equal_section(Section* t, Section* t1){
    return (t->full_name==t1->full_name);
}

class Course_Name {
    string course_code;
    string short_form;
    string full_form;
    public:
    Course_Name* left;
    Course_Name* right;
    string name; 
    string full_name;

    Course_Name() :left(nullptr),right(nullptr) {}
    Course_Name(string a, string b, string c) :course_code(a), short_form(b), full_form(c), left(nullptr),right(nullptr) {
        name = to_lowercase(course_code) + "," + to_lowercase(short_form) + "," + to_lowercase(full_form);
        full_name =course_code + "," +short_form + "," +full_form;
    }
};

bool equal_course(Course_Name* t, Course_Name* t1){
    return (t->name==t1->name);
}


class location {
public:
    string building;
    string floor;
    string room_number;
    location(string b, string fl, string rn) {
        building = b;
        floor = fl;
        room_number = rn;
    }
};

struct Time {
public:
    string day;
    int s_hours;
    int s_minutes;
    int e_hours;
    int e_minutes;
    string starttime;
    string endtime;
    Time() : day(""), s_hours(0), s_minutes(0), e_hours(0), e_minutes(0),
        starttime(""), endtime("") {
    }
    Time(string day, string starttime, int n)
    : day(day), starttime(starttime)
{
    // DYNAMIC PARSING
    int pos = starttime.find(':');
    s_hours = stoi(starttime.substr(0, pos));
    s_minutes = stoi(starttime.substr(pos + 1));

    // Duration calculation
    int duration = (50 * n) + ((n - 1) * 5);
    int totalMin = s_minutes + duration;

    e_hours = s_hours + (totalMin / 60);
    e_minutes = totalMin % 60;

    endtime = make_time(e_hours, e_minutes);
}

    string make_time(int h, int m) {
        string hh = (h < 10 ? "0" : "") + to_string(h);
        string mm = (m < 10 ? "0" : "") + to_string(m);
        return hh + ":" + mm;
    }
    void print_time() {

        cout << "Start: " << starttime << "  End: " << endtime << endl;
    }
    void print_time_with_day() {
        cout<<day<<endl;
        cout << "Start: " << starttime << "  End: " << endtime << endl;
    }
    
};

bool equal_time(Time* t, Time* t1){
    return (t->day==t1->day&&t->s_hours==t1->s_hours&&t->s_minutes==t1->s_minutes&&t->e_hours==t1->e_hours&&t->e_minutes==t1->e_minutes);
}


class Teacher {   
public:
    string full_name="";
    string name="";
    string email="";
    string department="";
    Teacher* left=nullptr;
    Teacher* right=nullptr;
    // Course_Name* courses=nullptr;
    // location* office=nullptr;
    Slot* slots = nullptr;
    Teacher(){}
    Teacher(string a, string b) :full_name(a),department(b){
        name = to_lowercase(full_name);
        for(int i=0;i<full_name.size();i++){
            if(full_name[i]>='A'&&full_name[i]<='Z') email+=full_name[i]+32;
            else if(full_name[i]==' ') email+='.';
            else email+=full_name[i];
        }
        email+="@nu.edu.pk";
    }
    void add_slot(Slot* newone);
    bool check_collision(Time* t);
    void print_slots_list(string day);
    void print_info(string day){
        cout<<"Full Name: "<<full_name<<endl;
        cout<<"Department: "<<department<<endl;
        cout<<"Email: "<<email<<endl;
        if(this->slots!=nullptr){
            cout<<"----- SLOT LIST -----"<<endl;
            this->print_slots_list(day);
        }
        else cout<<"NO CLASSES RIGHT NOW"<<endl;
    }
};  

bool equal_teacher(Teacher* t, Teacher* t1){
    return (t->full_name==t1->full_name);
}


class Classroom { 
public:
    Slot* slots=nullptr;
    string building;
    string room;
    string full_name;
    string name;
    Classroom* left;
    Classroom* right;
    Classroom():left(nullptr), right(nullptr){}
    Classroom(string a):full_name(a),left(nullptr),right(nullptr),building(""),room(""){
        name = to_lowercase(full_name);
        int i;
        for(i=0;full_name[i]!=',';i++) building+=full_name[i];
        for(int j=i+1;j<full_name.size();j++) room+=full_name[j];
    }
    void add_slot(Slot* newone);
    bool check_collision(Time* t);
    void print_slots_list(string day);
    void print_info(string day){
        cout<<"Building: "<<building<<endl;
        cout<<"Room: "<<room<<endl;
         if(this->slots!=nullptr){
            cout<<"----- SLOT LIST -----"<<endl;
            this->print_slots_list(day);
        }
        else cout<<"NO CLASSES RIGHT NOW"<<endl;
    }
};

bool equal_room(Classroom* t, Classroom* t1){
    return (t->full_name==t1->full_name);
}

template<typename T>
class BST {
    string List;
    void add_entity_main(T*& head, T* newone) {
        if (head == nullptr) {
            head = newone;
            return;
        }
        if (newone->name < head->name) add_entity_main(head->left, newone);
        else add_entity_main(head->right, newone);
    }
    void display_main(T*& head) {
        if (head == nullptr) return;
        display_main(head->left);
        cout << head->name << ":";
        display_main(head->right);
    }
    void update_string_main(T* head) {
        if (head == nullptr) return;
        update_string_main(head->left);
        List += head->name;
        List += ':';
        update_string_main(head->right);
    }

    T* searchHelper(T* node, string target) {
        if (!node) return nullptr;

        if (node->name == target)  
            return node;

        if (target < node->name)
            return searchHelper(node->left, target);
        else
            return searchHelper(node->right, target);
    }
public:
    T* head;
    BST() :head(nullptr), List("") {}
    void add_entity(T* newone) {
        this->add_entity_main(this->head, newone);
        List = "";
        this->update_string_main(this->head);
    }
    void display() {
        this->display_main(this->head);
    }
    T* search(string newone) {
        return searchHelper(this->head, newone);
    }
    string get_List() {
        return this->List;
    }
};



void setup_file_data(BST<Course_Name>& courses, BST<Teacher>& teachers, BST<Classroom>& rooms,BST<Section>& section) {
    fstream file;
    file.open("Courses.txt");
    string line;
    while (getline(file, line)) {
        string code = "";
        string form = "";
        string full = "";
        int index = 0;
        for (int i = 0; line[i] != ','; i++, index++) code += line[i];
        for (int i = index + 1; line[i] != ','; i++, index++) form += line[i];
        for (int i = index + 2; i < line.size(); i++) full += line[i];
        Course_Name* newone = new Course_Name(code, form, full);
        courses.add_entity(newone);
    }
    file.close();
    file.open("Teachers.txt");
    line = "";
    while (getline(file, line)) {
        string name = "";
        string dep = "";
        int index = 0;
        for (int i = 0; line[i] != ','; i++, index++) name += line[i];
        for (int i = index + 1; i < line.size(); i++, index++) dep += line[i];
        Teacher* newone = new Teacher(name, dep);
        teachers.add_entity(newone);
    }
    file.close();
    file.open("Classrooms.txt");
    line = "";
    while (getline(file, line)) {
        string name = "";
        int index = 0;
        for (int i = 0; i < line.size(); i++, index++) name += line[i];
        Classroom* newone = new Classroom(name);
        rooms.add_entity(newone);
    }
    file.close();
    file.open("Sections.txt");
    line = "";
    while (getline(file, line)) {
        string name = "";
        int index = 0;
        for (int i = 0; i < line.size(); i++, index++) name += line[i];
        Section* newone = new Section(name);
        section.add_entity(newone);
    }
    file.close();
    
}

// KMP STRING SEARCH
template <typename T>
void findMatches(BST<T> tree,string big, string pattern) {
    bool found=false;
    int n = big.size();
    int m = pattern.size();

    // lowercase copies for matching
    string bigLow = "";
    for (char c : big) bigLow += tolower(c);
    string patLow = "";
    for (char c : pattern) patLow += tolower(c);

    // Build KMP LPS table
    vector<int> lps(m, 0);
    for (int i = 1, len = 0; i < m; ) {
        if (patLow[i] == patLow[len]) lps[i++] = ++len;
        else if (len) len = lps[len - 1];
        else lps[i++] = 0;
    }

    // KMP search + immediate printing
    for (int i = 0, j = 0; i < n; ) {

        if (bigLow[i] == patLow[j]) {
            i++;
            j++;

            if (j == m) {
                int matchStart = i - j;

                // Go LEFT until ':'
                int L = matchStart;
                while (L > 0 && big[L] != ':') L--;
                if (big[L] == ':') L++;

                // Go RIGHT until ':'
                int R = matchStart;
                while (R < n && big[R] != ':') R++;

                // Extract & print full name
                     
                if(!found)  cout << "Did you mean ?\n";
                found=true;
                string match = big.substr(L, R - L);
                cout << setw(50) << tree.search(match)->full_name;  // Fixed width
                if (r%3 == 0){  // After every 3rd item, add newline
                cout << endl; 
                }
                r++;
                j = lps[j - 1];  // continue
            }
        }
        else {
            if (j) j = lps[j - 1];
            else i++;
        }
    }
    if(!found) cout<<"NO SUCH ENTITY EXISTS!"<<endl;
    else cout<<endl;
}

class Slot {
public:
    Time* time_of_class;
    Teacher* teacher;
    Classroom* classroom;
    Course_Name* course;
    Section* section;
    Slot* next;
    Slot():next(nullptr){}
    Slot(Time* t, Teacher* t1, Classroom* t2, Course_Name* t3, Section* t4) :next(nullptr), teacher(t1), time_of_class(t), classroom(t2), course(t3), section(t4) {}
    void print(){
        cout<<time_of_class->day<<"\n"<<time_of_class->starttime<<" - "<<time_of_class->endtime<<"\n"<<classroom->full_name<<"\n"<<section->full_name<<"\n"<<course->full_name<<"\n"<<teacher->full_name<<endl;
    }
    Slot(Slot& other) {
    time_of_class = other.time_of_class;
    teacher = other.teacher;
    classroom = other.classroom;
    course = other.course;
    section = other.section;
    next = nullptr;
    }
};

int get_day_order(string a){
    if(a=="monday") return 0;
    else if(a=="tuesday") return 1;
    else if(a=="wednesday") return 2;
    else if(a=="thursday") return 3;
    else if(a=="friday") return 4;
    return -1;
}

void Section::add_slot(Slot* newone) {
        if (slots == nullptr){
             slots = newone;
             return;
        }
        else {
            
            if(get_day_order(newone->time_of_class->day)<get_day_order(slots->time_of_class->day)){
                newone->next=slots;
                slots=newone;
                return;
            }
            Slot* prev=slots;
            Slot* prev2=slots;
            while(1){
                if(get_day_order(newone->time_of_class->day)==get_day_order(prev->time_of_class->day)) break;
                if(prev->next!=nullptr&&get_day_order(newone->time_of_class->day)<get_day_order(prev->next->time_of_class->day)){
                    newone->next=prev->next;
                    prev->next=newone;
                    return;
                }
                if(prev->next==nullptr&&get_day_order(newone->time_of_class->day)>get_day_order(prev->time_of_class->day)){
                    prev->next=newone;
                    return;
                }
                prev2=prev;
                prev=prev->next;
            }
            while(prev->next!=nullptr&&get_day_order(newone->time_of_class->day)==get_day_order(prev->time_of_class->day)){
                if(newone->time_of_class->s_hours*60 + newone->time_of_class->s_minutes<prev->time_of_class->s_hours*60 + prev->time_of_class->s_minutes){
                    newone->next=prev;
                    prev2->next=newone;
                    return;
                }
                prev2=prev;
                prev=prev->next;
            }
        }
}

void Teacher::add_slot(Slot* newone) {
        if (slots == nullptr){
             slots = newone;
             return;
        }
        else {
            
            if(get_day_order(newone->time_of_class->day)<get_day_order(slots->time_of_class->day)){
                newone->next=slots;
                slots=newone;
                return;
            }
            Slot* prev=slots;
            Slot* prev2=slots;
            while(1){
                if(get_day_order(newone->time_of_class->day)==get_day_order(prev->time_of_class->day)) break;
                if(prev->next!=nullptr&&get_day_order(newone->time_of_class->day)<get_day_order(prev->next->time_of_class->day)){
                    newone->next=prev->next;
                    prev->next=newone;
                    return;
                }
                if(prev->next==nullptr&&get_day_order(newone->time_of_class->day)>get_day_order(prev->time_of_class->day)){
                    prev->next=newone;
                    return;
                }
                prev2=prev;
                prev=prev->next;
            }
            while(prev->next!=nullptr&&get_day_order(newone->time_of_class->day)==get_day_order(prev->time_of_class->day)){
                if(newone->time_of_class->s_hours*60 + newone->time_of_class->s_minutes<prev->time_of_class->s_hours*60 + prev->time_of_class->s_minutes){
                    newone->next=prev;
                    prev2->next=newone;
                    return;
                }
                prev2=prev;
                prev=prev->next;
            }
        }        
}

void Classroom::add_slot(Slot* newone) {
        if (slots == nullptr){
             slots = newone;
             return;
        }
        else {
            
            if(get_day_order(newone->time_of_class->day)<get_day_order(slots->time_of_class->day)){
                newone->next=slots;
                slots=newone;
                return;
            }
            Slot* prev=slots;
            Slot* prev2=slots;
            while(1){
                if(get_day_order(newone->time_of_class->day)==get_day_order(prev->time_of_class->day)) break;
                if(prev->next!=nullptr&&get_day_order(newone->time_of_class->day)<get_day_order(prev->next->time_of_class->day)){
                    newone->next=prev->next;
                    prev->next=newone;
                    return;
                }
                if(prev->next==nullptr&&get_day_order(newone->time_of_class->day)>get_day_order(prev->time_of_class->day)){
                    prev->next=newone;
                    return;
                }
                prev2=prev;
                prev=prev->next;
            }
            while(prev->next!=nullptr&&get_day_order(newone->time_of_class->day)==get_day_order(prev->time_of_class->day)){
                if(newone->time_of_class->s_hours*60 + newone->time_of_class->s_minutes<prev->time_of_class->s_hours*60 + prev->time_of_class->s_minutes){
                    newone->next=prev;
                    prev2->next=newone;
                    return;
                }
                prev2=prev;
                prev=prev->next;
            }
        }
}

bool Teacher::check_collision(Time* t){
    Slot* temp=slots;
    int newstart=t->s_hours*60+t->s_minutes;
    int newend=t->e_hours*60+t->e_minutes;
    if(temp==nullptr) return 1;
    while(temp!=nullptr){
        if(t->day==temp->time_of_class->day){
            if(newstart<temp->time_of_class->e_hours*60+temp->time_of_class->e_minutes&&newend>temp->time_of_class->s_hours*60+temp->time_of_class->s_minutes){
                cout<<"OVERLAP FOUND!"<<endl;
                temp->print();
                return 0;
            }
        }
        temp=temp->next;
    }
    return 1;
}


bool Classroom::check_collision(Time* t){
    Slot* temp=slots;
    int newstart=t->s_hours*60+t->s_minutes;
    int newend=t->e_hours*60+t->e_minutes;
    if(temp==nullptr) return 1;
    while(temp!=nullptr){
        if(t->day==temp->time_of_class->day){
            if(newstart<temp->time_of_class->e_hours*60+temp->time_of_class->e_minutes&&newend>temp->time_of_class->s_hours*60+temp->time_of_class->s_minutes){
                cout<<"OVERLAP FOUND!"<<endl;
                temp->print();
                return 0;
            }
        }
        temp=temp->next;
    }
    return 1;
}


bool Section::check_collision(Time* t){
    Slot* temp=slots;
    int newstart=t->s_hours*60+t->s_minutes;
    int newend=t->e_hours*60+t->e_minutes;
    if(temp==nullptr) return 1;
    while(temp!=nullptr){
        if(t->day==temp->time_of_class->day){
            if(newstart<temp->time_of_class->e_hours*60+temp->time_of_class->e_minutes&&newend>temp->time_of_class->s_hours*60+temp->time_of_class->s_minutes){
                cout<<"OVERLAP FOUND!"<<endl;
                temp->print();
                return 0;
            }
        }
        temp=temp->next;
    }
    return 1;
}

void Teacher::print_slots_list(string day){
    Slot* temp=slots;
    while(temp!=nullptr){
        cout<<endl;
        if(day=="all") temp->print();
        else if(day==temp->time_of_class->day) temp->print();
        temp=temp->next;
    }
}

void Classroom::print_slots_list(string day){
    Slot* temp=slots;
    while(temp!=nullptr){
        cout<<endl;
        if(day=="all") temp->print();
        else if(day==temp->time_of_class->day) temp->print();
        temp=temp->next;
    }
}

void Section::print_slots_list(string day){
    Slot* temp=slots;
    while(temp!=nullptr){
        cout<<endl;
        if(day=="all") temp->print();
        else if(day==temp->time_of_class->day) temp->print();
        temp=temp->next;
    }
}
// Move cursor to (x,y)
void goToXY(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Print message centered horizontally at given row (vertical)
void inputCentered(const string& message, int row) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int x = (width - message.length()) / 2;  // center horizontally

    goToXY(x, row);
    cout << message;
}


int Login(int i , int centerRow ){
    
   
     system("cls") ; 
        if (i==4){
            return 0 ; 
        }
         string user_name  ; 
         string pass_word  ; 
        cout  << endl ; 
        cin.ignore() ; 
        inputCentered("Enter username: " , centerRow);
        getline (cin , user_name) ; 
        cin.ignore()  ; 
       inputCentered("Enter password: " , centerRow+2);
        getline (cin , pass_word) ; 
        if (user_name == username && password==pass_word){
            return 1 ; 
            // code  ; 
        }
        else if (user_name != username && password==pass_word){
            inputCentered( "Warning wrong username entered !!!" , centerRow+4) ; 
            getch() ; 
            i++ ; 
            Login(i , centerRow ) ; 
        }
        else if (user_name == username && password!=pass_word){
            inputCentered ("Warning wrong username or password entered !!!" , centerRow+4) ; 
            getch() ; 
            i++ ; 
            Login(i , centerRow ) ; 
        }
        else if (user_name != username && password!=pass_word){
            inputCentered("Warning wrong username or password entered !!!" , centerRow+4) ; 
            getch() ; 
            i++ ; 
            Login(i , centerRow ) ; 
        } 
}



void delete_node_teacher(Time* t, Teacher* t1, Classroom* t2, Course_Name* t3, Section* t4){
    
    
    if(equal_time(t1->slots->time_of_class,t)&&equal_room(t1->slots->classroom,t2)&&equal_course(t1->slots->course,t3)&&equal_section(t1->slots->section,t4)){
        Slot* del = t1->slots;         
        t1->slots = t1->slots->next;   
        delete del;                    
    }
    else{
        Slot* temp=t1->slots;
        while (temp != nullptr) {
            if(equal_time(temp->next->time_of_class,t)&&equal_room(temp->next->classroom,t2)&&equal_course(temp->next->course,t3)&&equal_section(temp->next->section,t4)){
                Slot* del=temp->next;
                if(temp->next->next!=nullptr){
                    temp->next=temp->next->next;
                    delete del;
                }
                else{
                    delete del;
                    temp->next=nullptr;
                }
            }
            temp = temp->next;  
        }
    }
    
    
    
    
}


void delete_node_classroom(Time* t, Teacher* t1, Classroom* t2, Course_Name* t3, Section* t4){
        
    
    if(equal_time(t2->slots->time_of_class,t)&&equal_teacher(t2->slots->teacher,t1)&&equal_course(t2->slots->course,t3)&&equal_section(t2->slots->section,t4)){
        Slot* del = t2->slots;         
        t2->slots = t2->slots->next;   
        delete del;                    
    }
    else{
        Slot* temp=t2->slots;
         while (temp != nullptr) {
            if(equal_time(temp->next->time_of_class,t)&&equal_teacher(temp->next->teacher,t1)&&equal_course(temp->next->course,t3)&&equal_section(temp->next->section,t4)){
                Slot* del=temp->next;
                if(temp->next->next!=nullptr){
                    temp->next=temp->next->next;
                    delete del;
                }
                else{
                    delete del;
                    temp->next=nullptr;
                }
            }
            temp = temp->next;  
        }
    }
      
    
}

void delete_node_section(Time* t, Teacher* t1, Classroom* t2, Course_Name* t3, Section* t4){
        
    
    if(equal_time(t4->slots->time_of_class,t)&&equal_teacher(t4->slots->teacher,t1)&&equal_course(t4->slots->course,t3)&&equal_room(t4->slots->classroom,t2)){
        Slot* del = t4->slots;         
        t4->slots = t4->slots->next;   
        delete del;                    
    }
    else{
        Slot* temp=t4->slots;
        while (temp != nullptr) {
            if(equal_time(temp->next->time_of_class,t)&&equal_teacher(temp->next->teacher,t1)&&equal_course(temp->next->course,t3)&&equal_room(temp->next->classroom,t2)){
                Slot* del=temp->next;
                if(temp->next->next!=nullptr){
                    temp->next=temp->next->next;
                    delete del;
                }
                else{
                    delete del;
                    temp->next=nullptr;
                }
            }
            temp = temp->next;  
        }
    }
}

class Admin{
    public:
    string username;
    string password;
    Admin* next=nullptr;
    Admin():next(nullptr),username(""),password(""){}
    Admin(string a, string b):next(nullptr),username(a),password(b){
    }
};

class HashMap{
    public:
    Admin* table[26]={nullptr};
    HashMap(){
        fstream file;
        file.open("Admins.txt");
        string line;
        while (getline(file, line)) {
            string username="";
            string password="";
            int hash=0;
            int index=0;
            for(int i=0;line[i]!=',';i++,index++){
                 username+=line[i];
            }
            hash=calculate_hash(username);
            for(int i=index+1;i<line.size();i++) password+=line[i];
            if(table[hash]==nullptr) table[hash]=new Admin(username,password);
            else{
                Admin* temp=table[hash];
                while(temp->next!=nullptr) temp=temp->next;
                temp->next=new Admin(username, password);
            } 
        }
        file.close();
    }

    int calculate_hash(string username){
        int hash=0;
            for(int i=0;i<username.size();i++){
                 if(username[i]>='A'&&username[i]<='Z')  hash+=(username[i]+32);
                 else if (username[i]>='a'&&username[i]<='z')hash+=username[i];
                 hash=hash%26;
            }
        return hash;
    }

    string search(string username, string password){
        string stat="";
        int hash=calculate_hash(username);
        if(table[hash]==nullptr){
            stat="00";
            return stat;
        }
        Admin* temp=table[hash];
        while(temp!=nullptr){
            stat="";
            if(temp->username==username) stat+="1";
            if(temp->password==password) stat+="1";
            if(stat=="11"){
                return stat;
            }
            temp=temp->next;
        }
        return stat;
    }
};


int Login_Admin(HashMap& H, int centerRow){
    system("cls") ; 
    string user_name  ; 
    string pass_word  ; 
    cout  << endl ; 
    cin.ignore() ; 
    inputCentered("Enter username: " , centerRow);
    getline (cin , user_name) ; 
    cin.ignore() ; 
    inputCentered("Enter password: " , centerRow+2);
    getline (cin , pass_word) ; 
    string stat=H.search(user_name,pass_word);
    if(stat=="11") return 1;
    else if(stat=="00"){
        cin.ignore()  ;
        inputCentered ("Warning wrong username or password entered !!!" , centerRow+4) ; 
        _getch();
    }
    return 0;
}

bool validate_day(string day){
    return(to_lowercase(day) == "monday" || to_lowercase(day) == "tuesday" || to_lowercase(day) == "wednesday" || to_lowercase(day) == "thursday" || to_lowercase(day) == "friday");
}

int main() {
    int opt  ; 
    BST<Course_Name> courses;
    BST<Teacher> teachers;
    BST<Classroom> rooms;
    BST<Section> section;
    setup_file_data(courses, teachers, rooms, section);   
    HashMap Admins;
    int  i =  1 ;
     // Get console size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    int centerRow = height / 2;
    string user_name  ; 
    string pass_word  ;  
    int choice;
    while(1){
            system("cls");
            inputCentered("----- FAST TIMETABLE -----" , centerRow-2) ;  
            cout << endl  ; 
            inputCentered ("OPTION 1 : Admin Mode" , centerRow) ; 
            inputCentered ("OPTION 2 : Student Mode" , centerRow+2) ; 
            inputCentered ("OPTION 3 : Exit" , centerRow+4) ; 
            cout<<endl;
            inputCentered ("Enter Option : " , centerRow+6) ; 
            cin >> opt ;
    while (opt!=1 && opt!=2&&opt!=3){
        system("cls") ; 
        inputCentered ("Warning invalid option entered  " , centerRow) ;
        inputCentered ("Enter correct Option : " , centerRow+2) ;
        cin >> opt ;    
        }
    if (opt==1){
    //   int  n = Login(i , centerRow); 
    int n=Login_Admin(Admins,centerRow);
      if (n==1){  
        while(1){
            system("cls")  ; 
            inputCentered("1. Enter Slot" , centerRow ) ; 
            inputCentered("2. Delete Slot" , centerRow+2 ) ; 
            inputCentered("3. Exit Admin Mode" , centerRow+4 ) ; 
            inputCentered("Enter your choice: "   , centerRow+6 )  ; 
            cin >> choice;
            if (choice == 1) {
            system("cls"); 
            string day;
            cout <<"Enter the Day: ";
            cin >> day;
            if (validate_day(day)) {
                string option;
                int n;
                cout <<   "Enter the Starting time: ";
                cin >> option;
                cout  << "Enter the number of slots: ";
                cin >> n;
                Time* t=new Time(day, option, n);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Teacher* t1;
                while (1) {
                    string teacher_name="";
                    cout<< "Enter the Teacher Name : ";
                    getline(cin, teacher_name);            
                    r= 1  ; 
                    if (teachers.search(to_lowercase(teacher_name)) != nullptr) {
                        t1=teachers.search(to_lowercase(teacher_name));
                        break;
                    }
                    else {
                        findMatches(teachers, teachers.get_List(), to_lowercase(teacher_name));
                    }
                }
                if(t1->check_collision(t)==1){
                Classroom* t2;
                while (1) {
                    string classroom_name="";                    
                    cout <<"Enter the Classroom: ";
                    getline(cin, classroom_name);  
                    r= 0 ;           
                    if (rooms.search(to_lowercase(classroom_name)) != nullptr) {
                        t2=rooms.search(to_lowercase(classroom_name));
                        break;
                    }
                    else {
                        findMatches(rooms, rooms.get_List(), to_lowercase(classroom_name));
                    }
                }
                if(t2->check_collision(t)==1){
                Course_Name* t3;
                while (1) {
                    string course_name="";
                    cout <<"Enter the Course: ";
                    getline(cin, course_name);            
                    r= 1 ; 
                    if (courses.search(to_lowercase(course_name)) != nullptr) {
                        t3=courses.search(to_lowercase(course_name));
                        break;
                    }
                    else {
                        findMatches(courses, courses.get_List(), to_lowercase(course_name));
                    }
                }            
                 
    
                Section* t4;
                while (1) {
                    string section_name="";
                    cout <<"Enter the Section: "; 
                    getline(cin, section_name);            
                    r= 0 ; 
                    if (section.search(to_lowercase(section_name)) != nullptr) {
                        t4=section.search(to_lowercase(section_name));
                        break;
                    }
                    else {
                        findMatches(section, section.get_List(), to_lowercase(section_name));
                    }
                }
                if(t4->check_collision(t)==1){
                    Slot* S=new Slot(t,t1, t2, t3, t4);
                    Slot* S_teacher = new Slot(*S); 
                    Slot* S_section = new Slot(*S);
                    Slot* S_room    = new Slot(*S);
                    t1->add_slot(S_teacher);
                    t4->add_slot(S_section);
                    t2->add_slot(S_room);
                    cout<<"----- NEW SLOT ADDED -----"<<endl;
                    S->print();
                    cout<<"\nPress Any key to continue: ";
                    _getch();                    
                }
                else{
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
                }
                }
                else{
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
                }
                }
                else{
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
                }
                }
                else{
                    cout<<"Enter Valid Day"<<endl;
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
                }   
            }

            else if(choice==2){
                system("cls");
                string day;
                string time;
                int n;
                cout<<"Enter the Day: ";
                cin>>day;
               if (validate_day(day)){

               
                cout<<"Enter the Starting time of Slot: ";
                cin>>time;
                cout<<"Enter the number of slots: ";
                cin>>n;
                Time* t=new Time(day,time,n);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Teacher* t1;
                while (1) {
                    string teacher_name="";
                    cout << "Enter the Teacher name: ";
                    getline(cin, teacher_name);            
                    if (teachers.search(to_lowercase(teacher_name)) != nullptr) {
                        t1=teachers.search(to_lowercase(teacher_name));
                        break;
                    }
                    else {
                        findMatches(teachers, teachers.get_List(), to_lowercase(teacher_name));
                    }
                }
                Classroom* t2;
                while (1) {
                    string classroom_name="";                    
                    cout << "Enter the Classroom: ";
                    getline(cin, classroom_name);            
                    if (rooms.search(to_lowercase(classroom_name)) != nullptr) {
                        t2=rooms.search(to_lowercase(classroom_name));
                        break;
                    }
                    else {
                        findMatches(rooms, rooms.get_List(), to_lowercase(classroom_name));
                    }
                }
                Course_Name* t3;
                while (1) {
                    string course_name="";
                    cout << "Enter the Course: ";
                    getline(cin, course_name);            
                    if (courses.search(to_lowercase(course_name)) != nullptr) {
                        t3=courses.search(to_lowercase(course_name));
                        break;
                    }
                    else {
                        findMatches(courses, courses.get_List(), to_lowercase(course_name));
                    }
                }  
                Section* t4;
                while (1) {
                    string section_name="";
                    cout << "Enter the Section: ";
                    getline(cin, section_name);            
                    if (section.search(to_lowercase(section_name)) != nullptr) {
                        t4=section.search(to_lowercase(section_name));
                        break;
                    }
                    else {
                        findMatches(section, section.get_List(), to_lowercase(section_name));
                    }
                }
                Slot* temp=t1->slots;
                bool found=false;
                while(temp!=nullptr){
                    if(equal_time(temp->time_of_class,t)&&equal_room(temp->classroom,t2)&&equal_course(temp->course,t3)&&equal_section(temp->section,t4)){
                        cout<<"----- FOUND ONE SLOT -----"<<endl;
                        temp->print();
                        found=true;
                        break;
                    }
                    temp=temp->next;
                }
                if(found){
                    string confirm="";
                    while(1){
                        cout<<"Do you want to delete it ? Y/N: ";
                    cin>>confirm;
                    if(confirm=="Y"||confirm=="y"){
                        delete_node_teacher(t,t1,t2,t3,t4);
                        delete_node_classroom(t,t1,t2,t3,t4);
                        delete_node_section(t,t1,t2,t3,t4);
                        cout<<"NODE DELETED SUCCESSFULLY "<<endl;
                        cout<<"\nPress Any key to continue: ";
                        _getch(); 
                        break;
                    }
                    else if(confirm=="N"||confirm=="n") break;
                    else cout<<"Only (Y/y) or (N/n) inputs are accepted"<<endl;
                    }
                }
                else{
                    cout<<"No Slot found"<<endl;
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
                }
            }
            else{
                    cout<<"Enter Valid Day"<<endl;
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
            }   
            }
            else if(choice==3) break;   
        }
    }
    else {
        system("cls")  ; 
        inputCentered ("Access denied check credentials and try again !!!" , centerRow)  ; 
        _getch();
    }
}
    else if(opt==2){
        while(1){
            system ("cls") ; 
            cout << endl  ;     
            inputCentered("1. Search Teacher Info" , centerRow); 
            cout  << endl  ; 
            inputCentered("2. Search by Section" , centerRow+2); 
            cout << endl  ; 
            inputCentered("3. Search by Classroom" , centerRow+4 )   ; 
            cout << endl  ; 
            inputCentered("4. Exit" , centerRow+6 )   ; 
            cout << endl  ; 
            inputCentered("Enter your choice: "   , centerRow + 8 )  ; 
            cin >> choice;  
            if(choice==1){
                system("cls");
                Teacher* t1;
                bool quit=false;
                string day;
                while (1) {
                    
                    string teacher_name="";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter the Teacher name ('0' for cancel searching): ";
                    getline(cin, teacher_name);            
                    cout<<"Enter the Day (Write 'all' for complete Slots): ";
                    cin>>day;
                    if(validate_day(day)||day=="all"){
                    if(teacher_name=="0"){
                        quit=true;
                        break;
                    }
                    if (teachers.search(to_lowercase(teacher_name)) != nullptr) {
                        t1=teachers.search(to_lowercase(teacher_name));
                        break;
                    }
                    else {
                        findMatches(teachers, teachers.get_List(), to_lowercase(teacher_name));
                    }          
                    }      
                    else{
                        cout<<"Enter Valid Day"<<endl;
                        cout<<"\nPress Any key to continue: ";
                        _getch(); 
                        quit=true;
                        break;
                    }   
                }
                if(!quit){
                    t1->print_info(day);
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
                }
            }
            else if(choice==2){
                system("cls");
                bool quit=false;
                Section* t4;
                string day;
                while (1) {
                    string section_name="";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter the Section ('0' for cancel searching): ";
                    getline(cin, section_name); 
                    cout<<"Enter the Day (Write 'all' for complete Slots): ";
                    cin>>day;
                      if(validate_day(day)||day=="all"){
                    if(section_name=="0"){
                        quit=true;
                        break;
                    }           
                    if (section.search(to_lowercase(section_name)) != nullptr) {
                        t4=section.search(to_lowercase(section_name));
                        break;
                    }
                    else {
                        findMatches(section, section.get_List(), to_lowercase(section_name));
                    }
                     }      
                    else{
                        cout<<"Enter Valid Day"<<endl;
                        cout<<"\nPress Any key to continue: ";
                        _getch(); 
                        quit=true;
                        break;
                    }   
                }
                if(!quit){
                    t4->print_info(day);
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
                }
            }
            else if(choice==3){
                system("cls");
                bool quit=false;
                Classroom* t2;
                string day;
                while (1) {
                    string classroom_name="";                    
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout <<"Enter the Classroom ('0' for cancel searching): ";
                    getline(cin, classroom_name);  
                    cout<<"Enter the Day (Write 'all' for complete Slots): ";
                    cin>>day;
                      if(validate_day(day)||day=="all"){
                    if(classroom_name=="0"){
                        quit=true;
                        break;
                    }   
                    if (rooms.search(to_lowercase(classroom_name)) != nullptr) {
                        t2=rooms.search(to_lowercase(classroom_name));
                        break;
                    }
                    else {
                        findMatches(rooms, rooms.get_List(), to_lowercase(classroom_name));
                    }
                     }      
                    else{
                        cout<<"Enter Valid Day"<<endl;
                        cout<<"\nPress Any key to continue: ";
                        _getch(); 
                        quit=true;
                        break;
                    }   
                }
                if(!quit){
                    t2->print_info(day);
                    cout<<"\nPress Any key to continue: ";
                    _getch(); 
                }
            }
            else if(choice ==4) break;
        }
    }     
    else if(opt==3) break;
}
}
