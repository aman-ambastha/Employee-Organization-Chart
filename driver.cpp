/**
 * Start of a driver file to test orgtree.cpp
 * CS 210 Summer 2023
 * @author Aman Ambastha
 * @date Jun 2023
 */

#include "orgtree.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MOST CASES ARE
 * HIDDEN ON GRADESCOPE.
 */

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void asserts(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
		// If you do comment this out, ignore the
		// "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Construct the following organization chart for testing
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     */

    Employee *head = new Employee(1, vector<int> {2, 3, 4}); // Head Employee ID : 1
    // Direct Employees Reporting To Head : 51, 52, 53
    Employee *e2 = head->getDirectReports().at(0); // Get Employee Pointer With ID 2
    Employee *e3 = head->getDirectReports().at(1); // Get Employee Pointer With ID 3
    Employee *e4 = head->getDirectReports().at(2); // Get Employee Pointer With ID 4

    e2->addDirectReports(vector<int>{5, 6});
    // Direct Employees Reporting To Employee With ID 2 : 5, 6
    e3->addDirectReports(vector<int>{7, 8});
    // Direct Employees Reporting To Employee With ID 3 : 7, 8
    e4->addDirectReport(9);
    // Direct Employees Reporting To Employee With ID 4 : 9

   Employee *e5 = e2->getDirectReports().at(0); // Get Employee Pointer With ID 5
   Employee *e6 = e2->getDirectReports().at(1); // Get Employee Pointer With ID 6
   Employee *e9 = e4->getDirectReports().at(0); // Get Employee Pointer With ID 9

   e5->addDirectReport(10);
   // Direct Employees Reporting To Employee With ID 5 : 10
   e6->addDirectReport(11);
   // Direct Employees Reporting To Employee With ID 6 : 11
   e9->addDirectReport(12);
   // Direct Employees Reporting To Employee With ID 9 : 12

    // Begin Testing
    // A few sample testing code are provided below
    
    // TODO Test all Orgtree functions
    //      according to the specifications in the comment section ABOVE each function signature. 
    
    // IMPORTANT: You should also construct at least one different chart 
    // Also make sure to check edge cases, such as empty chart, or one employee chart.

    // Test isEmployeePresentInOrg function
    cout << "Testing isEmployeePresentInOrg Function " << endl;
    // Test For Returning Correct Output For If Employee ID 6 Is Present In Org Chart

    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 6);
    asserts(employeePresent, "ID 6 Present In Tree");

    // Test For Returning Correct Output For If Employee ID -2 Is Present In Org Chart

    employeePresent = Orgtree::isEmployeePresentInOrg(head, -2);
    asserts(!employeePresent, "ID -2 Not Present In Tree");

    // My Own Test For isEmployeePresentInOrg function on same organization chart / tree
    // Test For Returning Correct Output For If Employee ID 9 Is Present In Org Chart

    bool checkOwnEmployeePresent = Orgtree::isEmployeePresentInOrg(head, 9);
    asserts(checkOwnEmployeePresent, "ID 9 Present In tree");

    // Test For Returning Correct Output For If Employee ID 19 Is Present In Org Chart

    checkOwnEmployeePresent = Orgtree::isEmployeePresentInOrg(head, 19);
    asserts(!checkOwnEmployeePresent, "ID 19 Not Present In Tree");

    cout << endl;

    //TODO...

    // Test findManagersOfEmployee function
    cout << "Testing findManagersOfEmployee Function " << endl;
    vector<int> manager_ids;
    // Test Function For Returning Correct Mangers Of Employee 11

    employeePresent = Orgtree::findManagersOfEmployee(head, 11, manager_ids);
    asserts(employeePresent, "ID 11 Present In Tree");
    vector<int> expected_manager_ids{ 6, 2, 1 };
    asserts(manager_ids == expected_manager_ids, "Your code should return (6, 2, 1) as managers of employee 11");
    manager_ids.clear();

    // Test Function For Returning Correct Mangers Of Employee -2

    employeePresent = Orgtree::findManagersOfEmployee(head, -2, manager_ids);
    asserts(manager_ids.size() == 0, "ID -2 Not Present In Tree, its manager ids should be empty");

   // My own Test For findManagersOfEmployee function on same organization chart / tree
   // Test Function For Returning Correct Mangers Of Employee 8

   checkOwnEmployeePresent = Orgtree::findManagersOfEmployee(head, 8, manager_ids);
   asserts(checkOwnEmployeePresent, "ID 8 Present In Tree");
   vector<int> expected_manager_ids2{3, 1};
   asserts(manager_ids == expected_manager_ids2, "Your code should return (3, 1) as managers of employee 8");
   manager_ids.clear();

   cout << endl;


    //TODO...

    // Test findEmployeeLevel function
    cout << "Testing findEmployeeLevel Function " << endl;
    // Test For Returning Correct Output For The Level Of Employee ID 2

    int employeeLevel = Orgtree::findEmployeeLevel(head, 2, 0);
    asserts(employeeLevel == 1, "Level of ID 2 returns " + to_string(employeeLevel) + ", expected 1");

    // My own Test for findEmployeeLevel on same organization chart / tree
    // Test For Returning Correct Output For The Level Of Employee ID 9

   employeeLevel = Orgtree::findEmployeeLevel(head, 9, 0);
   asserts(employeeLevel == 2, "Level of ID 9 returns " + to_string(employeeLevel) + ", expected 2");

    // Test For Returning Correct Output For The Level Of Employee ID 12.

   employeeLevel = Orgtree::findEmployeeLevel(head, 12, 0);
   asserts(employeeLevel == 3, "Level of ID 12 returns " + to_string(employeeLevel) + ", expected 3");

    // Test For Returning Correct Output For The Level Of Employee ID 18

   employeeLevel = Orgtree::findEmployeeLevel(head, 18, 0);
   asserts(employeeLevel == Employee::NOT_FOUND, "Level of ID 18 returns " + to_string(employeeLevel) + ", expected -1");

   cout << endl;

    //TODO...

    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID

    cout << "Testing findEmployeeLevel Function " << endl;
    // Test For Returning Correct Closest Shared Manager Between Employee ID 3 and 4

    Employee * a = Orgtree::findClosestSharedManager(head, 3, 4);
    asserts(a->getEmployeeID() == 1, "Closest Shared ID is " + to_string(a->getEmployeeID()) + ", expected 1");

    // Test For Returning Correct Closest Shared Manager Between Employee 7 and 8

    a = Orgtree::findClosestSharedManager(head, 7, 8);
    asserts(a->getEmployeeID() == 3, "Closest Shared ID is " + to_string(a->getEmployeeID()) + ", expected 3");

    // Test For Returning Correct Closest Shared Manager Between Employee ID 19 and 23

    a = Orgtree::findClosestSharedManager(head, 19, 23);
    asserts(a == nullptr, "Should return nullptr");

    cout << endl;

    //TODO...
    // TODO numManagers = ...

    // Test findNumOfManagersBetween function
    cout << "Testing findNumOfManagersBetween Function " << endl;
    // Test For Return Correct # Of Managers Between Employee ID 10 and 11

    int numManagers = Orgtree::findNumOfManagersBetween(head, 10, 11);
    asserts(numManagers == 3, "Managers between 10 and 11 returns " + to_string(numManagers) + ", expected 3");

    // My own test for findNumOfManagersBetween function
    // Test For Return Correct # Of Managers Between Employee ID 11 and 12

    numManagers = Orgtree::findNumOfManagersBetween(head, 11, 12);
    asserts(numManagers == 5, "Managers between 11 and 12 returns " + to_string(numManagers) + ", expected 5");

    // Test For Return Correct # Of Managers Between Employee ID 19 and 23

    numManagers = Orgtree::findNumOfManagersBetween(head, 19, 23);
    asserts(numManagers == Employee::NOT_FOUND, "Correctly returned -1");

    cout << endl;

    // Test deleteOrgtree function
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteOrgtree function at the end of this driver testing code
    // to delete all the allocated memory for the tree. 
    cout << "Testing deleteOrgtree Function " << endl;
    // Test deleteOrgtree Function. Nodes should be printed in post-order manner.
    // All memory should be deallocated on the heap.
    Orgtree::deleteOrgtree(head);
    cout << endl << "All test cases passed!" << endl;
    cout << endl;

    // Use the printed employee ID along the sequence of deletion to verify your implementation
    // This part will be autograded as well as manually inspected for grading

    cout << " ------------------------------------------------------------------------------------------- " << endl;
    cout << " ------------------------------------------------------------------------------------------- " << endl;
    cout << endl;
    cout << "Testing New Organizational Chart. ID's will begin from 50" << endl << endl;

    /*
    * Construct new organization chart for testing purposes
    *                50
    *           /     \    \
    *          51     52    53
    *         / \     / \    \
    *        54 55   57 58    59
    *       /   / \          / \
    *      60  61  62       63  64
    *         / \          /    / \
    *        65  66       67   68 69
    */

    Employee *head2 = new Employee(50, vector<int> {51, 52, 53}); // Head Employee ID : 50
    // Direct Employees Reporting To Head : 51, 52, 53
    Employee *e51 = head2->getDirectReports().at(0); // Get Employee Pointer With ID 51
    Employee *e52 = head2->getDirectReports().at(1); // Get Employee Pointer With ID 52
    Employee *e53 = head2->getDirectReports().at(2); // Get Employee Pointer With ID 53

    e51->addDirectReports(vector<int>{54, 55});
    // Direct Employees Reporting To 51 : 54, 55
    e52->addDirectReports(vector<int>{57, 58});
    // Direct Employees Reporting To 52 : 57, 58
    e53->addDirectReport(59);
    // Direct Employees Reporting To 53 : 59

    Employee *e54 = e51->getDirectReports().at(0); // Get Employee Pointer With ID 54
    Employee *e55 = e51->getDirectReports().at(1); // Get Employee Pointer With ID 55
    Employee *e59 = e53->getDirectReports().at(0); // Get Employee Pointer With ID 59

    e54->addDirectReport(60);
    // Direct Employees Reporting To 54 : 60
    e55->addDirectReports(vector<int>{61, 62});
    // Direct Employees Reporting To 55 : 61, 62
    e59->addDirectReports(vector<int>{63, 64});
    // Direct Employees Reporting To 59 : 63, 64

    Employee *e61 = e55->getDirectReports().at(0);  // Get Employee Pointer With ID 61
    e61->addDirectReports(vector<int>{65, 66});
    // Direct Employees Reporting To 61 : 65, 66

    Employee *e63 = e59->getDirectReports().at(0);  // Get Employee Pointer With ID 63
    Employee *e64 = e59->getDirectReports().at(1);  // Get Employee Pointer With ID 64
    e63->addDirectReport(67);
    // // Direct Employees Reporting To 63 : 67
    e64->addDirectReports(vector<int>{68, 69});
    // Direct Employees Reporting To 64 : 68, 69

    // Test isEmployeePresentInOrg function
    cout << "Testing isEmployeePresentInOrg Function " << endl;
    // Test For Returning Correct Output For If Employee ID 57 Is Present In Org Chart

    bool employeePresent2 = Orgtree::isEmployeePresentInOrg(head2, 57);
    asserts(employeePresent2, "ID 57 Is Present In Tree");

    // Test For Returning Correct Output For If Employee ID 89 Is Present In Org Chart

    employeePresent2 = Orgtree::isEmployeePresentInOrg(head2, 89);
    asserts(!employeePresent2, "ID 89 Not Present In Tree");

    // Test For Returning Correct Output For If Employee ID 64 Is Present In Org Chart

    bool checkOwnEmployeePresent2 = Orgtree::isEmployeePresentInOrg(head2, 64);
    asserts(checkOwnEmployeePresent2, "ID 64 Is Present In Tree");

    // Test For Returning Correct Output For If Employee ID 60 Is Present In Org Chart

    checkOwnEmployeePresent2 = Orgtree::isEmployeePresentInOrg(head2, 60);
    asserts(checkOwnEmployeePresent2, "ID 60 Is Present In Tree");

    // Test For Returning Correct Output For If Employee ID 68 Is Present In Org Chart

    checkOwnEmployeePresent2 = Orgtree::isEmployeePresentInOrg(head2, 68);
    asserts(checkOwnEmployeePresent2, "ID 68 Is Present In Tree");

    // Test For Returning Correct Output For If Employee ID 99 Is Present In Org Chart

    employeePresent2 = Orgtree::isEmployeePresentInOrg(head2, 99);
    asserts(!employeePresent2, "ID 99 Not Present In Tree");

    cout << endl;

    // Test findManagersOfEmployee function
    cout << "Testing findManagersOfEmployee Function " << endl;
    vector<int> manager_ids2;
    // Test Function For Returning Correct Mangers Of Employee 61

    employeePresent2 = Orgtree::findManagersOfEmployee(head2, 61, manager_ids2);
    asserts(employeePresent2, "ID 61 Present In Tree");
    vector<int> expected_manager_ids2_1 {55, 51, 50};
    asserts(manager_ids2 == expected_manager_ids2_1, "Your code should return (55, 51, 50) as managers of employee 61");
    manager_ids2.clear();

    // Test Function For Returning Correct Mangers Of Employee 67

    employeePresent2 = Orgtree::findManagersOfEmployee(head2, 67, manager_ids2);
    asserts(employeePresent2, "ID 67 Present In Tree");
    vector<int> expected_manager_ids2_2 {63, 59, 53, 50};
    asserts(manager_ids2 == expected_manager_ids2_2, "Your code should return (63, 59, 53, 50) as managers of employee 67");
    manager_ids2.clear();

    // Test Function For Returning Correct Mangers Of Employee 89

    employeePresent2 = Orgtree::findManagersOfEmployee(head2, 89, manager_ids2);
    asserts(manager_ids2.size() == 0, "ID 89 Not Present In Tree, its manager ids should be empty");

    cout << endl;

    // Test findEmployeeLevel function
    cout << "Testing findEmployeeLevel Function " << endl;
    // Test For Returning Correct Output For The Level Of Employee ID 61.

    int employeeLevel2 = Orgtree::findEmployeeLevel(head2, 61, 0);
    asserts(employeeLevel2 == 3, "Level of ID 61 returns " + to_string(employeeLevel2) + ", expected 3");

    // Test For Returning Correct Output For The Level Of Employee ID 59.

    employeeLevel2 = Orgtree::findEmployeeLevel(head2, 59, 0);
    asserts(employeeLevel2 == 2, "Level of ID 59 returns " + to_string(employeeLevel2) + ", expected 2");

    // Test For Returning Correct Output For The Level Of Employee ID 52.

    employeeLevel2 = Orgtree::findEmployeeLevel(head2, 52, 0);
    asserts(employeeLevel2 == 1, "Level of ID 52 returns " + to_string(employeeLevel2) + ", expected 1");

    // Test For Returning Correct Output For The Level Of Employee ID 66.

    employeeLevel2 = Orgtree::findEmployeeLevel(head2, 66, 0);
    asserts(employeeLevel2 == 4, "Level of ID 66 returns " + to_string(employeeLevel2) + ", expected 4");

    // Test For Returning Correct Output For The Level Of Employee ID 100.

    employeeLevel2 = Orgtree::findEmployeeLevel(head2, 100, 0);
    asserts(employeeLevel2 == Employee::NOT_FOUND, "Level of ID 100 returns " + to_string(employeeLevel2) + ", expected -1");

    cout << endl;

    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID

    cout << "Testing findClosestSharedManager Function " << endl;
    // Test For Returning Correct Closest Shared Manager Between Employee ID 61 and 62

    Employee * closest  = Orgtree::findClosestSharedManager(head2, 61, 62);
    asserts(closest->getEmployeeID() == 55, "Closest Shared ID is " + to_string(closest->getEmployeeID()) + ", expected 55");

    // Test For Returning Correct Closest Shared Manager Between Employee ID 64 and 67

    closest = Orgtree::findClosestSharedManager(head2, 64, 67);
    asserts(closest->getEmployeeID() == 59, "Closest Shared ID is " + to_string(closest->getEmployeeID()) + ", expected 59");

    // Test For Returning Correct Closest Shared Manager Between Employee ID 60 and 54

    closest = Orgtree::findClosestSharedManager(head2, 60, 54);
    asserts(closest->getEmployeeID() == 54, "Closest Shared ID is " + to_string(closest->getEmployeeID()) + ", expected 54");

    // Test For Returning Correct Closest Shared Manager Between Employee ID 58 and 93

    closest = Orgtree::findClosestSharedManager(head2, 58, 93);
    asserts(closest->getEmployeeID() == 58, "Closest Shared ID is " + to_string(closest->getEmployeeID()) + ", expected 58");

    // Test For Returning Correct Closest Shared Manager Between Employee ID 65 and 69

    closest = Orgtree::findClosestSharedManager(head2, 65, 69);
    asserts(closest->getEmployeeID() == 50, "Closest Shared ID is " + to_string(closest->getEmployeeID()) + ", expected 50");

    // Test For Returning Correct Closest Shared Manager Between Employee ID 51 and 66

    closest = Orgtree::findClosestSharedManager(head2, 51, 66);
    asserts(closest->getEmployeeID() == 51, "Closest Shared ID is " + to_string(closest->getEmployeeID()) + ", expected 51");

    // Test For Returning Correct Closest Shared Manager Between Employee ID 84 and 89

    closest = Orgtree::findClosestSharedManager(head2, 84, 89);
    asserts(closest == nullptr, "Should return nullptr");

    cout << endl;

    // Test findNumOfManagersBetween function
    cout << "Testing findNumOfManagersBetween Function " << endl;
    // Test For Return Correct # Of Managers Between Employee ID 60 and 55

    int numManagers2 = Orgtree::findNumOfManagersBetween(head2, 60, 55);
    asserts(numManagers2 == 2, "Managers between 60 and 55 returns " + to_string(numManagers2) + ", expected 2");

    // Test For Return Correct # Of Managers Between Employee ID 57 and 58

    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 57, 58);
    asserts(numManagers2 == 1, "Managers between 57 and 58 returns " + to_string(numManagers2) + ", expected 1");

    // Test For Return Correct # Of Managers Between Employee ID 55 and 59

    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 55, 59);
    asserts(numManagers2 == 3, "Managers between 55 and 59 returns " + to_string(numManagers2) + ", expected 3");

    // Test For Return Correct # Of Managers Between Employee ID 62 and 59

    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 62, 59);
    asserts(numManagers2 == 4, "Managers between 62 and 59 returns " + to_string(numManagers2) + ", expected 4");

    // Test For Return Correct # Of Managers Between Employee ID 34 and 90

    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 34, 90);
    asserts(numManagers2 == Employee::NOT_FOUND, "Correctly returned -1");

    cout << endl;

    cout << "Testing deleteOrgtree Function " << endl;
    // Test deleteOrgtree Function. Nodes should be printed in post-order manner.
    // All memory should be deallocated on the heap.
    Orgtree::deleteOrgtree(head2);
    cout << endl << "All test cases passed!" << endl;
    cout << endl;

    cout << " ------------------------------------------------------------------------------------------- " << endl;
    cout << " ------------------------------------------------------------------------------------------- " << endl;
    cout << endl;
    cout << "Testing Empty Organizational Chart. Edge Case Testing " << endl << endl;

    // No Chart Needs To Be Constructed. Empty Chart Is Represented By head == nullptr.
    // This chart is for edge case testing

    Employee * head3 = nullptr; // Empty Chart

    // Test isEmployeePresentInOrg function
    cout << "Testing isEmployeePresentInOrg Function" << endl;
    // Test With Empty Chart. Pass Random ID of 57
    bool employeePresent3 = Orgtree::isEmployeePresentInOrg(head3, 57);
    asserts(!employeePresent3, "Empty Chart, No Employees Present");
    cout << endl;

    // Test findManagersOfEmployee function
    cout << "Testing findManagersOfEmployee Function " << endl;
    // Test With Empty Chart. Pass Random ID of 57
    vector<int> manager_ids3;
    employeePresent3 = Orgtree::findManagersOfEmployee(head3, 57, manager_ids3);
    asserts(!employeePresent3 && manager_ids3.size() == 0, "Empty Chart, No Employees Present");
    cout << endl;

    // Test findEmployeeLevel function
    cout << "Testing findEmployeeLevel Function " << endl;
    // Test With Empty Chart. Pass Random ID of 57
    int employeeLevel3 = Orgtree::findEmployeeLevel(head3, 57, 0);
    asserts(employeeLevel3 == Employee::NOT_FOUND, "Empty Chart, No Employees Present");
    cout << endl;

    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID

    cout << "Testing findClosestSharedManager Function " << endl;
    // Test With Empty Chart. Pass Random ID's of 57 and 58
    Employee * closest2 = Orgtree::findClosestSharedManager(head3, 57, 58);
    asserts(closest2 == nullptr, "Empty Chart, No Employees Present");
    cout << endl;

    // Test findNumOfManagersBetween function
    cout << "Testing findNumOfManagersBetween Function " << endl;
    // Test With Empty Chart. Pass Random ID's of 57 and 58
    int numManagers3 = Orgtree::findNumOfManagersBetween(head3, 57, 58);
    asserts(numManagers3 == Employee::NOT_FOUND, "Empty Chart, No Employees Present");
    cout << endl;

    cout << "Testing deleteOrgtree Function " << endl;
    // Test With Empty Chart. No memory really needs to be deallocated.
    Orgtree::deleteOrgtree(head3);
    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}
