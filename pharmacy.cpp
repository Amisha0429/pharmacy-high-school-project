#include<fstream.h> //header files
#include<conio.h>   //for clrscr,getch etc
#include<string.h>  //for string operations
#include<process.h> //for macros and declarations
#include<stdio.h>   //memory allocation and process control
#include<ctype.h>   //for uppercase function(toupper)

class medicine  //to store list of names of medicines and categories
{
   public:
   char s[5][40],sub[5][5][40];
   medicine()         //constructor 
    {
     strcpy(sub[0][0],"Paracetemol");
     strcpy(sub[0][1],"Guaifenesin");
     strcpy(sub[0][2],"Vicks");
     strcpy(sub[0][3],"Benylin\t");
     strcpy(sub[0][4],"Delsym");
     strcpy(sub[1][0],"Sudafed");
     strcpy(sub[1][1],"Synex spray");
     strcpy(sub[1][2],"Synex capsule");
     strcpy(sub[1][3],"Vicks 44");
     strcpy(sub[1][4],"Otrivin\t");
     strcpy(sub[2][0],"Cepacol");
     strcpy(sub[2][1],"Chloraseptic");
     strcpy(sub[2][2],"Tylenol");
     strcpy(sub[2][3],"Advil Motrin");
     strcpy(sub[2][4],"Aleve");
     strcpy(sub[3][0],"Benadryl");
     strcpy(sub[3][1],"Chlor-Trimeton");
     strcpy(sub[3][2],"Dimetapp");
     strcpy(sub[3][3],"Tavist\t");
     strcpy(sub[3][4],"Claritin");
     strcpy(sub[4][0],"Emetrol");
     strcpy(sub[4][1],"Pepto Bismol");
     strcpy(sub[4][2],"Enfalyte");
     strcpy(sub[4][3],"Pedialyte");
     strcpy(sub[4][4],"Bonine\t");

     strcpy(s[0],"FOR COUGH\t");
     strcpy(s[1],"FOR DECONGESTION\t");
     strcpy(s[2],"FOR SORE THROAT\t");
     strcpy(s[3],"FOR ALLERGIES\t");
     strcpy(s[4],"FOR NAUSEA OR VOMITING");

}     //end of constructor
};   //end of class

class userlist  //to store list of users
{
  public:
  int no;
  char users[100][50];
};


class user  //to store account details
{
  public:
   int sbj[5][7],totp,totr;
   char password[20];
   void showpb()
     {
       cout<<"\n\n\n\n\n\n 'P' Purchase\n 'B' Back";
     }
};

void show()
{
cout<<"\n\n\n\n\n\tPress any of the keys given above!";
} 

void show2()
{
cout<<"\n\n\n\n\n\tPress any key to back!";
}

void setdefault(user &usr)
{
  int i,j;
  for(i=0;i<5;i++)
   {
     for(j=0;j<7;j++)
     {
      usr.sbj[i][j]=0;
     }
   }
  usr.totp=0;
  usr.totr=0;
}

void notification(user &u)
{
   clrscr();
   ofstream f("MEDLIST");
   f.write((char *) &u,sizeof(u));
   f.close();
   cout<<"\n\n\n\n\n\n\n\tThank you for your purchasing this medicine. ";
   cout<<"\tNow press any key to exit";
   getch();
   exit(0);
}

void uppercase(char *a)
{
   for(int i=0;a[i]!='\0';i++)
     {
       a[i]=toupper(a[i]);
     }
}

void namecutter(char name[])
{
   userlist u;
   char temp[50];
   int i;
   ifstream fi("USERLIST");
   fi.read((char *) &u,sizeof(u));
   fi.close();
   for(i=0;i<u.no-1;i++)
    {
      if(strcmp(u.users[i],name)==0)
      {
        strcpy(temp,u.users[i]);
        strcpy(u.users[i],u.users[i+1]);
        strcpy(u.users[i+1],temp);
      }
    }
  u.no--;ofstream fo("USERLIST");
  fo.write((char *) &u,sizeof(u));
  fo.close();
}


