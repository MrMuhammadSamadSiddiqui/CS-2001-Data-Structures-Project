// NOTE TO ALL COLLABORATORS: PLEASE ADD COMMENTS WITH YOUR CODE JUST SO WE CAN UNDERSTAND WHAT YOU INTENDED TO ACHIEVE. NOT DETAILED ONES, JUST ENOUGH TO MAKE US UNDERSTAND. 

#include<iostream>
using namespace std;

class Teacher {    // TEACHER NODE
public:
	string name;
	// location of teacher
	// courses that the teacher will teach
	// TimeTable
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

/*
    This is a BST
    Why I added this ? you may ask 
    While entring slots we need to make sure all teachers name or classroom names are valid. 
    for this we need a string through which we will use KMP or Boyre moore to validate
    BUT !!!
    we also need a storage and we can't just update string everytime separately. 
    So here is the BST
    It will make Teacher's or any Node's own BST, add into it, and will update List. 
    This is how we will acquire the List of Teachers or any Node anytime, irrespective of update. this will always give us alphabetical order 

    NOTE: I ADDED LIST TO THIS JUST SO WE CAN APPLY BOYRE MOORE OR KMP FOR MULTIPLE SUBSTIRNG SEARCH OTHERWISE BST SEARCHING IS ALOT FASTER BUT STRICT 
*/
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
    Search_Timetable(string day){

    }

    Search_Timetable(){
      
    }
    Sort_Timetable(string day){
      
    }
    


}; 

int main(){
  cout<<"Welcome to FAST NATIONAL UNIVERISTY KARACHI CAMPUS timetable management system" << endl ; 
}
