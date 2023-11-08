#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <windows.h>
#include <sstream>

using namespace std;

class Hotel {
public:
    struct RNode {
        string roomtype;
        int price;
        int filled;
        int minRoomNo;
        int maxRoomNo;
        RNode* next = NULL;
    };

    struct Node {
        string name;
        string address;
        string pno;
        int roomno;
        string roomtype;
        int checkindate[3];
        int days;
        int totalprice;
        Node* next = NULL;
    };

public:
    Node* tail = NULL;
    Node* head = NULL;
    RNode* Rhead = NULL;
    RNode* Rtail = NULL;

    void insert();
    void displayRoomRanges();
    // ... other method declarations ...

    void update();
    void searchbyroom();
    void searchbycategory();
    void deletes();
    void sort1();
    void sort2();
    void display();
    void fillroomcategory(string a,int p,int f,int min,int max);
    void roomcat_data();
    void bill();
    //void displayRoomRanges();
};
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//--------------------------------------------------------------------------------------------------------------------------
void printtfu() {
  setColor(6);
    cout << " _______  __   __  _______  __    _  ___   _  _______    _______  _______  ______      __   __  _______  ___   __    _  _______ \n";
    cout << "|       ||  | |  ||   _   ||  |  | ||   | | ||       |  |       ||       ||    _ |    |  | |  ||       ||   | |  |  | | |      |\n";
    cout << "|_     _||  |_|  ||  |_|  ||   |_| ||   |_| ||  _____|  |    ___||   _   ||   | ||    |  | |  || ______||   | |   |_| | |    __|\n";
    cout << "  |   |  |       ||       ||       ||      | | |_____   |  |___  |  | |  ||   |_||_   |  |_|  || |_____ |   | |       | |   |  __ \n";
    cout << "  |   |  |       ||       ||  _    ||     |_ |_____  |  |    __| |  |_|  ||    __  |  |       ||_____  ||   | |  _    | |   | |  |\n";
    cout << "  |   |  |   _   ||   _   || | |   ||    _  | _____| |  |   |    |       ||   |  | |  |       | _____| ||   | | | |   | |   |_|  |\n";
    cout << "  |___|  |__| |__||__| |__||_|  |__||___| |_||_______|  |___|    |_______||___|  |_|  |_______||_______||___| |_|  |__| |________|\n";
}
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
void Hotel::fillroomcategory(string rtype, int p,int minRoomNo, int maxRoomNo,int filled=0){
    RNode* r=new RNode;
    r->filled=filled;
    r->roomtype=rtype;
    r->price=p;
    r->minRoomNo=minRoomNo;
    r->maxRoomNo=maxRoomNo;
    if(Rhead==NULL){
        Rhead=r;
        return;
    }
    else{
        RNode *r1=Rhead;
        while(r1->next!=NULL){
            r1=r1->next;
        }
        r1->next=r;
    }
}
//--------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
void Hotel::roomcat_data(){
    RNode *curr=Rhead;
    while(curr!=NULL){
        cout<<"ROOM-TYPE: "<<curr->roomtype<<"      "<<"PRICE PER DAY: "<<curr->price<<"       "<<"ROOMS FILLED: "<<curr->filled<<endl;
        curr=curr->next;
    }
    cout<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Hotel::insert() {
    while (true) {
        Node* newnode = new Node;
        
        cout << "ENTER CUSTOMER DETAILS:" << endl;
        cout << "ENTER GUEST NAME: ";
        cin.ignore();
        getline(cin, newnode->name);

        cout << "ENTER GUEST ADDRESS: ";
        getline(cin, newnode->address);

        // Phone number input validation
        while(true){
		cout<<"ENTER GUEST CONTACT NUMBER (10 digit) : ";
		string tempPno;  
		cin>> tempPno;
		 bool validNumber = true;

    if (tempPno.length() != 10) {
        validNumber = false;
    }
    for (int i = 0; i < tempPno.length(); i++) {
            if (tempPno[i] < '0' || tempPno[i] > '9') {
                validNumber = false;
                break;
            }
        }
	  if (!validNumber) {
        cout << "Invalid phone number entered! Please provide a 10-digit numeric value." << endl;
    } else {
        newnode->pno = tempPno; // Store the validated number
        break;
    }
		}


        // Date input validation
		while (true) {
    int x, y, z;
    cout << "ENTER DATE OF Check-In (DD MM YYYY): ";
    cin >> x >> y >> z;

    if ((x > 0 && x <= 31) && (y > 0 && y < 13) && (z >= 2023)) {
        newnode->checkindate[0] = x;
        newnode->checkindate[1] = y;
        newnode->checkindate[2] = z;
        break;
    } else {
        cout << "INVALID DATE ENTERED!" << endl;
        cin.clear();
        // clear the buffer
        while (cin.get() != '\n') continue;
    }
}
		bool validInput = false;
while (!validInput) {
    cout << "ENTER NO. OF DAYS OF STAY: ";
    string input;
    cin.ignore();
    getline(cin, input);

    bool isNumber = true;
    for (int i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])) {
            isNumber = false;
            break;
        }
    }

    if (isNumber) {
        // If the input contains only digits, convert it to an integer
        stringstream convert(input);
        if (convert >> newnode->days) {
            validInput = true;
            break;
        } else {
            cout << "INVALID INPUT! TRY AGAIN" << endl;
        }
    }
}

        cout << "ENTER ROOM DETAILS:" << endl;
      
		    bool validRoomType = false;
        int selectedOption = 0;

        while (!validRoomType) {
            int option = 1;
            cout<<"1.DELUXE SUITE "<<" "<<"2.FAMILY SUITE "<<" "<<"3.OCEAN VIEW SUITE "<<" "<<"4.PENTHOUSE SUITE "<<" "<<"5.STANDARD AC SUITE "<<" "<<"6.STANDARD NON AC SUITE"<<endl;
            cout << "Choose Room Type: " << endl;
            RNode* tempRNode = Rhead;

            while (tempRNode != NULL) {
                cout << "Option " << option << ": " << tempRNode->roomtype << endl;
                tempRNode = tempRNode->next;
                option++;
            }

            cout << "Enter option: ";
            cin >> selectedOption;

            int counter = 1;
            tempRNode = Rhead;

            while (tempRNode != NULL) {
                if (counter == selectedOption) {
                    tempRNode->filled++;
                    newnode->roomtype = tempRNode->roomtype;
                    validRoomType = true;
                    break;
                }
			  tempRNode = tempRNode->next;
                counter++;
            }

            if (!validRoomType) {
                cout << "INVALID ROOM TYPE ENTERED!" << endl;
            }
        }


			RNode* tempRNode = Rhead;
			while (tempRNode != NULL) {
   				 cout << left << setw(15) << tempRNode->roomtype << " - Room No. " << tempRNode->minRoomNo << " to " << tempRNode->maxRoomNo << endl;
    			 tempRNode = tempRNode->next;
				}

			
			bool roomOccupied = false;
			int rn;

			while (true) {
    			cout << "ALLOT ROOM NUMBER: ";
    			cin >> rn;
    			roomOccupied = false;

    			// Check if the entered room number is outside the room range or already occupied
    			RNode* tempRNode = Rhead;
   				while (tempRNode != NULL) {
        		if (tempRNode->roomtype == newnode->roomtype) {
            		if (rn < tempRNode->minRoomNo || rn > tempRNode->maxRoomNo) {
                		roomOccupied = true;
                		cout << "ROOM NUMBER NOT AVAILABLE FOR SELECTED ROOM TYPE. TRY AGAIN..." << endl;
                		break;
            }
        }
        tempRNode = tempRNode->next;
    }

    if (!roomOccupied) {
        // Check if the room number is already allotted to another guest
        Node* temp = head;
        bool roomAlreadyAllotted = false;
        while (temp != NULL) {
            if (temp->roomno == rn) {
                roomAlreadyAllotted = true;
                break;
            }
            temp = temp->next;
        }

        if (roomAlreadyAllotted) {
            roomOccupied = true;
            cout << "ROOM NUMBER ALREADY OCCUPIED. TRY AGAIN..." << endl;
        } else {
            newnode->roomno = rn;
            cout << "ROOM NUMBER " << rn << " ALLOTTED SUCCESSFULLY." << endl;
            break;
        }
    }
}

	
       

        // Insert new node into the list
        if (head == NULL) {
            head = newnode;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newnode;
        }

        cout << endl << "1. PRESS 1 FOR ANOTHER CHECK-IN "<<endl;
		cout<<endl<<"2. ANY NUMBER (2-9) TO RETURN TO MAIN MENU: ";
        string k;
        cin.ignore();
        getline(cin,k);
        if (k != "1") {
            break;
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------
void Hotel::deletes() {
    cout << "ENTER ROOM NO. FOR CHECK OUT: ";
    int roomNumber;
    cin >> roomNumber;

    Node* current = head;
    Node* previous = NULL;
    string roomTypeToDelete;

    bool roomFound = false;

    // Check if the head is to be deleted
    if (current != NULL && current->roomno == roomNumber) {
        roomTypeToDelete = current->roomtype;
        head = current->next;
        delete current;
        roomFound = true;
    } else {
        // Search for the room number in the list
        while (current != NULL) {
            if (current->roomno == roomNumber) {
                roomTypeToDelete = current->roomtype;
                previous->next = current->next;
                delete current;
                roomFound = true;
                break;
            }
            previous = current;
            current = current->next;
        }
    }

    if (!roomFound) {
        cout << "ROOM NOT FOUND OR ALREADY CHECKED OUT." << endl;
        return;
    }

    // Decrement filled rooms for the respective room type in the RNode list
    RNode* r = Rhead;
    while (r != NULL) {
        if (r->roomtype == roomTypeToDelete) {
            r->filled--;
            break;
        }
        r = r->next;
    }
    cout<<"ROOM CHECK OUT. SUCCESS"<<endl;
}

//----------------------------------------------------------------------------------------------------------------------------
void Hotel::searchbyroom(){
        int y;
        cout<<"ENTER THE ROOM NO. : ";
        cin>>y;
        Node*we=head;
        while(we!=NULL){
            if(we->roomno==y){
            	setColor(8);
            	cout << "_______________________________________________________________________________________________________________________________" << endl;
				cout << "ROOM NO.\tGUEST NAME\tROOM TYPE\tCONTACT NUMBER\tCHECK-IN-DATE\tNO-OF-DAYS-OF-STAY\tADDRESS" << endl;
				cout << "_______________________________________________________________________________________________________________________________" << endl;

				cout << we->roomno << "\t\t" << we->name << "\t\t" << we->roomtype << "\t\t" << we->pno << "\t\t"
    			 << we->checkindate[0] << "-" << we->checkindate[1] << "-" << we->checkindate[2] << "\t\t"
     			<< we->days << "\t\t" << we->address << endl;

				cout << "_______________________________________________________________________________________________________________________________" << endl;

				 break;
            }
            we=we->next;
        }setColor(7);
        if(we==NULL){
            cout<<"NO INFO. FOUND IN THE RECORDS !"<<endl;
        }
        return;
	}

//----------------------------------------------------------------------------------------------------------------------------
void Hotel::searchbycategory() {
    string h;
    cin.ignore();
    cout << "ENTER ROOM CATEGORY: ";
    getline(cin, h);
    Node* we = head;
    int count = 0;
    while (we != NULL) {
        if (we->roomtype == h) {
            count++;
          setColor(8);  
          cout << "_______________________________________________________________________________________________________________________________________________________" << endl;
				cout << "ROOM NO.\tGUEST NAME\tROOM TYPE\tCONTACT NUMBER\tCHECK-IN-DATE\tNO-OF-DAYS-OF-STAY\tADDRESS" << endl;
				cout << "__________________________________________________________________________________________________________________________________" << endl;

				cout << we->roomno << "\t\t" << we->name << "\t\t" << we->roomtype << "\t\t" << we->pno << "\t\t"
    			 << we->checkindate[0] << "-" << we->checkindate[1] << "-" << we->checkindate[2] << "\t\t"
     			<< we->days << "\t\t" << we->address << endl;

				cout << "_______________________________________________________________________________________________________________________________" << endl;
			 }
        we = we->next;
    }setColor(7);
    if (count == 0) {
        cout << "NO ROOM OF THIS CATEGORY IS FILLED." << endl;
    }
    return;
}


//----------------------------------------------------------------------------------------------------------------------------
// Function to display guest details
void Hotel::display() {
    Node* currentnode = head;
    if (currentnode == NULL) {
        cout << "RECORDS SECTION IS EMPTY." << endl;
        return;
    }
	cout<<"---------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "ROOM NO.   GUEST NAME      ROOM TYPE         CONTACT NUMBER    CHECK-IN-DATE   NO-OF-DAYS-OF-STAY   ADDRESS" << endl;
	cout<<"---------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    while (currentnode != NULL) {
        cout << currentnode->roomno << "         " << currentnode->name << "          " << currentnode->roomtype << "          "
             << currentnode->pno << "        " << currentnode->checkindate[0] << "-" << currentnode->checkindate[1] << "-"
             << currentnode->checkindate[2] << "        " << currentnode->days << "                " << currentnode->address << endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        currentnode = currentnode->next;
    }
}



