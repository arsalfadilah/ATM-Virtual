#include<iostream>
using namespace std;

void menuAwal();
int pilihMenu();
void CreateAccount();
void login(string user, string pass);
void menuCstmr();
void menuAdmn();
void infoAccountCstmr();
void setAccountCstmr();
bool searchInFile(string user);

//variabel global
struct cstmr{
    string UserName;
    string Password;
    float saldo;
    int NoRek;
}data;

int main(){
    //kebutuhan data :
    int jnsCstmr, fitur;
    string UserName, Password;

    //Algoritma :
    menuAwal();
    jnsCstmr = pilihMenu();
    switch(jnsCstmr){
        case 1: CreateAccount();break;
        case 2:
            login(UserName, Password);
            if(UserName == "admin" && Password=="admin"){
                menuAdmn();
            } else {
                menuCstmr();
            }
            break;
        default: cout<<"\nOps Your Choose isnt Right\n";main();
    }

    return 0;
}

void menuAwal(){
    cout<<"Menu"<<endl;
    cout<<"1. Create Account\n";
    cout<<"2. Login"<<endl;
}

int pilihMenu(){
    int pilih;

    cout<<"\nChoose : ";cin>>pilih;

    return pilih;
}

void CreateAccount(){
    string tmpPassword;
    int jmlhData=0;
    bool succes=true;
    char c;
    FILE *fyp;
    FILE *ftp;
    fyp = fopen("data.dat", "ab"); // a --> write appending, r-->read, w-->write
    ftp = fopen("data.dat", "rb"); // a --> write appending, r-->read, w-->write

    while(succes){
        cout<<"Username : ";cin>>data.UserName;
        if(searchInFile(data.UserName)){
            cout<<"Password : ";cin>>data.Password;
            cout<<"Konfirmasi Password : ";cin>>tmpPassword;
            cout<<"Saldo Awal : ";cin>>data.saldo;
        }
    }
    //Membuat No. Rekening berdasar jumlah account yang telah terdaftar
    while(fread(&data, sizeof(struct cstmr), 1, ftp)){
        jmlhData++;
    }

    data.NoRek = 100000 + jmlhData;
    cout<<"No. Rekening : "<<data.NoRek;

    fclose(ftp);

    if(data.Password==tmpPassword && fwrite(&data, sizeof(struct cstmr), 1, fyp)){
        cout<<"\nCongratulation Your Account Has Been Created !\n"<<endl;
        fclose(fyp);
        main();
    } else {
        cout<<"\nOh I'M Sorry, Your Account Hasnt Save\n";
        fclose(fyp);
    }
}

void login(string user, string pass){
    bool success=true;
    string UserName;
    string Password;

    FILE *flogin;
    flogin=fopen("data.dat", "rb");

    //Algoritma :
    while(success){
        cout<<"Username : ";cin>>UserName;
        cout<<"Password : ";cin>>Password;

        while(fread(&data, sizeof(struct cstmr), 1, flogin) && success){
            if(data.UserName==UserName && data.Password==Password){
                cout<<"Login Success !\n";
                fclose(flogin);
                success = false;
            }
        }
        if(success){
           cout<<"Your Username/Password is Wrong"<<endl;
        }
    }

}

void menuAdmn(){
    int pilihan;

    cout<<"Menu Admin"<<endl;
    cout<<"1. Info Account Customer\n";
    cout<<"2. Setting Account Customer";

    cout<<"\nChoose : ";cin>>pilihan;

    switch(pilihan){
        case 1: infoAccountCstmr(); break;
        case 2: setAccountCstmr(); break;
        default:
            cout<<"Wrong Input !";
            menuAdmn();
    }

}

void infoAccountCstmr(){
    FILE *infoFile;
    string UserName;
    int pilih, no=1;

    cout<<"\nInfo Account Customer\n";
    cout<<"1. Search By UserName\n";
    cout<<"2. See All\n";

    cout<<"Choose : ";cin>>pilih;

    infoFile=fopen("data.dat", "rb");

    switch(pilih){
    case 1:
        cout<<"Username : ";cin>>UserName;
        while(fread(&data, sizeof(struct cstmr), 1, infoFile)){
            if(data.UserName==UserName){
                cout<<"Password : "<<data.Password<<"\n";
                cout<<"No. Rek  : "<<data.NoRek<<"\n";
                cout<<"Saldo    : "<<data.saldo<<"\n";
            }

        } break;
    case 2:
        while(fread(&data, sizeof(struct cstmr), 1, infoFile)){
            cout<<"Username : "<<data.UserName<<"\n";
            cout<<"Password : "<<data.Password<<"\n";
            cout<<"No.Rek   : "<<data.NoRek<<"\n";
            cout<<"Saldo    : "<<data.saldo<<"\n";
        }break;
    default:
        cout<<"Wrong Input Try Again !";
        infoAccountCstmr();
    }
}

void setAccountCstmr(){
    string UserName;
    int pilih;

    cout<<"Username : ";cin>>UserName;
    cout<<"What do u want to :\n";
    cout<<"1. Change Password\n";
    cout<<"2. Delete Account";
    cout<<"Choose : ";cin>>pilih;
}


void menuCstmr(){
    cout<<"Belum jadi";
}

bool searchInFile(string user){
    struct tem{
        string UserName;
        string Password;
        float saldo;
        int NoRek;
    }srchData;

    FILE *searchFile;
    searchFile = fopen("data.dat", "rb");

    while(fread(&srchData, sizeof(struct tem), 1, searchFile)){
        if(user==srchData.UserName){
            return true;
        }
    }

    fclose(searchFile);

    return false;

}
