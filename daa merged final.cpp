#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <queue>
#include <limits.h>
#include <unordered_map>
#include <conio.h>
// For getch() function in Windows
#include <tuple>


using namespace std;


// Structure to represent a route

struct Route


 {

    string from;

    string to;

    double distance;

    double speed;

    double cost;

    string vehicle;

    string vehicleType;

    string departureTime;

    string arrivalTime;


};


// Structure for storing user profile

struct UserProfile

{

    string name;

    string email;

    int age;

    string phoneNumber;

    vector<string> travelHistory;

};


// Global variables


vector<string> cities;

vector<Route> routes;

string currentUser;

map<string, UserProfile> userProfiles;

UserProfile currentUserProfile;


// Function to mask input (for password)


// Function to mask password input

string maskInput()

{

    string password;

    char ch;

    cout << "Enter password: ";

    while (true)

        {

        ch = _getch();
    // Get character without displaying it

        if (ch == '\r')

        {
            // Enter key pressed

            cout << endl;

            break;

        }

        else if (ch == 8)

        {
            // Handle backspace

            if (!password.empty())

            {

                password.pop_back();

                cout << "\b \b";
                 // Remove asterisk from the screen
            }
        }

        else

        {

            password.push_back(ch);

            cout << "*";
            // Display asterisk
        }
    }

    return password;
}


// Global variables


// Function to load data from file

void loadData()

{

    ifstream inFile("cities_routes.txt");

    if (!inFile)

    {

        cout << "Error loading file. Ensure cities_routes.txt exists." << endl;

        return;

    }

    // Parse cities

    string line;

    while (getline(inFile, line))

    {

        if (line == "List of Cities:") break;

    }

    while (getline(inFile, line) && !line.empty())

    {

        cities.push_back(line.substr(2));
    // Ignore "- " prefix

    }

    // Parse routes

    while (getline(inFile, line))

    {

        if (line == "Routes:") break;

    }

    getline(inFile, line);
    // Skip the header
    while (getline(inFile, line))

    {

        Route route;

        stringstream ss(line);

        ss >> route.from >> route.to >> route.distance >> route.speed >> route.cost >> route.vehicle >> route.vehicleType >> route.departureTime >> route.arrivalTime;

        routes.push_back(route);

    }

    inFile.close();

}

// Function to handle user login

bool userLogin()

{

    string username, password;

    const string correctPassword = "user123";


    while (true)

    {

        cout << "Enter username: ";

        cin >> username;

        // Mask password input

        cin.ignore();
        // Clear newline character left in the buffer

        password = maskInput();

        if (password == correctPassword)

        {

            currentUser = username;

            cout << "Login successful! Welcome to Public Transport, " << username << "!\n";

            return true;

        }

         else

        {

            cout << "Incorrect password. Please try again.\n";

        }
    }
}

// Function to display available cities

void displayCities()

{

    cout << "Available Cities:\n";

    for (const auto &city : cities)

    {

        cout << "- " << city << endl;

    }
}

// Function to display routes

void displayRoutes()

{

    cout << setw(15) << "From" << setw(15) << "To" << setw(10) << "Distance"
         << setw(10) << "Speed" << setw(10) << "Cost" << setw(15)
         << "Vehicle" << setw(15) << "Type" << setw(15) << "Departure"
         << setw(15) << "Arrival\n";

    for (const auto &route : routes)

    {

        cout << setw(15) << route.from << setw(15) << route.to
             << setw(10) << route.distance << setw(10) << route.speed
             << setw(10) << route.cost << setw(15) << route.vehicle
             << setw(15) << route.vehicleType << setw(15) << route.departureTime
             << setw(15) << route.arrivalTime << "\n";

    }
}



// Function to search for a route

void searchRoute()

{

    string source, destination;

    cout << "Enter source city: ";

    cin >> source;

    cout << "Enter destination city: ";

    cin >> destination;

    cout << "Routes between " << source << " and " << destination << ":\n";

    cout << setw(15) << "From" << setw(15) << "To" << setw(10) << "Distance"
         << setw(10) << "Speed" << setw(10) << "Cost" << setw(15)
         << "Vehicle" << setw(15) << "Type" << setw(15) << "Departure"
         << setw(15) << "Arrival\n";


    bool found = false;

    for (const auto &route : routes)

    {

        if (route.from == source && route.to == destination)

        {

            found = true;

            cout << setw(15) << route.from << setw(15) << route.to
                 << setw(10) << route.distance << setw(10) << route.speed
                 << setw(10) << route.cost << setw(15) << route.vehicle
                 << setw(15) << route.vehicleType << setw(15) << route.departureTime
                 << setw(15) << route.arrivalTime << "\n";

        }

    }

    if (!found)

    {

        cout << "No routes found between " << source << " and " << destination << ".\n";

    }

}

// Function to make a booking

void makeBooking()

{

    string source, destination, vehicle, vehicleType;

    int age;

    cout << "Enter source city: ";

    cin >> source;

    cout << "Enter destination city: ";

    cin >> destination;

    cout << "Enter vehicle type (Bus/Train): ";

    cin >> vehicle;

    cout << "Enter vehicle subtype (AC/Sleeper Coach/Nonstop Bus/Express/Superfast/fast): ";

    cin >> vehicleType;

    cout << "Enter your age: ";

    cin >> age;

    double ticketCost = 0;

    for (const auto &route : routes)

        {

        if (route.from == source && route.to == destination && route.vehicle == vehicle && route.vehicleType == vehicleType)

        {

            ticketCost = route.cost;

            if (age < 12)

            {

                ticketCost /= 2;

                // Half ticket for children

            }

              else if (age > 60)

            {

                ticketCost *= 0.8;

                // Discount for senior citizens

            }

            cout << "Your ticket cost is: " << ticketCost << endl;

            currentUserProfile.travelHistory.push_back(source + " to " + destination);

            break;

        }
    }
}

// Function to update user profile

void updateProfile()

{
    string newName, newEmail, newPhoneNumber;

    cout << "Enter your new name: ";

    cin.ignore();
    // To ignore the previous newline character in the input buffer

    getline(cin, newName);

    cout << "Enter your new email: ";

    getline(cin, newEmail);

    cout << "Enter your new phone number: ";

    getline(cin, newPhoneNumber);

    currentUserProfile.name = newName;

    currentUserProfile.email = newEmail;

    currentUserProfile.phoneNumber = newPhoneNumber;


    cout << "Profile updated successfully!\n";
}


// Function to sort routes by cost and display them


void sortRoutesByCost()

{

    sort(routes.begin(), routes.end(), [](const Route& a, const Route& b)

    {

        return a.cost < b.cost;

    });

    cout << setw(15) << "From" << setw(15) << "To" << setw(10) << "Distance"
         << setw(10) << "Speed" << setw(10) << "Cost" << setw(15)
         << "Vehicle" << setw(15) << "Type" << setw(15) << "Departure"
         << setw(15) << "Arrival\n";

    for (const auto& route : routes)

    {

        cout << setw(15) << route.from << setw(15) << route.to
             << setw(10) << route.distance << setw(10) << route.speed
             << setw(10) << route.cost << setw(15) << route.vehicle
             << setw(15) << route.vehicleType << setw(15) << route.departureTime
             << setw(15) << route.arrivalTime << "\n";

    }
}


// Function to view the travel history for the user

void viewTravelHistory()

{

    if (currentUserProfile.travelHistory.empty())

    {

        cout << "You have no travel history.\n";

    }

    else

    {

        cout << "Your travel history:\n";

        for (const auto& trip : currentUserProfile.travelHistory)

        {

            cout << "- " << trip << endl;

        }
    }
}


// Function to apply promo code and provide a discount

void applyPromoCode()

{

    string promoCode;

    cout << "Enter promo code: ";

    cin >> promoCode;

    if (promoCode == "DISCOUNT10")

    {

        cout << "Promo code applied successfully! You get 10% off on your next booking.\n";

    }

    else if (promoCode == "HOLIDAY20")

    {

        cout << "Promo code applied successfully! You get 20% off on holiday bookings.\n";

    }

    else if (promoCode == "FESTIVE30")

    {

        cout << "Promo code applied successfully! You get 30% off during festive seasons.\n";

    }

    else

    {

        cout << "Invalid promo code. Try again.\n";

    }
}

// Function to get weather info (simulated here)

void getWeatherInfo()

{

    string city;

    cout << "Enter city name: ";

    cin >> city;

    // Example of simulated weather information

    cout << "Weather info for " << city << ":\n";

    cout << "Temperature: 25°C\n";

    cout << "Humidity: 60%\n";

    cout << "Conditions: Clear Sky\n";

}

// Function to plan a multi-city trip

void planMultiCityTrip()

{

    int numCities;

    cout << "Enter the number of cities in your multi-city trip: ";

    cin >> numCities;

    vector<string> citiesInTrip(numCities);

    cout << "Enter the names of cities you want to visit:\n";

    for (int i = 0; i < numCities; ++i)

    {

        cout << "City " << i + 1 << ": ";

        cin >> citiesInTrip[i];

    }

    cout << "You are planning a trip to:\n";

    for (const auto& city : citiesInTrip)

    {

        cout << "- " << city << endl;

    }
}

// Function to cancel a booking

void cancelBooking()

