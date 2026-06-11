#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>


using namespace std;




const string BookingsFileName = "Bookings.txt";

const short NumberOfRows = 13;
const short NumberOfColumns = 6;

const char FirstColumn = 'A';
const char LastColumn = FirstColumn + NumberOfColumns - 1;


enum enMainMenuOptions
{
	eBookSeat = 1, eShowSeats = 2, eShowBookings = 3,  eExit = 4
};



struct sPassenger
{
    string Name;
    string Phone;
    string Email;
    string Gender;
    string PassportNumber;
};



struct sSeat
{
    short Row;
    char Column;
    bool IsBooked;
};




struct sBooking
{
    sPassenger Passenger;
    sSeat Seat;
};



//Create Seat
sSeat Seats[NumberOfRows][NumberOfColumns];

void SaveBookingToFile(const sBooking& Booking);



void InitializeSeats()
{
    for (short row = 0; row < NumberOfRows; row++)
    {
        for (short col = 0; col < NumberOfColumns; col++)
        {
            Seats[row][col].Row = row + 1;
            Seats[row][col].Column = FirstColumn + col;
            Seats[row][col].IsBooked = false;
        }
    }
}



void ShowSeats()
{

    for (int row = 0; row < NumberOfRows; row++)
    {
        for (int col = 0; col < NumberOfColumns; col++)
        {

            if (Seats[row][col].IsBooked)
            {
                cout << "[XX] ";
            }
            else
            {
                cout << "[" << Seats[row][col].Row
                    << Seats[row][col].Column << "] ";
            }
        }

        cout << endl;
    }
}



sPassenger ReadPassengerInfo()
{
    sPassenger Passenger;

    cout << "\nEnter Passenger Name: ";
    getline(cin >> ws, Passenger.Name);

    cout << "\nEnter Passenger Phone: ";
    getline(cin, Passenger.Phone);

    cout << "\nEnter Passenger Email: ";
    getline(cin, Passenger.Email);

    cout << "\nEnter Passenger Gender: ";
    getline(cin, Passenger.Gender);

    cout << "\nEnter Passport Number: ";
    getline(cin, Passenger.PassportNumber);

    return Passenger;
}



void BookSeat()
 {
        short row;
        char column;

        cout << "\nEnter Row: ";
        cin >> row;

        cout << "\nEnter Column: ";
        cin >> column;





        column = toupper(column);

        if (row < 1 || row > NumberOfRows || column < FirstColumn || column > LastColumn)
        {
            cout << "\nInvalid seat. Please enter row from 1 to "
                << NumberOfRows
                << " and column from "
                << FirstColumn
                << " to "
                << LastColumn
                << ".\n";
            return;
        }


        short rowIndex = row - 1;
        short columnIndex = column - FirstColumn;


        if (Seats[rowIndex][columnIndex].IsBooked)
        {
            cout << "\nThis seat is no longer available. Please choose another seat.\n";
        }
        else
        {
            sPassenger Passenger = ReadPassengerInfo();

            Seats[rowIndex][columnIndex].IsBooked = true;

            sBooking Booking;


            Booking.Passenger = Passenger;
            Booking.Seat = Seats[rowIndex][columnIndex];

            SaveBookingToFile(Booking);


            cout << "\nBooking completed successfully.\n";
        }
}




sBooking ParseLineToBooking(const string& Line)
{
    sBooking Booking;

    stringstream SS(Line);

    getline(SS, Booking.Passenger.Name, ',');
    getline(SS, Booking.Passenger.Phone, ',');
    getline(SS, Booking.Passenger.Email, ',');
    getline(SS, Booking.Passenger.Gender, ',');
    getline(SS, Booking.Passenger.PassportNumber, ',');

    string Row;
    string Col;

    getline(SS, Row, ',');
    getline(SS, Col, ',');

    Booking.Seat.Row = stoi(Row);
    Booking.Seat.Column = Col[0];
    Booking.Seat.IsBooked = true;

    return Booking;
}








void LoadBookingsFromFile()
{
    fstream MyFile;

    MyFile.open(BookingsFileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;



        while (getline(MyFile, Line))
        {
            if (Line.empty())
                continue;
            
            
            sBooking Booking = ParseLineToBooking(Line);

         
            short rowIndex = Booking.Seat.Row - 1;
            short columnIndex = Booking.Seat.Column - FirstColumn;

          
            if (rowIndex < 0 || rowIndex >= NumberOfRows ||
                columnIndex < 0 || columnIndex >= NumberOfColumns)
            {
                continue;
            }


            Seats[rowIndex][columnIndex].IsBooked = true;
        }
    }

    MyFile.close();
}









void PrintBookingLine(const string& Line)
{
    

    sBooking Booking = ParseLineToBooking(Line);

    cout << "\n=========================\n";
    cout << "Name     : " << Booking.Passenger.Name << endl;
    cout << "Phone    : " << Booking.Passenger.Phone << endl;
    cout << "Email    : " << Booking.Passenger.Email << endl;
    cout << "Gender   : " << Booking.Passenger.Gender << endl;
    cout << "Passport : " << Booking.Passenger.PassportNumber << endl;
    cout << "Seat     : "
        << Booking.Seat.Row
        << Booking.Seat.Column << endl;

}



void ShowBookings()
{
    fstream MyFile;

    MyFile.open(BookingsFileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;

        bool   HasBookings = false;

        while (getline(MyFile, Line))
        {
            if (Line.empty())
                continue;



            HasBookings = true;

            PrintBookingLine(Line);
        }


           if (!HasBookings)
           {
                cout << "\nNo bookings found.\n";
           }

            MyFile.close();
        }

    else
    {
            cout << "\nNo bookings found.\n";
     }
}




enMainMenuOptions ReadMainMenuOption()
{
    short choice;

    cout << "\nChoose option: ";
    cin >> choice;

    return (enMainMenuOptions)choice;
}




void ShowMainMenu()
{
    cout << "\n========== Airline Booking ==========\n";
    cout << "1. Book Seat\n";
    cout << "2. Show Seats\n";
    cout << "3. Show Bookings\n";
    cout << "4. Exit\n";
}



void StartApplication()
{
    while (true)
    {

        ShowMainMenu();

        enMainMenuOptions choice = ReadMainMenuOption();
        switch (choice)
        {
        case eBookSeat:BookSeat();
            break;

        case eShowSeats:ShowSeats();
            break;

        case eShowBookings:ShowBookings();
            break;

        case eExit:
            return;

        default:
            cout << "\nInvalid option. Please choose from 1 to 4.\n";
        }
    }
}





void SaveBookingToFile(const sBooking& Booking)
{
    fstream MyFile;

    MyFile.open(BookingsFileName, ios::out | ios::app);



    if (MyFile.is_open())
    {
        MyFile << Booking.Passenger.Name
            << ","
            << Booking.Passenger.Phone
            << ","
            << Booking.Passenger.Email
            << ","
            << Booking.Passenger.Gender
            << ","
            << Booking.Passenger.PassportNumber
            << ","
            << Booking.Seat.Row
            << ","
            << Booking.Seat.Column
            << endl;
            
        MyFile.close();
    }
}




int main()
{
    InitializeSeats();

    LoadBookingsFromFile();



    StartApplication();


    return 0;
}