#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct User
{
  char username[20];
  char password[20];
  char fname[31];
  char lname[31];
};

struct Admin
{
  char adusername[20];
  char adpassword[20];
  char adfname[31];
  char adlname[31];
};

struct Package
{
  char name[20];
  float price;
  int tickets;
};

struct User users[100];
struct Package num[100];
struct Admin panel[100];
int userCount = 0;
int packageCount = 0;
int adminCount = 0;

void saveInFile()
{
  FILE *fp = fopen("users.txt", "w");
  if (fp == NULL)
  {
    printf("Error opening file\n");
    return;
  }
  fprintf(fp, "%d\n", userCount);
  for (int i = 0; i < userCount; i++)
  {
    fprintf(fp, "%s %s %s %s\n", users[i].username, users[i].password,
            users[i].fname, users[i].lname);
  }
  fclose(fp);
}

void adsaveInFile()
{
  FILE *fp3 = fopen("admin.txt", "w");
  if (fp3 == NULL)
  {
    printf("Error opening file\n");
    return;
  }
  fprintf(fp3, "%d\n", adminCount);
  for (int i = 0; i < adminCount; i++)
  {
    fprintf(fp3, "%s %s %s %s\n", panel[i].adusername, panel[i].adpassword,
            panel[i].adfname, panel[i].adlname);
  }
  fclose(fp3);
}

void saveinfilePackage()
{
  FILE *fp2;
  fp2 = fopen("packageinfo.txt", "w");
  if (fp2 == NULL)
  {
    printf("Error opening file.\n");
    return;
  }
  fprintf(fp2, "%d\n", packageCount);
  for (int i = 0; i < packageCount; i++)
  {
    fprintf(fp2, "%s %f %d\n", num[i].name, num[i].price, num[i].tickets);
  }
  fclose(fp2);
}

void loadFromFile()
{
  FILE *fp = fopen("users.txt", "r");
  if (fp == NULL)
  {
    printf("No previous state is saved.\n");
    return;
  }

  fscanf(fp, "%d", &userCount);
  for (int i = 0; i < userCount; i++)
  {
    fscanf(fp, "%s %s %s %s", users[i].username, users[i].password,
           users[i].fname, users[i].lname);
  }
}

void adloadFromFile()
{
  FILE *fp3 = fopen("admin.txt", "r");
  if (fp3 == NULL)
  {
    printf("No previous state is saved.\n");
    return;
  }

  fscanf(fp3, "%d", &adminCount);
  for (int i = 0; i < adminCount; i++)
  {
    fscanf(fp3, "%s %s %s %s", panel[i].adusername, panel[i].adpassword,
           panel[i].adfname, panel[i].adlname);
  }
}

void loadPackageFromFile()
{
  FILE *fp2;
  fp2 = fopen("package_info.txt", "r");
  if (fp2 == NULL)
  {
    printf("Error opening file.\n");
    return;
  }
  fprintf(fp2, "%d\n", packageCount);
  for (int i = 0; i < packageCount; i++)
  {
    fscanf(fp2, "%s %f %d\n", num[i].name, &num[i].price, &num[i].tickets);
  }
  fclose(fp2);
}

void exitpage()
{
  printf("\n\t\t\t\t******* *     * ******* *******\n");
  printf("\t\t\t\t*        *   *     *       *   \n");
  printf("\t\t\t\t*******    *       *       *   \n");
  printf("\t\t\t\t*        *   *     *       *   \n");
  printf("\t\t\t\t******* *     * *******    *   \n");
  return;
}

void exitProgram()
{
  system("clear");
  saveInFile();
  exitpage();
  exit(0);
}

int person[3] = {1, 2, 3};

/* Checks if user exists */
int checkIndex(char username[])
{
  for (int i = 0; i < userCount; i++)
  {
    if (strcmp(username, users[i].username) == 0)
    {
      return i;
    }
  }
  return -1;
}