{

    string source, destination;

    cout << "Enter source city of the booking you want to cancel: ";

    cin >> source;

    cout << "Enter destination city of the booking you want to cancel: ";

    cin >> destination;

    auto it = find(currentUserProfile.travelHistory.begin(), currentUserProfile.travelHistory.end(),
                   source + " to " + destination);


    if (it != currentUserProfile.travelHistory.end())

    {

        currentUserProfile.travelHistory.erase(it);

        cout << "Your booking from " << source << " to " << destination << " has been cancelled.\n";

    }

    else

    {

        cout << "No booking found from " << source << " to " << destination << ".\n";

    }

}

// Function to view refund policies

void viewRefundPolicies()

{

    cout << "Refund Policy:\n";

    cout << "- If you cancel your booking 24 hours before departure, you will get a 50% refund.\n";

    cout << "- If you cancel your booking 48 hours before departure, you will get a 75% refund.\n";

    cout << "- No refund will be provided if you cancel within 24 hours of departure.\n";

}

// Function to handle payment method selection

void choosePaymentMethod()

{

    int paymentChoice;

    cout << "\nChoose Payment Method:\n";

    cout << "1. Credit Card\n";

    cout << "2. Debit Card\n";

    cout << "3. UPI\n";

    cout << "4. Net Banking\n";

    cout << "5. Wallet (e.g., Paytm, Google Pay)\n";

    cout << "6. Cash on Delivery\n";

    cout << "Enter your choice: ";

    cin >> paymentChoice;

    switch (paymentChoice)
    {

        case 1:

            cout << "You selected Credit Card. Enter your card details securely.\n";

            break;


        case 2:

            cout << "You selected Debit Card. Enter your card details securely.\n";

            break;


        case 3:

            cout << "You selected UPI. Use your UPI ID to complete the payment.\n";

            break;


        case 4:

            cout << "You selected Net Banking. Proceed with your banking credentials.\n";

            break;


        case 5:

            cout << "You selected Wallet. Ensure your wallet has sufficient balance.\n";

            break;


        case 6:

            cout << "You selected Cash on Delivery. Payment will be collected at delivery.\n";

            break;


        default:

            cout << "Invalid payment method. Please try again.\n";

            break;


    }
}

// Function to rate the service

void rateService()

{

    int rating;

    cout << "Rate the service (1-5): ";

    cin >> rating;

    if (rating >= 1 && rating <= 5)

    {

        cout << "Thank you for your feedback!\n";

    }

    else

    {

        cout << "Invalid rating. Please provide a rating between 1 and 5.\n";

    }
}

// Function to provide feedback

void giveFeedback()

{

    string feedback;

    cout << "Please provide your feedback: ";

    cin.ignore();

    getline(cin, feedback);

    cout << "Thank you for your feedback!\n";

}

// Function to contact support

void contactSupport()

{

    string issue;

    cout << "Describe your issue or inquiry: ";

    cin.ignore();

    getline(cin, issue);

    cout << "Thank you for contacting support. We will get back to you shortly.\n";

}

// Function to view system info

void viewSystemInfo()

{

    time_t now = time(0);

    char* dt = ctime(&now);

    cout << "System Info:\n";

    cout << "Current date and time: " << dt << endl;

    cout << "Version: 1.0.0\n";

    cout << "Developer: Your Name\n";

}
// Function to view available vehicles

void viewAvailableVehicles()

{

    cout << "Available Vehicles:\n";

    for (const auto& route : routes)

    {

        cout << "- " << route.vehicle << " (" << route.vehicleType << ")\n";

    }
}

// Function to track live travel status (simulated)

void trackLiveTravelStatus()

{

    string source, destination;

    cout << "Enter source city: ";

    cin >> source;

    cout << "Enter destination city: ";

    cin >> destination;


    bool found = false;

    for (const auto& route : routes)

    {

        if (route.from == source && route.to == destination)

        {

            found = true;

            cout << "Tracking live status for your travel from " << source << " to " << destination << ":\n";

            cout << "Vehicle: " << route.vehicle << ", Type: " << route.vehicleType << "\n";

            cout << "Departure: " << route.departureTime << ", Arrival: " << route.arrivalTime << "\n";

            // Simulated status (this would normally be updated in real-time)

            cout << "Status: On time.\n";

            break;

        }

    }

    if (!found)

    {

        cout << "No travel information available for this route.\n";

    }

}

// Function to change booking details

void changeBookingDetails()

{

    string oldSource, oldDestination, newSource, newDestination;

    cout << "Enter source city of the booking you want to change: ";

    cin >> oldSource;

    cout << "Enter destination city of the booking you want to change: ";

    cin >> oldDestination;

    auto it = find(currentUserProfile.travelHistory.begin(), currentUserProfile.travelHistory.end(),
                   oldSource + " to " + oldDestination);

    if (it != currentUserProfile.travelHistory.end())

    {

        cout << "Enter new source city: ";

        cin >> newSource;

        cout << "Enter new destination city: ";

        cin >> newDestination;

        *it = newSource + " to " + newDestination;

        cout << "Booking details updated from " << oldSource << " to " << oldDestination
             << " to " << newSource << " to " << newDestination << ".\n";

    }

    else

    {

        cout << "No booking found from " << oldSource << " to " << oldDestination << ".\n";

    }
}


// Function to view special offers


void viewSpecialOffers()

{

    cout << "Special Offers:\n";

    cout << "- 10% off for senior citizens on all bookings.\n";

    cout << "- Free meal on routes over $100.\n";

    cout << "- 15% off on round-trip bookings.\n";

    cout << "- Group bookings (3+ people) get an additional 10% off.\n";

    cout << "- Book a ticket for $200+ and get a free hotel voucher.\n";

}

// Function to filter routes by vehicle type


void filterRoutesByVehicleType()

{

    string vehicleType;

    cout << "Enter the vehicle type to filter (e.g., AC, Nonstop Bus, Express): ";

    cin.ignore();

    getline(cin, vehicleType);


    cout << setw(15) << "From" << setw(15) << "To" << setw(10) << "Distance"
         << setw(10) << "Speed" << setw(10) << "Cost" << setw(15)
         << "Vehicle" << setw(15) << "Type" << setw(15) << "Departure"
         << setw(15) << "Arrival\n";


    bool found = false;

    for (const auto &route : routes)

    {

        if (route.vehicleType == vehicleType)

        {

            found = true;

            cout << setw(15) << route.from << setw(15) << route.to
                 << setw(10) << route.distance << setw(10) << route.speed
                 << setw(10) << route.cost << setw(15) << route.vehicle
                 << setw(15) << route.vehicleType << setw(15) << route.departureTime
                 << setw(15) << route.arrivalTime << "\n";

        }
    }

    if (!found)

    {

        cout << "No routes found for the selected vehicle type.\n";

    }
}

// Function to calculate travel duration

void calculateTravelDuration()

{

    string source, destination;

    cout << "Enter source city: ";

    cin >> source;

    cout << "Enter destination city: ";

    cin >> destination;

    bool found = false;

    for (const auto &route : routes)

    {

        if (route.from == source && route.to == destination)

        {

            found = true;

            double duration = route.distance / route.speed;

            cout << "The estimated travel duration from " << source << " to " << destination
                 << " is " << fixed << setprecision(2) << duration << " hours.\n";

            break;


        }
    }

    if (!found)

    {

        cout << "No routes found between " << source << " and " << destination << ".\n";

    }
}

// Function to view top destinations


void viewTopDestinations()

{

    map<string, int> destinationFrequency;


    for (const auto &route : routes)

    {

        destinationFrequency[route.to]++;

    }

    vector<pair<string, int>> sortedDestinations(destinationFrequency.begin(), destinationFrequency.end());

    sort(sortedDestinations.begin(), sortedDestinations.end(), [](const pair<string, int> &a, const pair<string, int> &b)
         { return b.second < a.second; });


    cout << "Top destinations based on frequency:\n";

    for (const auto &destination : sortedDestinations)

    {

        cout << "- " << destination.first << " (Visited " << destination.second << " times)\n";

    }
}

// Function to get estimated costs for travel


void getEstimatedCosts()

{

    string source, destination;

    cout << "Enter source city: ";

    cin >> source;

    cout << "Enter destination city: ";

    cin >> destination;

    double totalCost = 0.0;

    bool found = false;

    for (const auto &route : routes)

    {

        if (route.from == source && route.to == destination)

        {

            totalCost += route.cost;

            found = true;

        }
    }

    if (found)

    {

        cout << "The estimated total cost from " << source << " to " << destination << " is " << totalCost << ".\n";

    }

    else

    {

        cout << "No routes found between " << source << " and " << destination << ".\n";

    }
}

// Function to generate travel itinerary

void generateTravelItinerary()

{

    int numCities;

    cout << "Enter the number of cities in your itinerary: ";

    cin >> numCities;

    vector<string> itinerary(numCities);

    cout << "Enter the cities:\n";

    for (int i = 0; i < numCities; ++i)

    {

        cout << "City " << i + 1 << ": ";

        cin >> itinerary[i];

    }

    cout << "Your travel itinerary:\n";

    for (size_t i = 0; i < itinerary.size(); ++i)

    {

        cout << itinerary[i];

        if (i != itinerary.size() - 1)
            cout << " -> ";

    }

    cout << endl;

}

// Function to save favorite routes


void saveFavoriteRoute()

{

    string source, destination;

    cout << "Enter source city: ";

    cin >> source;

    cout << "Enter destination city: ";

    cin >> destination;

    bool found = false;

    for (const auto& route : routes)

    {

        if (route.from == source && route.to == destination)

        {

            found = true;

            currentUserProfile.travelHistory.push_back("Favorite: " + source + " to " + destination);

            cout << "Route from " << source << " to " << destination << " added to favorites.\n";

            break;

        }
    }

    if (!found)

    {

        cout << "No such route found to add to favorites.\n";

    }

}

