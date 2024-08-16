#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <iostream>

using namespace std;

int pmat[51][51]; // 선물 행렬

int solution(vector<string> friends, vector<string> gifts) {
    int answer = 0;
    unordered_map<string, int> fno; // 친구 번호
    unordered_map<int, int> prate; // 선물 지수
    vector<int> np(friends.size()); // 다음달에 받을 선물 갯수

    // unordered map을 이용해 행렬과 함께 사용가능케 함
    for (int i = 0; i < friends.size(); i++) {
        fno[friends[i]] = i;
        prate[i] = 0;
    }

    // vector gifts를 토대로 선물 행렬 작성
    for (auto i: gifts) {
        // ' '를 기준으로 선물 준 놈과 받은 놈을 나눔
        string from = i.substr(0,i.find(' '));
        string to = i.substr(i.find(' ') + 1);

        int fromi = fno[from];
        int toi = fno[to];
        // int fromi = distance(friends.begin(), find(friends.begin(), friends.end(), from));
        // int toi = distance(friends.begin(), find(friends.begin(), friends.end(), to));

        pmat[fromi][toi]++;
    }

    // 선물 지수 도출
    for (int i = 0; i < friends.size(); i++) {
        for (int j = 0; j < friends.size(); j++) {
            if (pmat[i][j]) {
                prate[i] += pmat[i][j];
                prate[j] -= pmat[i][j];
            }
        }
    }

    vector<pair<int,int>> compared; // 중복 확인 방지
    // 연산 드가자
    for (auto i: friends) {
        for (auto j: friends) {
            int f1 = fno[i]; int f2 = fno[j];
            if (find(compared.begin(), compared.end(), make_pair(f2,f1)) == compared.end()) {
                if (pmat[f1][f2] ==  pmat[f2][f1]) { // pmat_f1f2, pmat_f2f1 모두 0일 때 기록이 없음, 즉 같다 조건으로 모두 해결 가능
                    if (prate[f1] > prate[f2]) np[f1]++;
                    else if (prate[f1] < prate[f2]) np[f2]++;
                    else ; // 선물 지수도 같으면 주고 받지 않음
                }
                else { // 서로 선물을 준 개수로 판단
                    if (pmat[f1][f2] > pmat[f2][f1]) np[f1]++;
                    else np[f2]++;
                }
                compared.push_back(make_pair(f1, f2));
            }
        }
    }

    for (auto i: np) answer = max(i, answer);
    return answer;

}

//# pragma region 테스트
//
//int main() {
//    vector<string> friends = {"joy", "brad", "alessandro", "conan", "david"};
//    vector<string> gifts = {"alessandro brad", "alessandro joy", "alessandro conan", "david alessandro", "alessandro david"};
//    cout << solution(friends, gifts);
//    return 0;
//}
//
//#pragma endregion
