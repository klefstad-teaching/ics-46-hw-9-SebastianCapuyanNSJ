#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg)
{
    cerr << word1 << word2 << msg;
}

bool edit_distance_within(const string& str1, const string& str2, int d) 
{
    int len1 = str1.size();
    int len2 = str2.size();

    if (abs(len1 - len2) > d) return false;

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; ++i) dp[i][0] = i;
    for (int j = 0; j <= len2; ++j) dp[0][j] = j;


    for (int i = 1; i <= len1; ++i) 
    {
        for (int j = 1; j <= len2; ++j) 
        {
            if (str1[i - 1] == str2[j - 1]) 
            {
                dp[i][j] = dp[i - 1][j - 1];  
            } 
            else 
            {
                dp[i][j] = min({dp[i - 1][j - 1],  
                                dp[i - 1][j],      
                                dp[i][j - 1]}) + 1;
            }
        }
    }

    return dp[len1][len2] <= d;
}

bool is_adjacent(const string& word1, const string& word2) 
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) 
{
    queue<vector<string>> ladder_queue;  
    vector<string> start_ladder = {begin_word};
    ladder_queue.push(start_ladder);


    set<string> visited;  
    visited.insert(begin_word);

    vector<string> empty;

    while (!ladder_queue.empty()) 
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (const string& word : word_list) 
        {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) 
            {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word) 
                {
                    return new_ladder;  
                }

                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }

    return empty;  
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream in(file_name);
    if (!in) 
    { 
        error(file_name, "could not be opened.", "");
        return;
    }

    string word;
    while (in >> word)
    {  
        word_list.insert(word);
    }

    in.close();  
}

void print_word_ladder(const vector<string>& ladder) 
{
    if (ladder.empty()) 
    {
        error("Ladder is empty.", "", "\n");
        return;
    }
    
    for (size_t i = 0; i < ladder.size(); ++i) 
    {
        cout << ladder[i] << endl;
    }
    cout << endl;
}

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}