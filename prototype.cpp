#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

struct antrian{
    string music;
    antrian *next;
}; 
antrian *head, *tail, *newNode, *cur, *del, *bantu, *hapusNode;

void MusicList(string *music);
void openFile(string *music);
int countAntrian();
bool isEmpty();
void inputBelakang(string music);
void HapusDepan();
void display();
void searching();
void clear();

void add_music();

int main (){
    int pili;
    int pil;
    string *music = new string[15];


    do{ 
        openFile(music);
        MusicList(music);                            //!Contoh aja (Dihapus klo mau dimodif)
        cout << "1.Input" <<endl;
        cout << "2.Tampil" <<endl;
        cout << "3.Cari" <<endl;
        cout << "4.Keluar" <<endl;
        cout << "Masukkan pilihan: "; cin >> pili;

        if (pili == 1){
            cout << "\nmasukan data: "; cin >> pil;
            inputBelakang(music[pil-1]);
        }else if(pili == 2){
            display();
        }else if (pili == 3){
            searching();
        }
        else if(pili == 4){
            exit(0);
        }
    }while (pili != 4);

    return 0;    
}

//!List Music
void MusicList(string *music){           //!Masih progress nyari daftar musicnya
    cout << "-------------------- Daftar Lagu --------------------" <<endl;
    for(int i{}; i<15; i++)
    {
        cout << i+1 << ". " << *music << '\n';
        music++;
    }
    cout << "-----------------------------------------------------" <<endl <<endl;
}
void openFile(string *music)
{
    fstream listMusic;

    listMusic.open("List_music.txt");

    while(!listMusic.eof())
    {
        getline(listMusic, *music);
        music++;
    }
    listMusic.close();
}
//!Linked List
void searching(){
    antrian *temp;
    temp=head;
    int i=1;

    string caridata;
    int ketemu = 0;
    if(isEmpty!=NULL){
        cout<<"Masukan Music yang Ingin dicari : \n";
        cin.ignore();
        getline(cin, caridata);
        cout<<"Music yang anda cari \n";
        while(temp !=NULL){
            temp -> music;
            if (caridata==temp->music){
                cout<<"Judul\t" << i << ": " << temp->music<< endl;
        //        cout<<"Artis\t : "<<temp->artis<<endl;
                ketemu=1;
                i++;
            }
            temp=temp->next;
        }
        cout<<"==================================\n";
        if(ketemu==0){
            cout<<"Music yang anda cari tidak terdaftar \n";
            cout<<"==================================\n";
        }
    }
}
void inputBelakang(string music){
    if(isEmpty()){
        head = new antrian();
        head->music = music;
        head->next = NULL;
        tail = head;
        cout << "Music berhasil ditambahkan ke daftar antrian belakang" << endl <<endl;
    } else{
        newNode = new antrian();
        newNode->music = music;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        cout << "Music berhasil ditambahkan ke daftar antrian belakang" << endl <<endl;
    }
}
void HapusDepan(){
    if(isEmpty()){
        cout << "Antrian kosong" << endl;
    } else{
        del = head;
        head = head->next;
        del->next = NULL;
        delete del; 
        cout << "Music skipped" << endl;
    }
}
int countAntrian(){
    if(head == NULL){
        return 0;
    } else{
        int counter = 0;
        cur = head;
        while(cur != NULL){
            counter++;
            cur = cur->next;
        }
        return counter;
    }
}
bool isEmpty(){
    if(countAntrian() == 0){
        return true;
    } else{
        return false;
    }
}
void display(){
    cout << "\nData Antrian: " << endl;
    if(isEmpty()){
        cout << "Antrian kosong" << endl;
    } else{
        cout << "Jumlah data: " << countAntrian() << endl;
        cur = head;
        int nomor = 0;
        while(cur != NULL){
            cout << nomor+1 << ". " << cur->music << endl;
            cur = cur->next;
            nomor++;
        }
    }
    cout << endl;
}
void clear(){
    if(isEmpty()){
        cout << "Antrian Kosong" << endl;
    } else {
        head->next = NULL;
        head = NULL;
        cout << "Menghapus seluruh data pada Antrian" << endl;
        
        cur = head;
        while(cur != NULL){
            del = cur;
            cur = cur->next;
            
            // menghapus node
            del->next = NULL;
            delete del;
        }
        head = NULL;
    }
}