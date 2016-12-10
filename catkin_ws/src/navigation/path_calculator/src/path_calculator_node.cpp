#include "ros/ros.h"
#include "navig_msgs/CalculatePath.h"
#include <climits>
#include <math.h>
//limits.h

nav_msgs::Path global_path;
//nav_msgs::OccupancyGrid temp;

nav_msgs::OccupancyGrid grow_obs(nav_msgs::OccupancyGrid& map,
                                 int k)
{
    nav_msgs::OccupancyGrid temp;
    for(int j=0; j<k; j++)
    {
      temp = map;
      for(size_t i = map.info.width + 1; i<map.data.size() - map.info.width - 1; i++)
      {
        if(map.data[i]>50)
        {
          temp.data[i + 1] = 100;
          temp.data[i - 1] = 100;
          temp.data[i + map.info.width] = 100;
          temp.data[i - map.info.width] = 100;
          temp.data[i + map.info.width + 1] = 100;
          temp.data[i + map.info.width - 1] = 100;
          temp.data[i - map.info.width + 1] = 100;
          temp.data[i - map.info.width - 1] = 100;
        }
      }
      map = temp;
    }
    return map;
}

bool a_star(float startX, float startY, float goalX,
            float goalY, nav_msgs::OccupancyGrid& map,
            nav_msgs::Path& optimal_path)
{
    
    /*optimal_path.header.frame_id = "map";
    optimal_path.poses.clear();
    geometry_msgs::PoseStamped p;
    p.pose.position.x = 1.0;
    p.pose.position.y = 1.0;
    optimal_path.poses.push_back(p);
    p.pose.position.x = 2.0;
    p.pose.position.y = 2.0;
    optimal_path.poses.push_back(p);*/
    //*************************************************************    
    bool* isknown =  new bool[map.data.size()];
    int* gValues = new int[map.data.size()];
    int* fValues = new int[map.data.size()];
    int* previous = new int[map.data.size()];
    bool* isInOpenList = new bool[map.data.size()];
    std::vector<int> openList;
    for(size_t i=0; i < map.data.size(); i++)
    {
      isknown[i] = false;
      gValues[i] = INT_MAX;//climits
      fValues[i] = INT_MAX;
      previous[i] = -1;
      isInOpenList[i] = false;
    }
    int currentCellX = (int)( (startX - map.info.origin.position.x)/map.info.resolution );
    int currentCellY = (int)( (startY - map.info.origin.position.y)/map.info.resolution );
    int currentCell = currentCellY * map.info.width + currentCellX;
    int goalCellX =  (int)( (goalX - map.info.origin.position.x)/map.info.resolution );
    int goalCellY =  (int)( (goalY - map.info.origin.position.y)/map.info.resolution );
    int goalCell = goalCellY * map.info.width + goalCellX;

    std::cout << "Start X: "  << currentCellX << "      Start Y: "  << currentCellY << std::endl;
    std::cout << "Goal X: "  << goalCellX << "      Goal Y: "  << goalCellY << std::endl;
    std::cout << "width: "  << map.info.width << "      height: "  << map.info.height << "      Size: "  << map.data.size()  << "      Resolution: "  << map.info.resolution  << std::endl;
    std::cout << "Origen X: "  << map.info.origin.position.x << "      Origen Y: "  << map.info.origin.position.y << std::endl;
    std::cout << "currentCell: " << currentCell << "      goalCell: " << goalCell << std::endl; 

    isknown[currentCell] = true;
    gValues[currentCell] = 0;
    fValues[currentCell] = abs(goalCellY - currentCellY) + abs(goalCellX - currentCellX);
    int attempts = map.data.size();
    int* neighbors = new int[4];
    
    while(currentCell != goalCell && --attempts>0)
    {
      neighbors[0] = currentCell - 1;
      neighbors[1] = currentCell + 1;
      neighbors[2] = currentCell + map.info.width;
      neighbors[3] = currentCell - map.info.width;
      int gTemp = gValues[currentCell] + 1;
      for(int i=0; i<4; i++)
      {
        if(map.data[neighbors[i]]>50 || isknown[neighbors[i]]) continue;

        if(gTemp < gValues[neighbors[i]])
        {
          gValues[neighbors[i]] = gTemp;
          fValues[neighbors[i]] = gTemp + abs(goalCellX - neighbors[i] % map.info.width) + abs(goalCellY - neighbors[i] / map.info.width);
          previous[neighbors[i]] = currentCell;
        }
        if(!isInOpenList[neighbors[i]])
        {
          isInOpenList[neighbors[i]] = true;
          openList.push_back(neighbors[i]);
        }
      }

      int minIdx = -1;
      int minF = INT_MAX;
      for(int i=0; i<openList.size(); i++)
      {
        if(fValues[openList[i]] < minF)
        {
          minF = fValues[openList[i]];
          minIdx = i;
        }
      }
      currentCell = openList[minIdx];
      isknown[currentCell] = true;
      openList.erase(openList.begin() + minIdx);
    }
    
    std::cout << "Current Cell: " << currentCell << "    Goal Cell: " << goalCell << std::endl;
    
    if(currentCell != goalCell)
    {
      std::cout << "Cannot calculate path..." << std::endl;
      return false;
    }
    
    optimal_path.poses.clear();
    optimal_path.header.frame_id = "map";

    while(currentCell != -1)
    {
      geometry_msgs::PoseStamped p;
      p.pose.position.x = (currentCell % map.info.width) * map.info.resolution + map.info.origin.position.x;
      p.pose.position.y = (currentCell / map.info.width) * map.info.resolution + map.info.origin.position.y;
      optimal_path.poses.insert(optimal_path.poses.begin(), p);
      currentCell = previous[currentCell];
    }
    delete[] isknown;
    delete[] gValues;
    delete[] fValues;
    delete[] previous;
    delete[] isInOpenList;
    delete[] neighbors;
    return true;
}

