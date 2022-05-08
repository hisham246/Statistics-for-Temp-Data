#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

// Function prototype. Function calculating all operations on data.
void calculations (double [][13], int);

int main()
{
	//Prompt to display data from the file
	cout << "This program collects data from CASE1.csv and calculates\n"
	     << "statistical data for the following:\n"
	     << "Ta - atmospheric temperature (degrees Celsius)\n" 
		 << "RH - relative humidity(%)\n"
		 << "Tg - globe temperature (degrees Celsius)\n"
		 << "Va - air velocity(m/s)\n\n"
		 << "Press RETURN/ENTER to proceed.\n\n";
	cout << setw(75) << "Case 1: 20 C\n";
	cout << setw(81) << "------------------\n\n";
	cout << "Date" << setw(12) << "Time" << setw(10) << "Tal" << setw(8)
	     << "Ta2" << setw(8) << "Ta3" << setw(8) << "Ta4" << setw(8)
	     << "RH1" << setw(8) << "RH2" << setw(8) << "RH3" << setw(8)
	     << "RH4" << setw(8) << "Tg1" << setw(8) << "Tg2" << setw(8)
	     << "Tg3" << setw(8) << "Tg4" << setw(8) << "Va" << endl;
	cin.get();
	
	
	// Taking data from the file to store it in a 2D array and display it.
	ifstream ThermME;
	
	ThermME.open("CASE1.csv");
	double data[361][13];
	int hours = 14, minutes = 16, seconds = 0;
	string date = ("23-04-2019"); // Displaying date in the table.
	
	if (!ThermME)
	{
		cout << "File open failure!\n";
	}
	// Displaying the time of 1 hour on 10 second intervals.
	else
	{
		for (int rows = 0;rows < 361;rows++)
		{
			string line;
			getline(ThermME, line);
            stringstream iss(line);
            cout << date << "  ";
            cout  << hours << ":";
            cout  << setw(2) << setfill('0') << minutes << ":";
            cout  << setw(2) << setfill('0') << seconds << "  ";
             seconds += 10;
            if (seconds == 60)
            {
            	seconds = 0;
            	minutes++;
            	if(minutes == 60)
                {
                    minutes = 0;
                    hours++;
                }
			}
			// Converting string data from file into array.
			for (int cols = 0; cols < 13; cols++)
			{
                string val;
                getline(iss, val,',');
                stringstream convertor(val);
                convertor >> data[rows][cols];
                cout << fixed << setprecision(3) << " " << data[rows][cols] << " ";
            }
            cout << endl;
        } 
	}
    cout << endl << endl;
    calculations(data, 361); // Function call.
    return 0;
}

