#include<iostream>
using namespace std;
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

class Rooms{
     Search_For_Free_Rooms(string day , ){
       
     }    
};
class Teachers{
     Search_Teacher(string name){
       
     }
     Search_Teacher_Timetable(string name){
       
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