// Function to view travel alerts and notifications


void viewTravelAlerts()

{

    cout << "Travel Alerts & Notifications:\n";

    cout << "- Heavy rainfall expected in Bangalore on Jan 3.\n";

    cout << "- Scheduled maintenance on Route 1 between Mysore and Chennai.\n";

    cout << "- Discounts available on weekend travel to Goa.\n";

}

// Function to share travel plans with friends

void shareTravelPlans()

{
    string friendEmail, travelDetails;

    cout << "Enter your friend's email: ";

    cin >> friendEmail;

    cout << "Enter the travel details you'd like to share: ";

    cin.ignore();

    getline(cin, travelDetails);

    cout << "Travel plan shared successfully with " << friendEmail << ".\n";

}

// Function to view nearby attractions

void viewNearbyAttractions()

{

    string city;

    cout << "Enter the city to view nearby attractions: ";

    cin >> city;

    cout << "Nearby attractions in " << city << ":\n";

    cout << "- Historical Monument\n";

    cout << "- Popular Museum\n";

    cout << "- Beautiful Park\n";

}

// Function to enable dark mode

void enableDarkMode()

{

    char choice;

    cout << "Enable dark mode? (y/n): ";

    cin >> choice;

    if (choice == 'y' || choice == 'Y')

    {

        cout << "Dark mode enabled.\n";

        // Simulated change of display
    }

    else

    {

        cout << "Dark mode not enabled.\n";

    }
}

// Add new menu options to display in the main menu


void displayMainMenu()

{

    int choice;

    while (true)

    {

        cout << "\nMain Menu:\n";

        cout << "1. View Cities\n";

        cout << "2. View Routes\n";

        cout << "3. Search for a Route\n";

        cout << "4. Book a Ticket\n";

        cout << "5. Update Profile\n";

        cout << "6. Sort Routes by Cost\n";

        cout << "7. View Travel History\n";

        cout << "8. Apply Promo Code\n";

        cout << "9. Get Weather Info\n";

        cout << "10. Plan a Multi-City Trip\n";

        cout << "11. Cancel Booking\n";

        cout << "12. View Refund Policies\n";

        cout << "13. Choose Payment Method\n";

        cout << "14. Rate the Service\n";

        cout << "15. Give Feedback\n";

        cout << "16. Contact Support\n";

        cout << "17. View System Info\n";

        cout << "18. View Available Vehicles\n";

        cout << "19. Track Live Travel Status\n";

        cout << "20. Change Booking Details\n";

        cout << "21. View Special Offers\n";

        cout << "22. Filter Routes by Vehicle Type\n";

        cout << "23. Calculate Travel Duration\n";

        cout << "24. View Top Destinations\n";

        cout << "25. Get Estimated Costs\n";

        cout << "26. Generate Travel Itinerary\n";

        cout << "27. Save Favorite Routes\n";

        cout << "28. View Travel Alerts and Notifications\n";

        cout << "29. Share Travel Plans with Friends\n";

        cout << "30. View Nearby Attractions\n";

        cout << "31. Enable Dark Mode\n";

        cout << "32. Log Out\n";

        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)

        {

            case 1:
                displayCities();

                break;


            case 2:
                displayRoutes();

                break;


            case 3:
                searchRoute();

                break;


            case 4:
                makeBooking();

                break;


            case 5:
                updateProfile();

                break;


            case 6:
                sortRoutesByCost();

                break;


            case 7:
                viewTravelHistory();

                break;


            case 8:
                applyPromoCode();

                break;


            case 9:
                getWeatherInfo();

                break;


            case 10:
                planMultiCityTrip();

                break;


            case 11:
                cancelBooking();

                break;


            case 12:
                viewRefundPolicies();

                break;


            case 13:
                choosePaymentMethod();

                break;


            case 14:
                rateService();

                break;


            case 15:
                giveFeedback();

                break;


            case 16:
                contactSupport();

                break;


            case 17:
                viewSystemInfo();

                break;


            case 18:
                viewAvailableVehicles();

                break;


            case 19:
                trackLiveTravelStatus();

                break;


            case 20:
                changeBookingDetails();

                break;



            case 21:
                viewSpecialOffers();

                break;


            case 22:
                filterRoutesByVehicleType();

                break;


            case 23:
                 calculateTravelDuration();

                 break;


            case 24:
                viewTopDestinations();

                break;


            case 25:
                 getEstimatedCosts();

                 break;


            case 26:
               generateTravelItinerary();

               break;


            case 27:
                saveFavoriteRoute();

                break;


            case 28:
                viewTravelAlerts();

                break;


            case 29:
                shareTravelPlans();

                break;


            case 30:
                viewNearbyAttractions();

                 break;


            case 31:
                enableDarkMode();

                break;



            case 32:
                cout << "Logging out...\n";

                currentUser = "";

                return;


            default:
                cout << "Invalid choice, please try again.\n";

                break;

        }
    }
}

struct Edge

{

    int to;

    int weight;

};

class CityGraph

{

private:

    vector<vector<Edge>> graph;

    unordered_map<int, string> colonyNames;

    unordered_map<int, string> colonyCategories;

    unordered_map<int, int> totalHouses;
          // Number of houses in the colony

    unordered_map<int, int> kacchaHouses;
          // Number of kaccha houses

    int totalRoadCost;


public:

    CityGraph(int initialColonies) : totalRoadCost(0)

    {

        graph.resize(initialColonies);

    }

    void setColonyName(int id, const string& name)

    {

        colonyNames[id] = name;

    }

    string getColonyName(int id) const

    {

        return colonyNames.count(id) ? colonyNames.at(id) : "Unknown";

    }

    void addColony(const string& colonyName)

    {

        int colonyId = graph.size();

        graph.push_back({});

        colonyNames[colonyId] = colonyName;

        totalHouses[colonyId] = 0;
         // Initialize number of houses to 0

        kacchaHouses[colonyId] = 0;
        // Initialize number of kaccha houses to 0

        cout << "New colony added: " << colonyName << " (ID: " << colonyId << ")" << endl;

    }

    void removeColony(int id)

     {

        if (id < 0 || id >= graph.size() || colonyNames.count(id) == 0)

        {

            cerr << "Error: Invalid colony ID!" << endl;

            return;

        }

        for (const Edge& edge : graph[id])

        {

            int neighbor = edge.to;

            graph[neighbor].erase(remove_if(graph[neighbor].begin(), graph[neighbor].end(),
                                             [id](const Edge& e) { return e.to == id; }),
                                   graph[neighbor].end());

            totalRoadCost -= edge.weight;

        }

        graph[id].clear();

        colonyNames.erase(id);

        colonyCategories.erase(id);

        totalHouses.erase(id);

        kacchaHouses.erase(id);

        cout << "Colony " << id << " removed successfully." << endl;

    }

    void addRoad(int from, int to, int weight)

     {

        if (from < 0 || to < 0 || from >= graph.size() || to >= graph.size() || weight <= 0)
        {
            cerr << "Error: Invalid input for adding road!" << endl;

            return;

        }

        graph[from].push_back({to, weight});

        graph[to].push_back({from, weight});

        totalRoadCost += weight;

        cout << "Road added between " << getColonyName(from) << " and " << getColonyName(to)
             << " with distance " << weight << endl;

    }

    void removeRoad(int from, int to)

    {

        auto removeEdge = [&](int from, int to)

         {

            for (auto it = graph[from].begin(); it != graph[from].end(); ++it)

            {

                if (it->to == to)

                {

                    totalRoadCost -= it->weight;

                    graph[from].erase(it);

                    return true;

                }
            }

            return false;

        };


        bool removedFrom = removeEdge(from, to);

        bool removedTo = removeEdge(to, from);

        if (removedFrom && removedTo)

        {

            cout << "Road removed between " << getColonyName(from) << " and " << getColonyName(to) << "." << endl;

        }

        else

        {

            cerr << "Error: Road not found between specified colonies!" << endl;

        }
    }

    void displayGraph() const

     {

        cout << "\nCity Connectivity Graph:\n";

        for (int i = 0; i < graph.size(); ++i)

        {

            if (colonyNames.count(i) == 0) continue;

            cout << getColonyName(i) << " (ID: " << i << ") -> ";

            for (const Edge& edge : graph[i])

            {

                cout << "[" << getColonyName(edge.to) << ", Distance: " << edge.weight << "] ";

            }

            cout << endl;

        }
    }

    vector<int> findShortestPaths(int start) const

