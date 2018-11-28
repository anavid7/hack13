#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "airport.h"

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
int cmpByGPSId(const void* a, const void* b) {
  const Airport *t1 = (const Airport*)s1;
  const Airport *t2 = (const Airport*)s2;
  if (t1->gpsid > t2->gpsid) {
    return 1;
  } else if (t1->gpsid < t2->gpsid) {
    return -1;
  } else {
    return 0;
  }
}

/**
 * A comparator function that orders the two Airport structures by
 * their type.
 */
int cmpByType(const void* a, const void* b) {
  const Airport *t1 = (const Airport*)s1;
  const Airport *t2 = (const Airport*)s2;
  return strcmp(t1->type, t2->type);

}

/**
 * A comparator function that orders the two Airport structures by
 * their name in lexicographic order.
 */
int cmpByName(const void* a, const void* b) {
  const Airport *t1 = (const Airport*)s1;
  const Airport *t2 = (const Airport*)s2;
  return strcmp(t1->name, t2->name);
}

/**
 * A comparator function that orders the two Airport structures by
 * their name in reverse lexicographic order.
 */
int cmpByNameDesc(const void* a, const void* b) {
  const Airport *t1 = (const Airport*)s1;
  const Airport *t2 = (const Airport*)s2;
  return -(strcmp(t1->name, t2->name));
}
/**
 * A comparator function that orders the two Airport structures first by
 * country, then by city
 */
int cmpByCountryCity(const void* a, const void* b) {
  const Airpot *t1 = (const Aiport*)s1;
  const Aiport *t2 = (const Airpot*)s2;
  if (strcmp(t1->country, t2->country) == 0) {
    return strcmp(t1->city, t2->city);
  } else {
    return strcmp(t1->country, t2->country);
  }
}

/**
 * A comparator function that orders the given Airport structures
 * by their latitudes north to south
 */
int cmpByLatitude(const void* a, const void* b) {
  const Aiport  *t1 = (const Airport*)s1;
  const Aiport *t2 = (const Airport*)s2;
  if (t1->latitude > t2->latitude) {
    return 1;
  } else if (t1->latitude < t2->latitude) {
    return -1;
  } else {
    return 0;
  }
}
/**
 * A comparator function that orders the given Airport structures
 * by their longitudes west to east
 */
int cmpByLongitude(const void* a, const void* b) {
  const Aiport *t1 = (const Airport*)s1;
  const Aiport *t2 = (const Airport*)s2;
  if (t1->longitude > t2->longitude) {
    return 1;
  } else if (t1->longitude < t2->longitude) {
    return -1;
  } else {
    return 0;
  }
}

/**
 * A comparator function that orders the two Airport structures by
 * their relative distance from Lincoln Municipal Airport
 * (0R2, 40.846176, -96.75471)
 * in ascending order according (closest to Lincoln would come first)
 */
int cmpByLincolnDistance(const void* a, const void* b) {
  const Aiport *t1 = (const Airport*)s1;
  const Airport *t2 = (const Airport*)s2;
  Airport* lincolnAirport = createAirport("LNK", "sml", "Lincoln Municipal Airport", 40.846176, -96.75471, 1219, "Lincoln, Nebraska", "USA");
  double cows = getAirDistance(lincolnAirport, t1);
  double chickens = getAirDistance(linclonAiport, t2);
  if (cows > chickens) {
    return 1;
  } else if (cows < chickens) {
    return -1;
  } else {
    return 0;
  }
}


/**
 * A function that generates and prints several reports on the
 * given array of Airport structures.
 */
void generateReports(Airport *airports, int n) {
  int i;
  int size = sizeof(Airport);
  printf("Airports:\n");
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\n%s\n", "Sorted lists:");
  printf("%s\n", "Sort by GPS ID:");
  qsort(airports, n, size, cmpByGPSId);
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\n%s\n", "Sort by Type:");
  qsort(airports, n, size, cmpByType);
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\n%s\n", "Sort by Name:");
  qsort(airports, n, size, cmpByName);
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\n%s\n", "Sort by Name descending:");
  qsort(airports, n, size, cmpByNameDesc);
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\n%s\n", "Sort by Country & City:");
  qsort(airports, n, size, cmpByCountryCity);
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\n%s\n", "Sort by Latitude:");
  qsort(airports, n, size, cmpByLatitude);
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\n%s\n", "Sort by Longitude:");
  qsort(airports, n, size, cmpByLongitude);
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\n%s\n", "Sort by distance from Lincoln");
  qsort(airports, n, size, cmpByLincolnDistance);
  for (i=0; i<n; i++) {
    printf("%s\n", airportToString(airports[i]));
  }
  printf("\nThe closest airport to Lincoln is: %s\n", airportToString(airports[0]));

  qsort(airports, n, size, cmpByLongitude);
  printf("The median airport in terms of Longitude is: %s\n", airportToString(airports[(n/2)]));

  for(i=0; i<n; i++) {
   if (airports[i].city == "New York") {
     printf("New York Aiprot exits at indici: %d\n", i);
     printf("%s\n", airportToString(airports[i]));
   } else if (i = n-1) {
     printf("New York is not inside of this list\n");
   }
  }

  for(i=0; i<n; i++) {
    if (airports[i].countryAbbrv == "CA") {
      printf("A Canadian airport exits at indici: %d\n", i);
      printf("%s\n", airportToString(airports[i]));
    } else if (i = n-1) {
      printf("There is no Cnadian Airport in this list\n");
    }
  }

  for(i=0; i<n; i++) {
    if (airports[i].type == "large_airport") {
      printf("A larg airport exits at indici: %d\n", i);
      printf("%s\n", airportToString(airports[i]));
    } else if (i = n-1) {
      printf("There is no larg airport in this list\n");
    }
  }

}
