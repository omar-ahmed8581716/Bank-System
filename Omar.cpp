#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string FileName = "DataInfo.txt";   

enum enProcessTypes {
  Show = 1 , Add = 2 , 
  Delete = 3 , Update = 4 , 
  Find = 5 , Exit = 6  
};

struct stClientInfo {
	string Name = "";
	string AccountNumber = "";
	string PinCode = "";
	string PhoneNumber = "";
	double Balance = 0;
	bool MarkForDelete = false ; // To Delete Client 
};

// ************** These are Basic Functions **************

stClientInfo ReadCLientInfo(string AccountNumber)
{
	// this Function To update clinet info

	stClientInfo Client;

	Client.AccountNumber = AccountNumber;

	cout << " Enter Pin Code : ";
	getline(cin>>ws, Client.PinCode);

	cout << " Enter Client Name : ";
	getline(cin , Client.Name);

	cout << " Enter Phone Number : ";
	getline(cin , Client.PhoneNumber);

	cout << " Enter Balance : ";
	cin >>Client.Balance;

	return Client;
}

string ReadAccountNumber()
{
	string AccountNumber = "";

	cout << " Enter Account Number : ";
	cin >> AccountNumber;

	return AccountNumber;
}        

vector<string> SpilitString( string Text , string Seperator )
{
	short Pos = 0;
	string Word = "";
	vector<string> vString;

	while ((Pos = Text.find(Seperator)) != std::string::npos)
	{
		Word = Text.substr(0, Pos);

		if (Word != "")
		{
			vString.push_back(Word);
		}

		Text.erase(0, Pos + Seperator.length());
	}

	if (Text != "")
	{
		vString.push_back(Text);
	}

	return vString;
}

stClientInfo ConvertDataToStruct(string Text , string Seprator = "#//#")
{
	vector<string> vString;
	stClientInfo Client;

	vString = SpilitString(Text, Seprator );

		Client.AccountNumber = vString[0];
		Client.PinCode       = vString[1];
		Client.Name          = vString[2];
		Client.PhoneNumber   = vString[3];
		Client.Balance       = stod(vString[4]); // Change Balance from string to doubel , 
	                                            //  To storge in struct
	return Client;
}

string ConvertDataToLine(stClientInfo Client, string Sepetator = "#//#")
{
	string Line = "";

	Line += Client.AccountNumber + Sepetator ;
	Line += Client.PinCode + Sepetator ;
	Line += Client.Name + Sepetator ;
	Line += Client.PhoneNumber + Sepetator ;
	Line += to_string(Client.Balance) ; // change balance (doubel) => string

	return Line;
}

vector<stClientInfo> ReloadDataFromFile(string FileName)
{
	vector<stClientInfo> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in); // Read Mode   

	if (MyFile.is_open())             // Comp enter File , search data (any word in line)
	{                                //  if Line != empty , take the line and spilit it and 
		string Line;                // storage in structure , after that push (client) in vector
		stClientInfo Client;

		while (getline(MyFile, Line))
		{
			if (Line != "")
			{
				Client = ConvertDataToStruct(Line);
				vClients.push_back(Client);
			}
		}

		MyFile.close();
	}

	return vClients ;
}

bool IsClintFindByAccountNumber(string AccountNumber, string FileName, stClientInfo& Client)
{
	vector<stClientInfo> vClient = ReloadDataFromFile(FileName);

	for (stClientInfo& C : vClient)
	{
		if (AccountNumber == C.AccountNumber)
		{
			Client = C;
			return true;
	    }
	}
	return false;
}

void PrintClientCard(stClientInfo &Client)
{
	cout << "\n ***** Client Details ***** \n";
	cout << "-------------------------------\n";
	cout << " Account Number : " << Client.AccountNumber << endl;
	cout << " Pin Code       : " << Client.PinCode       << endl;
	cout << " Client Name    : " << Client.Name		     << endl;
	cout << " Phone Number   : " << Client.PhoneNumber	 << endl;
	cout << " Balance        : " << Client.Balance		 << endl;
	cout << "\n-------------------------------\n";
}

