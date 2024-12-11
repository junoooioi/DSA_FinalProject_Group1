// Alcantara, Begino, Benavente, Mallari

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

// Node for Binary Search Tree
struct BSTNode {
    string team;
    int score;
    BSTNode* left;
    BSTNode* right;

    BSTNode(string t, int s) : team(t), score(s), left(NULL), right(NULL) {}
};

// Max-Heap Class
class MaxHeap {
    vector<pair<string, int>> heap;

    // Helper function to maintain heap property while moving down the tree
    void heapifyDown(int index) {
        int largest = index;  // Start with the current index as the largest
        int left = 2 * index + 1; // Left child index
        int right = 2 * index + 2; // Right child index

        // Check if left child exists and is greater than the current largest
        if (left < heap.size() && heap[left].second > heap[largest].second)
            largest = left;

        // Check if right child exists and is greater than the current largest
        if (right < heap.size() && heap[right].second > heap[largest].second)
            largest = right;

        // If largest is not the current index, swap and continue heapifying
        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

    // Helper function to maintain heap property while moving up the tree
    void heapifyUp(int index) {
        // Move up the tree while the parent is smaller than the current node
        while (index > 0 && heap[(index - 1) / 2].second < heap[index].second) {
            swap(heap[index], heap[(index - 1) / 2]); // Swap with the parent
            index = (index - 1) / 2; // Move to the parent's index
        }
    }

public:
    vector<pair<string, int>> teams;

    // Insert a new team and score into the heap
    void insert(const string& team, int score) {
        teams.push_back({team, score}); // Add new team and score to the heap
        heap.push_back({team, score});  // Add to the max-heap vector
        heapifyUp(heap.size() - 1);     // Maintain heap property
    }

    // Remove a team from the heap
    void remove(const string& team) {
        for (int i = 0; i < teams.size(); ++i) {
            if (teams[i].first == team) {
                teams.erase(teams.begin() + i);
                break;
            }
        }
        for (int i = 0; i < heap.size(); ++i) {
            if (heap[i].first == team) {
                heap[i] = heap.back(); // Replace with the last element
                heap.pop_back();       // Remove the last element
                if (i < heap.size()) {
                    heapifyDown(i);    // Rebalance the heap from index i
                    heapifyUp(i);      // Ensure the heap property is maintained
                }
                break;
            }
        }
    }

    //TRAVERSALS OPERATION

    // Display the Max-Heap leaderboard
    void display() const {
        cout << "\n=== Max-Heap Leaderboard ===\n";
        if (heap.empty()) {
            cout << "No teams in the leaderboard.\n";
            return;
        }
        for (int i = 0; i < heap.size(); ++i) {
            cout << i + 1 << ". " << heap[i].first << " - Score: " << heap[i].second << endl;
        }
    }

    // Display the Max-Heap elements from maximum to minimum
    void displaySorted() {
        cout << "\n=== Max-Heap (Sorted) ===\n";

        // Temporary heap to avoid modifying the original
        vector<pair<string, int>> tempHeap = heap;
        while (!tempHeap.empty()) {
            // Extract the maximum element repeatedly
            pair<string, int> maxElement = tempHeap[0];
            cout << maxElement.first << " - Score: " << maxElement.second << endl;

            // Move the last element to the root and maintain heap property
            tempHeap[0] = tempHeap.back();
            tempHeap.pop_back();

            // Heapify down the modified heap
            int index = 0;
            int largest = index;
            int left, right;

            do {
                largest = index;
                left = 2 * index + 1;
                right = 2 * index + 2;

                if (left < tempHeap.size() && tempHeap[left].second > tempHeap[largest].second)
                    largest = left;
                if (right < tempHeap.size() && tempHeap[right].second > tempHeap[largest].second)
                    largest = right;

                if (largest != index) {
                    swap(tempHeap[index], tempHeap[largest]);
                    index = largest;
                } else {
                    break;
                }
            } while (true);
        }
    }

    // Display the updated list of teams
    void displayUpdatedList() const {
        cout << "\n=== Updated List ===\n";
        if (teams.empty()) {
            cout << "No teams in the list.\n";
            return;
        }
        for (const auto& team : teams) {
            cout << team.first << " - Score: " << team.second << endl;
        }
    }
};

// Binary Search Tree Functions

//INSERTION IN BST

BSTNode* insertBST(BSTNode* root, const string& team, int score) {
    if (!root) return new BSTNode(team, score);
    if (score < root->score)
        root->left = insertBST(root->left, team, score);
    else if (score > root->score || (score == root->score && team < root->team))
        root->right = insertBST(root->right, team, score);
    return root;
}

//DELETATION IN BST

BSTNode* deleteBST(BSTNode* root, const string& team) {
    if (!root) return nullptr;

    if (team < root->team)
        root->left = deleteBST(root->left, team);
    else if (team > root->team)
        root->right = deleteBST(root->right, team);
    else {
        if (!root->left) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }
        BSTNode* temp = root->right;
        while (temp->left) temp = temp->left;
        root->team = temp->team;
        root->score = temp->score;
        root->right = deleteBST(root->right, temp->team);
    }
    return root;
}

//TRAVERSAL (IN-ORDER)

