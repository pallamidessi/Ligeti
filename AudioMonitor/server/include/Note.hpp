/**
 * @file note.hpp
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

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define NOTE_1 1
#define NOTE_2 2
#define NOTE_3 3
#define NOTE_4 4

class Note{
  public:
    Note (){}
    virtual ~Note (){}
    
    virtual int computeNote()=0;
    virtual std::vector<int> getNoteHistory(){return mNoteHistory;}

  protected:
    std::vector<int> mNoteHistory; 
    
    bool mQualityNotation;
    bool mQuantityNotation;

    float mBestDiffRatio;
    float mWorstDiffRatio;
    float mAverageDiffRatio;
    float mStdevDiffRatio;
};