nav_msgs::Path smooth_path(nav_msgs::Path& path, float alpha,
                           float beta)
{
    float tol = 0.0001;
    //float tol = 0.001 * path.poses.size();
    float error = tol + 1;
    //gradiente de dimension del numero de puntos
    nav_msgs::Path smoothPath = path;
    int attempts = 10000;
    while(error > tol && --attempts>0)
    {
      error = 0;
      //for(int i=1; i<path.poses.size()-1; i++)
      for(size_t i=1; i<path.poses.size()-1; i++)
      {
        float lastx = smoothPath.poses[i].pose.position.x;
        float lasty = smoothPath.poses[i].pose.position.y;
        smoothPath.poses[i].pose.position.x -= alpha * (lastx - path.poses[i].pose.position.x) + beta * (2*lastx - smoothPath.poses[i-1].pose.position.x -smoothPath.poses[i+1].pose.position.x);
        smoothPath.poses[i].pose.position.y -= alpha * (lasty - path.poses[i].pose.position.y) + beta * (2*lasty - smoothPath.poses[i-1].pose.position.y -smoothPath.poses[i+1].pose.position.y);
        //el error es la magnitud del gradiente
        //p pertenece a R^(2n),n=numero de puntos,       P-=p- + gradiente fabs()
        error += abs(smoothPath.poses[i].pose.position.x - lastx) + abs(smoothPath.poses[i].pose.position.y - lasty);
      }
    }
    return smoothPath;
    //return path;
}

bool callback_a_star(navig_msgs::CalculatePath::Request& req,
                     navig_msgs::CalculatePath::Response& res)
{
    std::cout << "StartPose: " << req.start_pose.position.x <<
        "  " << req.start_pose.position.y << std::endl;

    req.map = grow_obs(req.map, 6);

    nav_msgs::Path path;
    if(!a_star(req.start_pose.position.x,
               req.start_pose.position.y,
               req.goal_pose.position.x,
               req.goal_pose.position.y, req.map, path))
    {
        std::cout << "Cannot calculate A* :'(" << std::endl;
        return false;
    }
    std::cout << "A* calculated succesfully... " << std::endl;
    res.path = path;
    //res.path = smooth_path(path, 5, 1);
    global_path = res.path;
    return true;
}

int main(int argc, char** argv)
{
    std::cout << "Init path calculator..." << std::endl;
    ros::init(argc, argv, "path_calculator");
    ros::NodeHandle n;
    ros::ServiceServer srv = n.advertiseService(
        "/navigation/a_star", callback_a_star);
    ros::Publisher pubPath = n.advertise<nav_msgs::Path>(
        "/navigation/a_star_path", 1);
    ros::Rate loop(10);
    while(ros::ok())
    {
        pubPath.publish(global_path);
        ros::spinOnce();
        loop.sleep();
    }
}
