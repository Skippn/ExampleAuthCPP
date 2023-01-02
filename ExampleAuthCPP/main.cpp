#include "api.h"
#include "skStr.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HWND console = GetConsoleWindow();
RECT r;

int main()
{
    SetConsoleTitleA("xhop#2146");
    auth::Client client("AID", "APIKEY", "SECRET"); //AID, APIKEY, SECRET
    std::string option, username, email, password, key;

    if (client.init())
    {
    r1:
        system("cls");
        std::cout << skCrypt("\n[1] Login") << std::endl;
        std::cout << skCrypt("[2] Register") << std::endl;
        std::cout << skCrypt("[3] Extend Subscription") << std::endl;
        std::cout << skCrypt("\nOption : ");
        std::cin >> option;
        if (option == "1")
        {
            system("cls");
            std::cout << skCrypt("\nUsername : ");
            std::cin >> username;
            std::cout << skCrypt("\nPassword : ");
            std::cin >> password;
            auto login_result = client.userLogin(username, password);
            if (login_result != auth::Error::SUCCESS)
            {
                auto myString = auth::errorMessage(login_result);
                LPCSTR lpMyString = myString.c_str();
                MessageBox(NULL, lpMyString, "", MB_ICONERROR | MB_OK);
                exit(-1);
            }
            std::cout << client.getUser() << std::endl;
            system("pause");
        }
        else if (option == "2")
        {
            system("cls");
            std::cout << skCrypt("\nUsername : ");
            std::cin >> username;
            std::cout << skCrypt("\nEmail : ");
            std::cin >> email;
            std::cout << skCrypt("\nPassword : ");
            std::cin >> password;
            std::cout << skCrypt("\nSubscription Key : ");
            std::cin >> key;
            auto register_result = client.userRegister(username, email, password, key);
            if (register_result != auth::Error::SUCCESS)
            {
                std::string myString = auth::errorMessage(register_result);
                LPCSTR lpMyString = myString.c_str();
                MessageBox(NULL, lpMyString, "", MB_ICONERROR | MB_OK);
                exit(-1);
            }
            MessageBox(NULL, "Welcome, you have successfully registered!", "", MB_ICONINFORMATION | MB_OK);
            goto r1;
        }
        else if (option == "3")
        {
            system("cls");
            std::cout << skCrypt("\nUsername : ");
            std::cin >> username;
            std::cout << skCrypt("\nPassword : ");
            std::cin >> password;
            std::cout << skCrypt("\nSubscription Key : ");
            std::cin >> key;
            auto register_result = client.extendSubscription(username, password, key);
            if (register_result != auth::Error::SUCCESS)
            {
                std::string myString = auth::errorMessage(register_result);
                LPCSTR lpMyString = myString.c_str();
                MessageBox(NULL, lpMyString, "", MB_ICONERROR | MB_OK);
                exit(-1);
            }
            MessageBox(NULL, "Your new subscription has been added to your account!", "", MB_ICONINFORMATION | MB_OK);
            goto r1;
        }
        else
            goto r1;
    }
    else
    {
        MessageBox(NULL, "Init Failed!", "", MB_ICONERROR | MB_OK);
        exit(-1);
    }

    return 0;
}