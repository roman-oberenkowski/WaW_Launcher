#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>

using namespace std;

ifstream modlist;   //txt with mod folders
ifstream notesRead; //to read notes from folders
ofstream notesWrite; //to write
//-------------------functions at the end
void refresh();
void modlistOpen();
void displayList();
void getParams();
void help();
void notesAdd(string modname);
void showLaunchParam();
string getModName(int nr);
//-----------------------
int maxModNumber;
string input="";
string launchCommand="";    //what command to send;
string temp;
string modName;//mod folder name
//----------------------
int main()
{
    cout.fill('0');     //fill to three in the first column using 0s
    bool error;
    bool notesEdit;
    bool mods;
    bool fullscreen;

    while(1)
    {
        //vars---
        notesEdit=false;
        error=false;
        mods=false;
        //fullscreen=false;  added false to the find f

        //---
        system("cls");
        displayList();
        getParams();
        //notes edit
        if(input.find('n')!=string::npos)
        {
            notesEdit=true;
            input.erase(input.find('n'),1);
        }
        //quit
        if(input.find('q')!=string::npos)
        {
            return 0;
        }
        //refresh - noLaunch
        while(input.find('r')!=string::npos)
        {
            refresh();
            displayList();
            getParams();
        }
        //help - noLaunch
        while(input.find('h')!=string::npos)
        {
            help();//waits to finish
            system("cls");
            displayList();
            getParams();
        }
        //t4m
        if(input.find('t')!=string::npos)
        {
            launchCommand="t4m.exe ";
            input.erase(input.find('t'),1);
        }
        else
            launchCommand="CoDWaW.exe ";
        //fullscreen
        if(input.find('f')!=string::npos)
        {
            launchCommand+="+seta r_fullscreen \"1\" ";
            input.erase(input.find('f'),1);
            fullscreen=true;
        }
        else
        {
            launchCommand+="+seta r_fullscreen \"0\" ";
            fullscreen=false;
        }
        //add mods folder, set appdata to game folder :)
        launchCommand+="+set fs_localAppData %cd% ";
        //-----------
        if(input.size()>0)//some input
        {
            mods=true; //enable the notes dialog
            int modNr=atoi(input.c_str());
            if(modNr<maxModNumber&&modNr>0)//numer ok
            {
                modName=getModName(modNr);
                if(notesEdit)//edit the notes in notepad
                {
                    string pathn="notepad mods\\"+modName+"\\_"+modName+"_notes.txt";
                    cout<<"notes "<<pathn<<endl;
                    system(pathn.c_str());
                    error=1;;
                }
                else//launch the game
                {
                    //launchCommand+="+set fs_game \"mods\\"+temp+"\" ";
                    launchCommand+="+set fs_game \"mods/"+modName+"\" ";
                }

            }
            else
            {
                cout<<"Invalid number!"<<endl;
                mods=false;
                error=1;
            }
        }
        else //blank input -> no mods
        {
            cout<<"Launching without mods"<<endl;
            mods=false;
        }
        if(!error)
        {
            if(fullscreen)
            {
                cout<<"Fullscreen Mode!"<<endl;
                showLaunchParam();
                system(launchCommand.c_str());
            }
            else //windowed mode
            {
                cout<<"Windowed Mode!"<<endl;
                cout<<"+Launching borderless gaming mode!"<<endl;
                system("_borderlessgaming.bat");
                showLaunchParam();
                system(launchCommand.c_str());
                cout<<"Stopping borderless gaming mode!"<<endl;
                system("taskkill /im BorderlessGaming.exe");
            }
            if(mods)
                notesAdd(modName);
        }
    }
}

//------------------------------------------FUNCTIONS----------------------------------------
void getParams()
{
    cout<<"h-help|r-refresh|q-quit"<<endl;
    input="";               //clear input
    getline(cin,input);     //read user input
}
void displayList()
{
    modlistOpen();
    string modName;
    string modNotesPath;
    int i=1;  //mod number
    while(!modlist.eof())   //read the modlist line by line to the end
    {
        getline(modlist, modName);
        if(i!=1)
            cout<<endl;     //new line only when not the first one
        if(modName.size()>0)
        {
            cout<<setw(3)<<i<<" - ";
            modNotesPath="mods\\"+modName+"\\_"+modName+"_notes.txt"; //reused modName as temp variable for notes...
            notesRead.open(modNotesPath.c_str());
            if(notesRead)
            {
                getline(notesRead,modName);  //get the name of the mod
                getline(notesRead,modNotesPath);  //get the notes about the mod
                cout<<modName<<" | "<<modNotesPath;
            }
            else
            {
                cout<<modName;
                notesRead.clear();
            }
            notesRead.close();
        }
        i++;
    }
    modlist.close();
    maxModNumber=i-1; // -1 to take back the last count
}
void modlistOpen()
{
    modlist.open("_modlist.txt");
    if (!modlist)
    {
        //missing file -> create using refresh
        modlist.close();    //close
        refresh();          //generate
        modlist.clear();    //clear the open error
        modlist.open("_modlist.txt");   //open again
    }
}
void refresh()
{
    system("cls");
    cout<<"Generating new modlist..."<<endl;
    system("dir mods /a /b >_modlist.txt");
}
void help()
{
    cout<<"TO DO";
    getch();
}
void notesAdd(string name)
{
    string path="mods\\"+name+"\\_"+name+"_notes.txt";
    cout<<"notes save to: "<<path<<endl;
    notesRead.open(path.c_str());
    if(!notesRead)
    {
        //display the question
        cout<<"there are no notes available notes for this map yet, would you like to add some?"<<endl<<"(ESC to cancel, any  other to confirm)"<<endl;
        notesRead.close();
        if(getch()!=27) //nacisn¹³ coœ innego ni¿ escape,
        {
            notesWrite.open(path.c_str());
            cout<<"OK, give us some info: "<<endl;
            cout<<"First: the full name of the MOD: ("<<name<<") "<<endl;
            getline(cin,path);       //using path as userinput
            if(path.size()<2){
                path=name;
            }
            notesWrite<<path<<endl;
            cout<<"Now your thoughts"<<endl;
            getline(cin,path);
            notesWrite<<path;
            notesWrite.close();
        }
    }
}
void showLaunchParam()
{
    cout<<"Launching waw with following parameters: "<<endl;
    cout<<launchCommand<<endl;
}
string getModName(int nr)
{
    string load;
    //searching for selected mod...
    modlist.open("_modlist.txt");
    for(int j=1; j<=nr; j++)
    {
        getline(modlist, load);
    }
    modlist.close();
    return load;
}