    {

        int n = graph.size();

        vector<int> distance(n, INT_MAX);

        distance[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        pq.push({0, start});


        while (!pq.empty())

        {

            int currentDistance = pq.top().first;

            int currentNode = pq.top().second;

            pq.pop();


            if (currentDistance > distance[currentNode]) continue;


            for (const Edge& edge : graph[currentNode])

            {

                int newDistance = currentDistance + edge.weight;

                if (newDistance < distance[edge.to])

                {

                    distance[edge.to] = newDistance;

                    pq.push({newDistance, edge.to});

                }
            }
        }

        return distance;

    }

    void setColonyCategory(int id)

     {

        cout << "Select a category for colony " << getColonyName(id) << ":\n";

        cout << "1. Slum\n2. Residential\n3. Commercial\n";

        int choice;

        cin >> choice;

        string category = (choice == 1) ? "Slum" : (choice == 2) ? "Residential" : (choice == 3) ? "Commercial" : "Unknown";

        colonyCategories[id] = category;

        cout << "Category set for colony " << getColonyName(id) << ": " << category << endl;

    }

    void displayColoniesByCategory() const

     {

        unordered_map<string, vector<int>> categoryMap;

        for (const auto& pair : colonyCategories)

        {

            categoryMap[pair.second].push_back(pair.first);

        }

        cout << "\nColonies by Category:\n";

        for (const auto& entry : categoryMap)

        {

            cout << "Category: " << entry.first << "\n";

            for (int id : entry.second)

            {

                cout << "  - " << getColonyName(id) << " (ID: " << id << ")\n";

            }
        }
    }

    void displayCategoryCounts() const

    {

        unordered_map<string, int> categoryCounts;

        for (const auto& pair : colonyCategories)

        {

            categoryCounts[pair.second]++;

        }

        cout << "\nCategory Counts:\n";

        for (const auto& entry : categoryCounts)

        {

            cout << entry.first << ": " << entry.second << endl;

        }
    }

    void displayColonyDetails() const

    {

        cout << "\nColony Details:\n";

        for (const auto& entry : colonyNames)

        {

            int id = entry.first;

            int pakkaHouses = totalHouses.at(id) - kacchaHouses.at(id);

            cout << "Colony ID: " << id << ", Name: " << entry.second
                 << ", Connections: " << graph[id].size()
                 << ", Category: " << (colonyCategories.count(id) ? colonyCategories.at(id) : "Uncategorized")
                 << ", Total Houses: " << totalHouses.at(id)
                 << ", Kaccha Houses: " << kacchaHouses.at(id)
                 << ", Pakka Houses: " << pakkaHouses << endl;

        }

        cout << endl;

    }

    void addHouses(int id, int total, int kaccha)

    {

        if (id < 0 || id >= graph.size() || colonyNames.count(id) == 0 || total < kaccha)

        {

            cerr << "Error: Invalid input!" << endl;

            return;

        }

        totalHouses[id] += total;

        kacchaHouses[id] += kaccha;

        cout << "House details updated for colony " << getColonyName(id) << "." << endl;

    }

    int findMostConnectedColony() const

     {

        int maxConnections = 0, mostConnectedId = -1;

        for (int i = 0; i < graph.size(); ++i)

        {

            if (graph[i].size() > maxConnections)

            {

                maxConnections = graph[i].size();

                mostConnectedId = i;

            }
        }

        return mostConnectedId;

    }

    int getTotalRoadCost() const

    {

        return totalRoadCost;

    }

    vector<vector<Edge>>& getGraph()

    {

        return graph;

    }

    void updateColonyCategory(int id, const string& newCategory)

    {

      if (colonyCategories.count(id) > 0)

    {

          colonyCategories[id] = newCategory;

          cout << "Colony category updated to: " << newCategory << endl;

      }

      else

       {

          cerr << "Error: Colony ID not found!" << endl;

       }

     }

};


void displayInstructions()

{

    cout << "\nInstructions:\n";

    cout << "1. Add colonies.\n";

    cout << "2. Add roads.\n";

    cout << "3. Remove a colony.\n";

    cout << "4. Remove a road.\n";

    cout << "5. View graph.\n";

    cout << "6. Find shortest paths.\n";

    cout << "7. Find colony with most connections.\n";

    cout << "8. View infrastructure cost.\n";

    cout << "9. View colony details.\n";

    cout << "10. Set colony category.\n";

    cout << "11. Display colonies by category.\n";

    cout << "12. Display category counts.\n";

    cout << "13. Add house details.\n";

    cout << "14. updateColonyCategory.\n";

    cout << "15. Exit.\n";

}


// Base class for Vehicles

class Vehicle

{

protected:

    string id;
    // Vehicle identifier

    string type;
    // Type of vehicle (Electric, Bicycle, etc.)

    string source;
    // Source of the vehicle

    bool isAvailable;
    // Availability of the vehicle

    vector<string> feedback;
    // Feedback for the vehicle


public:

    Vehicle(string id, string type, string source) : id(id), type(type), source(source), isAvailable(true) {}

    virtual ~Vehicle() {}


    string getId() { return id; }

    string getType() { return type; }

    string getSource() { return source; }

    bool isAvailableForRent() { return isAvailable; }


    // Method to book the vehicle (mark as unavailable)


    void book()

    {

        if (isAvailable)

        {

            isAvailable = false;

            cout << "Vehicle " << id << " has been booked successfully." << endl;

        }

        else

        {

            cout << "Vehicle " << id << " is not available." << endl;

        }
    }

    // Method to release the vehicle (mark as available)

    void release()

    {

        isAvailable = true;

        cout << "Vehicle " << id << " is now available for rent." << endl;

    }

    // Method to add feedback for the vehicle

    void addFeedback(const string &feedbackText)

    {

        feedback.push_back(feedbackText);

    }

    // Display the feedback for the vehicle

    void displayFeedback()

    {

        cout << "Feedback for Vehicle " << id << ":\n";

        for (const auto &f : feedback)

        {

            cout << "- " << f << endl;

        }
    }
};

// ElectricVehicle Class inheriting from Vehicle


class ElectricVehicle : public Vehicle

{

public:

    ElectricVehicle(string id, string source) : Vehicle(id, "Electric", source) {}

};

// Bicycle Class inheriting from Vehicle


class Bicycle : public Vehicle

{

public:

    Bicycle(string id, string source) : Vehicle(id, "Bicycle", source) {}

};

// PublicTransport Class for Route Management

class PublicTransport

{

private:
    map<string, tuple<string, string, vector<string>, double>> routes;
    // routeName -> (source, destination, viaRoutes, distance)


public:
    // Load routes from a file

    void loadRoutesFromFile()

    {

        ifstream file("routes.txt");

        if (!file.is_open())

        {

            cout << "No existing route data found.\n";

            return;

        }

        string line;

        string routeName;

        string source, destination;

        vector<string> viaRoutes;

        double distance = 0.0;

        // Read data from the file and parse routes

        while (getline(file, line))

        {

            if (line.find("Route: ") != string::npos)

            {

                if (!routeName.empty())

                {

                    routes[routeName] = make_tuple(source, destination, viaRoutes, distance);

                    viaRoutes.clear();

                }

                routeName = line.substr(7);

            }

            else if (line.find("Source: ") != string::npos)

            {

                source = line.substr(8);

            }

            else if (line.find("Destination: ") != string::npos)

            {

                destination = line.substr(14);

            }

            else if (line.find("Via Routes: ") != string::npos)

            {

                stringstream ss(line.substr(12));

                string stop;

                while (getline(ss, stop, ' '))

                {

                    if (!stop.empty())

                    {

                        viaRoutes.push_back(stop);

                    }
                }
            }

            else if (line.find("Distance: ") != string::npos)

            {

                distance = stod(line.substr(10));

            }
        }


        // Store the last route in the map

        if (!routeName.empty())

        {

            routes[routeName] = make_tuple(source, destination, viaRoutes, distance);

        }

        file.close();

    }



    // Display all available routes

    void displayRoutes()

    {

        if (routes.empty())

        {

            cout << "No routes available.\n";

            return;

        }

        cout << "Available Public Transport Routes:\n";

        for (const auto &route : routes)

        {

            cout << "Route: " << route.first << "\n";

            cout << "Source: " << get<0>(route.second) << "\n";

            cout << "Destination: " << get<1>(route.second) << "\n";

            cout << "Via Routes: ";

            for (const auto &stop : get<2>(route.second))

            {

                cout << stop << " ";

            }

            cout << "\nDistance: " << get<3>(route.second) << " km\n\n";

        }
    }

    // Method to find the shortest route using Dijkstra's algorithm

    void findShortestRoute(string source, string destination)

    {

        cout << "Calculating shortest route from " << source << " to " << destination << "...\n";

        unordered_map<string, double> minDist;

        unordered_map<string, string> prev;



        // Initialize distances to infinity

        for (const auto &entry : routes)

        {

            minDist[get<0>(entry.second)] = numeric_limits<double>::max();

            minDist[get<1>(entry.second)] = numeric_limits<double>::max();

        }

        minDist[source] = 0;



        // Priority queue to select the node with the smallest distance

        auto cmp = [&minDist](const string &a, const string &b)

        {

            return minDist[a] > minDist[b];

        };

        priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);

        pq.push(source);


        // Dijkstra's algorithm to find the shortest path

        while (!pq.empty())

        {

            string current = pq.top();

            pq.pop();

            for (const auto &entry : routes)

            {

                if (get<0>(entry.second) == current)

                {

                    string next = get<1>(entry.second);

                    double weight = get<3>(entry.second);


                    if (minDist[current] + weight < minDist[next])

                    {

                        minDist[next] = minDist[current] + weight;

                        prev[next] = current;

                        pq.push(next);

                    }
                }
            }
        }

        // Print the shortest route if found

        if (minDist[destination] == numeric_limits<double>::max())

        {

            cout << "No route found from " << source << " to " << destination << ".\n";

            return;

        }

        vector<string> path;

        for (string at = destination; at != ""; at = prev[at])

        {

            path.push_back(at);

        }

        reverse(path.begin(), path.end());


        cout << "Shortest Route: ";

        for (const auto &stop : path)

        {

            cout << stop << " ";

        }

        cout << "\nTotal Distance: " << minDist[destination] << " km\n";

    }



    // Save a new route to the file

    void saveRouteToFile(const string &routeName, const string &source, const string &destination, const vector<string> &viaRoutes, double distance)

