# ✈️ AirlineBookingSystem-CPP

## 📌 Overview

A simple Airline Booking System built using C++.

The system allows passengers to manage airline reservations through a menu-driven console application.

Users can:

* Book seats
* View seat availability
* Search bookings by passport number
* Update booking information
* Delete bookings
* Count total bookings
* Save and load reservations from a text file

The project simulates a basic airline reservation workflow while focusing on core C++ programming concepts, file handling, data persistence, and input validation.

---

## 🏗️ System Design

Console Application

Menu Driven Architecture

Data is managed using:

* Structs
* Enums
* 2D Arrays
* Text Files

---

## ⚙️ Features

### Booking Management

* Book New Seat
* Find Booking By Passport Number
* Update Passenger Information
* Update Reserved Seat
* Delete Booking
* Count Total Bookings

### Seat Management

* Display Seat Layout
* Seat Availability Validation
* Prevent Double Booking
* Restore Reserved Seats On Startup

### Data Management

* Save Bookings To TXT File
* Load Existing Bookings
* Parse Text Records Using stringstream
* Data Persistence Between Sessions

### Input Validation

* Passport Number Uniqueness Validation
* Seat Range Validation
* Invalid Menu Option Validation
* Invalid Update Option Validation
* Invalid Seat Input Validation
* Protection Against Non-Numeric Input
* Protection Against Oversized Numeric Input
* Support For Safe User Input Handling

---

## 📂 Project Structure

AirlineBookingSystem

* Main Menu
* Passenger Management
* Seat Management
* Booking Management
* CRUD Operations
* File Handling
* Data Parsing
* Input Validation

---

## 🧠 Core Concepts

* Structs
* Enums
* Functions
* 2D Arrays
* File Handling
* stringstream
* Vectors
* Data Parsing
* Input Validation
* CRUD Operations
* Menu Driven Applications

---

## 💺 Seat Layout

Aircraft Configuration:

* 13 Rows
* 6 Seats Per Row
* Columns A → F

Example:

1A  1B  1C  1D  1E  1F

Reserved seats are displayed as:

[XX]

---

## 💾 File Storage

File Name:

Bookings.txt

Stored Information:

* Passenger Name
* Phone Number
* Email Address
* Gender
* Passport Number
* Seat Row
* Seat Column

Example Record:

Shady,123456,[s@hotmail.com](mailto:s@hotmail.com),M,AA12345,1,A

---

## 🔄 Data Persistence

The system automatically:

* Saves bookings to file
* Loads bookings when the application starts
* Restores reserved seats from previous sessions
* Synchronizes seat status with stored reservations

This prevents data loss between program executions.

---

## 🚀 How To Run

1. Open the project in Visual Studio
2. Build the solution
3. Run the application
4. Use the menu to manage reservations

---

## 🧪 Implemented CRUD Operations

### Create

* Book New Seat

### Read

* Show Seats
* Show All Bookings
* Find Booking By Passport Number
* Count Total Bookings

### Update

* Update Passenger Information
* Update Reserved Seat

### Delete

* Delete Booking By Passport Number

---

## 💡 Future Improvements

* Ticket Generation
* Seat Classes (Economy / Business / First Class)
* Flight Management Module
* Multiple Flights Support
* Booking Confirmation Number
* Binary File Storage
* Database Integration
* OOP Version Using Classes

---

## 👨‍💻 Developed & Designed By

Shady Mahmoud

< SHADY CODES />

---

🔥 This project demonstrates:

* C++
* Problem Solving
* Struct-Based Design
* CRUD Operations
* Arrays
* File Handling
* Data Persistence
* Input Validation
* Text Parsing
* Console Application Development

