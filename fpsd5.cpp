#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <list>
using namespace std;

int N = 1;
struct Music
{
    string nama;
    int count{};
};
struct antrian
{
    string music;
    antrian *next;
};
antrian *head, *tail, *newNode, *cur, *del, *bantu, *hapusNode;

void setcolor(unsigned short color);
void coordxy(int x, int y);
void loadingBar();
void MusicList(Music *music);
void openFile(Music *music);
int countAntrian();
bool isEmpty();
void inputBelakang(string music);
void HapusMusic();
void display();
void searching();
void sortCount(Music *music);
void sortAbjad();

void add_music();

int main()
{
    int pili;
    int pil;
    Music *music = new Music[15];
    openFile(music);

    do
    {
        system("cls");
        MusicList(music); //! Contoh aja (Dihapus klo mau dimodif)
        setcolor(7);
        coordxy(5,22);cout << ">>>>>>>>>>>>>>   SPOTIFIVE   <<<<<<<<<<<<<<<" << endl;
        coordxy(5,23);cout << "x==========================================x" << endl;
        setcolor(11); 
        coordxy(5,24);cout << "|\t\t Menu Playlist Music\t\t|" << endl;
        setcolor(7);
        coordxy(5,25);cout << "x==========================================x" << endl;
        coordxy(7,26);cout << " 1.Tambah playlist" << endl;
        coordxy(7,27);cout << " 2.Tampilkan playlist saat ini" << endl;
        coordxy(7,28);cout << " 3.Cari lagu di daftar playlist" << endl;
        coordxy(7,29);cout << " 4.Skip lagu" << endl;
        coordxy(7,30);cout << " 5.Lagu yang paling sering diputar" << endl;
        coordxy(7,31);cout << " 6.Sort playlist" << endl;
        coordxy(7,32);cout << " 7.Keluar playlist" <<endl;
        setcolor(11);
        coordxy(0,33);cout << "-----------------------------------------------------"<<endl;
        setcolor(7);
        coordxy(2,34);cout << "Masukkan pilihan: ";
        cin >> pili;
        setcolor(11);
        coordxy(0,35);cout << "-----------------------------------------------------"<<endl;
        setcolor(7);

        if (pili == 1)
        {
            cout << "\n  Masukan nomer lagu : ";
            cin >> pil;
            inputBelakang(music[pil-1].nama);
            music[pil-1].count++;
            loadingBar();
            coordxy(44, 28);
            system("pause");
        }
        else if (pili == 2)
        {
            display();
            system("pause");
        }
        else if (pili == 3)
        {
            searching();
        }
        else if (pili == 4)
        {
            HapusMusic();
            system("pause");
        }
        else if (pili == 5)
        {
            sortCount(music);
        }
        else if (pili == 6){
            sortAbjad();
        }
        else if (pili == 7){
            exit(0);
        }
    } while (pili != 7);
}

void coordxy(int x, int y)
{
    HANDLE consola;
    COORD posicion;

    posicion.X = x;
    posicion.Y = y;
    consola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(consola, posicion);
}
void setcolor(unsigned short color) // setcolor
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hCon,color);

}
void loadingBar()
{

    system("cls"); // cleaning the screen

    // ADDING sOME TEXT
    coordxy(44, 13);
    setcolor(11);
    cout << "LOADING...";

    // LEVEL %
    int level = 13; // it goes until 100%

    // We draw FRAME for the bar
    for (int x = 44; x < 74; x++)
    { // 2 horizontal lines
        coordxy(x, 14);
        printf("%c", 205);
        coordxy(x, 16);
        printf("%c", 205);
    }

    for (int y = 15; y < 16; y++)
    { // 2 vertical lines
        coordxy(44, y);
        printf("%c", 186);
        coordxy(74, y);
        printf("%c", 186);
    }

    // Corners of the frame

    // top left
    coordxy(44, 14);
    printf("%c", 201);
    // top right
    coordxy(74, 14);
    printf("%c", 187);
    // bottom left
    coordxy(44, 16);
    printf("%c", 200);
    // bottom right
    coordxy(74, 16);
    printf("%c", 188);

    // bar internal content
    for (int load = 45; load <= 73; load++)
    {
        coordxy(load, 15);
        printf("%c", 178); // 178 ASCII code, it is a square
        Sleep(30);         // we pause the action in every cycle, so it gives an effect of a running bar.

        // number with the loaded level
        level += 3; // we had 13 at the beginning and it adds +3 every cycle
        coordxy(58, 17);
        cout << level << "%"; // this shows the number until 100% loaded...
    }
}

