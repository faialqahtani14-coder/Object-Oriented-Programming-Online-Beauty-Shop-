/*
Purpose: This program is about an international company's employees. it allows users to select a choice from a menu (Add/Update/Delete/Search/Sort/Display/Save/Exit).

*/

#include <iostream> 
#include<string>
#include<fstream>
#include <ctime>
using namespace std;
//Global variables
const int SIZE=100; //global constant
int count=0; // actual size of array

int total[6]={0}; //counter for statistical report

struct Employees {
	
	string Name;
	string Id;
	string Nationality;
	int Salary;
	
} emps[SIZE];

//functions prototypes
int menu();
void add_emp();
void delete_emp();
void update_emp();
void sort_emp();
bool emptyArray();
int search();
void show_emp(int i);
void display_emp();
void add_data();
void save_emp(Employees emp[], int count);
bool checknum (string name);
bool checkletter (string name);
void report_emps();

int main() 
{
 	int choice;  
    ifstream infile("internationalcomp.txt", ios::in);
       int counter = 0 ;
	   if(infile.is_open()) {

         while (!infile.eof())
         {
           getline(infile, emps[counter].Id,'#');
           getline(infile, emps[counter].Name,'#');
           getline(infile, emps[counter].Nationality,'#');
           infile>> emps[counter].Salary;
           infile.ignore();

           counter++;
        }
        count=counter-1;
        //counter--;
        infile.close();  
    }
    
    else {
     cout<<"\n\n\t\tEmployee Management System"<<endl;
	}
  //to show the menu to the user
	do{
		choice=menu();
	    
		switch (choice)
		{
			case 1: //Add new employee
					if (count<SIZE)
					   add_emp();
					else 
					   cout<<"\nERROR: The array is full. Please delete employee first!";
					break;
       
			case 2: //delete an employee
					if (!emptyArray())
						delete_emp();
					break;
				
			case 3: //update employee's salary
					if (!emptyArray()) 
					   update_emp(); 		
					break;
				
			case 4: //print all employees	
					if (!emptyArray())
						display_emp();
	
					break;

			case 5: //find an employee by id
					if (!emptyArray())
				    {
				    	int i=search();
				    	if (i>=0)
				    	    show_emp(i);
				    	else
				    	    cout<<"\n Employee could not be found\n";
					}
					break;
					
			case 6: //sort employees by their salary
				if (!emptyArray())
					    sort_emp(); 
					break;
					
			case 7: cout<<"\n Thank you for using our program <3! \n";
					 break;
					
			default: cout<<"\n Incorrect menu option. Please try another option.";
		}
		
	}while(choice!=7);
	 report_emps();
	 save_emp(emps,count);
	 
 
	return 0;
}//end of main


int menu()
{
	int choice;
	cout<<"\n Please choose an option:"
		<<"\n1  - Add an employee"
  		<<"\n2  - Delete an employee"
  		<<"\n3  - Update an employee's salary"
  		<<"\n4  - Display all employee"
  		<<"\n5  - Find an employee by their ID"
  		<<"\n6  - Sort employees by their salary"
  		<<"\n7  - Exit "
		<<"\n>> ";    
	cin>>choice;
	return choice;
}//end of menu

void add_emp()
{   total[0]++; //statistical report counter
    cout<<"Please enter employee`s information: ";
	cout<<"\n Their id: ";      
	cin>>emps[count].Id;
	while(checknum(emps[count].Id))
    {
       cout<<"Please enter a DIGIT !";
       cout<<"\n Their id : ";
       cin>>emps[count].Id;
    }
	cout<<"\n Their name: ";      
	cin>>emps[count].Name;	
    while(checkletter(emps[count].Name))
    {
       cout<<"please enter a LETTER !";
       cout<<"\n Their name:";
       cin>>emps[count].Name;
    }		    
	cout<<"\n Their nationality: ";      
	cin>>emps[count].Nationality;
    while(checkletter(emps[count].Nationality))
    {
       cout<<"Please enter a LETTER !";
       cout<<"\n Their nationality:";
       cin>>emps[count].Nationality;
    }					
	cout<<"\n Their salary: ";     
	cin>>emps[count].Salary;
	count++;  
}//end of add_emp

void display_emp()
{    
      total[5]++;    
	for (int i=0;i<count;i++)
	     show_emp(i);
}//end of display_emp+

void show_emp(int i)
{
	cout<<"\n Employee "<<(i+1)<<"\n"
	    <<"\n\t ID    :"<<emps[i].Id<<"\n"
	    <<"\n\t Name  : "<<emps[i].Name<<"\n"
		<<"\n\t Nationality:"<<emps[i].Nationality<<"\n"
		<<"\n\t Salary :"<<emps[i].Salary <<"\n";
}//end of show_emp