enProcessTypes ReadOpetionFromUser()
{
	short Opetion = 0;

	cout << " Choose your Opetion from this Menu : ";
	cin >> Opetion;

	while (Opetion > 6 || Opetion < 1)  // valedation 
	{
		cout << " Wrong Answer , Plese Enter Another Answer : ";
		cin >> Opetion;
	}

	return (enProcessTypes) Opetion;
}

void PrintOpetionOnTheScreen()
{
	cout << "\n======================================\n";
	cout << "\t Main Opetions ";
	cout << "\n======================================\n";
	cout << "   [1] Show Clinets List  \n";
	cout << "   [2] Add New Client  \n";
	cout << "   [3] Delete Clinet  \n";
	cout << "   [4] Update Clinet Info  \n";
	cout << "   [5] Find Clinet  \n";
	cout << "   [6] Exit  \n";
	cout << "=======================================\n";
}

void GoBackToMainMenu()
{
	cout << "\n\n Click any key to go back to Main Menue...";
	system("pause>0");
	PrintOpetionOnTheScreen();
}

// ************** These are Showing Functions **************

void PrintOneClient__Show(stClientInfo Client)
{ 
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.PhoneNumber;
	cout << "| " << left << setw(9)  << Client.Balance <<"|";

	//  | A150  | 147852 | Omar Ahmed    | 01011223344  | 5000 |
}

void PrintAllClients__Show(vector<stClientInfo> vClients)
{
	cout << "\n\t\t\t\t***** CLient List [" << vClients.size() << "] Clients  *****";
	cout << "\n________________________________________________________________________________________________\n\n";
																				
	cout << "| " << left << setw(15) << "Account Number ";						
	cout << "| " << left << setw(10) << "Pin Code ";							
	cout << "| " << left << setw(40) << "Client Name ";							
	cout << "| " << left << setw(12) << "Phone ";								
	cout << "| " << left << setw(9) << "Balance  |";								
	cout << "\n________________________________________________________________________________________________\n";
																				
	for (stClientInfo& Client : vClients)										
	{																			
		PrintOneClient__Show(Client);											
		cout << endl;															
	}																			
																				
	cout << "\n________________________________________________________________________________________________\n";
																				
}

// ************** These are Adding Functions **************

void AddClintDataToFile__Add(string FileName, string Line)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << Line << endl;
		MyFile.close();
	}
}

void AddNewClient__Add()
{
	cout << "\---------------------------------\n";
	cout << "\t Add New Client \n";
	cout << "---------------------------------\n\n";

	stClientInfo Client;
	string AccountNumber = ReadAccountNumber();

	while (IsClintFindByAccountNumber(AccountNumber , FileName ,Client))
	{
		cout << " This Account Number [" << AccountNumber << "] already exists, Enter another Account Number : ";
		cin >> AccountNumber;
	}

	Client = ReadCLientInfo(AccountNumber);

	string Line = ConvertDataToLine(Client);

	AddClintDataToFile__Add(FileName, Line);
}

void AddMoreClients__Add()
{
	char AddMore = 'y';

	do
	{
		AddNewClient__Add();

		cout << " Client Added Successfuly , Do you want Add More Clients ? : ";
		cin >> AddMore;

	} while (AddMore == 'y' || AddMore == 'Y');
}

// ************** These are Finding Functions **************

bool FindTheClint()
{
	cout << "\n----------------------------\n";
	cout << "\t Find Client \n";
	cout << "----------------------------\n\n";

	string AccountNumber = ReadAccountNumber();
	stClientInfo Client;

	while (!IsClintFindByAccountNumber(AccountNumber, FileName, Client))
	{
		cout << "\nClient with Account Number [" << AccountNumber << "] is not found , Enter again: ";
		cin >> AccountNumber;
	}

	PrintClientCard(Client);
	return true;
	
}

