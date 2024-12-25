#include <iostream>
#include <string>

using namespace std;

void setSchedule(string *&schedule, int &size) {
    cout << "Enter the number of time slots for the schedule: ";
    cin >> size;

    if (schedule != nullptr) {
        delete[] schedule;
    }

    schedule = new string[size]; 

    for (int i = 0; i < size; ++i) {
        int status;
        cout << "Enter status for slot " << (i + 1) << " (0 for Available, 1 for Booked): ";
        cin >> status;

        if (status == 1) {
            schedule[i] = "Booked";
        } else if (status == 0) {
            schedule[i] = "Available";
        } else {
            cout << "Invalid input. Setting to 'Available' by default.\n";
            schedule[i] = "Available";
        }
    }
}

void setPackage(int *&packagePrices, int &size) {
    cout << "Enter the number of photo packages: ";
    cin >> size;

    if (packagePrices != nullptr) {
        delete[] packagePrices;
    }

    packagePrices = new int[size]; 

    for (int i = 0; i < size; ++i) {
        cout << "Enter the price for package " << (i + 1) << ": ";
        cin >> packagePrices[i];
    }
}

void ownerMenu(string *&schedule, int &size_schedule, int *&package, int &size_package, int &income) {
    int choice;
    while (true) {
        cout << "\nOwner Menu:\n";
        cout << "1. Set Schedule\n";
        cout << "2. Monitor Bookings\n";
        cout << "3. Set Photo Package\n";
        cout << "4. Monitor Income\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            setSchedule(schedule, size_schedule);
            break;
        case 2:
            cout << "Current Bookings:\n";
            for (int i = 0; i < size_schedule; ++i) {
                cout << "Slot " << (i + 1) << ": " << schedule[i] << endl;
            }
            break;
        case 3:
            setPackage(package, size_package);
            break;
        case 4:
            cout << "Total Income: $" << income << endl;
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}

void staffMenu(string *schedule, int size_schedule, int *package, int size_package, int &income) {
    int choice;
    while (true) {
        cout << "\nStaff Menu:\n";
        cout << "1. Input Booking\n";
        cout << "2. Check Availability\n";
        cout << "3. Update Session Status\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            cout << "Enter the customer's name: ";
            cin >> name;
            int slot;
            cout << "Enter the slot number to book (1 to " << size_schedule << "): ";
            cin >> slot;

            if (slot < 1 || slot > size_schedule) {
                cout << "Invalid slot number.\n";
            } else if (schedule[slot - 1] == "Booked") {
                cout << "Slot is already booked. Please choose another slot.\n";
            } else {
                cout << "Available packages:\n";
                for (int i = 0; i < size_package; ++i) {
                    cout << (i + 1) << ". $" << package[i] << endl;
                }

                int packageChoice;
                cout << "Select a package for this booking: ";
                cin >> packageChoice;

                if (packageChoice < 1 || packageChoice > size_package) {
                    cout << "Invalid package choice. Booking cancelled.\n";
                } else {
                    schedule[slot - 1] = "Booked";
                    income += package[packageChoice - 1];
                    cout << "Booking confirmed for " << name << " in slot " << slot << " with package $" << package[packageChoice - 1] << ".\n";
                }
            }
            break;
        }
        case 2:
            cout << "Slot Availability:\n";
            for (int i = 0; i < size_schedule; ++i) {
                cout << "Slot " << (i + 1) << ": " << schedule[i] << endl;
            }
            break;
        case 3: {
            int slot, status;
            cout << "Enter the slot number to update (1 to " << size_schedule << "): ";
            cin >> slot;

            if (slot < 1 || slot > size_schedule) {
                cout << "Invalid slot number.\n";
            } else {
                cout << "Enter new status for slot " << slot << " (1 for Booked, 0 for Available): ";
                cin >> status;

                if (status == 1) {
                    schedule[slot - 1] = "Booked";
                } else if (status == 0) {
                    schedule[slot - 1] = "Available";
                } else {
                    cout << "Invalid status. No changes made.\n";
                }
            }
            break;
        }
        case 4:
            return;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}

string setRole(int role_mode) {
    if (role_mode == 1) {
        return "Owner";
    } else if (role_mode == 2) {
        return "Staff";
    } else {
        return "Invalid role, please select correct role";
    }
}

int main() {
    int role_mode;
    string role;
    int size_for_schedule = 0, size_for_package = 0;
    int income = 0;

    string *schedule = nullptr;
    int *package = nullptr;

    cout << "Welcome to Photography Management\n";

    while (true) {
        cout << "Who are you (1 for Owner, 2 for Staff): ";
        cin >> role_mode;

        role = setRole(role_mode);

        if (role == "Owner" || role == "Staff") {
            cout << "Hello " << role << ", how can I help you today?\n";

            if (role == "Owner") {
                ownerMenu(schedule, size_for_schedule, package, size_for_package, income);
            } else if (role == "Staff") {
                staffMenu(schedule, size_for_schedule, package, size_for_package, income);
            }
        } else {
            cout << role << endl;
        }

        char continueChoice;
        cout << "Do you want to continue? (y/n): ";
        cin >> continueChoice;
        if (continueChoice != 'y' && continueChoice != 'Y') {
            cout << "Thank you for using our service.\n";

            break;
        }
    }

    return 0;
}