void delete_emp()
{   total[1]++;
	int index=search();
	ofstream outfile;
    outfile.open("internationalcomp.txt",ios::app);
    if (outfile.is_open())
	{
	  if (index<0)
	 {
		 cout<<"\n Not found \n";
		 return;  //to exit from the function
	 }
	
	  for (int j=index; j< count; j++){
	  
		 emps[j]=emps[j+1];
				
	     count--;
	     cout<<"\n Employee deleted successfully. \n";}
    }
         count++;
         outfile.close();
}//end of delete_emp

void update_emp()
{// updating the employee's salary only	
    total[2]++;
	int index=search();
	if (index<0)
	{
		cout<<"\n Not found \n";
		return;  //to exit from the function
	}
	
	cout<<"\n Please enter the old salary: "<<emps[index].Salary;
	cout<<"\n Please enter the new salary: ";
	cin>>emps[index].Salary;
	cout<<"\n Employee`s salary updated successfully. \n";
}//end of update_emp

bool emptyArray()
{
	if (count==0)
	{
		cout<<"\n The array is empty!\n";
		return true;
	}
	
	return false;
}//end of emptyArray

bool checknum (string name )
{ 
    for(int i=0 ; i<name.length();i++)
    { if (isdigit(name[i]))
    return false; }

    return true;
} // end of checknum

bool checkletter (string name )
{
    for(int i=0 ; i<name.length();i++)
    { if (isalpha(name[i]))
    return false; }

    return true;
} // end of checkletter

int search()
{//classic way 
    total[3]++;
	string id;
	
	cout<<"\n Please enter an employee`s ID:";
	cin>>id;

	for (int i=0;i<count;i++)
		if (emps[i].Id==id)
			return i;	
	
	return -1;  //if not found
}//end of search 

void sort_emp()
{//sort salary in descending order
    total[4]++;
	bool ordered=false;
	Employees temp;
	
	if (count < 2) 
		cout<<"\n Nothing to sort!";
		
    for(int i = 0; i < count-1 && ordered==false ; ++i) 
    {	 
		ordered=true;
		for(int j = 0; j < count-1;++j)
  	     	if(emps[j].Salary < emps[j+1].Salary)     
	     	{        
			ordered=false;
	            temp = emps[j];
	            emps[j] = emps[j+1];
	            emps[j+1] = temp;
	    	}
 	}
 	cout<<"\n Salaries in descending order:";
 	display_emp();	
}//end of sort function

void add_data() 
{   
    ofstream addfile;
    addfile.open("internationalcomp.txt",ios::app);
    if(addfile.is_open())
    {
        add_emp();
        addfile<<emps[count].Id<<"#";
        addfile<<emps[count].Name<<"#";
        addfile<<emps[count].Nationality<<"#";
        addfile<<emps[count].Salary<<endl;
        count++;
    }
    addfile.close();
}//end of add data


void save_emp(Employees emp[],int count)
{  
    ofstream inFile("internationalcomp.txt",ios::out);
    if(inFile.is_open())
    {
      for(int i=0 ; i<count ; i++)
      {
        inFile<<emps[i].Id<<"#";
        inFile<<emps[i].Name<<"#";
        inFile<<emps[i].Nationality<<"#";
        inFile<<emps[i].Salary<<endl;
      }
      inFile.close();
      cout<<"\n Data saved successfully \n ";
    }
    else cout<<"Failed to save data. Please try again. ";
}//end of save 


void report_emps()
{
	ofstream ReportFile; 	
	time_t t;	
	t= time(NULL);
	char *time=ctime(&t);
	ReportFile.open("report.txt", ios::app);
	if (ReportFile.is_open())
	{   ReportFile<<endl;
		ReportFile<<"The user chose to add data: "<<total[0]<<" times"<<endl;
		ReportFile<<"The user chose to delete data: "<<total[1] <<" times"<<endl;
		ReportFile<<"The user chose to update data: "<<total[2]<<" times"<<endl;
		ReportFile<<"The user chose to display data: "<<total[5]<<" times"<<endl;
		ReportFile<<"The user chose to search data: "<<total[3]<<" times"<<endl;
		ReportFile<<"The user chose to sort data: "<<total[4] <<" times"<<endl;
		ReportFile<<"The date of last update: "<<time<<endl;
	}
	else
	cout<< "Failed To Save Last Modifications!\n";
	ReportFile.close();
} //end of our report