int crtusr()
{
   clrscr();
   char name[50],reply;
   ifstream fi;
   user u;
   userlist list;
   fi.open("USERLIST");
   fi.read((char *) &list,sizeof(list));
   fi.close();
   if(list.no==99)
     { clrscr();
       cout<<"\n\tYou can't create any account.\n\t";
       cout<<"Since the accoutn list is full,\n\tso you have to";
       cout<<" delete an account";
       show2();
       getch();
       return 0;
     }
   cout<<"\n Enter your name(max 49 characters):\n ";
   page2:
   cin.getline(name,49);
   uppercase(name);
   if(name[0]=='\0'||name[0]==' ')
     {
       clrscr();
       cout<<"\n Please enter a valid name:";goto page2;
     }
   for(int i=0;name[i]!='\0';i++)
     {
       if(name[i]=='\\'||name[i]=='/'||name[i]==':'||name[i]=='*'||name[i]=='?'||name[i]=='\"'||name[i]=='<'||name[i]=='>'||name[i]=='|')
         { clrscr();
           cout<<"\n Please enter a valid name:";goto page2;
         }
     }
   fi.open(name);
   if(fi.good())
    {
     clrscr();
     cout<<"\n The name you have entered is already present!";
     cout<<"\n Please enter another:\n ";goto page2;
     }
   fi.close();
   page:  
   clrscr();
   cout<<"\n Do you want to add a password? (y/n):";
   reply=getch();
   if(reply=='Y'||reply=='y')
    { clrscr();
      cout<<"\n Enter your password(max 19 characters):\n ";
      cin.getline(u.password,19);
    }
   else if(reply=='N'||reply=='n')
    { strcpy(u.password,"########");
    }
   else
   { goto page;}
   setdefault(u);
   ofstream fo(name);
   fo.write((char *) &u,sizeof(u));
   fo.close();
   strcpy(list.users[list.no],name);
   list.no++;
   fo.open("USERLIST");
   fo.write((char *) &list,sizeof(list));
   fo.close();
   clrscr();
   cout<<"\n\n\tCongratulations! ";
   cout<<"You have created your account of name:\n\t'"<<name<<"'";
   show2();
   getch();
   return 0;
}



void chkusrlst()
{
  ifstream usrlst;
  usrlst.open("userlist");
  if(!usrlst.good())
   {
    ofstream fo("userlist");
    userlist list;
    list.no=0;
    fo.write((char *) &list,sizeof(list));
    fo.close();
   }
  usrlst.close();
}

void chkmedlst()
{
  ifstream medlst;int i,j;
  medlst.open("medlist");
  if(!medlst.good())
   {
    ofstream fo("medlist");
    user mdlst;
    for(i=0;i<5;i++)
     {
       for(j=0;j<5;j++)
       {
         mdlst.sbj[i][j]=1000;
       }
     }
    for(i=0;i<5;i++)
     {
      mdlst.sbj[i][5]=0;
      mdlst.sbj[i][6]=0;
     }
  mdlst.totp=0;
  mdlst.totr=0;
  fo.write((char *)&mdlst,sizeof(mdlst));
  fo.close();
   }
  medlst.close();
}


int showmeds()
{
  user guest;
  medicine sb;
  char i,k,ch,ch1,ch2;
  int x,y,j;
  page1:  
  clrscr();
  ifstream fi("Medlist");
  fi.read((char *) &guest,sizeof(guest));
  fi.close();cout<<"\n\n\n\n\n\n\n";
   for(x=0;x<5;x++)
     {
       cout<<" '"<<x+1<<"' "<<sb.s[x]<<"\n";
     }
  cout<<" 'B' Back";
  show();
  ch=getch();
  for(i='1',x=0;i<='5';i++,x++)
     {
       page2:  
       clrscr();
       if(ch==i)
         {
          cout<<"\n\n\n\t\t"<<sb.s[x]<<"\n\n\n\n";
          for(j=0;j<5;j++)
         {
          cout<<" \'"<<j+1<<"\' "<<sb.sub[x][j]<<"\t";
          cout<<guest.sbj[x][j]<<" remaining\n";
         }
          cout<<" 'B' Back";show();
          ch1=getch();
          for(k='1',y=0;k<='5';k++,y++)
         {
          if(ch1==k)
        {
          page3:  
          clrscr();
          cout<<"\n\t\t\t\t"<<sb.sub[x][y];
          guest.showpb();
          show();
          ch2=getch();
          if(ch2=='P'||ch2=='p')
           {
               if(guest.sbj[x][y]>0)
               { guest.totp++;
                 guest.sbj[x][5]++;
                 guest.sbj[x][y]--;
                 notification(guest);
               }
               else
               {
                clrscr();
                cout<<"\n\n\tYou can't purchase this medicine.\n\tMake ";
                cout<<"sure that no. of this medicine\n\tin ";
                cout<<"this shop is greater than zero.";
                show2();
                getch();
                goto page2;
               }
           }
           else if(ch2=='B'||ch2=='b')
           { goto page2;}
           else{ goto page3;}
            break;
      }
   }
    if(ch1=='B'||ch1=='b')
    { goto page1;}
    else{ goto page2;}
   }
  }
    if(ch=='B'||ch=='b')
    { return 1;}
    else{ goto page1;}
}