// ************** These are Delete Functions **************

bool MarkForDeleteByAccountNumber(string AccountNumber, vector<stClientInfo>& vClients)
{
	for (stClientInfo& Client : vClients)
	{
		if (AccountNumber == Client.AccountNumber)
		{
			Client.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector<stClientInfo> SaveDataToFile(string FileName , vector<stClientInfo> vClient)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string Line ;

	if(MyFile.is_open())
	{
		for (stClientInfo& Client : vClient)
		{
			if (Client.MarkForDelete == false)
			{
				Line = ConvertDataToLine(Client);
				MyFile << Line << endl;
		    }
        }

		MyFile.close();
	}

	return vClient;
}

bool DeleteClint(vector<stClientInfo> &vClient)
{
	cout << "\----------------------------\n";
	cout << "\t Delete Client \n";
	cout << "----------------------------\n\n";

	string AccountNumber = ReadAccountNumber();

	stClientInfo Client;
	char Answer = 'n';

	if (IsClintFindByAccountNumber(AccountNumber, FileName, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client ? y/n : ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			MarkForDeleteByAccountNumber(AccountNumber, vClient);
			SaveDataToFile(FileName, vClient);

			vClient = ReloadDataFromFile(FileName); // To Refresh Clients 
			cout << " Client Deleted Sccussfuly . ";
			return true;
		}
	}
	else
	{
		cout << "\n This Account Number [" << AccountNumber << "] is not Found . ";
		return false;
	}
}

// ************** These are Update Functions **************

bool UpdateCLientData(vector<stClientInfo>& vClient)
{
	cout << "\n----------------------------\n";
	cout << "   Update Client Data \n";
	cout << "----------------------------\n\n";

	stClientInfo Client;
	char Answer = 'n';
	string AccountNumber = ReadAccountNumber();

	if (IsClintFindByAccountNumber(AccountNumber, FileName, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want Update client Data ? y/n : ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (stClientInfo& C : vClient)
			{
				if (AccountNumber == C.AccountNumber)
				{
					C = ReadCLientInfo(AccountNumber);
					break;
			    }
		    }
			SaveDataToFile(FileName, vClient);
			cout << "\n Client Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\n This Account Number [" << AccountNumber << "] is not Found . ";
		return false;
	}
}

// ************** This program excuation function  **************

void programExcuation(enProcessTypes Opetion)
{
	vector<stClientInfo> vClient = ReloadDataFromFile(FileName);

	switch (Opetion)
	{
	case enProcessTypes::Show:
	{
		system("cls");
		PrintAllClients__Show(vClient);
		GoBackToMainMenu();
		break;
	}
	case enProcessTypes::Add:
	{
		system("cls");
		AddMoreClients__Add();
		GoBackToMainMenu();
		break;
	}
	case enProcessTypes::Delete:
	{
		system("cls");
		DeleteClint(vClient);
		GoBackToMainMenu();
		break;
	}
	case enProcessTypes::Update:
	{
		system("cls");
		UpdateCLientData(vClient);
		GoBackToMainMenu();
		break;
	}
	case enProcessTypes::Find:
	{
		system("cls");
		FindTheClint();
		GoBackToMainMenu();
		break;
	}
	case enProcessTypes::Exit:
	{
		system("cls");
		cout << "\n========================================\n";
		cout << "   Thank you To Use our Program :-) \n";
		cout << "========================================\n";
		break;
	}

	}

}

void ShowMainMenu()
{
	enProcessTypes Opetion;
	do
	{
		system("cls");
		PrintOpetionOnTheScreen();

		Opetion = ReadOpetionFromUser();
		programExcuation(Opetion);

	} while (Opetion != enProcessTypes::Exit);

}

int main()
{

	ShowMainMenu();

	cout << endl;
	return 0;
}

