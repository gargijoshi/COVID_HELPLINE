#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
using namespace std;

void changeColor(int desiredColor){ 						/*To change the text color */
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor); 
} 

class Covid_Testing {							/*Acts as a common class for People, Zones, Hospital*/
	string sample_collection_date, report_release_date = "Pending";
	string lname, fname, mname, contact_no, symptoms, address, gender, Detection;
	int bedCount, totalPatients;
	string hospName, hospCity, ptName, city;
	int age, data, priority;
	Covid_Testing* next_person, *next;
	
	public:
    	  int report_status=2, sample_id;
    	/*Default Constructor*/  
	Covid_Testing(){
	  next = NULL;
    	}
	
	/*Parameterized Constructor*/
	Covid_Testing(string lname, string fname, string mname, int age, string contact_no, string symptoms, string address, string gender) {
		this->lname = lname;
		this->fname = fname;
		this->mname = mname;
		this->age = age;
		this->contact_no = contact_no;
		this->symptoms = symptoms;
		this->address = address;
		this->gender = gender;
		next_person = NULL;
	}
	
	/*Friend classes*/
	friend class People;
	friend class Zones;
	friend class Hospital;
	string date() {
		//time_t result = time(NULL);
		char str[26];
		//time_t(str, sizeof str, &result);
		return str;
	}
};

/*Vaccination Module*/
class node{
  string aadhar,pan,nm,phn;   
  int age;
  int r;
   node *next;
   public:
     node(string nm,int age,string aadhar,string phn,string pan)   //Node creation
     {
	next=NULL;
	this->nm=nm;
	this->age=age;
	this->aadhar=aadhar;
	this->phn=phn;
	this->pan=pan;
	
    }
     friend class queue;
};

class queue{
 	
  node *newNode, *rear, *temp, *front, *start;
  public:
     queue(){                          //initialize rear,front,start;
       rear = front = start = NULL;
     }
      void enqueue();
     //node* dequeue();
     void confirmList();
     node* accept();
//     void display();
 };

/*Zones Module*/
class Zones{
    Covid_Testing *newNode, *front, *rear, *temp;
    public:
        Zones(){
            front = temp = rear = NULL;
        }
        void enQueue(string, int, int);
        void display();
};

/*Testing Module*/
class People {
public:
	Covid_Testing* head, * temp;
	People() {
		head = temp= NULL;
	}
	void registration(int);
	Covid_Testing* view_report(int);
	void admin();
};


/***********************Hospital Module*********************/
class Hospital{
    Covid_Testing *start, *temp, *newNode;
    public:
        Hospital(){
            start = temp = NULL;
        }
        void addHospital(string, string, int);//, int);
        void removeHospital(string);
        void checkBedAvailability(string);
        void covidHospitals();
        void admitPatient(Covid_Testing*);
        void updateBedCount(string, string);
};

