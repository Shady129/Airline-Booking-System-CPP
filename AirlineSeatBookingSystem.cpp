#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>

using namespace std;




const string BookingsFileName = "Bookings.txt";

const short NumberOfRows = 13;
const short NumberOfColumns = 6;

const char FirstColumn = 'A';
const char LastColumn = FirstColumn + NumberOfColumns - 1;


enum enMainMenuOptions
{
	eBookSeat = 1, 
    eShowSeats = 2,
    eShowBookings = 3,
    eFindBooking = 4,
    eDeleteBooking = 5,
    eUpdateBooking = 6,
    eCountBookings = 7,
    eExit = 8
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
void PrintBooking(const sBooking& Booking);
void FindBooking();
void DeleteBooking();
void UpdateBooking();
bool UpdateBookingByPassportNumber(string PassportNumber, sBooking UpdatedBooking);
bool FindBookingByPassportNumber(string PassportNumber, sBooking& Booking);
void CountBookings();






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





bool IsNumber(string Text)
{
    for (char c : Text)
    {
        if (!isdigit((unsigned char)c))
            return false;
    }

    return true;
}




void BookSeat()
 {
    string RowInput;
    string ColumnInput;

    cout << "\nEnter Row: ";
    cin >> RowInput;

    cout << "\nEnter Column: ";
    cin >> ColumnInput;

    if (!IsNumber(RowInput) || RowInput.length() > 2 || ColumnInput.length() != 1)
    {
        cout << "\nInvalid seat.\n";
        return;
    }

    short row = stoi(RowInput);
    char column = toupper((unsigned char)ColumnInput[0]);


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

        sBooking TempBooking;

        if (FindBookingByPassportNumber(Passenger.PassportNumber, TempBooking))
        {
            cout << "\nThis passport number already has a booking.\n";
            return;
        }

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




void PrintBooking(const sBooking& Booking)
{
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





void PrintBookingLine(const string& Line)
{
    

    sBooking Booking = ParseLineToBooking(Line);


    PrintBooking(Booking);
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
    string ChoiceInput;

    cout << "\nChoose option: ";
    cin >> ChoiceInput;

    if (!IsNumber(ChoiceInput))
        return (enMainMenuOptions)0;


    if (ChoiceInput.length() > 2)
        return (enMainMenuOptions)0;

    return (enMainMenuOptions)stoi(ChoiceInput);
}





void ShowMainMenu()
{
    cout << "\n========== Airline Booking ==========\n";
    cout << "1. Book Seat\n";
    cout << "2. Show Seats\n";
    cout << "3. Show Bookings\n";
    cout << "4. Find Booking\n";
    cout << "5. Delete Booking\n";
    cout << "6. Update Booking\n";
    cout << "7. Count Bookings\n";
    cout << "8. Exit\n";
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

        case eFindBooking:
            FindBooking();
            break;

        case eDeleteBooking:
            DeleteBooking();
            break;

        case eUpdateBooking:
            UpdateBooking();
            break;

        case eCountBookings:
            CountBookings();
            break;

        case eExit:
            return;

        default:
            cout << "\nInvalid option. Please choose from 1 to 8.\n";
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








bool FindBookingByPassportNumber(string PassportNumber, sBooking& Booking)
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

            Booking = ParseLineToBooking(Line);

            if (Booking.Passenger.PassportNumber == PassportNumber)
            {

                MyFile.close();
                return true;
            }

        }
        MyFile.close();
    }

    return false;
}





void  FindBooking()
{
    sBooking Booking;
    string PassportNumber;

    cout << "Enter Passport Number: ";
    getline(cin >> ws, PassportNumber);

    if (FindBookingByPassportNumber(PassportNumber, Booking))
    {
        PrintBooking(Booking);
    }
    else
    {
        cout << "\nBooking not found.\n";
    }
}





bool DeleteBookingByPassportNumber(string PassportNumber)
{
    fstream MyFile;

    MyFile.open(BookingsFileName, ios::in);
    
        if(!MyFile.is_open())
        
            return false;
        
        vector<string>Bookings;

        string Line;



        bool Isdeleted = false;

        while (getline(MyFile, Line))
        {
            if (Line.empty())
                continue;

            sBooking Booking = ParseLineToBooking(Line);



            if (Booking.Passenger.PassportNumber == PassportNumber)
            {
                Isdeleted = true;


                short rowIndex = Booking.Seat.Row - 1;
                short columnIndex = Booking.Seat.Column - FirstColumn;

                Seats[rowIndex][columnIndex].IsBooked = false;

            }
            else
            {
                Bookings.push_back(Line);
            }
        }

        MyFile.close();

        MyFile.open(BookingsFileName, ios::out);
        
            for (const string& Line : Bookings)
            {
                MyFile << Line << endl;
            }

            MyFile.close();

            return Isdeleted;
}





void DeleteBooking()
{
    sBooking Booking;
    string PassportNumber;


    cout << "Enter Passport Number: ";
    getline(cin >> ws, PassportNumber);


    string Answer;

    cout << "\nAre you sure you want to delete this booking? (Y/N): ";
    cin >> Answer;

    if (Answer.length() != 1)
    {
        cout << "\nInvalid answer.\n";
        return;
    }

    char Confirm = toupper((unsigned char)Answer[0]);

    if (Confirm != 'Y')
        return;


    if (DeleteBookingByPassportNumber(PassportNumber))
    {
        cout << "\nBooking deleted successfully.\n";
    }
    else
    {
        cout << "\nBooking not found.\n";
    }

}




void UpdateBooking()
{
    string PassportNumber;


    sBooking Booking;


    cout << "Enter Passport Number: ";
    getline(cin >> ws, PassportNumber);



    if (FindBookingByPassportNumber(PassportNumber, Booking))
    {
        PrintBooking(Booking);


        string UpdateChoiceInput;

        cout << "\n1. Update Passenger Info";
        cout << "\n2. Update Seat";
        cout << "\nChoose update option: ";

        cin >> UpdateChoiceInput;


        if (!IsNumber(UpdateChoiceInput) || UpdateChoiceInput.length() != 1)
        {
            cout << "\nInvalid update option.\n";
            return;
        }

        short UpdateChoice = stoi(UpdateChoiceInput);

        if (UpdateChoice == 1)
        {
            cout << "\nEnter New Passenger Information:\n";
            Booking.Passenger = ReadPassengerInfo();


            sBooking TempBooking;


            if (Booking.Passenger.PassportNumber != PassportNumber &&
                FindBookingByPassportNumber(Booking.Passenger.PassportNumber, TempBooking))
            {
                cout << "\nThis passport number already exists.\n";
                return;
            }

        }

        else if (UpdateChoice == 2)
        {
            string NewRowInput;
            string NewColumnInput;

            cout << "\nEnter New Row: ";
            cin >> NewRowInput;

            cout << "\nEnter New Column: ";
            cin >> NewColumnInput;

            if (!IsNumber(NewRowInput) ||
                NewRowInput.length() > 2 ||
                NewColumnInput.length() != 1)
            {
                cout << "\nInvalid seat.\n";
                return;
            }

            short NewRow = stoi(NewRowInput);
            char NewColumn = toupper((unsigned char)NewColumnInput[0]);

            if (NewRow < 1 || NewRow > NumberOfRows ||
                NewColumn < FirstColumn || NewColumn > LastColumn)
            {
                cout << "\nInvalid seat.\n";
                return;
            }

            short NewRowIndex = NewRow - 1;
            short NewColumnIndex = NewColumn - FirstColumn;

            if (NewRow == Booking.Seat.Row && NewColumn == Booking.Seat.Column)
            {
                cout << "\nThis is already the current seat.\n";
                return;
            }

            if (Seats[NewRowIndex][NewColumnIndex].IsBooked)
            {
                cout << "\nThis seat is already booked.\n";
                return;
            }

            short OldRowIndex = Booking.Seat.Row - 1;
            short OldColumnIndex = Booking.Seat.Column - FirstColumn;

            Seats[OldRowIndex][OldColumnIndex].IsBooked = false;
            Seats[NewRowIndex][NewColumnIndex].IsBooked = true;

            Booking.Seat = Seats[NewRowIndex][NewColumnIndex];

        }
    

    else
    {
        cout << "\nInvalid update option.\n";
        return;
    }

    UpdateBookingByPassportNumber(PassportNumber, Booking);
    cout << "\nBooking updated successfully.\n";
    }
    else
    {
        cout << "\nBooking not found.\n";
    }
}






bool UpdateBookingByPassportNumber(string PassportNumber, sBooking UpdatedBooking)
{
    fstream MyFile;

    MyFile.open(BookingsFileName, iostream::in);


    if (!MyFile.is_open())

        return false;

    vector<string> Bookings;


    string Line;


    bool IsUpdated = false;



    while (getline(MyFile, Line))
    {
        if (Line.empty())
            continue;


        sBooking Booking = ParseLineToBooking(Line);




        if (Booking.Passenger.PassportNumber == PassportNumber)
        {
            IsUpdated = true;
            Bookings.push_back(
                UpdatedBooking.Passenger.Name + "," +
                UpdatedBooking.Passenger.Phone + "," +
                UpdatedBooking.Passenger.Email + "," +
                UpdatedBooking.Passenger.Gender + "," +
                UpdatedBooking.Passenger.PassportNumber + "," +
                to_string(UpdatedBooking.Seat.Row) + "," +
                UpdatedBooking.Seat.Column
            );
        }
        else
        {
            Bookings.push_back(Line);
        }
    }

    MyFile.close();

    if (!IsUpdated)
        return false;


    MyFile.open(BookingsFileName, ios::out);

    for (const string& Line : Bookings)
    {
        MyFile << Line << endl;
    }

    MyFile.close();

    return true;

}




void CountBookings()
{
    fstream MyFile;


    MyFile.open(BookingsFileName, ios::in);

    int Count = 0;

    string Line;

    while (getline(MyFile, Line))
    {
        if (!Line.empty())
        {
            Count++;
        }

    }
    MyFile.close();

    cout << "\nTotal Bookings: " << Count << endl;

}









int main()
{
    InitializeSeats();

    LoadBookingsFromFile();

    StartApplication();


    return 0;
}