    {

        ofstream file("routes.txt", ios::app);

        if (file.is_open())

        {

            file << "Route: " << routeName << "\n";

            file << "Source: " << source << "\n";

            file << "Destination: " << destination << "\n";

            file << "Via Routes: ";

            for (const auto &route : viaRoutes)

            {

                file << route << " ";

            }

            file << "\n";

            file << "Distance: " << distance << " km\n";

            file << "----------------------------\n";

            file.close();

        }

        else

        {

            cout << "Error saving routes to file.\n";

        }
    }



     // Search routes by source and destination

    void searchRouteBySourceDestination(const string &source, const string &destination)

{

        bool found = false;

        cout << "Searching for routes from " << source << " to " << destination << "...\n";

        for (const auto &route : routes)

        {

            string routeSource = get<0>(route.second);

            string routeDestination = get<1>(route.second);

            if (routeSource == source && routeDestination == destination)

            {

                cout << "Found Route: " << route.first << "\n";

                cout << "Source: " << routeSource << "\n";

                cout << "Destination: " << routeDestination << "\n";

                cout << "Via Routes: ";

                for (const auto &stop : get<2>(route.second))

                {

                    cout << stop << " ";

                }

                cout << "\nDistance: " << get<3>(route.second) << " km\n";

                found = true;

            }
        }

        if (!found)

        {

            cout << "No routes found from " << source << " to " << destination << ".\n";

        }
    }

};

// Carpool System

class Carpool

{

private:

    struct CarpoolGroup

    {

        string driverId;

        string source;

        string destination;

        vector<string> viaRoutes;

        double distance;

        vector<string> passengers;

    };

    vector<CarpoolGroup> carpools;


public:

    // Load carpool data from file

    void loadCarpoolsFromFile()

    {

        ifstream file("carpool_data.txt");

        if (!file.is_open())

        {

            cout << "No existing carpool data found.\n";

            return;

        }

        string line;

        while (getline(file, line))

        {

            if (line.find("Driver ID: ") != string::npos)

        {

                string driverId = line.substr(11);

                getline(file, line);

                string source = line.substr(8);

                getline(file, line);

                string destination = line.substr(13);

                getline(file, line);

                stringstream ss(line.substr(12));
                 // Skip "Via Routes: "

                vector<string> viaRoutes;

                string stop;

                while (getline(ss, stop, ','))

                {

                    if (!stop.empty())

                    {

                        viaRoutes.push_back(stop);

                    }
                }

                getline(file, line);

                double distance = stod(line.substr(10));

                carpools.push_back({driverId, source, destination, viaRoutes, distance, {}});

            }
        }

        file.close();

    }

    // Create a new carpool

    void createCarpool(string driverId, string source, string destination, const vector<string> &viaRoutes, double distance)

    {

        carpools.push_back({driverId, source, destination, viaRoutes, distance, {}});

        saveCarpoolToFile(driverId, source, destination, viaRoutes, distance);

        cout << "Carpool created for Driver ID: " << driverId << "\n";

    }

    // Add a passenger to a carpool

    void addPassenger(string passenger, string source, string destination)

    {

        for (auto &carpool : carpools)

        {

            if (carpool.source == source && (carpool.destination == destination || find(carpool.viaRoutes.begin(), carpool.viaRoutes.end(), destination) != carpool.viaRoutes.end()))

            {

                if (carpool.passengers.size() >= 3)

                {

                    cout << "Carpool with Driver ID: " << carpool.driverId << " is already full.\n";

                    return;

                }

                if (find(carpool.passengers.begin(), carpool.passengers.end(), passenger) == carpool.passengers.end())

                {

                    carpool.passengers.push_back(passenger);

                    cout << "Passenger " << passenger << " added to carpool with Driver ID: " << carpool.driverId << "\n";

                    cout << "Total Passengers: " << carpool.passengers.size() << "/3\n";

                    saveCarpoolToFile(carpool.driverId, carpool.source, carpool.destination, carpool.viaRoutes, carpool.distance);

                    return;

                }

                else

                {

                    cout << "Passenger " << passenger << " is already in this carpool.\n";

                    return;

                }
            }
        }

        cout << "No matching carpool found for " << passenger << ".\n";

    }


    // Display active carpools

    void displayCarpools()

{

        if (carpools.empty())

        {

            cout << "No active carpools.\n";

            return;

        }

        cout << "Active Carpools:\n";

        for (const auto &carpool : carpools)

        {

            cout << "Driver ID: " << carpool.driverId << "\nSource: " << carpool.source
                 << "\nDestination: " << carpool.destination << "\nVia Routes: ";

            for (const auto &route : carpool.viaRoutes)

            {

                cout << route << " ";

            }

            cout << "\nPassengers: ";

            for (const auto &passenger : carpool.passengers)

            {

                cout << passenger << " ";

            }

            cout << "\nDistance: " << carpool.distance << " km\n\n";

        }
    }



    // Save carpool data to a file

    void saveCarpoolToFile(const string &driverId, const string &source, const string &destination, const vector<string> &viaRoutes, double distance)

{

        ofstream file("carpool_data.txt", ios::app);

        if (file.is_open())

        {

            file << "Driver ID: " << driverId << "\nSource: " << source
                 << "\nDestination: " << destination << "\nVia Routes: ";

            for (const auto &route : viaRoutes)

            {

                file << route << ",";

            }

            file << "\nDistance: " << distance << "\n";

            file.close();

        }

        else

        {

            cout << "Error saving carpool data to file.\n";

        }
    }

};



// Rental System

class RentalSystem

{

private:

    vector<Vehicle *> vehicles;

    vector<pair<string, string>> rentalHistory;
     // (vehicleID, renterID)


public:

    ~RentalSystem()

    {

        for (auto vehicle : vehicles)

        {

            delete vehicle;

        }
    }


    // Add a vehicle to the rental system

    void addVehicle(Vehicle *vehicle)

    {

        vehicles.push_back(vehicle);

    }


    // Load vehicles from file

    void loadVehiclesFromFile()

    {

        ifstream file("vehicles.txt");

        if (!file.is_open())

        {

            cout << "No existing vehicle data found.\n";

            return;

        }

        string line, id, type, source;

        while (getline(file, line))

            {

            if (line.find("Vehicle ID: ") != string::npos)

            {

                id = line.substr(12);

            }

             else if (line.find("Type: ") != string::npos)

            {

                type = line.substr(6);

            }

            else if (line.find("Source: ") != string::npos)

            {

                source = line.substr(8);

                if (type == "Electric")

                {

                    addVehicle(new ElectricVehicle(id, source));

                }

                 else if (type == "Bicycle")

                {

                    addVehicle(new Bicycle(id, source));

                }

                else

                {

                    addVehicle(new Vehicle(id, type, source));

                }
            }
        }

        file.close();

    }




    // Save vehicles to file

    void saveVehiclesToFile()

    {

        ofstream file("vehicles.txt");

        if (file.is_open())

        {

            for (auto vehicle : vehicles)


            {



                file << "Vehicle ID: " << vehicle->getId() << "\n";

                file << "Type: " << vehicle->getType() << "\n";

                file << "Source: " << vehicle->getSource() << "\n";

                file << "Status: " << (vehicle->isAvailableForRent() ? "available" : "booked") << "\n";

            }

            file.close();

        }

        else

        {

            cout << "Error saving vehicles to file.\n";

        }
    }

    void displayAvailableVehicles()

    {

        cout << "Available Vehicles:\n";

        for (auto vehicle : vehicles)

        {

            if (vehicle->isAvailableForRent())

            {

                cout << "ID: " << vehicle->getId() << "\tType: " << vehicle->getType() << "\tSource: " << vehicle->getSource() << "\tStatus: available" << endl;

            }
        }
    }



    // Book a vehicle for rent

    void bookVehicle(const string &id, const string &renterID)

    {

        for (auto vehicle : vehicles)

        {

            if (vehicle->getId() == id && vehicle->isAvailableForRent())

            {

                vehicle->book();

                rentalHistory.emplace_back(id, renterID);

                cout << "Vehicle " << id << " booked successfully by " << renterID << ".\n";

                saveVehiclesToFile();
                // Save updated data to file

                return;

            }
        }

        cout << "Vehicle ID not found or already booked.\n";

    }



    // Release a vehicle from rent

    void releaseVehicle(const string &id)

    {

        for (auto vehicle : vehicles)

        {

            if (vehicle->getId() == id && !vehicle->isAvailableForRent())

            {

                vehicle->release();

                saveVehiclesToFile();
                // Save updated data to file

                cout << "Vehicle " << id << " released successfully.\n";

                return;

            }
        }

        cout << "Vehicle ID not found or not booked.\n";

    }



    // Search available vehicles by source

    void searchAvailableVehiclesBySource(const string &source)

    {

        ifstream file("vehicles.txt");

        if (!file.is_open())

        {

            cout << "Error: Could not open vehicles data file.\n";

            return;

        }

        cout << "Available Vehicles at Source: " << source << "\n";

        bool found = false;


        string vehicleSource, id, type;

        while (file >> vehicleSource >> id >> type)

        {

            if (vehicleSource == source)

            {

                bool isAvailable = true;


                // Check if the vehicle is rented

                for (const auto &entry : rentalHistory)

                {

                    if (entry.first == id)

                     {

                        isAvailable = false;

                        break;

                    }
                }

                if (isAvailable)

                {

                    cout << vehicleSource << "\t" << id << "\t" << type << endl;

                    found = true;

                }
            }
        }

        if (!found)

        {

            cout << "No available vehicles found at " << source << ".\n";

        }

        file.close();

    }



    // Display the rental history

    void displayRentalHistory()

