#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>

using namespace std;
const string delimiter = ",";

class Drug{
	public:
		int Id;
		string Name;
		
		Drug()
		{
			Id = 0;
			Name = "";
		}
		Drug(int id, string name)
		{
			Id = id;
			Name = name;
		}
};
class Amount{
	public:
		int DrugId;
		int Value;
		Amount()
		{
			DrugId = 0 ; 
			Value =  0 ;
		}
		Amount(int drugId, int value)
		{
			DrugId = drugId;
			Value = value;
		}
};
class Sale{
	public:
		int Id;
		string NationalCode;
		int DrugId;
		int Amount;
		Sale()
		{
			Id = 0;
			Amount = 0;
			NationalCode = "";
			DrugId = 0;
		}
		Sale(int id, string nationalCode, int drugId, int amount)
		{
			Id = id;
			Amount = amount;
			NationalCode = nationalCode;
			DrugId = drugId;
		}
};


Amount * amountsList; 
Drug * drugsList;  
Sale * salesList;   
unsigned int amountsCount , drugsCount , salesCount;

void clear();
void _1();
void _2();
void _3();
void _4();
void Save();

int main()
{
	system("Color 84");
  
  	clear();
	cout << "Loading ..." << endl;
	
	// Drugs Load
	drugsCount =0;
	string unused;
	ifstream drugsFile ("Drugs.3ms");
	while ( getline(drugsFile, unused) )
	   ++drugsCount;
	 drugsFile.close();
	 drugsFile.open("Drugs.3ms");
	drugsList = new Drug [drugsCount];
	string line = "";
	int i = 0 ;
	while ( i < drugsCount  )
	{
		getline (drugsFile,line);
		int id = atoi(line.substr(0, line.find(delimiter)).c_str());
		line = line.erase(0, line.find(delimiter) + delimiter.length());
		string name = line;	
		(drugsList[i]) = Drug(id, name);
		i++;
	}
	drugsFile.close();
	
	
	// Sales Load
	salesCount =0;
	unused = "";
	ifstream salesFile ("Sales.3ms");
	while ( getline(salesFile, unused) )
	++salesCount;
	salesFile.close();
	salesFile.open("Sales.3ms");
	salesList = new Sale [salesCount];
	line = "";
	i = 0 ;
	while ( i < salesCount  )
	{
		getline (salesFile,line);
		int id = atoi(line.substr(0, line.find(delimiter)).c_str());
		line = line.erase(0, line.find(delimiter) + delimiter.length());
		string nationalCode = line.substr(0, line.find(delimiter));
		line = line.erase(0, line.find(delimiter) + delimiter.length());
		int drugId = atoi(line.c_str());
		line = line.erase(0, line.find(delimiter) + delimiter.length());
		int amount = atoi(line.c_str());
		(salesList[i]) = Sale(id, nationalCode, drugId, amount);	
		i++;
	}
	line="";
	salesFile.close();

	
	// Amounts Load
	amountsCount =0;
	unused = "";
	ifstream amountsFile ("Amounts.3ms");
	while ( getline(amountsFile, unused) )
	   ++amountsCount;
	amountsFile.close();
	amountsFile.open("Amounts.3ms");
	amountsList = new Amount [amountsCount];
	line = "";
	i = 0 ;
	while ( i < amountsCount  )
	{
		getline (amountsFile,line);
		int id = atoi(line.substr(0, line.find(delimiter)).c_str());
		line = line.erase(0, line.find(delimiter) + delimiter.length());
		int value = atoi(line.c_str());
		(amountsList[i]) = Amount(id, value);
		i++;
	}
	amountsFile.close();
	i = 0;
	
	// App start
	cout << "Lundary App v1.0.0.0" << endl;
    cout << "Press any key to continue..." << endl;
	bool AppClosed = false;
	while (!AppClosed)
	{	
		getch();
		clear();
	    cout << "1- Drugs" << endl;
	    cout << "2- Amount" << endl;
	    cout << "3- Sales" << endl;
	    cout << "4- Report" << endl;
	    cout << "5- Exit" << endl;
	    		
	    int Choice;
	    cin >> Choice;
	    
	    switch (Choice)
	    {
	    	case 1:
	    		_1();
	    		break;
			case 2:
				_2();
				break;
			case 3:
				_3();
				break;
			case 4:
				_4();
				break;
	    	case 5:
	    		clear();
	    		Save();
	    		cout << "Goodbye!" << endl;
	    		cout << "Press any key to exit";
	    		AppClosed = true;
				break;
	    								
		}
	    
	}
		
	getch();
    return 0;
}
void clear(){
	system("cls");
}
void _1(){
	clear();
	cout << "1- View" << endl;
    cout << "2- Add" << endl;
    cout << "3- Edit" << endl;
    cout << "4- Delete" << endl;
    		
    int Choice;
    cin >> Choice;
    clear();
    switch (Choice)
    {
    	case 1:
    	{
			// View Drugs
			cout << "|" << left << setw(10) << "Drug Code" << "|" << "Drug Name" <<  endl;
			for (int i = 0 ; i < drugsCount ; i ++)
			{
				cout << "|" << left << setw(10) << drugsList[i].Id << "|" << drugsList[i].Name << endl;
			}
    		break;
    	}
    	
		case 2:
		{
			// Add Drugs
			drugsCount ++ ; 
			Drug * temp = new Drug [drugsCount]; 
			for (int i = 0 ; i < drugsCount - 1; i ++)
			{
				temp[i] = drugsList[i];
			}
			cout << "Id: " ;
			int id ; 
			cin >> id;
			cout << "Name: ";
			string name;
			cin >> name;
			temp[drugsCount - 1 ] = Drug(id, name);
			drugsList =  new Drug [drugsCount ];
			for (int i = 0 ; i < drugsCount ; i ++)
			{
				drugsList[i] = temp[i] ;
			}
			// delete temp;
			cout << "Done!";
			break;
		}
		case 3:
			// Edit Drug
			cout << "Id: ";
			int id ;
			cin >> id;
			for (int i = 0 ; i < drugsCount ; i ++)
			{
				if (drugsList[i].Id == id)
				{
					cout << "Name: ";
					string name;
					cin >> name;
					drugsList[i] = Drug(id, name);
					cout << "Done!";
				}
			}
			break;
		case 4:
		{
			// Delete Drug
			cout << "Id: ";
			int id ;
			cin >> id;
			drugsCount--;
			Drug * temp = new Drug [drugsCount];
			bool found= false;
		
			for (int i = 0 ; i < drugsCount ; i ++)
			{
				if (drugsList[i].Id == id)
				{
					found = true;
				}
				temp[i] = drugsList[found ? i + 1 : i];
			}
			
			drugsList =  new Drug [drugsCount ];
			for (int i = 0 ; i < drugsCount ; i ++)
			{
				drugsList[i] = temp[i];
			}
			cout << "Done!";
			break;
		}
	}
}
void _2(){
	clear();
	cout << "1- View" << endl << "2- Edit" << endl;
	int myCase = 0;
	cin >> myCase;
	clear();
	switch (myCase)
	{
		case 1:
		{
			// View amounts
			cout << "|" << left << setw(10) << "Drug Code" << "|" << "Amount" <<  endl;
			for (int i = 0 ; i < amountsCount ; i ++)
			{
				cout << "|" << left << setw(10) << amountsList[i].DrugId << "|" << amountsList[i].Value << endl;
			}
			break;
		}
		case 2:{
			// Edit amounts
			
			cout << "Drug Code: ";
			int drugId ;
			cin >> drugId;
			for (int i = 0 ; i < amountsCount ; i ++)
			{
				if (amountsList[i].DrugId == drugId)
				{
					cout << "Value: ";
					int value;
					cin >> value;
					amountsList[i] = Amount(drugId, value);
					cout << "Done!";
				}
			}		
			break;
		}
	}
}
void _3(){
	clear();
	cout << "1- View" << endl << "2- Add" << endl;
	int myCase = 0;
	cin >> myCase;
	clear();
	switch (myCase)
	{
		case 1:
		{
			// View sales
			cout << "|" << left << setw(15) << "Factor Number" << "|" << left << setw(10) << "Drug Code" << "|" << left << setw(20) << "NationalCode" << "|" << "Amount" <<  endl;
			for (int i = 0 ; i < salesCount ; i ++)
			{
				cout << "|" << left << setw(15) << salesList[i].Id << "|" << left << setw(10) << salesList[i].DrugId << "|" << left << setw(20) << salesList[i].NationalCode << "|" << salesList[i].Amount <<  endl;
			}
			break;
		}
		case 2:
		{
			// Add sale
			salesCount ++ ; 
			Sale * temp = new Sale [salesCount]; 
			for (int i = 0 ; i < salesCount - 1; i ++)
			{
				temp[i] = salesList[i];
			}
			cout << "Id: ";
			int id;
			cin >> id;
			cout << "National Code: ";
			string nationalCode;
			cin >> nationalCode;
			int drugId;
			cout << "Drug Code: " ;
			cin >> drugId;
			int amount;
			cout << "Amount: " ;
			cin >> amount;
			temp[salesCount - 1 ] = Sale(id, nationalCode , drugId, amount);
			salesList =  new Sale [salesCount];
			for (int i = 0 ; i < salesCount ; i ++)
			{
				salesList[i] = temp[i] ;
			}
			cout << "Done!";
			break;
		}
	}
	
}
void _4(){
	// Report
	cout << "|" << left << setw(15) << "Factor Number" << "|" << left << setw(85) << "Drug Name" << "|" << left << setw(20) << "NationalCode" << "|" << "Amount" <<  endl;
	for (int i = 0 ; i < salesCount ; i ++)
	{
		cout << "|" << left << setw(15) << salesList[i].Id << "|" << left << setw(85);
		// drug name
		for (int j = 0; j < drugsCount; j ++)
		{
			if (drugsList[j].Id == salesList[i].DrugId)
			{
				cout << drugsList[j].Name;
			}
		}
		cout << "|" << left << setw(20) << salesList[i].NationalCode << "|" << salesList[i].Amount <<  endl;
	}
}
void Save(){
	// TODO
	
	// Drugs Save
	ofstream drugsFile("Drugs.3ms");
	for (int i = 0 ; i < drugsCount ; i ++)
	{
		drugsFile << drugsList[i].Id << "," << drugsList[i].Name << endl;
	}
	drugsFile.close();
	// Amount Save
	ofstream amountsFile("Amounts.3ms");
	for (int i = 0 ; i < amountsCount ; i ++)
	{
		amountsFile << amountsList[i].DrugId << "," << amountsList[i].Value << endl;
	}
	amountsFile.close();
	// Sales Save
	ofstream salesFile("Sales.3ms");
	for (int i = 0 ; i < salesCount ; i ++)
	{
		salesFile << salesList[i].Id << "," << salesList[i].NationalCode << "," << salesList[i].DrugId << "," << salesList[i].Amount << endl;
	}
	salesFile.close();
	// Reports Save
	ofstream reportFile("Report.html");
	reportFile << "<!doctype html><html><head><meta charset=\"utf-8\"><title>Drug Store</title><style>";
	reportFile << "table { border-collapse: collapse; text-align: left; width: 100%; } {font: normal 12px/150% Arial, Helvetica, sans-serif; background: #fff; overflow: hidden; border: 1px solid #991821; -webkit-border-radius: 3px; -moz-border-radius: 3px; border-radius: 3px; }table td, table th { padding: 3px 10px; }table thead th {background:-webkit-gradient( linear, left top, left bottom, color-stop(0.05, #991821), color-stop(1, #80141C) );background:-moz-linear-gradient( center top, #991821 5%, #80141C 100% );filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#991821', endColorstr='#80141C');background-color:#991821; color:#FFFFFF; font-size: 15px; font-weight: bold; border-left: 1px solid #B01C26; } table thead th:first-child { border: none; }table tbody td { color: #80141C; border-left: 1px solid #F7CDCD;font-size: 12px;font-weight: normal; }table tbody .alt td { background: #F7CDCD; color: #80141C; }table tbody td:first-child { border-left: none; }table tbody tr:last-child td { border-bottom: none; }table tfoot td div { border-top: 1px solid #991821;background: #F7CDCD;} table tfoot td { padding: 0; font-size: 12px } table tfoot td div{ padding: 2px; }table tfoot td ul { margin: 0; padding:0; list-style: none; text-align: right; }table tfoot  li { display: inline; }table tfoot li a { text-decoration: none; display: inline-block;  padding: 2px 8px; margin: 1px;color: #FFFFFF;border: 1px solid #991821;-webkit-border-radius: 3px; -moz-border-radius: 3px; border-radius: 3px; background:-webkit-gradient( linear, left top, left bottom, color-stop(0.05, #991821), color-stop(1, #80141C) );background:-moz-linear-gradient( center top, #991821 5%, #80141C 100% );filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#991821', endColorstr='#80141C');background-color:#991821; }table tfoot ul.active, table tfoot ul a:hover { text-decoration: none;border-color: #80141C; color: #FFFFFF; background: none; background-color:#991821;}div.dhtmlx_window_active, div.dhx_modal_cover_dv { position: fixed !important; }";
	reportFile << "</style></head><body><table><tbody><tr><th>Factor Number</th><th>Drug Name</th><th>National Code</th><th>Amount</th></tr>" << endl;
	for (int i = 0 ; i < salesCount ; i ++)
	{
		reportFile << "<tr><td>" << salesList[i].Id << "</td><td>";
		// drug name
		for (int j = 0; j < drugsCount; j ++)
		{
			if (drugsList[j].Id == salesList[i].DrugId)
			{
				reportFile << drugsList[j].Name;
			}
		}
		reportFile << "</td><td>" << salesList[i].NationalCode << "</td><td>" << salesList[i].Amount << "</td></tr>" << endl;
	}
	reportFile << "</tbody></table></body></html>";
	reportFile.close();
}