//-----------------------------------------------------------------------------------------------------------------------------
void restaurant() {
    std::string menuItems[] = {
        "Regular Tea", "Masala Tea", "Coffee", "Cold Drink", "Bread Butter",
        "Bread Jam", "Veg. Sandwich", "Veg. Toast Sandwich", "Cheese Toast Sandwich",
        "Grilled Sandwich", "Tomato Soup", "Hot & Sour", "Veg. Noodle Soup", "Sweet Corn",
        "Veg. Munchow", "Shahi Paneer", "Kadai Paneer", "Handi Paneer", "Palak Paneer",
        "Chilli Paneer", "Matar Mushroom", "Mix Veg", "Jeera Aloo", "Malai Kofta", "Aloo Matar",
        "Dal Fry", "Dal Makhani", "Dal Tadka", "Plain Roti", "Butter Roti",
        "Tandoori Roti", "Butter Naan", "Plain Rice", "Jeera Rice", "Veg Pulao", "Peas Pulao",
        "Plain Dosa", "Onion Dosa", "Masala Dosa", "Paneer Dosa", "Rice Idli", "Sambhar Vada",
        "Vanilla Ice Cream", "Strawberry Ice Cream", "Pineapple Ice Cream", "Butter Scotch Ice Cream"
    };

    double itemPrices[] = {
        20.00, 25.00, 25.00, 25.00, 30.00,
        30.00, 50.00, 50.00, 70.00, 70.00,
        110.00, 110.00, 110.00, 110.00, 110.00,
        110.00, 110.00, 120.00, 120.00, 140.00,
        140.00, 140.00, 140.00, 140.00, 140.00,
        140.00, 150.00, 150.00, 150.00, 15.00,
        15.00, 20.00, 20.00, 90.00, 90.00,
        110.00, 110.00, 110.00, 110.00, 110.00,
        100.00, 110.00, 130.00, 130.00, 130.00,
        140.00, 60.00, 60.00, 60.00, 60.00
    };

    // Example to print the menu items and their prices
    for (int i = 0; i < sizeof(menuItems) / sizeof(menuItems[0]); ++i) {
        std::cout << i + 1 << ". " << menuItems[i] << " - " << itemPrices[i] << std::endl;
    }
}
//----------------------------------------------------------------------------------------------------------------------------
void Hotel::sort1() {
    Node* start = head;
    Node* current = start;

    while (current) {
        if (current->days <= 1) {
            current = current->next;
            continue;
        }

        Node* temp = current;
        Node* minNode = current;
        int minRoomNo = current->roomno;

        while (temp) {
            if (minRoomNo > temp->roomno && temp->days > 1) {
                minRoomNo = temp->roomno;
                minNode = temp;
            }
            temp = temp->next;
        }

        // Swapping all necessary values
        string tempName = current->name;
        string tempAddress = current->address;
        string tempPno = current->pno;
        string tempRoomType = current->roomtype;
        int tempRoomNo = current->roomno;
        int tempCheckInDate[3];
        tempCheckInDate[0] = current->checkindate[0];
        tempCheckInDate[1] = current->checkindate[1];
        tempCheckInDate[2] = current->checkindate[2];
        int tempDays = current->days;

        current->name = minNode->name;
        current->address = minNode->address;
        current->pno = minNode->pno;
        current->roomtype = minNode->roomtype;
        current->roomno = minNode->roomno;
        current->checkindate[0] = minNode->checkindate[0];
        current->checkindate[1] = minNode->checkindate[1];
        current->checkindate[2] = minNode->checkindate[2];
        current->days = minNode->days;

        minNode->name = tempName;
        minNode->address = tempAddress;
        minNode->pno = tempPno;
        minNode->roomtype = tempRoomType;
        minNode->roomno = tempRoomNo;
        minNode->checkindate[0] = tempCheckInDate[0];
        minNode->checkindate[1] = tempCheckInDate[1];
        minNode->checkindate[2] = tempCheckInDate[2];
        minNode->days = tempDays;

        current = current->next;
    }

    cout << "Sorting by room numbers completed successfully." << endl;
}