    {

        cout << "Rental History:\n";

        for (const auto &entry : rentalHistory)

        {

            cout << "Vehicle ID: " << entry.first << " Renter ID: " << entry.second << endl;

        }
    }
};




// Structure to represent a traffic signal

struct TrafficSignal

{
    string location;

    string currentState;
    // "Red", "Yellow", "Green"

    int timer;
   // Duration in seconds

    int vehicleCount;
    // Number of vehicles waiting at the signal

    bool isPrioritized;
     // True if the signal is prioritized for emergency vehicles

    bool isActive;
        // Whether the signal is active or temporarily deactivated

    vector<string> history;
    // Record of state changes


};

// Initialize traffic signals with default states

void initializeSignals(vector<TrafficSignal>& signals)
{
    signals.push_back({"Main Street", "Red", 30, 0, false, true, {"Red"}});

    signals.push_back({"Highway 1", "Green", 60, 0, false, true, {"Green"}});

    signals.push_back({"Downtown", "Yellow", 10, 0, false, true, {"Yellow"}});
}

// Display current status of all traffic signals

void displaySignals(const vector<TrafficSignal>& signals)
{
    cout << "\nCurrent Traffic Signal Status:\n";

    cout << "---------------------------------\n";

    for (const auto& signal : signals)

        {
            cout << "Location: " << signal.location

                << " | State: " << signal.currentState

                << " | Timer: " << signal.timer << " seconds"

                << " | Vehicles waiting: " << signal.vehicleCount

                << " | Active: " << (signal.isActive ? "Yes" : "No")

                << " | Prioritized: " << (signal.isPrioritized ? "Yes" : "No") << endl;
        }
    cout << "---------------------------------\n";
}

// Change the state of the signal (Red -> Green -> Yellow -> Red)

void changeSignalState(TrafficSignal& signal)
 {
    if (signal.currentState == "Red")

        {
            signal.currentState = "Green";

            signal.timer = 60;  // Green lasts 60 seconds

        }
    else if (signal.currentState == "Green")

        {
            signal.currentState = "Yellow";

            signal.timer = 10;  // Yellow lasts 10 seconds

        }
    else if (signal.currentState == "Yellow")

        {
            signal.currentState = "Red";

            signal.timer = 30;  // Red lasts 30 seconds
        }
    signal.history.push_back(signal.currentState);

}

// Update the state of all traffic signals based on vehicle count

void updateSignals(vector<TrafficSignal>& signals)

{
    for (auto& signal : signals)

        {
            if (signal.isActive)

             {
                signal.timer--;

                if (signal.timer <= 0)

                 {

                    changeSignalState(signal);

                }

            }

        }

}

// Add a new traffic signal

void addSignal(vector<TrafficSignal>& signals)

 {
    string location;

    cout << "Enter the location for the new traffic signal: ";

    cin.ignore();

    getline(cin, location);

    signals.push_back({location, "Red", 30, 0, false, true, {"Red"}});

    cout << "New signal added at " << location << " with initial state 'Red'.\n";

}

// Manually control a traffic signal (change state)

void manualControl(vector<TrafficSignal>& signals)

 {
    displaySignals(signals);

    int index;

    cout << "Enter the index of the signal to control (1 to " << signals.size() << "): ";

    cin >> index;


    if (index < 1 || index > signals.size())

        {
            cout << "Invalid index. Returning to main menu.\n";


            return;
        }


    TrafficSignal& signal = signals[index - 1];

    cout << "Current state of " << signal.location << " is " << signal.currentState << ".\n";

    cout << "Enter the new state (Red/Yellow/Green): ";

    string newState;

    cin >> newState;


    if (newState == "Red" || newState == "Yellow" || newState == "Green")

        {

            signal.currentState = newState;

            signal.timer = (newState == "Green") ? 60 : (newState == "Yellow") ? 10 : 30;

            signal.history.push_back(newState);

            cout << "Signal state updated successfully.\n";

        }

    else

        {

            cout << "Invalid state entered. Returning to main menu.\n";

        }

}



// Display signal change history


void displaySignalHistory(const vector<TrafficSignal>& signals)

{

    cout << "\nSignal Change History:\n";

    for (const auto& signal : signals)

        {

            cout << "Location: " << signal.location << " | History: ";

            for (const auto& state : signal.history)

                {

                    cout << state << " ";

                }

            cout << endl;

        }

}



// Prioritize signal for emergency vehicle



void prioritizeSignal(vector<TrafficSignal>& signals)

{

    string location;

    cout << "Enter the location for emergency signal prioritization: ";

    cin.ignore();

    getline(cin, location);


    bool found = false;

    for (auto& signal : signals)

        {

            if (signal.location == location)

            {

                signal.isPrioritized = true;

                signal.currentState = "Green";


                signal.timer = 30;  // Emergency vehicles get a shorter green light

                signal.history.push_back("Green (Emergency)");

                cout << "Signal at " << location << " is prioritized for emergency vehicle.\n";

                found = true;

                break;

            }

        }


    if (!found)

        {

            cout << "No signal found at location " << location << ".\n";

        }

}



// Simulate vehicle count for each signal



void simulateVehicleCount(vector<TrafficSignal>& signals)


{

    for (auto& signal : signals)

        {

            if (signal.currentState == "Red")

             {

                signal.vehicleCount += rand() % 10 + 1;  // Add 1-10 vehicles when the signal is Red

            }

        }

}



// Adjust signal timing based on vehicle count


void adjustSignalTiming(vector<TrafficSignal>& signals)


{


    for (auto& signal : signals)


        {
            if (signal.vehicleCount > 10)


            {

                signal.timer = 90;
                // Extend green light for heavy traffic


                signal.currentState = "Green";

                cout << "Signal at " << signal.location << " extended green light due to heavy traffic.\n";

            }

    else if (signal.vehicleCount < 3)


        {
            signal.timer = 30;
    // Shorten green light for light traffic

            signal.currentState = "Green";

            cout << "Signal at " << signal.location << " shortened green light due to light traffic.\n";

        }

    }

}



// Deactivate or activate a signal


void toggleSignalActivity(vector<TrafficSignal>& signals)


 {

    string location;

    cout << "Enter the location of the signal to toggle: ";

    cin.ignore();

    getline(cin, location);


    for (auto& signal : signals)

        {

            if (signal.location == location)

            {

                signal.isActive = !signal.isActive;

                cout << "Signal at " << location << " is now " << (signal.isActive ? "active" : "inactive") << ".\n";

                return;

            }

        }

    cout << "Signal at " << location << " not found.\n";

}



// View specific signal details


void viewSignalDetails(const vector<TrafficSignal>& signals)

{

    int index;

    displaySignals(signals);

    cout << "Enter the index of the signal to view details (1 to " << signals.size() << "): ";

    cin >> index;


    if (index < 1 || index > signals.size())

        {

            cout << "Invalid index. Returning to main menu.\n";

            return;

        }

    const TrafficSignal& signal = signals[index - 1];

    cout << "\nSignal Details:\n"

         << "Location: " << signal.location << "\n"

         << "State: " << signal.currentState << "\n"

         << "Timer: " << signal.timer << " seconds\n"

         << "Vehicle count: " << signal.vehicleCount << "\n"

         << "Active: " << (signal.isActive ? "Yes" : "No") << "\n"

         << "Prioritized: " << (signal.isPrioritized ? "Yes" : "No") << "\n";

}

// Update vehicle count manually


void updateVehicleCount(vector<TrafficSignal>& signals)

 {

    int index;

    displaySignals(signals);

    cout << "Enter the index of the signal to update vehicle count (1 to " << signals.size() << "): ";

    cin >> index;


    if (index < 1 || index > signals.size())

        {
            cout << "Invalid index. Returning to main menu.\n";

            return;

        }


    TrafficSignal& signal = signals[index - 1];

    int newCount;

    cout << "Enter new vehicle count for signal at " << signal.location << ": ";

    cin >> newCount;


    signal.vehicleCount = newCount;

    cout << "Vehicle count updated to " << newCount << " for signal at " << signal.location << ".\n";

}




// Reset all signals to their default states


void resetAllSignals(vector<TrafficSignal>& signals)

{

    for (auto& signal : signals)


        {


            signal.currentState = "Red";

            signal.timer = 30;

            signal.vehicleCount = 0;

            signal.isPrioritized = false;

            signal.isActive = true;

            signal.history.clear();

            signal.history.push_back("Red");

        }


    cout << "All signals reset to default states.\n";


}



// View signals that are prioritized for emergency vehicles


void viewPrioritizedSignals(const vector<TrafficSignal>& signals)


{


    cout << "\nPrioritized Signals:\n";

    for (const auto& signal : signals)

        {
            if (signal.isPrioritized)

            {

                cout << "Location: " << signal.location << " | State: " << signal.currentState << endl;

            }

        }

}



// Change the timer for a specific signal



void changeSignalTimer(vector<TrafficSignal>& signals)

 {
    int index;

    displaySignals(signals);

    cout << "Enter the index of the signal to change timer (1 to " << signals.size() << "): ";

    cin >> index;


    if (index < 1 || index > signals.size())

        {

            cout << "Invalid index. Returning to main menu.\n";

            return;

        }


    TrafficSignal& signal = signals[index - 1];

    int newTimer;

    cout << "Enter new timer value (in seconds) for signal at " << signal.location << ": ";

    cin >> newTimer;


    signal.timer = newTimer;


    cout << "Timer for signal at " << signal.location << " updated to " << newTimer << " seconds.\n";



}



// View active signals



void viewActiveSignals(const vector<TrafficSignal>& signals)


