#include <iostream>
#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
// for DataBase-json
using json = nlohmann::json;
std::ifstream dbj("db.json");
json db = json::parse(dbj);
class DataBase
{
public:
    void show_tmenu()
    {
        int counter = 1;
        for (auto &item : db["items"].items())
        {
            std::cout << counter << ": " << item.key() << std::endl;  counter++;
        }
        int choise;
        std::cout << "0: Закінчити роботу" << std::endl;

        std::cout << ">>> ";
        std::cin >> choise;
        if (choise == 0)
        {
            std::ofstream file("db_new.json");
            file << db;
            std::cout << "Робота закінченна" << std::endl;
            exit(0);
        }
        second_level_menu(choise);
    };
    int second_level_menu(int choise)
    {
        int counter = 1;
        for (auto &item : db["items"].items())
        {
            if (counter == choise)
            {
                int counter2 = 1;
                for (auto &item2 : db["items"][item.key()].items())
                {
                    std::cout << counter2 << ": " << item2.key() << std::endl;  counter2++;
                }
                break;
            }
            counter++;
        }
        int choise2;
        std::cout << "0: Головне меню" << std::endl;
        std::cout << ">>> ";
        std::cin >> choise2;
        if (choise2 == 0)
        {
            show_tmenu();
        }
        std::vector<int> choises = {choise, choise2};
        third_level_menu(choises);
        return 0;
    };
    int third_level_menu(std::vector<int> choises)
    {
        int choise = choises[0];
        int choise2 = choises[1];
        int counter = 1;
        for (auto &item : db["items"].items())
        {
            if (counter == choise)
            {
                int counter2 = 1;
                for (auto &item2 : db["items"][item.key()].items())
                {
                    if (counter2 == choise2)
                    {
                        int counter3 = 1;
                        auto &path_to_item = db["items"][item.key()][item2.key()]; //.items();  for (auto &item3 : db["items"][item.key()][item2.key()].items())  {
                        std::cout << counter3 << ": " << item3.key() << " "  << item3.value() << std::endl;
                        counter3++;
                    }
                    int choise3;
                    std::cout << "0: Головне меню" << std::endl;
                    std::cout << "100: Додати товар" << std::endl;
                    std::cout << "200: Видалити товар" << std::endl;
                    std::cout << ">>> ";
                    std::cin >> choise3;
                    switch (choise3)
                    {
                        // go back
                        case 0:
                        {
                            show_tmenu();
                        }
                            // add
                        case 100:
                        {
                            std::string item;
                            std::string use_until;
                            int price;
                            int volume;
                            std::cout << "Назва товару: ";
                            std::cin >> item;
                            std::cout << "Ціна товару: ";
                            std::cin >> price;
                            std::cout << "Об'єм товару: ";
                            std::cin >> volume;
                            std::cout << "Термін придатності: ";
                            std::cin >> use_until;
                            json new_item = {{"Ціна", price},{"Об'єм", volume},{"Термін придатності", use_until}};  path_to_item[item]=new_item;

                            // Штука що додає товар
                            show_tmenu();
                        }
                            // minus
                        case 200:
                        {
                            std::string choise4;
                            std::cout << "Який товар бажаєте видалити?(текстом)" << std::endl;  std::cout << ">>> ";
                            std::cin.ignore();
                            std::getline(std::cin, choise4);
                            path_to_item.erase(choise4);
                            show_tmenu();
                        }
                    }
                    break;
                }
                counter2++;
            }
        }
        counter++;
    }
    return 0;
}
};
int main(int argc, char *argv[])
{
    DataBase Shop;
    system("figlet -c BAZAAR");
    system("echo -e \"Hello and welcome to the Bazaar program!\\n\\nThis tool allows you to see, add, and remove items from your market.\\n\\n\\n@vask.mykola.ki102\" | boxes -d dog\n");
    std::cout << "\n\n" << std::endl;
    Shop.show_tmenu();
    return 0;
};
