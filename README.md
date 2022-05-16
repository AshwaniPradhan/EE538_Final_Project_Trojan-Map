# EE538 Final Project - Spring 2022 - TrojanMap

## Deadline: 


Phase 1 submission: Monday, April 11 by 23:59 pm

Phase 2 submission: Wednesday, April 20 by 23:59 pm

Phase 3 submission: Sunday, May 1 by 23:59 pm

Video Presentation: Friday, April 29


## TrojanMap

This project focuses on using data structures in C++ and implementing various graph algorithms to build a map application.

<p align="center"><img src="img/TrojanMap.png" alt="Trojan" width="500" /></p>

- Please clone the repository, look through [README.md](README.md) and fill up functions to finish in the project.
- Please make sure that your code can run `bazel run/test`.
- In this project, you will need to fill up [trojanmap.cc](src/lib/trojanmap.cc) and add unit tests in the `tests` directory.

---

## The data Structure

Each point on the map is represented by the class **Node** shown below and defined in [trojanmap.h](src/lib/trojanmap.h).

```cpp
class Node {
  public:
    Node(){};
    Node(const Node &n){id = n.id; lat = n.lat; lon = n.lon; name = n.name; neighbors = n.neighbors; attributes = n.attributes;};
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string> neighbors;  // List of the ids of all neighbor points.
    std::unordered_set<std::string> attributes;  // List of the attributes of the location.
};
```

---

## Prerequisites

### OpenCV Installation

For visualization, we use OpenCV library. You will use this library as a black box and don't need to worry about the graphic details.

Use the following commands to install OpenCV and other libarary.

### Other library Installations

For MacOS:
```shell
$ brew install cmake
$ brew install opencv
$ brew install ncurses
```

For Ubuntu:
```shell
$ cd **your project folder**
$ git clone https://github.com/opencv/opencv.git
$ sudo apt-get install cmake libgtk2.0-dev pkg-config
$ sudo apt install libcanberra-gtk-module libcanberra-gtk3-module
$ sudo apt-get install libncurses5-dev libncursesw5-dev
$ cp ubuntu/* ./
```

Next, type the following, but make sure that you set the **path_to_install_folder** to be the absolute path to the **install** folder under opencv.

```shell
$ cd opencv/
$ mkdir build install
$ cd build
$ cmake -D CMAKE_INSTALL_PREFIX=**path_to_install_folder** -D BUILD_LIST=core,highgui,imgcodecs,imgproc,videoio ..
$ make install
```

For example, if cloned this repo under "/Users/ari/github/TrojanMap", you should type:

```shell
$ cd opencv/
$ mkdir build install
$ cd build
$ cmake -D CMAKE_INSTALL_PREFIX=/Users/ari/github/TrojanMap/opencv/install -D BUILD_LIST=core,highgui,imgcodecs,imgproc,videoio ..
$ make install
```

---

## Run the program

Please run:

For MacOS,

```shell
$ bazel run src/main:main
```

For Ubuntu, you need to use the following command to prevent errors.
               
```shell
$ bazel run --cxxopt='-std=c++17' src/main:main
```

If everything is correct, this menu will show up.

```shell
TrojanMap
**************************************************************
* Select the function you want to execute.                    
* 1. Autocomplete                                             
* 2. Find the location                                        
* 3. CalculateShortestPath                                    
* 4. Travelling salesman problem                              
* 5. Cycle Detection                                          
* 6. Topological Sort                                         
* 7. Find Nearby                                              
* 8. Exit                                                     
**************************************************************
Please select 1 - 8:
```

## Test the program

We created some tests for you to test your program, please run
```shell
$ bazel test tests:trojanmap_test
```

Please add you test in the [trojanmap_test_student.cc](tests/trojanmap_test_student.cc) and run

```shell
$ bazel test tests:trojanmap_test_student
```

# Final Report by Ashwani Pradhan and Krishna Kamal

youtube video link: https://www.youtube.com/watch?v=jEV6EDE8q30&t=303s


## Step 1: Autocomplete the location name

```c++
std::vector<std::string> Autocomplete(std::string name);
```

We consider the names of nodes as the locations. Implement a method to type the partial name of the location and return a list of possible locations with partial name as prefix. Please treat uppercase and lower case as the same character.

Example:

Input: "Chi" \
Output: ["Chick-fil-A", "Chipotle", "Chinese Street Food"]

Example:

```shell
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:ch
*************************Results******************************
Chinese Street Food
Cheebos Burger
Chick-fil-A
Chase
Chevron 1
Chipotle
Chase Plaza Heliport
Chevron 2
Church of Christ
Chucks Chicken & Waffles
Chevron
**************************************************************
Time taken by function: 2 ms
```

## Implementation and Results:
We accept the user input in string format and change it to lower case(to avoid case-sensitivity), before looking through each node for matching substring. 
Post which the autocomplete suggestions are displayed.

![Screenshot from 2022-04-30 17-41-50](https://user-images.githubusercontent.com/89834934/166133971-73eb7919-7493-4f06-9934-2a0b43efd0d8.png)


a) Following is the output for a valid user input:

