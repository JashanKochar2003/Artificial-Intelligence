#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct CompareFirst {
    bool operator()(const pair<int, pair<int,int>>& p1, const pair<int, pair<int,int>>& p2) {
        return p1.first < p2.first;
    }
};

void string_to_array(vector<vector<int>>& adjMatrix, const string& para) {
    unordered_map<char, int> convertor;
    convertor[' '] = 26;
    convertor['.'] = 27;
    for (char i = 'a'; i <= 'z'; i++) {
        convertor[i] = int(i - 'a');
    }
    for (int i = 1; i < para.length(); i++) {
        int row = convertor[para[i - 1]];
        int col = convertor[para[i]];
        adjMatrix[row][col]++;
    }
}

char index_to_char(int i) {
   
        if (i <= 25) {
             return (char(i + 'a'));
        } else if (i == 26) {
            return ' ';
        } else if (i == 27) {
            return '.';
        }
        return '.';
    }


void printGraph(const vector<vector<int>>& adjMatrix) {
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<char> array_to_string(const vector<int>& ans) {
    vector<char> result;
    for (int i : ans) {
        if (i <= 25) {
            result.push_back(char(i + 'a'));
        } else if (i == 26) {
            result.push_back(' ');
        } else if (i == 27) {
            result.push_back('.');
        }
    }
    return result;
}

void bsf(const vector<vector<int>>& adjMatrix, vector<vector<bool>>& visited, vector<int>& ans, int startIndex) {
    
    priority_queue<pair<int, pair<int, int>>> pq;
    
    pq.push(make_pair(INT_MAX, make_pair(startIndex, startIndex)));
    int count = 0;

    while (!pq.empty()) {
        
        auto [cost, nodePair] = pq.top();
        int startIndex = nodePair.first;
        int currentNode = nodePair.second;
        pq.pop();

        
        if (!visited[startIndex][currentNode]) {
            visited[startIndex][currentNode] = true;
            ans.push_back(currentNode);

            if (count != 0) {
                cout << index_to_char(startIndex) << "->" << index_to_char(currentNode) << endl;
            }

            
            if (currentNode == 27) break;

            
            for (int nextNode = 0; nextNode < adjMatrix[currentNode].size(); ++nextNode) {
                if (adjMatrix[currentNode][nextNode] > 0 && !visited[startIndex][nextNode]) {
                    pq.push(make_pair(adjMatrix[currentNode][nextNode], make_pair(currentNode, nextNode)));
                }
            }
            count++;
        }
    }
}


int main() {
    string para =     "Everything was in confusion in the Oblonskys' house. The wife had "
    "discovered that the husband was carrying on an intrigue with a French "
    "girl, who had been a governess in their family, and she had announced to "
    "her husband that she could not go on living in the same house with him. "
    "This position of affairs had now lasted three days, and not only the "
    "husband and wife themselves, but all the members of their family and "
    "household, were painfully conscious of it. Every person in the house "
    "felt that there was no sense in their living together, and that the "
    "stray people brought together by chance in any inn had more in common "
    "with one another than they, the members of the family and household of "
    "the Oblonskys. The wife did not leave her own room, the husband had not "
    "been at home for three days. The children ran wild all over the house; "
    "the English governess quarreled with the housekeeper, and wrote to a "
    "friend asking her to look out for a new situation for her; the man-cook "
    "had walked off the day before just at dinner time; the kitchen-maid, and "
    "the coachman had given warning.\n\n"
    
    "Three days after the quarrel, Prince Stepan Arkadyevitch "
    "Oblonsky--Stiva, as he was called in the fashionable world--woke up at "
    "his usual hour, that is, at eight o'clock in the morning, not in his "
    "wife's bedroom, but on the leather-covered sofa in his study. He turned "
    "over his stout, well-cared-for person on the springy sofa, as though he "
    "would sink into a long sleep again; he vigorously embraced the pillow on "
    "the other side and buried his face in it; but all at once he jumped up, "
    "sat up on the sofa, and opened his eyes.\n\n"

    "Stepan Arkadyevitch's eyes twinkled gaily, and he pondered with a smile. "
    "There was a great deal more that was "
    "delightful, only there's no putting it into words, or even expressing it "
    "in one's thoughts awake.\" And noticing a gleam of light peeping in "
    "beside one of the serge curtains, he cheerfully dropped his feet over "
    "the edge of the sofa, and felt about with them for his slippers, a "
    "present on his last birthday, worked for him by his wife on gold-colored "
    "morocco. And, as he had done every day for the last nine years, he "
    "stretched out his hand, without getting up, towards the place where his "
    "dressing-gown always hung in his bedroom. And thereupon he suddenly "
    "remembered that he was not sleeping in his wife's room, but in his "
    "study, and why: the smile vanished from his face, he knitted his brows.\n\n"

    "Most unpleasant of all was the first minute when, on coming, happy and "
    "good-humored, from the theater, with a huge pear in his hand for his "
    "wife, he had not found his wife in the drawing-room, to his surprise had "
    "not found her in the study either, and saw her at last in her bedroom "
    "with the unlucky letter that revealed everything in her hand.\n\n"

    "She, his Dolly, forever fussing and worrying over household details, and "
    "limited in her ideas, as he considered, was sitting perfectly still with "
    "the letter in her hand, looking at him with an expression of horror, "
    "despair, and indignation.\n\n"

    "And at this recollection, Stepan Arkadyevitch, as is so often the case, "
    "was not so much annoyed at the fact itself as at the way in which he had "
    "met his wife's words.\n\n"

    "There happened to him at that instant what does happen to people when "
    "they are unexpectedly caught in something very disgraceful. He did not "
    "succeed in adapting his face to the position in which he was placed "
    "towards his wife by the discovery of his fault. Instead of being hurt, "
    "denying, defending himself, begging forgiveness, instead of remaining "
    "indifferent even--anything would have been better than what he did "
    "do--his face utterly involuntarily (reflex spinal action, reflected "
    "Stepan Arkadyevitch, who was fond of physiology)--utterly involuntarily "
    "assumed its habitual, good-humored, and therefore idiotic smile.\n\n"

    "This idiotic smile he could not forgive himself. Catching sight of that "
    "smile, Dolly shuddered as though at physical pain, broke out with her "
    "characteristic heat into a flood of cruel words, and rushed out of the "
    "room. Since then she had refused to see her husband.";
    transform(para.begin(), para.end(), para.begin(), ::tolower);
    vector<vector<int>> adjMatrix(28, vector<int>(28, 0));
    vector<int> ans;

    string_to_array(adjMatrix, para);
    printGraph(adjMatrix);

    vector<vector<bool>> visited(28, vector<bool>(28, false));
    int startIndex = 'e' - 'a';  

    bsf(adjMatrix, visited, ans, startIndex);

    vector<char> res = array_to_string(ans);
    cout << "BSF traversal: "<<endl;
    for (const auto& node : res) {
        cout << node << " ";
    }
    return 0;
}