// Function header.
void calculations(double data[][13], int r)
{
	float average[13];
	float stdDev[13];
	for (int col = 0; col < 13; col++)
	{
		double totCol = 0.0;
		for (int row = 0; row < 361; row++)
		{
			totCol += data[row][col];
		}
		average[col] = totCol / 361;
	}
	double d[13] = {0.0};
	for (int col = 0; col < 13; col++)
	{
		for (int row = 0; row < 361; row++)
		{
			d[col] += pow(average[col] - data[row][col], 2);
		}
		stdDev[col] = sqrt(d[col] / 360);
	}
	
	double max[13] = {};
	for (int row = 0; row < 361; row++)
	{
		for (int col = 0; col < 13; col++)
		{
			if(data[row][col] > max[col])
			{
				max[col] = data[row][col];
			}
		}
	}
	double min[13] = {100,100,100,100,100,100,100,100,100,100,100,100,100};
    for (int row = 0; row < 361; row++)
    {
        for (int col = 0; col < 13; col++)
        {
            if(data[row][col] < min[col])
                min[col] = data[row][col];
        }
    }
    // Prompt for calculating data.
    cout << "For each unit, the following statistics has been calculated and\n"
         << "will be printed in the output file file##.csv:\n"
         << "Average \nStandard Devation \nMaximum \nMinimum \n\n"
         << "Press RETURN/ENTER to proceed:\n";
    cin.get();
    
    // Printing data in CSV file
    ofstream file;
    file.open("file##.csv");
    file << ",,,,," << "Case 1: 20 C" << ",,," << endl;
    file << ","<< "Ta1" << "," << "Ta2" << "," << "Ta3" << "," << "Ta4" << "," << "RH1" << "," << "RH2" 
	     << "," << "RH3" << "," << "RH4" << "," << "Tg1" << "," << "Tg2" << "," << "Tg3" << "," << "Tg4" 
		 << "," << "Va" << endl;
	// Printing average.
	file << "Average: " << ",";
	for (int count = 0; count < 13; count++)
	{
		if (count > 3 && count < 8)
    	{
    		file << fixed << setprecision(0) << average[count] << ",";
		}
		else
		{
			file << fixed << setprecision(1) << showpoint << average[count] << ",";
		}
	}
	file << endl;
	//Printing standard deviation.
	file << "Std. Dev.: " << ",";
    for (int count = 0; count < 13; count++)
    {
    	if (count > 3 && count < 8)
    	{
    		file << fixed << setprecision(0) << stdDev[count] << ",";
		}
		else
		{
			file << fixed << setprecision(1) << showpoint << stdDev[count] << ",";
		}
	}
	file << endl;
	// Printing maximum values.
	file << "Max: " << ",";
	for (int count = 0; count < 13; count++)
	{
		if (count > 3 && count < 8)
    	{
    		file << fixed << setprecision(0) << max[count] << ",";
		}
		else
		{
			file << fixed << setprecision(1) << showpoint << max[count] << ",";
		}
	}
	file << endl;
	// Printing minimum values.
    file << "Min: " << ",";
    for (int count = 0; count < 13; count++)
    {
    	if (count > 3 && count < 8)
    	{
    		file << fixed << setprecision(0) << min[count] << ",";
		}
		else
		{
			file << fixed << setprecision(1) << showpoint << min[count] << ",";
		}
	}
	file << endl;
	file << endl;
	file << endl;
	
	// Prompt for printing data.
	cout << "Output has been printed. Press RETURN/ENTER to proceed:\n";
	cin.get();
	
	// Calculating the average of Ta values.
	double aveTa, sumTa = 0.0;
	for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 0; cols < 4; cols++)
        {
            sumTa += data[rows][cols];
        }
    }
    aveTa = sumTa / (361.0 * 4.0);
    
    // Calculating the average of RH values.
    double aveRH, sumRH = 0.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 4; cols < 8; cols++)
        {
            sumRH += data[rows][cols];
        }
    }
    aveRH = sumRH / (361.0 * 4.0);
    
    // Calculating the average of Tg Values.
    double aveTg, sumTg = 0.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 8; cols < 12; cols++)
        {
            sumTg += data[rows][cols];
        }
    }
    aveTg = sumTg / (361.0 * 4.0);
    
    // Calculating the average of Va Values.
    double aveVa, sumVa = 0.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 12; cols < 13; cols++)
        {
            sumVa += data[rows][cols];
        }
    }
    aveVa = sumVa / (361.0);
    
    // Calculating standard deviation of Ta Values.
    double stdDevTa;
    double totSquares = 0.0;
    for (int cols = 0; cols < 4; cols++)
    {
        for (int rows = 0; rows < 361; rows++)
        {
            totSquares +=  pow(aveTa - data[rows][cols], 2);
        }
        stdDevTa = sqrt(totSquares / ((361.0 * 4.0) - 1));
    }
    
    // Calculating standard deviation of RH Values.
    double stdDevRH;
    totSquares = 0;
    for (int cols = 4; cols < 8; cols++)
    {
        for (int rows = 0; rows < 361; rows++)
        {
            totSquares +=  pow(aveRH - data[rows][cols], 2);
        }
        stdDevRH = sqrt(totSquares / ((361.0 * 4.0) - 1));
    }
    
    // Calculating standard deviation of Tg Values.
    double stdDevTg;
    totSquares = 0.0;
    for (int cols = 8; cols < 12; cols++)
    {
        for (int rows = 0; rows < 361; rows++)
        {
            totSquares +=  pow(aveTg - data[rows][cols], 2);
        }
        stdDevTg = sqrt(totSquares / ((361 * 4) - 1));
    }
    
    // Calculating standard deviation of Va Values.
    double stdDevVa;
    totSquares = 0.0;
    for (int cols = 12; cols < 13; cols++)
    {
        for (int rows = 0; rows < 361; rows++)
        {
            totSquares +=  pow(aveVa - data[rows][cols], 2);
        }
        stdDevVa = sqrt(totSquares / 360);
    }
    
    // Calculating the maximum of Ta Values.
	double maxTa = 0.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 0; cols < 4; cols++)
        {
            if (data[rows][cols] > maxTa)
            {
            	maxTa = data[rows][cols];
			}
        }
    }
    
    // Calculating the maximum of RH Values.
    double maxRH = 0.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 4; cols < 8; cols++)
        {
            if (data[rows][cols] > maxRH)
            {
            	maxRH = data[rows][cols];
			}
        }
    }
    
    // Calculating the maximum of Tg Values.
    double maxTg = 0.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 8; cols < 12; cols++)
        {
            if (data[rows][cols] > maxTg)
            {
            	maxTg = data[rows][cols];
			}
        }
    }
    
    // Calculating the maximum of Va Values.
    double maxVa = 0.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 12; cols < 13; cols++)
        {
            if(data[rows][cols] > maxVa)
            {
            	maxVa = data[rows][cols];
			}
        }
    }
    
    // Calculating the minimum of Ta Values.
    double minTa = 100.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 0; cols < 4; cols++)
        {
            if (data[rows][cols] < minTa)
            {
            	minTa = data[rows][cols];
			}
        }
    }
    
    // Calculating the minimum of RH Values.
    double minRH = 100.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 4; cols < 8; cols++)
        {
            if(data[rows][cols] < minRH)
            {
            	minRH = data[rows][cols];
			}
        }
    }
    
    // Calculating the minimum of Tg Values.
    double minTg = 100.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 8; cols < 12; cols++)
        {
            if(data[rows][cols] < minTg)
            {
            	minRH = data[rows][cols];
			}
        }
    }
    
    // Calculating the minimum of Va Values.
    double minVa = 100.0;
    for (int rows = 0; rows < 361; rows++)
    {
        for (int cols = 12; cols < 13; cols++)
        {
            if(data[rows][cols] < minVa)
            {
            	minVa = data[rows][cols];
			}
        }
    }
    
    // Prompt for calculating data.
    cout << "Statistics for the overall values of Ta, RH, Tg, and Va have been calculated.\n"
         << "Press RETURN/ENTER to add the values to output file file##.csv: \n";
    cin.get();
    
    // Printing data in the same CSV file.
    file << ",,," << "Case 1: 20 C" << endl;
	file << "," << "Ta" << "," << "RH" << "," << "Tg" << "," << "Va" << endl;
	
	// Printing average.
	file << "Average: " << ",";
    file << fixed << setprecision(1) << aveTa << "," << fixed << setprecision(0) 
	     << aveRH << "," << fixed << setprecision(1) << aveTg << "," << aveVa;
    file << endl;
    
    // Printing standard deviation.
    file << "Std. Dev.: " << ",";
    file << fixed << setprecision(1) << stdDevTa << "," << fixed << setprecision(0) 
	     << stdDevRH << "," << fixed << setprecision(1) << showpoint << stdDevTg << "," << stdDevVa;
    file << endl;
    
    // Printing maximum.
    file << "Maximum: " << ",";
    file << fixed << setprecision(1) << maxTa << "," << fixed << setprecision(0) 
	     << maxRH << "," << fixed << setprecision(1) << showpoint << maxTg << "," << maxVa;
    file << endl;
    
    // Printing minimum.
    file << "Minimum: " << ",";
    file << fixed << setprecision(1) << minTa << "," << fixed << setprecision(0) 
	     << minRH << "," << fixed << setprecision(1) << showpoint << minTg << "," << minVa;
    file << endl;
    file.close();
    
    // Prompt for printing data.
    cout << "Output has been printed. Press RETURN/ENTER to proceed:\n";
    cin.get();
    
    // Equations calculation.
    const double emissivity = 0.95;
    const double diameter = 0.04;
    double Tmrt;
    Tmrt = pow(pow(aveTg + 273, 4) + ( (1.1 * pow(10,8) * pow(aveVa, 0.6)) / (emissivity * pow(diameter, 0.4)) ) * (aveTg - aveTa), 0.25) - 273;
    double Top, TopIndoor;
    Top = (Tmrt + aveTa * sqrt(10 * aveVa)) / (1 + sqrt(10 * aveVa));
    TopIndoor = 0.5 * (aveTa + Tmrt);
    
    // Prompt for calculating data.
    cout << "Based on the average values of Ta, RH, Tg, and Va, the following are calculated:\n"
         << "Tmrt - mean radiant temperature(degrees Celsius)\n"
         << "Top - operative temperature(degrees Celsius)\n\n"
         << "Press RETURN/ENTER to print the results to the output file ###.csv:\n";
    cin.get();
    
    // Printing data in another CSV file.
    ofstream file2;
    file2.open("###.csv");
    file2 << ",,,"<< "Case 1: 20 C" << endl;
    file2 << "Ta" << ", " << "RH" << "," << "Tg" << "," << "Va"<< "," << "Tmrt" << "," << "Top" << endl;
    if(aveVa < 0.2)
    {
    	file2 << fixed << setprecision(1) << aveTa << "," << fixed << setprecision(0) << aveRH << ","
		      << fixed << setprecision(1) << showpoint << aveTg << "," << aveVa << "," << Tmrt << "," << TopIndoor;
	}
    else
    {
    	file2 << fixed << setprecision(1) << aveTa << "," << fixed << setprecision(0) << aveRH << "," 
		      << fixed << setprecision(1) << showpoint << aveTg << "," << aveVa << "," << Tmrt << "," << Top;
	}
	
	// Prompt for printing data.
	cout << "Output has been printed. Press RETURN/ENTER to proceed:\n";
	cin.get();
}	
