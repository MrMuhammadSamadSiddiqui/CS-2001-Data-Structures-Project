
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


// AVL code needs modification as per our program 

#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// Utility functions (no <algorithm> used)
int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* n) {
    if (n == nullptr) return 0;
    return n->height;
}

int getBalance(Node* n) {
    if (n == nullptr) return 0;
    return height(n->left) - height(n->right);
}

// Rotations
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxVal(height(y->left), height(y->right)) + 1;
    x->height = maxVal(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxVal(height(x->left), height(x->right)) + 1;
    y->height = maxVal(height(y->left), height(y->right)) + 1;

    return y;
}

// BST insert + AVL balancing
Node* insertNode(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // duplicates not allowed

    node->height = 1 + maxVal(height(node->left), height(node->right));
    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Smallest node finder
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// BST delete + AVL balancing
Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp;
            if (root->left != nullptr)
                temp = root->left;
            else
                temp = root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + maxVal(height(root->left), height(root->right));
    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search
bool searchNode(Node* root, int key) {
    if (root == nullptr) return false;
    if (root->key == key) return true;
    if (key < root->key) return searchNode(root->left, key);
    return searchNode(root->right, key);
}

// Traversals
void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

void preOrder(Node* root) {
    if (root == nullptr) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->key << " ";
}

// Pretty print tree (no strings used)
void printTree(Node* root, int space = 0) {
    if (root == nullptr) return;

    space += 6;
    printTree(root->right, space);

    cout << endl;
    for (int i = 6; i < space; i++)
        cout << " ";
    cout << root->key << "(" << root->height << ")\n";

    printTree(root->left, space);
}

// ================= MAIN =================
int main() {
    Node* root = nullptr;

    int arr[] = {20, 4, 15, 70, 50, 100, 80, 90, 85};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Inserting values:\n";
    for (int i = 0; i < n; i++) {
        root = insertNode(root, arr[i]);
    }

    cout << "\nInOrder: ";
    inOrder(root);

    cout << "\nPreOrder: ";
    preOrder(root);

    cout << "\nPostOrder: ";
    postOrder(root);

    cout << "\n\nAVL Tree Structure:\n";
    printTree(root);

    cout << "\nDeleting 70\n";
    root = deleteNode(root, 70);
    printTree(root);

    cout << "\nDeleting 100\n";
    root = deleteNode(root, 100);
    printTree(root);

    cout << "\nSearch 85: ";
    if (searchNode(root, 85))
        cout << "Found\n";
    else
        cout << "Not Found\n";

    cout << "Search 70: ";
    if (searchNode(root, 70))
        cout << "Found\n";
    else
        cout << "Not Found\n";

    return 0;
}


class Course_Name{
    string course_code;
    string short_form;
    string full_form;
    Course_Name* next;
    public:
	string name; // NAME SO THAT WE CAN MAKE THREE DIFF BST'S FOR COURSE NAME, FULL FORM AND SHORT FORM BUT FOR THIS WE NEED TO USE TRIGGERS OR FLAGS WHCIH WILL BE IMPLEMENTED SOON IN BST TREE
    Course_Name():next(nullptr){}
	Course_Name(string a, string b, string c):course_code(a),short_form(b), full_form(c), next(nullptr){
		name=course_code+" "+short_form+" "+full_form;
	}
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
