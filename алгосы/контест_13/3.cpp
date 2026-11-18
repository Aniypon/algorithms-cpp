#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int m, n;
    cin >> m >> n;

    vector<vector<bool>> adj(m + 1, vector<bool>(n + 1, false));

    for (int i = 1; i <= m; i++) {
        int girl;
        while (cin >> girl && girl != 0) {
            adj[i][girl] = true;
        }
    }

    int maxSize = 0;
    vector<int> bestBoys;
    vector<int> bestGirls;

    if (n > 0) {
        vector<int> allGirls;
        for (int j = 1; j <= n; j++) {
            allGirls.push_back(j);
        }
        maxSize = allGirls.size();
        bestBoys.clear();
        bestGirls = allGirls;
    }

    if (m > 0 && m > maxSize) {
        vector<int> allBoys;
        for (int i = 1; i <= m; i++) {
            allBoys.push_back(i);
        }
        maxSize = allBoys.size();
        bestBoys = allBoys;
        bestGirls.clear();
    }

    if (m <= 20) {

        for (int boysSubset = 1; boysSubset < (1 << m); boysSubset++) {
            vector<int> boys;
            for (int i = 0; i < m; i++) {
                if ((boysSubset >> i) & 1) {
                    boys.push_back(i + 1);
                }
            }

            vector<int> girls;
            for (int j = 1; j <= n; j++) {
                bool allKnow = true;
                for (int boy : boys) {
                    if (!adj[boy][j]) {
                        allKnow = false;
                        break;
                    }
                }
                if (allKnow) {
                    girls.push_back(j);
                }
            }

            if (boys.size() + girls.size() > maxSize) {
                maxSize = boys.size() + girls.size();
                bestBoys = boys;
                bestGirls = girls;
            }
        }
    } else {

        vector<bool> useBoy(m + 1, true);
        vector<bool> useGirl(n + 1, true);

        bool changed = true;
        while (changed) {
            changed = false;

            for (int j = 1; j <= n; j++) {
                if (useGirl[j]) {
                    for (int i = 1; i <= m; i++) {
                        if (useBoy[i] && !adj[i][j]) {
                            useGirl[j] = false;
                            changed = true;
                            break;
                        }
                    }
                }
            }

            for (int i = 1; i <= m; i++) {
                if (useBoy[i]) {
                    for (int j = 1; j <= n; j++) {
                        if (useGirl[j] && !adj[i][j]) {
                            useBoy[i] = false;
                            changed = true;
                            break;
                        }
                    }
                }
            }
        }

        vector<int> boys, girls;
        for (int i = 1; i <= m; i++) {
            if (useBoy[i])
                boys.push_back(i);
        }
        for (int j = 1; j <= n; j++) {
            if (useGirl[j])
                girls.push_back(j);
        }

        if (boys.size() + girls.size() > maxSize) {
            maxSize = boys.size() + girls.size();
            bestBoys = boys;
            bestGirls = girls;
        }

        vector<pair<int, int>> boyPopularity;
        for (int i = 1; i <= m; i++) {
            int count = 0;
            for (int j = 1; j <= n; j++) {
                if (adj[i][j])
                    count++;
            }
            boyPopularity.push_back({count, i});
        }
        sort(boyPopularity.begin(), boyPopularity.end(), greater<pair<int, int>>());

        for (int k = 1; k <= min(30LL, m); k++) {
            vector<bool> tempBoys(m + 1, false);
            for (int i = 0; i < k; i++) {
                tempBoys[boyPopularity[i].second] = true;
            }

            vector<bool> tempGirls(n + 1, true);
            bool valid = true;

            for (int j = 1; j <= n; j++) {
                for (int i = 1; i <= m; i++) {
                    if (tempBoys[i] && !adj[i][j]) {
                        tempGirls[j] = false;
                        break;
                    }
                }
            }

            int tempSize = 0;
            for (int i = 1; i <= m; i++)
                if (tempBoys[i])
                    tempSize++;
            for (int j = 1; j <= n; j++)
                if (tempGirls[j])
                    tempSize++;

            if (tempSize > maxSize) {
                maxSize = tempSize;
                bestBoys.clear();
                bestGirls.clear();
                for (int i = 1; i <= m; i++)
                    if (tempBoys[i])
                        bestBoys.push_back(i);
                for (int j = 1; j <= n; j++)
                    if (tempGirls[j])
                        bestGirls.push_back(j);
            }
        }
    }

    cout << maxSize << endl;
    cout << bestBoys.size() << " " << bestGirls.size() << endl;

    for (int boy : bestBoys) {
        cout << boy << " ";
    }
    cout << endl;

    for (int girl : bestGirls) {
        cout << girl << " ";
    }
    cout << endl;
}

int32_t main() {
    int k;
    cin >> k;

    while (k--) {
        solve();
    }

    return 0;
}