int adcheckIndex(char adusername[])
{
  for (int i = 0; i < adminCount; i++)
  {
    if (strcmp(adusername, panel[i].adusername) == 0)
    {
      return i;
    }
  }
  return -1;
}

int checkPackageIndex(char name[])
{
  for (int i = 0; i < packageCount; i++)
  {
    if (strcmp(name, num[i].name) == 0)
    {
      return i;
    }
  }
  return -1;
}

int addUser(struct User user)
{
  if (checkIndex(user.username) != -1)
  {
    return 0;
  }
  users[userCount] = user;
  userCount++;

  return 1;
}

int addAdmin(struct Admin panel1)
{
  if (adcheckIndex(panel1.adusername) != -1)
  {
    return 0;
  }
  panel[adminCount] = panel1;
  adminCount++;

  return 1;
}

int addPackage(struct Package num1)
{
  if (checkIndex(num1.name))
  {
    return 0;
  }
  num[packageCount] = num1;
  packageCount++;

  return 1;
}

int updateUser(char username[20], struct User user)
{
  strcpy(user.username, username);

  int idx = checkIndex(username);
  if (idx != -1)
  {
    users[idx] = user;
    return 1;
  }
  return 0;
}

int updateAdmin(char adusername[20], struct Admin panel1)
{
  strcpy(panel1.adusername, adusername);

  int aidx = adcheckIndex(adusername);
  if (aidx != -1)
  {
    panel[aidx] = panel1;
    return 1;
  }
  return 0;
}

int updatePackage(char name[20], struct Package num1)
{
  strcpy(num1.name, name);

  int pidx = checkPackageIndex(name);
  if (pidx != -1)
  {
    num[pidx] = num1;
    return 1;
  }
  return 0;
}

int deleteUser(char username[20])
{
  int idx = checkIndex(username);

  if (idx != -1)
  {
    for (int j = idx; j < userCount; j++)
    {
      users[j] = users[j + 1];
    }

    userCount--;
    return 1;
  }
  return 0;
}

int deletePackage(char name[20])
{
  int pidx = checkPackageIndex(name);

  if (pidx != -1)
  {
    for (int j = pidx; j < packageCount; j++)
    {
      num[j] = num[j + 1];
    }

    packageCount--;
    return 1;
  }
  return 0;
}

struct User *getUser(char username[20])
{
  int idx = checkIndex(username);

  if (idx != -1)
  {
    return &users[idx];
  }

  return NULL;
}

struct Admin *getAdmin(char adusername[20])
{
  int aidx = adcheckIndex(adusername);

  if (aidx != -1)
  {
    return &panel[aidx];
  }

  return NULL;
}

struct Package *getPackage(char name[20])
{
  int pidx = (checkPackageIndex(name));

  if (pidx != -1)
  {
    return &num[pidx];
  }
  return NULL;
};

struct User *getUsers()
{
  return users;
}

struct Admin *getAdmins()
{
  return panel;
}

struct Package *getPackages()
{
  return num;
}
void UserWelcomePage();
void UserSignUpPage()
{
  struct User user;

  printf("Username: ");
  scanf("%s", user.username);

  printf("Password: ");
  scanf("%s", user.password);

  printf("First Name: ");
  scanf("%s", user.fname);

  printf("Last Name: ");
  scanf("%s", user.lname);

  if (addUser(user))
  {
    UserWelcomePage();
  }
  else
  {
    printf("User already exists\n");
  }
}

void PackageListPage();

void AddListPackage()
{
  struct Package num;

  printf("Package Name: ");
  scanf("%s", num.name);

  printf("Package Price: ");
  scanf("%f", num.price);

  printf("Amount of Booking Availabe: ");
  scanf("%d", num.tickets);

  if (addPackage(num))
  {
    PackageListPage();
  }
  else
  {
    printf("User already exists\n");
  }
}
void AdminWelcomePage();