//! List Music
void MusicList(Music *music)
{
    setcolor(11);
    cout << "\n-------------------- Daftar Lagu ---------------------" << endl;
    setcolor(11); cout << "|" ;
    coordxy(2,2); cout << " No. " ;
    coordxy(8,2); cout << "|";
    coordxy(21,2); cout << "Judul Lagu " ;
    coordxy(42,2); cout << "|";
    coordxy(44,2);cout << " Jumlah " << '\n';
    coordxy(53,2); cout << "|" <<endl;
    cout << "------------------------------------------------------" << endl;
    for (int i{}; i < 15; i++)
    {   
        setcolor(11); 
        coordxy(0,i+4);
        cout << "|" ;

        setcolor(7);
        coordxy(3,i+4); cout << i + 1 << ". " ;

        setcolor(11);
        coordxy(8,i+4); 
        cout << "|";

        setcolor(7);
        coordxy(11,i+4); cout << music[i].nama ;

        setcolor(11);
        coordxy(42,i+4); cout << "|";

        setcolor(7);
        coordxy(48,i+4);cout << music[i].count << '\n';

        setcolor(11);
        coordxy(53,i+4); cout << "|";

    }
    setcolor(11);
    coordxy(0,19);cout << "------------------------------------------------------" << endl
         << endl;
}
void openFile(Music *music)
{
    fstream listMusic;

    listMusic.open("List_music.txt");

    int i = 0;
    while (!listMusic.eof())
    {
        getline(listMusic, music[i].nama);
        i++;
    }
    listMusic.close();
}
//! Linked List
void searching()
{
    antrian *temp;
    temp = head;
    int i = 1;

    string caridata;
    int ketemu = 0;

    if (isEmpty != NULL)
    {
        cout << "Masukan Music yang Ingin dicari : \n";
        cin.ignore();
        getline(cin, caridata);
        coordxy(44, 28);
        loadingBar();
        system("CLS");
        setcolor(7);
        cout << "Music yang anda cari \n";
        while (temp != NULL)
        {
            if (caridata == temp->music)
            {   
                cout << "Judul\t" << i << ": " ;
                setcolor(10);cout << temp->music << endl;
                //        cout<<"Artis\t : "<<temp->artis<<endl;
                ketemu = 1;
                i++;
            }
            temp = temp->next;
            setcolor(7);
        }
        cout << "==================================\n";
        if (ketemu == 0)
        {
            setcolor(12);cout << "Music yang anda cari tidak terdaftar \n";
            setcolor(7);cout << "==================================\n";
        }
        system("pause");
    }
}
void inputBelakang(string music)
{
    if (isEmpty())
    {
        head = new antrian();
        head->music = music;
        head->next = NULL;
        tail = head;
        setcolor(10);
        cout << "Music berhasil ditambahkan ke daftar antrian belakang" << endl;
    }
    else
    {
        newNode = new antrian();
        newNode->music = music;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        setcolor(10);
        cout << "Music berhasil ditambahkan ke daftar antrian belakang" << endl;
    }
}
void HapusMusic()
{

    string YesNo;
    if (isEmpty())
    {
        cout << "\n| ------------------------------- |" << endl;
        setcolor(12);cout << "           Antrian Kosong          " << endl;
        setcolor(7);cout << "| ------------------------------- |" << endl;
    }
    else
    {
        cout << "\n| ------------------------------------- |" << endl;
        cout << "   Anda yakin mau menghapus lagu y/n : ";
        cin >> YesNo;
        if (YesNo == "Y" || YesNo == "y")
        {
            del = head;
            head = head->next;
            del->next = NULL;
            delete del;
            cout << endl;
            setcolor(12); cout << "             Lagu anda di skip         " << endl;
            setcolor(7);cout << "| -------------------------------------- |" << endl;
            N--;
        }
    }
}
int countAntrian()
{
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        int counter = 0;
        cur = head;
        while (cur != NULL)
        {
            counter++;
            cur = cur->next;
        }
        return counter;
    }
}
bool isEmpty()
{
    if (countAntrian() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void display()
{
    if (isEmpty())
    {   
        setcolor(12);
        cout << "\n Playlist kosong" << endl;
        setcolor(7);
    }
    else
    {
        cout << "\n Jumlah lagu: " << countAntrian() << endl;
        cur = head;
        int nomor = 1;
        while (cur != NULL)
        {
            setcolor(11);
            cout << "  " << nomor << ". " << cur->music << endl;
            cur = cur->next;
            nomor++;
            
        }
       setcolor(7);
    }
    cout << endl;
}
//! Sort
void sortCount(Music *music)
{
    Music temp, temp_s;
    for (int i = 0; i < 14 ; i++)
        {
            for (int j = 0; j < 14 - i; j++)
            {
                if (music[j].count < music[j + 1].count)
                {
                    temp = music[j];
                    music[j] = music[j+1];
                    music[j+1] = temp;
                }
            }
        }    
}
void sortAbjad (){
    cur = head;
    antrian *index = NULL;
    string temp;

    if (head == NULL){
        return;
    }
    else{
        while (cur != NULL)
        {
            index = cur->next;
            while (index != NULL)
            {
                if(cur->music[0] > index->music[0]){
                    temp = cur->music;
                    cur->music = index->music;
                    index->music = temp;
                }
                index = index->next;
            }
            cur = cur->next;
            
        }
        
    }
}
//!