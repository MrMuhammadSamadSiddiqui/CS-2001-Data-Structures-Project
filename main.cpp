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

class Add_My_Classes{
     public : 
     Node* head  ; 
     Insert_Classes(string cn , string sc){
          Node* classes = new Node(cn , sc) ; 
          
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
