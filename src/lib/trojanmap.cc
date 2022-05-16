#include<limits.h>
#include "trojanmap.h"


//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string& id) {
    return 0;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string& id) { 
    return 0;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return "NULL".
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string& id) { 
    return "";
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return an empty vector.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string& id) {
    return {};
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(const std::string& name) {
  std::string res = "";
    for(auto i = data.begin(); i != data.end(); i++)
    {
    if(name == i->second.name){
      res = i->first;
    }
  }
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) 
{
  std::pair<double, double> results(-1, -1); //if name not available, return -1, -1
  double temp_latitude = -1; //initilizing temporary longitude and latitude values
  double temp_longitude = -1;
  if (name == "") //if no name is given, return (-1,-1)
  {
    return results;
  }
  for (auto i = data.begin(); i != data.end(); i++)
  {
    if (i->second.name == name)
    {
      temp_latitude = i->second.lat;
      temp_longitude = i->second.lon;
    }
  }
  //std::cout<<"Latitude:"<<temp_latitude<<"Longitude:"<<temp_longitude<<std::endl;
  results.first = temp_latitude;
  results.second = temp_longitude;
  return results;
}


/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * 
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b)
{
  int len_str1 = a.size();
  int len_str2 = b.size();
  std::vector<std::vector<int>> dp(len_str1+1, std::vector<int>(len_str2+1, 0));
  //initialization of 2D vector for tabulization
  for(int i = 0; i <= len_str1; i++)
  {
    dp[i][0] = i;
  }
  for(int j = 0; j <= len_str2; j++)
  {
    dp[0][j] = j;
  }

  if(len_str1 == 0)
  {
    return len_str2; //if first string is empty return second string size
  }
  if(len_str2 == 0)
  {
    return len_str1; //if second string is empty return first string size
  }

  for(int i = 0; i < len_str1; i++)
  {
    for(int j = 0; j < len_str2; j++)
    {
      if (a[i] == b[j])
      {
        dp[i+1][j+1] = dp[i][j];
      }
      else
      {
        dp[i+1][j+1] = std::min({dp[i][j+1], dp[i+1][j], dp[i][j]}) + 1;
        //bottom-up approach, considering in ascending order of indexes
        //here insert opration is +1 to j, delete +1 to i and replace +1 to i and j
      }

    }
  }
  return dp[len_str1][len_str2];
}

/**
 * FindClosestName: Given a location name, return the name with smallest edit distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  
  std::string tmp="";
  
  //std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  int dist=INT_MAX;
  for(auto i=data.begin();i!=data.end();i++) {
    if(TrojanMap::CalculateEditDistance(name,i->second.name)<dist){
      dist=TrojanMap::CalculateEditDistance(name,i->second.name);
      tmp=i->second.name;
    }
  }
  return tmp;
}


/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the predecefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
  //transforming the entry to lowercase 
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  for(auto i = data.begin(); i != data.end(); i++)
  {
    std::string name_str = i->second.name.substr(0, name.length());
    std::transform(name_str.begin(), name_str.end(), name_str.begin(), ::tolower);
    if(name == name_str)
    {
      results.push_back(i->second.name);
    }
  }
  if(results.size() == 0)
  {
    return {""};
  }
  return results;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < int(path.size())-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}



/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) 
{
  std::vector<std::string> path;
  std::unordered_map <std::string,std::string> predecessor;
  std::unordered_map <std::string,bool> visited; 
  std::unordered_map <std::string,double> distance; 
  //initializing distance of all vertices as infinite
  for(auto i:data){
      distance[i.second.id] = DBL_MAX;
    }
  //min heap using priority queue
  std::priority_queue <std::pair<double,std::string>,std::vector<std::pair<double,std::string>>,std::greater<std::pair<double,std::string>>> pq;       
  std::string origin = GetID(location1_name);
  std::string destination = GetID(location2_name);
  distance[origin] = 0;// origin node is visited and distance is zero
  for(auto nodes:data)
  {
    visited[nodes.second.id] = false;
  }
    pq.push(make_pair(distance[origin],origin));
    while(pq.empty()!=true){
      std::string curr = pq.top().second;
      pq.pop();
      if(curr!=destination)
      {
        if(CalculateDistance(curr,origin)>distance[curr])
        {
          continue;
        }
        else if(visited[curr])
        {
          continue;
        }
        else{
          visited[curr] = true;
          for(auto neighbour : data[curr].neighbors){
            double new_dist = distance[curr] + CalculateDistance(curr,neighbour);
             if(distance[neighbour]>new_dist){
               distance[neighbour] = new_dist;
               predecessor[neighbour] = curr;   
               pq.push(make_pair(distance[neighbour],neighbour));          
          }
          }
        }
      }
      else{
      visited[destination] = true;
      break;
      }
    }
    if(!visited[destination])
     return path;
    for(auto node = destination; node!= origin; node = predecessor[node])
    {
      path.push_back(node);
    }
    path.push_back(origin);
    std::reverse(path.begin(),path.end());
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Do the early termination when there is no change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name)
{
  std::vector<std::string> path;
  std::string begin = GetID(location1_name);
  std::string end = GetID(location2_name);
  std::unordered_map <std::string,double> distance;
  std::unordered_map <std::string,std::string> predecessor; 
  for(auto i:data)
  {
   distance[i.second.id] = DBL_MAX;
  }
  int k = 0;
  distance[begin] = 0;
  if(begin!=end)
  {
      for (int i = 0; i < data.size()-1; i++)
      {
        for (auto p: data)
        {
          std::string curr = p.second.id;
            for(auto temp_neighbor : p.second.neighbors)
            {
                  double new_distance = distance[curr] + CalculateDistance(curr,temp_neighbor);
                  if(distance[temp_neighbor]>new_distance)
                  {
                    distance[temp_neighbor] = new_distance;
                    predecessor[temp_neighbor] = curr;                    
                    k++;
                  }
            }
        }
          if(k==0){break;}
            k = 0;
      }
  }
    if(distance[end]==DBL_MAX) return path;
    for(auto node = end; node!= begin; node = predecessor[node])
    {
      path.push_back(node);
    }
    path.push_back(begin);
    std::reverse(path.begin(),path.end());
  return path;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */

