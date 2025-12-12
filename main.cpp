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


string to_lowercase(string a) {
    string ret = "";
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != ' ') {
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
    void print();
    
    
};

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




class Teacher {   
public:
    string full_name="";
    string name="";
    string email="";
    string department="";
    Teacher* left=nullptr;
    Teacher* right=nullptr;
    Course_Name* courses=nullptr;
    location* office=nullptr;
    Slot* slots = nullptr;

    Teacher(){}
    Teacher(string a, string b) :full_name(a),department(b){
        name = to_lowercase(full_name);
    }
    void add_slot(Slot* newone);
    bool check_collision(Time* t);
    void print();
    
};  

class Classroom { 
public:
    Slot* slots=nullptr;
    string full_name;
    string name;
    Classroom* left;
    Classroom* right;
    Classroom():left(nullptr), right(nullptr){}
    Classroom(string a):full_name(a),left(nullptr),right(nullptr){
        name = to_lowercase(full_name);
    }
    void add_slot(Slot* newone);
    bool check_collision(Time* t);
    void print();
};

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
                cout << tree.search(match)->full_name;
                cout << endl;

                

                j = lps[j - 1];  // continue
            }
        }
        else {
            if (j) j = lps[j - 1];
            else i++;
        }
    }
    if(!found) cout<<"NO SUCH ENTITY EXISTS!"<<endl;
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
        cout<<time_of_class->starttime<<" - "<<time_of_class->endtime<<"\n"<<classroom->full_name<<"\n"<<section->full_name<<"\n"<<course->full_name<<"\n"<<teacher->full_name<<endl;
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

void Section::add_slot(Slot* newone) {
        if (slots == nullptr) slots = newone;
        else {
            Slot* temp = slots;
            while (temp ->next!= nullptr) temp = temp->next;
            temp->next = newone;
        }
}

void Teacher::add_slot(Slot* newone) {
        if (slots == nullptr) slots = newone;
        else {
            Slot* temp = slots;
            while (temp ->next!= nullptr) temp = temp->next;

            temp->next = newone;
        }
}

void Classroom::add_slot(Slot* newone) {
        if (slots == nullptr) slots = newone;
        else {
            Slot* temp = slots;
            while (temp ->next!= nullptr) temp = temp->next;


            temp->next = newone;
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

void Teacher::print(){
    Slot* temp=slots;
    while(temp!=nullptr){
        temp->print();
        cout<<endl;
        temp=temp->next;
    }
}

void Classroom::print(){
    Slot* temp=slots;
    while(temp!=nullptr){
        temp->print();
        cout<<endl;
        temp=temp->next;
    }
}

void Section::print(){
    Slot* temp=slots;
    while(temp!=nullptr){
        temp->print();
        cout<<endl;
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



int main() {
    int opt  ; 
    BST<Course_Name> courses;
    BST<Teacher> teachers;
    BST<Classroom> rooms;
    BST<Section> section;
    setup_file_data(courses, teachers, rooms, section); 
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
            inputCentered("----- FAST TIMETABLE -----" , centerRow-2) ;  
            cout << endl  ; 
            inputCentered ("OPTION 1 : Admin Mode" , centerRow) ; 
            inputCentered ("OPTION 2 : Student Mode" , centerRow+2) ; 
            inputCentered ("Enter Option : " , centerRow+4) ; 
            cin >> opt  ;
    while (opt!=1 && opt!=2){
        system("cls") ; 
        inputCentered ("Warning invalid option entered  " , centerRow) ;
        inputCentered ("Enter correct Option : " , centerRow+2) ;
        cin >> opt ;    
        }
    if (opt==1){
      int  n = Login(i , centerRow) ; 
      if (n==1){  
        system("cls")  ; 
        inputCentered("1. Enter Slot" , centerRow ) ; 
        cout << endl  ;  
        inputCentered("Enter your choice: "   , centerRow+2 )  ; 
        cin >> choice;
        if (choice == 1) {
            system("cls") ; 
        string day;
        cout << "Enter the day: ";
        cin >> day;
        if (to_lowercase(day) == "monday" || to_lowercase(day) == "tuesday" || to_lowercase(day) == "wednesday" || to_lowercase(day) == "thursday" || to_lowercase(day) == "friday") {
            string option;
            int n;
            cout << "Enter the Starting time: ";
            cin >> option;
            cout << "Enter the number of slots: ";
            cin >> n;
            Time* t=new Time(day, option, n);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Teacher* t1;
            while (1) {
                string teacher_name="";
                cout << endl;
                cout << "Enter the teacher name: ";
                getline(cin, teacher_name);            
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
                cout << endl;
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
            if(t2->check_collision(t)==1){
            Course_Name* t3;
            while (1) {
                string course_name="";
                cout << endl;
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
                cout << endl;
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
            if(t4->check_collision(t)==1){
                Slot* S=new Slot(t,t1, t2, t3, t4);
               Slot* S_teacher = new Slot(*S); 
                Slot* S_section = new Slot(*S);
                Slot* S_room    = new Slot(*S);
                

                t1->add_slot(S_teacher);
                    t4->add_slot(S_section);
                t2->add_slot(S_room);
                }
            }
            }   
        }
    }

    else break;   
    }
    
    else {
        system("cls")  ; 
        inputCentered ("Access denied check credentials and try again !!!" , centerRow)  ; 
        return 0 ; 
    }
}
    else if(opt==2){
        system ("cls") ; 
      cout << endl  ;     
            inputCentered("2. Search by Teacher" , centerRow+2)  ; 
            cout  << endl  ; 
            inputCentered("3. Search by Section" , centerRow+4) ; 
            cout << endl  ; 
            inputCentered("4. Exit" , centerRow+6 )   ; 
            cout << endl  ; 
            inputCentered("Enter your choice: "   , centerRow + 8 )  ; 
             cin >> choice;  
    }            

}
}