void pur_ret(char name[])
{
  clrscr();
  user u;
  medicine s;
  ifstream fi(name);
  int i;
  fi.read((char *) &u,sizeof(u));fi.close();
  cout<<"\n\n\n\n TYPE\t\tPurchased\tReturned\n\n\n";
    for(i=0;i<5;i++)
      {
        cout<<" "<<i+1<<"."<<" "<<s.s[i]<<"\t"<<u.sbj[i][5];
        cout<<"\t\t"<<u.sbj[i][6]<<"\n";
      }
  cout<<" 6. "<<"Total\t\t"<<u.totp<<"\t\t"<<u.totr;show2();getch();
}

  







void showuserlist()
{
  clrscr();
  int i;
  userlist list;
  ifstream fi("USERLIST");
  fi.read((char *) &list,sizeof(list));fi.close();
   for(i=0;i<list.no;i++)
    {
      cout<<"\n "<<i+1<<". "<<list.users[i];
    }
  show2();
  getch();
}



int openacc()
{
  user u,mdlst;
  userlist list;
  char name[50],passw[20],reply;
  ofstream fo;
  page1:
  clrscr();
  cout<<"\n Enter your account name:\n ";
  cin.getline(name,49);
  uppercase(name);
  ifstream fi(name);
  if(!fi.good())
   { pagename:
     clrscr();
     cout<<"\n\n Wrong account name!\n Enter again?(y/n)\n ";
     reply=getch();
     if(reply=='y'||reply=='Y')
      { goto page1;}
     else if(reply=='n'||reply=='N')
      { return 0;}
     else{ goto pagename;}
   }
  fi.read((char *) &u,sizeof(u));
  fi.close();
  fi.open("USERLIST");
  fi.read((char *) &list,sizeof(list));
  fi.close();
  int flag=0;
   for(int s=0;s<list.no;s++)
   {
    if(!strcmp(name,list.users[s]))
    { flag=1;break;}
   }
  if(flag==0)
  { strcpy(list.users[list.no],name);
    list.no++;
    fo.open("USERLIST");
    fo.write((char *) &list,sizeof(list));
    fo.close();
  }
  if(!strcmp(u.password,"########"))
   { goto page3;}
  page2:
  clrscr();
  cout<<"\n Enter your password:\n ";
  cin.getline(passw,19);
   if(strcmp(u.password,passw))
    { pagepass:
      clrscr();
      cout<<"\n\n Wrong password!\n Enter again?(y/n)\n ";
      reply=getch();
      if(reply=='y'||reply=='Y')
        { goto page2;}
      else if(reply=='n'||reply=='N')
        { return 0;}
      else
        { goto pagepass;}
     }
   page3: clrscr();
   fi.open("MEDLIST");
   fi.read((char *) &mdlst,sizeof(mdlst));
   fi.close();
   cout<<"\n\n\n\tWelcome "<<name;
   cout<<"\n\n\n\n '1' Purchase medicines\n '2' No. of medicines";
   cout<<" you are having\n '3' No. of medicines purchased";
   cout<<"by you\n '4' Add/modify password\n '5' Remove password\n ";
   cout<<"'6' Delete your account\n 'B' Back";show();reply=getch();
   if(reply=='1')
    {
      medicine sb;
      char i,k,ch,ch1,ch2;
      int x,y,j;
      page31:  
      clrscr();
      cout<<"\n\n\n\n\n\n\n";
      for(x=0;x<5;x++)
     {
      cout<<" '"<<x+1<<"' "<<sb.s[x]<<"\n";
     }
      cout<<" 'B' Back";
      show();
      ch=getch();
      for(i='1',x=0;i<='5';i++,x++)
      {
        page32:  
        clrscr();
        if(ch==i)
         {
           cout<<"\n\n\n\t\t"<<sb.s[x]<<"\n\n\n\n";
           for(j=0;j<5;j++)
            {
             cout<<" \'"<<j+1<<"\' "<<sb.sub[x][j]<<"\t";
             cout<<mdlst.sbj[x][j]<<" remaining\n";
            }
           cout<<" 'B' Back";
           show();
           ch1=getch();
           for(k='1',y=0;k<='5';k++,y++)
             {
              if(ch1==k)
               {
                page33:  
                clrscr();
                cout<<"\n\t\t\t\t"<<sb.sub[x][y];
                u.showpb();
                cout<<"\n 'R' Return";show();
                ch2=getch();
                if(ch2=='P'||ch2=='p')
                 {
                  if(mdlst.sbj[x][y]>0)
                   {
                      u.totp++;
                      mdlst.totp++;
                      u.sbj[x][5]++;
                      mdlst.sbj[x][5]++;
                      u.sbj[x][y]++;
                      mdlst.sbj[x][y]--;
                      fo.open("MEDLIST");
                      fo.write((char *) &mdlst,sizeof(mdlst));
                      fo.close();
                      fo.open(name);
                      fo.write((char *) &u,sizeof(u));
                      fo.close();
                      clrscr();
                      cout<<"\n\n\tOK! You have purchased this book";
                   }
                  else
                  {
                    clrscr();
                    cout<<"\n\n\tYou can't purchase this medicine.\n\tMake ";
                    cout<<"sure that quantity of this medicine\n\tin ";
                    cout<<"this shop is greater than zero.";
                   }
                  show2();
                  getch();
                 goto page32;
             }
            else if(ch2=='r'||ch2=='R')
          {
             if(u.sbj[x][y]>0)
             {
              u.totr++;
              mdlst.totr++;
              u.sbj[x][6]++;
              mdlst.sbj[x][6]++;
              u.sbj[x][y]--;
              mdlst.sbj[x][y]++;
              fo.open("BOOKLIST");
              fo.write((char *) &mdlst,sizeof(mdlst));
              fo.close();
              fo.open(name);
              fo.write((char *) &u,sizeof(u));
              fo.close();
              clrscr();
              cout<<"\n\n\tOK! You have returned this medicine";
             }
         else
             {
              clrscr();
              cout<<"\n\n\tYou can't return this medicine.\n\tMake ";
              cout<<"sure that no. of medicine this shop and \n\tyou";
              cout<<" are having is greater than zero.";
             }
         show2();
         getch();
         goto page32;
         }
     else if(ch2=='B'||ch2=='b')
     { goto page32;}
     else{ goto page33;}
       }
      }
     if(ch1=='B'||ch1=='b'){ goto page31;}
     else{ goto page32;}
     }
    }
   if(ch=='B'||ch=='b'){ goto page3;}
   else{ goto page31;}
   }
   else if(reply=='2')
    {
      clrscr();
      int i,j;
      for(i=0;i<5;i++)
       { medicine sb;
         cout<<"\n "<<sb.s[i]<<"\n";
         for(j=0;j<5;j++)
         {
            cout<<"  "<<j+1<<". "<<sb.sub[i][j]<<"\t"<<u.sbj[i][j];
            cout<<" remaining\n";
         }

       }
     show2();
     getch();
     goto page3;
      }
      else if(reply=='3')
       { pur_ret(name);
         goto page3;
       }
      else if(reply=='4')
      { clrscr();
        cout<<"\n Enter new password(max 19 characters):\n ";
        cin.getline(passw,19);
        strcpy(u.password,passw);
        clrscr();
        cout<<"\n\tPassword modified succesfully!";
        show2();
        getch();
        fo.open(name);
        fo.write((char *) &u,sizeof(u));
        fo.close();
        goto page3;
      }
    else if(reply=='5')
     { page35:
       clrscr();
       cout<<"\n Remove password?(y/n):";
       reply=getch();
       if(reply=='Y'||reply=='y')
        { strcpy(u.password,"########");
          fo.open(name);
          fo.write((char *) &u,sizeof(u));
          fo.close();
          clrscr();
          cout<<"\n\tPassword removed successfully!";
          show2();
          getch();
          goto page3;
        }
      else if(reply=='N'||reply=='n'){ goto page3;}
      else{ goto page35;}
     }
      else if(reply=='6')
       { page36: 
         clrscr();
         cout<<"\n Do you want to delete your account?(y/n):";
         reply=getch();
         if(reply=='Y'||reply=='y')
          { clrscr();
            remove(name);
            cout<<"\n\tYour account is deleted successfully!";
            show2();
            getch();
            namecutter(name);
            return 0;
           }
         else if(reply=='N'||reply=='n'){ goto page3;}
         else{goto page36;}
       }
         else if(reply=='b'||reply=='B')
          { page3b:
            clrscr();
            cout<<"\n Do you want to exit from your account?(y/n):";
            reply=getch();
            if(reply=='Y'||reply=='y'){ return 0;}
            else if(reply=='N'||reply=='n'){ goto page3;}
            else{ goto page3b;}
           }
         else{ goto page3;}
}

int main()
{
  chkusrlst();
  chkmedlst();
  mpage:
  clrscr();
  char ch;
  cout<<"\n\n\t\t\t PHARMACY \n\n\n\n\n '1' See the ";
  cout<<"lists of medicines\n '2' Create an account\n '3' Open an account";
  cout<<"\n '4' See about no. of medicines purchased\n";
  cout<<" '5' See the list of accounts\n '6' Quit";show();
  ch=getch();
  switch(ch)
  {
    case '1': if(showmeds()==1)
              {  goto mpage;
              }
    break;
    case '2': crtusr();
    goto mpage;
    case '3': openacc();
    goto mpage;
    case '4': pur_ret("MEDLIST");
    goto mpage;
    case '5': showuserlist();
    goto mpage;
    case '6': return 0;
    default : goto mpage;
  }
  getch();
  return 0;
}