void TrojanMap::TravelBruteForce(std::string origin, std::vector<std::string> &location_ids, std::string curr_node, double curr_cost, 
                                  std::vector<std::string> &curr_path, std::pair<double, std::vector<std::vector<std::string>>> &records )
                                  {
                                    if(curr_path.size() == location_ids.size())
                                    {
                                      curr_path.push_back(origin); // checking at the leaf node
                                      double final_cost = curr_cost + CalculateDistance(origin, curr_node);
                                      //checking if we want to keep this cost or not, depending on which is smaller
                                      if(final_cost <= records.first)
                                      {
                                        records.second.push_back(curr_path);
                                        records.first = final_cost;
                                      }

                                    }
                                    //if not on a leaf node
                                    for(auto i = location_ids.begin(); i != location_ids.end(); i++)
                                    {
                                      if(auto j=std::find(curr_path.begin(),curr_path.end(),*i) != curr_path.end())
                                      {//ignore the current_id if its in the path
                                      continue;
                                      }
                                      else
                                      {
                                        //if current_id is not in path, we will add it
                                        std::vector<std::string> new_path = curr_path;
                                        new_path.push_back(*i);
                                        TravelBruteForce(origin, location_ids, *i, curr_cost+CalculateDistance(curr_node, *i), new_path, records);
                                      }
                                    }
                                  }
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) 
                                    {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::string origin = location_ids[0];
  std::vector<std::string> current_path = {origin};
  records.first = DBL_MAX;
  TravelBruteForce(origin, location_ids, origin, 0, current_path, records);
  //std::cout<< "The shortest path is given by: " <<records.first<< "and the size is:" << records.second.size()<<std::endl;

  return records;
}

//Backtracking
void TrojanMap::TravelBacktrack(std::string origin, std::vector<std::string> &location_ids, std::string curr_node, double curr_cost, 
                                  std::vector<std::string> &curr_path, std::pair<double, std::vector<std::vector<std::string>>> &records )
                                  {
                                    if(curr_path.size() == location_ids.size())
                                    {
                                      // checking at the leaf node
                                      curr_path.push_back(origin); 
                                      double final_cost = curr_cost + CalculateDistance(origin, curr_node);
                                      //checking if we want to keep this cost or not, depending on which is smaller
                                      if(final_cost <= records.first)
                                      {
                                        records.second.push_back(curr_path);
                                        records.first = final_cost;
                                      }
                                    }
                                    // Early backtracking
                                    if(curr_cost > records.first)
                                    {
                                      return;
                                    }
                                    //if not on a leaf node- evaluate all children
                                    for(auto i = location_ids.begin(); i != location_ids.end(); i++)
                                    {
                                      if(auto j=std::find(curr_path.begin(),curr_path.end(),*i) != curr_path.end())
                                      {//ignore the current_id if its in the path
                                      continue;
                                      }
                                      else
                                      {
                                        //if current_id is not in path, we will add it
                                        std::vector<std::string> new_path = curr_path;
                                        new_path.push_back(*i);
                                        TravelBruteForce(origin, location_ids, *i, curr_cost+CalculateDistance(curr_node, *i), new_path, records);
                                      }
                                    }
                                  }