void AdminSignUpPage()
{
  struct Admin panel;

  printf("Admin Username: ");
  scanf("%s", panel.adusername);

  printf("Admin Password: ");
  scanf("%s", panel.adpassword);

  printf("Admin First Name: ");
  scanf("%s", panel.adfname);

  printf("Admin Last Name: ");
  scanf("%s", panel.adlname);

  if (addAdmin(panel))
  {
    AdminWelcomePage();
  }
  else
  {
    printf("User already exists\n");
  }
}

void UserListPage()
{
  struct User *usr = getUsers();
  for (int i = 0; i < userCount; i++)
  {
    printf("%s %s %s\n", usr[i].username, usr[i].fname, usr[i].lname);
  }
  printf("\n");
  printf("\n");
}

void AdminListPage()
{
  struct Admin *adm = getAdmins();
  for (int i = 0; i < adminCount; i++)
  {
    printf("%s %s %s\n", adm[i].adusername, adm[i].adfname, adm[i].adlname);
  }
  printf("\n");
  printf("\n");
}

void PackageListPage()
{
  struct Package *pack = getPackages();
  for (int i = 0; i < packageCount; i++)
  {
    printf("%s %f %d\n", pack[i].name, pack[i].price, pack[i].tickets);
  }
  printf("\n");
  printf("\n");
}

void SingleUserPage()
{
  char username[20];

  printf("Enter username: ");
  scanf("%s", username);

  struct User *user = getUser(username);

  if (user != NULL)
  {
    printf("%s %s %s\n", user->username, user->fname, user->lname);
  }
  else
  {
    printf("User not found\n");
  }

  printf("\n");
  printf("\n");
}

void DeleteUserPage()
{
  char username[20];

  printf("Enter the username you want to remove: ");
  scanf("%s", username);

  if (deleteUser(username))
  {
    printf("User deleted successfully\n");
  }
  else
  {
    printf("User not found\n");
  }

  printf("\n");
  printf("\n");
}

void DeletePackgePage()
{
  char name[20];

  printf("Enter the Package you want to remove: ");
  scanf("%s", name);

  if (deletePackage(name))
  {
    printf("User deleted successfully\n");
  }
  else
  {
    printf("User not found\n");
  }

  printf("\n");
  printf("\n");
}

void UpdateUserPage()
{
  struct User user;

  char username[20];

  printf("Enter the username you want to update: ");
  scanf("%s", username);

  if (checkIndex(username))
  {
    printf("User not found\n");
    return;
  }

  strcpy(user.username, username);

  printf("Password: ");
  scanf("%s", user.password);

  printf("First Name: ");
  scanf("%s", user.fname);

  printf("Last Name: ");
  scanf("%s", user.lname);

  updateUser(username, user);
}

void UpdatePackagePage()
{
  struct Package num;

  char name[20];

  printf("Enter the username you want to update: ");
  scanf("%s", name);

  if (checkPackageIndex(name))
  {
    printf("User not found\n");
    return;
  }

  strcpy(num.name, name);

  printf("Re-enter Package Name: ");
  scanf("%s", num.name);

  printf("Re-enter Package Price: ");
  scanf("%f", &num.price);

  printf("Re-enter Amount of Tickets: ");
  scanf("%d", &num.tickets);

  updatePackage(name, num);
}

int loginUser(char username[20], char password[20])
{
  struct User *usr = getUser(username);

  if (usr != NULL && strcmp(usr->password, password) == 0)
  {
    printf("Welcome to homepage.");

    return 1;
  }

  return 0;
}

int loginAdmin(char adusername[20], char adpassword[20])
{
  struct Admin *adm = getAdmin(adusername);

  if (adm != NULL && strcmp(adm->adpassword, adpassword) == 0)
  {

    printf("Welcome to admin page");
    return 1;
  }

  return 0;
}

void logout()
{
  printf("Logged out successfully");
  exitpage();
  exitProgram();
}

void UserSignInPage()
{
  char username[20], password[20];

  printf("Username: ");
  scanf("%s", username);

  printf("Password: ");
  scanf("%s", password);

  if (loginUser(username, password))
  {
    UserWelcomePage();
  }
  else
  {
    printf("Login failed\n");
  }
}

