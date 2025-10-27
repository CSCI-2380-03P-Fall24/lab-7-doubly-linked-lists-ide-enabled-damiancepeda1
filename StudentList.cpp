	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
    tail = nullptr;
    numStudents = 0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {

		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		Node* newNode = new Node{s, nullptr, nullptr};

    if (!head) { // list is empty
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    numStudents++;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		 Node* newNode = new Node{s, nullptr, nullptr};

    if (!tail) { // list is empty
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    numStudents++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		  Node* current = head;
    if (!current) {
        cout << "List is empty.\n";
        return;
    }

    while (current) {
        cout << current->data.getName() << endl;
        current = current->next;
    }
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if (!tail) {
        cout << "Error: list is empty.\n";
        return;
    }

    Node* temp = tail;
    if (head == tail) { 
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    numStudents--;
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		 if (!head) {
        cout << "Error: list is empty.\n";
        return;
    }

    Node* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }

    delete temp;
    numStudents--;
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		if (index <= 0) {
        addFront(s);
        return;
    }

    if (index >= numStudents) {
        cout << "Index out of range — inserting at back.\n";
        addBack(s);
        return;
    }

    Node* newNode = new Node{s, nullptr, nullptr};
    Node* current = head;

    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;

    numStudents++;
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		  Node* current = head;
    while (current) {
        if (current->data.getId() == idNum) {
            return current->data;
        }
        current = current->next;
    }

    cout << "No student found with ID " << idNum << endl;
    Student dummy;
    return dummy;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		if (!head) {
        cout << "List is empty.\n";
        return;
    }

    Node* current = head;
    while (current && current->data.getId() != idNum) {
        current = current->next;
    }

    if (!current) {
        cout << "No student found with ID " << idNum << endl;
        return;
    }

    // Case 1: removing head
    if (current == head) {
        popFront();
        return;
    }
    // Case 2: removing tail
    if (current == tail) {
        popBack();
        return;
    }

    // Case 3: middle node
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    numStudents--;
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		  Node* current = head;
    while (current) {
        if (current->data.getId() == idNum) {
            current->data.setGPA(newGPA);
            cout << "Updated GPA for student ID " << idNum << " to " << newGPA << endl;
            return;
        }
        current = current->next;
    }

    cout << "No student found with ID " << idNum << endl;
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		 if (!otherList.head) {
        cout << "Other list is empty. Nothing to merge.\n";
        return;
    }

    if (!head) {
        // this list is empty, just take the other list
        head = otherList.head;
        tail = otherList.tail;
    } else {
        // link the two lists
        tail->next = otherList.head;
        otherList.head->prev = tail;
        tail = otherList.tail;
    }

    numStudents += otherList.numStudents;

    // empty the other list
    otherList.head = nullptr;
    otherList.tail = nullptr;
    otherList.numStudents = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		 StudentList honorList;

    Node* current = head;
    while (current) {
        if (current->data.getGPA() >= minGPA) {
            honorList.addBack(current->data);
        }
        current = current->next;
    }

    return honorList;
	}

	//remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold) {
		if (!head) {
        cout << "List is empty.\n";
        return;
    }

    Node* current = head;
    while (current) {
        Node* nextNode = current->next;

        if (current->data.getGPA() < threshold) {
            // removing head
            if (current == head) {
                popFront();
            }
            // removing tail
            else if (current == tail) {
                popBack();
            }
            // removing middle
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                numStudents--;
            }
        }

        current = nextNode;
    }
	}
