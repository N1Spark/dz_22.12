#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#pragma comment(lib, "urlmon.lib")
using namespace std;

int main()
{
	setlocale(0, "ru");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	// the URL to download from 
	string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";
	string srcURL2 = "https://api.privatbank.ua/p24api/pubinfo?exchange&coursid=5";
	// the destination file 
	string destFile = "Gov.txt";
	//// URLDownloadToFile returns S_OK on success 
	if (S_OK == URLDownloadToFileA(NULL, srcURL.c_str(), destFile.c_str(), 0, NULL))
	{
		cout << "Saved to " << destFile << "\n";
	}
	else cout << "Fail!\n";
	fstream File_ex;
	File_ex.open("Gov.txt");
	string  buf;
	while (true)
	{
		if (File_ex.eof())
			break;
		else
		{
			getline(File_ex, buf);
			if (buf.find(":978") != -1)
			{
				cout << "Euro: ";
				for (int i = buf.find(":978") + 29; buf[i] != ','; i++)
					cout << buf[i];
				cout << " grn;" << endl;
			}
			if (buf.find(":840") != -1)
			{
				cout << "USD: ";
				for (int i = buf.find(":840") + 38; buf[i] != ','; i++)
					cout << buf[i];
				cout << " grn." << endl;
			}

		}
	}
	File_ex.close();
	string dest2File = "Priv.txt";
	if (S_OK == URLDownloadToFileA(NULL, srcURL2.c_str(), dest2File.c_str(), 0, NULL))
	{
		cout << "\nSaved to " << dest2File << "\n";
	}
	else cout << "Fail!\n";
	File_ex.open("Priv.txt");
	while (true)
	{
		if (File_ex.eof())
			break;
		else
		{
			getline(File_ex, buf);
			if (buf.find("EUR") != -1)
			{
				cout << "Euro: buy= ";
				for (int i = buf.find("EUR") + 29; buf[i + 1] != ','; i++)
					cout << buf[i];
				cout << " grn;";
				cout << " sell= ";
				for (int i = buf.find("EUR") + 29; buf[i + 1] != ','; i++)
					cout << buf[i];
				cout << " grn." << endl;
			}
			if (buf.find("USD") != -1)
			{
				cout << "USD: buy= ";
				for (int i = buf.find("USD") + 29; buf[i + 1] != ','; i++)
					cout << buf[i];
				cout << " grn;";
				cout << " sell= ";
				for (int i = buf.find("USD") + 29; buf[i + 1] != ','; i++)
					cout << buf[i];
				cout << " grn." << endl;
			}
		}
	}
}