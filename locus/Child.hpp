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

/// Child class, used as base for all objects that behaves in parent-child structure
class Child {
public:
    /// Gets child name.
    string getName();

    /// Sets child name.
    void setName(string name);

    /// Gets all children as list.
    /// \return List of children.
    list<Child*> getChildren();

    /// Finds a specific child with name.
    /// \param childName Name of child to be found.
    /// \returns Found child.
    /// \throws runtime_error When child is not found.
    Child* getChildByName(string const childName);

    /// Adds another child.
    void addChild(Child* child);

    /// Removes a child. Doesn't delete the child object.
    void removeChild(Child* child);

    /// Removes a child specified by name.
    /// \param childName Name of child to be removed.
    void removeChildByName(string const childName);

    /// Is this child drawable?
    bool isDrawable;
protected:
    list<Child*>::iterator getChildByNameRecursive(string const childName);
    string name;
    list<Child*> children;
};


#endif /* Child_hpp */
