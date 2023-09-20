#include "orgtree.h"
#include <iostream>
using namespace std;
/* Single Programmer Affidavit: I, the undersigned promise that the submitted assignment is my own work. While I was
 free to discuss ideas with others, the work contained is my own. I recognize that should this not be the case;
 I will be subject to penalties as outlined in the course syllabus. */

// Name: Aman Ambastha
// Red ID: 827938027

/**
 * Check if an employee is present in an organization chart. 
 * 
 * @param  head the head / root Employee of the organization chart
 * @param  e_id the employee id being searched
 * @return      true or false
 *		returns false if head is nullptr
 * @see         
 */
bool Orgtree::isEmployeePresentInOrg(Employee* head, int e_id) {
  // Write your recursive implementation here

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.

  // Base Case 1: Empty Organization Chart, Return False, because no employees exist
  // A chart is empty if the head pointer is equal to nullptr.
  if (head == nullptr){
      return false;
  }
  // Base Case 2: If the employee is found, return true
  if (head->getEmployeeID() == e_id){
      return true;
  }
  // Recursive Case:
  // Search employee in each subtree of the head using for loop to iterate through directReports vector.
  for (int x = 0; x < head->getDirectReports().size(); x++){
      if(isEmployeePresentInOrg(head->getDirectReports().at(x), e_id)){ // Recursive Calling
          return true; // Return True if the employee is found in one of the child subtree
      }
  }
  // If employee is not found in the tree or organizational chart, return false
  return false;
}

/**
 * Find all managers of an employee. 
 * 
 * @param  head     the head / root Employee of the organization chart
 * @param  e_id     the employee id being searched
 * @param  managers a vector of ids of all managers in the ascending order 
 *                  of their tree height
 *                  i.e., managers starting from direct manager node to the root node
 *                  If the org chart is empty, or e_id is the head, or 
 *                  e_id is not in the chart, managers should be empty after the search. 
 * @return          is employee found
 * @see         
 */
bool Orgtree::findManagersOfEmployee(Employee* head, int e_id, vector<int> &managers) {

  // The implementation should be similar to isEmployeePresentInOrg

  // Base Case 1: Empty Organization Chart, Return False, because no employees exist
  // A chart is empty if the head pointer is equal to nullptr.
  if(head == nullptr){
      return false;
  }
  // Base Case 2: If the employee is found, return true. Also means managers will be added to the managers vector
  // unless the ID passed is the head manager's.
  if(head->getEmployeeID() == e_id){
      return true;
  }
  // Recursive Case:
  // Search subtrees from the head through iteration of directReports vector, after all subtrees are searched, if the
  // employee is found, add all the managers to the vector and return true.
    for (int x = 0; x < head->getDirectReports().size(); x++){
        if(findManagersOfEmployee(head->getDirectReports().at(x), e_id, managers)) { // Recursive Calling
            // Employee was found
            // Insert managers to vector along the backtracking process of recursive calls
            managers.push_back(head->getEmployeeID());
            return true; // Return True, because employee was found. Managers vector should not be empty.
        }
    }
  // Return False if employee is not found & managers vector should be empty.
  return false;
}

/**
 * Find the level of an employee in an organization chart / tree. 
 * 
 * <p>
 * The head / root of the org chart has a level of 0, children of the head have
 * a level of head plus 1, and so on and so forth... 
 * 
 * <p>
 * Assumption: e_id is unique among all employee IDs
 *
 * @param  head      the head / root Employee of the organization chart
 * @param  e_id      the employee id being searched
 * @param  headLevel the level of the head employee of the organization 
 * @return    level of the employee in the org chart
 *      returns Employee::NOT_FOUND if e_id is not present or head is nullptr
 * @see         
 */
