/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>



#include "schedule.h"
#include "utils.h"
#include <algorithm>


/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename)
{
  V2D out;
  std::ifstream file(filename);
  std::string line;
  if(file.is_open())
  {
    while(getline(file,line))
    {
      std::vector<std::string> temp;
      int size=SplitString(line, ',', temp);
      for(int i=0; i<size; i++)
      {
        temp[i]=Trim(temp[i]);
      }
      out.push_back(temp);
    } 
  }
  return out;
  
}
  
/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(V2D & cv, V2D & student){
    // YOUR CODE HERE
    V2D out;
    for(unsigned int i=0; i<cv.size();i++)
    {
      std::vector<std::string> line;
      std::string course=cv[i][0];
      line.push_back(course);
      for(unsigned int j=0; j<cv[i].size(); j++)
      {
        std::string stu=cv[i][j];
        for(unsigned int x=0; x<student.size();x++)
        {
          std::string tempStud=student[x][0];
          if(tempStud==stu)
          {
            for(unsigned int y=1; y<student[x].size();y++)
            {
              std::string tempCourse=student[x][y];
              if(tempCourse==course)
              {
                line.push_back(stu);
              }
            }
          }
        }
      }
      if(line.size()>1)
      {
        out.push_back(line);
      }
    }
    for(unsigned int x=0; x<out.size(); x++)
    {
      for(unsigned int y=0; y<out[x].size(); y++)
      {
        std::cout<< out[x][y] <<std::endl;
      }
    }
    return out;
}
matrix buildAdjMatrix(V2D courses)
{
  matrix adjacency_matrix;
  for(unsigned int i=0; i<courses.size();i++)
  {
    std::vector<int> temp;
    for(unsigned int j=0; j<courses.size();j++)
    {
      temp.push_back(0);
    }
    adjacency_matrix.push_back(temp);
  }
  for(unsigned int x=0; x<adjacency_matrix.size();x++)
  {
    for(unsigned int y=0; y<adjacency_matrix[0].size(); y++)
    {
      if(x==y)
      {
        adjacency_matrix[x][y]=0;
      }
      else
      {
        std::vector<std::string> temp1;
        std::vector<std::string> temp2;
        for(unsigned int i=1; i<courses[x].size(); i++)
        {
          temp1.push_back(courses[x][i]);
        }
        for(unsigned int j=1; j<courses[y].size(); j++)
        {
          temp2.push_back(courses[y][j]);
        }
        if(haveCommon(temp1, temp2))
        {
          adjacency_matrix[x][y]=1;
        }
      }
    }
  }
  return adjacency_matrix;
}

bool haveCommon(std::vector<std::string> v1, std::vector<std::string> v2)
{
  for(unsigned int i=0; i<v1.size();i++)
  {
    std::string temp=v1[i];
    for(unsigned int j=0; j<v2.size();j++)
    {
      std::string temp2=v2[j];
      if(temp==temp2)
      {
        return true;
      }
    }
  }
  return false;
}

std::vector<int> getColorList(matrix m)
{
  std::vector<int> colorList;
  for(unsigned int i=0; i<m.size(); i++)
  {
    for(unsigned int j=0; j<m[i].size(); j++)
    {
      if(m[i][j]==1)
      {
        colorList.push_back(i);
        colorList.push_back(j);
      }
    }
  }
  return colorList;
}

int numColor(matrix m)
{
  std::vector<int> colorList=getColorList(m);
  int ans=1;
  std::vector<int> second;
  for(unsigned int j=colorList.size()/2; j<colorList.size(); j++)
  {
    second.push_back(colorList[j]);
  }
  for(unsigned int i=0; i<(colorList.size()/2)-1; i++)
  {
    std::vector<int> temp;
    int a=colorList[i];
    int b=colorList[i+1];
    temp.push_back(b);
    temp.push_back(a);
    if(containsColor(second, temp))
    {
      ans++;
    }
  }
  return ans;
}

bool containsColor(std::vector<int> v1, std::vector<int> v2)
{
  std::vector<int>::iterator iter;
  iter = std::search(v1.begin(), v1.end(), v2.begin(), v2.end());
  if (iter != v1.end())
  {
    return true;
  }
  else
  {
    return false;
  }

}
    

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */

V2D schedule(V2D courses, std::vector<std::string> timeslots){
    // Your code here!
    V2D ans;
    matrix adj_matrix=buildAdjMatrix(courses);
    int color=numColor(adj_matrix);
    int num=timeslots.size();
    std::vector<int> courseAdded;
    for(unsigned int i=0; i<courses.size(); i++)
    {
      courseAdded.push_back(0);
    }
    if(num<color)
    {
      std::vector<std::string> ans2;
      for(int i=0; i<5; i++)
      {
        ans2.push_back("-1");
      }
      ans.push_back(ans2);
    }
    else
    {
      for(unsigned i=0; i<timeslots.size(); i++)
      {
        std::vector<std::string> l;
        l.push_back(timeslots[i]);
        for(unsigned y=0; y<adj_matrix.size(); y++)
        {
          for(unsigned x=y; x<adj_matrix[x].size(); x++)
          {
            if(adj_matrix[y][x]==0&&courseAdded[x]==0)
            {
              l.push_back
            }
          }
        }
      }
    }
    return ans;
}