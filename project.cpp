#include <bits/stdc++.h>
using namespace std;
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
class Person {
protected:
    string name;
    string contact;
    string address;
public:
    Person(const string& n, const string& c, const string& a) 
        : name(n), contact(c), address(a) {}
    virtual ~Person() {}
    string getName() const { return name; }
    string getContact() const { return contact; }
    string getAddress() const { return address; }
    virtual void display() const {
        cout << "Name: " << name << "\nContact: " << contact 
             << "\nAddress: " << address << endl;
    }
};
class Patient : public Person {
private:
    int patientId;
    int age;
    string gender;
    string medicalHistory;
public:
    Patient(int id, const string& n, const string& c, const string& a, 
            int ag, const string& g, const string& mh)
        : Person(n, c, a), patientId(id), age(ag), gender(g), medicalHistory(mh) {}
    int getPatientId() const { return patientId; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    string getMedicalHistory() const { return medicalHistory; }
    void display() const override {
        cout << "\nPatient ID: " << patientId << endl;
        Person::display();
        cout << "Age: " << age << "\nGender: " << gender 
             << "\nMedical History: " << medicalHistory << endl;
    }
    void updateMedicalHistory(const string& newHistory) {
        medicalHistory += "\n" + newHistory;
    }
};
class Doctor : public Person {
private:
    int doctorId;
    string specialization;
    vector<string> availableDays;
    vector<pair<int, int>> availableHours; // pairs of start and end hours
public:
    Doctor(int id, const string& n, const string& c, const string& a, 
           const string& spec, const vector<string>& days, 
           const vector<pair<int, int>>& hours)
        : Person(n, c, a), doctorId(id), specialization(spec), 
          availableDays(days), availableHours(hours) {}
    int getDoctorId() const { return doctorId; }
    string getSpecialization() const { return specialization; }
    vector<string> getAvailableDays() const { return availableDays; }
    vector<pair<int, int>> getAvailableHours() const { return availableHours; }
    void display() const override {
        cout << "\nDoctor ID: " << doctorId << endl;
        Person::display();
        cout << "Specialization: " << specialization << "\nAvailable Days: ";
        for (const auto& day : availableDays) {
            cout << day << " ";
        }
        cout << "\nAvailable Hours: ";
        for (const auto& hour : availableHours) {
            cout << hour.first << ":00-" << hour.second << ":00 ";
        }
        cout << endl;
    }
    bool isAvailable(const string& day, int hour) const {
        // Check if doctor is available on given day and hour
        bool dayFound = find(availableDays.begin(), availableDays.end(), day) != availableDays.end();
        if (!dayFound) return false;
        for (const auto& timeSlot : availableHours) {
            if (hour >= timeSlot.first && hour < timeSlot.second) {
                return true;
            }
        }
        return false;
    }
};
class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;
    int hour;
    string purpose;
    bool completed;
public:
    Appointment(int id, int pId, int dId, const string& dt, int hr, const string& purp)
        : appointmentId(id), patientId(pId), doctorId(dId), date(dt), 
          hour(hr), purpose(purp), completed(false) {}
    int getAppointmentId() const { return appointmentId; }
    int getPatientId() const { return patientId; }
    int getDoctorId() const { return doctorId; }
    string getDate() const { return date; }
    int getHour() const { return hour; }
    string getPurpose() const { return purpose; }
    bool isCompleted() const { return completed; }
    void markCompleted() { completed = true; }
    void display() const {
        cout << "\nAppointment ID: " << appointmentId 
             << "\nPatient ID: " << patientId
             << "\nDoctor ID: " << doctorId
             << "\nDate: " << date
             << "\nTime: " << hour << ":00"
             << "\nPurpose: " << purpose
             << "\nStatus: " << (completed ? "Completed" : "Pending") << endl;
    }
};
class HospitalManagementSystem {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    int nextPatientId = 1;
    int nextDoctorId = 1;
    int nextAppointmentId = 1;
public:
    const vector<Doctor>& getDoctors() const { return doctors; }
    const vector<Patient>& getPatients() const { return patients; }
    const vector<Appointment>& getAppointments() const { return appointments; }
    void addPatient(const string& name, const string& contact, const string& address,
                    int age, const string& gender, const string& medicalHistory) {
        patients.emplace_back(nextPatientId++, name, contact, address, age, gender, medicalHistory);
        cout << "Patient added successfully with ID: " << (nextPatientId - 1) << endl;
    }
    void displayAllPatients() const {
        if (patients.empty()) {
            cout << "No patients registered." << endl;
            return;
        }
        cout << "\n=== List of All Patients ===\n";
        for (const auto& patient : patients) {
            patient.display();
            cout << "------------------------" << endl;
        }
    }
    Patient* findPatient(int id) {
        for (auto& patient : patients) {
            if (patient.getPatientId() == id) 
                return &patient;
        }
        return nullptr;
    }
    void addDoctor(const string& name, const string& contact, const string& address,
                   const string& specialization, const vector<string>& availableDays,
                   const vector<pair<int, int>>& availableHours) {
        doctors.emplace_back(nextDoctorId++, name, contact, address, 
                            specialization, availableDays, availableHours);
        cout << "Doctor added successfully with ID: " << (nextDoctorId - 1) << endl;
    }
    void displayAllDoctors() const {
        if (doctors.empty()) {
            cout << "No doctors registered." << endl;
            return;
        }
        cout << "\n=== List of All Doctors ===\n";
        for (const auto& doctor : doctors) {
            doctor.display();
            cout << "------------------------" << endl;
        }
    }
    Doctor* findDoctor(int id) {
        for (auto& doctor : doctors) {
            if (doctor.getDoctorId() == id) {
                return &doctor;
            }
        }
        return nullptr;
    }
    bool scheduleAppointment(int patientId, int doctorId, const string& date, 
                            int hour, const string& purpose) {
        Patient* patient = findPatient(patientId);
        Doctor* doctor = findDoctor(doctorId);
        if (!patient || !doctor) {
            cout << "Invalid patient or doctor ID." << endl;
            return false;
        }
        string day = "Monday"; // In real implementation, calculate from date
        if (!doctor->isAvailable(day, hour)) {
            cout << "Doctor is not available at the requested time." << endl;
            return false;
        }
        for (const auto& app : appointments) {
            if (app.getDoctorId() == doctorId && app.getDate() == date && 
                app.getHour() == hour && !app.isCompleted()) {
                cout << "Doctor already has an appointment at this time." << endl;
                return false;
            }
        }
        appointments.emplace_back(nextAppointmentId++, patientId, doctorId, date, hour, purpose);
        cout << "Appointment scheduled successfully with ID: " << (nextAppointmentId - 1) << endl;
        return true;
    }
    void displayAllAppointments() const {
        if (appointments.empty()) {
            cout << "No appointments scheduled." << endl;
            return;
        }
        cout << "\n=== List of All Appointments ===\n";
        for (const auto& appointment : appointments) {
            appointment.display();
            cout << "------------------------" << endl;
        }
    }
    void displayDoctorAppointments(int doctorId) const {
        bool found = false;
        cout << "\n=== Appointments for Doctor ID " << doctorId << " ===\n";
        for (const auto& appointment : appointments) {
            if (appointment.getDoctorId() == doctorId) {
                appointment.display();
                cout << "------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No appointments found for this doctor." << endl;
        }
    }
    void displayPatientAppointments(int patientId) const {
        bool found = false;
        cout << "\n=== Appointments for Patient ID " << patientId << " ===\n";
        for (const auto& appointment : appointments) {
            if (appointment.getPatientId() == patientId) {
                appointment.display();
                cout << "------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No appointments found for this patient." << endl;
        }
    }
    bool completeAppointment(int appointmentId) {
        for (auto& appointment : appointments) {
            if (appointment.getAppointmentId() == appointmentId) {
                if (appointment.isCompleted()) {
                    cout << "Appointment is already completed." << endl;
                    return false;
                }
                appointment.markCompleted();
                cout << "Appointment marked as completed." << endl;
                return true;
            }
        }
        cout << "Appointment not found." << endl;
        return false;
    }
    void saveData() const {
        ofstream outFile("hospital_data.txt");
        if (!outFile) {
            cerr << "Error saving data." << endl;
            return;
        }
        outFile << "[Patients]\n";
        for (const auto& patient : patients) {
            outFile << patient.getPatientId() << "|" << patient.getName() << "|"
                    << patient.getContact() << "|" << patient.getAddress() << "|"
                    << patient.getAge() << "|" << patient.getGender() << "|"
                    << patient.getMedicalHistory() << "\n";
        }
        outFile << "[Doctors]\n";
        for (const auto& doctor : doctors) {
            outFile << doctor.getDoctorId() << "|" << doctor.getName() << "|"
                    << doctor.getContact() << "|" << doctor.getAddress() << "|"
                    << doctor.getSpecialization() << "|";
            for (const auto& day : doctor.getAvailableDays()) {
                outFile << day << ";";
            }
            outFile << "|";
            for (const auto& hour : doctor.getAvailableHours()) {
                outFile << hour.first << "-" << hour.second << ";";
            }
            outFile << "\n";
        }
        outFile << "[Appointments]\n";
        for (const auto& appointment : appointments) {
            outFile << appointment.getAppointmentId() << "|" << appointment.getPatientId() << "|"
                    << appointment.getDoctorId() << "|" << appointment.getDate() << "|"
                    << appointment.getHour() << "|" << appointment.getPurpose() << "|"
                    << appointment.isCompleted() << "\n";
        }
        outFile.close();
        cout << "Data saved successfully to hospital_data.txt" << endl;
    }
    void loadData() {
        ifstream inFile("hospital_data.txt");
        if (!inFile) {
            cerr << "No existing data file found." << endl;
            return;
        }
        string line;
        string section;
        nextPatientId = 1;
        nextDoctorId = 1;
        nextAppointmentId = 1;
        patients.clear();
        doctors.clear();
        appointments.clear();
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            if (line == "[Patients]" || line == "[Doctors]" || line == "[Appointments]") {
                section = line;
                continue;
            }
            if (section == "[Patients]") {
                vector<string> data = split(line, '|');
                if (data.size() >= 7) {
                    int id = stoi(data[0]);
                    int age = stoi(data[4]);
                    patients.emplace_back(id, data[1], data[2], data[3], age, data[5], data[6]);
                    if (id >= nextPatientId) nextPatientId = id + 1;
                }
            }
            else if (section == "[Doctors]") {
                vector<string> data = split(line, '|');
                if (data.size() >= 7) {
                    int id = stoi(data[0]);
                    vector<string> days = split(data[5], ';');
                    days.erase(remove(days.begin(), days.end(), ""), days.end());
                    vector<string> hourStrings = split(data[6], ';');
                    hourStrings.erase(remove(hourStrings.begin(), hourStrings.end(), ""), hourStrings.end());
                    vector<pair<int, int>> hours;
                    for (const auto& h : hourStrings) {
                        vector<string> time = split(h, '-');
                        if (time.size() == 2) {
                            hours.emplace_back(stoi(time[0]), stoi(time[1]));
                        }
                    }
                    doctors.emplace_back(id, data[1], data[2], data[3], data[4], days, hours);
                    if (id >= nextDoctorId) nextDoctorId = id + 1;
                }
            }
            else if (section == "[Appointments]") {
                vector<string> data = split(line, '|');
                if (data.size() >= 7) {
                    int id = stoi(data[0]);
                    int pId = stoi(data[1]);
                    int dId = stoi(data[2]);
                    int hour = stoi(data[4]);
                    bool completed = (data[6] == "1");
                    Appointment app(id, pId, dId, data[3], hour, data[5]);
                    if (completed) app.markCompleted();
                    appointments.push_back(app);
                    if (id >= nextAppointmentId) nextAppointmentId = id + 1;
                }
            }
        }
        inFile.close();
        cout << "Data loaded successfully from hospital_data.txt" << endl;
    }
};
void displayMainMenu() {
    cout << "\n=== Hospital Management System ===\n";
    cout << "1. Patient Management\n";
    cout << "2. Doctor Management\n";
    cout << "3. Appointment Management\n";
    cout << "4. Save Data\n";
    cout << "5. Load Data\n";
    cout << "6. Exit\n";
    cout << "Enter your choice (1-6): ";
}
void patientManagementMenu(HospitalManagementSystem& hms) {
    int choice;
    do {
        cout << "\n=== Patient Management ===\n";
        cout << "1. Add New Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Find Patient by ID\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string name, contact, address, gender, medicalHistory;
                int age;
                cout << "\nEnter patient details:\n";
                cout << "Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Contact: ";
                getline(cin, contact);
                cout << "Address: ";
                getline(cin, address);
                cout << "Age: ";
                cin >> age;
                cout << "Gender: ";
                cin.ignore();
                getline(cin, gender);
                cout << "Medical History: ";
                getline(cin, medicalHistory);
                hms.addPatient(name, contact, address, age, gender, medicalHistory);
                break;
            }
            case 2:
                hms.displayAllPatients();
                break;
            case 3: {
                int id;
                cout << "Enter patient ID: ";
                cin >> id;
                Patient* patient = hms.findPatient(id);
                if (patient) {
                    cout << "\nPatient Details:\n";
                    patient->display();
                } else {
                    cout << "Patient not found." << endl;
                }
                break;
            }
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);
}
void doctorManagementMenu(HospitalManagementSystem& hms) {
    int choice;
    do {
        cout << "\n=== Doctor Management ===\n";
        cout << "1. Add New Doctor\n";
        cout << "2. View All Doctors\n";
        cout << "3. Find Doctor by ID\n";
        cout << "4. Search Doctors by Specialization\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string name, contact, address, specialization;
                vector<string> days;
                vector<pair<int, int>> hours;
                string dayInput, hourInput;
                cout << "\nEnter doctor details:\n";
                cout << "Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Contact: ";
                getline(cin, contact);
                cout << "Address: ";
                getline(cin, address);
                cout << "Specialization: ";
                getline(cin, specialization);
                cout << "Available days (comma separated, e.g., Monday,Wednesday,Friday): ";
                getline(cin, dayInput);
                days = split(dayInput, ',');
                cout << "Available hours (start-end pairs, comma separated, e.g., 9-12,14-17): ";
                getline(cin, hourInput);
                vector<string> hourSlots = split(hourInput, ',');
                for (const auto& slot : hourSlots) {
                    vector<string> times = split(slot, '-');
                    if (times.size() == 2) {
                        hours.emplace_back(stoi(times[0]), stoi(times[1]));
                    }
                }
                hms.addDoctor(name, contact, address, specialization, days, hours);
                break;
            }
            case 2:
                hms.displayAllDoctors();
                break;
            case 3: {
                int id;
                cout << "Enter doctor ID: ";
                cin >> id;
                Doctor* doctor = hms.findDoctor(id);
                if (doctor) {
                    cout << "\nDoctor Details:\n";
                    doctor->display();
                } else {
                    cout << "Doctor not found." << endl;
                }
                break;
            }
            case 4: {
                string spec;
                cout << "Enter specialization to search: ";
                cin.ignore();
                getline(cin, spec);
                bool found = false;
                cout << "\nDoctors with specialization '" << spec << "':\n";
                for (const auto& doctor : hms.getDoctors()) {
                    if (doctor.getSpecialization() == spec) {
                        doctor.display();
                        cout << "------------------------" << endl;
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No doctors found with this specialization." << endl;
                }
                break;
            }
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);
}
void appointmentManagementMenu(HospitalManagementSystem& hms) {
    int choice;
    do {
        cout << "\n=== Appointment Management ===\n";
        cout << "1. Schedule New Appointment\n";
        cout << "2. View All Appointments\n";
        cout << "3. View Doctor's Appointments\n";
        cout << "4. View Patient's Appointments\n";
        cout << "5. Mark Appointment as Completed\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int patientId, doctorId, hour;
                string date, purpose;
                cout << "\nSchedule New Appointment:\n";
                hms.displayAllPatients();
                cout << "Enter patient ID: ";
                cin >> patientId;
                hms.displayAllDoctors();
                cout << "Enter doctor ID: ";
                cin >> doctorId;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter hour (0-23): ";
                cin >> hour;
                cout << "Enter purpose: ";
                cin.ignore();
                getline(cin, purpose);
                hms.scheduleAppointment(patientId, doctorId, date, hour, purpose);
                break;
            }
            case 2:
                hms.displayAllAppointments();
                break;
            case 3: {
                int doctorId;
                hms.displayAllDoctors();
                cout << "Enter doctor ID to view appointments: ";
                cin >> doctorId;
                hms.displayDoctorAppointments(doctorId);
                break;
            }
            case 4: {
                int patientId;
                hms.displayAllPatients();
                cout << "Enter patient ID to view appointments: ";
                cin >> patientId;
                hms.displayPatientAppointments(patientId);
                break;
            }
            case 5: {
                int appointmentId;
                hms.displayAllAppointments();
                cout << "Enter appointment ID to mark as completed: ";
                cin >> appointmentId;
                hms.completeAppointment(appointmentId);
                break;
            }
            case 6:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);
}
int main() {
    HospitalManagementSystem hms;
    int choice;
    hms.loadData();
    do {
        displayMainMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                patientManagementMenu(hms);
                break;
            case 2:
                doctorManagementMenu(hms);
                break;
            case 3:
                appointmentManagementMenu(hms);
                break;
            case 4:
                hms.saveData();
                break;
            case 5:
                hms.loadData();
                break;
            case 6:
                cout << "Exiting program. Saving data..." << endl;
                hms.saveData();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
    return 0;
}