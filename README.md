# Statisical Analysis for Temperature Sensor Data
The field measurement of thermal comfort was conducted in experimental living room with five
or six respondents. The four-thermostat setting of air-conditioning was applied in this
measurement. Each thermostat setting was repeated four times. As a programmer, you need to
write a programme to compile the raw data and analyse the data.

## Part 1: Compiling raw data ##
The number indicates the observation data of room air temperature, relative humidity, globe
temperature, and air velocity of several sensors with ten seconds interval in experimental living
room.

* Data for temperature and relative humidity:
The columns are: (1) Number of sampling; (2) date; (3) time; (4) temperature of sensor; (5)
relative humidity (RH); (6) air temperature (Ta); (7) globe temperature (Tg).

* Data for air velocity:
The columns are (2) time and (3) air velocity.

## Part 2: Calculating the average, standard deviation, maximum, and minimum for all variables ##
Formatting: One decimal point for all variables except relative humidity is no decimal point. Results are printed to file##.csv.

## Part 3: Calculating the mean radiant temperature (Tmrt) and operative temperature (Top) ##
Mean radiant temperature (Tmrt) can be estimated using the following equation:

![equation](https://latex.codecogs.com/svg.image?T_%7Bm%20r%20t%7D=%5Cleft%5B%5Cleft(T_%7Bg%7D&plus;273%5Cright)%5E%7B4%7D&plus;%5Cfrac%7B1.1%20%5Ctimes%2010%5E%7B8%7D%20V_%7Ba%7D%5E%7B0.6%7D%7D%7B%5Cvarepsilon%20D%5E%7B0.4%7D%7D%5Cleft(T_%7Bg%7D-T_%7Ba%7D%5Cright)%5Cright%5D%5E%7B%5Cfrac%7B1%7D%7B4%7D%7D-273)

where ε refers to emissivity of the globe, taken as 0.95 for a black globe, and D is the diameter of
the globe which is fixed at 0.04 m.

Top is approximated as follows:

![equation](https://latex.codecogs.com/svg.image?T_%7Bo%20p%7D=%5Cfrac%7B%5Cleft(T_%7Bm%20r%20t%7D&plus;T_%7Ba%7D%20%5Ctimes%20%5Csqrt%7B10%20V_%7Ba%7D%7D%5Cright)%7D%7B1&plus;%5Csqrt%7B10%20V_%7Ba%7D%7D%7D)

At indoor condition when average of air speeds is less than 0.20 m/s, Top is approximated with following equation:

![equation](https://latex.codecogs.com/svg.image?T_%7Bo%20p%7D=0.5%5Cleft(T_%7Ba%7D&plus;T_%7Bm%20r%20t%7D%5Cright))

Results are printed in ###.csv.