void AdminSignInPage()
{
  char adusername[20], adpassword[20];

  printf("Admin Username: ");
  scanf("%s", adusername);

  printf("Admin Password: ");
  scanf("%s", adpassword);

  if (loginAdmin(adusername, adpassword))
  {
    AdminWelcomePage();
  }
  else
  {
    printf("Admin Login failed\n");
  }
}

void signin()
{
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.  NO  .            CHOICE             .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   1  .      SIGN UP AS CUSTOMER      .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   2  .      SIGN IN AS CUSTOMER      .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   3  .       SIGN UP AS ADMIN        .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   4  .       SIGN IN AS ADMIN        .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   5  .            LOGOUT             .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   0  .             EXIT              .\n");
  printf("\t\t\t\t........................................\n");
  return;
}

void yesno();

void HomePage()
{
  int choice;

  signin();

  printf("ENTER CHOICE:");

  scanf("%d", &choice);

  switch (choice)
  {
  case 1:
    UserSignUpPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      HomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 2:
    UserSignInPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      HomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 3:
    AdminSignUpPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      HomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 4:
    AdminSignInPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      HomePage();
      break;
    case 0:
      logout();
    }
    break;
  case -1:
    printf("Good bye!!!\n");
    exitProgram();
    break;
  case 5:
    logout();
    break;
  case 0:
    exitProgram();
    break;
  default:
    printf("Invalid choice\n");
  }
}

void adminpage()
{
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.  NO  .            CHOICE             .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   1  .          ADD PACKAGE          .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   2  .        DELETE PACKAGE         .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   3  .         PACKAGE LIST          .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   4  .         DELETE USER           .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   5  .        UPDATE PACKAGE         .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   6  .          ADMIN LIST           .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   7  .           LOGOUT              .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   0  .            EXIT               .\n");
  printf("\t\t\t\t........................................\n");
  return;
}

void yesno();

void AdminWelcomePage()
{

  int choice;

  adminpage();

  printf("ENTER CHOICE:");

  scanf("%d", &choice);

  switch (choice)
  {
  case 1:
    AddListPackage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      AdminWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 2:
    DeletePackgePage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      AdminWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 3:
    PackageListPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      AdminWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 4:
    DeleteUserPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      AdminWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 5:
    UpdatePackagePage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      AdminWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 6:
    AdminListPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      AdminWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 7:
    logout();
    break;
  case 0:
    exitProgram();
    break;
  }
}

void yesno()
{
  printf("\n\t\t\t\t.........................\n");
  printf("\t\t\t\t.  NO  .     CHOICE     .\n");
  printf("\t\t\t\t.........................\n");
  printf("\t\t\t\t.   1  .      YES       .\n");
  printf("\t\t\t\t.........................\n");
  printf("\t\t\t\t.   0  .       NO       .\n");
  printf("\t\t\t\t.........................\n");
  return;
}

