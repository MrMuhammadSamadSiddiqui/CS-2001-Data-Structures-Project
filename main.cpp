
// NOTE TO ALL COLLABORATORS: PLEASE ADD COMMENTS WITH YOUR CODE JUST SO WE CAN UNDERSTAND WHAT YOU INTENDED TO ACHIEVE. NOT DETAILED ONES, JUST ENOUGH TO MAKE US UNDERSTAND. 

#include<iostream>
using namespace std;

class Section{
public:
	string name;
	Section* next;
	Section():next(nullptr){}
	Section(string a):next(nullptr),name(a){}
};

class Course_Name{
    string course_code;
    string short_form;
    string full_form;
    Course_Name* next;
    public:
    Course_Name():next(nullptr){}
};
 
struct location{
    // location of the teacher_office  
    public  : 
    string building  ; 
    string floor   ; 
    string room_number   ; 
    location(string b , string fl , string rn ){
        building  = b ; 
        floor  = fl   ; 
        room_number = rn  ; 
    }

 } ; 

struct Time {
    public : 
    int minutes  ; 
    int hours  ; 
    Time(){
        minutes   = 0 ; 
        hours  = 0  ; 
    }
    
    
    // function to calculate end time of class  n is basically the number of slots the class is in 2 slot 3 slot etc.
    Time end_time(int n , Time t){
        Time end_time  ; 
        end_time.minutes = t.minutes +(50*n) + ((n-1)*5) ;
        end_time.hours = t.hours + (end_time.minutes/60)  ; 
        end_time.minutes   = end_time.minutes%60  ;  
        return end_time ; 
    }

    void print_time(){
      cout << hours << " : " << minutes << endl   ; 
    }
};

class Slot{
    Teacher* teacher;
    Time* time_of_class;
    Classroom* classroom;
    Course_Name* course;	
	Section* section;
    Slot* next;
    public:
    Slot():next(nullptr),teacher(nullptr),time_of_class(nullptr),classroom(nullptr),course(nullptr),section(nullptr){}
};

class Teacher {    // TEACHER NODE
public:
	// Courses 
	// TimeTable
	string name;
	location* office;
    string email  ; 
	Teacher* left;
	Teacher* right;

	// Helper functions needed !!!
	Teacher() :left(nullptr), right(nullptr) {}
	Teacher(string a):name(a),left(nullptr),right(nullptr) {}
};

class Classroom { // CLASSROOM NODE
public:
	string name;
	// availibility status (bool ? i guess ) 
	Classroom* left;
	Classroom* right;

	// helper functions needed !!!
	Classroom() :left(nullptr), right(nullptr) {}
	Classroom(string a):name(a),left(nullptr),right(nullptr){}

};

template<typename T>
class BST {
	T* head;
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
		cout << head->name << ",";
		display_main(head->right);
	}
	void update_string_main(T* head) {
		if (head == nullptr) return;
		update_string_main(head->left);
		List += head->name;
		List += ',';
		update_string_main(head->right);
	}
public:
	BST():head(nullptr),List(""){}
	void add_entity(T* newone) {
		this->add_entity_main(this->head,newone);
		List = "";
		this->update_string_main(this->head);
	}
	void display() {
		this->display_main(this->head);
	}
	string get_List() {
		return this->List;
	}
};



struct Node {
    Node* next   ; 
    string course_name  ; 
     string section  ; 
     Node(){ next  = nullptr ; }
     Node(string c , string s ){
          course_name = c ; 
          section = s ; 
          next  = nullptr ; 
     }
};

void add_students_slots(){
      Slot* Monday = nullptr ; 
      Slot* Tuesday = nullptr ; 
      Slot* Wednesday = nullptr ; 
      Slot* Thursday = nullptr ;
      Slot* Friday  = nullptr ;  
}

class Add_My_Classes {
public:
    Node* head;     
    int total_classes;  

    Add_My_Classes() {
        head = nullptr;
        total_classes = 0;
    }

    
    void Insert_Classes(string course, string section) {
        if (Search_Class(course)) {
            cout << "This course is already added!" << endl;
            return;
        }

        Node* newNode = new Node(course, section);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newNode;
        }

        total_classes++;
        cout << "Class added successfully: " << course << " - Section " << section << endl;
    }


    bool Search_Class(string course) {
        Node* temp = head;

        while (temp != nullptr) {
            if (temp->course_name == course)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void Update_Section(string course, string newSection) {
        Node* temp = head;

        while (temp != nullptr) {
            if (temp->course_name == course) {
                temp->section = newSection;
                cout << "Section updated successfully!" << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Course not found!" << endl;
    }

    void Delete_Class(string course) {
        if (head == nullptr) {
            cout << "No classes to delete." << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        if (temp->course_name == course) {
            head = head->next;
            delete temp;
            total_classes--;
            cout << "Class removed successfully!" << endl;
            return;
        }

        while (temp != nullptr && temp->course_name != course) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Course not found!" << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
        total_classes--;
        cout << "Class removed successfully!" << endl;
    }

    void Display_Classes() {
        if (head == nullptr) {
            cout << "No classes added yet!" << endl;
            return;
        }

        cout << "\n===== Added Classes =====\n";
        Node* temp = head;

        while (temp != nullptr) {
            cout << "Course: " << temp->course_name
                 << " | Section: " << temp->section << endl;
            temp = temp->next;
        }
        cout << "Total Classes: " << total_classes << endl;
    }
};

class Timetable {
    void Search_Timetable(string day){
    
}

    void Search_Timetable(){
      
    }
    void Sort_Timetable(string day){
      
    }
    


}; 

int main(){
  cout<<"Welcome to FAST NATIONAL UNIVERISTY KARACHI CAMPUS timetable management system" << endl ; 
}
