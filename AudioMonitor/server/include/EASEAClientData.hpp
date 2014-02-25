/**
 * @file EASEAClientData.c
 * @author Pallamidessi Joseph
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
**/  
#ifndef _EASEACLIENTDATA_HPP__
#define _EASEACLIENTDATA_HPP__

#include <cstdio>
#include <cstdlib>
#include <vector>

/**
*  /struct   EASEAClientData 
*  /brief    Represent an EASEA client and store its data. 
*  /details  Hold client data and socket. 
*  
**/
class EASEAClientData {
  
  public:
    
    /*Constructor/Destructor------------------------------------------------------*/ 
    /**
    * /brief    Constructor of EASEAClientData
    * /details  Empty constructor
    *
    **/
    EASEAClientData ();
    
    
    /**
    * /brief    Constructor of EASEAClientData
    * /details Store the client's socket.
    *
    * @param  sock A previously created socket representing an EASEA client
    **/
    EASEAClientData (int sock);
    
    
    /**
    * /brief    Destructor of EASEAClientData   
    * /details 
    *
    **/
    virtual ~EASEAClientData ();
    
    /*Method----------------------------------------------------------------------*/
    /**
    * /brief    A more generic way to add data. 
    * /details  See specific implementation for details.
    *
    *  @param  buffer Adress to the data to process
    **/
    virtual void processBuffer(char* buffer);
    

    /**
    * /brief    Add data to the different vector.
    * /details  TODO: Not very generic.
    *
    *  @param  best     Value to push back to the best's vector.
    *  @param  worst    Value to push back to the worst's vector.
    *  @param  stdev    Value to push back to the stdev's vector.
    *  @param  average  Value to push back to the average's vector.
    **/
    void addData(float best,float worst,float stdev,float average);
    
    
    /**
    * /brief    Print the content of the different vectors.
    * /details  For debugging purpose, print on stdout.
    *
    **/
    void print();

    
    /*Getter----------------------------------------------------------------------*/
    /**
    * /brief   Return the socket.
    * /details Getter.
    *
    * @return  socket This instance's socket.
    **/
    int getSocket();
    
    
    /**
    * /brief   Return the last data on each vector, in an array.
    * /details TODO: dirty
    *
    * @return  array An flat array of the last data on each vector.
    **/
    float* getLast(); //Vague: specialized struct instead ?
    
    
    /**
    * /brief    Return the value of ignoreFlag
    * /details  The select based server check this to know if the data are wanted.
    *
    * @return  ignoreFlag The current ignore flag.
    **/
    bool toIgnore();
    
    
    /**
    * /brief    Return the vector containing the worst notes.
    * /details Getter.
    *
    * @return  vector A pointer to the vector.
    **/
    std::vector<float>* getWorstVector();
    
    
    /**
    * /brief    Return the vector containing the best notes.
    * /details Getter.
    *
    * @return  vector A pointer to the vector.
    **/
    std::vector<float>* getBestVector();
    
    
    /**
    * /brief    Return the vector containing the standard deviation of the
    * population.
    * /details Getter.
    *
    * @return  vector A pointer to the vector.
    **/
    std::vector<float>* getStDevVector();
    
    
    /**
    * /brief    Return the vector containing the average notes of the population.
    * /details Getter.
    *
    * @return  vector A pointer to the vector.
    **/
    std::vector<float>* getAverageVector();
    
    
    /*Setter----------------------------------------------------------------------*/
    /**
    * /brief    Set the ignore flag.
    * /details  Data will not be process/add if ignoreFlag is true. 
    *
    *  @param  value New value of the ignoreFlag.
    **/
    void setIgnoreFlag(bool value);
  
  
  private:
  
    /* Data-----------------------------------------------------------------------*/
    int clientSockfd;
    int nbData;
    bool ignoreFlag;
    std::vector<float> best;
    std::vector<float> average;
    std::vector<float> stdev;
    std::vector<float> worst;
};

#endif