void pricePackagelist()
{
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.  NO  .            PACKAGE             . PRICE .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   1  .   COX'S BAZAR 3 NIGHT 2 DAYS   .  9499 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   2  .    BANDARBAN 3 NIGHT 2 DAYS    .  4999 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   3  .   CHITTAGONG 3 NIGHT 2 DAYS    .  8999 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   4  .    RANGAMATI 3 NIGHT 2 DAYS    .  6999 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   5  .      SYLHET 3 NIGHT 2 DAYS     .  8499 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   6  .       SAJEK 3 NIGHT 2 DAYS     .  3499 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   7  .      KUAKATA 4 NIGHT 3 DAYS    .  6799 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   8  .   SAINT MARTIN 2 NIGHT 3 DAYS  .  7499 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.   9  .    DARJEELING 4 NIGHT 5 DAYS   . 19499 .\n");
  printf("\t\t\t\t.................................................\n");
  printf("\t\t\t\t.  10  .     KOLKATA 3 NIGHT 4 DAYS     . 22999 .\n");
  printf("\t\t\t\t.................................................\n");
  int choice;
  printf("\nENTER CHOICE:");
  scanf("%d", &choice);
  switch (choice)
  {
  case 1:
    printf("Do you want to purchase the package\nCOX'S BAZAR 3 NIGHT 2 DAYS");
    printf("CHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      printf("PACKAGE SUCCESSFULLY PURCHASED");
      UserWelcomePage();
      break;
    case 0:
      printf("DO YOU WANT TO GO TO HOMESCREEN\n");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        UserWelcomePage();
        break;
      case 0:
        logout();
        break;
      }
      break;
    }
    break;
  case 2:
    printf("DO YOU WANT TO PURCHASE THE PACKAGE\nBANDARBAN 3 NIGHT 2 DAYS");
    yesno();
    printf("CHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      printf("PACKAGE SUCCESSFULLY PURCHASED");
      UserWelcomePage();
      break;
    case 0:
      printf("DO YOU WANT TO GO TO HOMESCREEN\n");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        UserWelcomePage();
        break;
      case 0:
        logout();
        break;
      }
      break;
    case 3:
      printf("DO YOU WANT TO PURCHASE THE PACKAGE\nCHITTAGONG 3 NIGHT 2 DAYS");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("PACKAGE SUCCESSFULLY PURCHASED");
        UserWelcomePage();
        break;
      case 0:
        printf("DO YOU WANT TO GO TO HOMESCREEN\n");
        yesno();
        printf("CHOICE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
          UserWelcomePage();
          break;
        case 0:
          logout();
          break;
        }
      }
      break;
    case 4:
      printf("DO YOU WANT TO PURCHASE THE PACKAGE\nRANGAMATI 3 NIGHT 2 DAYS");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("PACKAGE SUCCESSFULLY PURCHASED");
        UserWelcomePage();
        break;
      case 0:
        printf("DO YOU WANT TO GO TO HOMESCREEN\n");
        yesno();
        printf("CHOICE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
          UserWelcomePage();
          break;
        case 0:
          logout();
          break;
        }
        break;
      }
      break;
    case 5:
      printf("DO YOU WANT TO PURCHASE THE PACKAGE\nSYLHET 3 NIGHT 2 DAYS");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("PACKAGE SUCCESSFULLY PURCHASED");
        UserWelcomePage();
        break;
      case 0:
        printf("DO YOU WANT TO GO TO HOMESCREEN\n");
        yesno();
        printf("CHOICE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
          UserWelcomePage();
          break;
        case 0:
          logout();
          break;
        }
        break;
      }
      break;
    case 6:
      printf("DO YOU WANT TO PURCHASE THE PACKAGE\nSAJEK 3 NIGHT 2 DAYS");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("PACKAGE SUCCESSFULLY PURCHASED");
        UserWelcomePage();
        break;
      case 0:
        printf("DO YOU WANT TO GO TO HOMESCREEN\n");
        yesno();
        printf("CHOICE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
          UserWelcomePage();
          break;
        case 0:
          logout();
          break;
        }
        break;
      }
      break;
    case 7:
      printf("DO YOU WANT TO PURCHASE THE PACKAGE\nKUAKATA 4 NIGHT 3 DAYS");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("PACKAGE SUCCESSFULLY PURCHASED");
        UserWelcomePage();
        break;
      case 0:
        printf("DO YOU WANT TO GO TO HOMESCREEN\n");
        yesno();
        printf("CHOICE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
          UserWelcomePage();
          break;
        case 0:
          logout();
          break;
        }
        break;
      }
      break;
    case 8:
      printf("DO YOU WANT TO PURCHASE THE PACKAGE\nSAINT MARTIN 2 NIGHT 3 DAYS");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("PACKAGE SUCCESSFULLY PURCHASED");
        UserWelcomePage();
        break;
      case 0:
        printf("DO YOU WANT TO GO TO HOMESCREEN\n");
        yesno();
        printf("CHOICE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
          UserWelcomePage();
          break;
        case 0:
          logout();
          break;
        }
        break;
      }
      break;
    case 9:
      printf("DO YOU WANT TO PURCHASE THE PACKAGE\nDARJEELING 4 NIGHT 5 DAYS");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("PACKAGE SUCCESSFULLY PURCHASED");
        UserWelcomePage();
        break;
      case 0:
        printf("DO YOU WANT TO GO TO HOMESCREEN\n");
        yesno();
        printf("CHOICE:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
          UserWelcomePage();
          break;
        case 0:
          logout();
          break;
        }
        break;
      }
      break;
    case 10:
      printf("DO YOU WANT TO PURCHASE THE PACKAGE\nKOLKATA 3 NIGHT 4 DAYS");
      yesno();
      printf("CHOICE:");
      scanf("%d", &choice);
      switch (choice)
      {
      case 1:
        printf("PACKAGE SUCCESSFULLY PURCHASED");
        break;
      case 0:
        printf("DO YOU WANT TO GO TO HOMESCREEN\n");
        yesno();
        printf("CHOICE:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
          UserWelcomePage();
          break;
        case 0:
          logout();
          break;
        }
        break;
      }
      break;
    }
    return;
  }
}

