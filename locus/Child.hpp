//
//  Child.hpp
//  locus
//
//  Created by Marián Hlaváč on 26/11/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Child_hpp
#define Child_hpp

#include <string>
#include <list>


using namespace std;

class Child {
public:
    string getName();
    void setName(string name);
    list<Child*> getChildren();
    Child* getChildByName(string const childName);
    void addChild(Child* child);
    void removeChild(Child* child);
    void removeChildByName(string const childName);
    bool isDrawable;
protected:
    string name;
    list<Child*> children;
};


#endif /* Child_hpp */