int Orgtree::findEmployeeLevel(Employee* head, int e_id, int headLevel) {
    // Write your recursive implementation here.

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    // Base Case 1: Empty Organization Chart, Return False, because no employees exist
    // A chart is empty if the head pointer is equal to nullptr. So, return -1 = Employee::NOT_FOUND
    if (head == nullptr) {
        return Employee::NOT_FOUND;
    }
    // Base Case 2: The employee is found and return the employee's level in organizational chart.
    if (head->getEmployeeID() == e_id) {
        return headLevel;
    }
    // Recursive Case: Search subtrees from the head through iteration of directReports vector,
    // after all subtrees are searched, if the employee is found, return the employee's level.
    for (int x = 0; x < head->getDirectReports().size(); x++){
        // While searching the subtrees, the level increases by 1, so pass headLevel + 1 in the recursive call.
        int level = findEmployeeLevel(head->getDirectReports().at(x), e_id, headLevel + 1);
        if(level != Employee::NOT_FOUND){ // Implies employee was found
            return level; // Return employee's level.
        }
    }
    // If the employee was not found after searching all subtrees (the complete organization chart), return
    // -1 = Employee::NOT_FOUND. Since employee is not found, there is no level. So return -1.
    return Employee::NOT_FOUND;
}

/**
 * Find the closest shared manager of two employees e1 and e2. 
 * 
 * <p>
 * There are two possible organizational relationships between two employees in the org chart:
 * case 1: e1 or e2 is a manager of the other employee; 
 * case 2: e1 or e2 is not a manager of the other employee, they have at least one shared manager
 *
 * Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee 2 in the organization chart 
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   closest shared manager in the org chart between employee e1 and employee e2
   *           if head is nullptr, returns nullptr
   *           if neither e1 or e2 is present, returns nullptr
   *           if e1 is present and e2 is not, returns e1
   *           if e2 is present and e1 is not, returns e2
   *           if e1 and e2 both are present, returns their shared manager
   *              if e1 is a manager (ancestor) of e2, returns e1
   *              else if e2 is a manager (ancestor) of e1, returns e2
   *              else returns the shared manager of e1 and e2
 * @see         
 */
Employee* Orgtree::findClosestSharedManager(Employee* head, int e1_id, int e2_id) {
    // Write your recursive implementation here

    // Important: Your implementation MUST use the recursive approach
    // as required in the assignment 3 prompt to avoid penalties.

    Employee * firstEmployee = nullptr; // Employee pointer for first found employee
    Employee * secondEmployee = nullptr; // Employee pointer for second found employee

    // Base Case 1: Empty Organization Chart, no employees present in tree, so return nullptr.
    // A chart is empty if the head pointer is equal to nullptr
    if (head == nullptr) {
        return nullptr;
    }
    // Base Case 2: Either e1_id or e2_id is the same as the head / root
    // So return the head / root. This also means that either the first employee or second employee was found.
    if (head->getEmployeeID() == e1_id || head->getEmployeeID() == e2_id) {
        return head;
    }
    // Recursive Case: Traverse through the subtrees of the head by iterating through the directReports vector
    // and find where the employees are.
    for (int x = 0; x < head->getDirectReports().size(); x++) {
        if (firstEmployee == nullptr){ // If firstEmployee != nullptr, first employee has been found.
            // Search and find firstEmployee recursively. Recursive Calling of Function
            firstEmployee = findClosestSharedManager(head->getDirectReports().at(x), e1_id, e2_id);
        }
        else {
            // If first employee has been found, search for second employee recursively. Recursive Calling of Function.
            secondEmployee = findClosestSharedManager(head->getDirectReports().at(x), e1_id, e2_id);
        }
        if (firstEmployee != nullptr && secondEmployee != nullptr) {
           // If the first employee is found in one subtree, and the other is found from another subtree,
           // the head at that recursive step would be the closest shared manager of the employees
           return head; // Return head as closest shared manager
        }
    }
   // If either the first or second employee is first found in one subtree (following one subtree),
   // but the other employee is NOT found from any other subtree, then the found
   // employee must either be the manager of the other employee, or the other employee
   // is NOT in the org chart; in either case, the first found employee should be
   // returned as the shared manager.
    if (firstEmployee != nullptr) {
        return firstEmployee; // Return first found employee.
    }
    return nullptr; // If neither employee is found in the org chart, return nullptr.
}

