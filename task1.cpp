#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

void openFile(string name, string &data)
{
    fstream input;
    input.open(name, ios::in);

    if (input.good() != true)
    {
        throw runtime_error("Nie otworzono poprawnie pliku");   
    }

    getline(input, data);

    input.close();

   
}

void getData(string& data, int& failed, string& output_data)
{
    vector <bitset<8>> all_message;

    for (int i = 0; i < data.length(); i += 8)
    {
        string temp = data.substr(i, 8);
        all_message.push_back(bitset<8>(temp));
    }

    for (auto message : all_message)
    {
        int sum = 0;

        for (int i = 0; i < 7; i++)
            sum += message[i];

        if (sum == 0 || (sum - message[7]) % 2 != message[7])
        {
            failed++;
            continue;
        }
        output_data += message.to_string();
    }
}

void saveDataInFile(int numberOfObjectsLoaded, int numberOfObjectsWithError, string correctData)
{
    fstream output;

    output.open("output.txt", ios::out);

    output << numberOfObjectsLoaded << endl;
    output << numberOfObjectsWithError << endl;
    output << correctData << endl;

    output.close();

}

int main()
{
    string data, output_data;
    int failed = 0;

    try {
        openFile("input.txt", data);
    }
    catch (runtime_error e)
    {
        cout << e.what();
    }

    getData(data, failed, output_data);

    saveDataInFile(data.length() / 8, failed, output_data);

    return 0;
}