```shell
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:noRM
*************************Results******************************
Normandie & Exposition
Normandie & Jefferson
Normandie & 29th 1
Normandie & 29th
Normandie & 36th
Normandie & Adams 1
Normandie & 24th
Normandie & 24th 1
Normandie & Exposition 1
Normandie Elementary School
Normandie & Jefferson 1
Normandie & Adams
Normandie & 36th 1
**************************************************************
Time taken by function: 3 ms
```

b) Following is the result for invalid input:

```shell
**************************************************************
* 1. Autocomplete                                             
**************************************************************

Please input a partial location:90q
*************************Results******************************

**************************************************************
Time taken by function: 3 ms
```
From the above results, we can see that each result takes almost the same time to be displayed. The reason is that the implemeted algorithm is travelling all the
nodes to find a match for entered substring. So the worst case time-complexity for this algorithm is given by O(n).


## Step 2-1: Find the place's Coordinates in the Map

```c++
std::pair<double, double> GetPosition(std::string name);
```

Given a location name, return the latitude and longitude. There are no duplicated location names. You should mark the given locations on the map. If the location does not exist, return (-1, -1). The algorithm is case-sensitive.

Example:

Input: "Target" \
Output: (34.0257016, -118.2843512)

```shell
**************************************************************
* 2. Find the position                                        
**************************************************************

Please input a location:Target
*************************Results******************************
Latitude: 34.0257 Longitude: -118.284
**************************************************************
Time taken by function: 1 ms
```
<p align="center"><img src="img/Target.png" alt="Target" width="500"/></p>

## Implemetation and Result:
To implement this function, we iterate through the data vector to find the matching location name, and as we have a match, we capture the longitude and lattitude of that particular location from the datasheet and return that as the result for the user query.