//----------------------------------------------------------------------------------------------------------------------------
void Hotel::sort2() {
    Node* start = head;
    Node* current = start;

    while (current) {
        if (current->days <= 1) {
            current = current->next;
            continue;
        }

        Node* temp = current;
        Node* minNode = current;
        int minDays = current->days;

        while (temp) {
            if (minDays > temp->days && temp->days > 1) {
                minDays = temp->days;
                minNode = temp;
            }
            temp = temp->next;
        }

        // Swapping all necessary values
        string tempName = current->name;
        string tempAddress = current->address;
        string tempPno = current->pno;
        string tempRoomType = current->roomtype;
        int tempRoomNo = current->roomno;
        int tempCheckInDate[3];
        tempCheckInDate[0] = current->checkindate[0];
        tempCheckInDate[1] = current->checkindate[1];
        tempCheckInDate[2] = current->checkindate[2];
        int tempDays = current->days;

        current->name = minNode->name;
        current->address = minNode->address;
        current->pno = minNode->pno;
        current->roomtype = minNode->roomtype;
        current->roomno = minNode->roomno;
        current->checkindate[0] = minNode->checkindate[0];
        current->checkindate[1] = minNode->checkindate[1];
        current->checkindate[2] = minNode->checkindate[2];
        current->days = minNode->days;

        minNode->name = tempName;
        minNode->address = tempAddress;
        minNode->pno = tempPno;
        minNode->roomtype = tempRoomType;
        minNode->roomno = tempRoomNo;
        minNode->checkindate[0] = tempCheckInDate[0];
        minNode->checkindate[1] = tempCheckInDate[1];
        minNode->checkindate[2] = tempCheckInDate[2];
        minNode->days = tempDays;

        current = current->next;
    }

    cout << "Sorting by number of days of stay completed successfully." << endl;
}

