#include "fstream"
#include "iostream"
#include "istream"
#include <string>

using namespace std;

struct EngRuDictionary
{
	char englishWord[10];
	char russianWord[10];
};

struct book
{
	char Fam[30];
	char Name[15];
	int year;
};
//чтение из текстового файла записи типа book, формирование и запись в двоичный
//функция записи в файл значения типа book
void create_bin_file(ifstream& ft, ofstream& fb)
{
	book x;
	while (!ft.eof())
	{
		ft >> x.Fam;	//заполнение Х
		ft >> x.Name;
		ft >> x.year;
		ft.get();
		//Запись Х в дв.файл
		fb.write((char*)&x, sizeof(book));
	}
	ft.close();
	fb.close();
}
//вывод записей двоичного файла
void out_bin_file(ifstream& fb)
{
	book x;
	//чтение из файла всей записи 
	while (fb.read((char*)&x, sizeof(book)))
	{
		cout << x.Fam;
		cout << x.Name;
		cout << x.year;
		
	}
	fb.close();
}
int main()
{
	system("chcp 1251 > null");
	ifstream ft("C:\\Users\\defox\\Desktop\\ggg.txt", ios::in);
	string n1, n2;
	ft >> n1 >> n2;
	cout << n1 << n2;
	
	
	
	return 0;
}
