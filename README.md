# Hospital Management System

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![OOP](https://img.shields.io/badge/Object_Oriented-Design-success.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

A comprehensive Hospital Management System implemented in C++ that handles patient records, doctor information, and appointment scheduling with persistent data storage.

## Key Features

- **Patient Management**:
  - Add/View/Update patient records
  - Store medical history and demographic information
  - Unique patient ID generation

- **Doctor Management**:
  - Maintain doctor profiles with specialization
  - Manage availability schedules
  - Search by specialization

- **Appointment System**:
  - Intelligent scheduling with conflict detection
  - Status tracking (Pending/Completed)
  - View appointments by patient or doctor

- **Data Persistence**:
  - Automatic saving to `hospital_data.txt`
  - Data loading on startup
  - Custom serialization format

## Technical Highlights

- **Object-Oriented Design**:
  - Inheritance hierarchy (Person → Patient/Doctor)
  - Polymorphic methods for display functionality
  - Encapsulated data members

- **Efficient Data Handling**:
  - STL containers (vectors, pairs)
  - O(n) search complexity
  - Custom data serialization

- **Robust Error Handling**:
  - Input validation
  - Conflict detection for appointments
  - Comprehensive error messages

## Getting Started

### Prerequisites
- C++17 compatible compiler (g++/clang++)
- Linux/macOS/Windows (with WSL recommended for Windows)

### Compilation & Execution
```bash
g++ hospital_management.cpp -o hospital -std=c++17
./hospital