void userhomepage()
{
  printf("\n\t\t\t\t........................................\n");
  printf("\t\t\t\t.  NO  .            CHOICE             .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   1  .         BOOK PACKAGE          .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   2  .      UPDATE PROFILE INFO      .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   4  .            LOGOUT             .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   0  .             EXIT              .\n");
  printf("\t\t\t\t........................................\n");
  return;
}

void UserWelcomePage()
{

  int choice;

  userhomepage();

  scanf("%d", &choice);

  switch (choice)
  {
  case 1:
    pricePackagelist();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      UserWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 2:
    SingleUserPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      UserWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case 3:
    UpdateUserPage();
    printf("DO YOU WANT TO EXIT?");
    yesno();
    printf("\nCHOICE:");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      UserWelcomePage();
      break;
    case 0:
      logout();
    }
    break;
  case -1:
    exitProgram();
    break;
  default:
    printf("Invalid choice\n");
  }
  return;
}

void delay(int milliseconds)
{
  long pause;
  clock_t now, then;

  pause = milliseconds * (CLOCKS_PER_SEC / 1000);
  now = then = clock();
  while ((now - then) < pause)
    now = clock();
}

void welcome(int x)
{
  printf("\t\t\t\t******* ******* ******* *     * **   ** ******* *     *\n");
  printf("\t\t\t\t   *    *     *    *    *     * * * * * *     * *     *\n");
  printf("\t\t\t\t   *    *******    *    *     * *  *  * ******* *******\n");
  printf("\t\t\t\t   *    *  *       *    *     * *     * *       *     *\n");
  printf("\t\t\t\t   *    *    *  ******* ******* *     * *       *     *\n");
  char title[30] = " WELCOME";
  int z = strlen(title);
  printf("\t\t\t\t");
  for (int i = 0; i < 24; i++)
  {
    delay(x);
    printf("\xB2");
  }
  for (int i = 0; i <= z; i++)
  {
    delay(x);
    printf("%c", title[i]);
  }
  for (int i = 0; i < 23; i++)
  {
    delay(x);
    printf("\xB2");
  }
}

void homexit()
{
  printf("\n\t\t\t\t........................................\n");
  printf("\t\t\t\t.  NO  .            CHOICE             .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   1  .           HOME PAGE           .\n");
  printf("\t\t\t\t........................................\n");
  printf("\t\t\t\t.   0  .          EXIT PROGRAM         .\n");
  printf("\t\t\t\t........................................\n");
  return;
}

int main(void)
{
  int choice;
  loadFromFile();
  loadPackageFromFile();
  adloadFromFile();
  welcome(60);
  homexit();
  printf("\n\t\t\t\tCHOICE:");
  scanf("%d", &choice);

  switch (choice)
  {
  case 1:
    HomePage();
    break;
  case 0:
    exitProgram();
    break;
  default:
    printf("Something went wrong!!!");
  }
}