// Helper function for in-order traversal
void displayBSTInOrder(BSTNode* root, int& rank) {
    if (!root) return;

    displayBSTInOrder(root->left, rank);
    cout << rank << ". " << root->team << " - Score: " << root->score << endl;
    rank++;
    displayBSTInOrder(root->right, rank);
}

//TRAVERSAL (PRE-ORDER)

// Helper function for preorder traversal
void displayBSTPreOrder(BSTNode* root, int& rank) {
    if (!root) return;

    cout << rank << ". " << root->team << " - Score: " << root->score << endl;
    rank++;
    displayBSTPreOrder(root->left, rank);
    displayBSTPreOrder(root->right, rank);
}

//TRAVERSAL (POST-ORDER)

// Helper function for postorder traversal
void displayBSTPostOrder(BSTNode* root, int& rank) {
    if (!root) return;

    displayBSTPostOrder(root->left, rank);
    displayBSTPostOrder(root->right, rank);
    cout << rank << ". " << root->team << " - Score: " << root->score << endl;
    rank++;
}

// Wrapper function to display BST rankings
void showRankings(BSTNode* root) {
    cout << "\n=== Team Rankings (BST Traversal) ===\n";
    if (!root) {
        cout << "No teams to display.\n";
        return;
    }

    cout << "Choose a traversal method:\n";
    cout << "1. Preorder\n";
    cout << "2. Inorder\n";
    cout << "3. Postorder\n";
    cout << "Enter your choice (1-3): ";

    int traversalChoice;
    cin >> traversalChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int rank = 1; // Initialize rank counter

    switch (traversalChoice) {
    case 1:
        cout << "\n=== Preorder Traversal ===\n";
        displayBSTPreOrder(root, rank);
        break;
    case 2:
        cout << "\n=== Inorder Traversal ===\n";
        displayBSTInOrder(root, rank);
        break;
    case 3:
        cout << "\n=== Postorder Traversal ===\n";
        displayBSTPostOrder(root, rank);
        break;
    default:
        cout << "Invalid choice! Showing Inorder traversal by default.\n";
        displayBSTInOrder(root, rank);
    }
}

// Modified displayHeap to show Max-Heap and Min-Heap sorted order
void displayHeap(vector<pair<string, int>> heap, bool isMaxHeap) {
    cout << "\n=== Leaderboard (" << (isMaxHeap ? "Max-Heap (Descending)" : "Min-Heap (Ascending)" ) << ") ===\n";

    // Sort the heap for display purposes
    vector<pair<string, int>> sortedHeap = heap;
    sort(sortedHeap.begin(), sortedHeap.end(),
         [isMaxHeap](const pair<string, int>& a, const pair<string, int>& b) {
             return isMaxHeap ? a.second > b.second : a.second < b.second;
         });

    for (const auto& item : sortedHeap) {
        cout << item.first << " - Score: " << item.second << endl;
    }
}

// Updated Option 4 Menu
void displayHeapMenu(const MaxHeap& maxHeap) {
    cout << "\n=== Heap Leaderboard Options ===\n";
    cout << "1. Heapify for Max Heap\n";
    cout << "2. Heapify for Min Heap\n";
    cout << "Choose an option (1-2): ";

    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
    case 1:
        displayHeap(maxHeap.teams, true);  // Display as Max-Heap (Descending)
        break;
    case 2:
        displayHeap(maxHeap.teams, false); // Display as Min-Heap (Ascending)
        break;
    default:
        cout << "Invalid choice! Defaulting to Max-Heap.\n";
        displayHeap(maxHeap.teams, true); // Default to Max-Heap
    }
}


// Updated Menu Function
void menu(MaxHeap& maxHeap, BSTNode*& bstRoot) {
    int choice, score;
    string team;

    do {
        cout << "\n=== Tournament Ranking System ===\n";
        cout << "1. Add a Team and Score\n";
        cout << "2. Remove a Team\n";
        cout << "3. View Rankings (Sorted BST)\n";
        cout << "4. Show Leaderboard\n";
        cout << "5. Exit\n";
        cout << "---------------------------------\n";
        cout << "Choose an option (1-5): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Enter team name: ";
            getline(cin, team);
            cout << "Enter team score: ";
            cin >> score;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bstRoot = insertBST(bstRoot, team, score);
            maxHeap.insert(team, score);
            cout << "Team added successfully!";
            maxHeap.displayUpdatedList();
            break;

        case 2:
            cout << "Enter team name to remove: ";
            getline(cin, team);
            bstRoot = deleteBST(bstRoot, team);
            maxHeap.remove(team);
            cout << "Team removed successfully!";
            maxHeap.displayUpdatedList();
            break;

        case 3:
            showRankings(bstRoot);
            break;

        // Updated Option 4 in menu
        case 4:
            displayHeapMenu(maxHeap); // Updated to include both Max-Heap and Min-Heap
            break;


        case 5:
            cout << "End of Program.\n";
            break;

        default:
            cout << "Invalid choice! Please select a valid option.\n";
        }
    } while (choice != 5);
}

int main() {
    MaxHeap maxHeap;
    BSTNode* bstRoot = NULL;

    menu(maxHeap, bstRoot);

    return 0;
}