![Screenshot from 2022-04-30 17-42-07](https://user-images.githubusercontent.com/89834934/166133981-940bffbf-4e1e-4c70-9055-310dcad60a98.png)


One valid result is displayed here:
```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:Chipotle 
*************************Results******************************
Latitude: 34.017 Longitude: -118.282
**************************************************************
Time taken by function: 2 ms
```
![Screenshot from 2022-05-01 17-01-05](https://user-images.githubusercontent.com/89834934/166164476-931f4e2b-7def-40e7-ac8d-3e8acaa8b434.png)


Another result for invalid input with "Did you mean" suggestion:
```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:l897
*************************Results******************************
No matched locations.
Did you mean 94 instead of l897? [y/n]n
**************************************************************
Time taken by function: 2 ms
```

Result for empty name given in the user entry:
```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:
*************************Results******************************
No matched locations.
Did you mean  instead of ? [y/n]y
Latitude: -1 Longitude: -1
**************************************************************
Time taken by function: 0 ms
```

The time-complexity for the algorithm is given by O(n).

## Step 2-2: Check edit distance between two location names

```c++
int CalculateEditDistance(std::string name1, std::string name2);
```

When entering a location name that does not exist in the map, the map will determine whether the input can be replaced with a "similar name" or not. Similar names refer to the names that exist in the map with a smallest distance from the original input. The distance between two names A and B is the minimum number of operations required to convert A to B. There are 3 operations:
+ Insert a character
+ Delete a character
+ Replace a character

If the exact match is found, it will be shown on the map. Otherwise, the map will show the most similar name by using FindClosestName and print a warning. For example, if I type Rolphs, I should get a warning like "Did you mean Ralphs instead of Rolphs?"

You can use dynamic programming to calculate edit distance. 

Example:

Input: "Rolphs", "Ralphs" \
Output: 1

```c++
std::string FindClosestName(std::string name);
```

Example:

Input: "Rolphs"\
Output: "Ralphs"

******************************************************************
All the functions for the phase-1 are implemented and completed.
*******************************************************************

### Implementation and Results
CalculateEditDistance:
Here we make use of Levenshtein Distance algorithm to calculate the distance between two strings.
To make use of dynamic programming concept, we use a 2D vector(string, int) for tabulization. We initialize the matrix for the given length of two strings. We have the base condition as if the one of the string is empty then the other string is the optput. The we run into a loop to compare the character from first string to second string. If the characters from both strings are not the same then we take the minimum from three specifies operation(insert, delete, replace). We use the bottom-up approach, considering the ascending order of indexes while calculating the distance between strings.
Time complexity for this algorithm is given by O(n*m).(n and m are the length of respective strings.)

FindClosestName: 
Here we use the CalculateEditDistance function and compare the entered string with all the strings in the data vector to find the ones, which are closet to the entered string and the output will show the closet one as an suggestion for "Did you mean".
Because we are using CalculateEditDistance with a for loop to through the data vector and compare, the time complexity for this function is O(no. of data point *n*m)
n and m are length of two strings.

```shell
**************************************************************
* 2. Find the location                                        
**************************************************************

Please input a location:Rolphs
*************************Results******************************
No matched locations.
Did you mean Ralphs instead of Rolphs? [y/n]y
Latitude: 34.0318 Longitude: -118.291
**************************************************************
Time taken by function: 2 ms
```



## Step 3: CalculateShortestPath between two places

```c++
std::vector<std::string> CalculateShortestPath_Dijkstra(std::string &location1_name,
                                               std::string &location2_name);
std::vector<std::string> CalculateShortestPath_Bellman_Ford(std::string &location1_name,
                                               std::string &location2_name);
```

Given 2 locations A and B, find the best route from A to B. The distance between 2 points is the euclidean distance using latitude and longitude. You should use both Dijkstra algorithm and Bellman-Ford algorithm. Compare the time for the different methods. Show the routes on the map. If there is no path, please return empty vector.

Please report and compare the time spent by these 2 algorithms.

Example:

Input: "Ralphs", "ChickfilA" \
Output: ["2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441",
      "6813405269", "6816193784", "6389467806", "6816193783", "123178876", "2613117895", "122719259",
      "2613117861", "6817230316", "3642819026", "6817230310", "7811699597", "5565967545", "123318572",
      "6813405206", "6813379482", "544672028", "21306059", "6813379476", "6818390140", "63068610", 
      "6818390143", "7434941012", "4015423966", "5690152766", "6813379440", "6813379466", "21306060",
      "6813379469", "6813379427", "123005255", "6807200376", "6807200380", "6813379451", "6813379463",
      "123327639", "6813379460", "4141790922", "4015423963", "1286136447", "1286136422", "4015423962",
      "6813379494", "63068643", "6813379496", "123241977", "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544",
      "6813405275", "348121996", "348121864", "6813405280", "1472141024", "6813411590", "216155217", 
      "6813411589", "1837212103", "1837212101", "6820935911", "4547476733"]

```shell
**************************************************************
* 3. CalculateShortestPath                                    
**************************************************************

Please input the start location:Ralphs
Please input the destination:Target
*************************Dijkstra*****************************
*************************Results******************************
"2578244375","5559640911","6787470571","6808093910","8410528464","8410528457","6808093913","6808093919","6816831441","6813405269","6816193784","6389467806","6816193783","123178876","2613117895","122719259","6807243574","6807243576","213332111","441895337","441895335","122719255","2613117893","6813405231","6813405237","6813405235","6047197523","6813379584","5237417650",
The distance of the path is:0.823773 miles
**************************************************************
Time taken by function: 23 ms

*************************Bellman_Ford*************************
*************************Results******************************
"2578244375","5559640911","6787470571","6808093910","8410528464","8410528457","6808093913","6808093919","6816831441","6813405269","6816193784","6389467806","6816193783","123178876","2613117895","122719259","6807243574","6807243576","213332111","441895337","441895335","122719255","2613117893","6813405231","6813405237","6813405235","6047197523","6813379584","5237417650",
The distance of the path is:0.823773 miles
**************************************************************
Time taken by function: 3484 ms
```

<p align="center"><img src="img/Routing.png" alt="Routing" width="500"/></p>


### 3.1 Dijkstra: Implemetation and Result:
Dijkstra uses greedy approach. Here we initialized the distance from source to each node as infinity. Then we took an unordered map called predecessor which keeps track of all previous nodes (which are locations), to build the entire shortest path after the algorithm has run.
We are using a min_heap to keep track of the shortest distance from the source at all times.

We iterate through neighbors of the top of the heap and if the distance to the current node + edge is less than the neighbors previously-stored, we push it into to the heap, and we repeat this process until the heap is empty.
One limitation of Dijkstra is that it can not handdle the neagative cycles.
The worst case time complexity for this algorithms is O(E*log(V)), where E-edges and V- vertices.

The result is shown below:
```shell
**************************************************************
* 3. CalculateShortestPath                                    
**************************************************************

Please input the start location:Target
Please input the destination:Ralphs
*************************Dijkstra*****************************
*************************Results******************************
"5237417650","6814769289","6813379584","6813379479","4015372485","7071032399","4015372486","6813405232","122719216","6813405229","4015372487","4015372488","6813405266","6813416159","122814447","4015377689","4015377690","6816193698","6807937306","6807937309","6804883323","6816193696","544693739","4015377691","6816193694","6816193693","6816193692","4015442011","6787470576","6816193770","123230412","452688931","452688933","6816193774","123408705","6816193777","452688940","123318563","6813416129","6813416130","7645318201","6813416131","8410938469","6805802087","4380040167","4380040158","4380040154","2578244375",
The distance of the path is:0.927969 miles
**************************************************************
Time taken by function: 62 ms
```
### 3.1 Bellman_Ford: Implemetation and Result:

Here We used the iterative approach. We used a map called distance to save the distance from source to that node. The main idea here is to relax all the edges during each iterarion. We initialized all the distances from source to each node as infinity. When we traverse through the graph, we use an extra intermediate edge each time and update the distance of the node with the shortest calculated distance.
Bellman_ford can potentially handle the negative edges and cycles. 

```shell
*************************Bellman_Ford*************************
*************************Results******************************
"5237417650","6814769289","6813379584","6813379479","4015372485","7071032399","4015372486","6813405232","122719216","6813405229","4015372487","4015372488","6813405266","6813416159","122814447","4015377689","4015377690","6816193698","6807937306","6807937309","6804883323","6816193696","544693739","4015377691","6816193694","6816193693","6816193692","4015442011","6787470576","6816193770","123230412","452688931","452688933","6816193774","123408705","6816193777","452688940","123318563","6813416129","6813416130","7645318201","6813416131","8410938469","6805802087","4380040167","4380040158","4380040154","2578244375",
The distance of the path is:0.927969 miles
**************************************************************
Time taken by function: 7254 ms
```

As we are traversing through all the nodes and edges in the graph, the time-complexity for this algorithm is given by: O(E*V), where E-edges and V- vertices

![Screenshot from 2022-05-01 15-23-12](https://user-images.githubusercontent.com/89834934/166164572-e9323671-1b2f-4ea9-9f5d-a42e7c123fd8.png)

Following is the result from Google Maps, which is same as calculated by out algorithm:

![Screenshot from 2022-05-01 17-06-20](https://user-images.githubusercontent.com/89834934/166164663-b8f7bdab-aa4f-40ae-b381-3a13eb923706.png)

### Observation:
As we can see above, the time taken by Bellman_Ford algorithm is significantly higher than Dijkstra algorithm,  as we go through all the nodes and edges in the graph before providing the output where Dijkstra does not run all the nodes instead it jumps out if it reaches the inquired location. Following is the runtime comparison for Bellman Ford and Dijkstra for multiple origin and destination locations:

![Screenshot from 2022-05-01 17-10-30](https://user-images.githubusercontent.com/89834934/166164775-4b60adda-aabe-456f-ae9b-63540278a383.png)

Dijkstra's algorithm worked better in this application because there are no negative edges or negative cycles because every edge is greater than one. 


## Step 4: The Travelling Trojan Problem (AKA Travelling Salesman!)

In this section, we assume that we are using a UAV which means we can fly directly from 1 point to another point. Given a vector of location ids, assume every location can reach all other locations in the vector (i.e. assume that the vector of location ids is a complete graph).
Find the shortest route that covers all the locations exactly once and goes back to the start point. 

You will need to return the progress to get the shortest route which will then be converted to an animation.  

We will use the following algorithms:
- Brute-force (i.e. generating all permutations, and returning the minimum)
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Brute_force(
      std::vector<std::string> location_ids);
```

In this algorithm, we are considering the permutaions for every combination of the location ids so the worst case time-complexity for this algorithm can be given by O(n!).


- Brute-force enhanced with early backtracking
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Backtracking(
      std::vector<std::string> location_ids);
```

- [2-opt Heuristic](https://en.wikipedia.org/wiki/2-opt). Also see [this paper](http://cs.indstate.edu/~zeeshan/aman.pdf)
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(
      std::vector<std::string> location_ids);
```

We use early backtracking when the current cost is higher than current minimum.

Please report and compare the time spent by these 3 algorithms. 2-opt algorithm may not get the optimal solution. Please show how far your solution is from the optimal solution.

Show the routes on the map. For each intermediate solution, create a new plot. Your final video presentation should include the changes to your solution.

We will randomly select N points in the map and run your program.



```shell
**************************************************************
* 4. Travelling salesman problem                              
**************************************************************

In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.

Please input the number of the places:8
"8201681442","6197156485","7786565237","6820972477","6807600525","1832234142","6819144993","1873055949",
Calculating ...
*************************Results******************************
TravellingTrojan_Brute_force
"8201681442","1873055949","6197156485","1832234142","6807600525","6819144993","7786565237","6820972477","8201681442",
The distance of the path is:7.94756 miles
**************************************************************
You could find your animation at src/lib/output.avi.          
Time taken by function: 59 ms

Calculating ...
*************************Results******************************
TravellingTrojan_Backtracking
"8201681442","6820972477","7786565237","6819144993","6807600525","1832234142","6197156485","1873055949","8201681442",
The distance of the path is:7.94756 miles
**************************************************************
You could find your animation at src/lib/output_backtracking.avi.
Time taken by function: 20 ms

Calculating ...
*************************Results******************************
TravellingTrojan_2opt
"8201681442","1873055949","6197156485","1832234142","6807600525","6819144993","7786565237","6820972477","8201681442",
The distance of the path is:7.94756 miles
**************************************************************
You could find your animation at src/lib/output_2opt.avi.     
Time taken by function: 0 ms
```

<p align="center"><img src="img/TSP.png" alt="TSP" width="500"/></p>

<p align="center"><img src="img/output.gif" alt="TSP videos" width="500"/></p>





## Brute-force - Implementation and Result:

```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Brute_force(
      std::vector<std::string> location_ids);
```

Here we consider all the permutations of given locations. We calculate the effective distance and if that distance is not minimum (if it can not be included as valid solution), we discard it. And finally, we take the minimum distance of them all.

![Screenshot from 2022-05-01 17-29-48](https://user-images.githubusercontent.com/89834934/166165392-29aca82c-82f9-421b-8485-fbc026e4b49d.png)

FOllowing is the output for 9 points:
```shell
**************************************************************
* 4. Travelling salesman problem                              
**************************************************************

In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.

Please input the number of the places:9
"7362236511","2613066352","6278441230","7250039349","123371441","358850013","3411951514","2643391587","6805824915",
Calculating ...
*************************Results******************************
TravellingTrojan_Brute_force
"7362236511","2643391587","358850013","6278441230","7250039349","2613066352","123371441","6805824915","3411951514","7362236511",
The distance of the path is:9.07003 miles
**************************************************************
You could find your animation at src/lib/output0.avi.          
Time taken by function: 326 ms
```
Following is the animation for 9 points:

![output0_AdobeCreativeCloudExpress](https://user-images.githubusercontent.com/89834934/166165594-b357a272-173a-44bc-8408-aeda80c42fa1.gif)

In this algorithm, we are considering the permutaions for every combination of the location ids so the worst case time-complexity for this algorithm can be given by O(n!).



## Early-backtracking - Implementation and Result:

```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_Backtracking(
      std::vector<std::string> location_ids);
```

The algorithm for brute force and early-backtracking is almost same. The only difference is that in this algorithm, we terminate the recursion when the distance is greater than the shortest distance, which saves us some time but still the time complexity is effectively the same.
```shell
Calculating ...
The shortest path is given by: 9.07003and the size is:25
*************************Results******************************
TravellingTrojan_Backtracking
"7362236511","2643391587","358850013","6278441230","7250039349","2613066352","123371441","6805824915","3411951514","7362236511",
The distance of the path is:9.07003 miles
**************************************************************
You could find your animation at src/lib/output0_backtracking.avi.
Time taken by function: 319 ms
```
Here we can observe that the time taken for 9 points is nearly the same with very little improvement over brute-force algorithm. So the time complexity for this algorithm is also same as O(n!)
Following is the animation for 9 points:

![output0_backtracking_AdobeCreativeCloudExpress](https://user-images.githubusercontent.com/89834934/166165916-819d57f3-bdf4-4f64-8dd8-0318b1ffbe04.gif)




## 2-opt Heuristic - Implementation and Result:

```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_2opt(
      std::vector<std::string> location_ids);
```

Here we can generate one path from another using a simple move called 2-opt.
The idea is to cross path between nodes until there is no additional improvements in the result path. Each time we reverse the part of the path to see whether the new path is better than the last one,if it does then we add the current path to the records and update the current best available path. We keep doing this until there is no improvement i.e. no other better path option available.
It may not always give the shortest path, but it is a lot quicker than the backtracking approach. The time complexity of this approach is O(n^2).

The result for 9 points is shown below:
```shell
Calculating ...
*************************Results******************************
TravellingTrojan_2opt
"7362236511","2643391587","358850013","6278441230","7250039349","2613066352","123371441","6805824915","3411951514","7362236511",
The distance of the path is:9.07003 miles
**************************************************************
You could find your animation at src/lib/output0_2opt.avi.     
Time taken by function: 1 ms
```

Following is the animation for 9 points for 2-opt approach:

![output0_2opt_AdobeCreativeCloudExpress](https://user-images.githubusercontent.com/89834934/166166157-7d9306a5-6dcd-4fb8-bf89-c85e289cd6d3.gif)

## Observations and Comparison:

Following is the runtime comparison between all three approaches:
![Screenshot from 2022-05-01 17-58-45](https://user-images.githubusercontent.com/89834934/166166257-78189f6b-4bfc-48c4-9fe8-3e6f896c882c.png)

Final output on map for 9 nodes:

![Screenshot from 2022-05-01 23-01-38](https://user-images.githubusercontent.com/89834934/166179317-30d4164b-b0c1-4f64-badf-f9e6bd8c202a.png)

## 3opt:
```c++
std::pair<double, std::vector<std::vector<std::string>>> TravellingTrojan_3opt(
       std::vector<std::string> &location_ids);
double helper_3opt(std::vector<std::string> &route, int i, int j, int k, std::pair<double, std::vector<std::vector<std::string>>> &records);
```
In 3opt, we are selecting two partsof the path and 2opt seperately and this continuously done, untilno improvements can be made.
And to reverse the path here(as we did in 2opt), we use a helper function which uses CalculateDistance function, Here we swap the order of two parts of the path.

## Step 5: Cycle Detection

```c++
bool CycleDetection(std::vector<double> &square);
```

In this section, we use a square-shaped subgraph of the original graph by using four coordinates stored in ```std::vector<double> square```, which follows the order of left, right, upper, and lower bounds. 

Then try to determine if there is a cycle path in the that subgraph. If it does, return true and report that path on the map. Otherwise return false.

Example 1:
```shell
Input: square = {-118.299, -118.264, 34.032, 34.011}
Output: true
```
Here we use the whole original graph as our subgraph. 
<p align="center"><img src="img/cycle1.png" alt="TSP" width="500"/></p>

Example 2:
```shell
Input: square = {-118.290, -118.289, 34.030, 34.020}
Output: false
```
Here we use a square area inside USC campus as our subgraph
<p align="center"><img src="img/cycle2.png" alt="TSP" width="500"/></p>

```shell
5
**************************************************************
* 5. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.299
Please input the right bound longitude(between -118.320 and -118.250):-118.264
Please input the upper bound latitude(between 34.000 and 34.040):34.032
Please input the lower bound latitude(between 34.000 and 34.040):34.011
*************************Results******************************
there exists a cycle in the subgraph 
**************************************************************
Time taken by function: 0 ms

5
**************************************************************
* 5. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.290
Please input the right bound longitude(between -118.320 and -118.250):-118.289
Please input the upper bound latitude(between 34.000 and 34.040):34.030
Please input the lower bound latitude(between 34.000 and 34.040):34.020
*************************Results******************************
there exist no cycle in the subgraph 
**************************************************************
Time taken by function: 0 ms
```
### Implementation and Results:

Here the idea is to run DFS on the graph starting from each node and if we find a back edge i.e. when we hit a visited node, then the cycle is present.
So as we are traversing through each edge and vertices. 

The time-complexity for cycle detection is given by O(E+V). 

Following is the example for cycles detected in the graph:

```shell
**************************************************************
* 5. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.290
Please input the right bound longitude(between -118.320 and -118.250):-118.288
Please input the upper bound latitude(between 34.000 and 34.040):34.030
Please input the lower bound latitude(between 34.000 and 34.040):34.025
*************************Results******************************
there exists a cycle in the subgraph 
**************************************************************
Time taken by function: 0 ms
```
![Screenshot from 2022-05-01 21-41-47](https://user-images.githubusercontent.com/89834934/166177985-d7e66c94-702e-40fb-8f53-58501483cf46.png)

The single cycle can be seen below:

![Screenshot from 2022-05-01 21-41-20](https://user-images.githubusercontent.com/89834934/166178002-fb550b97-3445-4c5b-8087-b14912040b34.png)



Following is the example when cycle was not selected:
```shell
**************************************************************
* 5. Cycle Detection                                          
**************************************************************

Please input the left bound longitude(between -118.320 and -118.250):-118.290
Please input the right bound longitude(between -118.320 and -118.250):-118.289
Please input the upper bound latitude(between 34.000 and 34.040):34.030
Please input the lower bound latitude(between 34.000 and 34.040):34.020
*************************Results******************************
there exist no cycle in the subgraph 
**************************************************************
Time taken by function: 0 ms
```
Map:

![7e0ac9a3-6bc2-42a5-9c4e-35df641ada81](https://user-images.githubusercontent.com/89834934/166178044-d6a82d4d-b7cc-4f2d-88d7-d00b2af65ef6.jpeg)




## Step 6: Topological Sort

```c++
std::vector<std::string> DeliveringTrojan(std::vector<std::string> &location_names,
                                            std::vector<std::vector<std::string>> &dependencies);
```
In this section, we assume that we are using a UAV which means we can fly directly from 1 point to another point. Tommy Trojan got a part-time job from TrojanEats, for which he needs to pick up and deliver food from local restaurants to various location near the campus. Tommy needs to visit a few different location near the campus with certain order, since there are some constraints. For example, he must first get the food from the restaurant before arriving at the delivery point. 

The TrojanEats app will have some instructions about these constraints. So, Tommy asks you to help him figure out the feasible route!

Here we will give you a vector of location names that Tommy needs to visit, and also some dependencies between those locations.


For example, 

```shell
Input: 
location_names = {"Ralphs", "Chick-fil-A", "KFC"}
dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"Chick-fil-A", "KFC"}}
```

Here, ```{"Ralphs","KFC"}``` means
that Tommy must go to `Ralphs` prior to `KFC`.

Your output should be:
```shell
Output: Ralphs  -> Chick-fil-A -> KFC
```
Also, we provide ```PlotPointsOrder``` function that can visualize the results on the map. It will plot each location name and also some arrowed lines to demonstrate a feasible route.

If no feasible route exists, you could simply return an empty vector.

Hint:
- You also need to finish ```ReadLocationsFromCSVFile``` and ```ReadDependenciesFromCSVFile``` functions, so you could read and parse data from you own CSV files. We also give two sample CSV files under ```input``` folder, which could be a reference. 
- When it asks you filenames, you need to give the absolute path.
- If you do not have ```ReadLocationsFromCSVFile``` and ```ReadDependenciesFromCSVFile``` functions ready yet, you can just press enter when it asks you filenames. It will call the default locations and dependencies.
- The locations are actually nodes, and the dependencies could be directed edges. You may want to first construct a DAG and then implement topological sort algorithm to get the route.

```shell
*************************Results******************************
Topological Sorting Results:
Ralphs
Chick-fil-A
KFC
**************************************************************
Time taken by function: 2 ms
```
<p align="center"><img src="img/TopologicalSort.png" alt="TSP" width="500"/></p>

In the user interface, we read the locations and dependencies from `topologicalsort_dependencies.csv` and `topologicalsort_locations.csv` to modify your input there.

### Implementation and Results:
Here we are given a vector of locations and dependencies. We use an adjacency list with given dependencies to obtain a possible path(kind of like pre-requisites). We essentially run DFS, but on DAG(directed acyclic graphs). 
As we are going through each edges and vertices, the time complexity for this algorithm is given by: O(V+E).

Following is the output for 9 dependencies:

Input - 
dependencies
Start, Destination
Ralphs,Chick-fil-A
Ralphs,KFC
Chick-fil-A,KFC
Target,CVS Pharmacy
Target,Chick-fil-A
Chick-fil-A,Trader Joes
Food 4 Less,Target
CVS Pharmacy,Ralphs
Cal Mart Beer & Wine Food Store,Trader Joes

Locations:
Name
Ralphs
KFC
Chick-fil-A
CVS Pharmacy
Target
Trader Joes
Food 4 Less
Cal Mart Beer & Wine Food Store

Result Output->

```shell
**************************************************************
* 6. Topological Sort                                         
**************************************************************

Please input the locations filename:/home/ashwani/Documents/EE538/Final_Project/final-project-AshwaniPradhan-1/input/topologicalsort_locations_n2.csv
Please input the dependencies filename:/home/ashwani/Documents/EE538/Final_Project/final-project-AshwaniPradhan-1/input/topologicalsort_dependencies_n1.csv
CVS Pharmacy   1
Cal Mart Beer & Wine Food Store   0
Chick-fil-A   2
Food 4 Less   0
KFC   2
Name   0
Ralphs   1
Target   1
Trader Joes   2
current count 0
current count 1
current count 2
*************************Results******************************
Topological Sorting Results:
Cal Mart Beer & Wine Food Store
Food 4 Less
Name
Target
CVS Pharmacy
Ralphs
Chick-fil-A
KFC
Trader Joes
**************************************************************
Time taken by function: 0 ms
```

Following are locations on the map:
![Screenshot from 2022-05-01 22-30-48](https://user-images.githubusercontent.com/89834934/166177868-759e0327-be58-400f-bd8c-cb9589e83b7e.png)


## Step 7: Find Nearby

Given a attribute name C, a location name L and a number r and k, find at most k locations in attribute C on the map near L(do not include L) with the range of r and return a vector of string ids. The order of locaitons should from nearest to farthest. And you should not include the current location. 

```
Here we are going through each edges and vertices, so soo the time complexity of the algorithm is given by: O(E+V)

```c++
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k);
```
All attributes
```
'artwork', 'attraction', 'bakery', 'bank', 'bar', 'beauty', 'beverages', 'bicycle', 'bicycle_rental', 'bus_station', 'cafe', 'car', 'car_repair', 'car_wash', 'charging_station', 'childcare', 'clinic', 'clothes', 'confectionery', 'convenience', 'copyshop', 'dentist', 'department_store', 'driving_school', 'fabric', 'fast_food', 'food_court', 'fountain', 'fuel', 'gallery', 'hairdresser', 'hospital', 'hotel', 'library', 'marketplace', 'mobile_phone', 'museum', 'music', 'optician', 'parcel_locker', 'parking', 'pharmacy', 'place_of_worship', 'police', 'post_office', 'restaurant', 'school', 'shoe_repair', 'shoes', 'skate', 'social_facility', 'supermarket', 'theatre', 'tobacco', 'yes', 'yoga'
```
Please report and compare the time spent by this algorithm and show the points on the map.

```shell
**************************************************************
* 7. Find Nearby                                    
**************************************************************

Please input the attribute:supermarket
Please input the locations:Ralphs
Please input radius r:10
Please input number k:10
*************************Results******************************
Find Nearby Results:
1 Trader Joes
2 Cal Mart Beer & Wine Food Store
3 Food 4 Less
**************************************************************
Time taken by function: 5 ms
```

<p align="center"><img src="img/Nearby.png" alt="Nearby" width="500"/></p>

### Implementation and Result:

Here we are given an attribute, according to which we will go through the datapoints and if the data point which has the same attribute has distance to the given location(centre) less than radius (r) . We save it into the heap, then we return using the heap, k of them in order of nearest to farthest.

![Screenshot from 2022-05-01 23-07-18](https://user-images.githubusercontent.com/89834934/166179698-ea23ba05-2004-48be-8e35-10532e22688b.png)


Following is the output result:
```shell
**************************************************************
* 7. Find Nearby                                              
**************************************************************

Please input the attribute:supermarket
Please input the locations:Chick-fil-A
Please input radius r:12
Please input number k:5
*************************Results******************************
Find Nearby Results:
1 Cal Mart Beer & Wine Food Store
2 Trader Joes
3 Ralphs
4 Food 4 Less
**************************************************************
Time taken by function: 41 ms
```
![Screenshot from 2022-05-01 22-50-33](https://user-images.githubusercontent.com/89834934/166178770-97d76b31-fb02-41fa-ae94-83203ba8c585.png)


As we are traversing through the dataset and performing push and pop operations from heap, the time complexity for this algorithm is given by O(n*log(k)). 

## Reporting Runtime:
For each menu item, your program should show the time it took to finish each task.

Please make sure to provide various examples when you report the runtime. For example for topological sort, show an example with few nodes and another example with 10 or more nodes. The idea is to see how your runtime grows as input size grows.

## Runtime Comparison
For shortest path algorithms, you should compare solving the same problem with different algorithms (Dijkstra and Bellman-Ford). Please show the results on at least 3 different examples.

Similarly for TSP problem, please provide various examples that show the runtime comparison. In particular, you should show at what point using the exhaustive search is not practical and compare the same input with the heuristic implementation.

## Ncurses Implementation and result:
All the functions will be using the gui and the result will be shown as following:
![Screenshot from 2022-05-02 00-00-53](https://user-images.githubusercontent.com/89834934/166183314-ead80287-f8c1-4575-9a23-9b2a032902c2.png)

![Screenshot from 2022-05-02 00-01-11](https://user-images.githubusercontent.com/89834934/166183328-56e1ebcb-b15f-41a8-9fa2-9dbcb7e8b5ba.png)

![Screenshot from 2022-05-02 00-06-49](https://user-images.githubusercontent.com/89834934/166183330-c8f765a8-0ad8-43e2-b3b6-adcf1814bec4.png)

![Screenshot from 2022-05-02 00-07-06](https://user-images.githubusercontent.com/89834934/166183339-2b066311-074e-4206-944a-09d1303b6a95.png)

![Screenshot from 2022-05-02 00-07-17](https://user-images.githubusercontent.com/89834934/166183343-dbae147c-6ed5-48e1-8d5d-a57c656c0c25.png)




### Learning Experience: 
In this course, we learnt Object Oriented Programming concepts such as Class, constructor, destructor etc. We learnt various Data Structures such as Linked List, Stack, Queue, Binary Trees, Heaps (Min and Max Heap), Graphs and their algorithms. We also learnt various Sorting techniques.
The most interesting concept that we learnt in the project was visualizing the shortest path between two places using Graph Algorithms and solving the Travelling Salesman Problem (BackTracking, Early backtracking, and 2opt heuristic Approach).
We would like to thank Professor Arash for introducing us to the most known algorithms in Computer Science and teaching us the approach and correct thought process while solving the problems. Thanks to the TA team to be always available and help us along the way of our learning process and make it a better experience.


## Report and Rubrics:

Your final project should be checked into Github. The README of your project is your report. 

### Report:

Your REPORT.md file should include four sections:
Please create a new REPORT.md file and write your report there.

1. High-level overview of your design (Use diagrams and pictures for your data structures).
2. Detailed description of each function and its time complexity.
3. Time spent for each function.
4. Discussion, conclusion, and lessons learned.

### Rubrics:

1. Implementation of Auto complete: 5 points. (Phase 1)
2. Implementation of GetPosition: 5 points. (Phase 1)
3. Implementation of EditDistance: 10 points. (Phase 1)
4. Implementation of shortest path: 15 points. (Phase 2)
   1. Bellman-Ford implementation
   2. Dijkstra implementation
   3. Plot two paths, and measure and report time spent by two algorithms.
5. Implement of Cycle detection: 10 points. (Phase 2)
   1. Boolean value and draw the cycle if there exists one.
6. Topological Sort: 10 points. (Phase 2)
   1. Check whether there exist a topological sort or not
   2. Return the correct order and plot those point on the map
7. Implementation of Travelling Trojan: (Phase 3)
   1. Brute-force: 5 points.
   2. Brute-force enhanced with early backtracking: 5 points.
   3. 2-opt: 10 points.
   4. Animated plot: 5 points.
8. FindNearby points: 10 points. (Phase 3)
   1. Return the correct ids and draw the points.
9. Video presentation and report: 10 points. (Phase 3)
10. Creating reasonable unit tests: 10 points.
      1. Three different unit tests for each item.
11. **Extra credit items**: Maximum of 20 points:
      1. [3-opt](http://cs.indstate.edu/~zeeshan/aman.pdf): 10 points.
      2. [Genetic algorithm](https://www.geeksforgeeks.org/traveling-salesman-problem-using-genetic-algorithm/) implementation for Travelling Trojan: 10 points
      3. Create dynamic and animated UI using [ncurses](https://en.wikipedia.org/wiki/Ncurses): 10 points
         - Uncomment #define NCURSES in main.cc and mapui.h
         - Create your menu in DynamicPrintMenu().
         - You could check https://github.com/ourarash/ncurses_bazel
         - Please develope your own UI.
         - Example
            <p align="center"><img src="img/ncurses example.gif" alt="example" width="500"/></p>
               

      4. Accurate measurement of your algorithm    runtime using Google Benchmark while sweeping the input size and providing a diagram of how the runtime grows based on the input size: 10 points.



