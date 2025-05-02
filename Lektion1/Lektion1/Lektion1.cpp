
#include <iostream>
#include <vector>

using namespace std;

// Struktur / klass för ett spelobjekt
class GameObject
{
    public:
        string name;
        int health;

        GameObject(string name, int health)
        {
            this->name = name;
            this->health = health;
        }
};

// Hash-tabell med separat chaning (vid konflikter)
class GameObjectTable
{
    private:
        static const int TABLE_SIZE = 10;
        vector<vector<GameObject>> table;

        int hash(const string& key)
        {
            int hashValue = 0;
            for (char c : key)
            {
                hashValue = (hashValue * 31 + c) % TABLE_SIZE;
            }
            return hashValue;
        }
    
    public:
        GameObjectTable() : table(TABLE_SIZE) {}

        // Metod för att stoppa in ett värde i Hash-tabellen
        void insert(const GameObject& object)
        {
            int index = hash(object.name);
            table[index].push_back(object);
        }

        // Sök efter ett värde i Hash-tabellen
        GameObject* find(const string& key)
        {
            int index = hash(key);
            for (GameObject& object : table[index])
            {
                if (object.name == key)
                {
                    return &object;
                }
            }
            return nullptr; // Vi kunde inte hitta ett objekt med det namnet
        }
    
        void printTable()
        {
            for (int i = 0; i < TABLE_SIZE; i++)
            {
                cout << "[" << i << "]: ";
                for (const auto& obj : table[i])
                {
                    cout << obj.name << " (" << obj.health << ") ";
                }
                cout << "\n";
            }
        }
};

int main(int argc, char* argv[])
{
    GameObjectTable tbl;

    tbl.insert(GameObject("Runner number 1", 23));
    tbl.insert(GameObject("Katniss", 54));
    tbl.insert(GameObject("Triss", 45));
    tbl.insert(GameObject("Lyra", 5));
    tbl.printTable();

    // ---

    GameObject* found = tbl.find("Triss");
    if (found)
    {
        cout << "Found: " << found->name << "with " << found->health << " health.\n";
    } else
    {
        cout << "Not found.\n";
    }

     found = tbl.find("Arnold");
    if (found)
    {
        cout << "Found: " << found->name << " with " << found->health << " health.\n";
    } else
    {
        cout << "Not found.\n";
    }
    
    return 0;
}
