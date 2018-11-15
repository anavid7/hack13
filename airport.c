typedef struct {
  char* gpsId;
  char* type;
  char* name;
  double latitude;
  double longitude;
  int elevationFeet;
  char* city;
  char* countryAbbrv;
} Airport;

/**
 * A factory function to create a new Airport with the given
 * attributes.  This function should make *deep* copies of each
 * of the relevant fields and return a pointer to the newly
 * created Airport structure.
 */
Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv) {
    Airport* airport = (Airport*)malloc(sizeof(Airport));

    airport->gpsId = (char*)malloc(sizeof(char) * (strlen(gpsId) + 1));
    strcpy(airport->gpsId, gpsId);

    airport->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(airport->type, type);

    airport->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(airport->name, name);

    airport->latitude = latitude;

    airport->longitude = longitude;

    airport->elevationFeet = elevationFeet;

    airport->city = (char*)malloc(sizeof(char) * (strlen(city) + 1));
    strcpy(airport->city, city);

    airport->countryAbbrv =
     (char*)malloc(sizeof(char) * (strlen(countryAbbrv) + 1));
    strcpy(airport->countryAbbrv, countryAbbrv);

    return airport;
  }

/**
 * This function initializes an existing allocated
 * Airport structure with the given attributes.
 */
void initAirport(Airport* airport,
                 const char* gpsId,
                 const char* type,
                 const char* name,
                 double latitude,
                 double longitude,
                 int elevationFeet,
                 const char* city,
                 const char* countryAbbrv) {
    airport->gpsId = (char*)malloc(sizeof(char) * (strlen(gpsId) + 1));
    strcpy(airport->gpsId, gpsId);

    airport->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
    strcpy(airport->type, type);

    airport->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(airport->name, name);

    airport->latitude = latitude;

    airport->longitude = longitude;

    airport->elevationFeet = elevationFeet;

    airport->city = (char*)malloc(sizeof(char) * (strlen(city) + 1));
    strcpy(airport->city, city);

    airport->countryAbbrv =
       (char*)malloc(sizeof(char) * (strlen(countryAbbrv) + 1));
    strcpy(airport->countryAbbrv, countryAbbrv);
  }

/**
 * Constructs a new string representation of the given
 * Airport structure.
 */
char* airportToString(const Airport* a) {
  int n = strlen(a->gpsId) + strlen(a->type) + strlen(a->name) +
          strlen(a->city) + strlen(a->countryAbbrv) + sizeof(double) +
          sizeof(double) + sizeof(int);

  char* buff = (char*)malloc(sizeof(char) * (n + 200));

  sprintf(buff, "GPSID:      %s\nSize:       %s\nName:       %s\nLatitude-   %f\nLongitude-  %f\nElevation-  %dft\nCity:       %s\nCountry:    %s\n",
          a->gpsId, a->type, a->name,
          a->latitude, a->longitude, a->elevationFeet, a->city,
          a->countryAbbrv);

  return buff;
}

/**
 * cmputes the air distance, in kilometers, between
 * the two Airports using their latitude/longitude
 */
double getAirDistance(const Airport* origin, const Airport* destination) {
  int r = 6371;

  double rLatitudeA = ((origin->latitude) / 180) * M_PI;
  double rLatitudeB = ((destination->latitude) / 180) * M_PI;
  double rLongitudeA = ((origin->longitude) / 180) * M_PI;
  double rLongitudeB = ((destination->longitude) / 180) * M_PI;
  double rLongitudeDiffernce = rLongitudeB - rLongitudeA;

  return (acos((sin(rLatitudeA) * sin(rLatitudeB)) +
               (cos(rLatitudeA) * cos(rLatitudeB) * cos(rLongitudeDiffernce))) *
          r);
}

/**
 * cmputes the estimated travel time (in hours) for a flight
 * that involves the given stops using the average flight speed
 * (kilometers per hour) and average layover time (in hours)
 */
double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs) {
    int i = 0;
    int j = 1;
    int r = 6371;
    double totaldistince = 0;
    double distince = 0;

    while (j < size) {
      double rLatitudeA = (stops[i].latitude / 180) * M_PI;
      double rLatitudeB = (stops[j].latitude / 180) * M_PI;
      double rLongitudeA = (stops[i].longitude / 180) * M_PI;
      double rLongitudeB = (stops[j].longitude / 180) * M_PI;
      double rLongitudeDiffernce = rLongitudeB - rLongitudeA;

      distince =
          acos((sin(rLatitudeA) * sin(rLatitudeB)) +
               (cos(rLatitudeA) * cos(rLatitudeB) * cos(rLongitudeDiffernce))) *
          r;

      totaldistince += distince;
      j++;
      i++;
    }
    return ((totaldistince / aveKmsPerHour) + (aveLayoverTimeHrs * (size - 2)));
  }

/**
 * A comparator function that orders the two Airport structures by
 * their GPS IDs in lexicographic order.
 */
int cmpByGPSId(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures by
 * their type.
 */
int cmpByType(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures by
 * their name in lexicographic order.
 */
int cmpByName(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures by
 * their name in reverse lexicographic order.
 */
int cmpByNameDesc(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures first by
 * country, then by city
 */
int cmpByCountryCity(const void* a, const void* b);

/**
 * A comparator function that orders the given Airport structures
 * by their latitudes north to south
 */
int cmpByLatitude(const void* a, const void* b);

/**
 * A comparator function that orders the given Airport structures
 * by their longitudes west to east
 */
int cmpByLongitude(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures by
 * their relative distance from Lincoln Municipal Airport
 * (0R2, 40.846176, -96.75471)
 * in ascending order according (closest to Lincoln would come first)
 */
int cmpByLincolnDistance(const void* a, const void* b);

/**
 * A function that generates and prints several reports on the
 * given array of Airport structures.
 */
void generateReports(Airport *airports, int n);
