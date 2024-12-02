#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>  // For std::this_thread
#include <chrono>  // For std::chrono::seconds
using namespace std;

string generateTimestamp() 
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ltm);
    return string(timestamp);
}
void saveToCSV(const string& filename, const string& timestamp, float temperature, float humidity, float co2) 
{
    ofstream file;
    file.open(filename, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << timestamp << "," << temperature << "," << humidity << "," << co2 << "\n";
        file.close();
    }
    else {
        std::cerr << "Unable to open file";
    }
}

int main() {
    string filename = "sensor_data.csv";
    int numEntries = 10; // Number of data entries to generate

    for (int i = 0; i < numEntries; ++i) {
        string timestamp = generateTimestamp();
        float temperature = 315.0 + i; // Example data generation
        float humidity = 81.0 + i;
        float co2 = 420.0 + i;

        saveToCSV(filename, timestamp, temperature, humidity, co2);

        // Sleep for 1 second to generate different timestamps
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}