{


    cout << "\nActive Signals:\n";

    for (const auto& signal : signals)


        {

            if (signal.isActive)

             {


                cout << "Location: " << signal.location << " | State: " << signal.currentState << endl;

            }


        }

}


// Remove a traffic signal


void removeSignal(vector<TrafficSignal>& signals)


 {


    string location;

    cout << "Enter the location of the signal to remove: ";

    cin.ignore();


    getline(cin, location);



    auto it = remove_if(signals.begin(), signals.end(), [&location](const TrafficSignal& signal) {

        return signal.location == location;

    });


    if (it != signals.end())

        {

            signals.erase(it, signals.end());

            cout << "Signal at " << location << " removed.\n";

        }

    else

        {

            cout << "No signal found at location " << location << ".\n";

        }


}


// Generate a traffic report


void generateTrafficReport(const vector<TrafficSignal>& signals)


{

    cout << "\nTraffic Report:\n";


    for (const auto& signal : signals)

        {

            cout << "Location: " << signal.location

                << " | State: " << signal.currentState

                << " | Timer: " << signal.timer << " seconds"

                << " | Vehicles waiting: " << signal.vehicleCount << endl;

        }

}



// Prioritize signal based on traffic density



void prioritizeSignalBasedOnDensity(vector<TrafficSignal>& signals)

 {

    for (auto& signal : signals)

        {

            if (signal.vehicleCount > 20)

             {

                 // If there are more than 20 vehicles waiting


                signal.isPrioritized = true;


                signal.currentState = "Green";

                signal.timer = 60;  // Longer green light for heavy traffic

                signal.history.push_back("Green (Prioritized by Density)");


                cout << "Signal at " << signal.location << " is now prioritized due to high traffic density.\n";


            }

        }

}


// View signal state summary

void viewSignalStateSummary(const vector<TrafficSignal>& signals)

{

    int redCount = 0, greenCount = 0, yellowCount = 0;

    for (const auto& signal : signals)

        {

            if (signal.currentState == "Red")


            {

                redCount++;


            }


    else if (signal.currentState == "Green")


            {


                greenCount++;


            }


    else if (signal.currentState == "Yellow")


            {

                yellowCount++;

            }
        }


    cout << "\nSignal State Summary:\n"

         << "Red: " << redCount << "\n"

         << "Green: " << greenCount << "\n"

         << "Yellow: " << yellowCount << "\n";

}



// Generate an emergency report
void generateEmergencyReport(const vector<TrafficSignal>& signals)

 {

    cout << "\nEmergency Signal Report:\n";

    for (const auto& signal : signals)

        {

            if (signal.isPrioritized)

            {

                cout << "Location: " << signal.location

                    << " | State: " << signal.currentState

                    << " | Timer: " << signal.timer << " seconds\n";

            }

        }


}


// Adjust signal state based on time of day (Morning, Afternoon, Night)



void adjustSignalStateBasedOnTime(vector<TrafficSignal>& signals)

{

    time_t t = time(0);  // Get current time

    tm* timeInfo = localtime(&t);

    int hour = timeInfo->tm_hour;


    for (auto& signal : signals)


        {

            if (hour >= 6 && hour < 9)

             {

                 // Morning rush hour (shorter green light)

                if (signal.currentState == "Green")

                {

                    signal.timer = 30;

                    cout << "Signal at " << signal.location << " adjusted for morning rush hour.\n";

                }

             }

    else if (hour >= 9 && hour < 17)


        {

            // Daytime


            if (signal.currentState == "Green")


                {

                    signal.timer = 60;

                }

        }

        else if (hour >= 17 && hour < 22)


            {

                // Evening rush hour


                if (signal.currentState == "Green")

                    {

                        signal.timer = 45;

                        cout << "Signal at " << signal.location << " adjusted for evening rush hour.\n";

                    }

            }

            else

                {

                     // Night


                    if (signal.currentState == "Green")

                     {

                        signal.timer = 120;  // Longer green light at night

                     }

                }

        }

}





// View vehicle queue length for each signal



void viewVehicleQueueLength(const vector<TrafficSignal>& signals)


{

    cout << "\nVehicle Queue Length:\n";

    for (const auto& signal : signals)

        {

            cout << "Location: " << signal.location


                << " | Vehicle Count: " << signal.vehicleCount << "\n";


        }

}


// Deactivate a traffic signal


void deactivateSignal(vector<TrafficSignal>& signals)



{


    displaySignals(signals);

    int index;


    cout << "Enter the index of the signal to deactivate (1 to " << signals.size() << "): ";

    cin >> index;

    if (index < 1 || index > signals.size())


        {

            cout << "Invalid index. Returning to main menu.\n";


            return;

        }

    TrafficSignal& signal = signals[index - 1];


    signal.isActive = false;


    cout << "Signal at " << signal.location << " has been deactivated.\n";


}


// Reactivate a traffic signal


void reactivateSignal(vector<TrafficSignal>& signals)


 {

    displaySignals(signals);

    int index;

    cout << "Enter the index of the signal to reactivate (1 to " << signals.size() << "): ";

    cin >> index;

    if (index < 1 || index > signals.size())

        {

            cout << "Invalid index. Returning to main menu.\n";

            return;


        }

    TrafficSignal& signal = signals[index - 1];


    signal.isActive = true;


    cout << "Signal at " << signal.location << " has been reactivated.\n";


}


void detectTrafficAccident(vector<TrafficSignal>& signals)


{

    string location;

    cout << "Enter the location to check for accident: ";

    cin.ignore();

    getline(cin, location);


    bool found = false;

    for (auto& signal : signals)

        {

            if (signal.location == location)

             {

                signal.isPrioritized = true;

                signal.currentState = "Red";

                signal.timer = 0;  // Emergency vehicles pass immediately

                signal.history.push_back("Red (Accident Detected)");

                cout << "Accident detected at " << location << ". Signal set to Red for clearing.\n";


                found = true;

                break;

            }

        }


    if (!found)


        {


            cout << "No signal found at location " << location << ".\n";


        }
}


void classifyVehicles(vector<TrafficSignal>& signals)


{

    cout << "\nClassifying Vehicles at each Signal:\n";


    for (auto& signal : signals)


        {


            int vehicleType = rand() % 4;
             // Randomly assign a vehicle type (0=car, 1=truck, 2=bus, 3=bike)


            string vehicleName;

            switch (vehicleType)

            {

                case 0: vehicleName = "Car"; break;


                case 1: vehicleName = "Truck"; break;

                case 2: vehicleName = "Bus"; break;

                case 3: vehicleName = "Bike"; break;

            }


        cout << "Location: " << signal.location << " | Vehicle type detected: " << vehicleName << "\n";

        }

}


void adjustSignalPatternByTime(vector<TrafficSignal>& signals)

 {

    time_t t = time(0);
    // Get current time

    tm* timeInfo = localtime(&t);

    int hour = timeInfo->tm_hour;


    if (hour >= 6 && hour < 9)



        {

            // Morning rush hour

            cout << "Adjusting signal patterns for morning rush hour.\n";


            for (auto& signal : signals)


                {


                    if (signal.currentState == "Red")


                    {


                        signal.timer = 20;
            // Shorter red light in the morning to reduce congestion


                        signal.history.push_back("Red (Morning rush hour)");


                    }

                }

        }

    else if (hour >= 22 || hour < 6)

        {


            // Late night

            cout << "Adjusting signal patterns for night time.\n";

            for (auto& signal : signals)

            {

                if (signal.currentState == "Green")

                    {

                        signal.timer = 120;
            // Longer green light at night due to lighter traffic


                        signal.history.push_back("Green (Night)");


                    }


            }

        }

}



void emergencyOverrideSignal(vector<TrafficSignal>& signals)

{

    string location;

    cout << "Enter the location of the signal to override: ";

    cin.ignore();

    getline(cin, location);


    string state;

    cout << "Enter the new state for the signal (Red/Green): ";


    cin >> state;

    bool found = false;

    for (auto& signal : signals)

        {

            if (signal.location == location)

            {

                signal.currentState = state;

                signal.timer = (state == "Green") ? 60 : 30;
                // Set timer accordingly

                signal.history.push_back(state + " (Emergency Override)");

                cout << "Signal at " << location << " has been overridden to " << state << ".\n";

                found = true;

                break;

            }

        }



    if (!found)

    {



        cout << "No signal found at location " << location << ".\n";


    }




};




int main()