//-----------------------------------------------------------------------------------------------------------------------------
void Hotel::update() {
    cout << "ENTER CUSTOMER NAME WHOSE ROOM YOU WANT TO UPDATE: ";
    string guestName;
    cin.ignore(); // Consume the newline character
    getline(cin, guestName);

    Node* current = head;
    bool guestFound = false;

    // Search for the guest in the list
    while (current != NULL) {
        if (current->name == guestName) {
            guestFound = true;
            break;
        }
        current = current->next;
    }

    if (!guestFound) {
        cout << "GUEST NOT FOUND IN THE RECORDS!" << endl;
        return;
    }

    cout << "SELECT WHAT YOU WANT TO UPDATE:" << endl;
    cout << "1. Change Room Number" << endl;
    cout << "2. Change Room Type" << endl;
    cout << "3. Change Number of Days of Stay" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: {
            // Change Room Number
            int newRoomNo;
            bool validRoom = false;

            while (!validRoom) {
                cout << "Enter new Room Number: ";
                cin >> newRoomNo;

                // Display room number ranges for each room type
            RNode* tempRNode1 = Rhead;
			while (tempRNode1 != NULL) {
   				 cout << left << setw(15) << tempRNode1->roomtype << " - Room No. " << tempRNode1->minRoomNo << " to " << tempRNode1->maxRoomNo << endl;
    			 tempRNode1 = tempRNode1->next;
				}


                // Check if the new room number is within the room type range and available
                RNode* tempRNode = Rhead;
                validRoom = false;

                while (tempRNode != NULL) {
                    if (current->roomtype == tempRNode->roomtype) {
                        if (newRoomNo >= tempRNode->minRoomNo && newRoomNo <= tempRNode->maxRoomNo) {
                            validRoom = true;
                            break;
                        }
                    }
                    tempRNode = tempRNode->next;
                }

                if (!validRoom) {
                    cout << "INVALID ROOM NUMBER! Please select from the available room numbers." << endl;
                }

                // Check if the room is already occupied
                Node* temp = head;
                bool roomOccupied = false;

                while (temp != NULL) {
                    if (temp->roomno == newRoomNo) {
                        roomOccupied = true;
                        cout << "ROOM ALREADY OCCUPIED! Please select a different room number." << endl;
                        break;
                    }
                    temp = temp->next;
                }

                if (!roomOccupied && validRoom) {
                    // Room is available within the specified range, update the room number
                    current->roomno = newRoomNo;
                    cout << "ROOM NUMBER UPDATED SUCCESSFULLY!" << endl;
                }
            }
            break;
        }
        case 2: {
            // Change Room Type
            string newRoomType;
            cout << "Enter new Room Type: ";
            cin.ignore(); // Consume the newline character
            getline(cin, newRoomType);

            // Decrement the count of the previous room type in RNode
            RNode* r1 = Rhead;
            while (r1 != NULL) {
                if (r1->roomtype == current->roomtype) {
                    r1->filled--;
                    break;
                }
                r1 = r1->next;
            }

            // Update the guest's room type and increment the count in RNode
            current->roomtype = newRoomType;
            r1 = Rhead;
            while (r1 != NULL) {
                if (r1->roomtype == newRoomType) {
                    r1->filled++;
                    break;
                }
                r1 = r1->next;
            }

            cout << "ROOM TYPE UPDATED SUCCESSFULLY!" << endl;
            break;
        }
        case 3: {
            // Change Number of Days of Stay
            int newStayDays;
            cout << "Enter new Number of Days of Stay: ";
            cin >> newStayDays;
            current->days = newStayDays;
            cout << "NUMBER OF DAYS OF STAY UPDATED SUCCESSFULLY!" << endl;
            break;
        }
        default:
            cout << "INVALID CHOICE!" << endl;
            break;
    }
}