/**
 * Calculate the number of managers between employee e1 and employee e2. 
 * 
 * <p>
 * The number of managers between employee e1 and employee e2 can be calculated by: 
 *  number of edges between employee 1 and closest shared manager + 
 *  number of edges between employee 2 and closest shared manager - 1
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   number of managers between employee e1 and employee e2
 *           returns Employee::NOT_FOUND if either e1 or e2 is not present in the chart or head is nullptr
 * @see         
 */
int Orgtree::findNumOfManagersBetween(Employee* head, int e1_id, int e2_id) {

    // Write your implementation here. You do NOT need to use recursive approach here.

    int managersBetween; // Variable to hold the value of number of managers between
    // If neither employee's ID is found in the organization chart, which means the employees are not in the chart
    if (!(isEmployeePresentInOrg(head, e1_id)) || !(isEmployeePresentInOrg(head, e2_id))) {
        return Employee::NOT_FOUND; // Return -1 = Employee::NOT_FOUND
    }
    // Otherwise, calculate number of managers between because both employees are found
    // Number of Managers Between = Number of edges between e1_id and closest shared manager +
    // Number of edges between e2_id and closest shared manager - 1

    Employee *closestManager = findClosestSharedManager(head, e1_id, e2_id); // Find the closest shared manager
    // After this managersBetween = Number of edges between e1_id and closest shared manager.
    managersBetween = (findEmployeeLevel(head, e1_id, 0) - findEmployeeLevel(head, closestManager->getEmployeeID(), 0));

    // After this managersBetween = Number of edges between e1_id and closest shared manager +
    // Number of edges between e2_id and closest shared manager.
    managersBetween += (findEmployeeLevel(head, e2_id, 0) - findEmployeeLevel(head, closestManager->getEmployeeID(), 0));

    managersBetween--; // Subtract 1 from managersBetween to get total managers between the two employees.

    return managersBetween; // Return number of managers between the two employees.
}
  // Use the above functions wherever you need to implement this function.

/** Recursively delete a tree 
 *  The proper implementation of this function is also needed for
 *  passing the valgrind memory leaking test. 
 * 
 * <p>
 * Traversing from the head / root node, recursively deallocate 
 * the memory of the descendants from the leaf node level. 
 *
 * DO NOT worry about removing them from the vector directReports
 * 
 * Use post order traversal:
 * Delete / deallocate the children recursively
 * Delete / deallocate the current node after deleting its children
 *     Before deleting the current node, print its employee ID and a new line
 *     This part will be autograded as well as manually inspected for grading
 * 
 * For example, with the following org chart, the post order traversal
 * order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
 *             1
 *           /    \
 *           2    3
 *          / \  / \
 *          5 6  7 8
 *
 * @param  head  the head / root Employee of the organization chart
 * @return   None 
 * 
 * @see         
 */
void Orgtree::deleteOrgtree(Employee* head) {
  // Write your recursive implementation here

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.

  // Base Case: Empty Organizational Chart, so no employees to delete.
  if(head == nullptr){
      return;
  }
  // Recursive Case: Delete children in the subtrees recursively by iterating through the directReports vector
  // The traversal will result in the head employee being deleted last. Post - Order traversal will be used
  // Left - Right - Root
  for (int x = 0; x < head->getDirectReports().size(); x++){
      deleteOrgtree(head->getDirectReports().at(x)); // Recursively delete children
  }
  // Print node's employee ID and a new line before deleting
  cout << head->getEmployeeID() << endl; // Print employees in the subtrees ID before deleting
  delete head; // Delete employee.
}