{

    loadData();


    if (userLogin())

    {

        displayMainMenu();

    }


    cout << "Welcome to Infrastructure Development\n";


    int initialColonies;

    cout << "Enter the number of initial colonies: ";

    cin >> initialColonies;


    CityGraph city(initialColonies);


    for (int i = 0; i < initialColonies; ++i)

    {

        string colonyName;

        cout << "Enter name for colony " << i << ": ";

        cin >> colonyName;

        city.setColonyName(i, colonyName);

    }


    int roads;

    cout << "Enter number of roads: ";

    cin >> roads;

    for (int i = 0; i < roads; ++i)

    {

        int from, to, distance;

        cout << "Enter road details (from to distance): ";

        cin >> from >> to >> distance;

        city.addRoad(from, to, distance);

    }

    while (true)

    {

        displayInstructions();

        int choice;

        cout << "Enter your choice: ";

        cin >> choice;


        switch (choice)

        {

            case 1:

            {

                string name;

                cout << "Enter new colony name: ";

                cin >> name;

                city.addColony(name);

                break;


            }

            case 2:

            {

                int from, to, distance;

                cout << "Enter road details (from to distance): ";

                cin >> from >> to >> distance;

                city.addRoad(from, to, distance);

                break;

            }

            case 3:

            {

                int id;

                cout << "Enter colony ID to remove: ";

                cin >> id;

                city.removeColony(id);

                break;


            }

            case 4:

            {

                int from, to;

                cout << "Enter road details to remove (from to): ";

                cin >> from >> to;

                city.removeRoad(from, to);

                break;


            }

            case 5:

                city.displayGraph();

                break;


            case 6:

            {

                int start;

                cout << "Enter start colony ID: ";

                cin >> start;

                vector<int> distances = city.findShortestPaths(start);

                cout << "Shortest paths from colony " << start << ":\n";

                for (size_t i = 0; i < distances.size(); ++i)

                {

                    cout << "To " << i << ": " << (distances[i] == INT_MAX ? "Not reachable" : to_string(distances[i]))
                         << endl;

                }

                break;


            }

            case 7:

            {

                int mostConnected = city.findMostConnectedColony();

                if (mostConnected != -1)

                {

                    cout << "The most connected colony is " << city.getColonyName(mostConnected)
                         << " with " << city.getGraph()[mostConnected].size() << " connections." << endl;

                }

                else

                {

                    cout << "No colonies available." << endl;

                }

                break;


            }

            case 8:

                cout << "Total road cost: " << city.getTotalRoadCost() << endl;

                break;


            case 9:

                city.displayColonyDetails();

                break;


            case 10:

            {

                int id;

                cout << "Enter colony ID: ";

                cin >> id;

                city.setColonyCategory(id);

                break;


            }

            case 11:

                city.displayColoniesByCategory();

                break;


            case 12:

                city.displayCategoryCounts();

                break;


            case 13:

            {

                int id, total, kaccha;

                cout << "Enter colony ID: ";

                cin >> id;

                cout << "Enter total houses: ";

                cin >> total;

                cout << "Enter kaccha houses: ";

                cin >> kaccha;

                city.addHouses(id, total, kaccha);

                break;


            }

          case 14:

            {

                    int id;

                    string newCategory;

                   cout << "Enter colony ID to update category: ";

                   cin >> id;

                  cout << "Enter new category: ";

                 cin >> newCategory;

                city.updateColonyCategory(id, newCategory);

                break;


            }

            case 15:

                cout << "Exiting...\n";

                 RentalSystem rentalSystem;

    PublicTransport publicTransport;

    Carpool carpool;



    // Load all data from files


    rentalSystem.loadVehiclesFromFile();


    publicTransport.loadRoutesFromFile();



    carpool.loadCarpoolsFromFile();



   int option;



do


{

    cout << "\nWelcome to Sustainable Transportation:\n";

    cout << "1. Display Available Vehicles\n";

    cout << "2. Book Vehicle\n";

    cout << "3. Release Vehicle\n";

    cout << "4. Display Rental History\n";

    cout << "5. Add Route to Public Transport\n";

    cout << "6. Display Public Transport Routes\n";

    cout << "7. Find Shortest Route\n";


    cout << "8. Create Carpool\n";

    cout << "9. Add Passenger to Carpool\n";

    cout << "10. Display Active Carpools\n";

    cout << "11. Search Route by Source and Destination\n";

    cout << "12. Search Available Vehicles by Source\n";

    cout << "13. Exit\n";

    cout << "Choose an option: ";

    cin >> option;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (option)

    {

        case 1:

            rentalSystem.displayAvailableVehicles();

            break;


        case 2:

        {

            string id, renterID;

            cout << "Enter Vehicle ID: ";

            cin >> id;

            cout << "Enter Renter ID: ";

            cin >> renterID;

            rentalSystem.bookVehicle(id, renterID);

            break;

        }


        case 3:



        {

            string id;

            cout << "Enter Vehicle ID to release: ";

            cin >> id;

            rentalSystem.releaseVehicle(id);

            break;

        }


        case 4:

            rentalSystem.displayRentalHistory();


            break;


        case 5:

        {

            string routeName, source, destination;

            vector<string> viaRoutes;

            double distance;


            cout << "Enter Route Name: ";

            cin >> routeName;

            cout << "Enter Source: ";

            cin >> source;

            cout << "Enter Destination: ";

            cin >> destination;

            cout << "Enter Distance: ";

            cin >> distance;


            string routeStop;

            cout << "Enter Via Routes (separated by spaces): ";

            while (cin >> routeStop)

            {
                viaRoutes.push_back(routeStop);

                if (cin.peek() == '\n') break;

            }


            publicTransport.saveRouteToFile(routeName, source, destination, viaRoutes, distance);

            break;

        }

        case 6:

            publicTransport.displayRoutes();

            break;


        case 7:


        {

            string source, destination;

            cout << "Enter Source: ";

            cin >> source;

            cout << "Enter Destination: ";

            cin >> destination;

            publicTransport.findShortestRoute(source, destination);

            break;

        }


        case 8:

        {

            string driverId, source, destination;

            vector<string> viaRoutes;

            double distance;


            cout << "Enter Driver ID: ";

            cin >> driverId;

            cout << "Enter Source: ";

            cin >> source;

            cout << "Enter Destination: ";

            cin >> destination;

            cout << "Enter Distance: ";


            cin >> distance;

            string routeStop;

            cout << "Enter Via Routes (separated by spaces): ";

            while (cin >> routeStop)

            {

                viaRoutes.push_back(routeStop);

                if (cin.peek() == '\n') break;

            }

            carpool.createCarpool(driverId, source, destination, viaRoutes, distance);

            break;

        }


        case 9:


        {

            string passenger, source, destination;

            cout << "Enter Passenger Name: ";

            cin >> passenger;

            cout << "Enter Source: ";

            cin >> source;

            cout << "Enter Destination: ";

            cin >> destination;

            carpool.addPassenger(passenger, source, destination);

            break;

        }

        case 10:

            carpool.displayCarpools();

            break;


        case 11:

        {

            string source, destination;

            cout << "Enter Source: ";

            cin >> source;

            cout << "Enter Destination: ";

            cin >> destination;

            publicTransport.searchRouteBySourceDestination(source, destination);

            break;

        }


        case 12:

        {

            string source;

            cout << "Enter Source: ";

            cin >> source;

            rentalSystem.searchAvailableVehiclesBySource(source);

            break;

        }


        case 13:

            cout << "Exiting...\n";

            break;


        default:

            cout << "Invalid option. Please try again.\n";

    }

}

while (option != 13);



vector<TrafficSignal> signals;

initializeSignals(signals);


int menu;

    cout << "\nSmart Traffic Management System:\n";

    cout << "1. Display traffic signals\n";

    cout << "2. Add a new traffic signal\n";


    cout << "3. Control signals manually\n";

    cout << "4. Display signal history\n";

    cout << "5. Prioritize signal for emergency vehicle\n";


    cout << "6. Adjust signal timing based on traffic density\n";

    cout << "7. Toggle signal activity\n";

    cout << "8. View specific signal details\n";

    cout << "9. Update vehicle count manually\n";


    cout << "10. Reset all signals\n";

    cout << "11. Change signal timer manually\n";


    cout << "12. View active signals\n";

    cout << "13. Remove a traffic signal\n";

    cout << "14. Generate traffic report\n";

    cout << "15. View signal state summary\n";


    cout << "16. Adjust signal state based on time of day\n";

    cout << "17. View vehicle queue length\n";

    cout << "18. Deactivate Signal\n";

    cout << "19. Reactivate Signal\n";

    cout << "20. Monitor Traffic Seed\n";

    cout << "21. Detect Traffic Accident\n";

    cout << "22. Classify Vehicles\n";


    cout << "23. Emergency Override for Signal\n";

    cout << "24. Exit\n";

    cout << "Enter your choice: ";

    while (true)

        {


            cin >> menu;


            switch (menu)

            {
                case 1:

                    displaySignals(signals);

                    break;

                case 2:

                    addSignal(signals);

                    break;

                case 3:

                    manualControl(signals);

                    break;

                case 4:

                    displaySignalHistory(signals);

                    break;

                case 5:

                    prioritizeSignal(signals);

                    break;


                case 6:

                    adjustSignalTiming(signals);

                    break;

                case 7:

                    toggleSignalActivity(signals);

                    break;

                case 8:

                    viewSignalDetails(signals);

                    break;

                case 9:

                    updateVehicleCount(signals);

                    break;

                case 10:

                    resetAllSignals(signals);

                    break;


                case 11:

                    changeSignalTimer(signals);

                    break;

                case 12:

                    viewActiveSignals(signals);

                    break;

                case 13:

                    removeSignal(signals);

                    break;

                case 14:

                    generateTrafficReport(signals);

                    break;

                case 15:

                    viewSignalStateSummary(signals);

                    break;

                case 16:

                    adjustSignalStateBasedOnTime(signals);


                    break;

                case 17:

                    viewVehicleQueueLength(signals);

                    break;

                case 18:

                    deactivateSignal(signals);

                    break;

                case 19:

                    reactivateSignal(signals);

                    break;

                case 20:

                    cout << "Traffic monitoring feature is under construction.\n";

                    break;

                case 21:

                    detectTrafficAccident(signals);

                    break;

                case 22:

                    classifyVehicles(signals);

                    break;


                case 23:

                    emergencyOverrideSignal(signals);

                    break;

                case 24:

                    cout << "Exiting Traffic Management System. Goodbye!\n";

                    return 0;

                default:

                    cout << "Invalid choice. Please try again.\n";

            }


        }

                return 0;

        }
    }
}