/***********Accepts cities & patient count for classifying under zones***********/
void Zones :: enQueue(string c, int d, int p){
	//system("cls");
    Covid_Testing *prev;
    newNode = new Covid_Testing();
    newNode->city = c;
    newNode->data = d;
    newNode->priority = p;
    newNode->next = NULL;
    if(front == NULL || p<front->priority){
        newNode->next = front;
        front = newNode;
    }
    else{
        temp = front;
        prev = temp;
        while(temp->next != NULL && temp->next->priority <= p)
            temp = temp->next;
        //temp->next = newNode;
        //newNode->next = prev;
        //newNode->next = temp;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

/**************Displays the cities according to zones*****************/
void Zones :: display(){
    system("cls");
    temp = front;
    if(front == NULL)
        cout<<"\nNo data currently available";
    else{
        cout<<"\n\t\t--------------------------Zones---------------------------------\n";
        changeColor(4);
        cout<<"\nRED";
        changeColor(14);			/****Changes the Text Color*****/ 
        cout<<"\t\t\t\tORANGE";
        changeColor(2);
        cout<<"\t\t\t\tGREEN\n";
        changeColor(15);
        while(temp != NULL){
            if(temp->priority == 3){
	changeColor(4); 
	cout<<temp->city<<" : "<<temp->data<<" Patients\n";
             }
            else if(temp->priority == 2){
	changeColor(14); 	
                  cout<<"\t\t\t\t"<<temp->city<<" : "<<temp->data<<" Patients\n";
            }
            else if(temp->priority == 1){
            	changeColor(2); 
	cout<<"\t\t\t\t\t\t\t\t"<<temp->city<<" : "<<temp->data<<" Patients\n";
            }
           changeColor(15);
           temp = temp->next;
        }
    }
}

 /*****Accept the data for vaccine registration******/
node*  queue::accept()                  
{
     string aadhar,pan,nm,phn;
     int age;
     again:
     cout<<"\nENTER YOUT DETAILS:\n";
     cout<<"\nenter your name:";
     cin>>nm;
     cout<<"\nenter age:";
     cin>>age;
     if(age<18){				/***Validates the age****/
    	cout<<"\nNot valid age\n";
    	goto again;
      }
     phone:
     cout<<"\nenter phone num:";
     cin>>phn;
     if(phn.length()!=10){
   	cout<<"\nphone number should required 10 digits";
    	goto phone;
      }
     adhar:
     cout<<"\nenter Aadhar card nmber:";
     cin>>aadhar;
     if(aadhar.length()!=12){
     	cout<<"\nAadhar number should required 12 digits";
     	goto adhar;
     }
    pann:
    cout<<"\nenter PAN card number:";
    cin>>pan;
    if(pan.length()!=10){
     	cout<<"\nPAN card number should required 10 digits";
     	goto pann;
    }
    cout<<"\n----------------------------------------------";
	newNode = new node(nm, age,phn,aadhar,pan);
	newNode->r=rand();
  return newNode;
}

/*********Adds people in registration queue*********/
void queue::enqueue(){           //add elemt into queue
   newNode=accept();           //call accept function
   newNode->next = NULL;        
   if(front == NULL){
     rear = front = newNode;
   }
   else {   
     rear->next = newNode;
     rear = newNode;
   }
   cout<<"\nCongratulations!!! Your registration is confirmed. ";
 // cout<<"\nYou are in waiting queue.\nwait until your registartion is confirmed\n";
 // cout<<"\n----------------------------------------------";
   }


/**********Displays confirm list of people for vaccination*********/   
void queue :: confirmList(){
  node *temp;
   int srNo=1;
   if(front == NULL)
   	cout<<"Empty list!";
   temp = front;
   cout<<"\n----------------------------------------------------------------------------------------------";
    cout<<"\nYour Registration is Confirmed!!\n";
    cout<<"You are getting vaccinated!\n\n";
    cout<<"-----------------------------------------------------------------------------------------------\n";
   cout<<"\nSrNo\tReg No\t\tName\t\tAge\tContact No\tAadhar No\t  PAN no\n";
   cout<<"------------------------------------------------------------------------------------------------\n";
   while(temp!=NULL){
	cout<<srNo<<"\t"<<temp->r<<"\t\t"<<temp->nm<<"\t\t"<<temp->age<<"\t"<<temp->aadhar<<"\t"<<temp->phn<<"\t"<<temp->pan;
	temp = temp->next;
	cout<<"\n";
	srNo++;
   }
   cout<<"\n\n\nYou can download your certificate from this link after vaccination:";
	cout<<"\nhttps://getcertificate.com\n";
	cout<<"\n----------------------------------------------------------------------------------------------";
   cout<<"\n________________________________________________________________________________________________";
  
}	

//Testing Module
/*************************Register for corona test*******************************/
void People::registration(int family_member) {
	Covid_Testing* new_person;
	string lname_, fname_, mname_, contact_, symptoms_, address_, gender_;
	int age_;
	system("cls");
	
	for (int i = 0; i < family_member; i++) {
		cout << "\nFill details of patient " << i + 1;
		cout << "\nEnter name: (lastname firstname middlename): ";
		cin >> lname_ >> fname_ >> mname_;
		cout << "Enter age: ";
		cin >> age_;
		cout << "Enter gender: ";
		cin >> gender_;
		cout << "Enter contact number: ";
		cin >> contact_;
		cout << "Enter symptoms (if no symptoms: type No): ";
		cin >> symptoms_;
		cout << "Enter city: ";
		cin >> address_;
		
		new_person = new Covid_Testing(lname_, fname_, mname_, age_, contact_, symptoms_, address_, gender_);
		new_person->sample_id = rand()%50;
		//new_person->sample_collection_date = new_person->date();
		if (head == NULL) {
			head = new_person;
			head->next_person = NULL;
		}
		else {
			temp = head;
			while (temp->next_person != NULL) {

				temp = temp->next_person;
			}
			temp->next_person = new_person;
			new_person->next_person = NULL;
		}
		cout << "\n--------------------------------------------------------------------------------------------------------";
		cout << "\nDear "<<new_person->fname<<", You are Registered for Covid-19 testing. \nOur Team member will come to your specified address and will collect the sample.";
		cout << "\nYOUR ID IS: " << new_person->sample_id;
		cout << "\n\t\t\tSTAY SAFE! STAY SECURE! WEAR MASK!";
		cout << "\n..........................................................................................................";
	}
}

/*******************************VIEW REPORT********************************/
Covid_Testing* People::view_report(int PatientID) {
	system("cls");
	Covid_Testing* temp1; int flag = 0, s;
	temp = head;
	if (head == NULL) {
		cout << "No reports are there. Please try again later.";
	}
	else {
		for (temp1 = head; temp1 != NULL; temp1 = temp1->next_person)
		{
			if (temp1->report_status == 0)
				temp1->Detection = "NEGATIVE";
			else if (temp1->report_status == 1)
				temp1->Detection = "POSITIVE";
			else
				temp1->Detection = "PENDING";
			if (temp1->sample_id == PatientID) {
				flag = 1;
				s = temp1->report_status;
				cout << "\n----------------------------------------------------------------------------------------------------------";
				cout << "\nPROCESSED AT:";
				cout << "\nThyrocare                                                                                 THYROCARE";
				cout << "\nD - 37 / 1, TTC, MIDC, Turbhe,                                                     The Trust, The Truth";
				cout << "\nNAVI MUMBAI - 400 703                                                              .....................";
				cout << "\n__________________________________________________________________________________________________________";
				cout << "\n	                                      RTPCR TEST REPORTS                                                 ";
				cout << "\n\t                                  MODULAR DIAGNOSTIC LABORATORY ";
				cout << "\n----------------------------------------------------------------------------------------------------------";
				cout << "\nTEST NAME: COVID-19 RT PCR \nREF BY: SELF";
				cout << "\n__________________________________________________________________________________________________________";
				cout << "\n Sample ID: \t\t\t\t\t|" << temp1->sample_id;
				cout << "\n Patient Name:\t\t\t\t\t|" << temp1->lname << " " << temp1->fname << " " << temp1->mname;
				cout << "\n Age\t\t\t\t\t\t|" << temp1->age;
				cout << "\n Gender\t\t\t\t\t\t|" << temp1->gender;
				cout << "\n Contact number\t\t\t\t\t|" << temp1->contact_no;
				cout << "\n Specimen type\t\t\t\t\t|Nasopharyngeal and Oropharyngeal";
				cout << "\n SARS-CoV2\t\t\t\t\t|" << temp1->Detection;
				cout << "\n__________________________________________________________________________________________________________";
				if (temp1->report_status == 1)
					cout << "\n\t\tYOU ARE TESTED " << temp1->Detection << " FOR SARS-CoV2 COVID-19!";
				if (temp1->report_status == 0) 
					cout << "\n\t\tYOU ARE TESTED " << temp1->Detection << " FOR SARS-CoV2 COVID-19!";
				if (temp1->report_status == 2)
					cout << "\n\t\t\t\tYOUR REPORT STATUS IS " << temp1->Detection << " PLEASE TRY AFTER SOME TIME";
				cout << "\n\n Sample Collected On (SCT): " << temp1->sample_collection_date;
				cout << " Report Released On  (RRT) :" << temp1->report_release_date;
				cout << "\n\t\t\t\t\t..................................";
				cout << "\n\t\t\t\t\tSTAY SAFE! STAY SECURE! WEAR MASK!";
			}
		}
		if (flag == 0) {
			cout << "No record Found!";
			return 0;
		}
	}
	    return temp;
}

/**************************ADMIN******************************/
void People::admin() {
	system("cls");
	string pass,ch;
	int detection;
	Covid_Testing* pending_status=NULL;
	cout << "Enter Password: ";
	cin >> pass;
	if (pass == "abcd") {
		if (head == NULL)
			cout << "\nNo testing reports pending to approve!";
		else {
			for (pending_status = head; pending_status != NULL; pending_status = pending_status->next_person)
			{
				if (pending_status->report_status != 1) {
					if (pending_status->report_status != 0) {
						cout << "\nReports of ID  number " << pending_status->sample_id;
						cout << "\nEnter SARS-CoV2 Detection: \n1. Positive \n0. Negative \nEnter status: ";
						cin >> detection;
						switch (detection) {
						case 0: pending_status->report_status = 0;
							//pending_status->report_release_date = pending_status->date();
							break;
						case 1: pending_status->report_status = 1;
							//pending_status->report_release_date = pending_status->date();
							break;
						}
					}
					cout << "Do you want to continue:(y/n)? ";
					cin >> ch;
					if ("n")
						break;
					else
						continue;
				}
				else
					cout << "No approvals are pending";
			}
		}
	}
	else {
		cout << "Password is incorrect. Please try again!";
	}
}

//Hospital Module
/********************Adds Covid hospital in the list************************/
void Hospital :: addHospital(string nm, string ct, int bed){//, int patient){
    system("cls");				/*********Clears the Screen**********/
    newNode = new Covid_Testing();
    newNode->hospName = nm;
    newNode->hospCity = ct;
    newNode->bedCount = bed;
    //newNode->totalPatients = patient;
    newNode->next = NULL;
    
    if(start == NULL)
        start = newNode;
    else{
        temp = start;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
        temp = newNode;
    }
    temp = start;
}

/**********************Removes hospital from the list************************/
void Hospital :: removeHospital(string nm){
	system("cls");
    int flag=0;
    Covid_Testing *prev;
    if(start == NULL)
        cout<<"\nNo hospital is currently added...";
    else{
        temp = start;
        prev = temp;
        while(temp != NULL){
            if(temp->hospName == nm){
                if(temp == start){
                    start = temp->next;
                }
                flag = 1;
                cout<<"\nDeleting hospital...";
                prev->next = temp->next;
                delete(temp);
                break;
            }
            else{
                prev = temp;
                temp = temp->next;
            }
        }
        if(flag == 0)
            cout<<"\nNo hospital found...";
        else
            cout<<"\nHospital deleted...\n";
    }
}

/*******************Checks bed availability of hospitals in particular city**************/
void Hospital :: checkBedAvailability(string ct){
    system("cls");
    int flag=0;
    if(start == NULL)
        cout<<"\nNo information available...";
    else{
        cout<<"\nCurrent statistics of bed availability in :"<<ct<<"\n";
        cout<<"Name\t\t\tCity\t\tBeds Availability\n";
        cout<<"-----------------------------------------------------------------\n";
        temp = start;
        while(temp != NULL){
            if(temp->hospCity == ct){
                cout<<temp->hospName<<"\t\t\t"<<temp->hospCity<<"\t\t"<<temp->bedCount;
                cout<<"\n";
                flag = 1;
            }
            temp = temp->next;
        }
        if(flag == 0)
            cout<<"\nNo record found";
    }
}


/************Displays list of Covid hospitals***************/
void Hospital :: covidHospitals(){
    system("cls");
    if(start == NULL)
        cout<<"No information available...";
    else{
        //cout<<"\nCurrent statistics of bed availability in :"<<ct<<"\n";
        cout<<"\nName\t\t\tCity\t\tBeds Availability\n";
        cout<<"-----------------------------------------------------------------\n";
        temp = start;
        while(temp != NULL){
            cout<<temp->hospName<<"\t\t\t"<<temp->hospCity<<"\t\t"<<temp->bedCount;
            cout<<"\n";
            //flag = 1;
            temp = temp->next;
        }
    }
}

/******************Admit +ve Patient*************************/
void Hospital :: admitPatient(Covid_Testing *p){
    string nm;
    cout<<p->fname;
    cout<<"\nBeds Availability in "<<p->address;
    checkBedAvailability(p->address);
    cout<<"\nEnter Hospital Name: ";
    cin.ignore();
    getline(cin, nm);
    updateBedCount(nm, p->address);
}

/********Update bed count | when patient gets admitted in the hospital************/ 
void Hospital :: updateBedCount(string nm, string ct){
    temp = start;
    while(temp != NULL){
        if(temp->hospName == nm && temp->hospCity == ct){
            break;
        }
        temp = temp->next;
    }
    int bed = temp->bedCount;
    cout<<bed;
    bed = bed-1;
    cout<<bed;
    temp->bedCount = bed--;
    checkBedAvailability(ct);			/*****Display new bed count*****/
}



/*******************Main Menu**************************/
int main() {
	People p;
	Hospital h;
	Zones z;
	int ch, bed, d, pr;
	string nm, ct;
	Covid_Testing *ptr;
	int n,choose, family_members, Patient_id, s;
	char chc;
	do{
	   menu:
	   cout<<"\n\t\t*******************CoVID HELPLINE**********************";
	   cout<<"\n\n";
	   cout<<"\t\t1. Zones\n\t\t2.Hospital\n\t\t3.Testing\n\t\t4.Vaccination\n\n";
	   cout<<"\t\tEnter your choice: ";
	   cin>>ch;
	   switch(ch){
	      case 1: do{
	      	system("cls");
                        	cout<<"\n\t\t----------------------Zones-----------------------";
                        	cout<<"\n\t\tEnter City:";
                        	cin>>ct;
                        	cout<<"\n\t\tEnter No. of Patients: ";
                        	cin>>d;
                        	if(d >= 1000)
                        	    pr = 3;
                        	if(d<1000 && d>=500)
                        	    pr = 2;
                        	else if(d<500)
                        	    pr = 1;
                        	z.enQueue(ct,d,pr);
                        	cout<<"\n\t\tDo you want to continue? Y/N: ";
                        	cin>>chc;
                                 }while(chc!='N' && chc!='n');
                    	z.display();
	              break;
	      case 2: system("cls");
		cout<<"\n\t\t------------------Hospitals-------------------- ";
                    	goto hosp;
                    	break;
            	     case 3: system("cls");
		cout<<"\n\t\t-------------------Testing----------------------";
                  	  	goto again;
                    	break;
                       case 4: system("cls");
		cout<<"\n\t\t-------------------Vaccination---------------------";
            		goto vaccine;
                  	  	break;
   	    case 5: exit(0);
                    	break;
	    }
	}while(ch!=5);
	do{
	    hosp:
        	       cout<<"\n\n\t\t1.Add Hospital\n\t\t2.Delete Hospital\n\t\t3.Bed Availability\n\t\t4.View Hospitals\n\t\t5.Exit";
        	       cout<<"\n\t\t---------------------------------------------------------------------";
                         cout<<"\n\t\tEnter your choice: ";
	       cin>>ch;
 	       switch(ch){
    	        case 1: cout<<"\n\t\tEnter hospital details: ";
            		cout<<"\n\t\t----------------------------------------------------";
                    	cout<<"\n\t\tName: ";
                    	cin.ignore();
                    	getline(cin, nm);
                    	cout<<"\n\t\tCity: ";
                    	getline(cin, ct);
                    	cout<<"\n\t\tVacant Bed Count: ";
                    	cin>>bed;
                    	h.addHospital(nm, ct, bed);
                    	cout<<"\n\t\t_______________________________________________________________________________";
                    	break;
            	     case 2: cout<<"\n\t\tEnter the name of Hospital: ";
                    	cin.ignore();
                    	getline(cin, nm);
                    	h.removeHospital(nm);
                    	cout<<"\n\t\t_______________________________________________________________________________";
                    	break;
            	    case 3: cout<<"\n\t\tEnter city: ";
                    	cin.ignore();
                    	getline(cin, ct);
		h.checkBedAvailability(ct);
                    	cout<<"\n\t\t_______________________________________________________________________________";
                    	break;
	    case 4: cout<<"\n\t\tHospitals ";
            		cout<<"\n\t\t----------------------------------------------------------";
                    	h.covidHospitals();
                    	break;
	   case 5: break;
        	}
    }while(ch!=5);
    
    goto menu;
    
    do {
	again:	
	cout << "\n..........................................................................................................";
	cout << "\n                                               THYROCARE                                                  ";
	cout << "\n                                       ........................                                           ";
	cout << "\n                                         The TRUST, THE TRUTH                                             ";
	cout<<"\n____________________________________________________________________________";
	cout << "\n\n\t\t\t\t\t    1. Patient \n\t\t\t\t\t    2. Admin \n\t\t\t\t\t    3. Exit"; 
	cout << "\n\t\t\t\t      -------------------------";
	cout << "\n\t\t\t\t\t    Enter choice: ";
	cin >> choose;
	switch (choose) {
	system("cls");
	case 1:system("cls");
		do {
		cout <<"\n__________________________________________________________________________";
		cout << "\n                                           COVID-19 TESTING PORTAL                                        ";
		cout << "\n1. Register for Covid-testing \n2. View your report \n3. Exit";
		cout << "\n__________________________________________________________________________________";
		cout << "\n Choose action : ";
		cin >> n;
		switch (n) {
			case 1:cout << "How many members you want to test for Covid-19: ";
				cin >> family_members;
				cout <<"\n_____________________________________________________________________";
				p.registration(family_members);
				break;
			case 2: system("cls");
				cout << "Enter ID of patient to view report: ";
				cin >> Patient_id;
				ptr = p.view_report(Patient_id);
				cout<<ptr->report_status;
				s = ptr->report_status;
				if(s==1){
				    cout<<"\nYou are tested CoVid Positive...\n";
				    cout<<"Do you want to get admitted in the hospital? Y/N";
				    cin>>chc;
				    switch(chc){
				        case 'Y': h.admitPatient(ptr);
				                  break;
				        case 'N': cout<<"\nStay Home Quarantined. Wear mask. Take appropriate precautions...";
				        		  goto again;
				                  break;
				    }
				}
				else{
					goto again;
				}
				break;
			case 3:system("cls");
				goto again;
				break;
			}
		}while (n != 3);
		break;		
		case 2: p.admin();
			break;
		}
		
	} while (choose != 3);
	
	goto menu;
	
	vaccine:
	cout<<"\n**************** WELCOME TO COVID-19 VACCINE SECTION******************\n";
	queue q;
	queue qm; 
	queue qj; 
	queue qn;//object of queue class
	char y;
	int size1=20;
	int size2=20;
	int size3=20;
	int size4=20;
	do{
		cout<<"\n\n*******************MENU********************\n1.VACCINE REGISTRATION\t\t2.ABOUT VACCINE\n3.RULES FOR VACCINE\t\t4.Exit";
		cout<<"\n\nEnter your choice:\n";
		cin>>ch;
		switch(ch){
	case 1:
		do{
		      cout<<"\n***********MENU***********";
		     cout<<"\nWhich is your area:\n";
		     cout<<"\n1.PUNE\t\t2.MUMBAI\n3.JALGOAN\t4.NAGPUR\n5.EXIT\n";
		     cout<<"\n\nEnter your choice:\n";
		    cin>>ch;
		    switch(ch){
			case 1:
		  	  cout<<"\nONLY 20 VACCINES ARE AVAILABLE\n";
      			do{
			     int ch;
		   	     cout<<"\n**********MENU**********\n1.Apply for registration\n2.Confirmed registration\n3.Exit\n";
			     int size=20;
			     cout<<"\nEnter your choice:";
			     cin>>ch;
		  	     switch(ch){
			           case 1:
				if(size1==0){
				cout<<"\nNo Vaccine available";
				}else{
	     			q.enqueue();
	     			size1=size1-1;
				}
				break;
			         case 2: q.confirmList();
				break;
			         case 3: break;
	 		        default:
				cout<<"\nInvalid option\n";
				break;
			    }
			cout<<"\n\nWant to continue in pune section ?\nif yes type y\nif not type n\n:";
			cin>>y;
		           }  while(y=='y');
		           break;
     		    case 2:
		          do{
			int ch;
			cout<<"\n**********MENU**********\n1.Apply for registration\n2.Confirmed registration\n3.Exit\n";
			cout<<"\nEnter your choice:";
			cin>>ch;
			switch(ch){
			     case 1:
			         if(size2==0){
				cout<<"\nNo vaccine available";
			        }
			        else{
			     	qm.enqueue();
	     			size2=size2-1;
			        }
			        break;
			case 2: qm.confirmList();
				break;
			case 3: break;
			default:
				cout<<"\nInvalid option\n";
				break;
			}
		       cout<<"\n\nWant to continue mumbai section ?\nif yes type y\nif not type n\n:";
	     	       cin>>y;
	                        } while(y=='y');
     		     break;
     		case 3:
		   do{
		       int ch;
	   	       cout<<"\n**********MENU**********\n1.Apply for registration\n2.Confirmed registration\n3.Exit\n";
		       cout<<"\nEnter your choice:";
		       cin>>ch;
		       switch(ch){
		            case 1:
			if(size3==0){
				cout<<"\nNo vaccine available";
			}
			else{
		     	  	qj.enqueue();
		     		size3=size3-1;
			}
			break;
		           case 2: qj.confirmList();			
			break;
		           case 3:  break;
		           default:
			cout<<"\nInvalid option\n";
			break;
		      }
		     cout<<"\n\nWant to continue jalgoan section ?\nif yes type y\nif not type n\n:";
		     cin>>y;
	               }  while(y=='y');
     		break;
	        case 4:
	 	do{int ch;
		cout<<"\n**********MENU**********\n1.Apply for registration\n2.Confirmed registration\n3.Exit\n";
		cout<<"\nEnter your choice:";
		cin>>ch;
		switch(ch){
		        case 1:
			if(size4==0){
				cout<<"\nNo vaccine available";
			}else{
	     	       	qn.enqueue();
	     		size4=size4-1;
			}
			break;
  		      case 2:qn.confirmList();		
			break;
		      case 3:		
			break;
		      default:
			cout<<"\nInvalid option\n";
			break;
		}
		cout<<"\n\nWant to continue nagpur section ?\nif yes type y\nif not type n\n:";
		cin>>y;
		}while(y=='y');
	 	break;
	     case 5:	break;
	     default:
	 	cout<<"Invalid";
	 }
             } while(ch!=5);
              break;		
            case 2:
	cout<<"Vaccines definition\n\nThe body’s immune system helps protect against pathogens that cause infection. Most of the time, it’s an efficient system. It either keeps microorganisms out or tracks them down and gets rid of them.\nHowever, some pathogens can overwhelm the immune system. When this happens, it can cause serious illness.\nThe pathogens most likely to cause problems are the ones the body doesn’t recognize. Vaccination is a way to “teach” the immune system how to recognize and eliminate an organism. That way, your body is prepared if you’re ever exposed.\nVaccinations are an important form of primary prevention. That means they can protect people from getting sick. \nVaccinations have allowed us to control diseases that once threatened many lives, such as:\n";
                cout<<"\n\nmeasles\nolio\ntetanus\nwhooping cough\n";
                cout<<"\n\nIt’s important that as many people as possible get vaccinated. Vaccinations don’t just protect individuals. When enough people are vaccinated, it helps protect society.\nhis occurs through herd immunity. Widespread vaccinations make it less likely that a susceptible person will come into contact with someone who has a particular disease.\n";
                cout<<"\n\nHow does vaccination work?\nA healthy immune system defends against invaders. The immune system is composed of several types of cells. These cells defend against and remove harmful pathogens. However, they have to recognize that an invader is dangerous.\nVaccination teaches the body to recognize new diseases. It stimulates the body to make antibodies against antigens of pathogens. It also primes immune cells to remember the types of antigens that cause infection. That allows for a faster response to the disease in the future.\nVaccines work by exposing you to a safe version of a disease. \nThis can take the form of:";
                cout<<"\n\na protein or sugar from the makeup of a pathogen\na dead or inactivated form of a pathogen\na toxoid containing toxin made by a pathogen\na weakened pathogen";
                cout<<"\n\nWhen the body responds to the vaccine, it builds an adaptive immune response. This helps equip the body to fight off an actual infection.\nVaccines are usually given by injection. Most vaccines contain two parts. The first is the antigen. This is the piece of the disease your body must learn to recognize. The second is the adjuvant.\nThe adjuvant sends a danger signal to your body. It helps your immune system to respond more strongly against the antigen as an infection. This helps you develop immunity.";
                cout<<"\n------------------------------------------------------------------------------------------------------------------------------------------";
	break;
            
	case 3:
            	cout<<"\n1.Documents Required:\n\nAadhar card\nPAN card\nPhone number\n";
			     cout<<"\n2.Person with confirmed or suspected COVID-19 infection may increase the risk of spreading the same to others at vaccination site. For this reason, infected individuals should defer vaccination for 14 days after symptoms resolution.\n";
                 cout<<"\n3.Below 18 not aloweded\n";
                 break;

            case 4:
            	break;
		    default:
            	cout<<"\nInvalid option";
            	break;
				}
		}while(ch!=4);
		goto menu;
	return 0;
}

/**************************************************************************
	Time Complexities:
	Zones:
	    1. enQueue() 		:		O(1)
	    2. display() 		:		O(n)

	Hospital:
	    1. addHospital()		:		O(1)
	    2. removeHospital()	:		O(1)
	    3. checkBedAvailability()	:		O(n)
	    4. covidHospitals()	:		O(n)
	    5. updateBedCount()	:		O(n)

	Testing:
	    1. registration()		:		O(1)
	    2. view_Report()		:		O(n)
	    3. admin()		:		O(n)

	Vaccination:
	    1. enqueue()		:		O(1)
	    2. confirmList()		:		O(n)

****************************************************************************/

/*************Github link: https://github.com/Sayalinc28/Covid_Helpline.git ************/