//-----------------------------------------------------------------------------------------------------------------------------
void Hotel::bill() {
    cout << "ENTER CUSTOMER NAME FOR BILL GENERATION: ";
    string guestName;
    cin.ignore(); // Consume the newline character
    getline(cin, guestName);

    Node* current = head;
    bool guestFound = false;

    while (current != NULL) {
        if (current->name == guestName) {
            guestFound = true;
            break;
        }
        current = current->next;
    }

    if (!guestFound) {
        cout << "GUEST NOT FOUND IN THE RECORDS!" << endl;
        return;
    }

    // Calculate the total bill based on room price and number of days of stay
    RNode* roomDetails = Rhead;
    int totalBill = 0;

    while (roomDetails != NULL) {
        if (roomDetails->roomtype == current->roomtype) {
            totalBill = current->days * roomDetails->price;
            break;
        }
        roomDetails = roomDetails->next;
    }
 std::cout << "_______________________________________________________________________________________________________________________________" << std::endl;
    std::cout << "ROOM NO.\tGUEST NAME\t\tROOM TYPE\t\tCONTACT NUMBER\t\tCHECK-IN-DATE\t\tNO-OF-DAYS-OF-STAY\tADDRESS" << std::endl;
    std::cout << "_______________________________________________________________________________________________________________________________" << std::endl;
    std::cout << current->roomno << "\t\t" << current->name << "\t\t\t" << current->roomtype << "\t\t\t" << current->pno
              << "\t\t" << current->checkindate[0] << "-" << current->checkindate[1] << "-" << current->checkindate[2] << "\t\t" << current->days
              << "\t\t\t" << current->address << std::endl;
    std::cout << "_______________________________________________________________________________________________________________________________" << std::endl;
    std::cout << "TOTAL BILL AMOUNT: " << totalBill << std::endl;
    
}