std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::string origin = location_ids[0];
  std::vector<std::string> current_path = {origin};
  records.first = DBL_MAX;
  TravelBacktrack(origin, location_ids, origin, 0, current_path, records);
  std::cout<< "The shortest path is given by: " <<records.first<< "and the size is:" << records.second.size()<<std::endl;
  return records;
}
////////////////////////////
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> location_ids){
std::pair<double, std::vector<std::vector<std::string>>> records;
std::vector<std::string> curr_path = location_ids;
// pushing the first location into the current path
  curr_path.push_back(location_ids[0]);
  int size = location_ids.size();
  bool flag = true;
  while(flag){
    repeat:
    flag = false;
    double curr_path_length = CalculatePathLength(curr_path);
    for(int i = 1; i <= size - 2; i++){
      for(int k = i + 1; k <= size - 1; k++){
        auto new_path = Helper_2_opt(curr_path, i, k);
        double new_path_length = CalculatePathLength(new_path);
        if(new_path_length < curr_path_length){
          curr_path = new_path;
          curr_path_length = new_path_length;
          records.first = curr_path_length;
          records.second.push_back(curr_path);
          flag = true;
          goto repeat;
        }
      }
    }
  }
  return records;
}

std::vector<std::string> TrojanMap::Helper_2_opt(const std::vector<std::string> &path, int i, int k) {
  std::vector<std::string> path_swap(path);
  std::reverse(path_swap.begin() + i, path_swap.begin() + k + 1);
  return path_swap;
}


//3opt 

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(
       std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  std::vector< std::vector<int> > permutaions;

  std::vector<std::string> route1(location_ids);
  std::vector<std::string> route2(location_ids);
  route2.push_back(location_ids[0]);
  
  // all permutations of segment
  for(int i = 1; i < location_ids.size(); i ++){
    for(int j = i + 2; j < location_ids.size(); j++){
      for(int k = j + 2; k < location_ids.size() + (i > 0); k++){
        std::vector<int> tmp;
        tmp.push_back(i);
        tmp.push_back(j);
        tmp.push_back(k);
        std::cout<<i<<j<<k<<std::endl;
        permutaions.push_back(tmp);
      }
    }
  }
  while(true){
    double diff = 0;
    for(auto it: permutaions){
      diff += helper_3opt(route2, it[0], it[1], it[2], records);
    }

    if(diff >= 0){
      break;
    }
  }
  records.first = CalculatePathLength(records.second[records.second.size() - 1]);
  return records;        
}


double TrojanMap::helper_3opt(std::vector<std::string> &route, int i, int j, int k, std::pair<double, std::vector<std::vector<std::string>>> &records){

  std::string t1 = route[i - 1];
  std::string t2 = route[i];
  std::string t3 = route[j - 1];
  std::string t4 = route[j];
  std::string t5 = route[k - 1];
  std::string t6 = route[k % route.size()];

  double dist1 = CalculateDistance(t1,t2) + CalculateDistance(t3,t4) + CalculateDistance(t5,t6);
  double dist2 = CalculateDistance(t1,t3) + CalculateDistance(t2,t4) + CalculateDistance(t5,t6);
  double dist3 = CalculateDistance(t1,t2) + CalculateDistance(t3,t5) + CalculateDistance(t4,t6);
  double dist4 = CalculateDistance(t1,t4) + CalculateDistance(t5,t2) + CalculateDistance(t3,t6);
  double dist5 = CalculateDistance(t6,t2) + CalculateDistance(t3,t4) + CalculateDistance(t5,t6);

  if(dist1 > dist2){
    std::reverse(route.begin() + i, route.begin() + j);
    records.second.push_back(route);
    return dist2 - dist1;
  }

  else if(dist1 > dist3){
    std::reverse(route.begin() + j, route.begin() + k);
    records.second.push_back(route);
    return dist3 - dist1;
  }

  else if(dist1 > dist5){
    std::reverse(route.begin() + i, route.begin() + k);
    records.second.push_back(route);
    return dist5 - dist1;
  }
  else if(dist1 > dist4){
    int count = 0;
    std::vector<std::string> route1(route.begin() + j, route.begin() + k);
    std::vector<std::string> route2(route.begin() + i, route.begin() + j);
    route1.insert(route1.end(), route2.begin(), route2.end());
    for(auto it : route1){route[i + count] = it;}
    records.second.push_back(route);
    return dist4 - dist1;
  }
  return 0;
}


/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */

std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;

  std::fstream my_file;
  std::string line;
  my_file.open(locations_filename, std::ios::in);
 

  while (std::getline(my_file, line)) 
  {
    line.erase(std::remove(line.begin(),line.end(),','), line.end());
    if(line!="")
      location_names_from_csv.push_back(line);
  }
  my_file.close();

  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */

std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream my_file;
  my_file.open(dependencies_filename, std::ios::in);
  std::string line;

  std::getline(my_file, line);
  while (std::getline(my_file, line)) {
    //Creating 2 strings for the two locations
    std::string loc1 , loc2;
    auto loc = line.find(',');
    if(loc==0 || loc==line.size()-1)
    {
      continue;
    } 
    loc1 = line.substr(0,loc);
    loc2 = line.substr(loc+1);
    loc2.erase(std::remove(loc2.begin(),loc2.end(),','), loc2.end());
    dependencies_from_csv.push_back({loc1,loc2});
  }
  my_file.close();
  return dependencies_from_csv;
}


/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies. If there is no way to do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;
  std::map<std::string, int> vertex_in; //indegree and outdegree for DAG
  std::map<std::string, int> marked;

  // initialize the vertex_in with 0
  for(auto i : locations)
  {
    vertex_in[i] = 0;
    marked[i] = 0;
  }


  // caculate the degree of i in the locations
  for(auto i : dependencies){
    for(int j = 1; j < i.size(); j++){
      // current id is been pointed
      vertex_in[i[j]] += 1;
    }
  }

  for(auto i : vertex_in){
    std::cout<<i.first<<"   "<<i.second<<std::endl;
  }

  int count = 0;

  while(result.size() < locations.size()){

    std::cout<<"current count "<<count<<std::endl;

    for(auto it : vertex_in){
      if(it.second == 0 and std::find(result.begin(), result.end(), it.first) == result.end())
      {
        //std::cout<<"current "<<it.first<<"  with vertex_in "<<count<<"  it pushed in"<<std::endl;
        result.push_back(it.first);

        //make the current id's neighbor vertex_in - 1;
        for(auto i : dependencies)
        {
          if(i[0] == it.first)
          {
            for(int j = 1; j < i.size(); j++)
            {
              vertex_in[i[j]] -= 1;
            }
          }
        }
      }
    }

    count += 1;

    if(count > 10*locations.size())
    {
      std::cout<<"No options available"<<std::endl;
      std::vector<std::string> empty = {""};
      return empty;
    }
   // PlotPointsOrder(result);

  }
  return result;                                                     
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) 
{
  std::vector<std::string> id_sq = GetSubgraph(square);
  if(std::find(id_sq.begin(), id_sq.end(), id) != id_sq.end()) { return true;} 
  else {return false;}
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  
  double vertex_1 = square[0];
  double vertex_2 = square[1];
  double vertex_3 = square[2];
  double vertex_4 = square[3];

  for(auto j = data.begin(); j != data.end(); j++){
    if((data[j->first].lon)>vertex_1 && (data[j->first].lon)<vertex_2){
      if((data[j->first].lat)<vertex_3 && (data[j->first].lat)>vertex_4){
        subgraph.push_back(data[j->first].id);
      }
    }
  }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<std::string>} subgraph: list of location ids in the square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */

//helper function for cycle detection
bool TrojanMap::has_cycle(std::string curr,std::unordered_map<std::string, bool> &marked, std::string predecessor)
{
  marked[curr] = true;
  for(auto i:data[curr].neighbors)
  {
    if(marked.find(i) != marked.end())
      { 
      if(marked[i] == false)
      {
        if(has_cycle(i,marked,curr))
        {
          return true;
        }
      }
      else if((i!=predecessor) && (marked[i]== true)) {return true;}
    }
  }
  return false;
}

bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) 
{
  std::unordered_map<std::string, bool> marked;

  for(auto i:subgraph){
    marked[i] = false;
  }

  for(auto i:subgraph)
  {
    if(marked[i] == false)
    {
      if (has_cycle(i,marked,"")){ return true;
 }
    }
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r, 
 * find all locations in class C on the map near L with the range of r and return a vector of string ids
 * 
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  std::priority_queue<std::pair<double,std::string>> min_heap;
  if(GetID(name).empty() || k<1){return res;}
  for(auto i=data.begin();i!=data.end();i++){
    if(std::find((*i).second.attributes.begin(),(*i).second.attributes.end(),attributesName)!=(*i).second.attributes.end() && GetID(name)!=(*i).second.id){
    double dist=CalculateDistance(GetID(name),(*i).second.id);
     if(dist<r){
       std::pair <double, std::string> pair;
       pair=make_pair(dist,i->second.id);
       min_heap.push(pair);
     }
    }
  }
  int t=0;
  while (min_heap.empty()!=true && t<k)
  {
    res.push_back(min_heap.top().second);
    min_heap.pop();
    t+=1;
  }
  std::reverse(res.begin(),res.end());
  return res;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0]))
          n.attributes.insert(word);
        if (isdigit(word[0]))
          n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