//-----------------------------------------------------------------------------------------------------------------------------
void printhms() {
    setColor(5);
    cout << " __  __        __    __        ______    " << endl;
    cout << "/\\ \\_\\ \\      /\\ \"-.\\  \\      /\\  ___\\   " << endl;
    cout << "\\ \\  __ \\     \\ \\ \\-./\\ \\     \\ \\___  \\  " << endl;
    cout << " \\ \\_\\ \\_\\     \\ \\_\\ \\ \\_\\     \\/\\_____\\ " << endl;
    cout << "  \\/_/\\/_/      \\/_/  \\/_/      \\/_____/ " << endl;
	cout<<  "												"<<endl;
	cout<<endl;
}
//-----------------------------------------------------------------------------------------------------------------------------
int main() {
    Hotel a;
    //filling the hotel data.
    a.fillroomcategory("DELUXE SUITE",6000,1,100);
    a.fillroomcategory("FAMILY SUITE",7000,101,200);
    a.fillroomcategory("OCEAN VIEW SUITE",7500,201,300);
    a.fillroomcategory("PENTHOUSE SUITE",10000,301,400);
    a.fillroomcategory("STANDARD AC",4000,401,500);
    a.fillroomcategory("STANDARD NON-AC",3500,501,600);
while(true){

    	system("cls");
    	printhms();
        string k;
        string id, password;

       setColor(2); cout << "ENTER USER-ID FOR LOGIN: ";
         cin>> id;
        cin.ignore();

        cout <<endl<< "ENTER SYSTEM PASSWORD: ";
         cin >> password;

        if (id != "manager" || password != "123@") {
           setColor(4);
		   cout << "WRONG USER-ID OR PASSWORD..!     "<<endl;
            cout <<endl<< "PRESS ANY NUMBER TO TRY AGAIN (2 - 9): "<<endl;
            cout <<endl<< "PRESS (1) FOR EXIT :"<<endl;
            cin.ignore();
            getline(cin, k);
            if (k == "1") {
                break;
            }
        }  else {
            while (true) {
                system("cls");
                setColor(11);
				cout << "-------------------------------------------------------------" << endl;
				cout << "         WELCOME  TO  HOTEL MANAGEMENT  SYSTEM          " << endl;
				cout << "-------------------------------------------------------------" << endl << endl;

				setColor(7);
				cout << "MAIN MENU :" << endl;
				setColor(7);
				cout << "Task 1 --> ";
				setColor(6);
				cout << "BOOK A HOTEL ROOM (ROOM CHECK IN)!" << endl;

				setColor(7);
				cout << "Task 2 --> ";
				setColor(6);
				cout << "ROOM CHECK OUT !" << endl;

				setColor(7);
				cout << "Task 3 --> ";
				setColor(6);
				cout << "DISPLAY HOTEL'S GUEST LIST !" << endl;

				setColor(7);
				cout << "Task 4 --> ";
				setColor(6);
				cout << "SEARCH LOG : " << endl;

				setColor(7);
				cout << "Task 5 --> ";
				setColor(6);
				cout << "SORT THE DATABASE :" << endl;

				setColor(7);
				cout << "Task 6 --> ";
				setColor(6);
				cout << "UPDATE CUSTOMER INFO: " << endl;

				setColor(7);
				cout << "Task 7 --> ";
				setColor(6);
				cout << "VIEW ROOMS CATRGORICAL DATA: " << endl;

				setColor(7);
				cout << "Task 8 --> ";
				setColor(6);
				cout << "VIEW RESTAURANT MENU:" << endl;

				setColor(7);
				cout << "Task 9 --> ";
				setColor(6);
				cout << "GENERATE BILL: " << endl;

				setColor(7);
				cout << "Task 10-->";
				setColor(6);
				cout << "EXIT : "<<endl;

				setColor(5);
				cout << "ENTER TASK NO. TO PERFORM: ";


				setColor(14);
                int choice;
                cin >> choice;

                switch (choice) {
                    // Rest of your switch cases go here

    case 1:
   	 {
   	 	a.insert();
   	 	cout<<"DIRECTING TO MAIN MENU..."<<endl;
   	 	break;
   	 }
   	case 2:
   	    a.deletes();
   		break;
   	case 3:
   		cout<<"SURE HERE'S THE HOTEL GUEST LIST "<<endl<<endl;
   		a.display();
		break;
   	case 4:
        while(true){
   	        system("cls");
   		   setColor(6); cout<<" SEARCH OPTIONS:"<<endl;
   		    cout<<"1. SEARCH BY ROOM NO."<<endl;
   		    cout<<endl<<"2. SEARCH BY ROOM CATEGORY."<<endl;
   		    cout<<endl<<"3. PRESS 0 FOR MAIN MENU ."<<endl;
   		   setColor(14); int r; cin>>r;
   		    if(r==1){
   		        cout<<"SEARCH  BAR :"<<endl;
   		        a.searchbyroom();
   		    }
            if(r==2){
		        cout<<"SEARCH BAR :"<<endl;
		        a.searchbycategory();
            }
            break;
	    }
   		break;
    case 5:
       setColor(6); cout << "SORTING THE DATABASE :" << endl;
        cout << "1. SORTING BY ROOM NOS. " << endl;
        cout << "2. SORTING BY NO OF DAYS OF STAY. " << endl;
        int e;
        cin >> e;
        if (e == 1) {
            a.sort1();
            break;
        }
        else if (e == 2) {
            a.sort2();
            break;
        }
        else {
            cout << "INVALID CHOICE!" << endl;
        }
        break;

   	case 6:
   		cout<<"UPDATE ROOM INFO. :"<<endl;

		a.update();
		break;
	case 7:
	    cout<<"--------------------------------------------------------------------------------------------"<<endl;
	    a.roomcat_data();
	    cout<<"--------------------------------------------------------------------------------------------"<<endl;
	    break;
	case 8:
		restaurant();
		break;
	case 9:
		a.bill();
		break;
	case 10:
   		cout<<" THANKS FOR USING THE SYSTEM "<<endl;
   		printtfu();
   		exit(0);
   	default:
   		cout<<"PLEASE CHOOSE THE APPROPRIATE OPTION !"<<endl;
   		break;
   }
    cin.ignore(); // Consume the newline character
        cout << "Press Enter to continue...";
        cin.get();
		} // Wait for Enter key to be pressed
}
}
}


